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

int	ft_iter(t_data *phil_data)
{
	if (*phil_data->eat_iter != -1)
			phil_data->c_iter++;
	if (phil_data->c_iter == *phil_data->eat_iter)
	{
		phil_data->fin = 1;
		*phil_data->iters_end_p = *phil_data->iters_end_p + 1;
		return (0);
	}
	return (1);
}

void	ft_phil_do(t_data *phil_data)
{
	while (!*phil_data->death)
	{
		// if (phil_data->fork > phil_data->next->fork)
			ft_mut_fokrs(phil_data, 1);
		// else
		// 	ft_mut_fokrs(phil_data, 0);
		// if (phil_data->fork > phil_data->next->fork)
			ft_mut_fokrs(phil_data, 0);
		// else
			// ft_mut_fokrs(phil_data, 1);
		ft_last_eat(phil_data);
		my_usleep(*phil_data->time_to_eat);
		// if (phil_data->fork > phil_data->next->fork)
			ft_unmut_forks(phil_data, 0);
		// else
			// ft_unmut_forks(phil_data, 0);
		ft_sleep_thin(phil_data);
		if (!ft_iter(phil_data))
			break ;
	}
}

void	*ft_philos(void *list)
{	
	t_data	*phil_data;
	

	phil_data = list;
	gettimeofday(&phil_data->time_start, NULL);
	phil_data->time_s = phil_data->time_start.tv_sec  * 1000 + phil_data->time_start.tv_usec / 1000;
	if (phil_data->id % 2 == 0)
		my_usleep(*phil_data->time_to_eat - 50);
	ft_phil_do(phil_data);
	return (0);
}

void	ft_last_eat(t_data *phil_data)
{
	pthread_mutex_lock(&phil_data->mut_prio_h);
	pthread_mutex_lock(&phil_data->mut_last_eat);
	pthread_mutex_unlock(&phil_data->mut_prio_h);
	gettimeofday(&phil_data->last_eat, NULL);
	phil_data->time_last_e = ft_2_ms(phil_data->last_eat);
	// phil_data->need_eat = 0;
	pthread_mutex_unlock(&phil_data->mut_last_eat);
	gettimeofday(&phil_data->time_now, NULL);
	phil_data->time_n = ft_2_ms(phil_data->time_now);
	pthread_mutex_lock(phil_data->mut_print);
	printf("%ld ms %d eating\n", phil_data->time_n - phil_data->time_s, phil_data->id);
	pthread_mutex_unlock(phil_data->mut_print);
}

void	ft_sleep_thin(t_data *phil_data)
{
	gettimeofday(&phil_data->time_now, NULL);
	// pthread_mutex_lock(phil_data->mut_print);
	phil_data->time_n = ft_2_ms(phil_data->time_now);
	printf("%ld ms %d sleeping\n", phil_data->time_n - phil_data->time_s, phil_data->id);
	// pthread_mutex_unlock(phil_data->mut_print);
	my_usleep(*phil_data->time_to_sleep);
	gettimeofday(&phil_data->time_now, NULL);
	phil_data->time_n = ft_2_ms(phil_data->time_now);
	pthread_mutex_lock(phil_data->mut_print);
	printf("%ld ms %d thinking\n", phil_data->time_n - phil_data->time_s, phil_data->id);
	pthread_mutex_unlock(phil_data->mut_print);
}
