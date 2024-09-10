/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaldhahe <zaldhahe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 17:21:08 by zaldhahe          #+#    #+#             */
/*   Updated: 2024/09/08 17:21:08 by zaldhahe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int my_wait(struct timeval start, int et)
{
    struct timeval cur_time;
    long res;

	res = 0;
	gettimeofday(&cur_time, NULL);
	if (!et)
		et = 50;
	res = (cur_time.tv_sec * 1000 + cur_time.tv_usec / 1000) - (start.tv_sec
			* 1000 + start.tv_usec / 1000);
	if (res < 0)
		res += 1000;
	if (res >= et)
		return (1);
	return (0);
}

int eat(t_philo *philo)
{
    if (my_write(EATING, philo))
        return (1);
    gettimeofday(&philo->last_eat, NULL);
    while (1)
    {
        if (is_dead(philo))
            return (1);
        usleep(200);
        if (my_wait(philo->last_eat, philo->data->peat))
            break ;
    }
    if (philo->data->plimit != -1)
    {
        philo->meal_count++;
        if (philo->meal_count == philo->data->plimit)
            return (1);
    }
    return (0);
}

int unlock_fork(t_philo *philo, int flag)
{
    if (flag)
        my_mutex(&philo->fork_1->fork_mutex, UNLOCK);
    else
        my_mutex(&philo->fork_2->fork_mutex, UNLOCK);
    return (1);
}

void unlock_forks(t_philo *philo)
{
    my_mutex(&philo->fork_1->fork_mutex, UNLOCK);
    my_mutex(&philo->fork_2->fork_mutex, UNLOCK);
}

int odd(t_philo *philo)
{
    while (1)
    {
        my_mutex(&philo->fork_1->fork_mutex, LOCK);
        if (is_dead(philo))
            return (unlock_fork(philo, 1));
        my_mutex(&philo->fork_2->fork_mutex, LOCK);
        if (philo->id != philo->fork_1->last_used
            && philo->id != philo->fork_2->last_used)
            break ;
        unlock_forks(philo);
        usleep(200);
    }
    unlock_forks(philo);
    if (my_write(FORK, philo) || my_write(FORK, philo))
        return (1);
    if (eat(philo) && philo->meal_count != philo->data->plimit)
        return (1);
    my_mutex(&philo->fork_1->fork_mutex, LOCK);
    philo->fork_1->last_used = philo->id;
    my_mutex(&philo->fork_2->fork_mutex, LOCK);
    philo->fork_2->last_used = philo->id;
    unlock_forks(philo);
    if (philo->meal_count == philo->data->plimit)
        return (1);
    return (0);
}

int even(t_philo *philo)
{
    while (1)
    {
        my_mutex(&philo->fork_2->fork_mutex, LOCK);
        if (is_dead(philo))
            return (unlock_fork(philo, 0));
        my_mutex(&philo->fork_1->fork_mutex, LOCK);
        if (philo->id != philo->fork_1->last_used
            && philo->id != philo->fork_2->last_used)
            break ;
        unlock_forks(philo);
        usleep(200);
    }
    unlock_forks(philo);
    if (my_write(FORK, philo) || my_write(FORK, philo))
        return (1);
    if (eat(philo) && philo->meal_count != philo->data->plimit)
        return (1);
    my_mutex(&philo->fork_2->fork_mutex, LOCK);
    philo->fork_2->last_used = philo->id;
    my_mutex(&philo->fork_1->fork_mutex, LOCK);
    philo->fork_1->last_used = philo->id;
    unlock_forks(philo);
    if (philo->meal_count == philo->data->plimit)
        return (1);
    return (0);
}

int my_write(char *status,t_philo *philo)
{
    long    time;

    gettimeofday(&philo->curr_time, NULL);
    time = philo->curr_time.tv_sec * 1e3 + philo->curr_time.tv_usec / 1e3;
    my_mutex(&philo->data->write_mutex, LOCK);
    if (!philo->data->end)
    {
        printf(status, time - philo->data->start, philo->id);
        my_mutex(&philo->data->write_mutex, UNLOCK);
        return (0);
    }
    my_mutex(&philo->data->write_mutex, UNLOCK);
    return (1);
}

int	is_dead(t_philo *philo)
{
	long	cur;
	int		ret;

	ret = 0;
	gettimeofday(&philo->curr_time, NULL);
	philo->death = (philo->curr_time.tv_sec * 1000 + philo->curr_time.tv_usec / 1000) - (philo->last_eat.tv_sec * 1000 + philo->last_eat.tv_usec / 1000);
	cur = (philo->curr_time.tv_sec * 1000 + philo->curr_time.tv_usec / 1000) - philo->data->start;
    my_mutex(&philo->data->write_mutex, LOCK);
	if (philo->data->end)
		ret = 1;
	else if (philo->death >= philo->data->pdie)
	{
		printf(DIED, (int)(cur), philo->id);
		philo->data->end = 1;
		ret = 1;
	}
	my_mutex(&philo->data->write_mutex, UNLOCK);
	return (ret);
}

void    one_philo(t_philo *philo)
{
    gettimeofday(&philo->last_eat, NULL);
    if (is_dead(philo))
        return ;
    if (my_write(THINKING, philo))
        return ;
    my_mutex(&philo->fork_1->fork_mutex, LOCK);
    if (my_write(FORK, philo))
    {
        my_mutex(&philo->fork_1->fork_mutex, UNLOCK);
        return ;
    }
    while (1)
    {
        if (is_dead(philo))
        {
            my_mutex(&philo->fork_1->fork_mutex, UNLOCK);
            return ;
        }
    }
}

int sleepy(t_philo *philo)
{
    struct timeval start;

    if (my_write(SLEEPING, philo))
        return (1);
    gettimeofday(&start, NULL);
    while (1)
    {
        if (is_dead(philo))
            return (1);
        usleep(200);
        if (my_wait(start, philo->data->psleep))
            break ;
    }
    return (0);
}

void start_feeding(void *temp)
{
    t_philo *philo;

    philo = (t_philo *)temp;
    if (philo->data->pnum == 1)
    {
        one_philo(philo);
        return ;
    }
    gettimeofday(&philo->last_eat, NULL);
    while(1)
    {
        if (philo->data->plimit == 0)
            return ;
        if (my_write(THINKING, philo))
            return ;
        if (philo->id % 2)
        {
            if (odd(philo))
                break ;
        }
        else if (even(philo))
            break ;
        if (sleepy(philo))
            break ;
    }
}

int main(int ac, char **av)
{
    t_data	data;

	(void)ac;
	if (!checker(av, &data))
		exit(1);
	data.avstr = join_strings(av);
	data.avsplit = ft_split(data.avstr, ' ', &data);
    set_data(&data);
}