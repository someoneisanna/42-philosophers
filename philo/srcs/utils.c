/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataboada <ataboada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 13:25:42 by ataboada          #+#    #+#             */
/*   Updated: 2024/03/22 11:32:47 by ataboada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

int			ft_atoi(char *s);
int			ft_perror(t_data *d, char *s, int free_flag);
long long	ft_time_now(void);
void		ft_pstatus(t_philo *p, char *m);
void		ft_free_simulation(t_data *d);

int	ft_atoi(char *s)
{
	int		i;
	int		sig;
	long	res;

	i = 0;
	res = 0;
	sig = 1;
	while ((s[i] >= '\t' && s[i] <= '\r') || s[i] == ' ')
		i++;
	if (s[i] == '-' || s[i] == '+')
	{
		if (s[i] == '-')
			sig = -1;
		i++;
	}
	while (s[i] >= '0' && s[i] <= '9')
	{
		res = res * 10 + s[i] - '0';
		i++;
	}
	return (sig * res);
}

int	ft_perror(t_data *d, char *s, int free_flag)
{
	printf("%s", s);
	if (free_flag == 1)
		free(d->philo);
	if (free_flag == 2)
	{
		free(d->philo);
		free(d->fork_mtx);
	}
	return (1);
}

long long	ft_time_now(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	ft_pstatus(t_philo *p, char *m)
{
	long long	time;

	time = ft_time_now() - p->data->start_time;
	pthread_mutex_lock(&p->data->print_mtx);
	printf("%lld Philosopher %d %s\n", time, p->id, m);
	pthread_mutex_unlock(&p->data->print_mtx);
}

void	ft_free_simulation(t_data *d)
{
	int	i;

	i = -1;
	free(d->philo);
	pthread_mutex_destroy(&d->print_mtx);
	while (++i < d->n_philo)
		pthread_mutex_destroy(&d->fork_mtx[i]);
	free(d->fork_mtx);
}
