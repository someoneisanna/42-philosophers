/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataboada <ataboada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 10:29:02 by ataboada          #+#    #+#             */
/*   Updated: 2024/03/22 15:43:14 by ataboada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

// -------------------------------- INCLUDES -----------------------------------

# include <string.h>
# include <stdio.h>
# include <stdbool.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

// --------------------------------- DEFINES -----------------------------------

# define YES	1
# define NO		0

// -------------------------------- STRUCTS ------------------------------------

typedef struct s_philo
{
	int				id;
	int				fork_l;
	int				fork_r;
	int				times_eaten;
	long long		started_eating;
	pthread_t		thread;
	struct s_data	*data;
}	t_philo;

typedef struct s_data
{
	int				i;
	int				n_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				n_meals;
	int				n_philo_dead;
	int				n_philo_full;
	long long		start_time;
	pthread_mutex_t stop_mtx;
	pthread_mutex_t	print_mtx;
	pthread_mutex_t	*fork_mtx;
	t_philo			*philo;
}	t_data;

// ------------------------------- PROTOTYPES ----------------------------------

// main.c
int			ft_check_args(int ac, char **av);

// init.c
int			ft_initialize_data(int ac, char **av, t_data *d);
int			ft_initialize_mutexes(t_data *d);
int			ft_initialize_philo(t_data *d);
int			ft_initialize_threads(t_data *d);

// simulation.c
void		*ft_routine(void *ptr);
void		ft_eat(t_philo *p, pthread_mutex_t *f1, pthread_mutex_t *f2);
bool		ft_should_stop(t_data *d);
void		ft_simulation_monitor(t_data *d);

// utils.c
int			ft_atoi(char *s);
int			ft_perror(t_data *d, char *s, int free_flag);
void		ft_pstatus(t_philo *p, char *m);
long long	ft_time_now(void);
void		ft_free_simulation(t_data *d);

#endif
