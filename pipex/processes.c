/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itchinda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 18:05:39 by itchinda          #+#    #+#             */
/*   Updated: 2023/04/07 11:47:36 by itchinda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_command(char *av)
{
	int		i;
	int		j;
	char	*command;

	i = 0;
	j = 0;
	while (av[i] == ' ')
		i++;
	j = i;
	while (av[j] != ' ' && av[j])
		j++;
	command = ft_substr(av, i, j);
	return (command);
}

int	ft_pid1(int *fd, char **av, t_data cmd, char *envp[])
{
	int	infile;

	close(fd[0]);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
	infile = open(av[1], O_RDONLY, 0);
	dup2(infile, STDIN_FILENO);
	close(infile);
	if (access(av[1], R_OK) == -1)
	{
		write(2, "zsh: permission denied\n", 23);
		exit(EXIT_FAILURE);
	}
	if (execve(cmd.path1, cmd.args1, envp) == -1)
	{
		free(cmd.path1);
		free_tab(cmd.args1);
		free(cmd.path2);
		free_tab(cmd.args2);
		write(2, "zsh: command not found\n", 23);
		exit(EXIT_FAILURE);
	}
	return (0);
}

int	ft_pid2(int *fd, char **av, t_data cmd, char *envp[])
{
	int	outfile;

	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	outfile = open(av[4], O_TRUNC | O_CREAT | O_WRONLY, 0644);
	dup2(outfile, STDOUT_FILENO);
	close(outfile);
	if (access(av[4], W_OK) != 0)
	{
		write(2, "permission denied\n", 18);
		exit(EXIT_FAILURE);
	}
	if (execve(cmd.path2, cmd.args2, envp) == -1)
	{
		free(cmd.path1);
		free_tab(cmd.args1);
		free(cmd.path2);
		free_tab(cmd.args2);
		write(2, "zsh: command not found\n", 23);
		exit(EXIT_FAILURE);
	}
	return (0);
}

int	ft_process(int *fd, t_data cmd, char **av, char *envp[])
{
	int	pid1;
	int	pid2;

	if (pipe(fd) == -1)
		return (1);
	pid1 = fork();
	if (pid1 == 0)
		ft_pid1(fd, av, cmd, envp);
	pid2 = fork();
	if (pid2 == 0)
		ft_pid2(fd, av, cmd, envp);
	close(fd[0]);
	close(fd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	free(cmd.path1);
	return (0);
}
