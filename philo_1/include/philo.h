/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renstein <renstein@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 14:48:47 by renstein          #+#    #+#             */
/*   Updated: 2022/11/08 19:39:26 by renstein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# define GET_FORK_L "has taken a left fork"
# define GET_FORK_R "has taken a right fork"

# define FREE_FORK_L "has free a left fork"
# define FREE_FORK_R "has free a right fork"

# define EAT "is eating"
# define SLEEP "is sleeping"
# define THINK "is thinking"
# define DIED "died"


# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# include <string.h>

typedef struct s_philo
{
	pthread_t	thread_id;
	int 	numero;
	pthread_mutex_t* left_fork;
	pthread_mutex_t* right_fork;
	pthread_mutex_t mutex_death;

	int		time_start_eat;
	int		count_eat; ///
	int		flag;

}t_philo;

typedef struct s_data
{
	int philo_id;
	int number_philo;
	int time_to_die;
	int time_to_eat;
	int time_to_sleep;
	int num_times_eat; ///

	pthread_mutex_t* forks;

	long timestart_in_ms;
	pthread_mutex_t		mutex_count;
	pthread_mutex_t		mutex_print;

	t_philo	*philos;

}t_data;


void	ft_init_philo(t_data	*data);
void	ft_init_fork(t_data	*data);
void	create_thread(t_data *data);

void	ft_valid(int argc, char **argv, t_data *data);

int		ft_strlen(char const *buf);
int		ft_atoi(char *str);
void	ft_putstr_fd(char const *s, int fd);
void	ft_putnbr_fd(int n, int fd);


void	print(int time,int namber, char *output, pthread_mutex_t* mutex);

long		ft_get_time(long start);

void	*ft_life_philo(void	*datochka);
int		ft_died(t_data	*data);
// void	check_count_eat(t_data	*data);

#endif