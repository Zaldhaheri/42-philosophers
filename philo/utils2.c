/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaldhahe <zaldhahe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 22:42:10 by zaldhahe          #+#    #+#             */
/*   Updated: 2024/09/06 22:42:10 by zaldhahe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	count_word(char const *s, char c, t_data *data)
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
	data->count = d;
	return (d);
}

char	*word(char const *s, char c)
{
	char	*str;
	int		i;

	i = 0;
	if (!s)
		return (NULL);
	while (s[i] && s[i] != c)
		i++;
	str = malloc(sizeof(char) * (i + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (s[i] && s[i] != c)
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	**ft_split(char const *s, char c, t_data *data)
{
	int		j;
	char	**r;

	j = 0;
	if (!s)
		return (NULL);
	r = malloc (sizeof(char *) * (count_word(s, c, data) + 1));
	if (!r)
		return (NULL);
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (*s && *s != c)
		{
			r[j] = word(s, c);
			j++;
			while (*s && *s != c)
				s++;
		}
	}
	r[j] = NULL;
	return (r);
}
