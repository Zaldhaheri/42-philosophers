/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaldhahe <zaldhahe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 17:21:08 by zaldhahe          #+#    #+#             */
/*   Updated: 2024/09/08 17:21:08 by zaldhahe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	odd(t_philo *philo)
{
	while (1)
	{
		my_mutex(&philo->fork_1->fork_mutex, LOCK);
		if (is_dead(philo))
			return (unlock_fork(philo, 1));
		my_mutex(&philo->fork_2->fork_mutex, LOCK);
		if (philo->id != philo->fork_1->last_used
			&& philo->id != philo->fork_2->last_used)
			break ;
		unlock_forks(philo);
		usleep(200);
	}
	unlock_forks(philo);
	if (my_write(FORK, philo) || my_write(FORK, philo))
		return (1);
	if (eat(philo) && philo->meal_count != philo->data->plimit)
		return (1);
	my_mutex(&philo->fork_1->fork_mutex, LOCK);
	philo->fork_1->last_used = philo->id;
	my_mutex(&philo->fork_2->fork_mutex, LOCK);
	philo->fork_2->last_used = philo->id;
	unlock_forks(philo);
	if (philo->meal_count == philo->data->plimit)
		return (1);
	return (0);
}

int	even(t_philo *philo)
{
	while (1)
	{
		my_mutex(&philo->fork_2->fork_mutex, LOCK);
		if (is_dead(philo))
			return (unlock_fork(philo, 0));
		my_mutex(&philo->fork_1->fork_mutex, LOCK);
		if (philo->id != philo->fork_1->last_used
			&& philo->id != philo->fork_2->last_used)
			break ;
		unlock_forks(philo);
		usleep(200);
	}
	unlock_forks(philo);
	if (my_write(FORK, philo) || my_write(FORK, philo))
		return (1);
	if (eat(philo) && philo->meal_count != philo->data->plimit)
		return (1);
	my_mutex(&philo->fork_2->fork_mutex, LOCK);
	philo->fork_2->last_used = philo->id;
	my_mutex(&philo->fork_1->fork_mutex, LOCK);
	philo->fork_1->last_used = philo->id;
	unlock_forks(philo);
	if (philo->meal_count == philo->data->plimit)
		return (1);
	return (0);
}

void	one_philo(t_philo *philo)
{
	gettimeofday(&philo->last_eat, NULL);
	if (is_dead(philo))
		return ;
	if (my_write(THINKING, philo))
		return ;
	my_mutex(&philo->fork_1->fork_mutex, LOCK);
	if (my_write(FORK, philo))
	{
		my_mutex(&philo->fork_1->fork_mutex, UNLOCK);
		return ;
	}
	while (1)
	{
		if (is_dead(philo))
		{
			my_mutex(&philo->fork_1->fork_mutex, UNLOCK);
			return ;
		}
	}
}

void	start_feeding(void *temp)
{
	t_philo	*philo;

	philo = (t_philo *)temp;
	if (philo->data->pnum == 1)
	{
		one_philo(philo);
		return ;
	}
	gettimeofday(&philo->last_eat, NULL);
	while (1)
	{
		if (philo->data->plimit == 0)
			return ;
		if (my_write(THINKING, philo))
			return ;
		if (philo->id % 2)
		{
			if (odd(philo))
				break ;
		}
		else if (even(philo))
			break ;
		if (sleepy(philo))
			break ;
	}
}

int	main(int ac, char **av)
{
	t_data	data;

	(void)ac;
	if (!checker(av, &data))
		exit(1);
	data.avstr = join_strings(av);
	data.avsplit = ft_split(data.avstr, ' ', &data);
	set_data(&data);
}
