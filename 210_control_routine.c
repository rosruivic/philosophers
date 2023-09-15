/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   210_control_routine.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roruiz-v <roruiz-v@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 14:22:28 by roruiz-v          #+#    #+#             */
/*   Updated: 2023/09/15 20:20:39 by roruiz-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* **********      CTRL THREAD CREATES PHI THREADS       *********** */
/* **********          & CHECKS END CONDITIONS           *********** */

static int	ft_check_deads(t_bag *d)
{
	int		i;
	long	tm_last_eat;

	i = -1;
	while (++i < d->n_phi)
	{
		if (pthread_mutex_lock(&d->phi[i].lock_tm_last_eat) != 0)
			ft_error_msg(ERROR_LOCK_PHI_TM_LAST_EAT_MUTEX, d);
		if (d->phi[i].tm_last_eat > 0)
			tm_last_eat = d->phi[i].tm_last_eat;
		if (pthread_mutex_unlock(&d->phi[i].lock_tm_last_eat) != 0)
			ft_error_msg(ERROR_UNLOCK_PHI_TM_LAST_EAT_MUTEX, d);
		if (tm_last_eat > 0
			&& ft_gtod() - tm_last_eat > d->tm_to_die)
		{
			d->phi_dead = d->phi[i].id_phi;
			d->phi_dead_time = ft_gtod() - d->s_tm;
			return (1);
		}
	}
	return (0);
}

static int	ft_check_all_has_eaten(t_bag *d)
{
	int	i;
	int	n_has_eaten;

	n_has_eaten = 0;
	if (d->n_tms_must_eat < 0)
		return (0);
	i = -1;
	while (++i < d->n_phi)
	{
		if (pthread_mutex_lock(&d->phi[i].lock_n_tms_has_eaten) != 0)
			ft_error_msg(ERROR_LOCK_PHI_N_TMS_HAS_EATEN_MUTEX, d);
		if (d->phi[i].n_tms_has_eaten >= d->n_tms_must_eat)
			n_has_eaten++;
		if (pthread_mutex_unlock(&d->phi[i].lock_n_tms_has_eaten) != 0)
			ft_error_msg(ERROR_UNLOCK_PHI_N_TMS_HAS_EATEN_MUTEX, d);
	}
	if (n_has_eaten == d->n_phi)
		return (1);
	return (0);
}

static void	ft_changes_to_end_status(t_bag *data)
{
	if (pthread_mutex_lock(&data->lock_error) != 0)
		ft_error_msg(ERROR_LOCK_ERROR_MUTEX, data);
	data->error = END;
	if (pthread_mutex_unlock(&data->lock_error) != 0)
		ft_error_msg(ERROR_UNLOCK_ERROR_MUTEX, data);
}

/**
 * @brief Ctrl thread creates & destroyes the philos threads
 * 
 * @param data 
 * @return void* 
 */
void	*ft_ctrl_routine(void *data)
{
	t_bag	*d;

	d = (t_bag *)data;
	ft_create_philos_threads(d);
	if (d->n_phi < 3)
		usleep((d->tm_to_die - 2) * 1000);
	while (1)
	{
		if (d->phi[d->n_phi - 1].id_phi == d->n_phi)
			break ;
	}
	while (1)
	{
		if (ft_check_all_has_eaten(d))
			break ;
		if (ft_check_deads(d))
			break ;
	}
	ft_changes_to_end_status(d);
	ft_join_phi_threads(d);
	ft_phi_dead_print(d);
	ft_destroy_phi_mutexes(d);
	return (NULL);
}
