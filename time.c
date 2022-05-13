/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   time.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: gpirro <gpirro@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/09 12:17:21 by gpirro        #+#    #+#                 */
/*   Updated: 2022/05/13 13:51:21 by gpirro        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>
#include <gettime.h>
#include <sys/time.h>
#include <unistd.h>

/**
 * @brief Get the current time in milliseconds
 * 
 * @note tv_sec is in seconds and tv_usec is in microseconds.
 * to get a precise time we need to convert both to milliseconds
 * and add them up to eachother.
 * 
 * @return long int 
 */
long int	get_time(void)
{
	struct timeval	time;
	struct timeval	starttime;
	static long int	starttimeformatted;

	gettimeofday(&time, NULL);
	if (starttimeformatted == 0)
	{
		starttime = time;
		starttimeformatted = (starttime.tv_sec * 1000) + \
		(starttime.tv_usec / 1000);
	}
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000) - starttimeformatted);
}

void	ft_sleep(long int ms)
{
	long int	time;

	time = get_time();
	while ((get_time() - time) < ms)
		usleep(100);
}

/**
 * @brief checks if the philosopher will die within 
 * the time it has to sleep. If it will die, it will
 * calculate how long it will take to die and sleeps that
 * time and then returns -1. If it will not die it will
 * sleep for sleep time.
 * 
 * @param sleep 
 * @param philo 
 * @return int 
 */
int	sleep_or_die(long int sleep, t_philosopher *philo)
{
	if (philo->last_meal + philo->sim->ttd < get_time() + sleep)
	{
		ft_sleep(philo->last_meal + philo->sim->ttd - get_time());
		return (-1);
	}
	ft_sleep(sleep);
	return (0);
}
