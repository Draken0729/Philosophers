/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quentin83400 <quentin83400@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 10:36:05 by quentin           #+#    #+#             */
/*   Updated: 2025/06/27 11:26:55 by quentin8340      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	cleanup(t_data *data)
{
	int	i;

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

int	parse_args(int argc, char **argv, t_data *data)
{
	if (argc < 5)
		return (ft_printf("Pas assez d'argument\n"), 1);
	data->num_philos = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
	{
		data->must_eat = ft_atoi(argv[5]);
		if (data->must_eat <= 0)
			return (ft_printf("Paramètres invalides.\n"), 1);
	}
	else
		data->must_eat = -1;
	if (data->num_philos <= 0 || data->time_to_die <= 0
		|| data->time_to_eat <= 0 || data->time_to_sleep <= 0)
		return (ft_printf("Paramètres invalides.\n"), 1);
	return (0);
}

void	start_threads(t_data *data, pthread_t *monitor_thread)
{
	int	i;

	pthread_create(monitor_thread, NULL, monitor, data);
	i = 0;
	while (i < data->num_philos)
	{
		pthread_create(&data->philos[i].thread, NULL, philosopher_routine,
			&data->philos[i]);
		i++;
	}
}

void	join_threads(t_data *data, pthread_t monitor_thread)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		pthread_join(data->philos[i].thread, NULL);
		i++;
	}
	pthread_join(monitor_thread, NULL);
}

int	main(int argc, char **argv)
{
	t_data		data;
	pthread_t	monitor_thread;

	if (parse_args(argc, argv, &data))
		return (1);
	init_mutexes(&data);
	init_philosophers(&data);
	start_threads(&data, &monitor_thread);
	join_threads(&data, monitor_thread);
	cleanup(&data);
	return (0);
}
