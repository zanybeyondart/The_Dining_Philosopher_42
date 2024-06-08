/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zvakil <zvakil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 11:49:30 by zvakil            #+#    #+#             */
/*   Updated: 2024/06/09 00:26:30 by zvakil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eat_mode(t_main *main, t_philo *philo)
{
	int	time;

	if (!not_dead(main, philo))
		return ;
	pthread_mutex_lock(&main->p_lock);
	printf("%d %d is eating \n", current_time(main), philo->id);
	pthread_mutex_unlock(&main->p_lock);
	philo->eating = 1;
	philo->last_meal = current_time(main);
	time = current_time(main);
	while (1)
	{
		if (current_time(main) - time >= main->eat_time)
			break ;
		usleep(10);
	}
	philo->eating = 0;
	philo->meals++;
	pthread_mutex_lock(philo->next_mutex);
	philo->next_fork[1] = 0;
	pthread_mutex_unlock(philo->next_mutex);
	pthread_mutex_lock(philo->my_mutex);
	philo->my_fork[1] = 0;
	pthread_mutex_unlock(philo->my_mutex);
	sleeping(philo, main);
}

void	pick_fork(pthread_mutex_t *mtx, int *fork, t_main *main, t_philo *philo)
{
	if (!mtx || !fork)
		return ;
	while (1)
	{
		pthread_mutex_lock(mtx);
		if (fork[1] == 0)
		{
			if (!not_dead(main, philo))
			{
				pthread_mutex_unlock(mtx);
				break ;
			}
			fork[1] = 1;
			printf("%d %d picked up a fork \n", current_time(main), philo->id);
			pthread_mutex_unlock(mtx);
			break ;
		}
		if (!not_dead(main, philo))
		{
			pthread_mutex_unlock(mtx);
			break ;
		}
		pthread_mutex_unlock(mtx);
		usleep(10);
	}
}

int	eating(t_philo *philo, t_main *main)
{
	if (philo->id % 2 != 0)
	{
		pick_fork(philo->next_mutex, philo->next_fork, main, philo);
		pick_fork(philo->my_mutex, philo->my_fork, main, philo);
	}
	else
	{
		usleep(500);
		pick_fork(philo->next_mutex, philo->next_fork, main, philo);
		pick_fork(philo->my_mutex, philo->my_fork, main, philo);
	}
	if (philo->my_fork && philo->next_fork)
		eat_mode(main, philo);
	return (1);
}

void	sleeping(t_philo *philo, t_main *main)
{
	int	time;

	pthread_mutex_lock(&main->p_lock);
	if (main->philo_dead != 1)
	{
		printf("%d %d is sleeping\n", current_time(main), philo->id);
		pthread_mutex_unlock(&main->p_lock);
		time = current_time(main);
		while (not_dead(main, philo))
		{
			if (current_time(main) - time >= main->sleep_time)
				break ;
			usleep(10);
		}
	}
	else
		pthread_mutex_unlock(&main->p_lock);
	thinking(philo, main);
}

void	*function(void *ag)
{
	t_thread		*data;

	data = (t_thread *)ag;
	while (not_dead(data->main, data->philo)
		&& data->main->meals != data->philo->meals)
		eating(data->philo, data->main);
	free(data);
	return (NULL);
}
