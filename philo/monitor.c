/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaldhahe <zaldhahe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 22:46:13 by zaldhahe          #+#    #+#             */
/*   Updated: 2024/09/08 18:33:38 by zaldhahe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	monitor_synch(pthread_mutex_t *mutex, long *thread, long pnum)
{
	int	r;

	r = 0;
	my_mutex(mutex, LOCK);
	if (*thread == pnum)
		r = 1;
	my_mutex(mutex, UNLOCK);
	return (r);
}

void	*monitor_beasts(void *temp)
{
	t_data	*data;

	data = (t_data *)temp;
	while (!monitor_synch(&data->data_mutex,
			&data->running_threads, data->pnum))
		;
	while (!get_int(&data->data_mutex, &data->end))
	{
		data->j = -1;
		while (++data->j < data->pnum
			&& !get_int(&data->data_mutex, &data->end))
		{
			if (dead(data->arrphilo + data->j))
			{
				my_write(DIED, data->arrphilo + data->j);
				set_int(&data->data_mutex, &data->end, 1);
				break ;
			}
		}
	}
	return (NULL);
}

void	philo_synch(t_data *data)
{
	if (data->pnum == 1)
		return ;
	while (!get_int(&data->data_mutex, &data->pready))
		;
}

void	philo_desync(t_philo *philo)
{
	if (philo->data->pnum % 2 == 0)
	{
		if (philo->id % 2 == 0)
			my_usleep(300, philo->data);
	}
	else
	{
		if (philo->id % 2)
			sync_think(philo);
	}
}

void	sync_think(t_philo *philo)
{
	long	eat;
	long	sleep;
	long	think;

	if (philo->data->pnum % 2 == 0)
		return ;
	eat = philo->data->peat;
	sleep = philo->data->psleep;
	think = eat * 2 - sleep;
	if (think < 0)
		think = 0;
	my_usleep(think * 0.03, philo->data);
}
