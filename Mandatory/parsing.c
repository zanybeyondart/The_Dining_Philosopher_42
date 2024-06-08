/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zvakil <zvakil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 12:02:17 by zvakil            #+#    #+#             */
/*   Updated: 2024/06/08 22:30:49 by zvakil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_arguments(int ac, char **av)
{
	int	i;

	i = 1;
	if (ac < 5 || ac > 6)
	{
		exit_mes("Invalid Arguments : 4 or 5 Arguments only, Check Subject");
		return (0);
	}
	while (av[i] != NULL)
	{
		if (ft_atoi(av[i++]) == 0)
		{
			exit_mes("Invalid Arguments : Enter number greater than 0");
			return (0);
		}
	}
	return (1);
}

void	exit_mes(char *mes)
{
	printf("%s\n", mes);
}
