/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renstein <renstein@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 14:39:14 by renstein          #+#    #+#             */
/*   Updated: 2022/11/04 13:51:36 by renstein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/philo.h"

void	*ft_life_philo(void	*datochka)
{
	t_data *data = (t_data *)datochka;

	pthread_mutex_lock(&data->mutex_count);
	int my_num = data->philo_id;
	data->philo_id++;
	char my_char_num = my_num + '0';
	pthread_mutex_unlock(&data->mutex_count);

	if (my_num % 2 == 0) //
		usleep(10000);

	while (1)
	{
		pthread_mutex_lock(data->philos[my_num].left_fork); //zahvat
		print(ft_get_time(data->timestart_in_ms), my_num, "philo get left fork", &data->mutex_print);
		pthread_mutex_lock(data->philos[my_num].right_fork);
		print(ft_get_time(data->timestart_in_ms),  my_num, "philo get right fork", &data->mutex_print);

		print(ft_get_time(data->timestart_in_ms),  my_num, EAT, &data->mutex_print);

		pthread_mutex_unlock(data->philos[my_num].left_fork); //free
		print(ft_get_time(data->timestart_in_ms), my_num, "philo free left fork", &data->mutex_print);

		pthread_mutex_unlock(data->philos[my_num].right_fork);
		print(ft_get_time(data->timestart_in_ms),  my_num, "philo free right fork", &data->mutex_print);

		print(ft_get_time(data->timestart_in_ms),  my_num, SLEEP, &data->mutex_print);
		usleep(data->time_to_sleep);
		print(ft_get_time(data->timestart_in_ms),  my_num, THINK, &data->mutex_print);
	}
	return NULL;
}


void	ft_init_philo(t_data	*data)
{
	int i = 0;

	data->forks = malloc(sizeof(pthread_mutex_t) * data->number_philo);

	while (data->number_philo > i)
	{
		pthread_mutex_init(&data->forks[i++], NULL);
	}
	data->philos = malloc (sizeof(t_philo) * data->number_philo);
	i = 0;
	while (data->number_philo > i)
	{
		data->philos[i].left_fork = &data->forks[i];
		if (i == data->number_philo - 1)
			data->philos[i].right_fork = data->forks;
		else
			data->philos[i].right_fork = &data->forks[i + 1];
		i++;
	}
}

void	create_thread(t_data *data)
{
	int	i = 0;
	data->philo_id = 0;
	while (i < data->number_philo)
	{
		write (1, "pthread\n", ft_strlen("pthread\n"));
		pthread_create(&data->philos[i].thread_id, NULL, ft_life_philo, data);
		i++;
	}
}

void	ft_exit()
{
	ft_putstr_fd("Error argv\n", 1);
	return (0);
}

void	ft_valid(int argc, char **argv, t_data *data)
{
	int i = 1;

	if (argc != 6 || argc != 5 || !argv)
		ft_exit();
	while (i < argc)
	{
		if (ft_atoi(argv[i]) <= 0)
			ft_exit();
		i++;
	}
	data->number_philo = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	if (data->time_to_die < 60)
		ft_exit();
	data->time_to_eat =  ft_atoi(argv[3]);
	if (data->time_to_eat < 60)
		ft_exit();
	data->time_to_sleep =  ft_atoi(argv[4]);
	if (data->time_to_sleep < 60)
		ft_exit();
	if (argc == 6)
		data->number_times_eat =  ft_atoi(argv[5]);
}

//   ./philo 2 30 45 654 544

int	main(int argc, char** argv)
{
	t_data	data;
	struct timeval	time;

	gettimeofday(&time, 0);

	ft_valid(argc, argv, &data);
	ft_init_philo(&data);

	pthread_mutex_init(&data.mutex_print, NULL);
	pthread_mutex_init(&data.mutex_count, NULL);
	data.timestart_in_ms = time.tv_sec * 1000 + time.tv_usec / 1000;

	create_thread(&data);
	usleep(100000); // 1 sec

	return (0);
}
