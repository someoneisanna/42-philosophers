/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_simulation_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataboada <ataboada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 16:53:36 by ataboada          #+#    #+#             */
/*   Updated: 2023/07/24 16:30:28 by ataboada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

int		ft_only_one_philo(t_data *data);
int		ft_should_simulation_end(t_philo *philo, int end_flag);
void	ft_eat(t_philo *philo);
void	ft_print_status(t_philo *philo, char *str);
void	ft_skip_to_time(t_philo *philo, long long timetravel_dest);

int	ft_only_one_philo(t_data *data)
{
	ft_print_status(&data->philo[0], "has taken a fork");
	ft_skip_to_time(&data->philo[0], data->time_to_die);
	ft_print_status(&data->philo[0], "died");
	ft_should_simulation_end(&data->philo[0], 1);
	return (0);
}

int	ft_should_simulation_end(t_philo *philo, int end_flag)
{
	pthread_mutex_lock(&philo->data->mtx_end);
	if (end_flag == 1 || philo->data->end_flag == 1)
	{
		if (end_flag == 1)
			philo->data->end_flag = 1;
		pthread_mutex_unlock(&philo->data->mtx_end);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->mtx_end);
	return (0);
}

void	ft_eat(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&philo->data->mtx_fork[philo->fork_l]);
		pthread_mutex_lock(&philo->data->mtx_fork[philo->fork_r]);
	}
	else
	{
		pthread_mutex_lock(&philo->data->mtx_fork[philo->fork_r]);
		pthread_mutex_lock(&philo->data->mtx_fork[philo->fork_l]);
	}
	ft_print_status(philo, "has taken a fork");
	ft_print_status(philo, "has taken a fork");
	ft_print_status(philo, "is eating");
	ft_skip_to_time(philo, philo->data->time_to_eat);
	pthread_mutex_lock(&philo->data->mtx_eat);
	philo->times_eaten++;
	philo->last_eaten = ft_get_current_time();
	pthread_mutex_unlock(&philo->data->mtx_eat);
	pthread_mutex_unlock(&philo->data->mtx_fork[philo->fork_r]);
	pthread_mutex_unlock(&philo->data->mtx_fork[philo->fork_l]);
}

void	ft_print_status(t_philo *philo, char *str)
{
	long long	current_time;

	pthread_mutex_lock(&philo->data->mtx_print);
	if (ft_should_simulation_end(philo, 0) == 0)
	{
		current_time = ft_get_current_time() - philo->data->start_time;
		printf("%lld %d %s\n", current_time, philo->id, str);
	}
	pthread_mutex_unlock(&philo->data->mtx_print);
}

void	ft_skip_to_time(t_philo *philo, long long timetravel_dest)
{
	long long	start_time;

	start_time = ft_get_current_time();
	while (ft_should_simulation_end(philo, 0) == 0 && (ft_get_current_time() - start_time) < timetravel_dest)
		usleep(100);
}
