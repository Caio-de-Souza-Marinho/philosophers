/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caide-so <caide-so@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 20:26:25 by caide-so          #+#    #+#             */
/*   Updated: 2025/03/25 21:41:21 by caide-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	ft_atol(char *str)
{
	long	res;
	int		sign;
	int		i;

	res = 0;
	sign = 1;
	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	while (str[i] == '+' && str[i - 1] != '-')
		i++;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		res = (res * 10) + (str[i] - '0');
		i++;
	}
	return (res * sign);
}

unsigned long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	print_message(t_philo *philo, char *msg)
{
	unsigned long	time;

	time = get_time() - philo->table->start_time;
	safe_mutex(philo->table, &philo->table->write_mutex, LOCK);
	if (!philo->table->simulation_ended)
		printf("%lu %d %s\n", time, philo->id, msg);
	safe_mutex(philo->table, &philo->table->write_mutex, UNLOCK);
}

void	error_exit(t_table *table, char *error)
{
	safe_mutex(table, &table->write_mutex, LOCK);
	printf("%s", error);
	safe_mutex(table, &table->write_mutex, UNLOCK);
}

void	clean(t_table *table)
{
	int		i;

	i = 0;
	while (i < table->nbr_philos)
	{
		safe_mutex(table, &table->forks[i].fork, DESTROY);
		i++;
	}
	i = 0;
	while (i < table->nbr_philos)
	{
		safe_mutex(table, &table->philos[i].meal_mutex, DESTROY);
		i++;
	}
	safe_mutex(table, &table->write_mutex, DESTROY);
	safe_mutex(table, &table->sim_mutex, DESTROY);
	free(table->forks);
	free(table->philos);
}
