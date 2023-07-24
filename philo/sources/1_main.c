/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_main.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataboada <ataboada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 10:38:15 by ataboada          #+#    #+#             */
/*   Updated: 2023/07/24 16:59:20 by ataboada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

int		main(int argc, char **argv);
void	ft_check_args(int ac, char **av);

int	main(int argc, char **argv)
{
	t_data	data;

	ft_check_args(argc, argv);
	ft_initialize_data(&data, argc, argv);
	ft_initialize_philo(&data);
	ft_initialize_mtxs(&data);
	//ft_initialize_thread(&data);
	//ft_simulation_surveillance(&data);
}

void	ft_check_args(int ac, char **av)
{
	int	i;
	int	j;

	if (ac < 5 || ac > 6)
	{
		printf("Please enter 4 or 5 args:		\n");
		printf("  [1] Number of philosophers	\n");
		printf("  [2] Time to die				\n");
		printf("  [3] Time to eat				\n");
		printf("  [4] Time to sleep				\n");
		printf("  [5] Number of times each philosopher must eat\n");
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
				ft_perror("Error: Arguments must be numbers\n", NULL, 0);
		}
	}
}
