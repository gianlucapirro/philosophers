#ifndef PHILOSOHPERS_H
# define PHILOSOPHERS_H

typedef struct s_fork
{
	int forkNr;
}   	t_fork;


typedef struct s_forks
{
	t_fork	fork;
	t_fork	*next;
	t_fork	*prev;
}		t_forks;

typedef struct s_philosopher
{
	int philNr;
}   	t_philospher;


typedef struct s_philosophers
{
	t_philospher	phil;
	t_philospher	*next;
	t_philospher	*prev;
}		t_philosphers;


typedef struct s_data {
	int numberOfPhils;
	int timeToDie;
	int timeToEat;
	int timeToSleep;
	int notepme;
}   	t_data;

void    data_init(t_data *data, int argc, char *argv[])

#endif