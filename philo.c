/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbaret <qbaret@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 11:29:08 by quentin           #+#    #+#             */
/*   Updated: 2025/05/23 11:15:43 by qbaret           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void eat(t_philo *philo)
{
    pthread_mutex_lock(&philo->data->death_mutex);
    philo->last_meal = get_time();
    pthread_mutex_unlock(&philo->data->death_mutex);

    print_status(philo, "is eating");
    usleep(philo->data->time_to_eat * 1000 - 500);

    pthread_mutex_lock(&philo->data->death_mutex);
    philo->meals_eaten++;
    if (philo->data->must_eat > 0 && philo->meals_eaten >= philo->data->must_eat)
    {
        philo->data->finished++;
    }
    pthread_mutex_unlock(&philo->data->death_mutex);
}


void *philosopher_routine(void *arg)
{
    t_philo *philo = (t_philo *)arg;

    if (philo->id % 2 == 0)
    {
        usleep(philo->data->time_to_eat);
    }
    
    if (philo->id % 2 != 0 && philo->id == 0)
    {
        usleep(philo->data->time_to_eat);
    }
    
    while (1)
    {
        pthread_mutex_lock(&philo->data->death_mutex);
        if (philo->data->dead)
        {
            pthread_mutex_unlock(&philo->data->death_mutex);
            break;
        }
        pthread_mutex_unlock(&philo->data->death_mutex);

        if (philo->id % 2 == 0)
        {
            pthread_mutex_lock(philo->right_fork);
            print_status(philo, "has taken a fork");
            pthread_mutex_lock(philo->left_fork);
            print_status(philo, "has taken a fork");
        }
        else
        {
            pthread_mutex_lock(philo->left_fork);
            print_status(philo, "has taken a fork");
            pthread_mutex_lock(philo->right_fork);
            print_status(philo, "has taken a fork");
        }

        pthread_mutex_lock(&philo->data->death_mutex);
        if (philo->data->dead)
        {
            pthread_mutex_unlock(&philo->data->death_mutex);
            pthread_mutex_unlock(philo->left_fork);
            pthread_mutex_unlock(philo->right_fork);
            break;
        }
        pthread_mutex_unlock(&philo->data->death_mutex);

        eat(philo);

        pthread_mutex_unlock(philo->left_fork);
        pthread_mutex_unlock(philo->right_fork);

        pthread_mutex_lock(&philo->data->death_mutex);
        if (philo->data->dead)
        {
            pthread_mutex_unlock(&philo->data->death_mutex);
            break;
        }
        pthread_mutex_unlock(&philo->data->death_mutex);

        print_status(philo, "is sleeping");
        usleep(philo->data->time_to_sleep * 1000 - 500);

        print_status(philo, "is thinking");
        usleep(1000);
    }
    return NULL;
}

