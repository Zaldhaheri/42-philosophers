/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaldhahe <zaldhahe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 21:04:16 by zaldhahe          #+#    #+#             */
/*   Updated: 2024/07/07 21:45:32 by zaldhahe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//input:
	//number_of_philosophers,, time_to_die time_to_eat,,
	//time_to_sleep
	//number_of_times_each_philosopher_must_eat

void set_values(char *av[], t_data *data)
{
	data->pnum = atoi(av[1]);
	data->pdie = atoi(av[2]);
	data->peat = atoi(av[3]);
	data->psleep = atoi(av[4]);
	if (av[5])
		data->plimit = atoi(av[5]);
}

int	main(int ac, char *av[])
{
	t_data data;
	//parsing needed
	data.avstr = join_strings(av);
	data.count = count_word(data.avstr, ' ');
	set_values(av, &data);
	printf("%d %d %d %d ", data.pnum, data.pdie, data.peat, data.psleep);
	if (ac == 6)
		printf("%d", data.plimit);
	printf("\n");
	return(0);
}