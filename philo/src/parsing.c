#include "philo.h"
// t_data	*ft_create_data(int num)
// {
// 	static int count = 0;
// 	t_data		*data;

// 	data = malloc(sizeof(t_data));
// 	if (!data)
// 		return (0);
// 	if(count == 0)
// 		data->num_philo = num;
// 	else if (count == 1)
// 		data->

// 	count++;
// 	return (data);
// }

int	pars_string(t_vars *vars, char **argv)
{
	vars->i = 0;
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
	if (vars->num_philo < 2 || vars->t_2_die <= 0 || vars->t_2_eat <= 0 || vars->t_2_slp < 0)
		return (1);
	if (vars->i == 5 && vars->eat_iter <= 0)
		return (1);
	printf("nums %d %d %d %d %d\n", vars->num_philo, vars->t_2_die, vars->t_2_eat, vars->t_2_slp, vars->eat_iter);
	return (0);
}
