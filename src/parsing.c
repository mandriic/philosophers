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

void	ft_death(t_vars *vars, t_data *list, long t2)
{
	long	diff;

	vars->gen_time_ms = ft_2_ms(vars->cur_time);
	diff = vars->gen_time_ms - t2;
	printf("%ld ms %d died\n", diff, list->id);
	vars->death = 1;
}

// void	ft_need_eat(t_data *list, t_vars *vars)
// {
// 	long	diff;

// 	diff = ft_2_ms(list->last_eat, (list + 1)->last_eat);
// 	if (list == vars->list[0])
// 		diff = ft_2_ms(vars->last->last_eat, list->last_eat);
// 	if (diff > 0 || list->need_eat == -1)
// 		list->need_eat = 1;
// }

void	*ft_watcher(void *vars_l)
{
	// t_data			*temp_list;
	t_vars		*vars;
	vars = (t_vars *)vars_l;
	// temp_list = ((t_vars *)vars)->list;
	int i = 0;
	while (1)
	{
		// printf("vars-end%d\n", vars->iters_end);

		if (vars->list[i]->time_s)
		{
		// printf("vars-end%d\n", vars->iters_end);


			// ft_need_eat(vars->list[i], &vars);
			gettimeofday(&vars->cur_time, NULL);
	// 			pthread_mutex_lock(&vars->list[i]->mut_prio_l);
	// pthread_mutex_lock(&vars->list[i]->mut_prio_h);
	// pthread_mutex_lock(&vars->list[i]->mut_last_eat);
			if (ft_check(vars->list[i], vars) == 1)
			{

				pthread_mutex_lock(&vars->mut_stdout);
				ft_death(vars, vars->list[i],
					vars->list[i]->time_s);
				break ;
			}
			// pthread_mutex_unlock(&vars->list[i]->mut_last_eat);
			// pthread_mutex_unlock(&vars->list[i]->mut_prio_h);
			// pthread_mutex_unlock(&vars->list[i]->mut_prio_l);

		}
		// printf("vars-end%d\n", vars->iters_end);
		if (vars->iters_end == vars->num_philo)
		{
			vars->death = 1;
			break ;
		}
		// printf("death %d\n", vars->death);
		if (i == vars->num_philo - 1)
		{
			i = -1;
			// my_usleep(9);
		}

	// printf("wath\n");
		my_usleep(1);
		i++;
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
		printf("%ld ms 1 die\n", vars->t_2_die);
	if (vars->num_philo <= 1 || vars->t_2_die <= 0
		|| vars->t_2_eat <= 0 || vars->t_2_slp <= 0)
		return (1);
	if (vars->i == 5 && vars->eat_iter <= 0)
		return (1);
	return (0);
}
