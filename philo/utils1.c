/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaldhahe <zaldhahe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 21:43:28 by zaldhahe          #+#    #+#             */
/*   Updated: 2024/07/07 21:47:27 by zaldhahe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

char	*ft_strdup(const char *str)
{
	char	*dup;
	int		i;

	i = 0;
	dup = (char *) malloc(ft_strlen(str) + 1);
	if (!dup)
		return (NULL);
	while (str[i])
	{
		dup[i] = str[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	size_t	j;
	char	*r;

	i = 0;
	j = 0;
	r = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 3));
	if (!r)
		return (NULL);
	while (s1[i])
	{
		r[i] = s1[i];
		i++;
	}
	r[i++] = ' ';
	while (s2[j])
		r[i++] = s2[j++];
	r[i++] = ' ';
	r[i] = '\0';
	return (r);
}

int	count_word(char const *s, char c)
{
	int	d;

	d = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		while (*s && *s != c)
		{
			s++;
			if (*s == c || !*s)
				d++;
		}
	}
	return (d);
}

char	*join_strings(char *av[])
{
	int		i;
	char	*r;
	char	*temp;

	i = 1;
	r = ft_strdup("");
	while (av[i])
	{
		temp = r;
		r = ft_strjoin(r, av[i++]);
		free(temp);
	}
	return (r);
}
