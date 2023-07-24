/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_initializations.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataboada <ataboada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 15:24:38 by ataboada          #+#    #+#             */
/*   Updated: 2023/07/24 16:29:22 by ataboada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

void	ft_initialize_data(t_data *data, int ac, char **av);
void	ft_initialize_philo(t_data *data);
void	ft_initialize_mtxs(t_data *data);
void	ft_initialize_thread(t_data *data);
void	*ft_start_simulation(void *philo);

// this is where we initialize the data structure
void	ft_initialize_data(t_data *data, int ac, char **av)
{
	data->n_philo = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		data->times_must_eat = ft_atoi(av[5]);
	data->philo_is_full = 0;
	data->end_flag = 0;
	data->start_time = ft_get_current_time();
	data->philo = malloc(sizeof(t_philo) * data->n_philo);
	if (!data->philo)
		ft_perror("Error: Creation of the philo malloc failed\n", data, 1);
	if (data->n_philo < 1)
		ft_perror("Error: There must be at least one philosopher\n", data, 1);
	if (data->time_to_die < 1 || data->time_to_eat < 1 || data->time_to_sleep < 1)
		ft_perror("Error: Time arguments must be greater than 0\n", data, 1);
	if (ac == 6 && data->times_must_eat < 1)
		ft_perror("Error: If it exists, the last argument must be greater than 0\n", data, 1);
}

// this is where we initialize the philo structure
void	ft_initialize_philo(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->n_philo)
	{
		data->philo[i].id = i + 1;
		data->philo[i].fork_l = i;
		data->philo[i].fork_r = (i + 1) % data->n_philo;
		data->philo[i].times_eaten = 0;
		data->philo[i].last_eaten = data->start_time;
		data->philo[i].data = data;
	}
}

// this is where we initialize the mutexes that are in the data struct
void	ft_initialize_mtxs(t_data *data)
{
	int	i;

	i = -1;
	data->mtx_fork = malloc(sizeof(pthread_mutex_t) * data->n_philo);
	if (!data->mtx_fork)
		ft_perror("Error: Creation of the fork malloc failed\n", data, 3);
	while (++i < data->n_philo)
	{
		if (pthread_mutex_init(&data->mtx_fork[i], NULL) != 0)
			ft_perror("Error: Creation of the FORK mutex failed\n", data, 4);
	}
	if (pthread_mutex_init(&data->mtx_print, NULL))
		ft_perror("Error: Creation of the PRINT mutex failed\n", data, 4);
	if (pthread_mutex_init(&data->mtx_eat, NULL))
		ft_perror("Error: Creation of the EAT mutex failed\n", data, 4);
	if (pthread_mutex_init(&data->mtx_end, NULL))
		ft_perror("Error: Creation of the END mutex failed\n", data, 4);
}

// this is where we initialize the threads that are in the philo struct
void	ft_initialize_thread(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->n_philo)
	{
		if (pthread_create(&data->philo[i].thread, NULL, ft_start_simulation, &data->philo[i]) != 0)
			ft_perror("Error: Creation of the thread failed\n", data, 4);
	}
}

// this is the function that will be executed by the threads for each of the philosophers
void	*ft_start_simulation(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	if (philo->id % 2 == 0)
		usleep(philo->data->time_to_eat * 1000);
	while (1)
	{
		if (philo->data->n_philo == 1)
			exit (ft_only_one_philo(philo->data) && 0);
		if (ft_should_simulation_end(philo, 0) == 1)
			exit (0);
		ft_eat(philo);
		ft_print_status(philo, "is sleeping");
		ft_skip_to_time(philo, philo->data->time_to_sleep);
		ft_print_status(philo, "is thinking");
		if (philo->data->n_philo % 2 != 0)
			ft_skip_to_time(philo, philo->data->time_to_eat);
	}
}
