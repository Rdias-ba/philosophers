/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdias-ba <rdias-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 23:26:16 by rdias-ba          #+#    #+#             */
/*   Updated: 2023/11/10 00:56:42 by rdias-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <sys/time.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <pthread.h>

typedef struct s_philo
{
	int					id;
	int					has_eaten;
	int					left_id;
	int					right_id;
	long long			t_last_meal;
	struct s_data		*data;
	pthread_t			thread_id;
}						t_philo;

typedef struct s_data
{
	int					nb_philo;
	int					t_death;
	int					t_eat;
	int					t_sleep;
	int					nb_eat;
	int					died;
	int					all_ate;
	int					error_id;
	long long			start;
	pthread_mutex_t		dead;
	pthread_mutex_t		ate;
	pthread_mutex_t		has_eaten;
	pthread_mutex_t		eating;
	pthread_mutex_t		forks[250];
	pthread_mutex_t		print;
	t_philo				philo[250];
}						t_data;

int						print_error(char *str);
int						error_handler(int error_id);

int						init(t_data *data, char **av);
void					sleep_think(t_data *data, t_philo *philo);
void					all_ate(int i, t_data *data);
void					is_dead(t_data *data);

int						ft_atoi(const char *str);
void					print_message(t_data *data, int id, char *str);
long long				timestamp(void);
void					smart_sleep(long long time, t_data *data);

int						philo_thread(t_data *data);
void					exit_thread(t_data *data, t_philo *philo);

#endif