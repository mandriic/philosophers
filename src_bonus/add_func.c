#include "philo_bonus.h"

t_list	*ft_lstlast(t_list *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	if (*lst == NULL)
		*lst = new;
	else
		ft_lstlast(*lst)->next = new;
}

t_list	*ft_lstnew(t_data *content)
{
	t_list	*list;

	list = malloc(sizeof(t_list));
	if (NULL == list)
		return (0);
	(*list).content = content;
	(*list).next = NULL;
	return (list);
}

long	ft_2_ms(struct timeval time, struct timeval time2)
{
	long	ms;
	long	ms2;

	ms = time.tv_sec * 1000 + time.tv_usec / 1000;
	ms2 = time2.tv_sec * 1000 + time2.tv_usec / 1000;
	return (ms - ms2);
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

void	ft_death(t_vars *vars, t_list *list, struct timeval t2)
{
	long	diff;

	diff = ft_2_ms(list->content->cur_time, t2);
	// printf("%ld ms %d died\n", diff, list->content->id);
	vars->death = 1;
}

int	ft_check(t_list *l)
{
	long	diff_ct_le;
	long	diff_ct_ts;

	gettimeofday(&l->content->cur_time, NULL);
	diff_ct_le = ft_2_ms(l->content->cur_time, l->content->last_eat);
	diff_ct_ts = ft_2_ms(l->content->cur_time, l->content->time_start);
	if ((l->content->last_eat.tv_sec
			&& diff_ct_le > *l->content->time_to_die && !l->content->fin)
		|| (l->content->time_start.tv_sec
			&& !l->content->last_eat.tv_sec
			&& diff_ct_ts > *l->content->time_to_die && !l->content->fin))
		return (1);
	if(*l->content->eat_iter != -1 && *l->content->eat_iter == l->content->c_iter)
		return(2);
	return (0);
}
