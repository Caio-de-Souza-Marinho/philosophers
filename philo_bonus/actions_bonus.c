/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caide-so <caide-so@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 20:22:57 by caide-so          #+#    #+#             */
/*   Updated: 2025/04/09 20:24:40 by caide-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

// Philosopher's main action loop
// 1. Acquires forks via semaphores (sem_wait)
// 2. Updates death time and logs eating
// 3. Releases forks after eating (sem_post)
// 4. Sleeps and thinks
//
// Note: Uses look_up to check for starvation during actions
void	eat_sleep_think(t_table *table, t_philo *philo)
{
	take_forks(table, philo);
	philo->death_time = table->time_to_die + get_time();
	look_up(philo);
	print_message(table, philo, "is eating");
	philo->meals_eaten--;
	look_up(philo);
	usleep(table->time_to_eat * 1000);
	sem_post(table->forks);
	sem_post(table->forks);
	print_message(table, philo, "is sleeping");
	usleep(table->time_to_sleep * 1000);
	print_message(table, philo, "is thinking");
	look_up(philo);
}

// Acquires two forks using semaphores
// 1. Waits until at least two forks are available
// 2. Locks forks semaphore twice
//
// Note: Semaphore count represent available forks
void	take_forks(t_table *table, t_philo *philo)
{
	wait_forks(philo);
	sem_wait(table->forks);
	print_message(table, philo, "has taken a fork");
	sem_wait(table->forks);
	print_message(table, philo, "has taken a fork");
}

// Busy waits until at least two forks are available for the philosopher
// 1. Continuously checks the semaphore count to ensure >= 2 forks
// 2. Calls look_up during the wait to check for starvation
//
// Note: Avoids deadlock by ensuring a philosopher only proceeds when two forks
// are free
//
// Note: Uses active waiting but includes starvation checks to prevent infinite
// loops
void	wait_forks(t_philo *philo)
{
	while (*(int *)philo->table->forks < 2)
		look_up(philo);
}

// Checks if the philosopher has starved
// 1. Compares current time to death_time
// 2. Terminates the process if starved
//
// Note: Replaces the monitor thread from the mandatory version
void	look_up(t_philo *philo)
{
	if (get_time() >= (unsigned long)philo->death_time + 1)
	{
		print_message(philo->table, philo, "died");
		sem_close(philo->table->write);
		sem_close(philo->table->forks);
		clean(philo->table);
		exit(EXIT_FAILURE);
	}
}
