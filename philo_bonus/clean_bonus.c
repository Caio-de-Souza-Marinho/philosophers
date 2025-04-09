/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caide-so <caide-so@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 20:09:17 by caide-so          #+#    #+#             */
/*   Updated: 2025/04/09 20:10:02 by caide-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	clean(t_table *table)
{
	if (table->philos)
	{
		free(table->philos);
		table->philos = NULL;
	}
}

void	close_all_sems(t_table *table)
{
	if (table->forks)
		sem_close(table->forks);
	if (table->write)
		sem_close(table->write);
	sem_unlink(FORKS);
	sem_unlink(WRITE);
}
