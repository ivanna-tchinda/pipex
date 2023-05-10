/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itchinda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 18:14:06 by itchinda          #+#    #+#             */
/*   Updated: 2023/04/07 11:46:53 by itchinda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <stdlib.h>
# include <errno.h>
# include <string.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 25
# endif

typedef struct s_data{
	char	*path1;
	char	*path2;
	char	**args1;
	char	**args2;
	char	**env1;
	char	**env2;
	char	*new_av;
	char	**path;
	char	*to_find;
	char	*old;
}		t_data;

size_t	ft_strlen(const char *s);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char *s1, char *s2);
void	ft_setvalues(char **av, char **envp, t_data cmd);
int		ft_parse(char **av, t_data cmd);
char	**find_env(char *av, char **envp);
char	*ft_path(char *av, t_data cmd, char **envp);
char	*ft_path2(char *av, int arg, t_data cmd);
char	**ft_args(char *av, int arg, t_data cmd);
void	ft_env(char *av, char **envp);
char	**ft_split(char const *s, char c);
char	**ft_split2(char const *s, char c);
char	**which_env(char *av, char **env);
char	*which_envbis(char *av, char **env);
void	ft_allocate(char **s2, char const *s, char c);
char	*ft_command(char *av);
char	*ft_options(char *av);
int		ft_nboptions(char *av);
void	free_values(t_data *cmd);
int		free_arg1(t_data *cmd);
void	free_tabenv(char **tab, char *env);
void	free_tab(char **tab);
int		ft_process(int *fd, t_data cmd, char **av, char *envp[]);
int		ft_pid1(int *fd, char **av, t_data cmd, char *envp[]);
int		ft_pid2(int *fd, char **av, t_data cmd, char *envp[]);
char	**find_env2(char *av, char **envp);

void	pipex_bonus(int *fd, int ac, char **av, char **envp);

#endif
