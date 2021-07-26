/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztouzri <ztouzri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/26 11:28:28 by ztouzri           #+#    #+#             */
/*   Updated: 2021/07/26 12:09:18 by ztouzri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*eating_sleeping(void *arg)
{
	t_philo	philo;

	philo = *(t_philo *)arg;
	pthread_create(&philo.deathloop, NULL, &waitfordeath, &philo);
	while (1)
	{
		takeforks(&philo);
		printf("%lu %d is eating\n", gettimestamp(&philo), philo.id);
		*philo.lasteat = gettime();
		millisleep(philo.tte);
		dropforks(&philo);
		printf("%lu %d is sleeping\n", gettimestamp(&philo), philo.id);
		millisleep(philo.tts);
		printf("%lu %d is thinking\n", gettimestamp(&philo), philo.id);
	}
	return (0);
}

int	routine(t_info *infos, t_philo *philos)
{
	int	i;

	i = 0;
	while (i < infos->nbphil)
	{
		pthread_create(&philos[i].th, NULL, &eating_sleeping, &philos[i]);
		pthread_mutex_lock(&philos[i].deathlock);
		pthread_create(&philos[i].deathloop, NULL, &waitfordeath, &philos[i]);
		i++;
	}
	return (1);
}
