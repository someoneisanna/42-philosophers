/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataboada <ataboada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 18:16:44 by ataboada          #+#    #+#             */
/*   Updated: 2024/01/03 18:26:01 by ataboada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo/philosophers.h"

/*
	This is a basic example on how threads are created.
		* pthread_create() creates a new thread that executes a function
		concurrently with the rest of the program.
		* pthread_join() waits for a specific thread to terminate. If you don't
		call this function, the main thread will terminate before the new thread
		can print "Hello from thread!".

*/

void	*thread_function(void *)
{
	printf("Hello from thread!\n");
	return (NULL);
}

int	main(void)
{
	pthread_t	thread_name; // this is the thread identifier

	pthread_create(&thread_name, NULL, &thread_function, NULL); // create a new thread
	pthread_join(thread_name, NULL); // wait for a thread to terminate
}
