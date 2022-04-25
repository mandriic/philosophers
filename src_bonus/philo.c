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

void	ft_start_philo(t_vars *vars, t_list *tmp_list, int *i)
{

	gettimeofday(&tmp_list->content->last_eat, NULL);
	sem_wait(vars->sem4p);
	gettimeofday(&tmp_list->content->time_now, NULL);
	printf("%ld ms %d eating \n", ft_2_ms(tmp_list->content->time_now, tmp_list->content->time_start), tmp_list->content->id);
	sem_post(vars->sem4p);
	my_usleep(*tmp_list->content->time_to_eat);
	if (*tmp_list->content->eat_iter != -1)
		*i = *i + 1;
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

void	ft_take_fork(t_vars *vars, t_list *tmp_lst, int *i)
{
	while(1)
	{
		if (*tmp_lst->content->eat_iter == *i)
			exit(0);
		sem_wait(vars->sem);
		sem_wait(vars->sem);
		sem_wait(vars->sem4p);
		gettimeofday(&tmp_lst->content->time_now, NULL);
		printf("%ld ms %d has taken a fork 1 \n",
			ft_2_ms(tmp_lst->content->time_now, tmp_lst->content->time_start),
			tmp_lst->content->id);
		gettimeofday(&tmp_lst->content->time_now, NULL);
		printf("%ld ms %d has taken a fork 2 \n",
			ft_2_ms(tmp_lst->content->time_now, tmp_lst->content->time_start),
			tmp_lst->content->id);
		sem_post(vars->sem4p);
		gettimeofday(&tmp_lst->content->time_now, NULL);
		if (ft_check(tmp_lst) == 1)
	{
		sem_wait(vars->sem4p);
		printf("%ld ms %d DIED \n", ft_2_ms(tmp_lst->content->time_now,
			tmp_lst->content->time_start), tmp_lst->content->id);
		kill (0, 15);
	}
		ft_start_philo(vars, tmp_lst, i);
	}
}

void	ft_create_forks(t_vars *vars)
{
	t_list	*tmp_lst;
	int i = 0;

	tmp_lst = vars->list;
	while (1)	
	{
		if(tmp_lst == vars->last)
			break ;
		tmp_lst->content->pid = fork();
		if (tmp_lst->content->pid == 0)
			break ;
		tmp_lst = tmp_lst->next;
	}
	gettimeofday(&tmp_lst->content->time_start, NULL);
	ft_take_fork(vars, tmp_lst, &i);
}

void	ft_create_sem(t_vars *vars)
{
	vars->sem = sem_open ("sem", O_CREAT | O_EXCL, 0644, vars->num_philo);
	vars->sem4p = sem_open ("sem4p", O_CREAT | O_EXCL, 0644, 1);
	sem_unlink("sem");
	sem_unlink("sem4p");
	vars->main_pid = fork();
	if (vars->main_pid == 0)
		ft_create_forks(vars);
	else
	{
		waitpid(0, NULL, 0);
		sem_close(vars->sem4p);
		sem_close(vars->sem);
		kill(0, 15);
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