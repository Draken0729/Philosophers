/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quentin83400 <quentin83400@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 10:55:55 by quentin           #+#    #+#             */
/*   Updated: 2025/06/26 12:13:59 by quentin8340      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void *monitor(void *arg)
{
    t_data *data = (t_data *)arg;
    int i;

    if(data->num_philos == 1)
    {
        ft_printf("0 1 has taken a fork\n");
        usleep(data->time_to_die * 1000);
        pthread_mutex_lock(&data->death_mutex);
        data->dead = 1;
        pthread_mutex_unlock(&data->death_mutex);
        ft_printf("%d 1 died\n", data->time_to_die);
        return NULL;
    }
    
    while (1)
    {
        i = 0;
        while (i < data->num_philos)
        {
            pthread_mutex_lock(&data->death_mutex);
            if (get_time() - data->philos[i].last_meal > data->time_to_die)
            {
                data->dead = 1;
                print_status(&data->philos[i], "died");
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




