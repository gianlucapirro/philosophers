#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
#include <pthread.h>

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
	pthread_mutex_t			*forks;
	struct s_philosopher	*philosophers;

	long int				philoCount;
	long int				EatEachTime;

	pthread_mutex_t			printMutex;

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
void	*routine(void *arg);
void	action(t_philospher *philo, t_status action, pthread_mutex_t right, pthread_mutex_t left);


#endif