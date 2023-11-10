/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdias-ba <rdias-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 00:49:12 by rdias-ba          #+#    #+#             */
/*   Updated: 2023/11/10 00:57:09 by rdias-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

void	sleep_think(t_data *data, t_philo *philo)
{
	print_message(data, philo->id, "is sleeping");
	smart_sleep(data->t_sleep, data);
	print_message(data, philo->id, "is thinking");
}

void	is_dead(t_data *data)
{
	pthread_mutex_lock(&(data->dead));
	data->died = 1;
	pthread_mutex_unlock(&(data->dead));
}

void	all_ate(int i, t_data *data)
{
	if (i == data->nb_philo)
	{
		pthread_mutex_lock(&(data->ate));
		data->all_ate = 1;
		pthread_mutex_unlock(&(data->ate));
	}
}
