/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   115_dominant_hand.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roruiz-v <roruiz-v@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 17:11:07 by roruiz-v          #+#    #+#             */
/*   Updated: 2023/09/15 18:32:50 by roruiz-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* static long	ft_gtod_random(void)
{
	struct timeval	start_tm;

	gettimeofday(&start_tm, NULL);
	return (start_tm.tv_usec);
} */

/* 	IT'S CALLED BY 110_init_data (ft_init_philos) */
/* int	ft_dominant_hand(void)
{
	if (ft_gtod_random() % 2 == 0)
		return (1);
	else
		return (0);
} */

int	ft_dominant_hand(t_philo *phi)
{
	if (phi->id_phi % 2 == 0)
		return (1);
	else
		return (0);
}
