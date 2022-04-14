#include "philo.h"

void	*ft_philos(void *list)
{	
	t_list	*phil_data;

	phil_data = list;
	gettimeofday(&phil_data->content->time_start, NULL);
	if (phil_data->content->id % 2 == 0)
		my_usleep(1);
	while (1)
	{
		if (phil_data->content->fork > phil_data->next->content->fork)
			ft_mut_fokrs(phil_data, 1);
		else
			ft_mut_fokrs(phil_data, 0);
		if (phil_data->content->fork > phil_data->next->content->fork)
			ft_mut_fokrs(phil_data, 0);
		else
			ft_mut_fokrs(phil_data, 1);
		ft_last_eat(phil_data);
		my_usleep(*phil_data->content->time_to_eat);
		if (phil_data->content->fork > phil_data->next->content->fork)
			ft_unmut_forks(phil_data, 1);
		else
			ft_unmut_forks(phil_data, 0);
		ft_sleep_thin(phil_data);
	}
}

void	ft_mut_fokrs(t_list *phil_data, int biger)
{
	if (biger == 1)
	{
		pthread_mutex_lock(&phil_data->content->mut);
		gettimeofday(&phil_data->content->time_now, NULL);
	}
	else
	{
		pthread_mutex_lock(&phil_data->next->content->mut);
		gettimeofday(&phil_data->content->time_now, NULL);
	}
	pthread_mutex_lock(phil_data->content->mut_print);
	printf("%ld ms %d has taken a fork \n", ft_2_ms(phil_data->content->time_now,
			phil_data->content->time_start), phil_data->content->id);
	pthread_mutex_unlock(phil_data->content->mut_print);
}

void	ft_unmut_forks(t_list *phil_data, int biger)
{
	if (biger == 1)
	{
		pthread_mutex_unlock(&phil_data->next->content->mut);
		pthread_mutex_unlock(&phil_data->content->mut);
	}
	else
	{
		pthread_mutex_unlock(&phil_data->content->mut);
		pthread_mutex_unlock(&phil_data->next->content->mut);
	}
}

void	ft_last_eat(t_list *phil_data)
{
	pthread_mutex_lock(&phil_data->content->mut_last_eat);
	gettimeofday(&phil_data->content->last_eat, NULL);
	phil_data->content->changed = 1;
	pthread_mutex_unlock(&phil_data->content->mut_last_eat);
	pthread_mutex_lock(phil_data->content->mut_print);
	gettimeofday(&phil_data->content->time_now, NULL);
	printf("%ld ms %d eating\n", ft_2_ms(phil_data->content->time_now,
			phil_data->content->time_start), phil_data->content->id);
	pthread_mutex_unlock(phil_data->content->mut_print);
}

void	ft_sleep_thin(t_list *phil_data)
{
	gettimeofday(&phil_data->content->time_now, NULL);
	pthread_mutex_lock(phil_data->content->mut_print);
	printf("%ld ms %d sleeping\n", ft_2_ms(phil_data->content->time_now,
			phil_data->content->time_start), phil_data->content->id);
	pthread_mutex_unlock(phil_data->content->mut_print);
	my_usleep(*phil_data->content->time_to_sleep);
	gettimeofday(&phil_data->content->time_now, NULL);
	pthread_mutex_lock(phil_data->content->mut_print);
	printf("%ld ms %d thinking\n", ft_2_ms(phil_data->content->time_now,
			phil_data->content->time_start), phil_data->content->id);
	pthread_mutex_unlock(phil_data->content->mut_print);
}
