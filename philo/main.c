/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztouzri <ztouzri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/19 17:25:59 by ztouzri           #+#    #+#             */
/*   Updated: 2021/09/19 12:14:05 by ztouzri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_ender	g_ender;

/*
** usage d'une global pour checker si un philosophe est mort.
** si oui, n'afficher plus rien
*/

void	takeforks(t_philo *philo)
{
	while (!philo->leftforkinuse && !philo->rightforkinuse)
	{
		pthread_mutex_lock(philo->leftfork);
		printf("%lu %d has taken a fork\n", gettimestamp(philo), philo->id);
		*philo->leftforkinuse = 1;
		pthread_mutex_lock(philo->rightfork);
		printf("%lu %d has taken a fork\n", gettimestamp(philo), philo->id);
		*philo->rightforkinuse = 1;
	}
}

void	dropforks(t_philo *philo)
{
	pthread_mutex_unlock(philo->leftfork);
	*philo->leftforkinuse = 0;
	printf("%lu %d dropped a fork\n", gettimestamp(philo), philo->id);
	pthread_mutex_unlock(philo->rightfork);
	*philo->rightforkinuse = 0;
	printf("%lu %d dropped a fork\n", gettimestamp(philo), philo->id);
}

void	*waitfordeath(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (getstarvetime(*philo->lasteat) < philo->ttd)
		usleep(100);
	pthread_mutex_unlock(&philo->deathlock);
	pthread_mutex_lock(&philo->deathlock);
	if (!g_ender.end)
	{
		pthread_mutex_lock(&g_ender.ender);
		printf("%lu %d died\n", gettimestamp(philo), philo->id);
		g_ender.end = 1;
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_info		*infos;
	t_philo		*philos;

	if (ac != 5 && ac != 6)
		puterror("Please provide the correct number of arguments\n");
	else
	{
		argchecker(ac, av);
		infos = init_infos(av);
		if (ac == 6)
			infos->musteat = ft_atol(av[5]);
		if (infos->nbphil < 1)
			return (0);
		philos = init_philos(infos);
		g_ender.end = 0;
		pthread_mutex_init(&g_ender.ender, NULL);
		routine(infos, philos);
		while (!g_ender.end)
			;
	}
	return (0);
}
