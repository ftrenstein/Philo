/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life_died.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renstein <renstein@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 15:37:56 by renstein          #+#    #+#             */
/*   Updated: 2022/11/08 20:34:11 by renstein         ###   ########.fr       */
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
	data->philos[my_num].count_eat = 0;
	if (my_num % 2 == 0)
		usleep(1000);
	while (data->philos[my_num].count_eat < data->num_times_eat || data->num_times_eat == 0)
	{
		pthread_mutex_lock(data->philos[my_num].left_fork); //zahvat
		print(ft_get_time(data->timestart_in_ms), my_num, GET_FORK_L, &data->mutex_print);
		pthread_mutex_lock(data->philos[my_num].right_fork);
		print(ft_get_time(data->timestart_in_ms),  my_num,GET_FORK_R, &data->mutex_print);
		data->philos[my_num].time_start_eat = ft_get_time(data->timestart_in_ms);
		print(data->philos[my_num].time_start_eat, my_num, EAT, &data->mutex_print);
		data->philos[my_num].count_eat++;
		// check_count_eat(data);
		usleep(data->time_to_eat * 1000);
		pthread_mutex_unlock(data->philos[my_num].left_fork); //free
		print(ft_get_time(data->timestart_in_ms), my_num, FREE_FORK_L, &data->mutex_print);
		pthread_mutex_unlock(data->philos[my_num].right_fork);
		print(ft_get_time(data->timestart_in_ms),  my_num, FREE_FORK_R, &data->mutex_print);
		print(ft_get_time(data->timestart_in_ms),  my_num, SLEEP, &data->mutex_print);
		// data->philos[my_num].time_start_eat = ft_get_time(data->timestart_in_ms);
		usleep(data->time_to_sleep * 1000);
		print(ft_get_time(data->timestart_in_ms),  my_num, THINK, &data->mutex_print);
	}
}

void	ft_clear(t_data *data)
{
	free (data->forks);
	free (data->philos);
}

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
			ft_clear(&data);
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