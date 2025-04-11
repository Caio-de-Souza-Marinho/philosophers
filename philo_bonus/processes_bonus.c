/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caide-so <caide-so@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 08:10:16 by caide-so          #+#    #+#             */
/*   Updated: 2025/04/09 20:21:40 by caide-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

// Waits for child processes to terminate
// 1. Uses waitpid to monitor process exits
// 2. Checks exit status for failures (starvation case)
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

// Terminates all philosopher processes
// 1. Sends SIGKILL to each philosopher's PID
//
// Note: Called if a philosopher dies or an error occurs
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
