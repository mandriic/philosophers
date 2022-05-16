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
		printf("%d ms 1 die\n", vars->t_2_die);
	if (vars->num_philo <= 1 || vars->t_2_die <= 0
		|| vars->t_2_eat <= 0 || vars->t_2_slp <= 0)
		return (1);
	if (vars->i == 5 && vars->eat_iter <= 0)
		return (1);
	return (0);
}

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

void	ft_print(int var)
{
	if (var == 1)
	{
		printf("Usage: ./philo number_of_philofers time_to_die ");
		printf("time_to_eat time_to_sleep [times_to_eat]\n");
	}
	if (var == 2)
	{
		printf("Error\nphilosophers\t>=\t1\ntime_to_eat\t>\t0\n");
		printf("time_to_sleep\t>\t0\n");
		printf("time_to_die\t>\t0\n[eats_iter]\t>\t0\n");
	}
}

int	main(int argc, char **argv)
{
	t_vars		vars;
	pthread_t	watch;

	vars = (t_vars){};
	if (argc < 5 || argc > 6)
	{
		ft_print(1);
		return (0);
	}
	if (pars_string(&vars, &argv[1]) == 1)
	{
		ft_print(2);
		return (1);
	}
	if (ft_create_list(&vars))
		return (0);
	if (ft_create_pthread(&vars) == 1)
		return (0);
	if (pthread_create(&watch, NULL, ft_watcher, (void *) &vars) != 0)
		return (0);
	while (!vars.death)
		my_usleep(10);
	my_usleep(50000);
	// ft_free_all(&vars, &watch);
	return (0);
}

