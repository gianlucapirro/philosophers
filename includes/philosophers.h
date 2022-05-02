#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
#include <pthread.h>
#include <mutex.h>

typedef enum e_status
{
	EATING,
	SLEEPING,
	THINKING
}	t_status;

typedef enum e_proccess
{
	RUNNING,
	FINISHED
}	t_process;

typedef struct s_simulation {
	t_mutex					**forks;
	struct s_philosopher	*philosophers;

	long int				philoCount;
	long int				EatEachTime;

	long int				simStartTime;
	t_process				simStatus;

	long int				deathTime;
	long int				eatingTime;
	long int				sleepingTime;
}   	t_simulation;

typedef struct s_philosopher
{
	int				philoID;
	pthread_t		thread;

	pthread_mutex_t	eat;
	int				mealsCount;
	int				lastMeal;

	t_simulation	*simStatus;
}		t_philospher;

void    parse_arguments(t_simulation *simulation, int argc, char *argv[]);
int		simulation_init(t_simulation *simulation);
int		routine(void *arg);
int		action(t_philospher *philo, t_status action, t_mutex *right, t_mutex *left);

#endif