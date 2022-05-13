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

int	ft_create_list(t_vars *vars)
{
	t_data	*data;
	vars->list = malloc(sizeof(t_data *) * vars->num_philo + 1);
	vars->i = 0;
	pthread_mutex_init(&vars->mut_stdout, NULL);
	if (vars->num_philo != 1)
	{
		while (++vars->i <= vars->num_philo)
		{
			data = ft_data(vars->i, vars);
			if (!data)
				return (1);
			// if (!vars->list)
				vars->list[vars->i - 1] = data;
			// else if (vars->num_philo > 1)
			// {
			// 	vars->temp_tlist = ft_lstnew((t_data *)data);
			// 	ft_lstadd_back(&vars->list, vars->temp_tlist);
			// }
			// printf("%d test %d\n", vars->i, vars->list[vars->i - 1]->id);
		}
		// vars->last = ft_lstlast(vars->list);
		// if (vars->last != vars->list)
			// vars->last->next = vars->list;
	}
	vars->last = vars->list[vars->num_philo - 1];
	vars->list[vars->num_philo]= vars->list[0];
	int i = 0;
	while (i <= vars->num_philo - 1)
	{
	vars->list[i]->mut_n = &vars->list[i + 1]->mut;
	// printf("test %d\n", vars->list[i]->id);
	i++;
	}
	return (0);
}

int	ft_create_pthread(t_vars *vars)
{
	pthread_t	temp;
	vars->i = 0;
	while (++vars->i <= vars->num_philo)
	{	
		temp = vars->list[vars->i - 1]->philo;
		if (pthread_create(&temp, NULL, ft_philos, (void *)vars->list[vars->i - 1]) != 0)
			return (1);
	}

	return (0);
}

t_data	*ft_data(int id, t_vars *vars)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	pthread_mutex_init(&data->mut, NULL);
	pthread_mutex_init(&data->mut_last_eat, NULL);
	pthread_mutex_init(&data->mut_prio_l, NULL);
	pthread_mutex_init(&data->mut_prio_h, NULL);
	data->id = id;
	data->fork = id;
	data->time_to_eat = &vars->t_2_eat;
	data->time_to_die = &vars->t_2_die;
	data->time_to_sleep = &vars->t_2_slp;
	data->iters_end_p = &vars->iters_end;
	data->eat_iter = &vars->eat_iter;
	data->death = &vars->death;
	data->num_philo = &vars->num_philo;
	data->end4watch_p = &vars->end4watch;
	data->mut_print = &vars->mut_stdout;
	data->need_eat = -1;
	return (data);
}
