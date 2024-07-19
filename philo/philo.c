/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 21:04:16 by zaldhahe          #+#    #+#             */
/*   Updated: 2024/07/16 23:29:20 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//allowed functions:
	// memset, printf, malloc, free, write,
	// usleep, gettimeofday, pthread_create,
	// pthread_detach, pthread_join, pthread_mutex_init,
	// pthread_mutex_destroy, pthread_mutex_lock,
	// pthread_mutex_unlock

//input:
	//number_of_philosophers,, time_to_die time_to_eat,,
	//time_to_sleep
	//number_of_times_each_philosopher_must_eat

//output:
	//timestamp_in_ms X has taken a fork
	//timestamp_in_ms X is eating
	//timestamp_in_ms X is sleeping
	//timestamp_in_ms X is thinking
	//timestamp_in_ms X died

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
	}
	else
		freexit(data->avstr, data->avsplit, data);
}

void make_list(t_philo *philo, t_data *data)
{
	t_philo *curr;
	t_philo *prev;

	curr = philo;
	
}

void make_philo(t_philo *philo, t_data *data)
{
	int i;

	i = 0;
	while(i < data->pnum)
	{
		pthread_create()
	}
}

int	main(int ac, char *av[])
{
	(void)ac;
	t_data data;
	t_philo *philo;

	if (!checker(av, &data))
		exit(1);
	data.avstr = join_strings(av);
	data.avsplit = ft_split(data.avstr, ' ', &data);
	set_data(&data);
	printf("pnum: %d\n", data.pnum);
	printf("pdie: %d\n",data.pdie);
	printf("peat: %d\n",data.peat);
	printf("psleep: %d\n",data.psleep);
	if (data.plimit)
		printf("plimit: %d\n", data.plimit);
	make_philo(philo, &data);
	return (0);
}
