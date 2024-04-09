/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gianlucapirro <gianlucapirro@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 09:12:29 by gianlucapir       #+#    #+#             */
/*   Updated: 2022/10/05 22:43:20 by gianlucapir      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_philo_status(t_args *arg, int *done_philos)
{
	int	res;

	res = 0;
	pthread_mutex_lock(&arg->conf->global_mutex);
	if (arg->conf->must_eat != -1 && arg->times_eaten >= arg->conf->must_eat)
		(*done_philos)++;
	if (get_time() - arg->last_ate > (unsigned long)(arg->conf->time_to_die))
	{
		printf("%lu %i died\n", get_time(), arg->i + 1);
		arg->conf->done = 1;
		res = 1;
	}
	pthread_mutex_unlock(&arg->conf->global_mutex);
	return (res);
}

//done_philo indicates the amount of philos
// who have atleast eaten must_eat times
static void	manager(t_conf *conf, t_args *args)
{
	int	i;
	int	done_philos;

	while (1)
	{
		i = -1;
		done_philos = 0;
		while (++i < conf->n_philos)
		{
			if (check_philo_status(args + i, &done_philos))
				return ;
		}
		pthread_mutex_lock(&conf->global_mutex);
		if (done_philos == conf->n_philos)
			conf->done = 1;
		pthread_mutex_unlock(&conf->global_mutex);
		if (done_philos == conf->n_philos)
			return ;
	}
}

int	main(int argc, char **argv)
{
	int		i;
	t_conf	conf;
	t_args	*args;

	if (setup(argc, argv, &args, &conf) != 0)
		return (0);
	i = -1;
	while (++i < conf.n_philos)
	{
		if (pthread_create(conf.philos + i, NULL, &start, (void *)&(args[i])))
		{
			destroy_mutexes(&conf, conf.n_philos, 1);
			free(args);
			return (1);
		}
	}
	manager(&conf, args);
	i = -1;
	while (++i < conf.n_philos)
		pthread_join(conf.philos[i], NULL);
	destroy_mutexes(&conf, conf.n_philos, 1);
	free(args);
	return (0);
}
