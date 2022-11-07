/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renstein <renstein@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 14:39:14 by renstein          #+#    #+#             */
/*   Updated: 2022/11/07 19:02:52 by renstein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/philo.h"

void	*ft_life_philo(void	*datochka)
{
	t_data *data = (t_data *)datochka;

	pthread_mutex_lock(&data->mutex_count);
	int my_num = data->philo_id;
	data->philo_id++;
	pthread_mutex_unlock(&data->mutex_count);
	if (my_num % 2 == 0)
		usleep(1000);
	while (data->philos[my_num].count_eat < data->num_times_eat || !data->num_times_eat)
	{
		pthread_mutex_lock(data->philos[my_num].left_fork); //zahvat
		print(ft_get_time(data->timestart_in_ms), my_num, GET_FORK, &data->mutex_print);
		pthread_mutex_lock(data->philos[my_num].right_fork);
		print(ft_get_time(data->timestart_in_ms),  my_num,GET_FORK, &data->mutex_print);
		data->philos[my_num].time_start_eat = ft_get_time(data->timestart_in_ms);
		print(data->philos[my_num].time_start_eat, my_num, EAT, &data->mutex_print);
		data->philos[my_num].count_eat++;
		// check_count_eat(data);
		usleep(data->time_to_eat * 1000);
		pthread_mutex_unlock(data->philos[my_num].left_fork); //free
		print(ft_get_time(data->timestart_in_ms), my_num, GET_FORK, &data->mutex_print);
		pthread_mutex_unlock(data->philos[my_num].right_fork);
		print(ft_get_time(data->timestart_in_ms),  my_num, GET_FORK, &data->mutex_print);
		print(ft_get_time(data->timestart_in_ms),  my_num, SLEEP, &data->mutex_print);
		usleep(data->time_to_sleep * 1000);
		print(ft_get_time(data->timestart_in_ms),  my_num, THINK, &data->mutex_print);
	}
}

// void	check_count_eat(t_data	*data)
// {
// 	int i = 0;
// 	int count = 0;
// 	int my_num = 0;

// 	while(my_num < data->number_philo)
// 	{
// 		if (data->number_times_eat == data->philos[my_num].count_eat);
// 			count++;
// 		my_num++;
// 	}
// 	printf("COUNT count eat %d\n", count);
// 	if (data->number_times_eat <= count)
// 		ft_died(data);
// }

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
		pthread_detach(data->philos[i].thread_id);
		i++;
	}
}

//   ./philo 2 30 45 654 544

int		ft_died(t_data	*data)
{
	int my_num = 0;
	int	dif;
	int time;

	while (1)
	{
		time = ft_get_time(data->timestart_in_ms);
		dif = time - data->philos[my_num].time_start_eat;
		if (dif > data->time_to_die)
		{
			print(time,  my_num, DIED, &data->mutex_print);
			exit (0);
		}
		if (my_num == data->number_philo - 1)
		{
			my_num = 0;
			usleep (1000);
		}
		else
			my_num++;
	}
}


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

	ft_died(&data);
	usleep(1000000); // 10 sec

	return (0);
}
