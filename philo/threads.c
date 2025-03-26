/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caide-so <caide-so@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 20:57:38 by caide-so          #+#    #+#             */
/*   Updated: 2025/03/25 22:46:27 by caide-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	create_threads(t_table *table)
{
	int		i;
	t_philo	*solo_philo;

	i = 0;
	if (table->nbr_meals == 0)
		return ;
	else if (table->nbr_philos == 1)
	{
		solo_philo = &table->philos[0];
		pthread_create(&solo_philo->thread_id, NULL, one_philo, solo_philo);
	}
	else
	{
		while (i < table->nbr_philos)
		{
			pthread_create(&table->philos[i].thread_id, NULL,
				routine, &table->philos[i]);
			i++;
		}
	}
}

void	join_threads(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->nbr_philos)
	{
		pthread_join(table->philos[i].thread_id, NULL);
		i++;
	}
}
