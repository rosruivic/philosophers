/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   320_phi_gets_forks.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roruiz-v <roruiz-v@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 13:20:37 by roruiz-v          #+#    #+#             */
/*   Updated: 2023/09/15 18:35:51 by roruiz-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	ft_print_fork(t_philo *p)
{
	if (pthread_mutex_lock(&p->orgn->lock_print) != NO_ERROR)
		ft_error_msg(ERROR_LOCK_PRINT_MUTEX, p->orgn);
	printf("%s%ld %i %s\n", B, ft_gtod() - p->orgn->s_tm, p->id_phi, FORK);
	if (pthread_mutex_unlock(&p->orgn->lock_print) != NO_ERROR)
		ft_error_msg(ERROR_UNLOCK_PRINT_MUTEX, p->orgn);
}

static void	ft_get_left_fork(t_philo *p)
{
	while (1)
	{			
		if (ft_phi_checks_end_status(p))
			return ;
		if (pthread_mutex_lock(&p->orgn->frk[p->indx_l_fork].f_mtx) != 0)
			ft_error_msg(ERROR_LOCK_FORK_MUTEX, p->orgn);
		if (p->orgn->frk[p->indx_l_fork].f_state == 0)
		{
			p->orgn->frk[p->indx_l_fork].f_state = 1;
			ft_print_fork(p);
			if (pthread_mutex_unlock(&p->orgn->frk[p->indx_l_fork].f_mtx) != 0)
				ft_error_msg(ERROR_UNLOCK_FORK_MUTEX, p->orgn);
			return ;
		}	
		if (pthread_mutex_unlock(&p->orgn->frk[p->indx_l_fork].f_mtx) != 0)
			ft_error_msg(ERROR_UNLOCK_FORK_MUTEX, p->orgn);
	}
}

static void	ft_get_right_fork(t_philo *p)
{
	while (1)
	{
		if (ft_phi_checks_end_status(p))
			return ;
		if (pthread_mutex_lock(&p->orgn->frk[p->indx_r_fork].f_mtx) != 0)
			ft_error_msg(ERROR_LOCK_FORK_MUTEX, p->orgn);
		if (p->orgn->frk[p->indx_r_fork].f_state == 0)
		{
			p->orgn->frk[p->indx_r_fork].f_state = 1;
			if (pthread_mutex_unlock(&p->orgn->frk[p->indx_r_fork].f_mtx) != 0)
				ft_error_msg(ERROR_UNLOCK_FORK_MUTEX, p->orgn);
			ft_print_fork(p);
			return ;
		}
		if (pthread_mutex_unlock(&p->orgn->frk[p->indx_r_fork].f_mtx) != 0)
			ft_error_msg(ERROR_UNLOCK_FORK_MUTEX, p->orgn);
	}
}

void	ft_phi_get_forks(t_philo *phi)
{
	if (phi->hand == 1)
	{
		ft_get_left_fork(phi);
		ft_get_right_fork(phi);
	}
	else
	{
		ft_get_right_fork(phi);
		ft_get_left_fork(phi);
	}
}
