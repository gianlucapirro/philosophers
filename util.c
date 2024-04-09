/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gianlucapirro <gianlucapirro@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 11:50:13 by gianlucapir       #+#    #+#             */
/*   Updated: 2022/10/05 22:43:56 by gianlucapir      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_atoi(const char *str)
{
	int	neg;
	int	number;

	neg = 1;
	number = 0;
	while (*str == '\t' || *str == '\n' || *str == '\v' || \
		*str == '\f' || *str == '\r' || *str == ' ')
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			neg = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		number = number * 10 + (*str - '0');
		str++;
	}
	return (neg * number);
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*res;
	int		len;
	char	*ptr;

	len = count * size;
	if (len == 0)
		len = 1;
	ptr = malloc(len);
	res = ptr;
	if (res)
	{
		while (len > 0)
		{
			*ptr = 0;
			len--;
			ptr++;
		}
	}
	return (res);
}

int	save_atoi(char *str)
{
	int	i;
	int	p;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (-1);
		i++;
	}
	p = ft_atoi(str);
	if (i == 10)
	{
		if (str[0] > '2' || p < 0)
			return (-1);
	}
	if (i > 10)
		return (-1);
	return (p);
}

unsigned long	get_time(void)
{
	struct timeval			tv;
	unsigned long			time_ms;
	static unsigned long	starttime;

	gettimeofday(&tv, NULL);
	if (starttime == 0)
		starttime = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	time_ms = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	return (time_ms - starttime);
}

// check every 0.001 sec if simulation has finished, if so return and stop sleep
// else continue.
void	fsleep(long unsigned int ms, t_conf *conf)
{
	long unsigned int	start;
	long unsigned int	time_left;

	start = get_time();
	while ((get_time() - start) < ms)
	{
		pthread_mutex_lock(&conf->global_mutex);
		if (conf->done)
		{
			pthread_mutex_unlock(&conf->global_mutex);
			return ;
		}
		pthread_mutex_unlock(&conf->global_mutex);
		usleep(100);
	}
	time_left = get_time() - start;
	if (time_left > 0)
		usleep(time_left);
}
