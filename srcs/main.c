/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgangaro <cgangaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 10:20:53 by cgangaro          #+#    #+#             */
/*   Updated: 2021/11/18 14:18:39 by cgangaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosopher.h"

int	main(int argc, char **argv)
{
	t_main	*main;
	int		ret_pars;

	ret_pars = parsing(argc, argv);
	if (ret_pars == -1)
		return (-1);
	if (ret_pars == 1)
		return (0);
	main = create_struct(argc, argv);
	first(main);
	return (0);
}

int	first(t_main *main)
{
	pthread_t	*threads;
	t_philo		*philo;
	int			i;

	threads = malloc(sizeof(pthread_t) * main->nb_philo);
	if (threads == NULL)
		exit (-1);
	philo = malloc(sizeof(t_philo) * main->nb_philo);
	i = 0;
	philo = init_philo(philo, main);
	while (i < main->nb_philo)
	{
		if (pthread_create(&threads[i], NULL, philo_function, &philo[i]))
		{
			printf("error\n");
			exit (-1);
		}
		i++;
	}
	check(philo, main);
	clean_philo(philo, main, threads);
	return (0);
}

void	check(t_philo *philo, t_main *main)
{
	int	i;

	main->start = 1;
	main->time_start = ft_get_time();
	while (main->die != 1)
	{
		i = 0;
		while (i < main->nb_philo && main->die != 1)
			i = check_philo(philo, main, i);
		if (check_philo_end(philo, main) == 1)
			break ;
	}
	if (main->philo_die > -1)
		ft_aff("is dead", main->philo_die, main->aff, main->time_start);
	else if (main->nb_each_meal_in != -1)
		ft_aff("the philosophers have eaten enough", -1,
			main->aff, main->time_start);
	i = 0;
	while (i < main->nb_philo)
	{
		while (philo[i].end != 1)
			;
		i++;
	}
}

int	check_philo(t_philo *philo, t_main *main, int i)
{
	long int	time;

	pthread_mutex_lock(&philo[i].lock_die);
	time = ft_get_time();
	if (((philo[i].start + main->time_to_die) < time) && philo[i].end != 1)
	{
		main->die = 1;
		main->philo_die = i;
	}
	pthread_mutex_unlock(&philo[i].lock_die);
	i++;
	return (i);
}

int	check_philo_end(t_philo *philo, t_main *main)
{
	int	i;
	int	ok;

	i = 0;
	ok = 1;
	while (i < main->nb_philo && ok == 1)
	{
		if (philo[i].end == 0)
			ok = 0;
		i++;
	}
	return (ok);
}
