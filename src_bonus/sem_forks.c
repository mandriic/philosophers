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

void	ft_start_philo(t_vars *vars, t_data *tmp_list, int *i)
{
	gettimeofday(&tmp_list->last_eat, NULL);
	gettimeofday(&tmp_list->time_now, NULL);
	sem_wait(vars->sem4p);
	printf("%ld ms %d eating \n", ft_2_ms(tmp_list->time_now) -
			tmp_list->time_s, tmp_list->id);
	sem_post(vars->sem4p);
	my_usleep(*tmp_list->time_to_eat);
	if (*tmp_list->eat_iter != -1)
		*i = *i + 1;
	sem_post(vars->sem);
	sem_post(vars->sem);
	gettimeofday(&tmp_list->time_now, NULL);
	sem_wait(vars->sem4p);
	printf("%ld ms %d sleeping\n", ft_2_ms(tmp_list->time_now) -
			tmp_list->time_s, tmp_list->id);
	sem_post(vars->sem4p);
	my_usleep(*tmp_list->time_to_sleep);
	gettimeofday(&tmp_list->time_now, NULL);

	sem_wait(vars->sem4p);
	printf("%ld ms %d thinking\n", ft_2_ms(tmp_list->time_now) -
			tmp_list->time_s, tmp_list->id);
	sem_post(vars->sem4p);
}

void	ft_print_4norm(t_vars *vars, t_data *tmp_lst)
{
	gettimeofday(&tmp_lst->time_now, NULL);
	sem_wait(vars->sem4p);
	printf("%ld ms %d has taken a fork 1 \n",
		ft_2_ms(tmp_lst->time_now) - tmp_lst->time_s,
		tmp_lst->id);
	sem_post(vars->sem4p);
	
	gettimeofday(&tmp_lst->time_now, NULL);
	sem_wait(vars->sem4p);

	printf("%ld ms %d has taken a fork 2 \n",
		ft_2_ms(tmp_lst->time_now) - tmp_lst->time_s,
		tmp_lst->id);
	sem_post(vars->sem4p);
}

void	ft_take_fork(t_vars *vars, t_data *tmp_lst, int *i)
{
	while (1)
	{
		if (*tmp_lst->eat_iter == *i)
			exit(0);
		sem_wait(vars->sem);
		sem_wait(vars->sem);
		ft_print_4norm(vars, tmp_lst);
		gettimeofday(&tmp_lst->time_now, NULL);
		// if (ft_check(tmp_lst) == 1)
		// {
		// 	sem_wait(vars->sem4p);
		// 	printf("%ld ms %d DIED \n", ft_2_ms(tmp_lst->time_now) -
		// 			tmp_lst->time_s, tmp_lst->id);
		// 	kill (0, 15);
		// }
		ft_start_philo(vars, tmp_lst, i);
	}
}
void	*ft_watcher(void *philosofer)
{
	t_data *tmp_lst;

	// sleep(5);
	tmp_lst = philosofer;
	struct timeval loctime;
	while (1)
	{
		if (ft_check(tmp_lst) == 1)
			{
				// sem_wait(vars->sem4p);
				gettimeofday(&loctime, NULL);
				printf("%ld ms %d DIED \n", ft_2_ms(loctime) -
						tmp_lst->time_s, tmp_lst->id);
				kill (0, 15);
			}
		my_usleep(1);
	}
	// return ;
}
void	ft_create_forks(t_vars *vars)
{
	int		i;

	i = 0;
	while (1)
	{
		vars->list[i]->pid = fork();
		if (vars->list[i]->pid == 0)
			break ;
		i++;
		if (i == vars->num_philo)
			break ;
	}
	i--;
	// printf("%d i\n", i);
	pthread_t watcher;
	pthread_create(&watcher, NULL, ft_watcher, (t_data *) vars->list[i]);
	gettimeofday(&vars->list[i]->time_start, NULL);
	vars->list[i]->time_s = ft_2_ms(vars->list[i]->time_start);
	//  printf("my pid is %d\n", vars->list[i]->pid);
	ft_take_fork(vars, vars->list[i], &i);
	exit(0);
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
		printf("main close");
		// sleep(5);
		kill(0, 15);
	}
}
