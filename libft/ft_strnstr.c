/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: balvyn-s <balvyn-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 19:41:23 by balvyn-s          #+#    #+#             */
/*   Updated: 2018/12/14 22:32:07 by balvyn-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t		i;
	size_t		j;
	char		*hay;

	hay = (char *)haystack;
	if (*needle == '\0')
		return (hay);
	if (len == 0)
		return (NULL);
	i = 0;
	while (hay[i] != '\0' && len--)
	{
		if (hay[i] == needle[0])
		{
			j = 1;
			while (hay[i + j] == needle[j] && needle[j] != '\0'
				&& len - j + 1 != 0)
				j++;
			if (needle[j] == '\0')
				return (&hay[i]);
		}
		i++;
	}
	return (NULL);
}
