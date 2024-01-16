/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_main.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataboada <ataboada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 10:38:15 by ataboada          #+#    #+#             */
/*   Updated: 2024/01/16 14:47:18 by ataboada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

int		main(int ac, char **av);
void	ft_check_args(int ac, char **av);

int	main(int ac, char **av)
{
	t_data	data;

	ft_check_args(ac, av);
	ft_initialize_data(ac, av, &data);
	ft_initialize_mutexes(&data);
	ft_initialize_philos(&data);
	if (data.n_philo == 1)
	{
		ft_pstatus(data.philo, "has taken a fork", 0);
		usleep(data.time_to_die * 1000);
		if (data.n_meals == 0)
			ft_pstatus(data.philo, NULL, YES);
		else
			ft_pstatus(data.philo, "died", 0);
	}
	else
		ft_initialize_threads(&data);
	ft_free_simulation(&data);
}

void	ft_check_args(int ac, char **av)
{
	int	i;
	int	j;

	if (ac < 5 || ac > 6)
	{
		printf("  Please enter 4 or 5 args:		\n");
		printf("	[1] Number of philosophers	\n");
		printf("	[2] Time to die				\n");
		printf("	[3] Time to eat				\n");
		printf("	[4] Time to sleep			\n");
		printf("	[5] Number of times each philosopher must eat\n");
		exit (1);
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
				ft_perror(NULL, "Error: Arguments must be numbers\n", 0);
		}
	}
}
