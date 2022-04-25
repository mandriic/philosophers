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
	// printf("2 ms%ld\n", time.tv_sec);
	// printf("2ms %ld\n", time2.tv_sec);

	ms = time.tv_sec * 1000 + time.tv_usec / 1000;
	ms2 = time2.tv_sec * 1000 + time2.tv_usec / 1000;
		// printf("ms-- %ld\n", ms);
	// printf("ms2-- %ld\n", ms2);
	// printf("DIIIIFFF%ld\n", ms - ms2 );
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

// printf("%d\n", l->content->my_iter_end);
	gettimeofday(&l->content->cur_time, NULL);
	diff_ct_le = ft_2_ms(l->content->cur_time, l->content->last_eat);
	diff_ct_ts = ft_2_ms(l->content->cur_time, l->content->time_start);
	// printf("cur time %dlast eat\n", l->content->last_eat.tv_usec);
	// printf("cur time %dtime staart\n", l->content->time_start.tv_usec );
	// printf("cur time %ld d[fff\n", diff_ct_le );
	// printf("cur time %ld gitttffff\n", diff_ct_ts );
	if ((l->content->last_eat.tv_sec
			&& diff_ct_le > *l->content->time_to_die && !l->content->fin)
		|| (l->content->time_start.tv_sec
			&& !l->content->last_eat.tv_sec
			&& diff_ct_ts > *l->content->time_to_die && !l->content->fin))
		return (1);
	// printf("eat iter 1%d eat iter 2%d myiter %d\n",*l->content->eat_iter, *l->content->eat_iter, l->content->c_iter);
	if(*l->content->eat_iter != -1 && *l->content->eat_iter == l->content->c_iter)
		return(2);
	return (0);
}


void	ft_need_eat(t_list *list, t_vars *vars)
{
	long	diff;

	diff = ft_2_ms(list->content->last_eat, list->next->content->last_eat);
	if (list == vars->list)
		diff = ft_2_ms(vars->last->content->last_eat, list->content->last_eat);
	if (diff > 0 || list->content->need_eat == -1)
		list->content->need_eat = 1;
}