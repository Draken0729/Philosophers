/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quentin83400 <quentin83400@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 10:45:14 by quentin           #+#    #+#             */
/*   Updated: 2025/07/02 13:50:54 by quentin8340      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	wait_start(t_philo *philo)
{
	if (philo->id % 2 == 0)
		ft_usleep(philo->data->time_to_eat, philo);
	else if (philo->data->num_philos % 2 != 0 && philo->id == 0)
		ft_usleep(philo->data->time_to_eat, philo);
}

void	init_mutexes(t_data *data)
{
	int	i;

	i = 0;
	data->forks = malloc(sizeof(pthread_mutex_t) * data->num_philos);
	while (i < data->num_philos)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		i++;
	}
	pthread_mutex_init(&data->print_mutex, NULL);
	pthread_mutex_init(&data->death_mutex, NULL);
}

void	init_philosophers(t_data *data)
{
	int	i;

	i = 0;
	data->philos = malloc(sizeof(t_philo) * data->num_philos);
	data->start_time = get_time();
	data->dead = 0;
	data->finished = 0;
	while (i < data->num_philos)
	{
		data->philos[i].id = i;
		data->philos[i].left_fork = &data->forks[i];
		data->philos[i].right_fork = &data->forks[(i + 1) % data->num_philos];
		data->philos[i].last_meal = get_time();
		data->philos[i].data = data;
		i++;
	}
}
