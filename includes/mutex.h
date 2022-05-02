/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mutex.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: gpirro <gpirro@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/02 12:42:09 by gpirro        #+#    #+#                 */
/*   Updated: 2022/05/02 13:28:35 by gpirro        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MUTEX_H
# define MUTEX_H

# include <pthread.h>

typedef struct	s_mutex {
	int	on;
	pthread_mutex_t	mutex;
	pthread_mutex_t	wait;
}	t_mutex;

t_mutex	*mutex_init(void);
void	mutex_free(t_mutex *m);
void	mutex_lock(t_mutex *m);
void	mutex_unlock(t_mutex *m);
int		mutex_trylock(t_mutex *m);

#endif