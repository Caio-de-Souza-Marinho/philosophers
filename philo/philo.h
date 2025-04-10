/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caide-so <caide-so@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 21:56:03 by caide-so          #+#    #+#             */
/*   Updated: 2025/04/02 22:36:13 by caide-so         ###   ########.fr       */
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

// to use gettimeofday
# include <sys/time.h>

// to use write, usleep
# include <unistd.h>

// to use pthread_create, pthread_detach, pthread_join, pthread_mutex_init,
// pthread_mutex_destroy, pthread_mutex_loc, pthread_mutex_unlock
# include <pthread.h>

// predefined error codes
# include <errno.h>

// Defines operation modes for mutex handling, used with the safe_mutex function
typedef enum e_mode
{
	INIT,
	LOCK,
	UNLOCK,
	DESTROY
}	t_mode;

typedef struct s_table	t_table;

// Represents a fork (shared resource) in the simulation
//
// Members:
// fork: Mutex controlling access to the fork
//
// fork_id: Unique identifier for debugging/logging
//
// Note: Forks are shared between adjacent philosophers
typedef struct s_fork
{
	pthread_mutex_t	fork;
	int				fork_id;
}	t_fork;

// Stores data for an individual philosopher
//
// Members:
// id: Philosopher's unique identifier (1-indexed)
//
// meal_counter: Tracks meals eaten (compared to nbr_meals)
//
// right_fork: Pointer to the fork on the philosopher's right
//
// left_fork: Pointer to the fork on the philosopher's left
//
// thread_id: Thread handle for the philosopher's routine
//
// meal_mutex: Mutex guarding access to last_meal_time and meal_counter
//
// last_meal_time: Timestamp(ms) of the philosopher's last meal
//
// table: Pointer to the global simulation state (t_table)
//
// Note: Forks are arranged circularly (last philo's left fork = first
// philo's right fork)
typedef struct s_philo
{
	int				id;
	int				meal_counter;
	t_fork			*right_fork;
	t_fork			*left_fork;
	pthread_t		thread_id;
	pthread_mutex_t	meal_mutex;
	unsigned long	last_meal_time;
	t_table			*table;
}	t_philo;

// Central simulation configuration and state
//
// Members:
// nbr_philos: Total number of philosophers
//
// time_to_die: Max time(ms) a philosopher can go without eating
//
// time_to_eat: Time(ms) a philosopher spends eating
//
// time_to_sleep: Time(ms) a philosopher spends sleeping
//
// nbr_meals: Optional meal goal
//
// simulation_ended: Flag to terminate all threads (1 = end)
//
// monitor: Thread handle for the monitoring thread
//
// start_time: Timestamp(ms) of simulation start
//
// write_mutex: Mutex for synchronized log output
//
// sim_mutex: Mutex guardind simulation_ended and finished_meals
//
// forks: Array of t_fork shared between philosophers
//
// philos: Array of t_philo representing each philosoper
typedef struct s_table
{
	int				nbr_philos;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	int				nbr_meals;
	int				simulation_ended;
	pthread_t		monitor;
	unsigned long	start_time;
	pthread_mutex_t	write_mutex;
	pthread_mutex_t	sim_mutex;
	t_fork			*forks;
	t_philo			*philos;
}	t_table;

// input check 
void			parse_args(int argc, char **argv, t_table *table);
int				validate_args(int argc, t_table *table);

// init
void			init_table(t_table *table);

// utils
unsigned long	get_time(void);
long			ft_atol(char *str);
void			error_exit(t_table *table, char *error);
void			print_message(t_philo *philo, char *msg);
int				ft_strcmp(const char *s1, const char *s2);

// safe functions
void			safe_mutex(t_table *table, pthread_mutex_t *mutex, t_mode mode);
void			handle_mutex_errors(int status, t_mode mode);

// threads
void			create_threads(t_table *table);
void			join_threads(t_table *table);

// routine
void			*one_philo(void *arg);
void			*routine(void *arg);
void			take_forks(t_philo *philo);
void			eat_sleep_think(t_philo *philo);

// clean
void			clean(t_table *table);

// monitor
void			monitor(t_table *table);
int				check_philo_death(t_philo *philo, long time_to_die);
int				check_all_meals(t_table *table);

#endif
