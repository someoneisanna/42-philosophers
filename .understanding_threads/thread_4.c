/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataboada <ataboada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 19:01:53 by ataboada          #+#    #+#             */
/*   Updated: 2024/01/05 13:32:58 by ataboada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo/philosophers.h"

/*
	Now we know how to create a program with multiple threads and how to protect
	variables with a mutex.
	We will now understand how to exit a program before all threads have finished
	executing.
*/

int	number = 0; // global variable
pthread_mutex_t	mutex; // global mutex

void	*thread_function(void *)
{
	pthread_mutex_lock(&mutex);
	if (number == 1)
	{
		printf("Exiting program from thread!\n");
		exit(0);
	}
	number++;
	printf("Hello from thread %i!\n", number);
	pthread_mutex_unlock(&mutex);
	return (NULL);
}

int	main(void)
{
	pthread_t	thread_1;
	pthread_t	thread_2;
	pthread_t	thread_3;

	pthread_mutex_init(&mutex, NULL); // initialize mutex (it can't be initialized in the thread)

	pthread_create(&thread_1, NULL, &thread_function, NULL);
	pthread_create(&thread_2, NULL, &thread_function, NULL);
	pthread_create(&thread_3, NULL, &thread_function, NULL);

	pthread_join(thread_1, NULL);
	pthread_join(thread_2, NULL);
	pthread_join(thread_3, NULL);

	pthread_mutex_destroy(&mutex); // destroy mutex (works like free for malloc)
}
