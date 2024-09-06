/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaldhahe <zaldhahe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 22:41:40 by zaldhahe          #+#    #+#             */
/*   Updated: 2024/09/06 22:41:40 by zaldhahe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ft_calloc(size_t count, size_t size)
{
	size_t	i;
	void	*str;

	i = 0;
	str = malloc(count * size);
	if (!str)
		return (0);
	while (i < (count * size))
		((char *)str)[i++] = '\0';
	return (str);
}

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
