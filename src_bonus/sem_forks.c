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
	pthread_mutex_lock(&tmp_list->mut_leat);
	gettimeofday(&tmp_list->last_eat, NULL);
	pthread_mutex_unlock(&tmp_list->mut_leat);

	gettimeofday(&tmp_list->time_now, NULL);
	tmp_list->time_n = ft_2_ms(tmp_list->time_now);
	sem_wait(vars->sem4p);
	pthread_mutex_lock(&tmp_list->mut_print);
	printf("%ld ms %d eating \n", tmp_list->time_n -
			tmp_list->time_s, tmp_list->id);
	pthread_mutex_unlock(&tmp_list->mut_print);

	sem_post(vars->sem4p);
	my_usleep(*tmp_list->time_to_eat);
	if (*tmp_list->eat_iter != -1)
		*i = *i + 1;
	sem_post(vars->sem);
	sem_post(vars->sem);
	gettimeofday(&tmp_list->time_now, NULL);
	tmp_list->time_n = ft_2_ms(tmp_list->time_now);
	sem_wait(vars->sem4p);
	pthread_mutex_lock(&tmp_list->mut_print);
	printf("%ld ms %d sleeping\n", tmp_list->time_n -
			tmp_list->time_s, tmp_list->id);
	pthread_mutex_unlock(&tmp_list->mut_print);
	
	sem_post(vars->sem4p);
	my_usleep(*tmp_list->time_to_sleep);
	gettimeofday(&tmp_list->time_now, NULL);
	tmp_list->time_n = ft_2_ms(tmp_list->time_now);
	sem_wait(vars->sem4p);
	pthread_mutex_lock(&tmp_list->mut_print);

	printf("%ld ms %d thinking\n", tmp_list->time_n -
			tmp_list->time_s, tmp_list->id);
	pthread_mutex_unlock(&tmp_list->mut_print);
	
	sem_post(vars->sem4p);
}

void	ft_print_4norm(t_vars *vars, t_data *tmp_list)
{
	gettimeofday(&tmp_list->time_now, NULL);
	tmp_list->time_n = ft_2_ms(tmp_list->time_now);
	sem_wait(vars->sem4p);
	pthread_mutex_lock(&tmp_list->mut_print);
	printf("%ld ms %d has taken a fork 1 \n",
		tmp_list->time_n - tmp_list->time_s,
		tmp_list->id);
	pthread_mutex_unlock(&tmp_list->mut_print);
	sem_post(vars->sem4p);
	
	gettimeofday(&tmp_list->time_now, NULL);
	tmp_list->time_n = ft_2_ms(tmp_list->time_now);
	sem_wait(vars->sem4p);
	pthread_mutex_lock(&tmp_list->mut_print);

	printf("%ld ms %d has taken a fork 2 \n",
		tmp_list->time_n  - tmp_list->time_s,
		tmp_list->id);
	pthread_mutex_unlock(&tmp_list->mut_print);

	sem_post(vars->sem4p);
}

void	ft_take_fork(t_vars *vars, t_data *tmp_list, int *i)
{
	while (1)
	{
		if (*tmp_list->eat_iter == *i)
			exit(0);
		sem_wait(vars->sem);
		sem_wait(vars->sem);
		ft_print_4norm(vars, tmp_list);
		gettimeofday(&tmp_list->time_now, NULL);
		// if (ft_check(tmp_list) == 1)
		// {
		// 	sem_wait(vars->sem4p);
		// 	printf("%ld ms %d DIED \n", ft_2_ms(tmp_list->time_now) -
		// 			tmp_list->time_s, tmp_list->id);
		// 	kill (0, 15);
		// }
		ft_start_philo(vars, tmp_list, i);
	}
}
void	*ft_watcher(void *philosofer)
{
	t_data *tmp_list;

	// sleep(5);
	tmp_list = philosofer;
	struct timeval loctime;
	while (1)
	{
		if (ft_check(tmp_list) == 1)
			{
				gettimeofday(&loctime, NULL);
				sem_wait(tmp_list->sem4p);
				pthread_mutex_lock(&tmp_list->mut_print);
				printf("%ld ms %d DIED \n", ft_2_ms(loctime) -
						tmp_list->time_s, tmp_list->id);
				kill (0, 15);
			}
		my_usleep(10);
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
	pthread_mutex_init(&vars->list[i]->mut_leat, NULL);
	pthread_mutex_init(&vars->list[i]->mut_print, NULL);
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
