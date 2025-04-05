/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caide-so <caide-so@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 16:29:15 by caide-so          #+#    #+#             */
/*   Updated: 2025/04/05 17:20:45 by caide-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*monitor(void *arg)
{
	t_philo	*philo;
	t_table	*table;

	philo = (t_philo *)arg;
	table = philo->table;
	while (1)
	{
		if (get_time() - philo->last_meal_time
			>= (unsigned long)table->time_to_die + 1)
		{
			print_message(table, philo, "is dead");
			sem_post(table->sim_end);
			exit(EXIT_FAILURE);
		}
		usleep(1000);
	}
	return (NULL);
}

void	*monitor_meals(void *arg)
{
	t_table	*table;
	int		i;

	table = (t_table *)arg;
	i = 0;
	while (i < table->nbr_philos)
	{
		sem_wait(table->meals_eaten);
		i++;
	}
	sem_post(table->sim_end);
	return (NULL);
}
