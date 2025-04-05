/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caide-so <caide-so@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 10:13:17 by caide-so          #+#    #+#             */
/*   Updated: 2025/04/05 17:24:55 by caide-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	routine(t_table *table, t_philo *philo)
{
	pthread_t	monitor_thread;

	philo->last_meal_time = table->start_time;
	pthread_create(&monitor_thread, NULL, monitor, philo);
	pthread_detach(monitor_thread);
	if (table->nbr_philos == 1)
		one_philo_routine(table, philo);
	else
		philos_routine(table, philo);
}

void	one_philo_routine(t_table *table, t_philo *philo)
{
	print_message(table, philo, "has taken a fork");
	usleep(table->time_to_die * 1000);
}

void	philos_routine(t_table *table, t_philo *philo)
{

	while (1)
	{
		take_forks(table, philo);
		eat_sleep_think(table, philo);
		if (table->nbr_meals != -1
			&& philo->meals_eaten >= table->nbr_meals)
		{
			sem_post(table->meals_eaten);
			exit(EXIT_SUCCESS);
		}
		usleep(100);
	}
}

void	take_forks(t_table *table, t_philo *philo)
{
	sem_wait(table->forks);
	print_message(table, philo, "has taken a fork");
	sem_wait(table->forks);
	print_message(table, philo, "has taken a fork");
}

void	eat_sleep_think(t_table *table, t_philo *philo)
{
	philo->last_meal_time = get_time();
	print_message(table, philo, "is eating");
	usleep(table->time_to_eat * 1000);
	philo->meals_eaten++;
	sem_post(table->forks);
	sem_post(table->forks);
	print_message(table, philo, "is sleeping");
	usleep(table->time_to_sleep * 1000);
	print_message(table, philo, "is thinking");
}
