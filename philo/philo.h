/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 21:04:19 by zaldhahe          #+#    #+#             */
/*   Updated: 2024/07/16 14:16:33 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <stdio.h>
#include <stdlib.h>

typedef struct s_data
{
	int i;
	int j;
	int flag;
	int	pnum; //num of philo
	int	pdie; //time to die
	int	peat; //time to eat
	int	psleep; //time to sleep
	int	plimit; //limit of eats until stop
	int count;
	char *avstr;
}	t_data;

#endif