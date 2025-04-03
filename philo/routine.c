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
