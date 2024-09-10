/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaldhahe <zaldhahe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 17:20:55 by zaldhahe          #+#    #+#             */
/*   Updated: 2024/09/08 17:20:55 by zaldhahe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_philo(t_data *data)
{
	t_fork	*forks;
	int		i;

	forks = data->arrfork;
	i = 0;
	gettimeofday(&data->start_time, NULL);
	data->start = (data->start_time.tv_sec * 1e3)
		+ (data->start_time.tv_usec / 1e3);
	while (i < data->pnum)
	{
		data->arrphilo[i].data = data;
		data->arrphilo[i].id = i + 1;
		data->arrphilo[i].meal_count = 0;
		data->arrphilo[i].fork_1 = &forks[i];
		data->arrphilo[i].fork_2 = &forks[(i + 1) % data->pnum];
		my_thread(&data->arrphilo[i].thread, (void *)start_feeding,
			&data->arrphilo[i], CREATE);
		i++;
	}
	i = -1;
	while (++i < data->pnum)
		my_thread(&data->arrphilo[i].thread, NULL, &data->arrphilo[i], JOIN);
}

void	set_forks(t_data *data)
{
	int		i;
	t_fork	*temp;

	i = 0;
	while (++i <= data->pnum)
	{
		temp = &data->arrfork[i - 1];
		if (!temp)
			return ;
		temp->forkid = i;
		temp->last_used = i;
		if (i % 2)
			temp->last_used--;
		if (i == 1)
			temp->last_used = data->pnum;
		if ((data->pnum % 2) && (data->pnum == i))
			temp->last_used = i;
		my_mutex(&data->arrfork[i - 1].fork_mutex, INIT);
	}
}

void	set_data(t_data *data)
{
	if (data->count == 5 || data->count == 4)
	{
		data->pnum = ft_atoi(data->avsplit[0], data);
		if (data->pnum > 200)
			freexit(data->avstr, data->avsplit, data);
		data->pdie = ft_atoi(data->avsplit[1], data);
		data->peat = ft_atoi(data->avsplit[2], data);
		data->psleep = ft_atoi(data->avsplit[3], data);
		data->end = 0;
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
	freeing(data->avstr, data->avsplit, data);
	data->arrphilo = ft_calloc(data->pnum, sizeof(t_philo));
	data->arrfork = ft_calloc(data->pnum, sizeof(t_fork));
	my_mutex(&data->write_mutex, INIT);
	set_forks(data);
	set_philo(data);
}
