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

void odd_philo(t_philo *philo)
{
	printf(MAGENTA "%d lil bro is thinking 💡\n" RESET, philo->id);
	pthread_mutex_lock(&philo->lfork->fork);
	pthread_mutex_lock(&philo->rfork->fork);
	printf(WHITE "%d lil bro took fork %d 🍽\n" RESET, philo->id, philo->lfork->forkid);
	printf(WHITE "%d lil bro took fork %d 🍽\n" RESET, philo->id, philo->rfork->forkid);
	printf(YELLOW "%d lil bro eating spaghetti 🍝\n" RESET, philo->id);
	pthread_mutex_unlock(&philo->rfork->fork);
	pthread_mutex_unlock(&philo->lfork->fork);
	printf(BLUE "%d lil bro sleeping 😴\n" RESET, philo->id);
}

void *hungy(void *arg)
{
	t_philo *philo;

	philo = (t_philo *) arg;
	// philo->lfork = &philo->data->arrfork[philo->id % (philo->data->pnum)];
	// philo->rfork = &philo->data->arrfork[(philo->id - 1) % (philo->data->pnum)];
	//printf("%d: left fork %d, right fork %d\n", philo->id, philo->lfork->forkid, philo->rfork->forkid);
	if (!philo->data || !philo)
	{
		printf("cant acces data\n");
		exit(1);
	}
	while (1)
	{
		odd_philo(philo);
	}
	return (NULL);
}

void create_philo(t_data *data)
{
	data->i = 0;
	while(data->i < data->pnum)
	{
		//printf("philo id: %d\nfork id: %d\n", data->arrphilo[data->i].id, data->arrfork[data->i].forkid);
		data->j = pthread_create(&data->arrphilo[data->i].pid, NULL, hungy, &data->arrphilo[data->i]);
		if (data->j != 0)
		{
			printf("Failed to create thread: %d\n", data->i);
			exit(1);
		}
		usleep(10);
		data->i++;
	}
	while(1);
	// data->i = 0;
    // while (data->i < data->pnum)
	// {
    //     pthread_join(data->arrphilo[data->i].pid, NULL);
    //     data->i++;
    // }
}

void create_table(t_data *data)
{
	data->arrphilo = ft_calloc(data->pnum, sizeof(t_philo)); 
	data->arrfork = ft_calloc(data->pnum, sizeof(t_fork));
	data->i = 0;
	while(data->i < data->pnum)
	{
		data->arrphilo[data->i].id = data->i + 1;
		data->arrfork[data->i].forkid = data->i;
		if(pthread_mutex_init(&data->arrfork[data->i].fork, NULL) != 0)
		{
			printf("Error creating fork mutex\n");
			exit (1);
		}
		data->arrphilo[data->i].data = data;
		data->i++;
	}
	data->i = 0;
	while(data->i < data->pnum)
	{
		data->arrphilo[data->i].lfork = &data->arrfork[(data->i + 1) % data->pnum];
		data->arrphilo[data->i].rfork = &data->arrfork[(data->i) % data->pnum];
		data->i++;
	}
}

int	main(int ac, char *av[])  
{
	(void)ac;
	t_data data;

	if (!checker(av, &data))
		exit(1);
	data.avstr = join_strings(av);
	data.avsplit = ft_split(data.avstr, ' ', &data);
	set_data(&data);
	printf("pnum: %d\n", data.pnum);
	printf("pdie: %ld\n",data.pdie);
	printf("peat: %ld\n",data.peat);
	printf("psleep: %ld\n",data.psleep);
	if (data.plimit)
		printf("plimit: %ld\n", data.plimit);
	freeing(data.avstr, data.avsplit, &data);
	create_table(&data);
	create_philo(&data);
	// free(data.arrphilo);
	// free(data.arrfork);
	return (0);
}
