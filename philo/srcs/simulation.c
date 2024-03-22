/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataboada <ataboada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 11:03:38 by ataboada          #+#    #+#             */
/*   Updated: 2024/03/22 16:38:59 by ataboada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

void	*ft_routine(void *ptr);
void	ft_eat(t_philo *p, pthread_mutex_t *fork_1, pthread_mutex_t *fork_2);
bool	ft_should_stop(t_data *d);
void	ft_simulation_monitor(t_data *d);

void	*ft_routine(void *ptr)
{
	t_philo	*p;
	t_data	*d;

	p = (t_philo *)ptr;
	d = p->data;
	while (1)
	{
		if (ft_should_stop(d) == true)
			break;
		if (p->id % 2 != 0)
			ft_eat(p, &d->fork_mtx[p->fork_r], &d->fork_mtx[p->fork_l]);
		else
			ft_eat(p, &d->fork_mtx[p->fork_l], &d->fork_mtx[p->fork_r]);
		if (ft_should_stop(d) == true)
			break;
		ft_pstatus(p, "is sleeping");
		usleep(d->time_to_sleep * 1000);
		if (ft_should_stop(d) == true)
			break;
		ft_pstatus(p, "is thinking");
	}
	return (NULL);
}

void	ft_eat(t_philo *p, pthread_mutex_t *fork_1, pthread_mutex_t *fork_2)
{
	pthread_mutex_lock(fork_1);
	pthread_mutex_lock(fork_2);
	if (ft_should_stop(p->data) == true)
	{
		pthread_mutex_unlock(fork_1);
		pthread_mutex_unlock(fork_2);
		return;
	}
	ft_pstatus(p, "has taken a fork");
	ft_pstatus(p, "has taken a fork");
	ft_pstatus(p, "is eating");
	pthread_mutex_lock(&p->data->stop_mtx);
	p->started_eating = ft_time_now();
	pthread_mutex_unlock(&p->data->stop_mtx);
	usleep(p->data->time_to_eat * 1000);
	pthread_mutex_unlock(fork_1);
	pthread_mutex_unlock(fork_2);
	pthread_mutex_lock(&p->data->stop_mtx);
	p->times_eaten++;
	if (p->times_eaten == p->data->n_meals)
		p->data->n_philo_full++;
	pthread_mutex_unlock(&p->data->stop_mtx);
}

bool	ft_should_stop(t_data *d)
{
	pthread_mutex_lock(&d->stop_mtx);
	if (d->n_philo_dead > 0 || d->n_philo_full == d->n_philo)
	{
		pthread_mutex_unlock(&d->stop_mtx);
		return (true);
	}
	pthread_mutex_unlock(&d->stop_mtx);
	return (false);
}

void	ft_simulation_monitor(t_data *d)
{
	while (1)
	{
		d->i = 0;
		pthread_mutex_lock(&d->stop_mtx);
		if (d->n_philo_full == d->n_philo)
		{
			printf("All philosophers have eaten %d times\n", d->n_meals);
			pthread_mutex_unlock(&d->stop_mtx);
			return;
		}
		pthread_mutex_unlock(&d->stop_mtx);
		while (d->i < d->n_philo)
		{
			pthread_mutex_lock(&d->stop_mtx);
			if (ft_time_now() - d->philo[d->i].started_eating > d->time_to_die)
			{
				d->n_philo_dead++;
				pthread_mutex_unlock(&d->stop_mtx);
				ft_pstatus(&d->philo[d->i], "died");
				return;
			}
			pthread_mutex_unlock(&d->stop_mtx);
			d->i++;
		}
	}
}
