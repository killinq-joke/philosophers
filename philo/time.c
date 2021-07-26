/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztouzri <ztouzri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/26 11:23:44 by ztouzri           #+#    #+#             */
/*   Updated: 2021/07/26 11:30:14 by ztouzri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

unsigned long	gettimestamp(t_philo *philo)
{
	struct timeval	currenttime;
	unsigned long	time;

	gettimeofday(&currenttime, NULL);
	time = currenttime.tv_sec * 1000 + currenttime.tv_usec / 1000;
	return (time - philo->begin);
}

void	millisleep(unsigned long u)
{
	usleep(u * 1000);
}
