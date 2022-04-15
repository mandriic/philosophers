/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mandriic <mandriic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 10:06:38 by mandriic          #+#    #+#             */
/*   Updated: 2022/04/15 10:06:41 by mandriic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_vars		vars;
	pthread_t	watch;

	vars = (t_vars){};
	if (argc < 5 || argc > 6)
	{
		printf("Usage: ./philo number_of_philofers time_to_die ");
		printf("time_to_eat time_to_sleep [times_to_eat]\n");
		return (0);
	}
	if (pars_string(&vars, &argv[1]) == 1)
	{
		printf("Error\nphilosophers\t>=\t2\ntime_to_eat\t>\t0\n");
		printf("time_to_sleep\t>\t0\n");
		printf("time_to_die\t>\t0\n[eats_iter]\t>\t0\n");
		return (1);
	}
	ft_create_list(&vars);
	ft_create_pthread(&vars);
	pthread_create(&watch, NULL, ft_watcher, (void *) &vars);
	while (!vars.death)
		usleep(1);
	return (0);
}
