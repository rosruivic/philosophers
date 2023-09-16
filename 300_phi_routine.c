/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   300_phi_routine.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roruiz-v <roruiz-v@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 13:56:55 by roruiz-v          #+#    #+#             */
/*   Updated: 2023/09/16 17:40:37 by roruiz-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_phi_checks_end_status(t_philo *p)
{
	int	status;

	status = 0;
	if (pthread_mutex_lock(&p->orgn->lock_error) != 0)
		ft_error_msg(ERROR_LOCK_ERROR_MUTEX, p->orgn);
	if (p->orgn->error == END)
	{
		status = 1;
	}
	if (pthread_mutex_unlock(&p->orgn->lock_error) != 0)
		ft_error_msg(ERROR_UNLOCK_ERROR_MUTEX, p->orgn);
	return (status);
}

void	*ft_phi_routine(void *philo)
{
	t_philo			*phi;

	phi = (t_philo *)philo;
	if (phi->hand)
		usleep(200);
	while (phi->orgn->error != END)
	{
		ft_phi_is_thinking(phi);
		ft_phi_get_forks(phi);
		if (phi->n_forks != 2)
		{
			while (ft_phi_checks_end_status(phi) == 0)
				;
			return (NULL);
		}
		ft_phi_is_eating(phi);
		ft_phi_is_sleeping(phi);
	}
	return (NULL);
}
