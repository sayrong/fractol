/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: balvyn-s <balvyn-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 19:30:05 by balvyn-s          #+#    #+#             */
/*   Updated: 2018/12/03 20:29:21 by balvyn-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	const char	*t_s;

	t_s = s;
	while (*t_s != '\0')
	{
		if (*t_s == c)
		{
			return ((char *)t_s);
		}
		t_s++;
	}
	if (c == 0)
	{
		return ((char *)t_s);
	}
	return (NULL);
}
