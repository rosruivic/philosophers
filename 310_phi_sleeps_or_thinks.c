/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   310_phi_sleeps_or_thinks.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roruiz-v <roruiz-v@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 13:07:11 by roruiz-v          #+#    #+#             */
/*   Updated: 2023/09/15 19:42:28 by roruiz-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_phi_is_thinking(t_philo *p)
{
	if (ft_phi_checks_end_status(p))
		return ;
	if (pthread_mutex_lock(&p->orgn->lock_print) != 0)
		ft_error_msg(ERROR_LOCK_PRINT_MUTEX, p->orgn);
	printf("%s%ld %i %s\n", G, ft_gtod() - p->orgn->s_tm, p->id_phi, THINK);
	if (pthread_mutex_unlock(&p->orgn->lock_print) != 0)
		ft_error_msg(ERROR_UNLOCK_PRINT_MUTEX, p->orgn);
}

static void	ft_phi_prints_is_sleeping(t_philo *p)
{
	if (ft_phi_checks_end_status(p))
		return ;
	if (pthread_mutex_lock(&p->orgn->lock_print) != 0)
		ft_error_msg(ERROR_LOCK_PRINT_MUTEX, p->orgn);
	printf("%s%ld %i %s\n", Y,
		(ft_gtod() - p->orgn->s_tm), p->id_phi, SLEEP);
	if (pthread_mutex_unlock(&p->orgn->lock_print) != 0)
		ft_error_msg(ERROR_UNLOCK_PRINT_MUTEX, p->orgn);
}

void	ft_phi_leaves_forks(t_philo *p)
{
	if (ft_phi_checks_end_status(p))
		return ;
	if (p->orgn->n_phi > 1)
	{
		if (pthread_mutex_lock(&p->orgn->frk[p->indx_l_fork].f_mtx) != 0)
			ft_error_msg(ERROR_LOCK_FORK_MUTEX, p->orgn);
		p->orgn->frk[p->indx_l_fork].f_state = 0;
		if (pthread_mutex_unlock(&p->orgn->frk[p->indx_l_fork].f_mtx) != 0)
			ft_error_msg(ERROR_UNLOCK_FORK_MUTEX, p->orgn);
	}
	if (ft_phi_checks_end_status(p))
		return ;
	if (pthread_mutex_lock(&p->orgn->frk[p->indx_r_fork].f_mtx) != 0)
		ft_error_msg(ERROR_LOCK_FORK_MUTEX, p->orgn);
	p->orgn->frk[p->indx_r_fork].f_state = 0;
	if (pthread_mutex_unlock(&p->orgn->frk[p->indx_r_fork].f_mtx) != 0)
		ft_error_msg(ERROR_UNLOCK_FORK_MUTEX, p->orgn);
}

void	ft_phi_is_sleeping(t_philo *phi)
{
	long	tm_last_eat;

	if (ft_phi_checks_end_status(phi))
		return ;
	if (pthread_mutex_lock(&phi->lock_tm_last_eat) != 0)
		ft_error_msg(ERROR_LOCK_PHI_TM_LAST_EAT_MUTEX, phi->orgn);
	tm_last_eat = phi->tm_last_eat;
	if (pthread_mutex_unlock(&phi->lock_tm_last_eat) != 0)
		ft_error_msg(ERROR_UNLOCK_PHI_TM_LAST_EAT_MUTEX, phi->orgn);
	ft_phi_prints_is_sleeping(phi);
	ft_phi_leaves_forks(phi);
	while (tm_last_eat + phi->orgn->tm_to_eat + phi->orgn->tm_to_slp
		> ft_gtod())
	{
		if (ft_phi_checks_end_status(phi))
			return ;
	}
}
