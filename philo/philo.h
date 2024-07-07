/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaldhahe <zaldhahe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 21:04:19 by zaldhahe          #+#    #+#             */
/*   Updated: 2024/07/07 21:47:40 by zaldhahe         ###   ########.fr       */
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

//checker
int	is_valid(char *av[], t_data *data);
int	checker(char *av[], t_data *data);

//utils
size_t	ft_strlen(const char *str);
char	*ft_strdup(const char *str);
char	*ft_strjoin(char const *s1, char const *s2);
int	count_word(char const *s, char c);
char	*join_strings(char *av[]);

#endif