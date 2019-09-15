/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: balvyn-s <balvyn-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/27 17:35:31 by balvyn-s          #+#    #+#             */
/*   Updated: 2018/12/07 23:47:04 by balvyn-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int				minus;
	long long int	result;
	int				overflow;

	minus = 1;
	result = 0;
	overflow = 0;
	while (*str == ' ' || (*str >= 9 && *str <= 14))
		str++;
	if (*str == '-')
		minus = -1;
	if (*str == '+' || *str == '-')
		str++;
	while (*str >= '0' && *str <= '9' && overflow++ < 19)
	{
		result *= 10;
		if (overflow == 19 && (9223372036854775807 - result) < (*str - 48))
			return (minus > 0 ? -1 : 0);
		result += *str - 48;
		str++;
		if (overflow == 20)
			return (minus > 0 ? -1 : 0);
	}
	return ((int)(result * minus));
}
