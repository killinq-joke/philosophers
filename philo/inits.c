/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztouzri <ztouzri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/19 18:23:52 by ztouzri           #+#    #+#             */
/*   Updated: 2021/09/19 01:07:54 by ztouzri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_info	*init_infos(char **av)
{
	t_info			*infos;
	struct timeval	currenttime;

	gettimeofday(&currenttime, NULL);
	infos = ft_calloc(1, sizeof (t_info));
	infos->nbphil = ft_atol(av[1]);
	infos->ttd = ft_atol(av[2]);
	infos->tte = ft_atol(av[3]);
	infos->tts = ft_atol(av[4]);
	infos->musteat = -1;
	infos->begin = currenttime.tv_sec * 1000 + currenttime.tv_usec / 1000;
	return (infos);
}

void	init_philos1(t_info *inf, t_philo *philos, int *f, pthread_mutex_t *fs)
{
	int	i;

	i = 0;
	while (i < inf->nbphil)
	{
		philos[i].id = i + 1;
		if (i == 0)
		{
			philos[i].leftfork = &fs[inf->nbphil - 1];
			philos[i].leftforkinuse = ft_calloc(1, sizeof (int));
			philos[i].leftforkinuse = &f[inf->nbphil - 1];
		}
		else
		{
			philos[i].leftfork = &fs[i - 1];
			philos[i].leftforkinuse = ft_calloc(1, sizeof (int));
			philos[i].leftforkinuse = &f[i - 1];
		}
		philos[i].rightfork = &fs[i];
		philos[i].rightforkinuse = ft_calloc(1, sizeof (int));
		philos[i].rightforkinuse = &f[i];
		i++;
	}
}

t_philo	*init_philos(t_info *infos)
{
	t_philo			*philos;
	pthread_mutex_t	*forks;
	int				*forksinuse;
	int				i;

	philos = ft_calloc(infos->nbphil, sizeof (t_philo));
	forks = ft_calloc(infos->nbphil, sizeof (pthread_mutex_t));
	forksinuse = ft_calloc(infos->nbphil, sizeof (int));
	i = 0;
	while (i < infos->nbphil)
	{
		pthread_mutex_init(&forks[i], NULL);
		philos[i].ttd = infos->ttd;
		philos[i].tte = infos->tte;
		philos[i].tts = infos->tts;
		philos[i].musteat = infos->musteat;
		philos[i].begin = infos->begin;
		philos[i].lasteat = &infos->begin;
		pthread_join(philos[i].th, NULL);
		i++;
	}
	init_philos1(infos, philos, forksinuse, forks);
	return (philos);
}
