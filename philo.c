/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gianlucapirro <gianlucapirro@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 09:12:29 by gianlucapir       #+#    #+#             */
/*   Updated: 2022/10/05 22:43:06 by gianlucapir      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//return 0 if succes else 1
static int	eating(t_args *args, pthread_mutex_t *right, pthread_mutex_t *left)
{
	t_conf	*conf;
	int		res;

	conf = args->conf;
	pthread_mutex_lock(right);
	pthread_mutex_lock(left);
	pthread_mutex_lock(&conf->global_mutex);
	res = 1;
	if (conf->done != 1)
	{
		printf("%lu %i has taken a fork\n", get_time(), args->i + 1);
		printf("%lu %i has taken a fork\n", get_time(), args->i + 1);
		printf("%lu %i is eating\n", get_time(), args->i + 1);
		res = 0;
	}
	args->last_ate = get_time();
	pthread_mutex_unlock(&conf->global_mutex);
	if (res == 0)
		fsleep(conf->time_to_eat, conf);
	pthread_mutex_unlock(right);
	pthread_mutex_unlock(left);
	pthread_mutex_lock(&conf->global_mutex);
	args->times_eaten++;
	pthread_mutex_unlock(&conf->global_mutex);
	return (res);
}

static int	sleeping(t_args *args)
{
	t_conf	*conf;
	int		res;

	conf = args->conf;
	pthread_mutex_lock(&conf->global_mutex);
	if (conf->done != 1)
	{
		printf("%lu %i is sleeping\n", get_time(), args->i + 1);
		res = 0;
	}
	else
		res = 1;
	pthread_mutex_unlock(&conf->global_mutex);
	if (res == 0)
		fsleep(conf->time_to_sleep, conf);
	return (res);
}

static int	thinking(t_args *args)
{
	t_conf	*conf;
	int		res;

	conf = args->conf;
	pthread_mutex_lock(&conf->global_mutex);
	if (conf->done != 1)
	{
		printf("%lu %i is thinking\n", get_time(), args->i + 1);
		res = 0;
	}
	else
		res = 1;
	pthread_mutex_unlock(&conf->global_mutex);
	return (res);
}

static int	philo_cycle(t_args *args, pthread_mutex_t *right, \
pthread_mutex_t *left)
{
	if (eating(args, right, left))
		return (1);
	if (sleeping(args))
		return (1);
	if (thinking(args))
		return (1);
	else
		return (0);
}

// alle oneven philos wachten zodat niet iedereen 
// tegelijk rechter fork pakt.
void	*start(void *params)
{
	t_args			*args;
	int				p;
	pthread_mutex_t	*left;
	pthread_mutex_t	*right;

	args = ((t_args *)params);
	p = args->conf->n_philos;
	left = &(args->conf->forks[args->i]);
	right = &(args->conf->forks[(args->i + 1) % p]);
	if (args->i % 2)
		usleep(15000);
	while (1)
	{
		if (philo_cycle(args, right, left) != 0)
			return (NULL);
	}
	return (NULL);
}
