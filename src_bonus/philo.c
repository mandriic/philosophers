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

#include "philo_bonus.h"

t_data	*ft_data(int id, t_vars *vars)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	data->id = id;
	data->time_to_eat = &vars->t_2_eat;
	data->time_to_die = &vars->t_2_die;
	data->time_to_sleep = &vars->t_2_slp;
	data->eat_iter = &vars->eat_iter;
	data->c_iter = 0;
	data->num_philo = &vars->num_philo;
	vars->end4watch = 0;
	data->last_eat.tv_sec = 0;
	data->last_eat.tv_usec = 0;
	data->time_start.tv_sec = 0;
	data->fin = 0;
	return (data);
}

void	ft_create_list(t_vars *vars)
{
	t_data	*data;
	t_list	*temp;

	vars->i = 1;
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

int	pars_string(t_vars *vars, char **argv)
{
	vars->eat_iter = -1;
	while (vars->i != 5)
	{
		if (vars->i == 0)
			vars->num_philo = ft_atoi_bonus(&argv[vars->i][0]);
		else if (vars->i == 1)
			vars->t_2_die = ft_atoi_bonus(&argv[vars->i][0]);
		else if (vars->i == 2)
			vars->t_2_eat = ft_atoi_bonus(&argv[vars->i][0]);
		else if (vars->i == 3)
			vars->t_2_slp = ft_atoi_bonus(&argv[vars->i][0]);
		else if (vars->i == 4)
			vars->eat_iter = ft_atoi_bonus(&argv[vars->i][0]);
		vars->i++;
		if (!argv[vars->i])
			break ;
	}
	if (vars->num_philo == 1)
		printf("%d ms 1 die\n", vars->t_2_die);
	if (vars->num_philo <= 1 || vars->t_2_die <= 0
		|| vars->t_2_eat <= 0 || vars->t_2_slp < 0)
		return (1);
	if (vars->i == 5 && vars->eat_iter <= 0)
		return (1);
	return (0);
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
		usleep(10);
		gettimeofday(&time_now, NULL);
	}
}

int	main(int argc, char **argv)
{
	t_vars		vars;

	vars = (t_vars){};
	vars.eat_iter = -1;
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
	ft_create_list(&vars);
	ft_create_sem(&vars);
	return (0);
}
