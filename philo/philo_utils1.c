/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philostuff.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaldhahe <zaldhahe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 12:13:00 by zaldhahe          #+#    #+#             */
/*   Updated: 2024/08/27 12:13:43 by zaldhahe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	mutex_error_handler(int status, int op)
{
	if (0 == status)
		return ;
	if (EINVAL == status && (LOCK == op || UNLOCK == op))
		freerror(NULL, NULL, NULL, "mutex value invalid\n");
	else if (EINVAL == status && INIT == op)
		freerror(NULL, NULL, NULL, "attr value invalid\n");
	else if (EDEADLK == status)
		freerror(NULL, NULL, NULL, "possible deadlock\n");
	else if (EPERM == status)
		freerror(NULL, NULL, NULL, "no mutex lock on current thread\n");
	else if (ENOMEM == status)
		freerror(NULL, NULL, NULL, "not enough memory for another mutex\n");
	else if (EBUSY == status)
		freerror(NULL, NULL, NULL, "locked mutex\n");
}

void	my_mutex(pthread_mutex_t *mutex, int op)
{
	if (LOCK == op)
		mutex_error_handler(pthread_mutex_lock(mutex), op);
	else if (UNLOCK == op)
		mutex_error_handler(pthread_mutex_unlock(mutex), op);
	else if (INIT == op)
		mutex_error_handler(pthread_mutex_init(mutex, NULL), op);
	else if (DESTROY == op)
		mutex_error_handler(pthread_mutex_destroy(mutex), op);
	else
		freerror(NULL, NULL, NULL, "Wrong op for my_mutex\n");
}

void	thread_error_handler(int status, int op)
{
	if (0 == status)
		return ;
	if (EAGAIN == status)
		freerror(NULL, NULL, NULL, "no resources for another thread\n");
	else if (EPERM == status)
		freerror(NULL, NULL, NULL,
			"caller doesnt have appropriate permission\n");
	else if (EINVAL == status && CREATE == op)
		freerror(NULL, NULL, NULL, "attr value invalid\n");
	else if (EINVAL == status && (JOIN == op || DETACH == op))
		freerror(NULL, NULL, NULL, "value by thread not joinable\n");
	else if (ESRCH == status)
		freerror(NULL, NULL, NULL, "no thread found\n");
	else if (EDEADLK == status)
		freerror(NULL, NULL, NULL, "deadlock thread detected\n");
}

void	my_thread(pthread_t *thread, void *(*func)(void *), void *data, int op)
{
	if (CREATE == op)
		thread_error_handler(pthread_create(thread, NULL, func, data), op);
	else if (JOIN == op)
		thread_error_handler(pthread_join(*thread, NULL), op);
	else if (DETACH == op)
		thread_error_handler(pthread_detach(*thread), op);
	else
		freerror(NULL, NULL, NULL, "wrong op for my_thread\n");
}

void	destroy_mutexes(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->pnum)
	{
		my_mutex(&data->arrfork[i].fork_mutex, DESTROY);
		my_mutex(&data->arrphilo[i].philo_mutex, DESTROY);
		i++;
	}
	my_mutex(&data->data_mutex, DESTROY);
	my_mutex(&data->write_mutex, DESTROY);
}
