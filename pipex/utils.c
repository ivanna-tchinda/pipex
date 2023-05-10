/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itchinda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 18:11:05 by itchinda          #+#    #+#             */
/*   Updated: 2023/04/05 18:11:45 by itchinda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

static char	*ft_malloc(char const *s, unsigned int start, size_t len)
{
	char	*s2;

	if (ft_strlen(s) == 1 && start > ft_strlen(s))
		s2 = (char *)malloc(sizeof(char));
	else if (len > ft_strlen(s))
		s2 = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1));
	else if (start > ft_strlen(s))
		s2 = (char *)malloc(sizeof(char));
	else if (len == ft_strlen(s) && start < len && len != 0)
		s2 = (char *)malloc(sizeof(char) * (len - start) + 1);
	else
		s2 = (char *)malloc(sizeof(char) * (len + 1));
	return (s2);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*s2;

	i = 0;
	if (!s)
		return (NULL);
	s2 = ft_malloc(s, start, len);
	if (!s2)
		return (NULL);
	while (i < len && s[i] && start < ft_strlen(s))
	{
		s2[i] = s[start];
		i++;
		start++;
	}
	s2[i] = '\0';
	return (s2);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*join;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	join = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!join)
		return (NULL);
	while (s1[i])
	{
		join[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		join[i + j] = s2[j];
		j++;
	}
	join[i + j] = '\0';
	return (join);
}

void	ft_allocate(char **s2, char const *s, char c)
{
	char	**tab_s2;
	char	*tmp;

	tmp = (char *)s;
	tab_s2 = s2;
	while (*tmp)
	{
		while (*s == c)
			++s;
		tmp = (char *)s;
		while (*tmp && *tmp != c)
			++tmp;
		if (*tmp == c || tmp > s)
		{
			*tab_s2 = ft_substr(s, 0, tmp - s);
			s = tmp;
			++tab_s2;
		}
	}
	*tab_s2 = NULL;
}
