/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mandriic <mandriic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 10:04:13 by mandriic          #+#    #+#             */
/*   Updated: 2022/04/15 10:04:18 by mandriic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_death(t_vars *vars, t_list *list, struct timeval t2)
{
	long	diff;

	diff = ft_2_ms(list->content->cur_time, t2);
	printf("%ld ms %d died\n", diff, list->content->id);
	vars->death = 1;
}

void	ft_need_eat(t_list *list, t_vars *vars)
{
	long	diff;

	diff = ft_2_ms(list->content->last_eat, list->next->content->last_eat);
	if (list == vars->list)
		diff = ft_2_ms(vars->last->content->last_eat, list->content->last_eat);
	pthread_mutex_lock(&((t_vars *)vars)->mut_ndet);
	if (diff > 0 || list->content->need_eat == -1)
		list->content->need_eat = 1;
	pthread_mutex_lock(&((t_vars *)vars)->mut_ndet);
}

void	*ft_watcher(void *vars)
{
	t_list			*temp_list;

	pthread_mutex_init(&((t_vars *)vars)->mut_ndet, NULL);
	temp_list = ((t_vars *)vars)->list;
	gettimeofday(&((t_vars *)vars)->time_start, NULL);
	while (*temp_list->content->iters_end_p != ((t_vars *)vars)->num_philo)
	{
		if (temp_list->content->time_start.tv_sec
			|| temp_list->content->last_eat.tv_sec)
		{
			pthread_mutex_lock(&((t_vars *)vars)->mut_ndet);
			ft_need_eat(temp_list, ((t_vars *)vars));
			pthread_mutex_unlock(&((t_vars *)vars)->mut_ndet);
			pthread_mutex_lock(&temp_list->content->mut_last_eat);
			gettimeofday(&temp_list->content->cur_time, NULL);
			if (ft_check(temp_list) == 1)
			{
				ft_death(((t_vars *)vars), temp_list,
					((t_vars *)vars)->time_start);
				break ;
			}
			pthread_mutex_unlock(&temp_list->content->mut_last_eat);
		}
		if (*temp_list->content->iters_end_p == ((t_vars *)vars)->num_philo)
			*temp_list->content->death = 1;
		temp_list = temp_list->next;
	}
	return (0);
}

int	pars_string(t_vars *vars, char **argv)
{
	vars->eat_iter = -1;
	while (vars->i != 5)
	{
		if (vars->i == 0)
			vars->num_philo = ft_atoi(&argv[vars->i][0]);
		else if (vars->i == 1)
			vars->t_2_die = ft_atoi(&argv[vars->i][0]);
		else if (vars->i == 2)
			vars->t_2_eat = ft_atoi(&argv[vars->i][0]);
		else if (vars->i == 3)
			vars->t_2_slp = ft_atoi(&argv[vars->i][0]);
		else if (vars->i == 4)
			vars->eat_iter = ft_atoi(&argv[vars->i][0]);
		vars->i++;
		if (!argv[vars->i])
			break ;
	}
	if (vars->num_philo == 1)
		printf("%d ms ONLY ONE FORK EXISTS 1 die\n", vars->t_2_die);
	if (vars->num_philo <= 1 || vars->t_2_die <= 0
		|| vars->t_2_eat <= 0 || vars->t_2_slp <= 0)
		return (1);
	if (vars->i == 5 && vars->eat_iter <= 0)
		return (1);
	return (0);
}
