/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_surveillance.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataboada <ataboada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 16:10:36 by ataboada          #+#    #+#             */
/*   Updated: 2023/08/06 15:30:06 by ataboada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

void	ft_surveillance(t_data *data);
int		ft_dead_or_full(t_data *data, t_philo *philo);

// this function is used to check if the simulation has ended or not
// note: the simulation ends once a philo dies or all philos have eaten
void	ft_surveillance(t_data *d)
{
	int	i;
	int	should_end;

	should_end = FALSE;
	while (should_end == FALSE)
	{
		i = -1;
		while (++i < d->n_philo)
		{
			if (should_end == FALSE && ft_dead_or_full(d, &d->philo[i]) == TRUE)
				should_end = TRUE;
		}
		usleep(10);
	}
}

// here we check if any philo has died and count how many philos have eaten
// we also check if the number of philos that have eaten is equal to the number
// of philos, which would mean that we should end the simulation
int	ft_dead_or_full(t_data *d, t_philo *p)
{
	pthread_mutex_lock(&d->mtx_eat);
	if ((ft_get_current_time() - p->last_eaten) >= d->time_to_die)
	{
		ft_print_status(p, "died");
		ft_should_simulation_end(p, TRUE);
		pthread_mutex_unlock(&d->mtx_eat);
		return (TRUE);
	}
	if ((d->times_must_eat > 0) && (p->times_eaten >= d->times_must_eat))
	{
		d->n_philo_full++;
		if (d->n_philo_full == d->n_philo)
		{
			ft_should_simulation_end(p, TRUE);
			ft_print_status(p, "");
			pthread_mutex_unlock(&d->mtx_eat);
			return (TRUE);
		}
	}
	pthread_mutex_unlock(&d->mtx_eat);
	return (FALSE);
}
