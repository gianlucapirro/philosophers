/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gianlucapirro <gianlucapirro@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 12:43:55 by gpirro            #+#    #+#             */
/*   Updated: 2022/09/22 18:11:29 by gianlucapir      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <mutex.h>

t_mutex	*mutex_init(void)
{
	t_mutex	*m;

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

/**
 * @brief destroys mutex 
 * 
 * @param m 
 */
void	mutex_free(t_mutex *m)
{
	pthread_mutex_destroy(&m->mutex);
	pthread_mutex_destroy(&m->wait);
	free(m);
}

/**
 * Mutex trylock to try and lock a mutex, if mutex is 
 * locked return 1 else lock the mutex and return 0 for succes.
 * the m->wait is to make sure that no race condition will take place.
 * 
 * @param m 
 * @return int 
 */
int	mutex_trylock(t_mutex *m)
{
	int	succes;

	pthread_mutex_lock(&m->wait);
	if (m->on == 0)
	{
		m->on = 1;
		pthread_mutex_lock(&m->mutex);
		succes = 1;
	}
	else
		succes = 0;
	pthread_mutex_unlock(&m->wait);
	return (succes);
}

void	mutex_lock(t_mutex *m)
{
	while (mutex_trylock(m))
	{
	}
}

void	mutex_unlock(t_mutex *m)
{
	pthread_mutex_lock(&m->wait);
	m->on = 0;
	pthread_mutex_unlock(&m->mutex);
	pthread_mutex_unlock(&m->wait);
}
