/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   5_utils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataboada <ataboada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 11:40:05 by ataboada          #+#    #+#             */
/*   Updated: 2023/07/24 17:15:19 by ataboada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

int			ft_atoi(const char *str);
void		ft_perror(char *str, t_data *data, int flag);
void		ft_free_mtxs_and_join_threads(t_data *data, int flag);
long long	ft_get_current_time(void);

// this is a function that will convert a string to an integer
int	ft_atoi(const char *str)
{
	int		i;
	int		sig;
	long	res;

	i = 0;
	res = 0;
	sig = 1;
	while ((str[i] >= '\t' && str[i] <= '\r') || str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sig = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + str[i] - '0';
		i++;
	}
	return (sig * res);
}

// this is a function the will print the error, free allocated memory and exit the program
void	ft_perror(char *str, t_data *data, int flag)
{
	printf("%s", str);
	if (flag == 1)
		free(data->philo);
	if (flag == 2)
		free(data->mtx_fork);
	if (flag == 3)
	{
		free(data->philo);
		free(data->mtx_fork);
	}
	if (flag == 4)
		ft_free_mtxs_and_join_threads(data, 4);
	if (flag == 5)
		ft_free_mtxs_and_join_threads(data, 5);
	exit (1);
}

// this is a function that will free the mutexes and the join the threads
void	ft_free_mtxs_and_join_threads(t_data *data, int flag)
{
	int	i;

	i = -1;
	if (flag == 5)
	{
		while (++i < data->n_philo)
			pthread_join(data->philo[i].thread, NULL);
	}
	i = -1;
	while (++i < data->n_philo)
		pthread_mutex_destroy(&data->mtx_fork[i]);
	free(data->philo);
	free(data->mtx_fork);
	pthread_mutex_destroy(&data->mtx_print);
	pthread_mutex_destroy(&data->mtx_eat);
	pthread_mutex_destroy(&data->mtx_end);
}

// this is a function that will return the current time in milliseconds
// we return the number of seconds multiplied by 1000 to get milliseconds and then the
// number of microseconds divided by 1000 to get the remaining miliseconds
long long	ft_get_current_time(void)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return ((current_time.tv_sec * 1000) + (current_time.tv_usec / 1000));
}
