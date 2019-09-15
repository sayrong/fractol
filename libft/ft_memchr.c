/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: balvyn-s <balvyn-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 19:18:45 by balvyn-s          #+#    #+#             */
/*   Updated: 2018/12/12 21:19:21 by balvyn-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char *t_s;

	t_s = s;
	while (n--)
	{
		if (*t_s == (unsigned char)c)
			return ((void *)t_s);
		t_s++;
	}
	return (NULL);
}
