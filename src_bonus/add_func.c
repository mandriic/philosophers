/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_func.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mandriic <mandriic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 22:24:41 by mandriic          #+#    #+#             */
/*   Updated: 2022/04/25 22:24:45 by mandriic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

// t_list	*ft_lstlast(t_list *lst)
// {
// 	if (!lst)
// 		return (NULL);
// 	while (lst->next != NULL)
// 		lst = lst->next;
// 	return (lst);
// }

// void	ft_lstadd_back(t_list **lst, t_list *new)
// {
// 	if (*lst == NULL)
// 		*lst = new;
// 	else
// 		ft_lstlast(*lst)->next = new;
// }

// t_list	*ft_lstnew(t_data)
// {
// 	t_list	*list;

// 	list = malloc(sizeof(t_list));
// 	if (NULL == list)
// 		return (0);
// 	(*list ;
// 	(*list).next = NULL;
// 	return (list);
// }

long	ft_2_ms(struct timeval time)
{
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int	ft_check(t_data *l)
{
	long	diff_ct_le;
	long	diff_ct_ts;
	long	loc_last_e;
	long	loc_cur_time;
	// long	loc_time_s;
	struct timeval loctime;

	loc_last_e = ft_2_ms(l->last_eat);
	gettimeofday(&loctime, NULL);
	loc_cur_time = ft_2_ms (loctime);
	diff_ct_le = loc_cur_time - loc_last_e;
	diff_ct_ts = loc_cur_time - l->time_s;
	if ((l->last_eat.tv_sec
			&& diff_ct_le > *l->time_to_die && !l->fin)
		|| (l->time_start.tv_sec
			&& !l->last_eat.tv_sec
			&& diff_ct_ts > *l->time_to_die && !l->fin))
		return (1);
	if (*l->eat_iter != -1 && *l->eat_iter
		== l->c_iter)
		return (2);
	return (0);
}
