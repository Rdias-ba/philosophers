/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdias-ba <rdias-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 23:25:29 by rdias-ba          #+#    #+#             */
/*   Updated: 2023/11/09 16:41:27 by rdias-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

int	main(int ac, char **av)
{
	t_data	data;

	if (ac != 5 && ac != 6)
		return (print_error("Wrong amount of arguments"));
	if (init(&data, av))
		return (error_handler(data.error_id));
	if (philo_thread(&data))
		return (print_error("There was an error creating the threads"));
	return (0);
}
