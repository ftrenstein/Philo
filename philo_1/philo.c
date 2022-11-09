/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renstein <renstein@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 14:39:14 by renstein          #+#    #+#             */
/*   Updated: 2022/11/09 20:22:08 by renstein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/philo.h"

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
	struct timeval	time;

	gettimeofday(&time, 0);
	pthread_mutex_init(&data->mutex_print, NULL);
	pthread_mutex_init(&data->mutex_count, NULL);

	data->philos = malloc (sizeof(t_philo) * data->number_philo);
	data->timestart_in_ms = time.tv_sec * 1000 + time.tv_usec / 1000;

}

void	ft_init_fork(t_data	*data)
{
	data->forks = malloc(sizeof(pthread_mutex_t) * data->number_philo);
	int i = 0;
	while (data->number_philo > i)
	{
		pthread_mutex_init(&data->forks[i++], NULL);
	}
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
		pthread_create(&data->philos[i].thread_id, NULL, ft_life_philo, data);
		pthread_detach(data->philos[i].thread_id);
		i++;
	}
	if (data->number_eats == data-> number_philo)
		print(ft_get_time(data->timestart_in_ms), i, ALL_FULL, &data->mutex_print);
}

int	main(int argc, char** argv)
{
	t_data	data;

	ft_valid(argc, argv, &data);

	ft_init_philo(&data);
	ft_init_fork(&data);

	create_thread(&data);

	ft_died(&data);
	usleep(1000000); // 10 sec

	return (0);
}
