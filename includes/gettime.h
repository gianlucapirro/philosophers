/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   gettime.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: gpirro <gpirro@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/09 10:55:38 by gpirro        #+#    #+#                 */
/*   Updated: 2022/05/09 12:20:31 by gpirro        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef GETTIME_H
# define GETTIME_H

# include <sys/time.h>
# include <philosophers.h>

long int	get_time(void);
void		ft_sleep(long int ms);
int			sleep_or_die(long int sleep, t_philosopher *philo);

#endif
