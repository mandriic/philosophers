// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   forks.c                                            :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: mandriic <mandriic@student.42.fr>          +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2022/04/15 10:26:29 by mandriic          #+#    #+#             */
// /*   Updated: 2022/04/15 10:26:32 by mandriic         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

#include "philo.h"

void	ft_mut_fokrs(t_data *phil_data, int biger)
{

	if (biger == 1)
	{
		pthread_mutex_lock(&phil_data->mut);
		//  printf("lock1 %d\n", phil_data->id);

	}
	else
	{
		pthread_mutex_lock(phil_data->mut_n);
		// printf("lock2 %d\n", (phil_data + 1)->id);

	}
	gettimeofday(&phil_data->time_now, NULL);

		phil_data->time_n = ft_2_ms(phil_data->time_now);
	pthread_mutex_lock(phil_data->mut_print);
	printf("%ld ms %d has taken a fork \n", phil_data->time_n - phil_data->time_s, phil_data->id);
	pthread_mutex_unlock(phil_data->mut_print);
}

void	ft_unmut_forks(t_data *phil_data, int biger)
{
	if (biger == 1)
	{
		//  printf("unlock1 %d\n", (phil_data + 1)->id);
		pthread_mutex_unlock(phil_data->mut_n);
		pthread_mutex_unlock(&phil_data->mut);

	}
	else
	{
		//  printf("unlock2 %d\n",(phil_data + 1)->id);

		pthread_mutex_unlock(&phil_data->mut);
		pthread_mutex_unlock(phil_data->mut_n);
	}
}

void	my_usleep(int ms)
{
	struct timeval	time_start;
	struct timeval	time_now;
	long diff = 0;
	long time_s;
	long time_n;
	gettimeofday(&time_now, NULL);
	gettimeofday(&time_start, NULL);
	time_s = ft_2_ms(time_start);
	while ( diff < ms)
	{
		usleep(10);
		gettimeofday(&time_now, NULL);
		time_n = ft_2_ms(time_now);
		diff = time_n - time_s;


	}
}
