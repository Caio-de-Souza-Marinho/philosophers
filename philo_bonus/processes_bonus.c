/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caide-so <caide-so@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 08:10:16 by caide-so          #+#    #+#             */
/*   Updated: 2025/04/05 17:09:49 by caide-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	spawn_philos(t_table *table)
{
	//pid_t	pid;
	int		i;

	i = 0;
	while (i < table->nbr_philos)
	{
		table->philos[i].id = i + 1;
		table->philos[i].table = table;
		table->philos[i].meals_eaten = table->nbr_meals;
		/*
		pid = fork();
		if (pid < 0)
			error_exit("Fork error");
		else if (pid == 0)
		{
			routine(table, &table->philos[i]);
			exit(EXIT_FAILURE);
		}
		else
			table->philos[i].pid = pid;
		*/
		i++;
	}
}
