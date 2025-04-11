/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caide-so <caide-so@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 10:13:17 by caide-so          #+#    #+#             */
/*   Updated: 2025/04/09 20:54:06 by caide-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

// Entry point for philosopher processes
// 1. Handle single philosopher edge case separately
// 2. Forks processes for all philosophers
//
// Note: Parent process waits for children via take_process
void	routine(t_table *table)
{
	pid_t		tmp_pid;

	if (table->nbr_philos == 1)
	{
		tmp_pid = one_philo_routine(table);
		waitpid(-1, &tmp_pid, 0);
		close_all_sems(table);
		clean(table);
	}
	else
	{
		start_routine(table);
		close_all_sems(table);
		clean(table);
	}
}

// Simulates a single philosopher
// 1. Locks the only fork using sem_wait
// 2. Waits until death time elapses
pid_t	one_philo_routine(t_table *table)
{
	pid_t	pid;
	t_philo	*philo;

	philo = &table->philos[0];
	pid = fork();
	if (pid == -1)
		error_exit("Fork error");
	else if (pid == 0)
	{
		table->start_time = get_time();
		philo->death_time = table->time_to_die - get_time();
		sem_wait(table->forks);
		print_message(table, philo, "has taken a fork");
		usleep(table->time_to_die * 1000);
		print_message(table, philo, "died");
		sem_close(table->write);
		sem_close(table->forks);
		clean(table);
		exit(EXIT_SUCCESS);
	}
	return (pid);
}

// Launches philosopher processes
// 1. Forks a process for each philosopher
// 2. Staggers even-numbered philosophers to reduce contention
void	start_routine(t_table *table)
{
	int	i;

	i = 0;
	table->start_time = get_time();
	while (i < table->nbr_philos)
	{
		philos_routine(table, i);
		usleep(1);
		i++;
	}
	take_process(table);
}

// Creates a child process for a philosopher and executes their behavior loop
// 1. Forks a process for the philosopher with the given id
// 2. Assigns the philosopher's initial death_time
// 3. Staggers even-numbered philosophers with usleep(500) to reduce fork
// contention
// 4. Executes eat_sleep_think in a loop until the meal quota is met
//
// Note: Child processes exit after completing their meal goal
//
// Note: Parent process stores the child's PID in the philosopher struct
void	philos_routine(t_table *table, int id)
{
	pid_t	pid;
	t_philo	*philo;

	usleep(1000);
	pid = fork();
	if (pid == 0)
	{
		philo = &table->philos[id];
		philo->death_time = table->time_to_die + get_time();
		if (philo->id % 2 == 0)
			usleep(500);
		while (philo->meals_eaten != 0)
			eat_sleep_think(table, philo);
		sem_close(table->write);
		sem_close(table->forks);
		clean(table);
		exit(EXIT_SUCCESS);
	}
	else
		table->philos[id].pid = pid;
}
