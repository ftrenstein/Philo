/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renstein <renstein@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 20:39:07 by renstein          #+#    #+#             */
/*   Updated: 2022/11/04 12:20:45 by renstein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/philo.h"

int	ft_strlen(char const *buf)
{
	int i = 0;

	while (buf[i])
		i++;
	return (i);
}

static int	ft_is_num(char c)
{
	return ((c >= '0') && (c <= '9'));
}

int	ft_atoi(char *str)
{
	int			sign;
	long long	r;

	sign = 1;
	r = 0;
	while (((*str >= 9) && (*str <= 13)) || (*str == 32))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -sign;
		str++;
	}
	while (ft_is_num(*str) && (r >= -2147483648) && (r < 2147483648))
	{
		r = r * 10 + (*str - '0');
		str++;
	}
	r = r * sign;
	if (r < -2147483648)
		r = 0;
	if (r > 2147483647)
		r = -1;
	return ((int)r);
}

void	ft_putnbr_fd(int n, int fd)
{
	char val;

	if (n == -2147483648)
		return (ft_putstr_fd("-2147483648", fd));
	if (n < 0)
	{
		write (fd, "-", 1);
		n = -n;
	}
	if (n < 10)
	{
		val = n + '0';
		write (fd, &val, 1);
		return ;
	}
	ft_putnbr_fd(n / 10, fd);
	ft_putnbr_fd(n % 10, fd);
}

void	ft_putstr_fd(char const *s, int fd)
{
	if (s != NULL)
		write(fd, s, ft_strlen(s));
}

	// int main()
	// {
	// 	char *str = "-";
	// 	printf("%d\n", ft_atoi(str));
	// }

int	ft_get_time(int start)
{
	struct timeval	time;

	gettimeofday(&time, 0);
	return ((time.tv_sec * 1000 + time.tv_usec / 1000) - start);
}

void	print(int time,int namber, char *output, pthread_mutex_t* mutex)
{
	pthread_mutex_lock(mutex);
	ft_putnbr_fd (time, 1);
	ft_putstr_fd (" ", 1);
	ft_putnbr_fd (namber, 1);
	ft_putstr_fd (" ", 1);
	ft_putstr_fd (output, 1);
	ft_putstr_fd ("\n", 1);
	pthread_mutex_unlock(mutex);
}