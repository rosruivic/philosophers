/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   220_ctrl_routine_extras.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roruiz-v <roruiz-v@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 15:08:44 by roruiz-v          #+#    #+#             */
/*   Updated: 2023/09/14 21:07:24 by roruiz-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_join_phi_threads(t_bag *data)
{
	int	i;

	i = -1;
	while (++i < data->n_phi)
	{
		if (pthread_join(data->phi[i].thr_phi, NULL) != 0)
			ft_error_msg(ERROR_IN_PHI_THREAD_JOIN, data);
	}
}

void	ft_destroy_phi_mutexes(t_bag *data)
{
	int	i;

	i = -1;
	while (++i < data->n_phi)
	{
		if (pthread_mutex_destroy(&data->frk[i].f_mtx) != 0)
			ft_error_msg(ERROR_DESTROYING_FORK_MUTEX, data);
	}
}

void	ft_create_philos_threads(t_bag *d)
{
	int		i;

	i = -1;
	while (++i < d->n_phi)
	{
		if (pthread_create(&d->phi[i].thr_phi, NULL,
				ft_phi_routine, &d->phi[i]) != 0)
		{
			ft_error_msg(ERROR_CREATING_PHILO_THREAD, d);
		}
	}
}
