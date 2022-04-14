#include "philo.h"

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

int	ft_check(t_list *l)
{
	if ((l->content->last_eat.tv_sec
			&& ft_2_ms(l->content->cur_time, l->content->last_eat)
			> *l->content->time_to_die) || (l->content->time_start.tv_sec
			&& !l->content->last_eat.tv_sec
			&& ft_2_ms(l->content->cur_time, l->content->time_start)
			> *l->content->time_to_die))
		return (1);
	return (0);
}

long	ft_2_ms(struct timeval time, struct timeval time2)
{
	long	ms;
	long	ms2;

	ms = time.tv_sec * 1000 + time.tv_usec / 1000;
	ms2 = time2.tv_sec * 1000 + time2.tv_usec / 1000;
	return (ms - ms2);
}
