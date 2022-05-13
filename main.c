/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gianlucapirro <gianlucapirro@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 14:03:40 by gpirro            #+#    #+#             */
/*   Updated: 2022/05/12 23:51:38 by gianlucapir      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <philosophers.h>
#include <gettime.h>
#include <string.h>

int	destroy_simulation(t_simulation *sim)
{
	mutex_free(sim->stop);
	mutex_free(*sim->forks);
	free(sim->philosophers);
	return (1);
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
		return (SUCCES);
	}
	if (simulation_init(simulation))
		return (destroy_simulation(simulation));
	if (start_simulation(simulation))
		return (destroy_simulation(simulation));
	return (1);
}
