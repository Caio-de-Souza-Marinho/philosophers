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

void	init_sems(t_table *table);
void	clean_exit(t_table *table, sem_t *semaphore, char *msg);

void	init_table(t_table *table)
{
	table->start_time = get_time();
	table->philos = (t_philo *)malloc((sizeof(t_philo) * table->nbr_philos));
	init_sems(table);
}

void	init_sems(t_table *table)
{
	sem_unlink(FORKS);
	sem_unlink(WRITE);
	table->forks = sem_open(FORKS, O_CREAT, 0644, table->nbr_philos);
	table->write = sem_open(WRITE, O_CREAT, 0644, 1);
}
