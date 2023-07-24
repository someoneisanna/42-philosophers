/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_surveillance.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataboada <ataboada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 16:10:36 by ataboada          #+#    #+#             */
/*   Updated: 2023/07/24 16:31:03 by ataboada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

void	ft_simulation_surveillance(t_data *data);
int		ft_philo_dead_or_full(t_philo *philo);

void	ft_simulation_surveillance(t_data *data)
{
	int	i;
	int	continue_simulation;

	continue_simulation = 1;
	while (continue_simulation == 1)
	{
		i = -1;
		data->philo_is_full = 0;
		while (++i < data->n_philo)
		{
			if (continue_simulation == 1 && ft_philo_dead_or_full(&data->philo[i]) == 1)
				continue_simulation = 0;
		}
		usleep(10);
	}
	ft_free_mtxs_and_join_threads(data, 5);
}

int	ft_philo_dead_or_full(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->mtx_eat);
	if ((ft_get_current_time() - philo->last_eaten) >= philo->data->time_to_die)
	{
		ft_print_status(philo, "died");
		ft_should_simulation_end(philo, 1);
		pthread_mutex_unlock(&philo->data->mtx_eat);
		return (1);
	}
	else if (philo->data->times_must_eat > 0 && philo->times_eaten >= philo->data->times_must_eat)
	{
		philo->data->philo_is_full++;
		if (philo->data->philo_is_full >= philo->data->n_philo)
		{
			ft_should_simulation_end(philo, 1);
			pthread_mutex_unlock(&philo->data->mtx_eat);
			return (1);
		}
	}
	pthread_mutex_unlock(&philo->data->mtx_eat);
	return (0);
}
