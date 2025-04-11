/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caide-so <caide-so@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 12:34:17 by caide-so          #+#    #+#             */
/*   Updated: 2025/04/09 20:10:40 by caide-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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

// Logs philosopher actions with timestamps
// 1. Uses sem_wait and sem_post on the write semaphore
// 2. Bypasses checks for "died" messages to ensure final log
void	print_message(t_table *table, t_philo *philo, char *msg)
{
	unsigned long	time;

	time = get_time() - table->start_time;
	if (ft_strcmp(msg, "died") == 0)
	{
		sem_wait(table->write);
		printf("%lu %d %s\n", time, philo->id, msg);
		return ;
	}
	else
	{
		sem_wait(table->write);
		printf("%lu %d %s\n", time, philo->id, msg);
		sem_post(table->write);
	}
}

// Prints error and exit
void	error_exit(char *error)
{
	printf("%s\n", error);
	exit (EXIT_FAILURE);
}

// Compares s1 and s2 until a mismatch of end of string
// Returns the ASCII difference between the first mismatched characters
int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while ((s1[i] || s2[i]))
	{
		if ((unsigned char)s1[i] != (unsigned char)s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}
