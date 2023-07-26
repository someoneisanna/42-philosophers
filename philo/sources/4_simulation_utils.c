/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_simulation_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataboada <ataboada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 16:53:36 by ataboada          #+#    #+#             */
/*   Updated: 2023/07/26 10:28:21 by ataboada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

int		ft_should_simulation_end(t_philo *philo, int should_end);
void	ft_print_status(t_philo *philo, char *str);
void	ft_eat(t_philo *philo);

int	ft_should_simulation_end(t_philo *philo, int should_end)
{
	pthread_mutex_lock(&philo->data->mtx_end);
	if (should_end == TRUE || philo->data->end_flag == 1)
	{
		if (should_end == TRUE)
			philo->data->end_flag = 1;
		pthread_mutex_unlock(&philo->data->mtx_end);
		return (TRUE);
	}
	pthread_mutex_unlock(&philo->data->mtx_end);
	return (FALSE);
}

void	ft_print_status(t_philo *philo, char *str)
{
	long long	timestamp;

	pthread_mutex_lock(&philo->data->mtx_print);
	if (ft_should_simulation_end(philo, FALSE) == FALSE)
	{
		timestamp = ft_get_current_time() - philo->data->start_time;
		printf("%lld %d %s\n", timestamp, philo->id, str);
	}
	if (str == NULL)
		printf("All philosophers have eaten %d times\n", philo->data->times_must_eat);
	pthread_mutex_unlock(&philo->data->mtx_print);
}

void	ft_eat(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&philo->data->mtx_fork[philo->fork_left]);
		pthread_mutex_lock(&philo->data->mtx_fork[philo->fork_right]);
	}
	else
	{
		pthread_mutex_lock(&philo->data->mtx_fork[philo->fork_right]);
		pthread_mutex_lock(&philo->data->mtx_fork[philo->fork_left]);
	}
	ft_print_status(philo, "has taken a fork");
	ft_print_status(philo, "has taken a fork");
	ft_print_status(philo, "is eating");
	usleep(philo->data->time_to_eat * 1000);
	pthread_mutex_lock(&philo->data->mtx_eat);
	philo->times_eaten++;
	philo->last_eaten = ft_get_current_time();
	pthread_mutex_unlock(&philo->data->mtx_eat);
	pthread_mutex_unlock(&philo->data->mtx_fork[philo->fork_right]);
	pthread_mutex_unlock(&philo->data->mtx_fork[philo->fork_left]);
}
