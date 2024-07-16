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
		printf("ball\n");
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
	printf("%s\n%d\n", data.avstr, data.count);
	set_data(&data);
	return (0);
}
