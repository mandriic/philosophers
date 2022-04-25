/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mandriic <mandriic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 10:06:38 by mandriic          #+#    #+#             */
/*   Updated: 2022/04/15 10:06:41 by mandriic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_free_all(t_vars *vars, pthread_t *watch)
{
	vars->temp_tlist = vars->list;
	while (1)
	{
		pthread_mutex_destroy(&vars->temp_tlist->content->mut);
		pthread_mutex_destroy(&vars->temp_tlist->content->mut_last_eat);
		pthread_join(vars->temp_tlist->content->philo, NULL);
		if (vars->temp_tlist == vars->last)
			break ;
		vars->temp_tlist = vars->temp_tlist->next;
	}
	pthread_mutex_destroy(&vars->mut_stdout);
	pthread_join(*watch, NULL);
	vars->temp_tlist = vars->list;
	while (1)
	{
		free(vars->temp_tlist->content);
		if (vars->temp_tlist == vars->last)
		{
			free(vars->list);
			break ;
		}
		vars->temp_tlist = vars->temp_tlist->next;
	}
}

int	main(int argc, char **argv)
{
	t_vars		vars;
	pthread_t	watch;

	vars = (t_vars){};
	if (argc < 5 || argc > 6)
	{
		printf("Usage: ./philo number_of_philofers time_to_die ");
		printf("time_to_eat time_to_sleep [times_to_eat]\n");
		return (0);
	}
	if (pars_string(&vars, &argv[1]) == 1)
	{
		printf("Error\nphilosophers\t>=\t1\ntime_to_eat\t>\t0\n");
		printf("time_to_sleep\t>\t0\n");
		printf("time_to_die\t>\t0\n[eats_iter]\t>\t0\n");
		return (1);
	}
	if (ft_create_list(&vars))
		return (0);
	ft_create_pthread(&vars);
	pthread_create(&watch, NULL, ft_watcher, (void *) &vars);
	while (!vars.death)
		usleep(10);
	ft_free_all(&vars, &watch);
	return (0);
}
