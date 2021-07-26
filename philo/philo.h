/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztouzri <ztouzri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/19 17:34:21 by ztouzri           #+#    #+#             */
/*   Updated: 2021/07/26 11:33:18 by ztouzri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_ender
{
	int				end;
	pthread_mutex_t	ender;
}				t_ender;

typedef struct s_info {
	int		nbphil;
	long	ttd;
	long	tte;
	long	tts;
	int		musteat;
	long	begin;
}				t_info;

typedef struct s_philo {
	pthread_t		th;
	int				id;
	int				*leftforkinuse;
	int				*rightforkinuse;
	pthread_t		deathloop;
	pthread_mutex_t	deathlock;
	pthread_mutex_t	*leftfork;
	pthread_mutex_t	*rightfork;
	long			ttd;
	long			tte;
	long			tts;
	int				musteat;
	long			*lasteat;
	long			begin;
}					t_philo;

int				ft_isdigit(int c);
long			ft_atol(const char *nptr);
void			*ft_calloc(size_t count, size_t size);
t_info			*init_infos(char **av);
t_philo			*init_philos(t_info *infos);
unsigned long	gettime(void);
long			getstarvetime(unsigned long starttime);
void			puterror(char *str);
int				isvalidnum(char *str);
int				argchecker(int ac, char **av);
void			millisleep(unsigned long u);
unsigned long	gettimestamp(t_philo *philo);
void			*waitfordeath(void *arg);
int				routine(t_info *infos, t_philo *philos);
void			takeforks(t_philo *philo);
void			dropforks(t_philo *philo);

#endif
