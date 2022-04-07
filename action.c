#include <philosophers.h>
#include <gettime.h>
#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>

void	action(t_philospher *philo, t_status action, pthread_mutex_t right, pthread_mutex_t left)
{
	if (action == EATING)
	{
		pthread_mutex_lock(&right);
		pthread_mutex_lock(&left);
		printf("\033[32m[%ld ms]	 | [philosopher %d]: Picked up a fork and is eating!\n", get_time(), philo->philoID);
		ft_sleep(philo->simStatus->eatingTime);
		pthread_mutex_unlock(&right);
		pthread_mutex_unlock(&left);
	}
	if (action == SLEEPING)
	{
		printf("\033[32m[%ld ms]	 | [philosopher %d]: Is sleeping!\n", get_time(), philo->philoID);
		ft_sleep(philo->simStatus->eatingTime);
	}
	if (action == THINKING)
	{
		printf("\033[32m[%ld ms]	 | [philosopher %d]: Is thinking!\n", get_time(), philo->philoID);
		ft_sleep(philo->simStatus->eatingTime);
	}
}

void	*routine(void *arg)
{
	t_philospher 	*philo;
	t_simulation	*stat;
	pthread_mutex_t	rightFork;
	pthread_mutex_t	leftFork;

	philo = (t_philospher *)arg;
	stat = philo->simStatus;
	rightFork = stat->forks[(philo->philoID + 1) % stat->philoCount];
	leftFork = stat->forks[(philo->philoID - 1 + stat->philoCount) % stat->philoCount];
	while (1)
	{
		action(philo, EATING, rightFork, leftFork);
		action(philo, SLEEPING, rightFork, leftFork);
		action(philo, THINKING, rightFork, leftFork);
	}
}