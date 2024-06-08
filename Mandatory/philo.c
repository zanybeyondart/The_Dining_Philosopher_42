/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zvakil <zvakil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 11:51:14 by zvakil            #+#    #+#             */
/*   Updated: 2024/06/08 22:38:22 by zvakil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	int	a;
	int	b;
	int	neg;

	b = 0;
	a = 0;
	while ((str[a] >= 9 && str[a] <= 13) || str[a] == ' ')
		a++;
	if (str[a] == '+' || str[a] == '-')
	{
		if (str[a] == '-')
			neg = 1;
		a++;
	}
	while (str[a] >= '0' && str[a] <= '9')
	{
		b = b * 10 + (str[a] - 48);
		a++;
	}
	if (neg == 1)
		return (b * -1);
	else
		return (b);
}

void	threader(t_philo *current_philo, t_main *main)
{
	t_thread	*data;

	data = smart_malloc(sizeof(t_thread));
	data->philo = current_philo;
	data->main = main;
	pthread_create(&current_philo->thread, NULL, function, (void *)data);
}

void	create_threads(t_main *main)
{
	t_philo	*current_philo;

	current_philo = main->philos;
	main->start_time = current_time(main);
	while (current_philo)
	{
		threader(current_philo, main);
		current_philo = current_philo->next;
	}
}

void	join_threads(t_philo *philos)
{
	while (philos)
	{
		pthread_join(philos->thread, NULL);
		philos = philos->next;
	}
}

int	main(int ac, char **av)
{
	t_main	*main;

	if (check_arguments(ac, av))
	{
		main = smart_malloc(sizeof(t_main));
		main->philos = init_thread(ft_atoi(av[1]));
		main->eat_time = ft_atoi(av[3]);
		main->current_time = 0;
		main->sleep_time = ft_atoi(av[4]);
		main->dead_time = ft_atoi(av[2]);
		main->philo_dead = 0;
		if (av[5])
			main->meals = ft_atoi(av[5]);
		else
			main->meals = -1;
		pthread_mutex_init(&main->p_lock, NULL);
		assign_forks(main->philos, NULL, NULL);
		create_threads(main);
		join_threads(main->philos);
		pthread_mutex_destroy(&main->p_lock);
		free_program(main->philos);
		free(main);
		return (0);
	}
	return (1);
}
