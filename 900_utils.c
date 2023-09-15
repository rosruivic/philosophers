/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   900_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roruiz-v <roruiz-v@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 09:45:10 by roruiz-v          #+#    #+#             */
/*   Updated: 2023/09/06 16:49:40 by roruiz-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	ft_gtod(void)
{
	struct timeval	start_tm;

	gettimeofday(&start_tm, NULL);
	return ((start_tm.tv_sec * 1000) + (start_tm.tv_usec / 1000));
}

int	ft_strlen(char *s)
{
	int	len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}

void	ft_putstr_fd(char *s, int fd)
{
	write (fd, s, ft_strlen(s));
}

int	ft_is_digit(char var)
{
	if (var >= '0' && var <= '9')
		return (1);
	else
		return (0);
}
