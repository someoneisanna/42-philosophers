/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_surveillance.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataboada <ataboada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 16:10:36 by ataboada          #+#    #+#             */
/*   Updated: 2023/07/26 10:31:57 by ataboada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

void	ft_surveillance(t_data *data);
int		ft_is_philo_dead_or_full(t_data *data, t_philo *philo);

void	ft_surveillance(t_data *data)
{
	int	i;
	int	should_end;

	should_end = FALSE;
	while (should_end == FALSE)
	{
		i = -1;
		while (++i < data->n_philo)
		{
			if (should_end == FALSE && ft_is_philo_dead_or_full(data, &data->philo[i]) == TRUE)
				should_end = TRUE;
		}
		usleep(10);
	}
}

int	ft_is_philo_dead_or_full(t_data *data, t_philo *philo)
{
	pthread_mutex_lock(&data->mtx_eat);
	if ((ft_get_current_time() - philo->last_eaten) >= data->time_to_die)
	{
		ft_print_status(philo, "died");
		ft_should_simulation_end(philo, TRUE);
		pthread_mutex_unlock(&data->mtx_eat);
		return (TRUE);
	}
	if ((data->times_must_eat > 0) && (philo->times_eaten >= data->times_must_eat))
	{
		data->n_philo_full++;
		if (data->n_philo_full == data->n_philo)
		{
			ft_should_simulation_end(philo, TRUE);
			ft_print_status(philo, "");
			pthread_mutex_unlock(&data->mtx_eat);
			return (TRUE);
		}
	}
	pthread_mutex_unlock(&data->mtx_eat);
	return (FALSE);
}
