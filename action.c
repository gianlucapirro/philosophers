#include <philosophers.h>
#include <gettime.h>
#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>

int	check_philo_status(t_philospher *philo)
{
	long int	ttd;
	long int	lastMeal;

	ttd = philo->simStatus->deathTime;
	lastMeal = philo->lastMeal;
	if ((get_time() - lastMeal) >= ttd)
	{
		printf("\033[1m\033[31m[%ld ms]	 | [philosopher %d]: Died ;d\n", get_time(), philo->philoID);
		return (1);
	}
	return (0);
}

int	action(t_philospher *philo, t_status action, t_mutex *right, t_mutex *left)
{
	if (action == EATING)
	{
		if (mutex_trylock(right) || mutex_trylock(left))
			return (check_philo_status(philo));
		printf("\033[32m[%ld ms]	 | [philosopher %d]: Picked up a fork and is eating!\n", get_time(), philo->philoID);
		ft_sleep(philo->simStatus->eatingTime);
		mutex_unlock(right);
		mutex_unlock(left);
	}
	if (action == SLEEPING)
	{
		printf("\033[32m[%ld ms]	 | [philosopher %d]: Is sleeping!\n", get_time(), philo->philoID);
		ft_sleep(philo->simStatus->sleepingTime);
	}
	if (action == THINKING)
	{
		printf("\033[32m[%ld ms]	 | [philosopher %d]: Is thinking!\n", get_time(), philo->philoID);
		ft_sleep(philo->simStatus->sleepingTime);
	}
	return (0);
}

int	routine(void *arg)
{
	t_philospher 	*philo;
	t_simulation	*stat;
	t_mutex			*rightFork;
	t_mutex			*leftFork;

	philo = (t_philospher *)arg;
	stat = philo->simStatus;
	rightFork = stat->forks[(philo->philoID + 1) % stat->philoCount];
	leftFork = stat->forks[(philo->philoID - 1 + stat->philoCount) % stat->philoCount];
	while (1)
	{
		if (action(philo, EATING, rightFork, leftFork) == 1)
			return (1);
		if (action(philo, SLEEPING, rightFork, leftFork) == 1)
			return (1);
		if (action(philo, THINKING, rightFork, leftFork) == 1)
			return (1);
	}
}