/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mandriic <mandriic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 10:06:48 by mandriic          #+#    #+#             */
/*   Updated: 2022/04/15 10:06:51 by mandriic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <sys/time.h>
# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>
# include <signal.h>
# include <semaphore.h>
# include <fcntl.h> 
# include <sys/types.h>
# include <sys/wait.h>      

typedef struct s_data
{
	int				id;
	int				pid;
	struct timeval	last_eat;
	int				*time_to_eat;
	int				*time_to_die;
	int				*time_to_sleep;
	int				*eat_iter;
	int				*num_philo;
	int				c_iter;
	int				fin;
	struct timeval	time_start;
	struct timeval	time_now;
	struct timeval	cur_time;
}t_data;

typedef struct s_list
{
	t_data			*content;
	struct s_list	*next;
}t_list;

typedef struct s_vars
{
	t_list			*list;
	t_list			*temp_tlist;
	t_list			*last;
	sem_t			*sem;
	sem_t			*sem4p;
	int				main_pid;
	struct timeval	cur_time;
	int				num_philo;
	int				t_2_die;
	int				t_2_eat;
	int				t_2_slp;
	int				eat_iter;
	int				end4watch;
	int				i;
	int				iters_end;
	int				death;
	long			difcl;
	long			difcs;
}t_vars;

void	ft_start_philo(t_vars *vars, t_list *tmp_list, int *i);
void	ft_print_4norm(t_vars *vars, t_list *tmp_lst);
void	ft_take_fork(t_vars *vars, t_list *tmp_lst, int *i);
void	ft_create_forks(t_vars *vars);
void	ft_create_sem(t_vars *vars);
long	ft_2_ms(struct timeval time, struct timeval time2);
int		ft_check(t_list *l);
void	ft_mut_fokrs(t_list *phil_data, int biger);
void	ft_create_list(t_vars *vars);
void	my_usleep(int ms);
t_data	*ft_data(int id, t_vars *vars);
int		pars_string(t_vars *vars, char **argv);
int		ft_atoi_bonus(const char *str);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
t_list	*ft_lstnew(t_data *content);
#endif
