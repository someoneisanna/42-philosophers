/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataboada <ataboada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 18:33:49 by ataboada          #+#    #+#             */
/*   Updated: 2024/01/03 19:01:11 by ataboada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo/philosophers.h"

/*
	Here, we use a mutex to protect the global variable number. That way, we
	ensure that only one thread can access it at a time, and data races are avoided.
	When you compile this with:
		cc -Wall -Wextra -Werror -fsanitize=thread thread_3.c; ./a.out
	We can no longer see the data race warning, because the mutex ensures that
	the threads are not accessing the variable at the same time.
*/

int	number = 0; // global variable
pthread_mutex_t	mutex; // global mutex

void	*thread_function(void *)
{
	pthread_mutex_lock(&mutex);
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
