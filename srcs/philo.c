/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgangaro <cgangaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 11:54:14 by cgangaro          #+#    #+#             */
/*   Updated: 2021/11/18 14:19:48 by cgangaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosopher.h"

void	*philo_function(void *data)
{
	t_philo	*philo;

	philo = data;
	while (philo->main->start != 1)
		;
	while (philo->main->die != 1)
	{
		ft_eat(philo);
		if (philo->main->die != 1)
		{
			ft_aff("sleep", philo->id, philo->main->aff, philo->time_start);
			ft_usleep(philo->main->time_to_sleep);
			if (philo->main->die != 1)
				ft_aff("think", philo->id, philo->main->aff, philo->time_start);
		}
		if (philo->main->nb_each_meal_in == philo->nb_meal)
			break ;
	}
	philo->end = 1;
	return (data);
}

void	ft_sleep(long int temp, int time, t_philo *philo)
{
	long int	temp2;

	temp2 = ft_get_time();
	while (temp2 < temp + time && philo->main->die != 1)
		temp2 = ft_get_time();
}

void	ft_eat(t_philo *philo)
{
	if (philo->main->die != 1)
	{
		mutex_fork(philo);
		pthread_mutex_lock(&philo->lock_die);
		philo->start = ft_get_time();
		pthread_mutex_unlock(&philo->lock_die);
		if (philo->main->die == 1)
			return ;
		ft_aff("eat", philo->id, philo->main->aff, philo->time_start);
		ft_usleep(philo->main->time_to_eat);
		if (philo->id % 2 == 0)
		{
			pthread_mutex_unlock(&philo->fork);
			if (philo->main->nb_philo > 1)
				pthread_mutex_unlock(philo->prev_fork);
		}
		else
		{
			if (philo->main->nb_philo > 1)
				pthread_mutex_unlock(philo->prev_fork);
			pthread_mutex_unlock(&philo->fork);
		}
		philo->nb_meal++;
	}
}

void	mutex_fork(t_philo *philo)
{
	if (philo->id % 2 == 0 && philo->main->die != 1)
	{
		pthread_mutex_lock(&philo->fork);
		if (philo->main->die == 1)
		{
			pthread_mutex_unlock(&philo->fork);
			return ;
		}
		ft_aff("take fork", philo->id, philo->main->aff, philo->time_start);
		if (philo->main->nb_philo > 1)
		{
			pthread_mutex_lock(philo->prev_fork);
			ft_aff("take second fork", philo->id,
				philo->main->aff, philo->time_start);
		}
		else
			ft_usleep(philo->main->time_to_die + 1);
	}
	else if (philo->main->die != 1)
		mutex_fork_2(philo);
}

void	mutex_fork_2(t_philo *philo)
{
	pthread_mutex_lock(philo->prev_fork);
	if (philo->main->die == 1)
	{
		pthread_mutex_unlock(philo->prev_fork);
		return ;
	}
	ft_aff("take fork", philo->id, philo->main->aff, philo->time_start);
	pthread_mutex_lock(&philo->fork);
	ft_aff("take second fork", philo->id, philo->main->aff, philo->time_start);
}
