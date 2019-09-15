/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: balvyn-s <balvyn-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/25 19:06:26 by balvyn-s          #+#    #+#             */
/*   Updated: 2018/12/12 21:13:03 by balvyn-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	char		*t_dst;
	const char	*t_src;
	char		t_s;

	t_dst = dst;
	t_src = src;
	t_s = (unsigned char)c;
	while (n-- != 0)
	{
		*t_dst = *t_src;
		if (*t_src == t_s)
			return (++t_dst);
		t_dst++;
		t_src++;
	}
	return (NULL);
}
