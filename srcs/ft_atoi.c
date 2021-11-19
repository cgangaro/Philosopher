/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgangaro <cgangaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 13:48:01 by cgangaro          #+#    #+#             */
/*   Updated: 2021/10/05 12:11:56 by cgangaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosopher.h"

int	ft_annexe2(const char *str, int i)
{
	while (str[i] == '\n' || str[i] == '\r'
		|| str[i] == '\t' || str[i] == '\v'
		|| str[i] == '\f' || str[i] == ' ')
		i++;
	return (i);
}

int	ft_atoi(const char *str)
{
	long long int	val;
	int				i;
	int				neg;

	i = 0;
	val = 0;
	neg = 1;
	i = ft_annexe2(str, i);
	if (str[i] == 45 || str[i] == 43)
	{
		if (str[i] == 45)
			neg *= -1;
		i++;
	}
	while (str[i] >= 48 && str[i] <= 57)
	{
		val = val * 10 + (str[i] - 48);
		if (val > 2147483647 && neg > 0)
			return (-1);
		else if (val > 2147483648 && neg == -1)
			return (-1);
		i++;
	}
	return (val * neg);
}
