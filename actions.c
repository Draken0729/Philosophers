/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quentin83400 <quentin83400@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 10:55:55 by quentin           #+#    #+#             */
/*   Updated: 2025/06/27 10:06:57 by quentin8340      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->death_mutex);
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->data->death_mutex);
	print_status(philo, "is eating");
	if (!ft_usleep(philo->data->time_to_eat, philo))
		return ;
	pthread_mutex_lock(&philo->data->death_mutex);
	philo->meals_eaten++;
	if (philo->data->must_eat > 0
		&& philo->meals_eaten >= philo->data->must_eat)
	{
		philo->data->finished++;
	}
	pthread_mutex_unlock(&philo->data->death_mutex);
}

bool	do_sleep_and_think(t_philo *philo)
{
	int	diff;

	print_status(philo, "is sleeping");
	if (!ft_usleep(philo->data->time_to_sleep, philo))
		return (false);
	print_status(philo, "is thinking");
	if (philo->data->time_to_eat > philo->data->time_to_sleep)
	{
		diff = philo->data->time_to_eat - philo->data->time_to_sleep;
		if (!ft_usleep(diff, philo))
			return (false);
	}
	if (philo->data->num_philos % 2 != 0)
		if (!ft_usleep(philo->data->time_to_eat, philo))
			return (false);
	return (true);
}

void	handle_one_philo(t_data *data)
{
	ft_printf("0 1 has taken a fork\n");
	usleep(data->time_to_die * 1000);
	pthread_mutex_lock(&data->death_mutex);
	data->dead = 1;
	pthread_mutex_unlock(&data->death_mutex);
	ft_printf("%d 1 died\n", data->time_to_die);
}

int	check_death_or_full(t_data *data, int i)
{
	pthread_mutex_lock(&data->death_mutex);
	if (get_time() - data->philos[i].last_meal > data->time_to_die)
	{
		data->dead = 1;
		print_status(&data->philos[i], "died");
		pthread_mutex_unlock(&data->death_mutex);
		return (1);
	}
	if (data->must_eat > 0 && data->finished >= data->num_philos)
	{
		printf("All philo finished eat !\n");
		data->dead = 1;
		pthread_mutex_unlock(&data->death_mutex);
		return (1);
	}
	pthread_mutex_unlock(&data->death_mutex);
	return (0);
}

void	*monitor(void *arg)
{
	t_data	*data;
	int		i;

	data = (t_data *)arg;
	if (data->num_philos == 1)
	{
		handle_one_philo(data);
		return (NULL);
	}
	while (1)
	{
		i = 0;
		while (i < data->num_philos)
		{
			if (check_death_or_full(data, i))
				return (NULL);
			i++;
		}
		usleep(1000);
	}
	return (NULL);
}
