/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataboada <ataboada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 10:38:15 by ataboada          #+#    #+#             */
/*   Updated: 2024/03/22 15:41:38 by ataboada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

int	main(int ac, char **av);
int	ft_check_args(int ac, char **av);

int	main(int ac, char **av)
{
	t_data	data;

	if (ft_check_args(ac, av) == 1)
		return (1);
	if (ft_initialize_data(ac, av, &data) == 1 ||
		ft_initialize_mutexes(&data) == 1 ||
		ft_initialize_philo(&data) == 1)
		return (1);
	if (data.n_philo == 1)
	{
		ft_pstatus(data.philo, "has taken a fork");
		usleep(data.time_to_die * 1000);
		ft_pstatus(data.philo, "died");
	}
	else
		ft_initialize_threads(&data);
	ft_free_simulation(&data);
}

int	ft_check_args(int ac, char **av)
{
	int	i;
	int	j;

	if (ac < 5 || ac > 6)
	{
		printf("Please enter 4 or 5 args: [1] Number of philosophers\n");
		printf("			  [2] Time to die\n");
		printf("			  [3] Time to eat\n");
		printf("			  [4] Time to sleep\n");
		printf("			  [5] Number of times each philo must eat\n");
		return (1);
	}
	i = 0;
	while (++i < ac)
	{
		j = -1;
		while (av[i][++j])
		{
			if (av[i][j] == '-')
				j++;
			if (av[i][j] < '0' || av[i][j] > '9')
				return (ft_perror(NULL, "Error: Args must be numbers\n", 0));
		}
	}
	return (0);
}
