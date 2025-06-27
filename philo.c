/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quentin83400 <quentin83400@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 11:29:08 by quentin           #+#    #+#             */
/*   Updated: 2025/06/27 11:26:48 by quentin8340      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	is_dead(t_philo *philo)
{
	bool	ret;

	pthread_mutex_lock(&philo->data->death_mutex);
	ret = philo->data->dead;
	pthread_mutex_unlock(&philo->data->death_mutex);
	return (ret);
}

void	wait_start(t_philo *philo)
{
	if (philo->id % 2 == 0)
		ft_usleep(philo->data->time_to_eat, philo);
	else if (philo->data->num_philos % 2 != 0 && philo->id == 0)
		ft_usleep(philo->data->time_to_eat, philo);
}

bool	take_forks(t_philo *philo)
{
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
	return (!is_dead(philo));
}

void	drop_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	*philosopher_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->data->num_philos == 1)
		return (NULL);
	wait_start(philo);
	while (!is_dead(philo))
	{
		if (!take_forks(philo))
			break ;
		if (is_dead(philo))
		{
			drop_forks(philo);
			break ;
		}
		eat(philo);
		if (is_dead(philo))
		{
			drop_forks(philo);
			break ;
		}
		drop_forks(philo);
		if (is_dead(philo))
			break ;
		if (!do_sleep_and_think(philo))
			break ;
	}
	return (NULL);
}
