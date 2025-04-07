/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quentin <quentin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 10:55:55 by quentin           #+#    #+#             */
/*   Updated: 2025/03/31 14:00:45 by quentin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void *monitor(void *arg)
{
    t_data *data = (t_data *)arg;
    int i;
    
    while (1)
    {
        i = 0;
        while (i < data->num_philos)
        {
            pthread_mutex_lock(&data->death_mutex);
            if (get_time() - data->philos[i].last_meal > data->time_to_die)
            {
                data->dead = 1;
                printf("⚠️ Philosophe %d est mort\n", data->philos[i].id);
                pthread_mutex_unlock(&data->death_mutex);
                return NULL;
            }

            if (data->must_eat > 0 && data->finished >= data->num_philos)
            {
                printf("✅ Tous les philosophes ont fini de manger !\n");
                data->dead = 1;
                pthread_mutex_unlock(&data->death_mutex);
                return NULL;
            }
            pthread_mutex_unlock(&data->death_mutex);
            i++;
        }
        usleep(1000);
    }
    return NULL;
}




