/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdias-ba <rdias-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 01:22:46 by rdias-ba          #+#    #+#             */
/*   Updated: 2023/11/09 16:41:43 by rdias-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

void	philo_eats(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	pthread_mutex_lock(&(data->forks[philo->left_id]));
	print_message(data, philo->id, "has taken a fork");
	if (data->nb_philo > 1)
	{
		pthread_mutex_lock(&(data->forks[philo->right_id]));
		print_message(data, philo->id, "has taken a fork");
	}
	else
	{
		pthread_mutex_unlock(&(data->forks[philo->left_id]));
		smart_sleep(data->t_death * 2, data);
		return ;
	}
	print_message(data, philo->id, "is eating");
	pthread_mutex_lock(&(data->eating));
	philo->t_last_meal = timestamp();
	pthread_mutex_unlock(&(data->eating));
	smart_sleep(data->t_eat, data);
	(philo->has_eaten)++;
	pthread_mutex_unlock(&(data->forks[philo->left_id]));
	pthread_mutex_unlock(&(data->forks[philo->right_id]));
}

void	*philo_life(void *void_philo)
{
	int				i;
	t_philo			*philo;
	t_data			*data;

	i = 0;
	philo = (t_philo *)void_philo;
	data = philo->data;
	if (philo->id % 2)
		usleep(15000);
	while (!(data->died))
	{
		philo_eats(philo);
		if (data->all_ate)
			break ;
		print_message(data, philo->id, "is sleeping");
		smart_sleep(data->t_sleep, data);
		print_message(data, philo->id, "is thinking");
		i++;
	}
	return (NULL);
}

void	exit_thread(t_data *data, t_philo *philos)
{
	int	i;

	i = -1;
	while (++i < data->nb_philo)
		pthread_join(philos[i].thread_id, NULL);
	i = -1;
	while (++i < data->nb_philo)
		pthread_mutex_destroy(&(data->forks[i]));
	pthread_mutex_destroy(&(data->print));
}

void	death_checker(t_data *data, t_philo *philo)
{
	int	i;

	while (!(data->all_ate))
	{
		i = -1;
		while (++i < data->nb_philo && !(data->died))
		{
			pthread_mutex_lock(&(data->eating));
			if (time_diff(philo[i].t_last_meal, timestamp()) >= data->t_death)
			{
				print_message(data, i, "died");
				data->died = 1;
			}
			pthread_mutex_unlock(&(data->eating));
			usleep(100);
		}
		if (data->died)
			break ;
		i = 0;
		while (data->nb_eat != -1 && i < data->nb_philo \
				&& philo[i].has_eaten >= data->nb_eat)
			i++;
		if (i == data->nb_philo)
			data->all_ate = 1;
	}
}

int	philo_thread(t_data *data)
{
	int			i;
	t_philo		*phi;

	i = 0;
	phi = data->philo;
	data->start = timestamp();
	while (i < data->nb_philo)
	{
		if (pthread_create(&(phi[i].thread_id), NULL, philo_life, &(phi[i])))
			return (1);
		phi[i].t_last_meal = timestamp();
		i++;
	}
	death_checker(data, data->philo);
	exit_thread(data, phi);
	return (0);
}
