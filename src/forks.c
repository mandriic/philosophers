/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mandriic <mandriic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 10:26:29 by mandriic          #+#    #+#             */
/*   Updated: 2022/04/15 10:26:32 by mandriic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_mut_fokrs(t_list *phil_data, int biger)
{
	long test;

	if (biger == 1)
	{
		pthread_mutex_lock(&phil_data->content->mut);
		(void) phil_data->content->fork;
	}
	else
	{
		pthread_mutex_lock(&phil_data->next->content->mut);
		(void) phil_data->next->content->fork;
	}
	gettimeofday(&phil_data->content->time_now, NULL);

	pthread_mutex_lock(phil_data->content->mut_print);
		test = ft_2_ms(phil_data->content->time_now,
			phil_data->content->time_start);
	printf("%ld ms %d has taken a fork \n", test, phil_data->content->id);
	pthread_mutex_unlock(phil_data->content->mut_print);
}

void	ft_unmut_forks(t_list *phil_data, int biger)
{
	if (biger == 1)
	{
		pthread_mutex_unlock(&phil_data->next->content->mut);
		pthread_mutex_unlock(&phil_data->content->mut);

	}
	else
	{
		pthread_mutex_unlock(&phil_data->content->mut);
		pthread_mutex_unlock(&phil_data->next->content->mut);
	}
}

void	my_usleep(int ms)
{
	struct timeval	time_start;
	struct timeval	time_now;

	gettimeofday(&time_now, NULL);
	gettimeofday(&time_start, NULL);
	while ((time_now.tv_sec - time_start.tv_sec) * 1000
		+ (time_now.tv_usec - time_start.tv_usec) / 1000 < ms)
	{
		gettimeofday(&time_now, NULL);
		usleep(10);
	}
}
