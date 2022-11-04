/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renstein <renstein@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 14:48:47 by renstein          #+#    #+#             */
/*   Updated: 2022/11/04 13:48:51 by renstein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# define GET_FORK "has taken a fork"
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

}t_philo;

typedef struct s_data
{
	int philo_id;
	int number_philo;
	int time_to_die;
	int time_to_eat;
	int time_to_sleep;
	int number_times_eat;

	pthread_mutex_t* forks;

	int timestart_in_ms;
	pthread_mutex_t		mutex_count;
	pthread_mutex_t		mutex_print;

	t_philo	*philos;

}t_data;


void	ft_philo_create(void *data);

void	create_thread(t_data *data);


int		ft_strlen(char const *buf);
int		ft_atoi(char *str);
void	ft_putstr_fd(char const *s, int fd);
void	ft_putnbr_fd(int n, int fd);

void	print(int time,int namber, char *output, pthread_mutex_t* mutex);
int		ft_get_time(int start);

#endif