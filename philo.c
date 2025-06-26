/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quentin83400 <quentin83400@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 11:29:08 by quentin           #+#    #+#             */
/*   Updated: 2025/06/26 12:20:43 by quentin8340      ###   ########.fr       */
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

void	*philosopher_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->data->num_philos == 1)
		return (NULL);
	if (philo->id % 2 == 0)
		if (!ft_usleep(philo->data->time_to_eat, philo))
			return (NULL);
	if (philo->data->num_philos % 2 != 0 && philo->id == 0)
		if (!ft_usleep(philo->data->time_to_eat, philo))
			return (NULL);
	while (1)
	{
		pthread_mutex_lock(&philo->data->death_mutex);
		if (philo->data->dead)
		{
			pthread_mutex_unlock(&philo->data->death_mutex);
			break ;
		}
		pthread_mutex_unlock(&philo->data->death_mutex);
		if (philo->id % 2 == 0)
		{
			pthread_mutex_lock(philo->right_fork);
			pthread_mutex_lock(&philo->data->death_mutex);
			if (philo->data->dead)
			{
				pthread_mutex_unlock(&philo->data->death_mutex);
                pthread_mutex_unlock(philo->right_fork);
				break ;
			}
			pthread_mutex_unlock(&philo->data->death_mutex);
			print_status(philo, "has taken a fork");
			pthread_mutex_lock(philo->left_fork);
			pthread_mutex_lock(&philo->data->death_mutex);
			if (philo->data->dead)
			{
				pthread_mutex_unlock(&philo->data->death_mutex);
                pthread_mutex_unlock(philo->right_fork);
                pthread_mutex_unlock(philo->left_fork);
				break ;
			}
			pthread_mutex_unlock(&philo->data->death_mutex);
			print_status(philo, "has taken a fork");
		}
		else
		{
			pthread_mutex_lock(philo->left_fork);
			pthread_mutex_lock(&philo->data->death_mutex);
			if (philo->data->dead)
			{
				pthread_mutex_unlock(&philo->data->death_mutex);
                pthread_mutex_unlock(philo->left_fork);
				break ;
			}
			pthread_mutex_unlock(&philo->data->death_mutex);
			print_status(philo, "has taken a fork");
			pthread_mutex_lock(philo->right_fork);
			pthread_mutex_lock(&philo->data->death_mutex);
			if (philo->data->dead)
			{
				pthread_mutex_unlock(&philo->data->death_mutex);
                pthread_mutex_unlock(philo->left_fork);
                pthread_mutex_unlock(philo->right_fork);
				break ;
			}
			pthread_mutex_unlock(&philo->data->death_mutex);
			print_status(philo, "has taken a fork");
		}
		pthread_mutex_lock(&philo->data->death_mutex);
		if (philo->data->dead)
		{
			pthread_mutex_unlock(&philo->data->death_mutex);
			pthread_mutex_unlock(philo->left_fork);
			pthread_mutex_unlock(philo->right_fork);
			break ;
		}
		pthread_mutex_unlock(&philo->data->death_mutex);
		eat(philo);
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_lock(&philo->data->death_mutex);
		if (philo->data->dead)
		{
			pthread_mutex_unlock(&philo->data->death_mutex);
			break ;
		}
		pthread_mutex_unlock(&philo->data->death_mutex);
		print_status(philo, "is sleeping");
		if (!ft_usleep(philo->data->time_to_sleep, philo))
			return (NULL);
		print_status(philo, "is thinking");
		if (philo->data->time_to_eat > philo->data->time_to_sleep)
			if (!ft_usleep(philo->data->time_to_eat
					- philo->data->time_to_sleep, philo))
				return (NULL);
		if (philo->data->num_philos % 2 != 0)
			if (!ft_usleep(philo->data->time_to_eat, philo))
				return (NULL);
	}
	return (NULL);
}
