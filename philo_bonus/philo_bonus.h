/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouhaga <abouhaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 15:21:29 by abouhaga          #+#    #+#             */
/*   Updated: 2022/09/11 11:10:43 by abouhaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <sys/types.h>
# include <signal.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/time.h>
# include <pthread.h>
# include <semaphore.h>
# include <stdbool.h>
# include <fcntl.h>
# include <sys/wait.h>

typedef struct s_philo
{
	pid_t	pid;
	int		nb_philo;
	int		index;
	long	init_time;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		nb_must_eat;
	bool	is_eating;
	bool	done_eating;
	sem_t	*bns_sem;
	sem_t   *message;
	sem_t   *forks;
	long	last_meal;
	int		number_of_times;
 } t_philo;

void	create_process(t_philo *philo);
void	ft_usleep(int ms_time);
int		ft_atoi(const char *str);
long	get_current_time(void);
void	smart_print(char *message, t_philo *philo, int p_id);

#endif