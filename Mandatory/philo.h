/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zvakil <zvakil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 11:53:25 by zvakil            #+#    #+#             */
/*   Updated: 2024/06/08 22:40:07 by zvakil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <strings.h>
# include <sys/time.h>

typedef struct s_philo
{
	pthread_t			thread;
	pthread_mutex_t		*my_mutex;
	pthread_mutex_t		*next_mutex;
	int					id;
	int					*my_fork;
	int					*next_fork;
	int					last_meal;
	int					start_time;
	int					eating;
	int					meals;
	struct s_philo		*next;
}	t_philo;

typedef struct s_main
{
	t_philo				*philos;
	pthread_mutex_t		p_lock;
	int					eat_time;
	int					current_time;
	int					sleep_time;
	int					dead_time;
	int					philo_dead;
	int					start_time;
	int					meals;
	pthread_t			thread;
}	t_main;

typedef struct s_thread
{
	t_philo				*philo;
	t_main				*main;
	struct s_thread		*next;
}	t_thread;

int			check_arguments(int ac, char **av);
int			ft_atoi(const char *str);
void		exit_mes(char *mes);
void		*smart_malloc(size_t size);
t_philo		*init_thread(int philos);
void		add_to_list(t_philo *philo, int index);
void		assign_forks(t_philo *philo, int *fork, pthread_mutex_t *mutex);
void		create_threads(t_main *main);
void		threader(t_philo *current_philo, t_main *main);
void		*function(void *ag);
int			not_dead(t_main *main, t_philo *philos);
int			current_time(t_main *main);
int			eating(t_philo *philo, t_main *main);
void		join_threads(t_philo *philos);
void		free_program(t_philo *philo);
void		thread_create(t_philo *philos);
void		sleeping(t_philo *philo, t_main *main);
int			not_dead(t_main *main, t_philo *philos);
int			current_time(t_main *main);
void		start_time(t_philo *philo);
void		thinking(t_philo *philo, t_main *main);

#endif