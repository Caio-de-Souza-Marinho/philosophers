/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caide-so <caide-so@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 20:26:25 by caide-so          #+#    #+#             */
/*   Updated: 2025/04/02 22:36:13 by caide-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// Converts a string to a long integer, handling signs and whitespace
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

// Retrieves the current system time in miliseconds
// 1. Uses gettimeofday to fetch the system time
// 2. Combines seconds and microseconds into a milisecond timestamp
unsigned long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

// Prints philosopher actions with timestamps
// 1. Checks if the simulation has ended before printing
// 2. Uses a mutex to synchronize log output
void	print_message(t_philo *philo, char *msg)
{
	unsigned long	time;

	if (ft_strcmp(msg, "died") != 0)
	{
		safe_mutex(philo->table, &philo->table->sim_mutex, LOCK);
		if (philo->table->simulation_ended)
		{
			safe_mutex(philo->table, &philo->table->sim_mutex, UNLOCK);
			return ;
		}
		safe_mutex(philo->table, &philo->table->sim_mutex, UNLOCK);
	}
	safe_mutex(philo->table, &philo->table->write_mutex, LOCK);
	time = get_time() - philo->table->start_time;
	printf("%lu %d %s\n", time, philo->id, msg);
	safe_mutex(philo->table, &philo->table->write_mutex, UNLOCK);
}

// Locks write mutex and prints an error message
void	error_exit(t_table *table, char *error)
{
	safe_mutex(table, &table->write_mutex, LOCK);
	printf("%s", error);
	safe_mutex(table, &table->write_mutex, UNLOCK);
}

// Releases all allocated resources and destroys mutexes
// 1. Iterates through forks and philosophers to destroy mutexes
// 2. Frees memory for forks, philosophers and global mutexes
void	clean(t_table *table)
{
	int		i;

	if (table->forks)
	{
		i = 0;
		while (i < table->nbr_philos)
		{
			safe_mutex(table, &table->forks[i].fork, DESTROY);
			i++;
		}
		free(table->forks);
	}
	if (table->philos)
	{
		i = 0;
		while (i < table->nbr_philos)
		{
			safe_mutex(table, &table->philos[i].meal_mutex, DESTROY);
			i++;
		}
		free(table->philos);
	}
	safe_mutex(table, &table->write_mutex, DESTROY);
	safe_mutex(table, &table->sim_mutex, DESTROY);
}
