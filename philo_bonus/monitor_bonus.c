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

/*
void	*monitor(void *arg)
{
	t_philo			*philo;
	t_table			*table;
	unsigned long	current_time;
	unsigned long	last_meal;

	philo = (t_philo *)arg;
	table = philo->table;
	while (1)
	{
		sem_wait(table->meal_time);
		current_time = get_time();
		last_meal = philo->last_meal_time;
		sem_post(table->meal_time);
		if (current_time - last_meal > (unsigned long)table->time_to_die + 1)
		{
			print_message(table, philo, "died");
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

void	monitor_processes(t_table *table)
{
	int	status;
	int	i;
	pid_t	pid;

	pid = waitpid(-1, &status, 0);
	if (WIFEXITED(status) || WIFSIGNALED(status))
	{
		i = 0;
		while (i < table->nbr_philos)
		{
			kill(table->philos[i].pid, SIGKILL);
			i++;
		}
		sem_post(table->sim_end);
	}
	(void)pid;
}
*/
