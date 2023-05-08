# ifndef PIPEX_H
# define PIPEX_H


#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <errno.h>

size_t	ft_strlen(const char *s);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char *s1, char *s2);
char *remove_spaces(char *av);
char *ft_options(char *av);
int	ft_count_opt(char *av);
char *ft_path(char *av);
char **ft_args(char *av);
int	free_tab(char **tab);
int ft_pid1(int *fd, char **av);
int ft_pid2(int *fd, char **av);
int	ft_parse(int ac, char **av);

# endif