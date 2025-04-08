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

	sem_wait(table->meal_time);
	philo->last_meal_time = get_time();
	sem_post(table->meal_time);
	pthread_create(&monitor_thread, NULL, monitor, philo);
	pthread_detach(monitor_thread);
	if (table->nbr_philos == 1)
		one_philo_routine(table, philo);
	else
		philos_routine(table, philo);
	sem_close(table->forks);
	sem_close(table->write);
	sem_close(table->sim_end);
	sem_close(table->meals_eaten);
	sem_close(table->max_philos);
	sem_close(table->meal_time);
}

void	one_philo_routine(t_table *table, t_philo *philo)
{
	print_message(table, philo, "has taken a fork");
	while (1)
		usleep(1000);
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
			break ;
		}
	}
	sem_close(table->forks);
	sem_close(table->write);
	exit(EXIT_SUCCESS);
}

void	take_forks(t_table *table, t_philo *philo)
{
	usleep(100 * (philo->id % 3));
	sem_wait(table->max_philos);
	sem_wait(table->forks);
	print_message(table, philo, "has taken a fork");
	sem_wait(table->forks);
	print_message(table, philo, "has taken a fork");
}

void	eat_sleep_think(t_table *table, t_philo *philo)
{
	print_message(table, philo, "is eating");
	sem_wait(table->meal_time);
	philo->last_meal_time = get_time();
	sem_post(table->meal_time);
	usleep(table->time_to_eat * 1000);
	philo->meals_eaten++;
	sem_post(table->forks);
	sem_post(table->forks);
	sem_post(table->max_philos);
	print_message(table, philo, "is sleeping");
	usleep(table->time_to_sleep * 1000);
	print_message(table, philo, "is thinking");
}
