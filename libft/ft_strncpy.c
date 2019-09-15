/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: balvyn-s <balvyn-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/27 18:14:31 by balvyn-s          #+#    #+#             */
/*   Updated: 2018/12/15 15:04:46 by balvyn-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncpy(char *dest, const char *src, size_t len)
{
	char *begin;

	begin = dest;
	while (len != 0 && *src != '\0')
	{
		*dest++ = *src++;
		len--;
	}
	while (len--)
		*dest++ = '\0';
	return (begin);
}
