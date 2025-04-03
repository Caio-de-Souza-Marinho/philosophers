/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caide-so <caide-so@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 20:14:48 by caide-so          #+#    #+#             */
/*   Updated: 2025/04/02 22:36:13 by caide-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	safe_mutex(t_table *table, pthread_mutex_t *mutex, t_mode mode)
{
	if (mode == INIT)
		handle_mutex_errors(table, pthread_mutex_init(mutex, NULL), mode);
	else if (mode == LOCK)
		handle_mutex_errors(table, pthread_mutex_lock(mutex), mode);
	else if (mode == UNLOCK)
		handle_mutex_errors(table, pthread_mutex_unlock(mutex), mode);
	else if (mode == DESTROY)
		handle_mutex_errors(table, pthread_mutex_destroy(mutex), mode);
	else
		error_exit(table, "Mutex code error\n");
}

void	handle_mutex_errors(t_table *table, int status, t_mode mode)
{
	if (status == 0)
		return ;
	if (status == EINVAL && (mode == LOCK || mode == UNLOCK
			|| mode == DESTROY))
		error_exit(table, "Invalid mutex operation\n");
	else if (status == EINVAL && (mode == INIT))
		error_exit(table, "Invalid attr for mutex init\n");
	else if (status == EDEADLK)
		error_exit(table, "Deadlock detected\n");
	else if (status == EPERM)
		error_exit(table, "Permission denied\n");
	else if (status == ENOMEM)
		error_exit(table, "Out of memory\n");
	else if (status == EBUSY)
		error_exit(table, "Mutex is locked\n");
	else
		error_exit(table, "Unknown mutex error\n");
}
