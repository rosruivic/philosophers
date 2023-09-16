/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   330_phi_eats.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roruiz-v <roruiz-v@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 02:18:13 by roruiz-v          #+#    #+#             */
/*   Updated: 2023/09/16 17:10:49 by roruiz-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	ft_phi_increase_n_tms_has_eaten(t_philo *p)
{
	if (ft_phi_checks_end_status(p))
		return ;
	if (pthread_mutex_lock(&p->lock_n_tms_has_eaten) != 0)
		ft_error_msg(ERROR_LOCK_PHI_N_TMS_HAS_EATEN_MUTEX, p->orgn);
	p->n_tms_has_eaten++;
	if (pthread_mutex_unlock(&p->lock_n_tms_has_eaten) != 0)
		ft_error_msg(ERROR_LOCK_PHI_N_TMS_HAS_EATEN_MUTEX, p->orgn);
}

static void	ft_phi_prints_is_eating(t_philo *p)
{
	if (ft_phi_checks_end_status(p))
		return ;
	if (pthread_mutex_lock(&p->orgn->lock_print) != 0)
		ft_error_msg(ERROR_LOCK_PRINT_MUTEX, p->orgn);
	printf("%s%ld %i %s\n", R, (ft_gtod() - p->orgn->s_tm), p->id_phi, EAT);
	if (pthread_mutex_unlock(&p->orgn->lock_print) != 0)
		ft_error_msg(ERROR_UNLOCK_PRINT_MUTEX, p->orgn);
}

void	ft_phi_is_eating(t_philo *phi)
{
	long	tm_last_eat;

	if (ft_phi_checks_end_status(phi))
		return ;
	if (pthread_mutex_lock(&phi->lock_tm_last_eat) != 0)
		ft_error_msg(ERROR_LOCK_PHI_TM_LAST_EAT_MUTEX, phi->orgn);
	phi->tm_last_eat = ft_gtod();
	tm_last_eat = phi->tm_last_eat;
	if (pthread_mutex_unlock(&phi->lock_tm_last_eat) != 0)
		ft_error_msg(ERROR_UNLOCK_PHI_TM_LAST_EAT_MUTEX, phi->orgn);
	ft_phi_prints_is_eating(phi);
	ft_phi_increase_n_tms_has_eaten(phi);
	while (tm_last_eat + phi->orgn->tm_to_eat > ft_gtod())
	{
		if (ft_phi_checks_end_status(phi))
			return ;
	}
}
