/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataboada <ataboada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 10:29:02 by ataboada          #+#    #+#             */
/*   Updated: 2024/01/16 16:16:35 by ataboada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

// -------------------------------- INCLUDES -----------------------------------

# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

// -------------------------------- DEFINES ------------------------------------

# define YES		1
# define NO			0

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
	int				n_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				n_meals;
	int				n_philo_full;
	int				n_philo_dead;
	long long		start_time;
	pthread_mutex_t	eat_mtx;
	pthread_mutex_t	print_mtx;
	pthread_mutex_t	*fork_mtx;
	t_philo			*philo;
}	t_data;

// ------------------------------- PROTOTYPES ----------------------------------

// main.c
void		ft_check_args(int ac, char **av);

// init.c
void		ft_initialize_data(int ac, char **av, t_data *d);
void		ft_initialize_mutexes(t_data *d);
void		ft_initialize_philos(t_data *d);
void		ft_initialize_threads(t_data *d);

// simulation.c
void		*ft_routine(void *ptr);
void		ft_eat(t_philo *p);
int			ft_should_simulation_end(t_philo *p);
int			ft_philo_monitor(t_data *d);
int			ft_philo_checker(t_data *d, t_philo *p);

// utils.c
int			ft_atoi(char *s);
void		ft_perror(t_data *d, char *s, int free_flag);
void		ft_pstatus(t_philo *p, char *m, int dead_or_full);
long long	ft_time_now(void);
void		ft_free_simulation(t_data *d);

#endif
