#ifndef PHILO
# define PHILO

#include <sys/time.h>
#include <stdio.h>
#include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>
# include <limits.h>

typedef struct s_data
{
	int num_philo;
	int state_fork;


}t_data;

typedef struct s_list
{
	t_data			*content;
	struct s_list	*next;
}t_list;


typedef struct s_vars
{
	t_list	*list_philo;
	int		num_philo;
	int		t_2_die;
	int		t_2_eat;
	int		t_2_slp;
	int		eat_iter;
	int		i;

}t_vars;




int	pars_string(t_vars *vars, char **argv);
int		ft_atoi(const char *str);



#endif