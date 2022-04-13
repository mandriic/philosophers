#ifndef PHILO
# define PHILO

#include <sys/time.h>
#include <stdio.h>
#include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>

typedef struct s_data
{
	int id;
	pthread_mutex_t mut;
	pthread_mutex_t mut_last_eat;
	pthread_mutex_t *mut_print;

	int fork;
	int avbl;
	// int fork_r;
	struct timeval last_eat;
	int need_eat;
	pthread_t philo;
	int *time_to_eat;
	int *time_to_die;
	int *time_to_sleep;
	int *num_philo;
}t_data;

typedef struct s_list
{
	t_data			*content;
	struct s_list	*next;
}t_list;

typedef struct s_vars
{
	t_list	*list;
	t_list	*temp_tlist;
	t_list *last;
	struct timeval cur_time;
	pthread_mutex_t mut_stdout;
	int		num_philo;
	int		t_2_die;
	int		t_2_eat;
	int		t_2_slp;
	int		eat_iter;
	int		i;
	int 	lets_see;
	int 	death;

}t_vars; 











int	pars_string(t_vars *vars, char **argv);
int		ft_atoi(const char *str);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
t_list	*ft_lstnew(t_data *content);






#endif