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
	table->forks = SEM_FAILED;
	table->write = SEM_FAILED;
	table->sim_end = SEM_FAILED;
	table->meals_eaten = SEM_FAILED;
	table->max_philos = SEM_FAILED;
	table->meal_time = SEM_FAILED;
	init_sems(table);
}

void	init_sems(t_table *table)
{
	unlink_all();
	table->forks = sem_open(FORKS, O_CREAT, 0644, table->nbr_philos);
	clean_exit(table, table->forks, "Failed to create forks semaphore");
	table->write = sem_open(WRITE, O_CREAT, 0644, 1);
	clean_exit(table, table->write, "Failed to create write semaphore");
	table->sim_end = sem_open(SIM_END, O_CREAT, 0644, 0);
	clean_exit(table, table->sim_end, "Failed to create meals_eaten semaphore");
	table->meals_eaten = sem_open(MEALS_EATEN, O_CREAT, 0644, 0);
	clean_exit(table, table->meals_eaten, "Failed meals_eaten semaphore");
	table->max_philos = sem_open(MAX_PH, O_CREAT, 0644, table->nbr_philos - 1);
	clean_exit(table, table->max_philos, "Failed max_philos semaphore");
	table->meal_time = sem_open(MEAL_TIME, O_CREAT, 0644, 1);
	clean_exit(table, table->meal_time, "Failed to create meal_time semaphore");
}

void	clean_exit(t_table *table, sem_t *semaphore, char *msg)
{
	sem_t	*sem;

	sem = semaphore;
	if (sem == SEM_FAILED)
	{
		clean(table);
		error_exit(msg);
	}
}

void	unlink_all(void)
{
	sem_unlink(FORKS);
	sem_unlink(WRITE);
	sem_unlink(SIM_END);
	sem_unlink(MEALS_EATEN);
	sem_unlink(MAX_PH);
	sem_unlink(MEAL_TIME);
}
