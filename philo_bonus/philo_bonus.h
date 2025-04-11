/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caide-so <caide-so@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 18:53:07 by caide-so          #+#    #+#             */
/*   Updated: 2025/04/09 20:53:51 by caide-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

// semaphore macros
# define FORKS "/forks"
# define WRITE "/write"

// to use memset
# include <string.h>

// to use printf
# include <stdio.h>

// to use malloc, free, exit
# include <stdlib.h>

// to use function gettimeofday
# include <sys/time.h>

// to use write, usleep, fork
# include <unistd.h>

// to use pthread_create, pthread_detach, pthread_join
# include <pthread.h>

// predefined error codes
# include <errno.h>

// to use kill
# include <signal.h>

// for O_* constants
# include <fcntl.h>

// to use sem_open, sem_close, sem_post, sem_wait, sem_unlink
# include <semaphore.h>

// to use waitpid
# include <sys/wait.h>

// for pid_t data type
# include <sys/types.h>

typedef struct s_table	t_table;

// Represents a philosopher
//
// Members:
// id: Philosopher's unique idendifier (1-indexed)
//
// meals_eaten: Count of meals consumed (decrements from nbr_meals)
//
// death_time: Timestamp(ms) when the philosopher will starve
//
// table: Pointer to the global simulation state (t_table)
//
// Note: Each philosopher runs in a separate process
typedef struct s_philo
{
	pid_t			pid;
	int				id;
	int				meals_eaten;
	unsigned long	death_time;
	t_table			*table;
}	t_philo;

// Global simulation configuration and state
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
// start_time: Timestamp(ms) of simulation start
//
// forks: Semaphore representing available forks (shared across processes)
//
// write: Semaphore for synchronized log output
//
// philos: Array of t_philo
//
// Note: Semaphores replace mutexes for inter-process synchronization
typedef struct s_table
{
	int				nbr_philos;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	int				nbr_meals;
	unsigned long	start_time;
	sem_t			*forks;
	sem_t			*write;
	t_philo			*philos;
}	t_table;

// input check
void			parse_args(int argc, char **argv, t_table *config);
int				validate_args(int argc, t_table *config);

// utils
unsigned long	get_time(void);
long			ft_atol(char *str);
void			error_exit(char *error);
void			print_message(t_table *table, t_philo *philo, char *msg);
int				ft_strcmp(const char *s1, const char *s2);

// clean
void			clean(t_table *table);
void			close_all_sems(t_table *table);

// init
void			init_table(t_table *table);
void			init_sems(t_table *table);

// processes
void			init_philos(t_table *table);
void			take_process(t_table *table);
void			kill_process(t_table *table);

// routine
void			routine(t_table *table);
pid_t			one_philo_routine(t_table *table);
void			start_routine(t_table *table);
void			philos_routine(t_table *table, int id);

// actions
void			eat_sleep_think(t_table *table, t_philo *philo);
void			take_forks(t_table *table, t_philo *philo);
void			wait_forks(t_philo *philo);
void			look_up(t_philo *philo);

// monitor
void			*monitor(void *arg);
void			*monitor_meals(void *arg);
void			monitor_processes(t_table *table);

#endif
