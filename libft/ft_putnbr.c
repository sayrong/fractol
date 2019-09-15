/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: balvyn-s <balvyn-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 18:16:50 by balvyn-s          #+#    #+#             */
/*   Updated: 2018/12/05 21:46:28 by balvyn-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr(int n)
{
	long int t_n;

	t_n = (long int)n;
	if (t_n < 0)
	{
		ft_putchar('-');
		t_n = -t_n;
	}
	if (t_n >= 10)
	{
		ft_putnbr(t_n / 10);
		ft_putchar(t_n % 10 + '0');
	}
	else
	{
		ft_putchar(t_n + '0');
	}
}
