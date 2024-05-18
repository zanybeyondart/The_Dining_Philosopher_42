/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zvakil <zvakil@student.42abudhabi.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 11:53:25 by zvakil            #+#    #+#             */
/*   Updated: 2024/05/12 17:21:08 by zvakil           ###   ########.fr       */
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
	int					id;
	int					*my_fork;
	int					*next_fork;
	pthread_mutex_t		*my_mutex;
	pthread_mutex_t		*next_mutex;
	int					last_meal;
	int					start_time;
	int					eating;
	struct s_philo		*next;
}	t_philo;

typedef struct s_main
{
	t_philo				*philos;
	int					eat_time;
	int					current_time;
	int					sleep_time;
	int					dead_time;
	int					philo_dead;
	int					start_time;
	pthread_mutex_t		p_lock;
	pthread_t			thread;
}	t_main;

typedef struct s_thread
{
	t_philo				*philo;
	t_main				*main;
	struct s_thread		*next;
}	t_thread;

void		check_arguments(int ac, char **av);
void		exit_mes(char *mes);
void		*monitor(void *ag);
void		check_if_invalid(char *av);
void		*smart_malloc(size_t size);
void		free_program(t_philo *philo);
void		thread_create(t_philo *philos);
void		*function(void *ag);
void		add_to_list(t_philo *philo, int index);
void		assign_forks(t_philo *philo, int *first_fork, pthread_mutex_t *first_m);
void		*function(void *ag);
void		sleeping(t_philo *philo, int start_time, t_main *main);
void		thinking(t_philo *philo, int start_time, t_main *main);
void		eating(t_philo *philo, int start_time, t_main *main);
int			magic_time(struct timeval time_main);
int			not_dead(t_main *main, t_philo *philos);
int			current_time(t_philo *philo);
void		start_time(t_philo *philo);
t_philo		*init_thread(int philos);

#endif