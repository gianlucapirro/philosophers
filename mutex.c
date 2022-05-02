/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mutex.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: gpirro <gpirro@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/02 12:43:55 by gpirro        #+#    #+#                 */
/*   Updated: 2022/05/02 13:46:55 by gpirro        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <mutex.h>

t_mutex *mutex_init(void)
{
	t_mutex *m;

	m = (t_mutex *)malloc(sizeof(t_mutex));
	if (m == NULL)
		return (NULL);
	m->on = 0;
	if (pthread_mutex_init(&m->mutex, NULL) != 0)
	{
		free(m);
		return (NULL);
	}
	if (pthread_mutex_init(&m->wait, NULL) != 0)
	{
		free(m);
		pthread_mutex_destroy(&m->mutex);
		return (NULL);
	}
	return (m);
}

void	mutex_free(t_mutex *m)
{
	pthread_mutex_destroy(&m->mutex);
	pthread_mutex_destroy(&m->wait);
	free(m);
}

void	mutex_lock(t_mutex *m)
{
	pthread_mutex_lock(&m->wait);
	m->on = 1;
	pthread_mutex_lock(&m->mutex);
	pthread_mutex_unlock(&m->wait);
}

// Mutex trylock to try and lock a mutex, if mutex is locked return 1 else lock the mutex and return 0 for succes.
// the m->wait is to make sure that no race condition will take place.
int	mutex_trylock(t_mutex *m)
{
	int	succes;

	pthread_mutex_lock(&m->wait);
	if (m->on == 0)
	{
		m->on = 1;
		pthread_mutex_lock(&m->mutex);
		succes = 0;
	}
	else
		succes = 1;
	pthread_mutex_unlock(&m->wait);
	return (succes);
}
	
void	mutex_unlock(t_mutex *m)
{
	pthread_mutex_lock(&m->wait);
	m->on = 0;
	pthread_mutex_unlock(&m->mutex);
	pthread_mutex_unlock(&m->wait);
}