/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mandriic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/26 09:04:03 by mandriic          #+#    #+#             */
/*   Updated: 2021/10/01 15:18:58 by mandriic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <limits.h>

static void	ft_error(void)
{
	write(1, "Error\n", 6);
	exit(1);
}
int	ft_atoi(const char *str)
{
	int	i;
	long long	pon;
	long long	digi;
	long long	ck;


	i = 0;
	pon = 1;
	digi = 0;
	while (str[i] == ' ' || (str[i] > 8 && str[i] < 14))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			pon *= -1;
		i++;
	}
	if (str[i] == '-' || str[i] == '+')
		return (0);
	while (str[i] <= '9' && str[i] >= '0')
	{
		digi = digi * 10 + (str[i] - '0');
		i++;
	}
	ck = digi * pon;

	if (ck > INT_MAX || ck < INT_MIN)
		ft_error();
	return (digi * pon);
}
