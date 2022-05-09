/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: gpirro <gpirro@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/09 15:36:28 by gpirro        #+#    #+#                 */
/*   Updated: 2022/05/09 15:55:08 by gpirro        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>
#include <stdio.h>
#include <gettime.h>
#include <mutex.h>

int	print(char *msg, t_philosopher *philo)
{
	pthread_mutex_lock(&philo->sim->stop->mutex);
	if (philo->sim->status != FINISHED)
		printf(msg, get_time(), philo->philo_id);
	pthread_mutex_unlock(&philo->sim->stop->mutex);
	return (0);
}
