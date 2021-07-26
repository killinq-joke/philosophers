/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztouzri <ztouzri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/19 18:23:52 by ztouzri           #+#    #+#             */
/*   Updated: 2021/07/26 11:21:17 by ztouzri          ###   ########.fr       */
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
	i = 0;
	while (i < infos->nbphil)
	{
		philos[i].id = i + 1;
		if (i == 0)
		{
			philos[i].leftfork = &forks[infos->nbphil - 1];
			philos[i].leftforkinuse = ft_calloc(1, sizeof (int));
			philos[i].leftforkinuse = &forksinuse[infos->nbphil - 1];
		}
		else
		{
			philos[i].leftfork = &forks[i - 1];
			philos[i].leftforkinuse = ft_calloc(1, sizeof (int));
			philos[i].leftforkinuse = &forksinuse[i - 1];
		}
		philos[i].rightfork = &forks[i];
		philos[i].rightforkinuse = ft_calloc(1, sizeof (int));
		philos[i].rightforkinuse = &forksinuse[i];
		i++;
	}
	return (philos);
}
