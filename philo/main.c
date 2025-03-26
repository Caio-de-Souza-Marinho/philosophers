/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caide-so <caide-so@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 21:55:11 by caide-so          #+#    #+#             */
/*   Updated: 2025/03/25 22:49:50 by caide-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
void	print_table(t_table *table);
void	print_forks(t_table *table);
void	print_philos(t_table *table);
*/

int	main(int argc, char **argv)
{
	t_table	table;	

	if (argc != 5 && argc != 6)
	{
		printf("ERROR: Wrong number of arguments\n");
		return (EXIT_FAILURE);
	}
	parse_args(argc, argv, &table);
	validate_args(argc, &table);
	init_table(&table);
	create_threads(&table);
	//monitor(&table);
	//	- create monitor thread
	//	- infinite loop that contains a function
	//	check philos
	//		- checks if a philo is dead of if
	//		all meals were eaten
	join_threads(&table);
	return (0);
}

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
	print_forks(table);
	print_philos(table);
}

void	print_forks(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->nbr_philos)
	{
		printf("fork id - %d\n", table->forks[i].fork_id);
		i++;
	}
}

void	print_philos(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->nbr_philos)
	{
		printf("==========PHILO %d==========\n", table->philos[i].id);
		printf("philo id - %d\n", table->philos[i].id);
		printf("meal counter - %d\n", table->philos[i].meal_counter);
		printf("right fork id - %d\n", table->philos[i].right_fork->fork_id);
		printf("left fork id - %d\n", table->philos[i].left_fork->fork_id);
		printf("last meal time - %lu\n", table->philos[i].last_meal_time);
		i++;
	}
}
*/

// validate inputs
// init simulation (parse data from arguments to the t_table struct)
// init each philo
// start philo routine
// 	assign each philo two forks
// 	philo X is eating
// 	philo X is sleeping
// 	philo X is thinking
// 	philo X died

/*
 * arguments
binary
number_of_philosophers
time_to_die
time_to_eat
time_to_sleep
[number_of_times_each_philosopher_must_eat]
*/
