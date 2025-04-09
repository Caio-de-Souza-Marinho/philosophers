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

void	take_forks(t_table *table, t_philo *philo);
void	wait_forks(t_philo *philo);
void	look_up(t_philo *philo);

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

void	take_forks(t_table *table, t_philo *philo)
{
	wait_forks(philo);
	sem_wait(table->forks);
	print_message(table, philo, "has taken a fork");
	sem_wait(table->forks);
	print_message(table, philo, "has taken a fork");
}

void	wait_forks(t_philo *philo)
{
	while (*(int *)philo->table->forks < 2)
		look_up(philo);
}

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
