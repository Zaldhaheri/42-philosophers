/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaldhahe <zaldhahe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 22:41:12 by zaldhahe          #+#    #+#             */
/*   Updated: 2024/09/06 22:42:19 by zaldhahe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str, t_data *data)
{
	int		i;
	int		s;
	long	r;

	i = 0;
	r = 0;
	s = 1;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i++] == '-')
			s *= -1;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		r = r * 10 + str[i++] - '0';
		if (r * s > INT_MAX || r * s < INT_MIN)
			freexit(data->avstr, data->avsplit, data);
	}
	return (r * s);
}

void	freexit(char *str, char **string, t_data *data)
{
	freeing(str, string, data);
	exit(1);
}

void	freerror(char *str, char **string, t_data *data, char *msg)
{
	printf("%s", msg);
	freexit(str, string, data);
}
