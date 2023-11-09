/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdias-ba <rdias-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 23:58:26 by rdias-ba          #+#    #+#             */
/*   Updated: 2023/11/09 17:41:22 by rdias-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

int	init_mutex(t_data *data)
{
	int	i;

	i = data->nb_philo;
	while (--i >= 0)
	{
		if (pthread_mutex_init(&(data->forks[i]), NULL))
			return (1);
	}
	if (pthread_mutex_init(&(data->print), NULL))
		return (1);
	if (pthread_mutex_init(&(data->eating), NULL))
		return (1);
	return (0);
}

int	init_philo(t_data *data)
{
	int	i;

	i = data->nb_philo;
	while (--i >= 0)
	{
		data->philo[i].id = i;
		data->philo[i].has_eaten = 0;
		data->philo[i].left_id = i;
		if (data->nb_philo > 1)
			data->philo[i].right_id = (i + 1) % data->nb_philo;
		else
			data->philo[i].right_id = i;
		data->philo[i].t_last_meal = 0;
		data->philo[i].data = data;
	}
	return (0);
}

int	init(t_data *data, char **av)
{
	data->nb_philo = ft_atoi(av[1]);
	data->t_death = ft_atoi(av[2]);
	data->t_eat = ft_atoi(av[3]);
	data->t_sleep = ft_atoi(av[4]);
	data->all_ate = 0;
	data->died = 0;
	data->error_id = 0;
	if (data->nb_philo < 1 || data->t_death < 0 || data->t_eat < 0
		|| data->t_sleep < 0 || data->nb_philo > 250)
		return (data->error_id = 1);
	if (av[5])
	{
		data->nb_eat = ft_atoi(av[5]);
		if (data->nb_eat <= 0)
			return (data->error_id = 1);
	}
	else
		data->nb_eat = -1;
	if (init_mutex(data))
		return (data->error_id = 2);
	init_philo(data);
	return (data->error_id);
}
