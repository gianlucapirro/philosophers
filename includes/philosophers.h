#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

typedef enum e_status
{
	EATING,
	SLEEPING,
	THINKING
}	t_status;

typedef struct s_simulation {
	pthread_mutex_t	*forks;
	t_philospher 	*philosophers;

	
}   	t_simulation;

typedef struct s_philosopher
{
	int				id;
	pthread_t		thread;

	pthread_mutex_t	eat;
	int				meals;
	int				last_meal;

	t_simulation	*status;	
}		t_philospher;

void    data_init(t_data *data, int argc, char *argv[]);

#endif