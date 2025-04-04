/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caide-so <caide-so@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 21:49:44 by caide-so          #+#    #+#             */
/*   Updated: 2025/04/01 21:59:54 by caide-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	init_sems(t_table *table);

void	init_table(t_table *table)
{
	table->start_time = get_time();
	table->philos = (t_philo *)malloc((sizeof(t_philo) * table->nbr_philos));
	init_sems(table);
}

void	init_sems(t_table *table)
{
	table->forks = sem_open("/forks", O_CREAT, 0644, table->nbr_philos);
	if (table->forks == SEM_FAILED)
		error_exit("Failed to create forks semaphore");
	table->write = sem_open("/write", O_CREAT, 0644, 1);
	if (table->write == SEM_FAILED)
		error_exit("Failed to create write semaphore");
	table->sim_end = sem_open("/sim_end", O_CREAT, 0644, 0);
	if (table->sim_end == SEM_FAILED)
		error_exit("Failed to create sim_end semaphore");
	table->meals_eaten = sem_open("/meals_eaten", O_CREAT, 0644, 0);
	if (table->meals_eaten == SEM_FAILED)
		error_exit("Failed to create meals_eaten semaphore");
}
