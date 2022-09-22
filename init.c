/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gianlucapirro <gianlucapirro@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 10:32:57 by gpirro            #+#    #+#             */
/*   Updated: 2022/09/22 18:54:42 by gianlucapir      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>
#include <utils.h>
#include <gettime.h>
#include <errors.h>
#include <stdlib.h>
#include <mutex.h>
#include <stdio.h>

/**
 * parse the input received as argv into the simulation struct.
 * 
 * @param simulation 
 * @param argc 
 * @param argv 
 */
void	parse_arguments(t_simulation *simulation, int argc, char *argv[])
{
	ft_strtol(argv[1], &simulation->philo_count);
	ft_strtol(argv[2], &simulation->ttd);
	ft_strtol(argv[3], &simulation->tte);
	ft_strtol(argv[4], &simulation->tts);
	if (argc == 6)
		ft_strtol(argv[5], &simulation->times_to_eat);
	else
		simulation->times_to_eat = -1;
}

/**
 * a new philosopher is born. It creates a 
 * philosopher and runs the routine function
 * 
 * @param philosopher 
 * @param sim 
 * @param philo_id 
 * @return PHILOSOPHER FAIL if fail or SUCCES if succeeds
 */
int	add_philosopher(t_philosopher *philosopher, t_simulation *sim, int philo_id)
{
	philosopher->philo_id = philo_id;
	philosopher->last_meal = sim->start_time;
	philosopher->meals_count = 0;
	philosopher->sim = sim;
	if (pthread_create(&(philosopher->thread), NULL, &routine, \
	(void *)philosopher) != 0)
		return (p_error("Error: pthread failed to create", PHILOSOPHER_FAIL));
	return (SUCCES);
}

/**
 * setup simulation settings
 * 
 * @param simulation 
 * @return return code if succes return succes
 */
int	simulation_init(t_simulation *sim)
{
	sim->status = RUNNING;
	sim->start_time = get_time();
	sim->forks = malloc(sizeof(t_mutex) * sim->philo_count);
	if (!sim->forks)
	{
		destroy_simulation(sim, SIM, 0);
		return (p_error("Error: fork malloc failed", MALLOC_FAILED));
	}
	sim->stop = mutex_init();
	if (sim->stop == NULL)
	{
		destroy_simulation(sim, SF, 0);
		return (p_error("Error: mutex init failed", MUTEX_FAILED));
	}
	sim->philosophers = malloc(sizeof(t_philosopher) * sim->philo_count);
	if (!sim->philosophers)
	{
		destroy_simulation(sim, SFS, 0);
		return (p_error("Error: philo add malloc fail", MALLOC_FAILED));
	}
	return (SUCCES);
}

/**
 * creates mutex for every fork and creates a thread for every philosopher, sleep
 * is there to make sure philo dont start at the same time.
 * 
 * @param sim 
 * @return errorcode on fail or SUCCES on succes 
 */
int	start_simulation(t_simulation *sim)
{
	int	i;

	i = -1;
	while (++i < sim->philo_count)
	{
		sim->forks[i] = mutex_init();
		if (sim->forks[i] == NULL)
			destroy_simulation(sim, SFSPF, i);
		if (sim->forks[i] == NULL)
			return (p_error("Error: could not init mutex", MUTEX_FAILED));
	}
	i = -1;
	while (++i < sim->philo_count)
	{
		if (add_philosopher(sim->philosophers + i, sim, i) != SUCCES)
			return (p_error("Error: philo add fialed", PHILOSOPHER_FAIL));
		ft_sleep(2);
	}
	i = -1;
	while (++i < sim->philo_count)
	{
		if (pthread_join(sim->philosophers[i].thread, NULL))
			return (p_error("Error: pthreadjoin failed", PHILOSOPHER_FAIL));
	}
	return (SUCCES);
}
