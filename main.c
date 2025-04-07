/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quentin <quentin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 10:36:05 by quentin           #+#    #+#             */
/*   Updated: 2025/03/31 11:30:16 by quentin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void cleanup(t_data *data)
{
	int i;
	
	i = 0;
    while (i < data->num_philos)
	{
        pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
    pthread_mutex_destroy(&data->print_mutex);
    pthread_mutex_destroy(&data->death_mutex);
    free(data->forks);
    free(data->philos);
}

int main(int argc, char **argv)
{
	int i;
    if (argc <= 3)
	{
        return (ft_printf("Pas assez d'argument\n"), 1);
	}
	t_data data;
    data.num_philos = ft_atoi(argv[1]);
    data.time_to_die = ft_atoi(argv[2]);
	data.time_to_eat = ft_atoi(argv[3]);
	data.time_to_sleep = ft_atoi(argv[4]);
	if(argc == 6)
		data.must_eat = ft_atoi(argv[5]);
	else
		data.must_eat = -1;
	if (data.num_philos <= 0 || data.time_to_die <= 0 || data.time_to_eat <= 0 || data.time_to_sleep <= 0)
        return (ft_printf("Paramètres invalides.\n"), 1);
	init_mutexes(&data);
    init_philosophers(&data);
	pthread_t monitor_thread;
    pthread_create(&monitor_thread, NULL, monitor, &data);
	i = 0;
	while(i < data.num_philos)
	{
        pthread_create(&data.philos[i].thread, NULL, philosopher_routine, &data.philos[i]);
		i++;
	}
	i = 0;
	while(i < data.num_philos)
	{
        pthread_join(data.philos[i].thread, NULL);
		i++;
	}
	pthread_join(monitor_thread, NULL);
	cleanup(&data);
	return 0;
}
