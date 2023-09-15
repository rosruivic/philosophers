/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   110_init_data.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roruiz-v <roruiz-v@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 13:04:42 by roruiz-v          #+#    #+#             */
/*   Updated: 2023/09/15 18:25:55 by roruiz-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	ft_init_forks(t_bag *data)
{
	int	i;

	if (data->error != NO_ERROR)
		return ;
	i = -1;
	while (++i < data->n_phi)
	{
		data->frk->f_state = 0;
		if (pthread_mutex_init(&data->frk[i].f_mtx, NULL) != 0)
			ft_error_msg(ERROR_INIT_FORK_MUTEX, data);
	}
}

static void	ft_init_phi_mutexes(t_bag *data, int i)
{
	if (pthread_mutex_init(&data->phi[i].lock_tm_last_eat, NULL) != 0)
		ft_error_msg(ERROR_INIT_PHI_TM_LAST_EAT_MUTEX, data);
	if (pthread_mutex_init(&data->phi[i].lock_n_tms_has_eaten, NULL) != 0)
		ft_error_msg(ERROR_INIT_PHI_N_TMS_HAS_EATEN_MUTEX, data);
}

/**
 * @brief We init items of the struct of philo:
 * - The philosopher thread will be created in 200_create_threads later.
 * - The printing identificator of the philosopher
 * - The time long since the init of the program by now (1st time).
 * - And the #_times he has already eaten (use when 5th param occurs). 
 * - #_forks he has in their hands (if = 2 -> he's eating)
 * @param data 
 */
static void	ft_init_philos(t_bag *data)
{
	int	i;

	i = -1;
	while (++i < data->n_phi && data->error == NO_ERROR)
	{
		data->phi[i].thr_phi = NULL;
		data->phi[i].id_phi = i + 1;
//		data->phi[i].hand = ft_dominant_hand(void);
		data->phi[i].hand = ft_dominant_hand(&data->phi[i]);
		data->phi[i].tm_last_eat = data->s_tm;
		if (data->n_tms_must_eat >= 0)
			data->phi[i].n_tms_has_eaten = 0;
		data->phi[i].n_forks = 0;
		if (i == 0 && data->n_phi > 0)
			data->phi[i].indx_l_fork = (data->n_phi - 1);
		else
			data->phi[i].indx_l_fork = i - 1;
		if (i == data->n_phi - 1)
			data->phi[i].indx_r_fork = 0;
		else
			data->phi[i].indx_r_fork = i + 1;
		data->phi[i].orgn = data;
		ft_init_phi_mutexes(data, i);
	}
}

static void	ft_init_main_struct(t_bag *data, int argc, char **argv)
{
	data->n_phi = ft_philo_atoi(argv[1]);
	data->tm_to_die = ft_philo_atoi(argv[2]);
	data->tm_to_eat = ft_philo_atoi(argv[3]);
	data->tm_to_slp = ft_philo_atoi(argv[4]);
	if (argc == 6)
		data->n_tms_must_eat = ft_philo_atoi(argv[5]);
	data->frk = malloc(data->n_phi * sizeof(t_fork));
	if (!data->frk)
		ft_error_msg(ERROR_FORKS_MALLOC, data);
	data->phi = malloc(data->n_phi * sizeof(t_philo));
	if (!data->phi)
		ft_error_msg(ERROR_PHILOS_MALLOC, data);
	pthread_mutex_init(&data->lock_error, NULL);
	pthread_mutex_init(&data->lock_print, NULL);
}

void	ft_init_data(t_bag *data, int argc, char **argv)
{
	if (data->error != NO_ERROR)
		return ;
	ft_init_main_struct(data, argc, argv);
	ft_init_forks(data);
	ft_init_philos(data);
	data->s_tm = ft_gtod();
}
