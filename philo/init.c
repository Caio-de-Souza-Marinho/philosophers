/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caide-so <caide-so@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 22:12:03 by caide-so          #+#    #+#             */
/*   Updated: 2025/03/17 22:53:41 by caide-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_philos(t_table *table);

void	init_table(t_table *table)
{
	int	i;

	table->simulation_ended = 0;
	table->finished_meals = 0;
	table->start_time = get_time();
	pthread_mutex_init(&table->write_mutex, NULL);
	pthread_mutex_init(&table->sim_mutex, NULL);
	table->forks = (t_fork *)malloc((sizeof(t_fork) * table->nbr_philos));
	if (!table->forks)
		exit (EXIT_FAILURE);
	i = 0;
	while (i < table->nbr_philos)
	{
		pthread_mutex_init(&table->forks[i].fork, NULL);
		table->forks[i].fork_id = i;
		i++;
	}
	table->philos = (t_philo *)malloc((sizeof(t_philo) * table->nbr_philos));
	if (!table->philos)
	{
		free(table->forks);
		exit(EXIT_FAILURE);
	}
	init_philos(table);
}

void	init_philos(t_table *table)
{
	int		i;
	t_philo	*philo;

	i = 0;
	while (i < table->nbr_philos)
	{
		philo = &table->philos[i];
		philo->id = i + 1;
		philo->meal_counter = 0;
		philo->right_fork = &table->forks[i];
		philo->left_fork = &table->forks[(i + 1) % table->nbr_philos];
		philo->table = table;
		philo->last_meal_time = table->start_time;
		//TODO mutexes
		//TODO assign_fork();
		i++;
	}
}
