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
#include <unistd.h>
#include <sys/time.h>

typedef struct s_data t_data;
typedef struct s_philo t_philo;
typedef struct s_fork t_fork;

struct s_data
{
	int i;
	int j;
	int flag;
	int count;
	char *avstr;
	char **avsplit;
	int		pnum; //num of philo
	long	pdie; //time to die
	long	peat; //time to eat
	long	psleep; //time to sleep
	long	plimit; //limit of eats until stop
	t_fork *arrfork;
	t_philo *arrphilo;
};

struct s_philo
{
	pthread_t pid;
	int id;
	long meals;
	int full;
	long meal_time;
	t_fork *lfork;
	t_fork *rfork;
	t_data *data;
};

struct s_fork
{
	int forkid;
	pthread_mutex_t fork;
};

size_t	ft_strlen(const char *str);
int	ft_atoi(const char *str, t_data *data);
char	*ft_strdup(const char *str);
char	*ft_strjoin(char const *s1, char const *s2);
char	*join_strings(char *av[]);
char	**ft_split(char const *s, char c, t_data *data);
void	*ft_calloc(size_t count, size_t size);

void	freeing(char *str, char **string, t_data *data);
void	freexit(char *str, char **string, t_data *data);
void	freerror(char *str, char **string, t_data *data, char *msg);
int is_valid(char *av[], t_data *data);
int checker(char *av[], t_data *data);

#endif