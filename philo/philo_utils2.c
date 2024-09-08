/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaldhahe <zaldhahe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 22:44:54 by zaldhahe          #+#    #+#             */
/*   Updated: 2024/09/08 19:41:46 by zaldhahe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	get_int(pthread_mutex_t *mutex, int *value)
{
	int	get;

	my_mutex(mutex, LOCK);
	get = *value;
	my_mutex(mutex, UNLOCK);
	return (get);
}

void	set_int(pthread_mutex_t *mutex, int *set, int value)
{
	my_mutex(mutex, LOCK);
	*set = value;
	my_mutex(mutex, UNLOCK);
}

void	set_long(pthread_mutex_t *mutex, long *set, long value)
{
	my_mutex(mutex, LOCK);
	*set = value;
	my_mutex(mutex, UNLOCK);
}

long	get_long(pthread_mutex_t *mutex, long *value)
{
	long	r;

	my_mutex(mutex, LOCK);
	r = *value;
	my_mutex(mutex, UNLOCK);
	return (r);
}

void	inc_long(pthread_mutex_t *mutex, long *value)
{
	my_mutex(mutex, LOCK);
	(*value)++;
	my_mutex(mutex, UNLOCK);
}
