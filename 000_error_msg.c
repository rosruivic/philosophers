/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   000_error_msg.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roruiz-v <roruiz-v@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 09:40:48 by roruiz-v          #+#    #+#             */
/*   Updated: 2023/09/16 19:21:19 by roruiz-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	ft_change_error_status(t_error_msg error, t_bag *data)
{
	pthread_mutex_lock(&data->lock_error);
	data->error = error;
	pthread_mutex_unlock(&data->lock_error);
}

static void	ft_mutex_init_or_lock_errors(t_error_msg error)
{
	if (error == ERROR_INIT_FORK_MUTEX)
		ft_putstr_fd("Error\n --- Error during FORK mutex init\n", 2);
	else if (error == ERROR_INIT_PRINT_MUTEX)
		ft_putstr_fd("Error\n --- Error during PRINT mutex init\n", 2);
	else if (error == ERROR_INIT_ERROR_MUTEX)
		ft_putstr_fd("Error\n --- Error during ERROR mutex init\n", 2);
	else if (error == ERROR_INIT_PHI_TM_LAST_EAT_MUTEX)
		ft_putstr_fd("Error\n --- Error during PHI_TM_LAST_EAT mutex init\n", 2);
	else if (error == ERROR_INIT_PHI_N_TMS_HAS_EATEN_MUTEX)
		ft_putstr_fd("Error\n --- Error during PHI_N_TMS_EATEN mutex init\n", 2);
	else if (error == ERROR_LOCK_FORK_MUTEX)
		ft_putstr_fd("Error\n --- Error locking FORK mutex\n", 2);
	else if (error == ERROR_LOCK_PRINT_MUTEX)
		ft_putstr_fd("Error\n --- Error locking PRINT mutex\n", 2);
	else if (error == ERROR_LOCK_ERROR_MUTEX)
		ft_putstr_fd("Error\n --- Error locking ERROR mutex\n", 2);
	else if (error == ERROR_LOCK_PHI_TM_LAST_EAT_MUTEX)
		ft_putstr_fd("Error\n --- Error locking PHI_TM_LAST_EAT mutex\n", 2);
	else if (error == ERROR_LOCK_PHI_N_TMS_HAS_EATEN_MUTEX)
		ft_putstr_fd("Error\n --- Error locking PHI_N_TMS_EATEN mutex\n", 2);
}

static void	ft_mutex_errors(t_error_msg error)
{
	if (error >= 20 && error <= 39)
		ft_mutex_init_or_lock_errors(error);
	else if (error == ERROR_UNLOCK_FORK_MUTEX)
		ft_putstr_fd("Error\n --- Error unlocking FORK mutex\n", 2);
	else if (error == ERROR_UNLOCK_PRINT_MUTEX)
		ft_putstr_fd("Error\n --- Error unlocking PRINT mutex\n", 2);
	else if (error == ERROR_UNLOCK_ERROR_MUTEX)
		ft_putstr_fd("Error\n --- Error unlocking ERROR mutex\n", 2);
	else if (error == ERROR_UNLOCK_PHI_TM_LAST_EAT_MUTEX)
		ft_putstr_fd("Error\n --- Error unlocking PHI_TM_LAST_EAT mutex\n", 2);
	else if (error == ERROR_UNLOCK_PHI_N_TMS_HAS_EATEN_MUTEX)
		ft_putstr_fd("Error\n --- Error unlocking PHI_N_TMS_EATEN mutex\n", 2);
	else if (error == ERROR_DESTROYING_FORK_MUTEX)
		ft_putstr_fd("Error\n --- Error destroying FORK mutex\n", 2);
	else if (error == ERROR_DESTROYING_PRINT_MUTEX)
		ft_putstr_fd("Error\n --- Error destroying PRINT mutex\n", 2);
	else if (error == ERROR_DESTROYING_ERROR_MUTEX)
		ft_putstr_fd("Error\n --- Error destroying ERROR mutex\n", 2);
	else if (error == ERROR_DESTROYING_PHI_TM_LAST_EAT_MUTEX)
		ft_putstr_fd("Error\n --- Error destroying PHI_TM_LAST_EAT mutex\n", 2);
	else if (error == ERROR_DESTROYING_PHI_N_TMS_HAS_EATEN_MUTEX)
		ft_putstr_fd("Error\n --- Error destroying PHI_N_TMS_EATEN mutex\n", 2);
}

void	ft_error_msg(t_error_msg error, t_bag *data)
{
	if (error >= 10 && error <= 59)
		ft_mutex_errors(error);
	else if (error == ERROR_INVALID_NUM_ARGMTS)
		ft_putstr_fd("Error\n --- Invalid number of arguments\n", 2);
	else if (error == ERROR_INVALID_TYPE_ARGMTS)
		ft_putstr_fd("Error\n --- Invalid arguments type\n", 2);
	else if (error == ERROR_OVERLIMITS)
		ft_putstr_fd("Error\n --- Some arguments over limits\n", 2);
	else if (error == ERROR_INVALID_NUM_PHILOSOPHERS)
		ft_putstr_fd("Error\n --- Invalid number of philosophers\n", 2);
	else if (error == ERROR_FORKS_MALLOC)
		ft_putstr_fd("Error\n --- Forks array MALLOC failure\n", 2);
	else if (error == ERROR_PHILOS_MALLOC)
		ft_putstr_fd("Error\n --- Philos array MALLOC failure\n", 2);
	else if (error == ERROR_CREATING_CONTROL_THREAD)
		ft_putstr_fd("Error\n --- CREATE control thread failure\n", 2);
	else if (error == ERROR_CREATING_PHILO_THREAD)
		ft_putstr_fd("Error\n --- CREATE philo thread failure\n", 2);
	else if (error == ERROR_IN_PHI_THREAD_JOIN)
		ft_putstr_fd("Error\n --- JOIN philo thread failure\n", 2);
	else if (error == ERROR_IN_CONTROL_THREAD_JOIN)
		ft_putstr_fd("Error\n --- JOIN control thread failure\n", 2);
	ft_change_error_status(error, data);
	ft_free_pointers(data);
	exit (EXIT_FAILURE);
}
