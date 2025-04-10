/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caide-so <caide-so@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 21:55:11 by caide-so          #+#    #+#             */
/*   Updated: 2025/04/02 22:36:13 by caide-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// Entry point for the philosopher simulation
// 1. Validates input arguments
// 2. Initializes resources and starts threads
// 3. Launches the monitor thread
// 4. Cleans up resources post-simulation
int	main(int argc, char **argv)
{
	t_table	table;	

	if (argc != 5 && argc != 6)
	{
		printf("ERROR: Wrong number of arguments\n");
		return (1);
	}
	parse_args(argc, argv, &table);
	if (validate_args(argc, &table))
		return (1);
	init_table(&table);
	create_threads(&table);
	monitor(&table);
	join_threads(&table);
	clean(&table);
	return (0);
}
