/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_list_pth.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mandriic <mandriic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 10:06:02 by mandriic          #+#    #+#             */
/*   Updated: 2022/04/15 10:06:05 by mandriic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_create_list(t_vars *vars)
{
	t_data	*data;
	t_list	*temp;

	vars->i = 1;
	pthread_mutex_init(&vars->mut_stdout, NULL);
	if (vars->num_philo != 1)
	{
		while (vars->i <= vars->num_philo)
		{
			data = ft_data(vars->i, vars);
			if (!vars->list)
				vars->list = ft_lstnew((t_data *)data);
			else if (vars->num_philo > 1)
			{
				vars->temp_tlist = ft_lstnew((t_data *)data);
				ft_lstadd_back(&vars->list, vars->temp_tlist);
			}
			vars->i++;
		}
		temp = vars->list;
		vars->last = ft_lstlast(vars->list);
		if (vars->last != vars->list)
			vars->last->next = vars->list;
	}
}

void	ft_create_pthread(t_vars *vars)
{
	t_list		*temp_list;
	pthread_t	temp;

	temp_list = vars->list;
	temp = vars->list->content->philo;
	while (1)
	{
		pthread_create(&temp, NULL, ft_philos, (void *)temp_list);
		if (temp_list == vars->last)
			break ;
		temp_list = temp_list->next;
	}
}

t_data	*ft_data(int id, t_vars *vars)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	pthread_mutex_init(&data->mut, NULL);
	pthread_mutex_init(&data->mut_last_eat, NULL);
	data->id = id;
	data->fork = id;
	data->time_to_eat = &vars->t_2_eat;
	data->time_to_die = &vars->t_2_die;
	data->time_to_sleep = &vars->t_2_slp;
	data->iters_end_p = &vars->iters_end;
	vars->iters_end = 0;
	data->eat_iter = &vars->eat_iter;
	data->c_iter = 0;
	data->death = &vars->death;
	data->num_philo = &vars->num_philo;
	data->end4watch_p = &vars->end4watch;
	vars->end4watch = 0;
	data->last_eat.tv_sec = 0;
	data->last_eat.tv_usec = 0;
	data->time_start.tv_sec = 0;
	data->mut_print = &vars->mut_stdout;
	data->my_iter_end = 0;
	data->fin = 0;
	data->started = 0;
	data->need_eat = -1;
	return (data);
}
