#include "src/philo.h"

int	ft_iter(t_list *phil_data)
{
	if (*phil_data->eat_iter != -1)
			phil_data->c_iter++;
	if (phil_data->c_iter == *phil_data->eat_iter)
	{
		phil_data->fin = 1;
		*phil_data->iters_end_p = *phil_data->iters_end_p + 1;
		return (0);
	}
	return (1);
}

void	ft_phil_do(t_list *phil_data)
{
	while (!*phil_data->death)
	{
		// if (phil_data->fork > phil_data->next->fork)
			ft_mut_fokrs(phil_data, 1);
		// else
		// 	ft_mut_fokrs(phil_data, 0);
		// if (phil_data->fork > phil_data->next->fork)
			ft_mut_fokrs(phil_data, 0);
		// else
			// ft_mut_fokrs(phil_data, 1);
		ft_last_eat(phil_data);
		my_usleep(*phil_data->time_to_eat);
		// if (phil_data->fork > phil_data->next->fork)
			ft_unmut_forks(phil_data, 0);
		// else
			// ft_unmut_forks(phil_data, 0);
		ft_sleep_thin(phil_data);
		if (!ft_iter(phil_data))
			break ;
	}
}

void	*ft_philos(void *list)
{	
	t_data	*phil_data;

	phil_data = list;
	gettimeofday(&phil_data->time_start, NULL);
	if (phil_data->id % 2 == 1)
		my_usleep(60);
	ft_phil_do(phil_data);
	return (0);
}

void	ft_last_eat(t_list *phil_data)
{
	pthread_mutex_lock(&phil_data->mut_last_eat);
	gettimeofday(&phil_data->last_eat, NULL);
	phil_data->need_eat = 0;
	pthread_mutex_unlock(&phil_data->mut_last_eat);
	pthread_mutex_lock(phil_data->mut_print);
	gettimeofday(&phil_data->time_now, NULL);
	printf("%ld ms %d eating\n", ft_2_ms(phil_data->time_now,
			phil_data->time_start), phil_data->id);
	pthread_mutex_unlock(phil_data->mut_print);
}

void	ft_sleep_thin(t_list *phil_data)
{
	gettimeofday(&phil_data->time_now, NULL);
	pthread_mutex_lock(phil_data->mut_print);
	printf("%ld ms %d sleeping\n", ft_2_ms(phil_data->time_now,
			phil_data->time_start), phil_data->id);
	pthread_mutex_unlock(phil_data->mut_print);
	my_usleep(*phil_data->time_to_sleep);
	gettimeofday(&phil_data->time_now, NULL);
	pthread_mutex_lock(phil_data->mut_print);
	printf("%ld ms %d thinking\n", ft_2_ms(phil_data->time_now,
			phil_data->time_start), phil_data->id);
	pthread_mutex_unlock(phil_data->mut_print);
}

void	ft_mut_fokrs(t_list *phil_data, int biger)
{
	long test;

	if (biger == 1)
	{
		pthread_mutex_lock(&phil_data->mut);
		(void) phil_data->fork;
	}
	else
	{
		pthread_mutex_lock(&phil_data->next->mut);
		(void) phil_data->next->fork;
	}
	gettimeofday(&phil_data->time_now, NULL);

	pthread_mutex_lock(phil_data->mut_print);
		test = ft_2_ms(phil_data->time_now,
			phil_data->time_start);
	printf("%ld ms %d has taken a fork \n", test, phil_data->id);
	pthread_mutex_unlock(phil_data->mut_print);
}

void	ft_unmut_forks(t_list *phil_data, int biger)
{
	if (biger == 1)
	{
		pthread_mutex_unlock(&phil_data->next->mut);
		pthread_mutex_unlock(&phil_data->mut);

	}
	else
	{
		pthread_mutex_unlock(&phil_data->mut);
		pthread_mutex_unlock(&phil_data->next->mut);
	}
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
		gettimeofday(&time_now, NULL);
		usleep(10);
	}
}

void	*ft_watcher(void *vars)
{
	t_list			*temp_list;

	temp_list = ((t_vars *)vars)->list;
	gettimeofday(&((t_vars *)vars)->time_start, NULL);
	while (*temp_list->iters_end_p != ((t_vars *)vars)->num_philo)
	{
		if (temp_list->time_start.tv_sec
			|| temp_list->last_eat.tv_sec)
		{
			ft_need_eat(temp_list, ((t_vars *)vars));
			pthread_mutex_lock(&temp_list->mut_last_eat);
			gettimeofday(&temp_list->cur_time, NULL);
			if (ft_check(temp_list) == 1)
			{
				pthread_mutex_lock(temp_list->mut_print);
				ft_death(((t_vars *)vars), temp_list,
					((t_vars *)vars)->time_start);
				break ;
			}
			pthread_mutex_unlock(&temp_list->mut_last_eat);
		}
		if (*temp_list->iters_end_p == ((t_vars *)vars)->num_philo)
			*temp_list->death = 1;
		temp_list = temp_list->next;
	}
	return (0);
}

