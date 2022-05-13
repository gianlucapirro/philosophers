/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosophers.h                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: gianlucapirro <gianlucapirro@student.42      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/09 14:05:05 by gpirro        #+#    #+#                 */
/*   Updated: 2022/05/13 12:25:25 by gpirro        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <mutex.h>
# include <utils.h>
# include <errors.h>
# include <stdlib.h>
# include <mutex.h>
# include <stdio.h>

typedef enum e_proccess
{
	RUNNING,
	FINISHED
}	t_process;

typedef struct s_simulation {
	t_mutex					**forks;
	t_mutex					*stop;
	struct s_philosopher	*philosophers;

	long int				philo_count;
	long int				times_to_eat;

	long int				start_time;
	t_process				status;

	long int				ttd;
	long int				tte;
	long int				tts;
}	t_simulation;

typedef struct s_philosopher
{
	int				philo_id;
	pthread_t		thread;

	pthread_mutex_t	eat;
	int				meals_count;
	long int		last_meal;

	t_simulation	*sim;
}		t_philosopher;

void	parse_arguments(t_simulation *simulation, int argc, char *argv[]);
int		simulation_init(t_simulation *simulation);
int		start_simulation(t_simulation *sim);
void	*routine(void *arg);
int		print(char *msg, t_philosopher *philo);

#endif