#include <philosophers.h>
#include <utils.h>
#include <gettime.h>
#include <errors.h>
#include <stdlib.h>
#include <mutex.h>

/**
 * parse the input received as argv into the simulation struct.
 * 
 * @param simulation 
 * @param argc 
 * @param argv 
 */
void    parse_arguments(t_simulation *simulation, int argc, char *argv[])
{
	ft_strtol(argv[1], &simulation->philoCount);
	ft_strtol(argv[2], &simulation->deathTime);
	ft_strtol(argv[3], &simulation->eatingTime);
	ft_strtol(argv[4], &simulation->sleepingTime);
	if (argc == 6)
		ft_strtol(argv[5], &simulation->EatEachTime);
	else
		simulation->EatEachTime = -1;
}

int	add_philosopher(t_philospher *philosopher, t_simulation *sim, int philoID)
{
	philosopher->philoID = philoID;
	philosopher->lastMeal = sim->simStartTime;
	philosopher->mealsCount = sim-> EatEachTime;
	philosopher->simStatus = sim;
	if (pthread_create(&(philosopher->thread), NULL, &routine, (void*)philosopher) != 0)
		return (p_error("Error: pthread failed to create", PHILOSOPHER_FAIL));
	return (SUCCES);
}

/**
 * setup simulation settings
 * 
 * @param simulation 
 * @return return code if succes return succes
 */
int     simulation_init(t_simulation *simulation)
{
	int i;

	simulation->simStatus = RUNNING;
	simulation->simStartTime = get_time();
	simulation->forks = malloc(sizeof(t_mutex) * simulation->philoCount);
	if (!simulation->forks)
		return (p_error("Error: Malloc failure, could not find any forks in the kitchen cabinet", MALLOC_FAILED));
	simulation->philosophers = malloc(sizeof(t_philospher) * simulation->philoCount);
	if (!simulation->philosophers)
		return (p_error("Error: philosopher could not be allocated", MALLOC_FAILED));
	i = 0;
	while (i < simulation->philoCount)
		if ((simulation->forks[i++] = mutex_init()) == NULL)
			return (p_error("Error: could not init mutex", MUTEX_FAILED));
	i = -1;
	while (++i < simulation->philoCount)
		if (add_philosopher(simulation->philosophers + i, simulation, i) != SUCCES)
			return (p_error("Error: could not add philosopher", PHILOSOPHER_FAIL));
	i = -1;
	while (++i < simulation->philoCount)
		if (!pthread_join(simulation->philosophers[i].thread, NULL))
			return (p_error("Error: pthreadjoin failed", PHILOSOPHER_FAIL));
	return (SUCCES);
}