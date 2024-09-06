/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaldhahe <zaldhahe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 22:37:39 by zaldhahe          #+#    #+#             */
/*   Updated: 2024/09/06 22:37:39 by zaldhahe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_valid(char *av[], t_data *data)
{
	while (av[data->i][data->j] == ' ')
		data->j++;
	if (av[data->i][data->j] == '\0')
		return (0);
	while (av[data->i][data->j] != '\0')
	{
		while (av[data->i][data->j] == ' ')
			data->j++;
		if (av[data->i][data->j] == '+' &&
			(av[data->i][data->j + 1] >= '0'
				&& av[data->i][data->j + 1] <= '9'))
			data->j++;
		if (av[data->i][data->j] < '0' || av[data->i][data->j] > '9')
			return (0);
		while (av[data->i][data->j] >= '0' && av[data->i][data->j] <= '9')
			data->j++;
		while (av[data->i][data->j] == ' ')
			data->j++;
		if (av[data->i][data->j] != '\0' && av[data->i][data->j] != ' ' &&
			(av[data->i][data->j] < '0' || av[data->i][data->j] > '9'))
			return (0);
	}
	return (1);
}

int	checker(char *av[], t_data *data)
{
	data->i = 1;
	while (av[data->i])
	{
		data->j = 0;
		if (!is_valid(av, data))
			return (0);
		data->i++;
	}
	return (1);
}
