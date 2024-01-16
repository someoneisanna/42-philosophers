/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataboada <ataboada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 18:26:26 by ataboada          #+#    #+#             */
/*   Updated: 2024/01/03 18:52:07 by ataboada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo/philosophers.h"

/*
	In this example, we create 3 threads and each one of them prints a different
	number.
	Data races can occur when multiple threads access and manipulate the same
	memory location at the same time. In this case, the global variable number
	is accessed by all threads, so we need to protect it with a mutex.
	When you compile this with:
		cc -Wall -Wextra -Werror -fsanitize=thread thread_2.c; ./a.out
	You will see a warning about data races happening in the program.
*/

int number = 0; // global variable

void	*thread_function(void *)
{
	number++;
	printf("Hello from thread %i!\n", number);
	return (NULL);
}

int	main(void)
{
	pthread_t	thread_1;
	pthread_t	thread_2;
	pthread_t	thread_3;

	pthread_create(&thread_1, NULL, &thread_function, NULL);
	pthread_create(&thread_2, NULL, &thread_function, NULL);
	pthread_create(&thread_3, NULL, &thread_function, NULL);

	pthread_join(thread_1, NULL);
	pthread_join(thread_2, NULL);
	pthread_join(thread_3, NULL);
}
