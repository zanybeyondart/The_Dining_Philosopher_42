/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zvakil <zvakil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 11:52:56 by zvakil            #+#    #+#             */
/*   Updated: 2024/06/08 22:33:20 by zvakil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_program(t_philo *philo)
{
	if (philo->next != NULL)
		free_program(philo->next);
	free(philo->my_fork);
	pthread_mutex_destroy(philo->my_mutex);
	free(philo->my_mutex);
	free(philo);
}

void	thinking(t_philo *philo, t_main *main)
{
	if (not_dead(main, philo))
	{
		pthread_mutex_lock(&main->p_lock);
		printf("%d %d is thinking\n", current_time(main), philo->id);
		pthread_mutex_unlock(&main->p_lock);
	}
}

void	add_to_list(t_philo *philo, int index)
{
	t_philo		*temp;

	temp = smart_malloc(sizeof(t_philo));
	temp->my_fork = smart_malloc(sizeof(int) * 2);
	temp->my_mutex = smart_malloc(sizeof(pthread_mutex_t));
	temp->next_mutex = NULL;
	temp->my_fork[0] = index;
	temp->eating = 0;
	temp->last_meal = 0;
	temp->my_fork[1] = 0;
	temp->start_time = 0;
	temp->start_time = 0;
	pthread_mutex_init(temp->my_mutex, NULL);
	temp->next_fork = NULL;
	temp->next = NULL;
	temp->id = index;
	while (philo->next != NULL)
		philo = philo->next;
	philo->next = temp;
	return ;
}

t_philo	*init_thread(int philos)
{
	t_philo			*philo;
	int				i;

	i = 1;
	philo = smart_malloc(sizeof(t_philo));
	philo->my_fork = smart_malloc(sizeof(int) * 2);
	philo->my_mutex = smart_malloc(sizeof(pthread_mutex_t));
	philo->next_mutex = NULL;
	philo->my_fork[0] = 1;
	philo->my_fork[1] = 0;
	philo->eating = 0;
	philo->last_meal = 0;
	philo->meals = 0;
	philo->start_time = 0;
	pthread_mutex_init(philo->my_mutex, NULL);
	philo->next_fork = NULL;
	philo->next = NULL;
	philo->id = i++;
	while (i <= philos)
	{
		add_to_list(philo, i);
		i++;
	}
	return (philo);
}
