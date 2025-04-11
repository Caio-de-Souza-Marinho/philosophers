/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caide-so <caide-so@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 21:49:44 by caide-so          #+#    #+#             */
/*   Updated: 2025/04/04 12:02:13 by caide-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

// Initializes simulation resources (semaphores and philosophers)
// 1. Allocates memory for philosophers
// 2. Calls init_sems to set up semaphores
void	init_table(t_table *table)
{
	table->start_time = get_time();
	table->philos = (t_philo *)malloc((sizeof(t_philo) * table->nbr_philos));
	init_sems(table);
}

// Creates and initializes semaphores
// 1. Unlinks existing semaphores to avoid conflicts
// 2. Opens new semaphores with appropriate permissions
void	init_sems(t_table *table)
{
	sem_unlink(FORKS);
	sem_unlink(WRITE);
	table->forks = sem_open(FORKS, O_CREAT, 0644, table->nbr_philos);
	table->write = sem_open(WRITE, O_CREAT, 0644, 1);
}

// Initializes philosophers
// 1. Assigns IDs and links philosophers to the global table
// 2. Sets initial meal count and death time
void	init_philos(t_table *table)
{
	int		i;

	i = 0;
	while (i < table->nbr_philos)
	{
		table->philos[i].id = i + 1;
		table->philos[i].table = table;
		table->philos[i].meals_eaten = table->nbr_meals;
		table->philos[i].death_time = table->time_to_die;
		i++;
	}
}
