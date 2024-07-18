/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 21:04:19 by zaldhahe          #+#    #+#             */
/*   Updated: 2024/07/16 23:26:25 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <pthread.h>


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
	char **avsplit;
}	t_data;

typedef struct s_philo
{
	pthread_t pid;
	int lfork;
	int rfork;
}

size_t	ft_strlen(const char *str);
int	ft_atoi(const char *str, t_data *data);
char	*ft_strdup(const char *str);
char	*ft_strjoin(char const *s1, char const *s2);
char	*join_strings(char *av[]);
char	**ft_split(char const *s, char c, t_data *data);

void	freeing(char *str, char **string, t_data *data);
void	freexit(char *str, char **string, t_data *data);
int is_valid(char *av[], t_data *data);
int checker(char *av[], t_data *data);

#endif