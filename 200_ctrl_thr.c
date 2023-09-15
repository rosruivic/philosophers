/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   200_ctrl_thr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roruiz-v <roruiz-v@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 11:44:23 by roruiz-v          #+#    #+#             */
/*   Updated: 2023/09/15 17:59:32 by roruiz-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_phi_dead_print(t_bag *d)
{
	if (d->phi_dead < 0)
		return ;
	if (pthread_mutex_lock(&d->lock_print) != 0)
		ft_error_msg(ERROR_LOCK_PRINT_MUTEX, d);
	printf("%s%ld %i %s\n", V, d->phi_dead_time, d->phi_dead, DEAD);
	if (pthread_mutex_unlock(&d->lock_print) != 0)
		ft_error_msg(ERROR_UNLOCK_PRINT_MUTEX, d);
}

void	ft_ctrl_thr(t_bag *d)
{
	if (d->error != NO_ERROR)
		return ;
	if (pthread_create(&d->thr_ctrl, NULL, ft_ctrl_routine, d) != 0)
		ft_error_msg(ERROR_CREATING_CONTROL_THREAD, d);
	if (pthread_join(d->thr_ctrl, NULL) != 0)
		ft_error_msg(ERROR_IN_CONTROL_THREAD_JOIN, d);
	if (pthread_mutex_destroy(&d->lock_error) != 0)
		ft_error_msg(ERROR_DESTROYING_ERROR_MUTEX, d);
	if (pthread_mutex_destroy(&d->lock_print) != 0)
		ft_error_msg(ERROR_DESTROYING_PRINT_MUTEX, d);
}
