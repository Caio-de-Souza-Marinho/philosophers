/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caide-so <caide-so@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 18:52:29 by caide-so          #+#    #+#             */
/*   Updated: 2025/04/09 20:25:18 by caide-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	main(int argc, char **argv)
{
	t_table		table;

	if (argc != 5 && argc != 6)
	{
		printf("ERROR: Wrong number of arguments\n");
		return (1);
	}
	parse_args(argc, argv, &table);
	if (validate_args(argc, &table))
		return (1);
	init_table(&table);
	spawn_philos(&table);
	routine(&table);
	return (0);
}

/*
void	print_table(t_table *table);
void	print_philos(t_table *table);
*/

/*
void	print_table(t_table *table)
{
	printf("number of philos - %d\n", table->nbr_philos);
	printf("time to die - %ld\n", table->time_to_die);
	printf("time to eat - %ld\n", table->time_to_eat);
	printf("time to sleep - %ld\n", table->time_to_sleep);
	printf("number of meals - %d\n", table->nbr_meals);
	printf("simulation ended - %d\n", table->simulation_ended);
	printf("finished meals - %d\n", table->finished_meals);
	printf("start time - %lu\n", table->start_time);
	print_philos(table);
}

void	print_philos(t_table *table)
{
	int	i;

	i = 0;
	printf("==========PHILOS=========\n");
	while (i < table->nbr_philos)
	{
		printf("philo %d ate %d meals\n", table->philos[i].id,
			table->philos[i].meals_eaten);
		i++;
	}
	printf("===========END===========\n");
}
*/
