/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caide-so <caide-so@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 22:45:27 by caide-so          #+#    #+#             */
/*   Updated: 2025/03/25 22:46:25 by caide-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*one_philo(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(&philo->right_fork->fork);
	print_message(philo, "has taken a fork");
	usleep(philo->table->time_to_die * 1000);
	pthread_mutex_unlock(&philo->right_fork->fork);
	return (NULL);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		pthread_mutex_lock(&philo->table->sim_mutex);
		if (philo->table->simulation_ended)
		{
			pthread_mutex_unlock(&philo->table->sim_mutex);
			break ;
		}
		pthread_mutex_unlock(&philo->table->sim_mutex);
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
		pthread_mutex_lock(&philo->left_fork->fork);
		print_message(philo, msg);
		pthread_mutex_lock(&philo->right_fork->fork);
		print_message(philo, msg);
	}
	else
	{
		pthread_mutex_lock(&philo->right_fork->fork);
		print_message(philo, msg);
		pthread_mutex_lock(&philo->left_fork->fork);
		print_message(philo, msg);
	}
}

void	eat_sleep_think(t_philo *philo)
{
	pthread_mutex_lock(&philo->meal_mutex);
	philo->last_meal_time = get_time();
	pthread_mutex_unlock(&philo->meal_mutex);
	print_message(philo, "is eating");
	usleep(philo->table->time_to_eat * 1000);
	pthread_mutex_lock(&philo->meal_mutex);
	philo->meal_counter++;
	pthread_mutex_unlock(&philo->meal_mutex);
	pthread_mutex_unlock(&philo->left_fork->fork);
	pthread_mutex_unlock(&philo->right_fork->fork);
	print_message(philo, "is sleeping");
	usleep(philo->table->time_to_sleep * 1000);
	print_message(philo, "is thinking");
}
