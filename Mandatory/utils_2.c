/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zvakil <zvakil@student.42abudhabi.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 15:11:54 by zvakil            #+#    #+#             */
/*   Updated: 2024/05/31 15:12:23 by zvakil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*smart_malloc(size_t size)
{
	void	*temp;

	temp = NULL;
	temp = malloc(size);
	if (temp == NULL)
		exit_mes("Program Failed : Memory Allocatin");
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

// int	not_dead(t_main *main, t_philo *philos)
// {
// 	if (philos == NULL || main->philo_dead == 1)
// 		return (1);
// 	if (philos->eating == 1)
// 		return (not_dead(main, philos->next));
// 	if (current_time(philos) - philos->last_meal >= main->dead_time
// 		&& main->philo_dead != 1)
// 	{
// 		printf("%d %d died\n", current_time(philos), philos->id);
// 		main->philo_dead = 1;
// 		return (not_dead(main, philos->next));
// 	}
// 	return (not_dead(main, philos->next));
// }

int	not_dead(t_main *main, t_philo *philos)
{
	pthread_mutex_lock(&main->p_lock);
	if (current_time(philos) - philos->last_meal > main->dead_time && main->philo_dead != 1)
	{
		printf("%d %d died\n", current_time(philos), philos->id);
		main->philo_dead = 1;
		pthread_mutex_unlock(&main->p_lock);
		return (0);
	}
	else
		pthread_mutex_unlock(&main->p_lock);
	return (1);
}

void	start_time(t_philo *philo)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	philo->start_time = (time.tv_sec * 1000) + (time.tv_usec / 1000);
}

int	current_time(t_philo *philo)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000) - philo->start_time);
}
