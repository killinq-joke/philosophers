/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztouzri <ztouzri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/26 11:22:33 by ztouzri           #+#    #+#             */
/*   Updated: 2021/07/26 11:31:35 by ztouzri          ###   ########.fr       */
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
