/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_functs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itchinda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 17:49:06 by itchinda          #+#    #+#             */
/*   Updated: 2023/04/05 18:05:06 by itchinda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_envir(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (strncmp(env[i], "PATH", 4) == 0)
			break ;
		i++;
	}
	return (env[i]);
}

char	*to_find(char **path, char *new_av)
{
	int		i;
	char	*to_find;

	i = 0;
	while (path[i])
	{
		to_find = ft_strjoin(path[i], new_av);
		free(path[i]);
		if (access(to_find, R_OK) == 0)
		{
			free(new_av);
			while (path[++i] != NULL)
				free(path[i]);
			free(path);
			return (to_find);
		}
		free(to_find);
		i++;
	}
	free(path);
	free(new_av);
	return (NULL);
}

char	*which_envbis(char *av, char **env)
{
	char	*new_av;
	char	**path;
	int		i;
	char	*old;

	i = 0;
	new_av = ft_strjoin("/", av);
	env[i] = ft_envir(env);
	if (!env[i])
		return (NULL);
	old = ft_substr(env[i], 5, ft_strlen(env[i]) - 5);
	path = ft_split(old, ':');
	free(old);
	return (to_find(path, new_av));
}

char	**which_env(char *av, char **env)
{
	char	*path;
	char	*new_av;
	char	**new_env;

	new_env = (char **)malloc(sizeof (char *) * 2);
	av = ft_command(av);
	new_av = ft_strjoin("/", av);
	while (*env != NULL)
	{
		path = ft_strjoin(*env, new_av);
		if (access(path, R_OK) == 0)
		{
			new_env[0] = *env;
			break ;
		}
		env++;
	}
	free(new_av);
	free(av);
	new_env[1] = NULL;
	free(path);
	return (new_env);
}

char	**find_env(char *av, char **envp)
{
	char	**env_vars;
	char	**env;

	while (*envp != NULL)
	{
		if (strncmp(*envp, "PATH", 4) == 0)
			break ;
		envp++;
	}
	env_vars = ft_split(*envp, ':');
	env = which_env(av, env_vars);
	if (env[0] == 0)
		free_tab(env_vars);
	else
		free_tabenv(env_vars, env[0]);
	return (env);
}
