/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caide-so <caide-so@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 08:10:16 by caide-so          #+#    #+#             */
/*   Updated: 2025/04/09 20:21:40 by caide-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	spawn_philos(t_table *table)
{
	int		i;

	i = 0;
	while (i < table->nbr_philos)
	{
		table->philos[i].id = i + 1;
		table->philos[i].table = table;
		table->philos[i].meals_eaten = table->nbr_meals;
		table->philos[i].death_time = table->time_to_die;
		i++;
	}
}

void	take_process(t_table *table)
{
	int	i;
	int	status;

	i = 0;
	while (i < table->nbr_philos)
	{
		waitpid(-1, &status, 0);
		if (WIFEXITED(status))
			if (WEXITSTATUS(status) == EXIT_FAILURE)
				return (kill_process(table));
		i++;
	}
}

void	kill_process(t_table *table)
{
	int	i;

	i = 0 ;
	while (i < table->nbr_philos)
	{
		kill(table->philos[i].pid, SIGKILL);
		i++;
	}
}
