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
		data->pnum = atoi(data->avsplit[0]);
		data->pdie = atoi(data->avsplit[1]);
		data->peat = atoi(data->avsplit[2]);
		data->psleep = atoi(data->avsplit[3]);
		if (data->count == 5)
			data->plimit = atoi(data->avsplit[4]);
	}
	else
		freexit(data->avstr, data->avsplit, data);
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
	printf("pdie: %d\n",data.pdie);
	printf("peat: %d\n",data.peat);
	printf("psleep: %d\n",data.psleep);
	if (data.plimit)
		printf("plimit: %d\n", data.plimit);
	return (0);
}
