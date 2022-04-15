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
	if (biger == 1)
	{
		pthread_mutex_lock(&phil_data->content->mut);
		(void) phil_data->content->fork;
		gettimeofday(&phil_data->content->time_now, NULL);
	}
	else
	{
		pthread_mutex_lock(&phil_data->next->content->mut);
		(void) phil_data->next->content->fork;
		gettimeofday(&phil_data->content->time_now, NULL);
	}
	pthread_mutex_lock(phil_data->content->mut_print);
	printf("%ld ms %d has taken a fork \n", ft_2_ms(phil_data->content->time_now,
			phil_data->content->time_start), phil_data->content->id);
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
