/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataboada <ataboada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 10:29:02 by ataboada          #+#    #+#             */
/*   Updated: 2023/07/24 16:27:49 by ataboada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_philo
{
	int				id;
	int				fork_l;
	int				fork_r;
	int				times_eaten;
	long long		last_eaten;
	struct s_data	*data;
	pthread_t		thread;

}	t_philo;

typedef struct s_data
{
	int				n_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				times_must_eat;
	int				philo_is_full;
	int				end_flag;
	long long		start_time;
	t_philo			*philo;
	pthread_mutex_t	*mtx_fork;
	pthread_mutex_t	mtx_print;
	pthread_mutex_t	mtx_eat;
	pthread_mutex_t	mtx_end;
}	t_data;

// --------------------------------- 1_main.c ----------------------------------

void		ft_check_args(int ac, char **av);

// ---------------------------- 2_initializations.c ----------------------------

void		ft_initialize_data(t_data *data, int ac, char **av);
void		ft_initialize_mtxs(t_data *data);
void		ft_initialize_philo(t_data *data);
void		ft_initialize_thread(t_data *data);

// ---------------------------- 3_simulation_utils.c ---------------------------

int			ft_only_one_philo(t_data *data);
int			ft_should_simulation_end(t_philo *philo, int end_flag);
void		ft_eat(t_philo *philo);
void		ft_print_status(t_philo *philo, char *str);
void		ft_skip_to_time(t_philo *philo, long long timetravel_dest);

// ---------------------------- 4_surveillance.c -------------------------------

void		ft_simulation_surveillance(t_data *data);
int			ft_philo_dead_or_full(t_philo *philo);

// --------------------------------- 5_utils.c ---------------------------------

int			ft_atoi(const char *str);
void		ft_perror(char *str, t_data *data, int flag);
void		ft_free_mtxs_and_join_threads(t_data *data, int flag);
long long	ft_get_current_time(void);

#endif
