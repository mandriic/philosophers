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

void	ft_start_philo(t_vars *vars, t_list *tmp_list, int *i)
{
	gettimeofday(&tmp_list->content->last_eat, NULL);
	sem_wait(vars->sem4p);
	gettimeofday(&tmp_list->content->time_now, NULL);
	printf("%ld ms %d eating \n", ft_2_ms(tmp_list->content->time_now,
			tmp_list->content->time_start), tmp_list->content->id);
	sem_post(vars->sem4p);
	my_usleep(*tmp_list->content->time_to_eat);
	if (*tmp_list->content->eat_iter != -1)
		*i = *i + 1;
	sem_post(vars->sem);
	sem_post(vars->sem);
	sem_wait(vars->sem4p);
	gettimeofday(&tmp_list->content->time_now, NULL);
	printf("%ld ms %d sleeping\n", ft_2_ms(tmp_list->content->time_now,
			tmp_list->content->time_start), tmp_list->content->id);
	sem_post(vars->sem4p);
	my_usleep(*tmp_list->content->time_to_sleep);
	sem_wait(vars->sem4p);
	gettimeofday(&tmp_list->content->time_now, NULL);
	printf("%ld ms %d thinking\n", ft_2_ms(tmp_list->content->time_now,
			tmp_list->content->time_start), tmp_list->content->id);
	sem_post(vars->sem4p);
}

void	ft_print_4norm(t_vars *vars, t_list *tmp_lst)
{
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
}

void	ft_take_fork(t_vars *vars, t_list *tmp_lst, int *i)
{
	while (1)
	{
		if (*tmp_lst->content->eat_iter == *i)
			exit(0);
		sem_wait(vars->sem);
		sem_wait(vars->sem);
		ft_print_4norm(vars, tmp_lst);
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
	int		i;

	i = 0;
	tmp_lst = vars->list;
	while (1)
	{
		if (tmp_lst == vars->last)
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
