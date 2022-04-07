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
	struct timeval 			time;
	struct timeval 			starttime;
	static long int			starttimeformatted;

	gettimeofday(&time, NULL);
	if (starttimeformatted == 0)
	{
		starttime = time;
		starttimeformatted = (starttime.tv_sec * 1000) + (starttime.tv_usec / 1000);
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