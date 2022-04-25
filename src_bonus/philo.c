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
	data->my_iter_end = 0;
	data->fin = 0;
	data->started = 0;
	data->need_eat = -1;
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
int ft_create_forks(t_vars *vars)
{
	t_list	*tmp_list;
		int i = 0;

	tmp_list = vars->list;

	while (1)	
	{
		if(tmp_list == vars->last)
			break ;
		tmp_list->content->pid = fork();
		if (tmp_list->content->pid == 0)
			break ;
		tmp_list = tmp_list->next;
	}
	gettimeofday(&tmp_list->content->time_start, NULL);
	while(1)
	{

	if (*tmp_list->content->eat_iter == i)
	{
		sem_wait(vars->sem4p);
		printf("%ld ms %d end of %d eating \n", ft_2_ms(tmp_list->content->time_now, tmp_list->content->time_start),  tmp_list->content->id, i);
		sem_post(vars->sem4p);
		waitpid(-1, NULL, WNOHANG); //WNOHANG
		exit(0);
	}
		sem_wait(vars->sem);
	sem_wait(vars->sem);
	sem_wait(vars->sem4p);
		gettimeofday(&tmp_list->content->time_now, NULL);
		printf("%ld ms %d has taken a fork 1 \n", ft_2_ms(tmp_list->content->time_now, tmp_list->content->time_start), tmp_list->content->id);
		gettimeofday(&tmp_list->content->time_now, NULL);
		printf("%ld ms %d has taken a fork 2 \n", ft_2_ms(tmp_list->content->time_now, tmp_list->content->time_start), tmp_list->content->id);
	sem_post(vars->sem4p);
	gettimeofday(&tmp_list->content->time_now, NULL);
	if(ft_check(tmp_list) == 1)
	{
		sem_wait(vars->sem4p);
		printf("%ld ms %d DIED \n", ft_2_ms(tmp_list->content->time_now, tmp_list->content->time_start),  tmp_list->content->id);
		kill (0, 15);
		sem_wait(vars->sem4p);
		exit(0);
		}
	gettimeofday(&tmp_list->content->last_eat, NULL);
	my_usleep(*tmp_list->content->time_to_eat);
	if (*tmp_list->content->eat_iter != -1)
		i++;
	sem_wait(vars->sem4p);
	gettimeofday(&tmp_list->content->time_now, NULL);
	printf("%ld ms %d eating \n", ft_2_ms(tmp_list->content->time_now, tmp_list->content->time_start), tmp_list->content->id);
	sem_post(vars->sem4p);
	sem_post(vars->sem);
	sem_post(vars->sem);
	sem_wait(vars->sem4p);
	gettimeofday(&tmp_list->content->time_now, NULL);
	printf("%ld ms %d sleeping\n", ft_2_ms(tmp_list->content->time_now, tmp_list->content->time_start), tmp_list->content->id);
	sem_post(vars->sem4p);
	my_usleep(*tmp_list->content->time_to_sleep);
	sem_wait(vars->sem4p);
	gettimeofday(&tmp_list->content->time_now, NULL);
	printf("%ld ms %d thinking\n", ft_2_ms(tmp_list->content->time_now, tmp_list->content->time_start),  tmp_list->content->id);
	sem_post(vars->sem4p);
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
	vars.sem = sem_open ("sem", O_CREAT | O_EXCL, 0644, vars.num_philo);
	vars.sem4p = sem_open ("sem4p", O_CREAT | O_EXCL, 0644, 1);
	sem_unlink("sem");
	sem_unlink("sem4p");
	vars.main_pid = fork();
	if (vars.main_pid == 0)
		ft_create_forks(&vars);
    else
    { 
    	waitpid(0, NULL, 0);
		sem_close(vars.sem4p);
		sem_close(vars.sem);
		kill(0, 15);
		exit(0);
	}
	return (0);
}