int	pars_string(t_vars *vars, char **argv)
{
	vars->eat_iter = -1;
	while (vars->i != 5)
	{
		if (vars->i == 0)
			vars->num_philo = ft_atoi(&argv[vars->i][0]);
		else if (vars->i == 1)
			vars->t_2_die = ft_atoi(&argv[vars->i][0]);
		else if (vars->i == 2)
			vars->t_2_eat = ft_atoi(&argv[vars->i][0]);
		else if (vars->i == 3)
			vars->t_2_slp = ft_atoi(&argv[vars->i][0]);
		else if (vars->i == 4)
			vars->eat_iter = ft_atoi(&argv[vars->i][0]);
		vars->i++;
		if (!argv[vars->i])
			break ;
	}
	if (vars->num_philo == 1)
		printf("%d ms 1 die\n", vars->t_2_die);
	if (vars->num_philo <= 1 || vars->t_2_die <= 0
		|| vars->t_2_eat <= 0 || vars->t_2_slp <= 0)
		return (1);
	if (vars->i == 5 && vars->eat_iter <= 0)
		return (1);
	return (0);
}

int	ft_create_list(t_vars *vars)
{
	t_data	*data;

	vars->i = 0;
	pthread_mutex_init(&vars->mut_stdout, NULL);
	if (vars->num_philo != 1)
	{
		while (++vars->i <= vars->num_philo)
		{
			data = ft_data(vars->i, vars);
			if (!data)
				return (1);
			if (!vars->list)
				vars->list = ft_lstnew((t_data *)data);
			else if (vars->num_philo > 1)
			{
				vars->temp_tlist = ft_lstnew((t_data *)data);
				ft_lstadd_back(&vars->list, vars->temp_tlist);
			}
		}
		vars->last = ft_lstlast(vars->list);
		if (vars->last != vars->list)
			vars->last->next = vars->list;
	}
	return (0);
}

int	ft_create_pthread(t_vars *vars)
{
	t_list		*temp_list;
	pthread_t	temp;

	temp_list = vars->list;
	while (1)
	{	
		temp = temp_list->philo;
		if (pthread_create(&temp, NULL, ft_philos, (void *)temp_list) != 0)
			return (1);
		if (temp_list == vars->last)
			break ;
		temp_list = temp_list->next;
	}
	return (0);
}

t_data	*ft_data(int id, t_vars *vars)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	pthread_mutex_init(&data->mut, NULL);
	pthread_mutex_init(&data->mut_last_eat, NULL);
	data->id = id;
	data->fork = id;
	data->time_to_eat = &vars->t_2_eat;
	data->time_to_die = &vars->t_2_die;
	data->time_to_sleep = &vars->t_2_slp;
	data->iters_end_p = &vars->iters_end;
	data->eat_iter = &vars->eat_iter;
	data->death = &vars->death;
	data->num_philo = &vars->num_philo;
	data->end4watch_p = &vars->end4watch;
	data->mut_print = &vars->mut_stdout;
	data->need_eat = -1;
	return (data);
}

void	ft_free_all(t_vars *vars, pthread_t *watch)
{
	vars->temp_tlist = vars->list;
	while (1)
	{
		pthread_mutex_destroy(&vars->temp_tlist->mut);
		pthread_mutex_destroy(&vars->temp_tlist->mut_last_eat);
		pthread_join(vars->temp_tlist->philo, NULL);
		if (vars->temp_tlist == vars->last)
			break ;
		vars->temp_tlist = vars->temp_tlist->next;
	}
	pthread_mutex_destroy(&vars->mut_stdout);
	pthread_join(*watch, NULL);
	vars->temp_tlist = vars->list;
	while (1)
	{
		free(vars->temp_tlist);
		if (vars->temp_tlist == vars->last)
		{
			free(vars->list);
			break ;
		}
		vars->temp_tlist = vars->temp_tlist->next;
	}
}

void	ft_print(int var)
{
	if (var == 1)
	{
		printf("Usage: ./philo number_of_philofers time_to_die ");
		printf("time_to_eat time_to_sleep [times_to_eat]\n");
	}
	if (var == 2)
	{
		printf("Error\nphilosophers\t>=\t1\ntime_to_eat\t>\t0\n");
		printf("time_to_sleep\t>\t0\n");
		printf("time_to_die\t>\t0\n[eats_iter]\t>\t0\n");
	}
}

int	main(int argc, char **argv)
{
	t_vars		vars;
	pthread_t	watch;

	vars = (t_vars){};
	if (argc < 5 || argc > 6)
	{
		ft_print(1);
		return (0);
	}
	if (pars_string(&vars, &argv[1]) == 1)
	{
		ft_print(2);
		return (1);
	}
	if (ft_create_list(&vars))
		return (0);
	if (ft_create_pthread(&vars) == 1)
		return (0);
	if (pthread_create(&watch, NULL, ft_watcher, (void *) &vars) != 0)
		return (0);
	while (!vars.death)
		usleep(10);
	// ft_free_all(&vars, &watch);
	return (0);
}