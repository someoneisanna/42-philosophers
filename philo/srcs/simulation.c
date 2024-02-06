/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataboada <ataboada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 11:03:38 by ataboada          #+#    #+#             */
/*   Updated: 2024/02/06 13:22:00 by ataboada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

void	*ft_routine(void *ptr);
void	ft_eat(t_philo *p, int fork_1, int fork_2);
int		ft_death_checker(t_data *d);
int		ft_philo_monitor(t_data *d);
int		ft_philo_checker(t_data *d, int i);

void	*ft_routine(void *ptr)
{
	t_philo	*p;

	p = (t_philo *)ptr;
	p->started_eating = ft_time_now();
	while (1)
	{
		if (ft_death_checker(p->data) == YES)
			break ;
		if (p->id % 2)
			ft_eat(p, p->fork_r, p->fork_l);
		else
			ft_eat(p, p->fork_l, p->fork_r);
		if (ft_death_checker(p->data) == YES)
			break ;
		ft_pstatus(p, "is sleeping", 0);
		usleep(p->data->time_to_sleep * 1000);
		if (ft_death_checker(p->data))
			break ;
		ft_pstatus(p, "is thinking", 0);
	}
	return (NULL);
}

void	ft_eat(t_philo *p, int fork_1, int fork_2)
{
	pthread_mutex_lock(&p->data->fork_mtx[fork_1]);
	ft_pstatus(p, "has taken a fork", 0);
	if (ft_death_checker(p->data) == YES)
	{
		pthread_mutex_unlock(&p->data->fork_mtx[fork_1]);
		return ;
	}
	pthread_mutex_lock(&p->data->fork_mtx[fork_2]);
	ft_pstatus(p, "has taken a fork", 0);
	if (ft_death_checker(p->data) == YES)
	{
		pthread_mutex_unlock(&p->data->fork_mtx[fork_1]);
		pthread_mutex_unlock(&p->data->fork_mtx[fork_2]);
		return ;
	}
	ft_pstatus(p, "is eating", 0);
	pthread_mutex_lock(&p->data->death_mtx);
	p->started_eating = ft_time_now();
	pthread_mutex_unlock(&p->data->death_mtx);
	usleep(p->data->time_to_eat * 1000);
	pthread_mutex_unlock(&p->data->fork_mtx[fork_1]);
	pthread_mutex_unlock(&p->data->fork_mtx[fork_2]);
	pthread_mutex_lock(&p->data->death_mtx);
	p->times_eaten++;
	pthread_mutex_unlock(&p->data->death_mtx);
}

int	ft_death_checker(t_data *d)
{
	pthread_mutex_lock(&d->death_mtx);
	if (d->n_philo_dead || d->n_philo_full >= d->n_philo || d->n_meals == 0)
	{
		pthread_mutex_unlock(&d->death_mtx);
		return (YES);
	}
	pthread_mutex_unlock(&d->death_mtx);
	return (NO);
}

int	ft_philo_monitor(t_data *d)
{
	int	i;

	while (1)
	{
		i = -1;
		while (++i < d->n_philo)
		{
			if (ft_philo_checker(d, i) == YES)
				return (YES);
		}
	}
}

int	ft_philo_checker(t_data *d, int i)
{
	pthread_mutex_lock(&d->death_mtx);
	if (ft_time_now() - d->philo[i].started_eating > d->time_to_die)
	{
		d->n_philo_dead++;
		ft_pstatus(d->philo, NULL, 1);
		pthread_mutex_unlock(&d->death_mtx);
		return (YES);
	}
	if (d->philo[i].times_eaten == d->n_meals && !d->philo[i].is_full)
	{
		d->philo[i].is_full = YES;
		d->n_philo_full++;
	}
	if (d->n_philo_full >= d->n_philo || d->n_meals == 0)
	{
		ft_pstatus(d->philo, NULL, 2);
		pthread_mutex_unlock(&d->death_mtx);
		return (YES);
	}
	pthread_mutex_unlock(&d->death_mtx);
	return (NO);
}
