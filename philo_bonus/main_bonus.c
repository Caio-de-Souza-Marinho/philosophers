/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caide-so <caide-so@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 18:52:29 by caide-so          #+#    #+#             */
/*   Updated: 2025/04/05 17:24:19 by caide-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

pid_t	single_philo(t_table *table);
void	close_all_sems(t_table *table);

int	main(int argc, char **argv)
{
	t_table		table;
	pid_t		tmp_pid;

	if (argc != 5 && argc != 6)
	{
		printf("ERROR: Wrong number of arguments\n");
		return (1);
	}
	parse_args(argc, argv, &table);
	if (validate_args(argc, &table))
		return (1);
	init_table(&table);
	spawn_philos(&table);
	if (table.nbr_philos == 1)
	{
		tmp_pid = single_philo(&table);
		waitpid(-1, &tmp_pid, 0);
		close_all_sems(&table);
		clean(&table);
	}
	else
	{
		start_philo(&table);
		close_all_sems(&table);
		clean(&table);
	}
	return (0);
}

pid_t	single_philo(t_table *table)
{
	pid_t	pid;
	t_philo	*philo;

	philo = &table->philos[0];
	pid = fork();
	if (pid == -1)
		error_exit("Fork error");
	else if (pid == 0)
	{
		table->start_time = get_time();
		philo->death_time = table->time_to_die - get_time();
		sem_wait(table->forks);
		print_message(table, philo, "has taken a fork");
		usleep(table->time_to_die * 1000);
		print_message(table, philo, "died");
		sem_close(table->write);
		sem_close(table->forks);
		clean(table);
		exit(EXIT_SUCCESS);
	}
	return (pid);
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
/*
void	print_table(t_table *table);
void	print_philos(t_table *table);
*/

/*
void	print_table(t_table *table)
{
	printf("number of philos - %d\n", table->nbr_philos);
	printf("time to die - %ld\n", table->time_to_die);
	printf("time to eat - %ld\n", table->time_to_eat);
	printf("time to sleep - %ld\n", table->time_to_sleep);
	printf("number of meals - %d\n", table->nbr_meals);
	printf("simulation ended - %d\n", table->simulation_ended);
	printf("finished meals - %d\n", table->finished_meals);
	printf("start time - %lu\n", table->start_time);
	print_philos(table);
}

void	print_philos(t_table *table)
{
	int	i;

	i = 0;
	printf("==========PHILOS=========\n");
	while (i < table->nbr_philos)
	{
		printf("philo %d ate %d meals\n", table->philos[i].id,
			table->philos[i].meals_eaten);
		i++;
	}
	printf("===========END===========\n");
}
*/
