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

void	spaghetti(t_philo *philo)
{
	my_mutex(&philo->fork_1->fork_mutex, LOCK);
	my_write(FIRST_FORK, philo);
	my_mutex(&philo->fork_2->fork_mutex, LOCK);
	my_write(SECOND_FORK, philo);
	set_long(&philo->philo_mutex, &philo->meal_time, get_time(2));
	philo->meals++;
	my_write(EATING, philo);
	my_usleep(philo->data->peat, philo->data);
	if (philo->data->plimit > 0 && philo->meals == philo->data->plimit)
		set_int(&philo->philo_mutex, &philo->full, 1);
	my_mutex(&philo->fork_1->fork_mutex, UNLOCK);
	my_mutex(&philo->fork_2->fork_mutex, UNLOCK);
}

void	*start_feeding(void *temp)
{
	t_philo	*philo;

	philo = (t_philo *)temp;
	philo_synch(philo->data);
	set_long(&philo->philo_mutex, &philo->meal_time, get_time(2));
	inc_long(&philo->data->data_mutex, &philo->data->running_threads);
	philo_desync(philo);
	while (!get_int(&philo->data->data_mutex, &philo->data->end))
	{
		if (philo->full)
			break ;
		spaghetti(philo);
		my_write(SLEEPING, philo);
		my_usleep(philo->data->psleep, philo->data);
		if (philo->full)
			break ;
		thinking(philo);
	}
	return (NULL);
}

void	*one_philo(void *temp)
{
	t_philo	*philo;

	philo = (t_philo *)temp;
	philo_synch(philo->data);
	set_long(&philo->philo_mutex, &philo->meal_time, get_time(2));
	inc_long(&philo->data->data_mutex, &philo->data->running_threads);
	my_write(FIRST_FORK, philo);
	usleep(philo->data->pdie);
	my_write(DIED, philo);
	while (!get_int(&philo->data->data_mutex, &philo->data->end))
		usleep(20000);
	return (NULL);
}

void	feed_the_beasts(t_data *data)
{
	data->i = -1;
	if (1 == data->pnum)
	{
		my_thread(&data->arrphilo[0].pid, one_philo,
			&data->arrphilo[0], CREATE);
		my_thread(&data->arrphilo[0].pid, NULL, NULL, DETACH);
		data->start = get_time(2);
		my_usleep(data->pdie * 1.5, data);
	}
	else
	{
		while (++data->i < data->pnum)
			my_thread(&data->arrphilo[data->i].pid, start_feeding,
				&data->arrphilo[data->i], CREATE);
		my_thread(&data->monitor, monitor_beasts, data, CREATE);
		data->start = get_time(2);
		set_int(&data->data_mutex, &data->pready, 1);
		data->i = -1;
		while (++data->i < data->pnum)
			my_thread(&data->arrphilo[data->i].pid, NULL,
				NULL, JOIN);
		set_int(&data->data_mutex, &data->end, 1);
		my_thread(&data->monitor, NULL, NULL, JOIN);
	}
}

int	main(int ac, char *av[])
{
	t_data	data;

	(void)ac;
	if (!checker(av, &data))
		exit(1);
	data.avstr = join_strings(av);
	data.avsplit = ft_split(data.avstr, ' ', &data);
	set_data(&data);
	freeing(data.avstr, data.avsplit, &data);
	data_init(&data);
	if (data.plimit != 0)
		feed_the_beasts(&data);
	destroy_mutexes(&data);
	free_data(&data);
	return (0);
}
