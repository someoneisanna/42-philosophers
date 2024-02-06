/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataboada <ataboada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 13:02:21 by ataboada          #+#    #+#             */
/*   Updated: 2024/02/06 13:25:10 by ataboada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

void	ft_initialize_data(int ac, char **av, t_data *d);
void	ft_initialize_mutexes(t_data *d);
void	ft_initialize_philos(t_data *d);
void	ft_initialize_threads(t_data *d);

void	ft_initialize_data(int ac, char **av, t_data *d)
{
	d->n_philo = ft_atoi(av[1]);
	d->time_to_die = ft_atoi(av[2]);
	d->time_to_eat = ft_atoi(av[3]);
	d->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		d->n_meals = ft_atoi(av[5]);
	else
		d->n_meals = -42;
	d->n_philo_dead = 0;
	d->n_philo_full = 0;
	d->print_flag = 0;
	d->start_time = ft_time_now();
	if (d->n_philo < 1)
		ft_perror(d, "Error: There must be at least 1 philosopher\n", 0);
	if (d->time_to_die < 0 || d->time_to_eat < 0 || d->time_to_sleep < 0)
		ft_perror(d, "Error: Time arguments must be positive\n", 0);
	if (d->n_meals < 0 && ac == 6)
		ft_perror(d, "Error: Number of times to eat must be positive\n", 0);
	d->philo = malloc(sizeof(t_philo) * d->n_philo);
	if (!d->philo)
		ft_perror(d, "Error: Failed to allocate memory\n", 0);
}

void	ft_initialize_mutexes(t_data *d)
{
	int	i;

	i = -1;
	if (pthread_mutex_init(&d->death_mtx, NULL))
		ft_perror(d, "Error: Failed to initialize mutex\n", 1);
	if (pthread_mutex_init(&d->print_mtx, NULL))
		ft_perror(d, "Error: Failed to initialize mutex\n", 1);
	d->fork_mtx = malloc(sizeof(pthread_mutex_t) * d->n_philo);
	if (!d->fork_mtx)
		ft_perror(d, "Error: Failed to allocate memory\n", 1);
	while (++i < d->n_philo)
	{
		if (pthread_mutex_init(&d->fork_mtx[i], NULL))
			ft_perror(d, "Error: Failed to initialize mutex\n", 2);
	}
}

void	ft_initialize_philos(t_data *d)
{
	int	i;

	i = -1;
	while (++i < d->n_philo)
	{
		d->philo[i].id = i + 1;
		d->philo[i].fork_l = i;
		d->philo[i].fork_r = (i + 1) % d->n_philo;
		d->philo[i].times_eaten = 0;
		d->philo[i].is_full = NO;
		d->philo[i].started_eating = d->start_time;
		d->philo[i].data = d;
	}
}

void	ft_initialize_threads(t_data *d)
{
	int	i;

	i = -1;
	d->start_time = ft_time_now();
	while (++i < d->n_philo)
	{
		if (pthread_create(&d->philo[i].thread, NULL, ft_routine, &d->philo[i]))
			ft_perror(d, "Error: Failed to create thread\n", 2);
		usleep(1000);
	}
	ft_philo_monitor(d);
	i = -1;
	while (++i < d->n_philo)
	{
		if (pthread_join(d->philo[i].thread, NULL))
			ft_perror(d, "Error: Failed to join thread\n", 2);
	}
}
