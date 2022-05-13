/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: gianlucapirro <gianlucapirro@student.42      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/09 14:03:40 by gpirro        #+#    #+#                 */
/*   Updated: 2022/05/13 13:32:33 by gpirro        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <philosophers.h>
#include <gettime.h>
#include <string.h>

/**
 * @brief Destroys simulation and frees all necessary parts,
 * to show in what position the program is we use enum freeable
 * !!ALWAYS DESTROYS SIMULATION!!
 * SF -> simulation, array of forks but not forks itself
 * SFS -> simulation, array of forks, stop mutex
 * SFSPF -> simulation, array of forks, stop mutex, 
 * array of philosophers, forks until failed mutex or end
 */
int	destroy_simulation(t_simulation *sim, int s, int failed_mutex)
{
	int	i;

	i = -1;
	if (s == SFS || s == SFSPF)
		mutex_free(sim->stop);
	if (s == SFSPF)
	{
		while (++i < failed_mutex)
			mutex_free(sim->forks[i]);
		free(sim->philosophers);
	}
	if (s == SF || s == SFS || s == SFSPF)
		free(sim->forks);
	free(sim);
	return (0);
}

/**
 * Starting point of philosophers!
 * 
 * @param argc 
 * @param argv 
 * @return return status 
 */
int	main(int argc, char *argv[])
{
	t_simulation	*simulation;

	if (error(argc, argv))
		return (1);
	simulation = memset(malloc(sizeof(t_simulation)), 0, sizeof(t_simulation));
	parse_arguments(simulation, argc, argv);
	if (simulation->philo_count == 1)
	{
		printf("\033[32m %li 1 Picked up a fork\n", get_time());
		printf("\033[31m[%li 1 Died\n", \
		simulation->ttd);
		return (0);
	}
	if (simulation_init(simulation))
		return (1);
	if (start_simulation(simulation))
		return (1);
	destroy_simulation(simulation, SFSPF, simulation->philo_count);
	return (SUCCES);
}
