/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caide-so <caide-so@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 18:53:07 by caide-so          #+#    #+#             */
/*   Updated: 2025/04/05 17:16:23 by caide-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

// MACROS
# define FORKS "/forks"
# define WRITE "/write"
# define SIM_END "/sim_end"
# define MEALS_EATEN "/meals_eaten"
# define MAX_PH "/max_philos"
# define MEAL_TIME "/meal_time"

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

typedef struct s_philo
{
	pid_t			pid;
	int				id;
	unsigned long	last_meal_time;
	int				meals_eaten;
	t_table			*table;
}	t_philo;

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
	sem_t			*sim_end;
	sem_t			*meals_eaten;
	sem_t			*max_philos;
	sem_t			*meal_time;
	t_philo			*philos;
}	t_table;

// input check
void			parse_args(int argc, char **argv, t_table *config);
int				validate_args(int argc, t_table *config);

// utils
unsigned long	get_time(void);
long			ft_atol(char *str);
void			clean(t_table *table);
void			error_exit(char *error);
void			print_message(t_table *table, t_philo *philo, char *msg);
void			unlink_all(void);
int				ft_strcmp(const char *s1, const char *s2);

// init
void			init_table(t_table *table);
void			init_sems(t_table *table);

// processes
void			spawn_philos(t_table *table);

// routine
void			routine(t_table *table, t_philo *philo);
void			one_philo_routine(t_table *table, t_philo *philo);
void			philos_routine(t_table *table, t_philo *philo);
void			take_forks(t_table *table, t_philo *philo);
void			eat_sleep_think(t_table *table, t_philo *philo);

// monitor
void			*monitor(void *arg);
void			*monitor_meals(void *arg);
void			monitor_processes(t_table *table);

#endif
