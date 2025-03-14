/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caide-so <caide-so@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 21:55:11 by caide-so          #+#    #+#             */
/*   Updated: 2025/03/10 21:56:36 by caide-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

typedef struct	s_philo
{
	int	index;
	pthread_mutex_t	*mutex;
	long	time_to_eat;
	long	time_to_sleep;
	struct timeval	*start_time;
}	t_philo;

long	get_elapsed_ms(struct timeval *start)
{
	struct timeval	now;
	long	seconds;
	long	microseconds;

	gettimeofday(&now, NULL);
	seconds = now.tv_sec - start->tv_sec;
	microseconds = now.tv_usec - start->tv_usec;
	if (microseconds < 0)
	{
		seconds--;
		microseconds += 1000000;
	}
	return ((seconds * 1000) + (microseconds / 1000));
}


void*	routine(void *arg)
{
	t_philo	*philo = (t_philo *)arg;

	// Eat
	pthread_mutex_lock(philo->mutex);
	printf("%ld Philosofer %d is eating\n", get_elapsed_ms(philo->start_time), philo->index);
	usleep(philo->time_to_eat * 1000);
	pthread_mutex_unlock(philo->mutex);

	// Sleep
	//pthread_mutex_lock(philo->mutex);
	printf("%ld Philosofer %d is sleeping\n", get_elapsed_ms(philo->start_time), philo->index);
	//pthread_mutex_unlock(philo->mutex);
	usleep(philo->time_to_sleep * 1000);

	// Thinking
	//pthread_mutex_lock(philo->mutex);
	printf("%ld Philosofer %d is thinking\n", get_elapsed_ms(philo->start_time), philo->index);
	//pthread_mutex_unlock(philo->mutex);

	return (NULL);
}

void	init_philo(t_philo *philo1, t_philo *philo2, pthread_mutex_t *mutex, struct timeval *start)
{
	int	i;
	long	time_to_eat = 200;
	long	time_to_sleep = 100;
	
	i = 1;
	philo1->index = i;
	philo1->mutex = mutex;
	philo1->time_to_eat = time_to_eat; 
	philo1->time_to_sleep = time_to_sleep; 
	philo1->start_time = start;
	i++;
	philo2->index = i;
	philo2->mutex = mutex;
	philo2->time_to_eat = time_to_eat; 
	philo2->time_to_sleep = time_to_sleep; 
	philo2->start_time = start;
}

int	main(void)
{
	struct timeval	start;

	gettimeofday(&start, NULL);

	pthread_t th1;
	pthread_t th2;

	t_philo	ph1;
	t_philo ph2;

	pthread_mutex_t mutex;
	pthread_mutex_init(&mutex, NULL);

	init_philo(&ph1, &ph2, &mutex, &start);

	pthread_create(&th1, NULL, routine, &ph1);
	usleep(1000);
	pthread_create(&th2, NULL, routine, &ph2);

	pthread_join(th1, NULL);
	pthread_join(th2, NULL);
	printf("============FIM===========\n");
	pthread_mutex_destroy(&mutex);

	return (0);
}
