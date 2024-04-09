/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gianlucapirro <gianlucapirro@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 09:15:25 by gianlucapir       #+#    #+#             */
/*   Updated: 2022/10/05 22:43:43 by gianlucapir      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct s_conf {
	pthread_mutex_t	global_mutex;
	pthread_mutex_t	*forks;
	pthread_t		*philos;
	int				n_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat;
	int				done;
}	t_conf;

typedef struct s_args {
	int		i;
	int		times_eaten;
	int		last_ate;
	t_conf	*conf;
}	t_args;

/* Setup.c */
int				setup(int argc, char **argv, t_args **args, t_conf *conf);
void			destroy_mutexes(t_conf *conf, int n, int rem_global_mutex);

/* philo.c */
void			*start(void *params);

/* Util.c */
unsigned long	get_time(void);
void			fsleep(long unsigned int ms, t_conf *conf);
int				save_atoi(char *str);
void			*ft_calloc(size_t count, size_t size);

#endif
