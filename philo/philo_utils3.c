/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaldhahe <zaldhahe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 22:50:17 by zaldhahe          #+#    #+#             */
/*   Updated: 2024/09/08 17:25:39 by zaldhahe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	my_write(int status, t_philo *philo)
{
	long	time;

	my_mutex(&philo->data->write_mutex, LOCK);
	time = get_time(2) - philo->data->start;
	if (!get_int(&philo->data->data_mutex, &philo->data->end))
	{
		printf(BLUE"%ld"RESET" ", time);
		if (FIRST_FORK == status)
			printf(WHITE"%d has taken a fork\n" RESET, philo->id);
		else if (SECOND_FORK == status)
			printf(WHITE"%d has taken a fork\n" RESET, philo->id);
		else if (EATING == status)
			printf(GREEN"%d is eating\n" RESET, philo->id);
		else if (SLEEPING == status)
			printf(CYAN"%d is sleeping\n" RESET, philo->id);
		else if (THINKING == status)
			printf(YELLOW"%d is thinking\n"RESET, philo->id);
		else if (DIED == status)
			printf(RED"%d died\n"RESET, philo->id);
	}
	my_mutex(&philo->data->write_mutex, UNLOCK);
}

long	get_time(int i)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL))
		freerror(NULL, NULL, NULL, "gettimeofday failed\n");
	if (i == 1)
		return (time.tv_sec + (time.tv_usec / 1e6));
	else if (i == 2)
		return ((time.tv_sec * 1e3) + (time.tv_usec / 1e3));
	else if (i == 3)
		return ((time.tv_sec * 1e6) + time.tv_usec);
	else
		freerror(NULL, NULL, NULL, "Wrong input in get_time\n");
	return (999);
}

void	my_usleep(long usec, t_data *data)
{
	long	start;
	long	elapsed;

	start = get_time(3);
	while (!get_int(&data->data_mutex, &data->end))
	{
		elapsed = get_time(3) - start;
		if (elapsed >= usec)
			break ;
		if (usec - elapsed > 1000)
			usleep(500);
		else
			usleep(50);
	}
}

void	thinking(t_philo *philo)
{
	my_write(THINKING, philo);
	usleep(100);
}

int	dead(t_philo *philo)
{
	long	curr;
	long	t_die;

	if (get_int(&philo->philo_mutex, &philo->full))
		return (0);
	curr = get_time(2) - philo->meal_time;
	t_die = philo->data->pdie / 1000;
	if (curr > t_die)
		return (1);
	return (0);
}
