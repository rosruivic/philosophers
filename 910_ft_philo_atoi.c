/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   910_ft_philo_atoi.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roruiz-v <roruiz-v@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 13:02:20 by roruiz-v          #+#    #+#             */
/*   Updated: 2023/09/16 19:26:03 by roruiz-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/****************************************************************************
  Converts the initial portion of the string pointed (passing spaces until
  	finds a number (or a sign belowed by a number), and then from there 
		to last until finds a no-number character, where it stops).
	Spaces are white space, tab, rc... (isspace(3)).
	It does not start de conversion until it finds a number or only one sign 
		followed by a number. It finishes when founds a '\0' and returns value.
	RETURN VALUE: the int representation of the string found.
	***************************************************************************
	VAR j: stocks 1st number position it founds;
	VAR i--: stocks last position with a number it founds.
	(We'll walk this positions in inverted order: units, decens, centens...)
*****************************************************************************/

#include "philo.h"

long	ft_philo_atoi(const char *str)
{
	long	i;
	long	nb;
	long	sg;

	i = -1;
	nb = 0;
	sg = 1;
	while (str[++i] && str[i] == ' ')
		;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sg = sg * (-1);
		i++;
	}
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		nb = (nb * 10) + (str[i] - '0');
		i++;
	}
	return (nb * sg);
}
