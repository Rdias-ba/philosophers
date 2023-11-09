/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdias-ba <rdias-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 23:42:54 by rdias-ba          #+#    #+#             */
/*   Updated: 2023/11/09 05:30:45 by rdias-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

int	print_error(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	write(2, "Error: ", 7);
	write(2, str, i);
	write(2, "\n", 1);
	return (1);
}

int	error_handler(int error)
{
	if (error == 1)
		return (print_error("At least one wrong argument"));
	if (error == 2)
		return (print_error("Fatal error when intializing mutex"));
	return (1);
}
