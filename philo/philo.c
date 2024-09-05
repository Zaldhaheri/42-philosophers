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

void	my_write(int status, t_philo *philo)
{
	long time;

	if (philo->full)
		return ;
	my_mutex(&philo->data->write_mutex, LOCK);
	time = get_time(2) - philo->data->start;
	// if (!get_int(&philo->data->data_mutex, &philo->data->end))
	// {
	// 	if (FIRST_FORK == status)
	// 		printf(BLUE "%-6ld ms"RESET": "WHITE" %d has taken fork %d\n" RESET, time, philo->id, philo->fork_1->forkid);
	// 	else if (SECOND_FORK == status)
	// 		printf(BLUE "%-6ld ms"RESET": "WHITE" %d has taken fork %d\n" RESET, time, philo->id, philo->fork_2->forkid);
	// 	else if (EATING == status)
	// 		printf(BLUE "%-6ld ms"RESET": "GREEN" %d is eating\n" RESET, time, philo->id);
	// 	else if (SLEEPING == status)
	// 		printf(BLUE "%-6ld ms"RESET": "CYAN" %d is sleeping\n" RESET, time, philo->id);
	// 	else if (THINKING == status)
	// 		printf(BLUE "%-6ld ms"RESET": "YELLOW" %d is thinking\n"RESET, time, philo->id);
	// 	else if (DIED == status)
	// 		printf(BLUE "%-6ld ms"RESET": "RED" %d died\n"RESET, time, philo->id);
	// }
	if (!get_int(&philo->data->data_mutex, &philo->data->end))
	{
		if (FIRST_FORK == status)
			printf(BLUE "%ld"RESET" "WHITE"%d has taken a fork\n" RESET, time, philo->id);
		else if (SECOND_FORK == status)
			printf(BLUE "%ld"RESET" "WHITE"%d has taken a fork\n" RESET, time, philo->id);
		else if (EATING == status)
			printf(BLUE "%ld"RESET" "GREEN"%d is eating\n" RESET, time, philo->id);
		else if (SLEEPING == status)
			printf(BLUE "%ld"RESET" "CYAN"%d is sleeping\n" RESET, time, philo->id);
		else if (THINKING == status)
			printf(BLUE "%ld"RESET" "YELLOW"%d is thinking\n"RESET, time, philo->id);
		else if (DIED == status)
			printf(BLUE "%ld"RESET" "RED"%d died\n"RESET, time, philo->id);
	}
	my_mutex(&philo->data->write_mutex, UNLOCK);
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
	return (999);
}

void my_usleep(long usec, t_data *data)
{
	long start;
	long curr;
	long rem;

	start = get_time(3);
	while(get_time(3) - start < usec)
	{
		if (get_int(&data->data_mutex, &data->end))
           break;
		curr = get_time(3) - start;
		rem = usec - curr;
		if (rem > 1000)
			usleep(rem / 2);
		else
		{
			while (get_time(3) - start < usec)
				;
		}
	}
}

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

void set_long(pthread_mutex_t *mutex, long *set, long value)
{
	my_mutex(mutex, LOCK);
	*set = value;
	my_mutex(mutex, UNLOCK);
}

long	get_long(pthread_mutex_t *mutex, long *value)
{
	int r;
	my_mutex(mutex, LOCK);
	r = *value;
	my_mutex(mutex, UNLOCK);
	return (r);
}

void inc_long(pthread_mutex_t *mutex, long *value)
{
	my_mutex(mutex, LOCK);
	(*value)++;
	my_mutex(mutex, UNLOCK);
}

void	philo_synch(t_data *data)
{
	while(!get_int(&data->data_mutex, &data->pready))
		;
}

int	monitor_synch(pthread_mutex_t *mutex, long *thread, long pnum)
{
	int r;

	r = 0;
	my_mutex(mutex, LOCK);
	if (*thread == pnum)
		r = 1;
	my_mutex(mutex, UNLOCK);
	return (r);
}

void thinking(t_philo *philo)
{
	my_write(THINKING, philo);
}

int	dead(t_philo *philo)
{
	long curr;
	long t_die;

	if (get_int(&philo->philo_mutex, &philo->full))
		return (0);
	curr = get_time(2) - philo->meal_time;
	t_die = philo->data->pdie / 1000;
	if (curr > t_die)
		return (1);
	return (0);
}

void	*monitor_beasts(void *temp)
{
	t_data *data;

	data = (t_data *)temp;
	while (!monitor_synch(&data->data_mutex, &data->running_threads, data->pnum))
		;
	while (!get_int(&data->data_mutex, &data->end))
	{
		data->j = -1;
		while (++data->j < data->pnum && !get_int(&data->data_mutex, &data->end))
		{
			if (dead(data->arrphilo + data->j))
			{
				my_write(DIED, data->arrphilo + data->j);
				set_int(&data->data_mutex, &data->end, 1);
			}
		}
	}
	return (NULL);
}

//grab forks
//eat print
//release fork
void spaghetti(t_philo *philo)
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

//wait for other philos to synchronize, then start
void	*start_feeding(void *temp)
{
	t_philo *philo;

	philo = (t_philo *)temp;
	philo_synch(philo->data);
	set_long(&philo->philo_mutex, &philo->meal_time, get_time(2));
	inc_long(&philo->data->data_mutex, &philo->data->running_threads);
	while(!get_int(&philo->data->data_mutex, &philo->data->end))
	{
		if (philo->full)
			break;
		spaghetti(philo);
		my_write(SLEEPING, philo);
		my_usleep(philo->data->psleep, philo->data);
		thinking(philo);
	}
	return (NULL);
}

void *one_philo(void *temp)
{
	t_philo *philo;

	philo = (t_philo *)temp;
	philo_synch(philo->data);
	set_long(&philo->philo_mutex, &philo->meal_time, get_time(2));
	inc_long(&philo->data->data_mutex, &philo->data->running_threads);
	my_write(FIRST_FORK, philo);
	while (!get_int(&philo->data->data_mutex, &philo->data->end))
		usleep(200);
	return (NULL);
}

void	feed_the_beasts(t_data *data)
{
	data->i = -1;
	if (data->plimit == 0)
		return ;
	else if (data->pnum == 1)
		my_thread(&data->arrphilo[0].pid, one_philo, &data->arrphilo[0], CREATE);
	else
	{
		while (++data->i < data->pnum)
			my_thread(&data->arrphilo[data->i].pid, start_feeding,
				&data->arrphilo[data->i], CREATE);
		//monitor

		my_thread(&data->monitor, monitor_beasts, data, CREATE);
		data->start = get_time(2);
		set_int(&data->data_mutex, &data->pready, 1); //start the threads
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
	freeing(data.avstr, data.avsplit, &data);
	data_init(&data);
	feed_the_beasts(&data);
	return (0);
}
