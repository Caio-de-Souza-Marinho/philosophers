/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caide-so <caide-so@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 10:13:17 by caide-so          #+#    #+#             */
/*   Updated: 2025/04/04 10:29:15 by caide-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	one_philo(t_table *table, t_philo *philo);

void	routine(t_table *table, t_philo *philo)
{
	if (table->nbr_philos == 1)
		one_philo(table, philo);
	//else
		//TODO: routine(philo);
}

void	one_philo(t_table *table, t_philo *philo)
{
	print_message(table, philo, "has taken a fork");
	usleep(table->time_to_die * 1000);
}
