/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_simulation_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataboada <ataboada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 16:53:36 by ataboada          #+#    #+#             */
/*   Updated: 2023/08/06 15:22:47 by ataboada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

int		ft_should_simulation_end(t_philo *philo, int should_end);
void	ft_print_status(t_philo *philo, char *str);
void	ft_eat(t_philo *philo);

// this is used to set the simulation to end
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

// this is used to print the status of the philosopher (the sentences that are
// printed in the subject)
// if we don't pass a string, it means that all philosophers have eaten the
// number of times they should
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
		printf("All philos have eaten %d times\n", philo->data->times_must_eat);
	pthread_mutex_unlock(&philo->data->mtx_print);
}

// this is the function where we simulate the philosopher eating
// remember: the philosopher can only eat if he has both forks
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
