/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zvakil <zvakil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 15:11:54 by zvakil            #+#    #+#             */
/*   Updated: 2024/06/08 22:33:04 by zvakil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*smart_malloc(size_t size)
{
	void	*temp;

	temp = NULL;
	temp = malloc(size);
	if (temp == NULL)
		exit_mes("Program Failed : Memory Allocation");
	return (temp);
}

void	assign_forks(t_philo *philo, int *first_fork, pthread_mutex_t *first_m)
{
	static int	i;

	if (philo->next && i == 0)
	{
		i++;
		philo->next_fork = philo->next->my_fork;
		philo->next_mutex = philo->next->my_mutex;
		assign_forks(philo->next, philo->my_fork, philo->my_mutex);
	}
	else if (philo->next)
	{
		philo->next_fork = philo->next->my_fork;
		philo->next_mutex = philo->next->my_mutex;
		assign_forks(philo->next, first_fork, first_m);
	}
	else if (philo->id > 0)
	{
		philo->next_fork = first_fork;
		philo->next_mutex = first_m;
	}
}

int	not_dead(t_main *main, t_philo *philos)
{
	int	current;

	pthread_mutex_lock(&main->p_lock);
	current = current_time(main);
	if (main->philo_dead == 1)
	{
		pthread_mutex_unlock(&main->p_lock);
		return (0);
	}
	if (current - philos->last_meal >= main->dead_time && main->philo_dead != 1)
	{
		printf("%d %d died\n", current, philos->id);
		main->philo_dead = 1;
		pthread_mutex_unlock(&main->p_lock);
		return (0);
	}
	pthread_mutex_unlock(&main->p_lock);
	return (1);
}


void	start_time(t_philo *philo)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	philo->start_time = (time.tv_sec * 1000) + (time.tv_usec / 1000);
}

int	current_time(t_main *main)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000) - main->start_time);
}
