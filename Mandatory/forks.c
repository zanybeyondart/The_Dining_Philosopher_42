/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zvakil <zvakil@student.42abudhabi.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 14:42:02 by zvakil            #+#    #+#             */
/*   Updated: 2024/05/18 14:42:19 by zvakil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	my_fork_pick(t_philo *philo, t_main *main)
{
	pthread_mutex_lock(philo->my_mutex);
	pthread_mutex_lock(&main->p_lock);
	if (main->philo_dead != 1)
	{
		printf("%d %d picked up a fork\n", current_time(philo), philo->id);
		pthread_mutex_unlock(&main->p_lock);
		philo->my_fork[1] = 1;
	}
	else
		pthread_mutex_unlock(&main->p_lock);
}

void	next_fork_pick(t_philo *philo, t_main *main)
{
	pthread_mutex_lock(philo->next_mutex);
	pthread_mutex_lock(&main->p_lock);
	if (main->philo_dead != 1)
	{
		printf("%d %d picked up a fork\n", current_time(philo), philo->id);
		pthread_mutex_unlock(&main->p_lock);
		philo->next_fork[1] = 1;
	}
	else
		pthread_mutex_unlock(&main->p_lock);
}
