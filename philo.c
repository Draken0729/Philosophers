/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quentin <quentin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 11:29:08 by quentin           #+#    #+#             */
/*   Updated: 2025/03/31 13:45:57 by quentin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void eat(t_philo *philo)
{
    pthread_mutex_lock(&philo->data->death_mutex);
    philo->last_meal = get_time();
    pthread_mutex_unlock(&philo->data->death_mutex);

    print_status(philo, "mange 🍽️");
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
        
    while (1)
    {
        pthread_mutex_lock(&philo->data->death_mutex);
        if (philo->data->dead)
        {
            pthread_mutex_unlock(&philo->data->death_mutex);
            break;
        }
        pthread_mutex_unlock(&philo->data->death_mutex);

        if (philo->id == philo->data->num_philos - 1)
        {
            pthread_mutex_lock(philo->right_fork);
            print_status(philo, "a pris la fourchette droite 🍴");
            pthread_mutex_lock(philo->left_fork);
            print_status(philo, "a pris la fourchette gauche 🍴");
        }
        else
        {
            pthread_mutex_lock(philo->left_fork);
            print_status(philo, "a pris la fourchette gauche 🍴");
            pthread_mutex_lock(philo->right_fork);
            print_status(philo, "a pris la fourchette droite 🍴");
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

        print_status(philo, "a pris les deux fourchettes 🍽️");
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

        print_status(philo, "dort 😴");
        usleep(philo->data->time_to_sleep * 1000 - 500);

        print_status(philo, "pense 🤔");
        usleep(1000);
    }
    return NULL;
}

