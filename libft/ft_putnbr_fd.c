/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: balvyn-s <balvyn-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 19:27:26 by balvyn-s          #+#    #+#             */
/*   Updated: 2018/12/05 21:50:43 by balvyn-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	long int t_n;

	t_n = (long int)n;
	if (t_n < 0)
	{
		ft_putchar_fd('-', fd);
		t_n = -t_n;
	}
	if (t_n >= 10)
	{
		ft_putnbr_fd(t_n / 10, fd);
		ft_putchar_fd(t_n % 10 + '0', fd);
	}
	else
	{
		ft_putchar_fd(t_n + '0', fd);
	}
}
