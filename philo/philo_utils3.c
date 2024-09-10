/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaldhahe <zaldhahe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 20:16:40 by zaldhahe          #+#    #+#             */
/*   Updated: 2024/09/10 20:17:26 by zaldhahe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	sleepy(t_philo *philo)
{
	struct timeval	start;

	if (my_write(SLEEPING, philo))
		return (1);
	gettimeofday(&start, NULL);
	while (1)
	{
		if (is_dead(philo))
			return (1);
		usleep(200);
		if (my_wait(start, philo->data->psleep))
			break ;
	}
	return (0);
}

int	eat(t_philo *philo)
{
	if (my_write(EATING, philo))
		return (1);
	gettimeofday(&philo->last_eat, NULL);
	while (1)
	{
		if (is_dead(philo))
			return (1);
		usleep(200);
		if (my_wait(philo->last_eat, philo->data->peat))
			break ;
	}
	if (philo->data->plimit != -1)
	{
		philo->meal_count++;
		if (philo->meal_count == philo->data->plimit)
			return (1);
	}
	return (0);
}

int	is_dead(t_philo *philo)
{
	long	cur;
	int		ret;

	ret = 0;
	gettimeofday(&philo->curr_time, NULL);
	philo->death = (philo->curr_time.tv_sec * 1e3 + philo->curr_time.tv_usec
			/ 1e3) - (philo->last_eat.tv_sec * 1e3
			+ philo->last_eat.tv_usec / 1e3);
	cur = (philo->curr_time.tv_sec * 1e3
			+ philo->curr_time.tv_usec / 1e3) - philo->data->start;
	my_mutex(&philo->data->write_mutex, LOCK);
	if (philo->data->end)
		ret = 1;
	else if (philo->death >= philo->data->pdie)
	{
		printf(DIED, (int)(cur), philo->id);
		philo->data->end = 1;
		ret = 1;
	}
	my_mutex(&philo->data->write_mutex, UNLOCK);
	return (ret);
}
