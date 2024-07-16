/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 21:04:16 by zaldhahe          #+#    #+#             */
/*   Updated: 2024/07/16 14:46:03 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//input:
	//number_of_philosophers,, time_to_die time_to_eat,,
	//time_to_sleep
	//number_of_times_each_philosopher_must_eat

int get_doublesize(char *av[])
{
	int size = 0;
	int i;
	int j;

	j = 1;
	while (av[j])
	{
		i = 0;
		while(av[j][i])
		{
			size++;
			i++;
		}
		j++;
	}
	return size;
}

char *joinstrings(char *av[])
{
	int i;
	int j;
	int k;
	char *str;

	str = malloc(sizeof(char *) + 1);
	j = 1;
	k = 0;
	while(av[j])
	{
		i = 0;
		while(av[j][i])
		{
			str[k] = av[j][i];
			i++;
			k++;
		}
		j++;
	}
	str[k] = '\0';
	return (str);
}

int	main(int ac, char *av[])
{
	(void)ac;
	//t_data data;

	printf("%s\n", joinstrings(av));

	// data.avstr = joinstrings(av);
	return(0);
}