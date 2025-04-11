/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_check_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caide-so <caide-so@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 12:21:46 by caide-so          #+#    #+#             */
/*   Updated: 2025/03/31 12:35:36 by caide-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

// Parse command-line arguments into simulation parameters
void	parse_args(int argc, char **argv, t_table *table)
{
	table->nbr_philos = (int)ft_atol(argv[1]);
	table->time_to_die = ft_atol(argv[2]);
	table->time_to_eat = ft_atol(argv[3]);
	table->time_to_sleep = ft_atol(argv[4]);
	if (argc == 6)
		table->nbr_meals = (int)ft_atol(argv[5]);
	else
		table->nbr_meals = -1;
}

// Ensures all input values are positive numbers
int	validate_args(int argc, t_table *table)
{
	if (table->nbr_philos <= 0 || table->time_to_die <= 0
		|| table->time_to_eat <= 0 || table->time_to_sleep <= 0
		|| (argc == 6 && table->nbr_meals <= 0))
	{
		printf("ERROR: Invalid argument (non-positive value)\n");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
