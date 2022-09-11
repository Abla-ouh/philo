/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouhaga <abouhaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 14:46:17 by abouhaga          #+#    #+#             */
/*   Updated: 2022/09/11 10:55:38 by abouhaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	check_number(char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (str[i] < '0' || str[i] > '9')
            return (0);
        i++;
    }
    return (1);
}

int check_args(char **av)
{
    int i;
    
    i = 1;
    while(av[i])
    {
        if (check_number(av[i]) == 0)
            return (0);
    	i++;
    }
    return(1);
}

t_philo *init_data(char **av)
{
	int i;
    t_philo *philos;
    
	i = 1;
	philos = malloc(sizeof(t_philo) * ft_atoi(av[1]));
	philos[0].nb_philo = ft_atoi(av[1]);
    sem_unlink("forks");
    philos[0].forks = sem_open("forks", O_CREAT, 0644, philos->nb_philo);
    if (philos[0].forks == SEM_FAILED)
    {
        printf("Error: sem_open failed\n");
        exit(1);
    }
    sem_unlink("message");
    philos[0].message = sem_open("message", O_CREAT, 0644, 1);
    if (philos[0].message == SEM_FAILED)
    {
        printf("Error: sem_open failed\n");
        exit(1);
    }
    sem_unlink("bns_sem");
    philos[0].bns_sem = sem_open("bns_sem", O_CREAT, 0644, 1);
	philos[0].time_to_die = ft_atoi(av[2]);
	philos[0].time_to_eat = ft_atoi(av[3]);
	philos[0].time_to_sleep = ft_atoi(av[4]);
	if(av[5])
		philos->nb_must_eat = ft_atoi(av[5]);
	else
		philos->nb_must_eat = -1;
	if (philos[0].nb_philo < 0 || philos[0].time_to_die < 0
		|| philos[0].time_to_eat < 0|| philos[0].time_to_sleep < 0)
			return (0);
	while(i < philos->nb_philo)
	{
        philos[i].forks = philos->forks;
        philos[i].message = philos->message;
        philos[i].nb_philo = philos->nb_philo;
		philos[i].time_to_sleep = philos->time_to_sleep;
		philos[i].time_to_eat = philos->time_to_eat;
		philos[i].time_to_die = philos->time_to_die;
		philos[i].nb_must_eat = philos->nb_must_eat;
		i++;
	}
	philos->done_eating = 0;
	return (philos);
}

void    kill_left(t_philo *philo)
{
    int i;

    i = 0;
    while(i < philo[i].nb_philo)
    {
        kill(philo[i].pid, SIGKILL);
        i++;
    }
}

int main(int ac, char **av)
{
	t_philo *philos;
    int status;
    int reswait;;

    if (ac == 5 || ac == 6)
    {
        status = 0;
        reswait = 0;
        if (!check_args(av))
			return(printf("Error: invalid arguments\n"));
        philos = init_data(av);
		if (!philos)
			return(printf("Error\n"));
        create_process(philos);
        while (reswait != -1 && status == 0)  
        {
           reswait = waitpid(-1, &status, 0);
        }
        if (status != 0)
            kill_left(philos);
        sem_close(philos->message);
        sem_close(philos->forks);
    }
    else
		return (printf("invalid arguments\n"));
    return (0);
}