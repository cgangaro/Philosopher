/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgangaro <cgangaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 12:41:07 by cgangaro          #+#    #+#             */
/*   Updated: 2021/11/18 14:18:26 by cgangaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>

typedef struct s_main
{
	int				nb_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_each_meal_in;
	int				start;
	long int		time_start;
	int				id_philo_eat;
	int				die;
	int				all_nb_meal;
	int				philo_die;
	pthread_mutex_t	aff;
}					t_main;

typedef struct s_philo
{
	int				id;
	int				nb_philo;
	pthread_mutex_t	lock_die;
	pthread_mutex_t	fork;
	pthread_mutex_t	*prev_fork;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				time_to_think;
	long int		start;
	int				nb_meal;
	int				die;
	int				end;
	long int		time_start;
	t_main			*main;
}				t_philo;

int			ft_atoi(const char *str);
size_t		ft_strlen(char *s);

int			parsing(int argc, char **argv);
int			parsing_2(char **argv, int i);
int			parsing_number_or_not(char *str);

t_main		*create_struct(int argc, char **argv);
t_philo		*init_philo(t_philo *philo, t_main *main);
t_philo		*init_philo_2(t_philo *philo, t_main *main, int i);

int			first(t_main *main);

void		*philo_function(void *data);

void		mutex_fork(t_philo *philo);
void		mutex_fork_2(t_philo *philo);
void		ft_eat(t_philo *philo);
void		ft_sleep(long int temp, int time, t_philo *philo);

long int	ft_get_time(void);
void		ft_usleep(long int time);

void		check(t_philo *philo, t_main *main);
int			check_philo(t_philo *philo, t_main *main, int i);
int			check_philo_end(t_philo *philo, t_main *main);

void		clean_philo(t_philo *philo, t_main *main, pthread_t *threads);

void		ft_aff(char *s, int id, pthread_mutex_t	aff, long int time_start);

#endif
