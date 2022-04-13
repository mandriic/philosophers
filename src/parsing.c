#include "philo.h"
void *my_usleep(int ms)
{
	struct timeval time_start;
	struct timeval time_now;
	gettimeofday(&time_now, NULL);
	gettimeofday(&time_start, NULL);
	while((time_now.tv_sec - time_start.tv_sec) * 1000 + (time_now.tv_usec - time_start.tv_usec)/ 1000 < ms)
	{
		usleep(10);
		gettimeofday(&time_now, NULL);
		// printf("%s\n", "test");
	}
}
t_data *ft_data(int id, t_vars *vars)
{
	t_data *data;
	data = malloc(sizeof(t_data));
	pthread_mutex_init(&data->mut, NULL);
	pthread_mutex_init(&data->mut_last_eat, NULL);

	data->id = id;
	data->fork = id;
	data->time_to_eat = &vars->t_2_eat;
	data->time_to_die = &vars->t_2_die;
	data->time_to_sleep = &vars->t_2_slp;
	data->num_philo = &vars->num_philo;
	data->need_eat = 1;
	data->last_eat.tv_sec = 0;
	data->last_eat.tv_usec = 0;
	data->mut_print = &vars->mut_stdout;
	// printf("%did \n", *data->time_to_eat);
	// sleep(3);
	return (data);
}
void ft_create_list(t_vars *vars)
{
	t_data *data;
	t_list *temp;
	t_list *last;


	vars->i = 1;

	while(vars->i <= vars->num_philo)
	{
		data = ft_data(vars->i,vars);
		if(!vars->list)
			vars->list = ft_lstnew((t_data *)data);
		else
		{
			vars->temp_tlist = ft_lstnew((t_data *)data);
			ft_lstadd_back(&vars->list, vars->temp_tlist);
		}
		vars->i++;

	}
	temp = vars->list;
	vars->last = ft_lstlast(vars->list);
	if (vars->last != vars->list)
		vars->last->next = vars->list;
	// while (temp->next != NULL)
	// {
	// 	printf("id is %d\n", temp->content->id);
	// 	// if (vars->list->next)
	// 		temp = temp->next;
	// }
	// printf("id %d " vars->list_philo->content->id);
}
void	*ft_philos(void *list)
{	
		t_list *phil_data;
		phil_data = list;
		struct timeval time_start;
		struct timeval time_now;
		if (phil_data->content->id%2 == 1)
			my_usleep(5);
		gettimeofday(&time_start, NULL);
		while(1)
		{


			if( *phil_data->content->num_philo > 1 && phil_data->content->fork > phil_data->next->content->fork)
			{	
				pthread_mutex_lock(&phil_data->content->mut);
				gettimeofday(&time_now, NULL);

				pthread_mutex_lock(phil_data->content->mut_print);
				printf("%ld ms %d has taken a fork %d\n", (time_now.tv_sec - time_start.tv_sec) * 1000 + (time_now.tv_usec - time_start.tv_usec) / 1000, phil_data->content->id, phil_data->content->fork); 
				pthread_mutex_unlock(phil_data->content->mut_print);

				pthread_mutex_lock(&phil_data->next->content->mut);
				gettimeofday(&time_now, NULL);

				pthread_mutex_lock(phil_data->content->mut_print);
				printf("%ld ms %d has taken a fork %d\n", (time_now.tv_sec - time_start.tv_sec) * 1000 + (time_now.tv_usec - time_start.tv_usec) / 1000, phil_data->content->id, phil_data->next->content->fork); 
				pthread_mutex_unlock(phil_data->content->mut_print);
				
				// printf("!Im philo num %d, im eatin with fork num %d and %d\n", phil_data->content->id, phil_data->content->fork, phil_data->next->content->fork);
				my_usleep(*phil_data->content->time_to_eat);
				pthread_mutex_lock(&phil_data->content->mut_last_eat);

				gettimeofday(&phil_data->content->last_eat, NULL);
				pthread_mutex_unlock(&phil_data->content->mut_last_eat);


				gettimeofday(&time_now, NULL);
				pthread_mutex_lock(phil_data->content->mut_print);

				printf("%ld ms %d eating\n", (time_now.tv_sec - time_start.tv_sec) * 1000 + (time_now.tv_usec - time_start.tv_usec) / 1000, phil_data->content->id); 
				pthread_mutex_unlock(phil_data->content->mut_print);

				pthread_mutex_unlock(&phil_data->next->content->mut);
				pthread_mutex_unlock(&phil_data->content->mut);
				gettimeofday(&time_now, NULL);
				pthread_mutex_lock(phil_data->content->mut_print);

				printf("%ld ms %d sleeping\n", (time_now.tv_sec - time_start.tv_sec) * 1000 + (time_now.tv_usec - time_start.tv_usec) / 1000, phil_data->content->id); 
				pthread_mutex_unlock(phil_data->content->mut_print);

				my_usleep(*phil_data->content->time_to_sleep);
				gettimeofday(&time_now, NULL);
				pthread_mutex_lock(phil_data->content->mut_print);

				printf("%ld ms %d thinking\n", (time_now.tv_sec - time_start.tv_sec) * 1000 + (time_now.tv_usec - time_start.tv_usec) / 1000, phil_data->content->id); 
				pthread_mutex_unlock(phil_data->content->mut_print);


			}
			else 
			{
				pthread_mutex_lock(&phil_data->next->content->mut);
				gettimeofday(&time_now, NULL);
				pthread_mutex_lock(phil_data->content->mut_print);

				printf("%ld ms %d has taken a fork %d\n", (time_now.tv_sec - time_start.tv_sec) * 1000 + (time_now.tv_usec - time_start.tv_usec) / 1000, phil_data->content->id, phil_data->next->content->fork); 
				pthread_mutex_unlock(phil_data->content->mut_print);

				pthread_mutex_lock(&phil_data->content->mut);
				gettimeofday(&time_now, NULL);
				pthread_mutex_lock(phil_data->content->mut_print);

				printf("%ld ms %d has taken a fork %d\n", (time_now.tv_sec - time_start.tv_sec) * 1000 + (time_now.tv_usec - time_start.tv_usec) / 1000, phil_data->content->id, phil_data->content->fork); 
				pthread_mutex_unlock(phil_data->content->mut_print);


				// printf("!Im philo num %d, im eatin with fork num %d and %d\n", phil_data->content->id, phil_data->content->fork, phil_data->next->content->fork);
				my_usleep(*phil_data->content->time_to_eat);
				pthread_mutex_lock(&phil_data->content->mut_last_eat);

				gettimeofday(&phil_data->content->last_eat, NULL);
				pthread_mutex_unlock(&phil_data->content->mut_last_eat);


				gettimeofday(&time_now, NULL);
				pthread_mutex_lock(phil_data->content->mut_print);

				printf("%ld ms %d eating\n", (time_now.tv_sec - time_start.tv_sec) * 1000 + (time_now.tv_usec - time_start.tv_usec) / 1000, phil_data->content->id); 
				pthread_mutex_unlock(phil_data->content->mut_print);

				pthread_mutex_unlock(&phil_data->content->mut);
				pthread_mutex_unlock(&phil_data->next->content->mut);
				gettimeofday(&time_now, NULL);
				pthread_mutex_lock(phil_data->content->mut_print);

				printf("%ld ms %d sleeping\n", (time_now.tv_sec - time_start.tv_sec) * 1000 + (time_now.tv_usec - time_start.tv_usec) / 1000, phil_data->content->id); 
				pthread_mutex_unlock(phil_data->content->mut_print);

				my_usleep(*phil_data->content->time_to_sleep);
				gettimeofday(&time_now, NULL);
				pthread_mutex_lock(phil_data->content->mut_print);

				printf("%ld ms %d thinking\n", (time_now.tv_sec - time_start.tv_sec) * 1000 + (time_now.tv_usec - time_start.tv_usec) / 1000, phil_data->content->id); 
				pthread_mutex_unlock(phil_data->content->mut_print);

			}

		}

}
void ft_create_pthread(t_vars *vars)
{
	t_list *temp_list;
	pthread_t temp;
	temp_list = vars->list;
	temp = vars->list->content->philo;

	while(1)	
	{
		pthread_create(&temp, NULL, ft_philos, (void *)temp_list);
		// pthread_join(temp, NULL);
		if (temp_list == vars->last)
			break ;
		temp_list = temp_list->next;
	}
}
void *ft_watcher(void *vars)
{
	t_list *temp_list;
	struct timeval start_time;
	struct timeval cur_time;

	t_vars *vars_l = vars;
	temp_list = vars_l->list;

	gettimeofday(&cur_time, NULL);
	gettimeofday(&start_time, NULL);
	// printf("%d\n", vars_l->cur_time.tv_usec);	
	while(1)
	{
		if(temp_list->content->last_eat.tv_usec)
		{
			gettimeofday(&cur_time, NULL);
			// printf("%ld\n", (cur_time.tv_sec - temp_list->content->last_eat.tv_sec) * 1000 + temp_list->content->last_eat.tv_usec / 1000);

			// time_in_mill_now = (vars_l->cur_time.tv_sec) * 1000 + (vars_l->cur_time.tv_usec) / 1000;
			// // time_next = (temp_list->next->content->last_eat.tv_sec) * 1000 + (temp_list->next->content->last_eat.tv_usec) / 1000;
			// time_in_mill_eat = (temp_list->content->last_eat.tv_sec) * 1000 + (temp_list->content->last_eat.tv_usec) / 1000;
			// diff = time_in_mill_now - time_in_mill_eat;
			pthread_mutex_lock(&temp_list->content->mut_last_eat);

			if ((cur_time.tv_sec - temp_list->content->last_eat.tv_sec) * 1000 + (cur_time.tv_usec - temp_list->content->last_eat.tv_usec) / 1000 > *temp_list->content->time_to_die)
			{
				printf("%ld ms %d died\n ", (cur_time.tv_sec - start_time.tv_sec)  * 1000 + (cur_time.tv_usec - start_time.tv_usec) / 1000, temp_list->content->id); 
				vars_l->death = 1;
				break ;	
			
			}
			pthread_mutex_unlock(&temp_list->content->mut_last_eat);

		}

		// if(temp_list->next != 0)
		// 	temp_list= temp_list->next;

		// else
		// 	break;

		// sleep(1);
	}
}
int	pars_string(t_vars *vars, char **argv)
{
	pthread_t watch;
	pthread_mutex_init(&vars->mut_stdout, NULL);
	vars->i = 0;
	vars->death = 0;
	vars->eat_iter = -1;
	vars->lets_see = 0;
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
		if (vars->num_philo < 1 || vars->t_2_die <= 0 || vars->t_2_eat <= 0 || vars->t_2_slp < 0)
		return (1);
	if (vars->i == 5 && vars->eat_iter <= 0)
		return (1);
	// printf("nums %d %d %d %d %d\n", vars->num_philo, vars->t_2_die, vars->t_2_eat, vars->t_2_slp, vars->eat_iter);
	ft_create_list(vars);
	ft_create_pthread(vars);
		pthread_create(&watch, NULL, ft_watcher, (void *) vars);
	while(!vars->death)
		usleep(1);
	return (0);
}

