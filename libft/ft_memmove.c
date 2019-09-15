/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: balvyn-s <balvyn-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/25 19:28:28 by balvyn-s          #+#    #+#             */
/*   Updated: 2018/12/12 21:17:07 by balvyn-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char		*t_dst;
	const char	*t_src;

	t_dst = dst;
	t_src = src;
	if (len == 0 || dst == src)
		return (dst);
	if ((unsigned long)dst < (unsigned long)src)
	{
		while (len-- != 0)
			*t_dst++ = *t_src++;
	}
	else
	{
		while (len-- != 0)
			t_dst[len] = t_src[len];
	}
	return ((void *)dst);
}
