/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zvakil <zvakil@student.42abudhabi.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 11:49:30 by zvakil            #+#    #+#             */
/*   Updated: 2024/05/12 17:46:46 by zvakil           ###   ########.fr       */
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

void	eating(t_philo *philo, int start_time, t_main *main)
{
	if (philo->id % 2 != 0)
	{
		my_fork_pick(philo, main);
		next_fork_pick(philo, main);
	}
	else if (philo->id % 2 == 0)
	{
		usleep(1000);
		next_fork_pick(philo, main);
		my_fork_pick(philo, main);
	}
	if (philo->my_fork[1] == 1 && philo->next_fork[1] == 1)
	{
		pthread_mutex_lock(&main->p_lock);
		printf("%d %d is eating \n", current_time(philo), philo->id);
		philo->eating = 1;
		philo->last_meal = current_time(philo);
		pthread_mutex_unlock(&main->p_lock);
		usleep(main->eat_time * 1000);
	}
	pthread_mutex_lock(&main->p_lock);
	philo->eating = 0;
	pthread_mutex_unlock(&main->p_lock);
	philo->next_fork[1] = 0;
	philo->my_fork[1] = 0;
	pthread_mutex_unlock(philo->my_mutex);
	pthread_mutex_unlock(philo->next_mutex);
}

void	thinking(t_philo *philo, int start_time, t_main *main)
{
	pthread_mutex_lock(&main->p_lock);
	if (main->philo_dead != 1)
	{
		printf("%d %d is thinking\n", current_time(philo), philo->id);
		pthread_mutex_unlock(&main->p_lock);
	}
	else
		pthread_mutex_unlock(&main->p_lock);
}

void	sleeping(t_philo *philo, int start_time, t_main *main)
{
	pthread_mutex_lock(&main->p_lock);
	if (main->philo_dead != 1)
	{
		printf("%d %d is sleeping\n", current_time(philo), philo->id);
		pthread_mutex_unlock(&main->p_lock);
		usleep(main->sleep_time * 1000);
	}
	else
		pthread_mutex_unlock(&main->p_lock);
}

void	*function(void *ag)
{
	struct timeval	time;
	t_thread		*data;

	data = (t_thread *)ag;
	while (1)
	{
		gettimeofday(&time, NULL);
		eating(data->philo, time.tv_usec, data->main);
		sleeping(data->philo, time.tv_usec, data->main);
		thinking(data->philo, time.tv_usec, data->main);
		pthread_mutex_lock(&data->main->p_lock);
		if (data->main->philo_dead == 1)
		{
			pthread_mutex_unlock(&data->main->p_lock);
			break;
		}
		pthread_mutex_unlock(&data->main->p_lock);
	}
	// usleep(5000);
	// pthread_mutex_destroy(data->philo->my_mutex);
	free(data);
	return (NULL);
}
