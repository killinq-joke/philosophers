/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztouzri <ztouzri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/19 17:25:59 by ztouzri           #+#    #+#             */
/*   Updated: 2021/07/26 09:52:23 by ztouzri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	puterror(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		write(2, &str[i], 1);
		i++;
	}
}

int	isvalidnum(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	argchecker(int ac, char **av)
{
	int	i;

	i = 1;
	while (i < ac)
	{
		if (!isvalidnum(av[i]))
		{
			puterror("Please provide numeric arguments\n");
			exit(0);
		}
		i++;
	}
	return (1);
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
		philos[i].lasteat = infos->begin;
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

unsigned long	gettimestamp(t_philo *philo)
{
	struct timeval	currenttime;
	unsigned long	time;

	gettimeofday(&currenttime, NULL);
	//printf("currentnext == %ld\n", currenttime.tv_sec);
	time = currenttime.tv_sec * 1000 + currenttime.tv_usec / 1000;
	return (time - philo->begin);
}

void	millisleep(unsigned long u)
{
	usleep(u * 1000);
}

void	takeforks(t_philo *philo)
{
	if (!philo->leftforkinuse && !philo->rightforkinuse)
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

unsigned long	gettime(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

long	getstarvetime(unsigned long starttime)
{
	return (gettime() - starttime);
}

void	*waitfordeath(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	printf("lasteat %ld, getstartve %ld\n", philo->lasteat, getstarvetime(philo->lasteat));
	while (getstarvetime(philo->lasteat) < philo->ttd)
		;
	pthread_mutex_unlock(&philo->deathlock);
	pthread_mutex_lock(&philo->deathlock);
	printf("%lu %d died\n", gettimestamp(philo), philo->id);
	exit(0);
	return (0);
}

void	*eating_sleeping(void *arg)
{
	t_philo	philo;

	philo = *(t_philo *)arg;
	printf("%ld \n", getstarvetime(philo.lasteat));
	pthread_create(&philo.deathloop, NULL, &waitfordeath, &philo);
	while (1)
	{
		takeforks(&philo);
		printf("%lu %d is eating\n", gettimestamp(&philo), philo.id);
		philo.lasteat = gettime();
		printf("lasteat %ld\n", philo.lasteat);
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
		usleep(100);
		i++;
	}
	return (1);
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
		// printf("nbphil == %d\nttd == %lu\ntte == %lu\ntts == %lu\nmusteat == %d\n", infos->nbphil, infos->ttd, infos->tte, infos->tts, infos->musteat);
		routine(infos, philos);
		while (1);
	}
	return (0);
}
