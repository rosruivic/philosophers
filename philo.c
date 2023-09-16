/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roruiz-v <roruiz-v@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 09:07:00 by roruiz-v          #+#    #+#             */
/*   Updated: 2023/09/16 17:58:09 by roruiz-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* static void	ft_leaks(void)
{
	system("leaks -q philo");
} */

void	ft_free_pointers(t_bag *data)
{
	if (data->frk)
		free(data->frk);
	if (data->phi)
		free(data->phi);
}

static void	ft_default_data_init(t_bag *data)
{
	data->n_phi = -42;
	data->tm_to_die = -42;
	data->tm_to_eat = -42;
	data->tm_to_slp = -42;
	data->n_tms_must_eat = -42;
	data->s_tm = -42;
	data->frk = NULL;
	data->phi = NULL;
	data->phi_dead = -42;
	data->phi_dead_time = -42;
	data->error = NO_ERROR;
}

/**
 * @brief 
 * 				atexit(ft_leaks);
 * @param argc 
 * @param argv 
 * @return int 
 */
int	main(int argc, char **argv)
{
	t_bag	data;

	//atexit(ft_leaks);
	ft_default_data_init(&data);
	ft_check_data(&data, argc, argv);
	ft_init_data(&data, argc, argv);
	ft_ctrl_thr(&data);
	ft_free_pointers(&data);
	return (0);
}
