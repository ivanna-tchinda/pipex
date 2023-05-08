#include "pipex.h"

int	free_tab(char **tab)
{
	int	i;
	char *ptr_tab;

	i = 0;
	while (tab[i])
	{
		ptr_tab = tab[i];
		free(ptr_tab);
		i++;
	}
	free(tab);
	return (0);
}



int	ft_parse(int ac, char **av)
{
	if (ac != 5)
		return (write(2, "Invalid number of arguments\n", 28));
	else if (access(av[1], 0) == -1)
		return(write(2, "Infile: no such file or directory\n", 34));
	return (0);
}

int main(int ac, char **av)
{
	(void)ac;
	if (ft_parse(ac, av) != 0)
		return (1);
	int fd[3];
	if (pipe(fd) == -1)
		return 1;

	int pid1 = fork();
	if (pid1 == -1)
		return 1;
	if (pid1 == 0)
		ft_pid1(fd, av);
	int pid2 = fork();
	if (pid2 == -1)
		return 1;
	if (pid2 == 0)
	{
		waitpid(pid1, NULL, 0);
		ft_pid2(fd, av);
	}
	int pid3 = fork();
	if (pid3 == -1)
		return 1;
	if (pid3 == 0)
	{
		waitpid(pid2, NULL, 0);
		close(fd[0]);
		close(fd[1]);
		close(fd[2]);
	}
	return (0);
}