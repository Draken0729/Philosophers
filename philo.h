/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbaret <qbaret@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 10:36:02 by quentin           #+#    #+#             */
/*   Updated: 2025/05/23 13:05:40 by qbaret           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "ft_printf/ft_printf.h"
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct s_data t_data;

typedef struct s_philo
{
	int				id;
	int is_dead;
    int meals_eaten;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t mutex;
    long long last_meal;
	t_data *data;
}					t_philo;

typedef struct s_data
{
    int num_philos;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int must_eat;
    int dead;
    int finished;
    pthread_mutex_t *forks;
    pthread_mutex_t print_mutex;
    pthread_mutex_t death_mutex;
    long long start_time;
    t_philo *philos;
} t_data;

long long get_time(void);
void print_status(t_philo *philo, char *status);
void init_mutexes(t_data *data);
void init_philosophers(t_data *data);
void *philosopher_routine(void *arg);
void *monitor(void *arg);
void cleanup(t_data *data);
int	ft_atoi(const char *nptr);

#endif