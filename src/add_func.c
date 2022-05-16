/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_func.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mandriic <mandriic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 10:05:36 by mandriic          #+#    #+#             */
/*   Updated: 2022/04/15 10:05:39 by mandriic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_check(t_data *l, t_vars *vars)
{
	long	diff_ct_le;
	long	diff_ct_ts;
	long	last_loc;
	pthread_mutex_lock(&l->mut_prio_l);
	pthread_mutex_lock(&l->mut_prio_h);
	pthread_mutex_lock(&l->mut_last_eat);
	pthread_mutex_unlock(&l->mut_prio_h);
	last_loc = l->time_last_e;
	pthread_mutex_unlock(&l->mut_last_eat);
	pthread_mutex_unlock(&l->mut_prio_l);
	vars->gen_time_ms = ft_2_ms(vars->cur_time);
	diff_ct_le = vars->gen_time_ms - last_loc;
	diff_ct_ts = vars->gen_time_ms - l->time_s;
	if ((l->last_eat.tv_sec
			&& diff_ct_le > *l->time_to_die && !l->fin)
		|| (l->time_start.tv_sec
			&& !l->last_eat.tv_sec
			&& diff_ct_ts > *l->time_to_die && !l->fin))
		return (1);
	return (0);
}

long	ft_2_ms(struct timeval time)
{
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}
