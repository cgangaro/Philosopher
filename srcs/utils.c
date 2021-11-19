/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgangaro <cgangaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 13:40:28 by cgangaro          #+#    #+#             */
/*   Updated: 2021/11/18 14:01:57 by cgangaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosopher.h"

t_main	*create_struct(int argc, char **argv)
{
	t_main	*main;

	main = malloc(sizeof(t_main));
	main->nb_philo = ft_atoi(argv[1]);
	main->time_to_die = ft_atoi(argv[2]);
	main->time_to_eat = ft_atoi(argv[3]);
	main->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		main->nb_each_meal_in = ft_atoi(argv[5]);
	else
		main->nb_each_meal_in = -1;
	main->start = 0;
	main->die = 0;
	main->all_nb_meal = 0;
	main->philo_die = -1;
	main->time_start = 0;
	main->all_nb_meal = 0;
	pthread_mutex_init(&main->aff, NULL);
	return (main);
}

size_t	ft_strlen(char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

t_philo	*init_philo(t_philo *philo, t_main *main)
{
	int	i;

	i = 0;
	while (i < main->nb_philo)
	{
		pthread_mutex_init(&philo[i].fork, NULL);
		pthread_mutex_init(&philo[i].lock_die, NULL);
		philo = init_philo_2(philo, main, i);
		if (i > 0)
		{
			philo[i].prev_fork = &philo[i - 1].fork;
		}
		i++;
	}
	philo[0].prev_fork = &philo[main->nb_philo - 1].fork;
	return (philo);
}

t_philo	*init_philo_2(t_philo *philo, t_main *main, int i)
{
	philo[i].nb_philo = main->nb_philo;
	philo[i].id = i;
	philo[i].die = 0;
	philo[i].time_start = ft_get_time();
	philo[i].main = main;
	philo[i].end = 0;
	philo[i].nb_meal = 0;
	philo[i].start = ft_get_time();
	return (philo);
}

void	clean_philo(t_philo *philo, t_main *main, pthread_t *threads)
{
	free(philo);
	free(main);
	free(threads);
}
