/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gianlucapirro <gianlucapirro@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 09:31:21 by gianlucapir       #+#    #+#             */
/*   Updated: 2022/10/05 22:43:50 by gianlucapir      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_args	*setup_args(t_conf *conf)
{
	int		i;
	t_args	*arr;

	arr = (t_args *)ft_calloc(sizeof(t_args), conf->n_philos);
	if (arr == NULL)
		return (NULL);
	i = 0;
	while (i < conf->n_philos)
	{
		arr[i].i = i;
		arr[i].conf = conf;
		i++;
	}
	return (arr);
}

void	destroy_mutexes(t_conf *conf, int n, int rem_global_mutex)
{
	pthread_mutex_t	fork;
	int				i;

	free(conf->philos);
	i = 0;
	while (i < n)
	{
		fork = conf->forks[i];
		pthread_mutex_destroy(&fork);
		i++;
	}
	free(conf->forks);
	if (rem_global_mutex)
	{
		fork = conf->global_mutex;
		pthread_mutex_destroy(&fork);
	}
}

int	get_mutexes(t_conf *conf)
{
	int	i;

	conf->philos = (pthread_t *)ft_calloc(conf->n_philos, sizeof(pthread_t));
	if (conf->philos == NULL)
		return (1);
	conf->forks = \
	(pthread_mutex_t *)ft_calloc(conf->n_philos, sizeof(pthread_mutex_t));
	if (conf->forks == NULL)
		free(conf->philos);
	if (conf->forks == NULL)
		return (1);
	i = -1;
	while (++i < conf->n_philos)
	{
		if (pthread_mutex_init(&(conf->forks[i]), NULL) == 0)
			continue ;
		destroy_mutexes(conf, i, 0);
		return (1);
	}
	if (pthread_mutex_init(&(conf->global_mutex), NULL) != 0)
	{
		destroy_mutexes(conf, i, 0);
		return (1);
	}
	return (0);
}

int	parse_args(int argc, char **argv, t_conf *conf)
{
	if (argc != 5 && argc != 6)
		printf("Error parsing arguments\n");
	if (argc != 5 && argc != 6)
		return (1);
	conf->n_philos = save_atoi(argv[1]);
	conf->time_to_die = save_atoi(argv[2]);
	conf->time_to_eat = save_atoi(argv[3]);
	conf->time_to_sleep = save_atoi(argv[4]);
	if (conf->n_philos < 0 || conf->time_to_die < 0 || \
		conf->time_to_eat < 0 || conf->time_to_sleep < 0)
	{
		printf("Error parsing arguments\n");
		return (1);
	}
	conf->must_eat = -1;
	conf->done = 0;
	if (argc == 6)
	{
		conf->must_eat = save_atoi(argv[5]);
		if (conf->must_eat < 0)
			printf("Error parsing arguments\n");
		if (conf->must_eat < 0)
			return (1);
	}
	return (0);
}

// Does the setup of the program.
// It loads the parameters from the argv.
// It allocates the memory for the args.
// It allocates the memory for the threads.
// It allocates the memory for the mutexes.
// It creates the mutexes.
// It destroys the mutexes and frees all allocation if something goes wrong.
int	setup(int argc, char **argv, t_args **args, t_conf *conf)
{
	if (parse_args(argc, argv, conf) == 1 || conf->must_eat == 0)
		return (1);
	if (conf->n_philos == 1)
		printf("0 1 has taken a fork\n%i 1 died\n", conf->time_to_die + 1);
	if (conf->n_philos <= 1)
		return (1);
	if (get_mutexes(conf))
		return (1);
	*args = setup_args(conf);
	if (*args == NULL)
	{
		destroy_mutexes(conf, conf->n_philos, 1);
		return (1);
	}
	return (0);
}
