/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbaret <qbaret@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 11:29:08 by quentin           #+#    #+#             */
/*   Updated: 2025/07/03 10:47:58 by qbaret           ###   ########.fr       */
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
	if(philo->id % 2 == 0)
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
	}
	else
	{
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
	}
}

static bool	check_and_drop_if_dead(t_philo *philo)
{
	if (is_dead(philo))
	{
		drop_forks(philo);
		return (true);
	}
	return (false);
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
		if (!take_forks(philo) || check_and_drop_if_dead(philo))
			break ;
		eat(philo);
		if (check_and_drop_if_dead(philo))
			break ;
		drop_forks(philo);
		if (check_and_drop_if_dead(philo) || !do_sleep_and_think(philo))
			break ;
	}
	return (NULL);
}
