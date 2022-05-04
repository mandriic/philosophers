/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mandriic <mandriic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 10:06:15 by mandriic          #+#    #+#             */
/*   Updated: 2022/04/15 10:06:18 by mandriic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_iter(t_list *phil_data)
{
	if (*phil_data->content->eat_iter != -1)
			phil_data->content->c_iter++;
	if (phil_data->content->c_iter == *phil_data->content->eat_iter)
	{
		phil_data->content->fin = 1;
		*phil_data->content->iters_end_p = *phil_data->content->iters_end_p + 1;
		return (0);
	}
	return (1);
}

void	ft_phil_do(t_list *phil_data)
{
	while (!*phil_data->content->death)
	{
		// if (phil_data->content->fork > phil_data->next->content->fork)
			ft_mut_fokrs(phil_data, 1);
		// else
		 	ft_mut_fokrs(phil_data, 0);
		// if (phil_data->content->fork > phil_data->next->content->fork)
			// ft_mut_fokrs(phil_data, 0);
		// else
			// ft_mut_fokrs(phil_data, 1);
		ft_last_eat(phil_data);
		my_usleep(*phil_data->content->time_to_eat);
		// if (phil_data->content->fork > phil_data->next->content->fork)
			// ft_unmut_forks(phil_data, 1);
		// else
			ft_unmut_forks(phil_data, 0);
		ft_sleep_thin(phil_data);
		if (!ft_iter(phil_data))
			break ;
	}
}

void	*ft_philos(void *list)
{	
	t_list	*phil_data;

	phil_data = list;
	gettimeofday(&phil_data->content->time_start, NULL);
	if (phil_data->content->id % 2 == 1)
		my_usleep(400);
	ft_phil_do(phil_data);
	return (0);
}

void	ft_last_eat(t_list *phil_data)
{
	pthread_mutex_lock(&phil_data->content->mut_last_eat);
	gettimeofday(&phil_data->content->last_eat, NULL);
	phil_data->content->need_eat = 0;
	pthread_mutex_unlock(&phil_data->content->mut_last_eat);
	pthread_mutex_lock(phil_data->content->mut_print);
	gettimeofday(&phil_data->content->time_now, NULL);
	printf("%ld ms %d eating\n", ft_2_ms(phil_data->content->time_now,
			phil_data->content->time_start), phil_data->content->id);
	pthread_mutex_unlock(phil_data->content->mut_print);
}

void	ft_sleep_thin(t_list *phil_data)
{
	gettimeofday(&phil_data->content->time_now, NULL);
	pthread_mutex_lock(phil_data->content->mut_print);
	printf("%ld ms %d sleeping\n", ft_2_ms(phil_data->content->time_now,
			phil_data->content->time_start), phil_data->content->id);
	pthread_mutex_unlock(phil_data->content->mut_print);
	my_usleep(*phil_data->content->time_to_sleep);
	gettimeofday(&phil_data->content->time_now, NULL);
	pthread_mutex_lock(phil_data->content->mut_print);
	printf("%ld ms %d thinking\n", ft_2_ms(phil_data->content->time_now,
			phil_data->content->time_start), phil_data->content->id);
	pthread_mutex_unlock(phil_data->content->mut_print);
}
