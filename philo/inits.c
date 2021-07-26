/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztouzri <ztouzri@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/19 18:23:52 by ztouzri           #+#    #+#             */
/*   Updated: 2021/06/21 06:44:53 by ztouzri          ###   ########.fr       */
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
