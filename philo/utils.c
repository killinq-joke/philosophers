/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztouzri <ztouzri@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/19 17:35:44 by ztouzri           #+#    #+#             */
/*   Updated: 2021/06/30 13:41:24 by ztouzri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_bzero(void *s, size_t n)
{
	size_t			i;
	unsigned char	*tmp;

	i = 0;
	while (i < n)
	{
		tmp = (unsigned char *)s;
		*tmp = 0;
		s++;
		i++;
	}
}

void	*ft_calloc(size_t count, size_t size)
{
	size_t	space;
	void	*ptr;

	space = count * size;
	ptr = malloc(space);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, space);
	return (ptr);
}

int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	return (0);
}

// int	ft_atoi(const char *nptr)
// {
// 	int		result;
// 	int		sign;
// 	size_t	i;

// 	sign = 1;
// 	result = 0;
// 	i = 0;
// 	while (nptr[i] == ' ' || nptr[i] == '\t' || nptr[i] == '\n'
// 		|| nptr[i] == '\r' || nptr[i] == '\v' || nptr[i] == '\f')
// 		i++;
// 	if (nptr[i] == '-' || nptr[i] == '+')
// 	{
// 		if (nptr[i] == '-')
// 			sign = -1;
// 		i++;
// 	}
// 	while (nptr[i] && ft_isdigit(nptr[i]))
// 	{
// 		result = result * 10 + nptr[i] - '0';
// 		i++;
// 	}
// 	return (sign * result);
// }

long	ft_atol(const char *nptr)
{
	unsigned long	result;
	size_t			i;

	result = 0;
	i = 0;
	while (nptr[i] == ' ' || nptr[i] == '\t' || nptr[i] == '\n'
		|| nptr[i] == '\r' || nptr[i] == '\v' || nptr[i] == '\f')
		i++;
	while (nptr[i] && ft_isdigit(nptr[i]))
	{
		result = result * 10 + nptr[i] - '0';
		i++;
	}
	return (result);
}
