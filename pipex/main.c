/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itchinda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 17:06:20 by itchinda          #+#    #+#             */
/*   Updated: 2023/04/05 18:04:36 by itchinda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_options(char *av)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (av[i] == ' ')
		i++;
	while (av[i] != ' ' && av[i])
		i++;
	if (!av[i])
		return (NULL);
	while (av[i] == ' ')
		i++;
	j = i;
	while (av[j])
		j++;
	return (ft_substr(av, i, j - i));
}

char	*ft_path(char *av, t_data cmd, char **envp)
{
	(void)cmd;
	char	*goodenv;
	char	*command;

	command = ft_command(av);
	goodenv = which_envbis(command, envp);
	if (goodenv == NULL)
		return (command);
	free(command);
	return (goodenv);
}

int	ft_nboptions(char *av)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	av = ft_options(av);
	if (!av)
		return (0);
	while (av[i])
	{
		if (av[i] == ' ' || !av[i + 1])
			count++;
		i++;
	}
	return (count);
}

int	ft_parse(char **av, t_data cmd)
{
	(void)cmd;
	if (access(av[1], 0) == -1)
		return (write(2, "Infile: no such file or directory\n", 34));
	else
		return (0);
	return (0);
}

int	main(int ac, char **av, char *envp[])
{
	int			fd[2];
	t_data		cmd;

	if (ac != 5)
		return (write(2, "Invalid number of arguments\n", 28));
	cmd.env1 = envp;
	cmd.env2 = envp;
	cmd.path1 = ft_path(av[2], cmd, envp);
	cmd.path2 = ft_path(av[3], cmd, envp);
	cmd.args1 = ft_split(av[2], ' ');
	cmd.args2 = ft_split(av[3], ' ');
	ft_parse(av, cmd);
	ft_process(fd, cmd, av, envp);
	free_tab(cmd.args1);
	free_tab(cmd.args2);
	free(cmd.path2);
	return (0);
}
