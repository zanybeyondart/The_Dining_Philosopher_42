/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zvakil <zvakil@student.42abudhabi.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 11:49:30 by zvakil            #+#    #+#             */
/*   Updated: 2024/06/01 20:02:02 by zvakil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eat_mode(t_main *main, t_philo *philo)
{
	int	time;

	printf("%d %d is eating \n", current_time(philo), philo->id);
	philo->eating = 1;
	philo->last_meal = current_time(philo);
	time = current_time(philo);
	while (1)
	{
		if (current_time(philo) - time >= main->eat_time)
			break ;
		usleep(100);
	}
	pthread_mutex_lock(&main->p_lock);
	philo->eating = 0;
	pthread_mutex_unlock(&main->p_lock);
	philo->next_fork[1] = 0;
	philo->my_fork[1] = 0;

}

void	pick_fork(pthread_mutex_t *mutex, int *fork, t_main *main, t_philo *philo)
{
	while (1)
	{
		pthread_mutex_lock(mutex);
		pthread_mutex_lock(&main->p_lock);
		if (fork[1] == 0 || main->philo_dead == 1)
		{
			pthread_mutex_unlock(mutex);
			pthread_mutex_unlock(&main->p_lock);
			break ;
		}
		pthread_mutex_unlock(mutex);
		pthread_mutex_unlock(&main->p_lock);
		usleep(100);
		not_dead(main, philo);
	}
	pthread_mutex_lock(mutex);
	if (not_dead(main, philo))
		fork[1] = 1;
}

int	eating(t_philo *philo, t_main *main)
{
	pthread_mutex_lock(&main->p_lock);
	if (main->philo_dead == 1)
	{
		pthread_mutex_unlock(&main->p_lock);
		return (0);
	}
	pthread_mutex_unlock(&main->p_lock);
	if (philo->id % 2 != 0)
	{
		pick_fork(philo->next_mutex, philo->next_fork, main, philo);
		pick_fork(philo->my_mutex, philo->my_fork, main, philo);
	}
	else
	{
		usleep(500);
		pick_fork(philo->my_mutex, philo->my_fork, main, philo);
		pick_fork(philo->next_mutex, philo->next_fork, main, philo);
	}
	if (philo->my_fork[1] == 1 && philo->next_fork[1] == 1)
		eat_mode(main, philo);
	pthread_mutex_unlock(philo->my_mutex);
	if (philo->next_mutex)
		pthread_mutex_unlock(philo->next_mutex);
	return (1);
}

void	thinking(t_philo *philo, t_main *main)
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

void	sleeping(t_philo *philo, t_main *main)
{
	int	time;

	pthread_mutex_lock(&main->p_lock);
	if (main->philo_dead != 1)
	{
		printf("%d %d is sleeping\n", current_time(philo), philo->id);
		pthread_mutex_unlock(&main->p_lock);
		time = current_time(philo);
		while (1)
		{
			if (current_time(philo) - time >= main->sleep_time)
				break ;
			if (philo->last_meal != 0
				&& current_time(philo) - philo->last_meal >= main->dead_time)
			{
				printf("%d %d died\n", current_time(philo), philo->id);
				pthread_mutex_lock(&main->p_lock);
				main->philo_dead = 1;
				pthread_mutex_unlock(&main->p_lock);
				break ;
			}
			usleep(100);
		}
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
		eating(data->philo, data->main);
		sleeping(data->philo, data->main);
		thinking(data->philo, data->main);
		pthread_mutex_lock(&data->main->p_lock);
		if (data->main->philo_dead == 1)
		{
			pthread_mutex_unlock(&data->main->p_lock);
			break ;
		}
		pthread_mutex_unlock(&data->main->p_lock);
	}
	free(data);
	return (NULL);
}
