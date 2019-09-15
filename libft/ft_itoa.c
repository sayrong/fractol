/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: balvyn-s <balvyn-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 18:33:24 by balvyn-s          #+#    #+#             */
/*   Updated: 2018/12/14 21:38:11 by balvyn-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		count_c(int n)
{
	int count;

	count = 1;
	if (n < 0)
		count++;
	if (n == 0)
		return (++count);
	while (n != 0)
	{
		n /= 10;
		count++;
	}
	return (count);
}

char			*ft_itoa(int n)
{
	char	*nb;
	int		count;
	int		i;
	int		minus;

	i = 0;
	minus = 1;
	count = count_c(n);
	if ((nb = (char *)malloc(sizeof(char) * count)))
	{
		if (n == 0)
			nb[0] = '0';
		minus = n < 0 ? -1 : 1;
		while (n != 0)
		{
			nb[i++] = (n % 10) * minus + '0';
			n /= 10;
		}
		if (minus < 0)
			nb[i++] = '-';
		nb[count - 1] = '\0';
		ft_strrev(nb);
	}
	return (nb);
}
