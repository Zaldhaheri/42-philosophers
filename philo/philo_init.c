/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaldhahe <zaldhahe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 15:26:24 by zaldhahe          #+#    #+#             */
/*   Updated: 2024/08/27 18:23:47 by zaldhahe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void set_data(t_data *data)
{
	if (data->count == 5 || data->count == 4)
	{
		data->pnum = ft_atoi(data->avsplit[0], data);
		if (data->pnum > 200)
			freexit(data->avstr, data->avsplit, data);
		data->pdie = ft_atoi(data->avsplit[1], data);
		data->peat = ft_atoi(data->avsplit[2], data);
		data->psleep = ft_atoi(data->avsplit[3], data);
		if (data->count == 5)
			data->plimit = ft_atoi(data->avsplit[4], data);
        else
            data->plimit = -1;
	}
	else
	{
		printf(RED "Input error\n" RESET);
		freexit(data->avstr, data->avsplit, data);
	}
}

void	philo_setfork(t_philo *philo, t_fork *arrfork, int x)
{
	if (philo->id % 2) //odd
	{
		philo->fork_1 = &arrfork[(x + 1) % philo->data->pnum]; //left fork
		philo->fork_2 = &arrfork[x]; //right fork
	}
	else //even
	{
		philo->fork_1 = &arrfork[x];
		philo->fork_2 = &arrfork[(x + 1) % philo->data->pnum];
	}
}

void	philo_init(t_data *data)
{
	t_philo *philo;

	data->i = 0;
	while (data->i < data->pnum)
	{
		philo = &data->arrphilo[data->i];
		philo->id = data->i + 1;
		philo->full = 0;
		philo->meals = 0;
		philo->data = data;
		philo_setfork(philo, data->arrfork, data->i);
		data->i++;
	}

}

void data_init(t_data *data)
{
	data->end = 0;
	data->arrphilo = ft_calloc(data->pnum, sizeof(t_philo)); 
	data->arrfork = ft_calloc(data->pnum, sizeof(t_fork));
	my_mutex(&data->data_mutex, INIT);
	data->pready = 0;
    data->i = 0;
	while(data->i < data->pnum)
	{
		my_mutex(&data->arrfork[data->i].fork, INIT);
		data->i++;
	}
	philo_init(data);
}