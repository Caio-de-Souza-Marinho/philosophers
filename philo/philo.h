/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caide-so <caide-so@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 21:56:03 by caide-so          #+#    #+#             */
/*   Updated: 2025/03/17 22:59:44 by caide-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

// to use memset
# include <string.h>

// to use printf
# include <stdio.h>

// to use malloc, free
# include <stdlib.h>

// to use function gettimeofday
# include <sys/time.h>

// to use write, usleep
# include <unistd.h>

// to use pthread_create, pthread_detach, pthread_join, pthread_mutex_init,
// pthread_mutex_destroy, pthread_mutex_loc, pthread_mutex_unlock
# include <pthread.h>

// predefined error codes
# include <errno.h>

typedef enum e_mode
{
	INIT,
	LOCK,
	UNLOCK,
	CREATE,
	JOIN,
	DETACH,
	DESTROY
}	t_mode;

typedef struct s_table	t_table;

typedef struct s_fork
{
	pthread_mutex_t	fork;
	int				fork_id;
}	t_fork;

typedef struct s_philo
{
	int				id;
	int				meal_counter;
	t_fork			*right_fork;
	t_fork			*left_fork;
	pthread_t		thread_id;
	pthread_mutex_t	philo_mutex;
	unsigned long	last_meal_time;
	t_table			*table;
}	t_philo;

typedef struct s_table
{
	int				nbr_philos;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	int				nbr_meals;
	int				simulation_ended;
	int				finished_meals;
	pthread_t		monitor;
	unsigned long	start_time;
	pthread_mutex_t	write_mutex;
	pthread_mutex_t	sim_mutex;
	t_fork			*forks;
	t_philo			*philos;
}	t_table;

// input check 
void			parse_args(int argc, char **argv, t_table *table);
void			validate_args(int argc, t_table *table);

// init
void			init_table(t_table *table);

// utils
unsigned long	get_time(void);
long			ft_atol(char *str);
void			error_exit(t_table *table, char *error);

// safe functions
void			safe_mutex(t_table *table, pthread_mutex_t *mutex, t_mode mode);
void			handle_mutex_errors(t_table *table, int status, t_mode mode);

#endif
