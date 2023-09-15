/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   100_check_data.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roruiz-v <roruiz-v@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 12:36:43 by roruiz-v          #+#    #+#             */
/*   Updated: 2023/09/05 15:37:22 by roruiz-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	ft_check_n_argmts(t_bag *data, int argc)
{
	if (argc < 5 || argc > 6)
		ft_error_msg(ERROR_INVALID_NUM_ARGMTS, data);
}

static void	ft_check_is_digit_argmts(t_bag *data, char **argv)
{
	int	i;
	int	j;

	i = 0;
	j = -1;
	if (data->error)
		return ;
	while (argv[++i])
	{
		j = -1;
		while (argv[i][++j])
		{
			if (ft_is_digit(argv[i][j]) == 0)
			{
				ft_error_msg(ERROR_INVALID_TYPE_ARGMTS, data);
				return ;
			}
		}
	}
}

void	ft_check_data(t_bag *data, int argc, char **argv)
{
	ft_check_n_argmts(data, argc);
	ft_check_is_digit_argmts(data, argv);
}
