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



// void odd_philo(t_philo *philo)
// {
// 	printf(MAGENTA "%d: lil bro is thinking 💡\n" RESET, philo->id);
// 	usleep(200);
// 	pthread_mutex_lock(&philo->lfork->fork);
// 	pthread_mutex_lock(&philo->rfork->fork);
// 	printf(WHITE "%d: lil bro took fork %d 🍽\n" RESET, philo->id, philo->lfork->forkid);
// 	printf(WHITE "%d: lil bro took fork %d 🍽\n" RESET, philo->id, philo->rfork->forkid);
// 	printf(YELLOW "%d: lil bro eating spaghetti 🍝\n" RESET, philo->id);
// 	pthread_mutex_unlock(&philo->rfork->fork);
// 	pthread_mutex_unlock(&philo->lfork->fork);
// 	printf(BLUE "%d: lil bro sleeping 😴\n" RESET, philo->id);
// }

int	get_int(pthread_mutex_t *mutex, int *value)
{
	int get;
	my_mutex(mutex, LOCK);
	get = *value;
	my_mutex(mutex, UNLOCK);
	return (get);
}

void set_int(pthread_mutex_t *mutex, int *set, int value)
{
	my_mutex(mutex, LOCK);
	*set = value;
	my_mutex(mutex, UNLOCK);
}

long	get_time(int i)
{
	struct timeval time;

	if (gettimeofday(&time, NULL))
		freerror(NULL, NULL, NULL, "gettimeofday failed\n");
	if (i == 1) //seconds
		return (time.tv_sec + (time.tv_usec / 1e6));
	else if (i == 2) // milliseconds
		return ((time.tv_sec * 1e3) + (time.tv_usec / 1e3));
	else if (i == 3) //microseconds
		return ((time.tv_sec *1e6) + time.tv_usec);
	else
		freerror(NULL, NULL, NULL, "Wrong input in get_time\n");
}

//void	my_usleep()

void	philo_synch(t_data *data)
{
	printf("synching\n");
	while(!get_int(&data->data_mutex, &data->pready))
		;
}

//wait for other philos to synchronize, then start
void	*start_feeding(void *temp)
{
	t_philo *philo;

	philo = (t_philo *)temp;
	philo_synch(philo->data);
	printf("in synch\n");
	//usleep(1000);
	while(!get_int(&philo->data->data_mutex, &philo->data->end))
	{
		printf("im in: %ld\n", get_time());
		if (philo->full)
			break;
		break;
		//beast_eating
		//beast_sleeping
		//beast_thinking
	}
	return (NULL);
}

void	feed_the_beasts(t_data *data)
{
	data->i = -1;
	if (data->plimit == 0)
		return ;
	else if (data->pnum == 1)
		return ;
	else
	{
		while (++data->i < data->pnum)
			my_thread(&data->arrphilo[data->i].pid, start_feeding,
				&data->arrphilo[data->i], CREATE);
		data->start = get_time();
		usleep(100);
		set_int(&data->data_mutex, &data->pready, 1);
		data->i = -1;
		while (++data->i < data->pnum)
			my_thread(&data->arrphilo[data->i].pid, NULL,
				NULL, JOIN);
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
	data_init(&data);
	feed_the_beasts(&data);
	return (0);
}
