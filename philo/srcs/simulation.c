/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataboada <ataboada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 11:03:38 by ataboada          #+#    #+#             */
/*   Updated: 2024/02/03 22:11:20 by ataboada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

void	*ft_routine(void *ptr);
void	ft_eat(t_philo *p, int fork_1, int fork_2);
int		ft_should_simulation_end(t_philo *p);
int		ft_philo_monitor(t_data *d);
int		ft_philo_checker(t_data *d, t_philo *p);

void	*ft_routine(void *ptr)
{
	t_philo		*p;

	p = (t_philo *)ptr;
	while (1)
	{
		if (ft_should_simulation_end(p) == YES)
			break ;
		if (p->id % 2 == 0)
			ft_eat(p, p->fork_r, p->fork_l);
		else
			ft_eat(p, p->fork_l, p->fork_r);
		if (ft_should_simulation_end(p) == YES)
			break ;
		ft_pstatus(p, "is sleeping", 0);
		usleep(p->data->time_to_sleep * 1000);
		if (ft_should_simulation_end(p) == YES)
			break ;
		ft_pstatus(p, "is thinking", 0);
	}
	return (NULL);
}

void	ft_eat(t_philo *p, int fork_1, int fork_2)
{
	pthread_mutex_lock(&p->data->fork_mtx[fork_1]);
	ft_pstatus(p, "has taken a fork", 0);
	pthread_mutex_lock(&p->data->fork_mtx[fork_2]);
	ft_pstatus(p, "has taken a fork", 0);
	ft_pstatus(p, "is eating", 0);
	pthread_mutex_lock(&p->data->eat_mtx);
	p->started_eating = ft_time_now();
	pthread_mutex_unlock(&p->data->eat_mtx);
	usleep(p->data->time_to_eat * 1000);
	pthread_mutex_unlock(&p->data->fork_mtx[fork_1]);
	pthread_mutex_unlock(&p->data->fork_mtx[fork_2]);
	pthread_mutex_lock(&p->data->eat_mtx);
	p->times_eaten++;
	if (p->data->n_meals != -42 && p->times_eaten == p->data->n_meals)
		p->data->n_philo_full++;
	pthread_mutex_unlock(&p->data->eat_mtx);
}

int	ft_should_simulation_end(t_philo *p)
{
	int	should_end;

	should_end = NO;
	pthread_mutex_lock(&p->data->eat_mtx);
	if (p->data->n_philo_dead > 0)
		should_end = YES;
	if (p->data->n_philo_full >= p->data->n_philo)
		should_end = YES;
	pthread_mutex_unlock(&p->data->eat_mtx);
	return (should_end);
}

int	ft_philo_monitor(t_data *d)
{
	int	i;
	int	should_end;

	should_end = NO;
	while (should_end == NO)
	{
		i = 0;
		while (i < d->n_philo)
		{
			if (should_end == NO && ft_philo_checker(d, &d->philo[i]) == YES)
				should_end = YES;
			i++;
		}
	}
	return (0);
}

int	ft_philo_checker(t_data *d, t_philo *p)
{
	pthread_mutex_lock(&d->eat_mtx);
	if (ft_time_now() - p->started_eating >= d->time_to_die)
	{
		d->n_philo_dead++;
		ft_pstatus(p, "died", 1);
		pthread_mutex_unlock(&d->eat_mtx);
		return (YES);
	}
	if (d->n_philo_full >= d->n_philo)
	{
		ft_pstatus(p, NULL, 2);
		pthread_mutex_unlock(&d->eat_mtx);
		return (YES);
	}
	pthread_mutex_unlock(&d->eat_mtx);
	return (NO);
}
