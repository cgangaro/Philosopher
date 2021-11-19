/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgangaro <cgangaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 12:06:31 by cgangaro          #+#    #+#             */
/*   Updated: 2021/11/18 13:57:59 by cgangaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosopher.h"

int	parsing(int argc, char **argv)
{
	int	i;

	if (argc < 5 || argc > 6)
	{
		printf("Error: trop ou pas assez de parametres\n");
		return (-1);
	}
	if (ft_atoi(argv[1]) <= 0)
	{
		printf("Error: nb de philo est un INT > 0\n");
		return (-1);
	}
	if (argc == 6 && ft_atoi(argv[5]) == 0)
	{
		printf("The philosopher(s) arrive at the table... and leave\n");
		return (1);
	}
	i = 1;
	while (i < argc)
	{
		if (parsing_2(argv, i) == -1)
			return (-1);
		i++;
	}
	return (0);
}

int	parsing_2(char **argv, int i)
{
	if (parsing_number_or_not(argv[i]) == -1)
	{
		printf("Error: les parametres ne doivent ");
		printf("contenir que des chiffres\n");
		return (-1);
	}
	if (ft_strlen(argv[i]) > 10)
	{
		printf("Error: les parametres ne doivent pas ");
		printf("depasse la range d'un INT\n");
		return (-1);
	}
	if (ft_atoi(argv[i]) < 0)
	{
		printf("Error: les parametres doivent etre ");
		printf("positif et ont pour max 2147483648\n");
		return (-1);
	}
	return (0);
}

int	parsing_number_or_not(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < 48 || str[i] > 57)
			return (-1);
		i++;
	}
	return (0);
}
