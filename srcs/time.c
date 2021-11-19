/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgangaro <cgangaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 13:44:04 by cgangaro          #+#    #+#             */
/*   Updated: 2021/11/18 14:19:06 by cgangaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosopher.h"

long int	ft_get_time(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

void	ft_usleep(long int time)
{
	long int	start;

	start = ft_get_time();
	while (ft_get_time() - start < (time))
		usleep(50);
}

void	ft_aff(char *s, int id, pthread_mutex_t	aff, long int time_start)
{
	pthread_mutex_lock(&aff);
	if (id >= 0)
		printf("%ldms : Philo %d %s\n", ft_get_time() - time_start, id + 1, s);
	else
		printf("%ldms : %s\n", ft_get_time() - time_start, s);
	pthread_mutex_unlock(&aff);
}
