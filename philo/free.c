/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaldhahe <zaldhahe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 22:42:10 by zaldhahe          #+#    #+#             */
/*   Updated: 2024/09/06 22:42:10 by zaldhahe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	freeing(char *str, char **string, t_data *data)
{
	int	i;

	i = -1;
	if (str)
		free(str);
	if (string)
	{
		while (++i <= data->count - 1)
			free(string[i]);
		free(string);
	}
}

void	free_data(t_data *data)
{
	int	i;

	i = 0;
	my_mutex(&data->write_mutex, DESTROY);
	while (i < data->pnum)
		my_mutex(&data->arrfork[i++].fork_mutex, DESTROY);
	if (data->arrfork)
		free(data->arrfork);
	if (data->arrphilo)
		free(data->arrphilo);
}
