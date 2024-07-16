/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaldhahe <zaldhahe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 21:04:16 by zaldhahe          #+#    #+#             */
/*   Updated: 2024/07/16 16:01:44 by zaldhahe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//input:
	//number_of_philosophers,, time_to_die time_to_eat,,
	//time_to_sleep
	//number_of_times_each_philosopher_must_eat

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

char	*ft_strdup(const char *str)
{
	char	*dup;
	int		i;

	i = 0;
	dup = (char *) malloc(ft_strlen(str) + 1);
	if (!dup)
		return (NULL);
	while (str[i])
	{
		dup[i] = str[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	size_t	j;
	char	*r;

	i = 0;
	j = 0;
	r = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 3));
	if (!r)
		return (NULL);
	while (s1[i])
	{
		r[i] = s1[i];
		i++;
	}
	r[i++] = ' ';
	while (s2[j])
		r[i++] = s2[j++];
	r[i++] = ' ';
	r[i] = '\0';
	return (r);
}

char	*join_strings(char *av[])
{
	int		i;
	char	*r;
	char	*temp;

	i = 1;
	r = ft_strdup("");
	while (av[i])
	{
		temp = r;
		r = ft_strjoin(r, av[i++]);
		free(temp);
	}
	return (r);
}

void freexit(char *str)
{
	if (str)
		free(str);
	exit(1);
}

// int is_valid(char *av[], t_data *data)
// {
// 	if (av[data->i][0] == 0)
// 		data->flag = 0;
// 	while(av[data->i][data->j] == ' ')
// 		data->j++;
// 	if (av[data->i][data->j] >= '0' && av[data->i][data->j] <= '9')
// 		data->flag = 1;
// 	else if (av[data->i][data->j] == '+' && av[data->i][data->j + 1] >= '0' && av[data->i][data->j + 1] <= '9')
// 	{
// 		data->flag = 1;
// 		if (data->j != 0 && av[data->i][data->j - 1] != ' ')
// 			data->flag = 0;
// 		data->j++;
// 	}
// 	while(av[data->i][data->j + 1] == ' ')
// 		data->j++;
// 	printf("Returning: %d\n", data->flag);
// 	return (data->flag);
// }

int	is_valid(char *av[], t_data *data)
{
	if (av[data->i][0] == 0)
		data->flag = 0;
	while (av[data->i][data->j] == ' ')
		data->j++;
	if ((av[data->i][data->j] == '-' || av[data->i][data->j] == '+') &&
			(av[data->i][data->j + 1] >= '0' &&
			av[data->i][data->j + 1] <= '9'))
	{
		data->flag = 1;
		if (data->j != 0 && av[data->i][data->j - 1] != ' ')
			data->flag = 0;
		data->j++;
	}
	else if (av[data->i][data->j] < '0' || av[data->i][data->j] > '9')
		data->flag = 1;
	while (av[data->i][data->j + 1] == ' ')
		data->j++;
	printf("Returning: %d\n", data->flag);
	return (data->flag);
}

int checker(char *av[], t_data *data)
{
	data->i = 1;
	while(av[data->i])
	{
		data->j = 0;
		if (av[data->i][0] == 0)
			return (0);
		while(av[data->i][data->j])
		{
			data->flag = 1;
			if (!is_valid(av, data))
				return (0);
			data->j++;
		}
		data->i++;
	}
	return (1);
}

int	main(int ac, char *av[])
{
	(void)ac;
	t_data data;

	if (!checker(av, &data))
		exit(1);
	//data.avstr = join_strings(av);
	
	return(0);
}