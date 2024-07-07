/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaldhahe <zaldhahe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 21:45:04 by zaldhahe          #+#    #+#             */
/*   Updated: 2024/07/07 21:46:16 by zaldhahe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//checking, "1 2 3" 2 1 allowed
// 0 and negatives not allowed
// 4 or 5 arguments
//only numbers allowed

int	is_valid(char *av[], t_data *data)
{
	if (av[data->i][0] == 0)
		data->flag = 0;
	while (av[data->i][data->j] == ' ')
		data->j++;
	if (av[data->i][data->j] >= '1' && av[data->i][data->j] <= '9')
		data->flag = 1;
	else if (av[data->i][data->j] == '+' &&
			(av[data->i][data->j + 1] >= '1' &&
			av[data->i][data->j + 1] <= '9'))
	{
		data->flag = 1;
		if (data->j != 0 && av[data->i][data->j - 1] != ' ')
			data->flag = 0;
		data->j++;
	}
	while (av[data->i][data->j + 1] == ' ')
		data->j++;
	return (data->flag);
}

int	checker(char *av[], t_data *data)
{
	data->i = 1;
	while (av[data->i])
	{
		data->j = 0;
		if (av[data->i][0] == 0)
			return (0);
		while (av[data->i][data->j])
		{
			data->flag = 0;
			if (!is_valid(av, data))
				return (0);
			data->j++;
		}
		data->i++;
	}
	return (1);
}