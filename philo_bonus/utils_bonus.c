/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caide-so <caide-so@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 12:34:17 by caide-so          #+#    #+#             */
/*   Updated: 2025/04/04 12:39:25 by caide-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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

void	error_exit(char *error)
{
	printf("%s\n", error);
	exit (EXIT_FAILURE);
}

void	clean(t_table *table)
{
	if (table->philos)
	{
		free(table->philos);
		table->philos = NULL;
	}
}
