/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caide-so <caide-so@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 10:13:17 by caide-so          #+#    #+#             */
/*   Updated: 2025/04/05 17:24:55 by caide-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	take_process(t_table *table);
void	wait_forks(t_philo *philo);
void	kill_process(t_table *table);
void	look_up(t_philo *philo);

void	start_philo(t_table *table)
{
	int	i;

	i = 0;
	table->start_time = get_time();
	while (i < table->nbr_philos)
	{
		routine(table, i);
		usleep(1);
		i++;
	}
	take_process(table);
}

void	routine(t_table *table, int id)
{
	pid_t	pid;
	t_philo	*philo;

	pid = fork();
	if (pid == 0)
	{
		philo = &table->philos[id];
		philo->death_time = table->time_to_die + get_time();
		if (philo->id % 2 == 0)
			usleep(500);
		while (philo->meals_eaten != 0)
			eat_sleep_think(table, philo);
		sem_close(table->write);
		sem_close(table->forks);
		clean(table);
		exit(EXIT_SUCCESS);
	}
	else
		table->philos[id].pid = pid;
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

/*
void	philos_routine(t_table *table, t_philo *philo)
{
	while (1)
	{
		take_forks(table, philo);
		eat_sleep_think(table, philo);
		if (table->nbr_meals != -1
			&& philo->meals_eaten >= table->nbr_meals)
		{
			sem_post(table->meals_eaten);
			break ;
		}
	}
	sem_close(table->forks);
	sem_close(table->write);
	exit(EXIT_SUCCESS);
}
*/

void	eat_sleep_think(t_table *table, t_philo *philo)
{
	take_forks(table, philo);
	philo->death_time = table->time_to_die + get_time();
	look_up(philo);
	print_message(table, philo, "is eating");
	philo->meals_eaten--;
	look_up(philo);
	usleep(table->time_to_eat * 1000);
	sem_post(table->forks);
	sem_post(table->forks);
	print_message(table, philo, "is sleeping");
	usleep(table->time_to_sleep * 1000);
	print_message(table, philo, "is thinking");
}

void	take_forks(t_table *table, t_philo *philo)
{
	wait_forks(philo);
	sem_wait(table->forks);
	print_message(table, philo, "has taken a fork");
	sem_wait(table->forks);
	print_message(table, philo, "has taken a fork");
}

void	wait_forks(t_philo *philo)
{
	while (*(int16_t *)philo->table->forks < 2)
		look_up(philo);
}

void	look_up(t_philo *philo)
{
	if (get_time() >= (unsigned long)philo->death_time + 1)
	{
		print_message(philo->table, philo, "died");
		sem_close(philo->table->write);
		sem_close(philo->table->forks);
		clean(philo->table);
		exit(EXIT_FAILURE);
	}
}
