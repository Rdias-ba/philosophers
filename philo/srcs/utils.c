/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdias-ba <rdias-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 00:35:20 by rdias-ba          #+#    #+#             */
/*   Updated: 2023/11/10 16:14:21 by rdias-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

int	ft_atoi(const char *str)
{
	long int	n;
	int			sign;

	n = 0;
	sign = 1;
	while ((*str <= 13 && *str >= 9) || *str == 32)
		str++;
	if (*str == '-')
		return (-1);
	else if (*str == '+')
		str++;
	while (*str)
	{
		if (*str >= '0' && *str <= '9')
			n = n * 10 + (*str++ - '0');
		else
			return (-1);
	}
	return ((int)(n * sign));
}

long long	timestamp(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

void	smart_sleep(long long time, t_data *data)
{
	long long	i;

	i = timestamp();
	pthread_mutex_lock(&(data->eating));
	if (!(data->died))
	{
		pthread_mutex_unlock(&(data->eating));
		while ((timestamp() - i) < time)
			usleep(100);
	}
	else
		pthread_mutex_unlock(&(data->eating));
}

void	print_message(t_data *data, int id, char *str)
{
	pthread_mutex_lock(&(data->print));
	pthread_mutex_lock(&(data->dead));
	if (!(data->died))
		printf("%lli %i %s\n", timestamp() - data->start, id + 1, str);
	pthread_mutex_unlock(&(data->print));
	pthread_mutex_unlock(&(data->dead));
	return ;
}
