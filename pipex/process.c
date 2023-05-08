#include "pipex.h"

int ft_pid1(int *fd, char **av)
{
	char *path = ft_path(av[2]);
	char **args = ft_args(av[2]);

	fd[0] = open(av[1], O_RDONLY, 0777);
	fd[1] = open("temp.txt", O_RDWR | O_CREAT, 0777);

	dup2(fd[0], STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	unlink(av[4]);
	execve(path, args, NULL);

	if (execve(path, args, NULL) == -1)
		return(write(2, "zsh: command not found\n", 23));

	//free_tab(args);
	//free(path);
	close(fd[0]);
	close(fd[1]);
	exit(EXIT_SUCCESS);
	return(0);
}

int ft_pid2(int *fd, char **av)
{
	char *path2 = ft_path(av[3]);
	char **args2 = ft_args(av[3]);

	fd[1] = open("temp.txt", O_RDWR | O_CREAT, 0777);

	if (access(av[4], W_OK) == -1)
		fd[2] = open(av[4], O_WRONLY | O_CREAT, 0777);

	fd[2] = open(av[4], O_WRONLY, 0777);
	dup2(fd[1], STDIN_FILENO);
	dup2(fd[2], STDOUT_FILENO);
	unlink("temp.txt");
	execve(path2, args2, NULL);

	if (execve(path2, args2, NULL) == -1)
		return(write(2, "zsh: command not found\n", 23));

	//free_tab(args2);
	//free(path2);
	close(fd[1]);
	close(fd[2]);
	exit(EXIT_SUCCESS);
	return(0);
}