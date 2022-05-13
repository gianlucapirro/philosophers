/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   action.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: gianlucapirro <gianlucapirro@student.42      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/09 10:31:38 by gpirro        #+#    #+#                 */
/*   Updated: 2022/05/13 11:34:27 by gpirro        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>
#include <gettime.h>
#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>

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

static int	eat(t_philosopher *philo)
{
	philo->last_meal = get_time();
	print("\033[32m %ld %d is eating\n", philo);
	if (philo->sim->times_to_eat != -1)
		philo->meals_count += 1;
	return (sleep_or_die(philo->sim->tte, philo));
}

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

static int	sleeping(t_philosopher *philo)
{
	if (check_philo_status(philo))
		return (1);
	print("\033[32m %ld %d is sleeping\n", philo);
	return (sleep_or_die(philo->sim->tts, philo));
}

void	*routine(void *arg)
{
	t_philosopher	*philo;
	t_simulation	*stat;
	t_mutex			*right_fork;
	t_mutex			*left_fork;

	philo = (t_philosopher *)arg;
	stat = philo->sim;
	right_fork = stat->forks[(philo->philo_id + 1) % stat->philo_count];
	left_fork = stat->forks[(philo->philo_id - 1 + stat->philo_count) \
	% stat->philo_count];
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
