#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <philosophers.h>
#include <errors.h>
#include <string.h>

/**
 * Starting point of philosophers!
 * 
 * @param argc 
 * @param argv 
 * @return return status 
 */
int main(int argc, char *argv[])
{
	t_simulation	*simulation;
	// t_philospher	phil;
	int				status;

	if ((status = error(argc, argv)))
		return (status);
	simulation = memset(malloc(sizeof(t_simulation)), 0, sizeof(t_simulation));
	parse_arguments(simulation, argc, argv);
	if (simulation->philoCount == 1)
	{
		printf("\033[32m[0 ms]	 | [philosopher 1]: Picked up a fork!\n");
		printf("\033[31m[%ld ms] | [philosopher 1]: Died...\n", simulation->deathTime);
		return (SUCCES);
	}
	if ((status = simulation_init(simulation)))
		return (status);
	return (0);
}