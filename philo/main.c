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
	int	time_to_eat;
	int	time_to_sleep;
}	t_philo;

void*	routine(void *arg)
{
	t_philo	*philo = (t_philo *)arg;

	pthread_mutex_lock(philo->mutex);
	printf("Philosofer %d is eating\n", philo->index);
	printf("Philosofer %d is sleeping\n", philo->index);
	printf("Philosofer %d is thinking\n", philo->index);
	pthread_mutex_unlock(philo->mutex);
	return (NULL);
}

void	init_philo(t_philo *philo1, t_philo *philo2, pthread_mutex_t *mutex)
{
	int	i;
	
	i = 1;
	philo1->index = i;
	philo1->mutex = mutex;
	i++;
	philo2->index = i;
	philo2->mutex = mutex;
}

int	main(void)
{
	pthread_t tred1;
	pthread_t tred2;

	t_philo	philo1;
	t_philo philo2;

	pthread_mutex_t mutex;
	pthread_mutex_init(&mutex, NULL);

	init_philo(&philo1, &philo2, &mutex);

	pthread_create(&tred1, NULL, routine, &philo1);
	pthread_create(&tred2, NULL, routine, &philo2);

	pthread_join(tred1, NULL);
	pthread_join(tred2, NULL);
	printf("============FIM===========\n");
	pthread_mutex_destroy(&mutex);
	return (0);
}
