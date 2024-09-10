/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaldhahe <zaldhahe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 20:15:23 by zaldhahe          #+#    #+#             */
/*   Updated: 2024/09/10 20:20:48 by zaldhahe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	my_write(char *status, t_philo *philo)
{
	long	time;

	my_mutex(&philo->data->write_mutex, LOCK);
	gettimeofday(&philo->curr_time, NULL);
	time = philo->curr_time.tv_sec * 1e3 + philo->curr_time.tv_usec / 1e3;
	if (!philo->data->end)
	{
		printf(status, time - philo->data->start, philo->id);
		my_mutex(&philo->data->write_mutex, UNLOCK);
		return (0);
	}
	my_mutex(&philo->data->write_mutex, UNLOCK);
	return (1);
}

int	my_wait(struct timeval start, int et)
{
	struct timeval	cur_time;
	long			res;

	res = 0;
	gettimeofday(&cur_time, NULL);
	if (!et)
		et = 50;
	res = (cur_time.tv_sec * 1000 + cur_time.tv_usec / 1000) - (start.tv_sec
			* 1000 + start.tv_usec / 1000);
	if (res < 0)
		res += 1000;
	if (res >= et)
		return (1);
	return (0);
}

int	unlock_fork(t_philo *philo, int flag)
{
	if (flag)
		my_mutex(&philo->fork_1->fork_mutex, UNLOCK);
	else
		my_mutex(&philo->fork_2->fork_mutex, UNLOCK);
	return (1);
}

void	unlock_forks(t_philo *philo)
{
	my_mutex(&philo->fork_1->fork_mutex, UNLOCK);
	my_mutex(&philo->fork_2->fork_mutex, UNLOCK);
}
