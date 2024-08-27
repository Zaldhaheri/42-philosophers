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

void	start_feeding(t_data *data)
{
	
}

void	feed_the_beasts(t_data *data)
{
	printf("im here\n");
	if (data->plimit == 0)
		return ;
	else if (data->pnum == 1)
		return ;
	else
	{
		while (data->i < data->pnum)
			my_thread(&data->arrphilo[data->i].pid, start_feeding, &data->arrphilo[data->i], CREATE);
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
