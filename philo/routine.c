/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caide-so <caide-so@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 22:45:27 by caide-so          #+#    #+#             */
/*   Updated: 2025/04/02 22:35:50 by caide-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// Simulates a single philosopher's actions
// 1. Locks the only available fork
// 2. Waits until the philosopher's death time elapses
void	*one_philo(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	safe_mutex(philo->table, &philo->right_fork->fork, LOCK);
	print_message(philo, "has taken a fork");
	usleep(philo->table->time_to_die * 1000);
	safe_mutex(philo->table, &philo->right_fork->fork, UNLOCK);
	return (NULL);
}

// Main loop for philosophers behavior
// 1. Continuously checks if the simulation has ended
// 2. Acquires forks, eats, sleeps and thinks
void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		safe_mutex(philo->table, &philo->table->sim_mutex, LOCK);
		if (philo->table->simulation_ended)
		{
			safe_mutex(philo->table, &philo->table->sim_mutex, UNLOCK);
			break ;
		}
		safe_mutex(philo->table, &philo->table->sim_mutex, UNLOCK);
		take_forks(philo);
		eat_sleep_think(philo);
		usleep(100);
	}
	return (NULL);
}

// Manages fork acquisition to avoid deadlock
// 1. Even-numbered philosophers delay slightly to stagger fork pickup
// 2. Alternates fork pickup order based on philosopher ID parity
void	take_forks(t_philo *philo)
{
	char	*msg;

	msg = "has taken a fork";
	if (philo->id % 2 == 0)
		usleep(100);
	if (philo->id % 2 == 0)
	{
		safe_mutex(philo->table, &philo->left_fork->fork, LOCK);
		print_message(philo, msg);
		safe_mutex(philo->table, &philo->right_fork->fork, LOCK);
		print_message(philo, msg);
	}
	else
	{
		safe_mutex(philo->table, &philo->right_fork->fork, LOCK);
		print_message(philo, msg);
		safe_mutex(philo->table, &philo->left_fork->fork, LOCK);
		print_message(philo, msg);
	}
}

// Executes eating sleeping and thinking phases
// 1. Updates the philosopher's last meal time
// 2. Releases forks after eating
// 3. Sleeps and thinks for the specified durations
void	eat_sleep_think(t_philo *philo)
{
	safe_mutex(philo->table, &philo->meal_mutex, LOCK);
	philo->last_meal_time = get_time();
	safe_mutex(philo->table, &philo->meal_mutex, UNLOCK);
	print_message(philo, "is eating");
	usleep(philo->table->time_to_eat * 1000);
	safe_mutex(philo->table, &philo->meal_mutex, LOCK);
	philo->meal_counter++;
	safe_mutex(philo->table, &philo->meal_mutex, UNLOCK);
	safe_mutex(philo->table, &philo->left_fork->fork, UNLOCK);
	safe_mutex(philo->table, &philo->right_fork->fork, UNLOCK);
	print_message(philo, "is sleeping");
	usleep(philo->table->time_to_sleep * 1000);
	print_message(philo, "is thinking");
}
