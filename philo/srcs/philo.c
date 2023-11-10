/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdias-ba <rdias-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 01:22:46 by rdias-ba          #+#    #+#             */
/*   Updated: 2023/11/10 16:16:57 by rdias-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

void	philo_eats(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	pthread_mutex_lock(&(data->forks[philo->left_id]));
	print_message(data, philo->id, "has taken a fork");
	if (data->nb_philo == 1)
	{
		pthread_mutex_unlock(&(data->forks[philo->left_id]));
		smart_sleep(data->t_death + 10, data);
		return ;
	}
	pthread_mutex_lock(&(data->forks[philo->right_id]));
	print_message(data, philo->id, "has taken a fork");
	pthread_mutex_lock(&(data->eating));
	print_message(data, philo->id, "is eating");
	philo->t_last_meal = timestamp();
	pthread_mutex_unlock(&(data->eating));
	smart_sleep(data->t_eat, data);
	pthread_mutex_lock(&(data->has_eaten));
	(philo->has_eaten)++;
	pthread_mutex_unlock(&(data->has_eaten));
	pthread_mutex_unlock(&(data->forks[philo->left_id]));
	pthread_mutex_unlock(&(data->forks[philo->right_id]));
}

void	*philo_life(void *void_philo)
{
	t_philo			*philo;
	t_data			*data;

	philo = (t_philo *)void_philo;
	data = philo->data;
	if (philo->id % 2)
		smart_sleep(data->t_eat, data);
	while (1)
	{
		if (!(pthread_mutex_lock(&(data->dead))) && data->died)
		{
			pthread_mutex_unlock(&(data->dead));
			break ;
		}
		pthread_mutex_unlock(&(data->dead));
		philo_eats(philo);
		if (!(pthread_mutex_lock(&(data->ate))) && data->all_ate)
		{
			pthread_mutex_unlock(&(data->ate));
			break ;
		}
		pthread_mutex_unlock(&(data->ate));
		sleep_think(data, philo);
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
	pthread_mutex_destroy(&(data->dead));
	pthread_mutex_destroy(&(data->eating));
	pthread_mutex_destroy(&(data->ate));
	pthread_mutex_destroy(&(data->has_eaten));
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
			if ((timestamp() - philo[i].t_last_meal) >= data->t_death)
			{
				print_message(data, i, "died");
				is_dead(data);
			}
			pthread_mutex_unlock(&(data->eating));
		}
		if (data->died)
			break ;
		i = 0;
		pthread_mutex_lock(&(data->has_eaten));
		while (data->nb_eat != -1 && i < data->nb_philo \
				&& philo[i].has_eaten >= data->nb_eat)
			i++;
		pthread_mutex_unlock(&(data->has_eaten));
		all_ate(i, data);
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
		pthread_mutex_lock(&(data->eating));
		phi[i].t_last_meal = timestamp();
		pthread_mutex_unlock(&(data->eating));
		i++;
	}
	death_checker(data, data->philo);
	exit_thread(data, phi);
	return (0);
}
