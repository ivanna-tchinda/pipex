#include "pipex.h"


char *remove_spaces(char *av)
{
	int i;

	i = 0;
	while (av[i] == ' ')
		i++;
	return(ft_substr(av, i, ft_strlen(av) - i));
}

//ft_options

char *ft_options(char *av) //fonction qui ne retourne que les options d'une commande
{
	int	i;

	i = 0;
	av = remove_spaces(av);
	while (av[i] != ' ' && av[i])
		i++;
	av = ft_substr(av, i, ft_strlen(av) - i);
	return (av);
}

//ft_count_opt

int	ft_count_opt(char *av) //compte le nombre d'options
{
	int	i;
	int count;

	i = 0;
	count = 0;
	av = remove_spaces(av);
	while (av[i])
	{
		if (av[i] == ' ' || !(av[i + 1]))
			count++;
		i++;
	}
	return (count);
}

// ft_path

char *ft_path(char *av)
{
	char *temp;
	char *path;
	int	i;
	int j;
	int count;

	i = 0;
	j = 0;
	count = ft_count_opt(av);
	av = remove_spaces(av);
	temp = NULL;
	while (av[i]) //on recupere seulement la commande sans les options
	{
		if(av[i] == ' ' || !av[i + 1])
		{	
			if (count > 1)
				temp = ft_substr(av, j, i - j);
			else
				temp = ft_substr(av, j, i - j + 1);
			break;
		}
		i++;
	}
	path = ft_strjoin("/usr/bin/", temp);
	return (path);
}


//ft_args

char **ft_args(char *av) //invalid write size of 8
{
	int i;
	int count;
	char **args;
	int j;
	int iargs;

	count = ft_count_opt(av);
	i = 0;
	j = 0;
	iargs = 1;
	args = malloc(ft_strlen(ft_path(av)) * sizeof(char) + 16); //verifier que c'est bon pck bizarre
	if (!args)
		return(NULL);
	args[0] = ft_path(av); 
	av = ft_options(av);
	while (av[j] && count > 1)
	{
		while (av[j] == ' ')
			j++;
		i = j;
		while ((av[j] != ' ' && av[j + 1]))
			j++;
		args[iargs++] = ft_substr(av, i, j - i + 1);
		j++;
	}
	free(av);
	args[iargs] = NULL;
	return(args);
}
