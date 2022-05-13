/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   action.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: gianlucapirro <gianlucapirro@student.42      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/09 10:31:38 by gpirro        #+#    #+#                 */
/*   Updated: 2022/05/13 13:51:52 by gpirro        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>
#include <gettime.h>
#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * @brief checks if philosopher is still alive
 * if philosopher has died it prints a death message
 * and returns 1 else return 0
 * 
 * @param philo 
 * @return int 
 */
int	check_philo_status(t_philosopher *philo)
{
	long int	ttd;
	long int	last_meal;

	pthread_mutex_lock(&philo->sim->stop->mutex);
	if (philo->sim->status == FINISHED)
	{
		pthread_mutex_unlock(&philo->sim->stop->mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->sim->stop->mutex);
	ttd = philo->sim->ttd;
	last_meal = philo->last_meal;
	if ((get_time() - last_meal) >= ttd)
	{
		pthread_mutex_lock(&philo->sim->stop->mutex);
		if (philo->sim->status != FINISHED)
		{
			printf("\033[31m %ld %d died\n", get_time(), philo->philo_id);
			philo->sim->status = FINISHED;
		}
		pthread_mutex_unlock(&philo->sim->stop->mutex);
		return (1);
	}
	return (0);
}

/**
 * @brief prints that philosopher is eating and 
 * updates the last time the philosopher has eaten
 * and the amount of meals the philosopher has eaten.
 * 
 * @param philo 
 * @return int 
 */
static int	eat(t_philosopher *philo)
{
	philo->last_meal = get_time();
	print("\033[32m %ld %d is eating\n", philo);
	if (philo->sim->times_to_eat != -1)
		philo->meals_count += 1;
	return (sleep_or_die(philo->sim->tte, philo));
}

/**
 * @brief tries to pick up two forks to start eating
 * 
 * @param philo 
 * @param right 
 * @param left 
 * @return int 
 */
static int	eating(t_philosopher *philo, t_mutex *right, t_mutex *left)
{
	while (check_philo_status(philo) == 0)
	{
		if (mutex_trylock(left))
		{
			print("\033[32m %ld %d has taken a fork\n", philo);
			while (check_philo_status(philo) == 0)
			{
				if (mutex_trylock(right))
				{
					print("\033[32m %ld %d has taken a fork\n", philo);
					if (eat(philo))
						return (1);
					mutex_unlock(right);
					mutex_unlock(left);
					return (0);
				}
			}
			return (1);
		}
	}
	return (1);
}

/**
 * @brief will let the philosopher sleep if it is still alive
 * 
 * @param philo 
 * @return int 
 */
static int	sleeping(t_philosopher *philo)
{
	if (check_philo_status(philo))
		return (1);
	print("\033[32m %ld %d is sleeping\n", philo);
	return (sleep_or_die(philo->sim->tts, philo));
}

/**
 * @brief routine that every philosopher (thread) follows
 * every philosopher must eat sleep and think
 * 
 * 
 * @param arg 
 * @return void* 
 */
void	*routine(void *arg)
{
	t_philosopher	*philo;
	t_simulation	*sim;
	t_mutex			*right_fork;
	t_mutex			*left_fork;

	philo = (t_philosopher *)arg;
	sim = philo->sim;
	right_fork = sim->forks[(philo->philo_id + 1) % sim->philo_count];
	left_fork = sim->forks[(philo->philo_id - 1 + sim->philo_count) \
	% sim->philo_count];
	while (1 && (philo->sim->times_to_eat == -1 || philo->meals_count < philo->sim->times_to_eat))
	{
		if (eating(philo, right_fork, left_fork) == 1 \
		&& check_philo_status(philo))
			break ;
		if (sleeping(philo) == 1 && check_philo_status(philo))
			break ;
		print("\033[32m %ld %d is thinking\n", philo);
	}
	return (NULL);
}
