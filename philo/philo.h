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

# include <stdio.h>
# include <stdlib.h>
# include <limits.h>
# include <pthread.h>
# include <errno.h>
# include <unistd.h>
# include <sys/time.h>

# define RESET   "\033[0m"
# define BLACK   "\033[30m"
# define RED     "\033[31m"
# define GREEN   "\033[32m"
# define YELLOW  "\033[33m"
# define BLUE    "\033[34m"
# define MAGENTA "\033[35m"
# define CYAN    "\033[36m"
# define WHITE   "\033[37m"

# define UNLOCK 0
# define LOCK 1
# define INIT 2
# define DESTROY 3
# define CREATE 4
# define JOIN 5
# define DETACH 6
# define EATING 7
# define SLEEPING 8
# define THINKING 9
# define FIRST_FORK 10
# define SECOND_FORK 11
# define DIED 12

typedef struct s_data	t_data;
typedef struct s_philo	t_philo;
typedef struct s_fork	t_fork;

struct s_data
{
	int				i;
	int				j;
	int				flag;
	int				count;
	char			*avstr; //input
	char			**avsplit; //split
	int				pnum; //num of philo
	long			pdie; //time to die
	long			peat; //time to eat
	long			psleep; //time to sleep
	long			plimit; //limit of eats until stop
	int				pready;	//for synchronization
	long			start;
	int				end;
	long			running_threads;
	pthread_t		monitor;
	pthread_mutex_t	data_mutex;
	pthread_mutex_t	write_mutex;
	t_fork			*arrfork; //arr struct of forks
	t_philo			*arrphilo; //arr struct of philos
};

struct s_philo
{
	pthread_t		pid; //process id
	int				id; //location on table
	int				full; //flag
	long			meals; //amount ate
	long			meal_time; //time eating
	t_fork			*fork_1; //first choice fork
	t_fork			*fork_2; //second choice fork
	pthread_mutex_t	philo_mutex;
	t_data			*data; //access to main data
};

struct s_fork
{
	int				forkid; //fork location on arr
	int				last_used; //for priority
	pthread_mutex_t	fork_mutex;
};

//philo_init
void	data_init(t_data *data);
void	philo_init(t_data *data);
void	philo_setfork(t_philo *philo, t_fork *arrfork, int x);
void	set_data(t_data *data);

//parsing
void	freeing(char *str, char **string, t_data *data);
void	freexit(char *str, char **string, t_data *data);
void	freerror(char *str, char **string, t_data *data, char *msg);
int		is_valid(char *av[], t_data *data);
int		checker(char *av[], t_data *data);

//philo sim
void	*one_philo(void *temp);
void	feed_the_beasts(t_data *data);
void	*start_feeding(void *temp);
void	spaghetti(t_philo *philo);
void	thinking(t_philo *philo);
int		dead(t_philo *philo);

//monitor
int		monitor_synch(pthread_mutex_t *mutex, long *thread, long pnum);
void	*monitor_beasts(void *temp);
void	philo_synch(t_data *data);
void	philo_desync(t_philo *philo);
void	sync_think(t_philo *philo);

//philo_utils
void	my_mutex(pthread_mutex_t *mutex, int op);
void	mutex_error_handler(int status, int op);
void	my_thread(pthread_t *thread, void *(*func)(void *), void *data, int op);
void	thread_error_handler(int status, int op);
void	my_usleep(long usec, t_data *data);
void	my_write(int status, t_philo *philo);

//setters getters
long	get_time(int i);
int		get_int(pthread_mutex_t *mutex, int *value);
void	set_int(pthread_mutex_t *mutex, int *set, int value);
long	get_long(pthread_mutex_t *mutex, long *value);
void	set_long(pthread_mutex_t *mutex, long *set, long value);
void	inc_long(pthread_mutex_t *mutex, long *value);

//utils
size_t	ft_strlen(const char *str);
int		ft_atoi(const char *str, t_data *data);
char	*ft_strdup(const char *str);
char	*ft_strjoin(char const *s1, char const *s2);
char	*join_strings(char *av[]);
char	**ft_split(char const *s, char c, t_data *data);
void	*ft_calloc(size_t count, size_t size);

#endif