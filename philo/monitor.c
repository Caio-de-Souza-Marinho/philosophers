/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caide-so <caide-so@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 21:20:01 by caide-so          #+#    #+#             */
/*   Updated: 2025/04/02 22:36:13 by caide-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
 * - infinite loop that contains the function check philos
 * - checks if a philo is dead of if all meals were eaten
*/
void	monitor(t_table *table)
{
	int	i;

	while (1)
	{
		i = 0;
		while (i < table->nbr_philos)
		{
			if (check_philo_death(&table->philos[i], table->time_to_die))
				return ;
			i++;
		}
		if (check_all_meals(table))
		{
			safe_mutex(table, &table->sim_mutex, LOCK);
			table->simulation_ended = 1;
			safe_mutex(table, &table->sim_mutex, UNLOCK);
			return ;
		}
		safe_mutex(table, &table->sim_mutex, LOCK);
		if (table->simulation_ended)
			return ;
		safe_mutex(table, &table->sim_mutex, UNLOCK);
		usleep(1000);
	}
}

int	check_philo_death(t_philo *philo, long time_to_die)
{
	unsigned long	time_since_meal;
	int				is_dead;

	is_dead = 0;
	safe_mutex(philo->table, &philo->meal_mutex, LOCK);
	time_since_meal = get_time() - philo->last_meal_time;
	safe_mutex(philo->table, &philo->meal_mutex, UNLOCK);
	safe_mutex(philo->table, &philo->table->sim_mutex, LOCK);
	if (!philo->table->simulation_ended
		&& time_since_meal > (unsigned long)time_to_die + 1)
	{
		philo->table->simulation_ended = 1;
		is_dead = 1;
	}
	safe_mutex(philo->table, &philo->table->sim_mutex, UNLOCK);
	if (is_dead)
	{
		print_message(philo, "is dead");
		return (1);
	}
	return (0);
}

int	check_all_meals(t_table *table)
{
	int	i;
	int	all_ate;

	i = 0;
	all_ate = 1;
	if (table->nbr_meals == -1)
		return (0);
	while (i < table->nbr_philos)
	{
		safe_mutex(table, &table->philos[i].meal_mutex, LOCK);
		if (table->philos[i].meal_counter < table->nbr_meals)
			all_ate = 0;
		safe_mutex(table, &table->philos[i].meal_mutex, UNLOCK);
		if (!all_ate)
			break ;
		i++;
	}
	return (all_ate);
}

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
