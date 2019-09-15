/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: balvyn-s <balvyn-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 19:47:09 by balvyn-s          #+#    #+#             */
/*   Updated: 2018/12/05 22:00:20 by balvyn-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*t_s;
	int		i;

	if (s == NULL)
		return (NULL);
	i = 0;
	t_s = (char *)malloc(sizeof(char) * len + 1);
	if (t_s)
	{
		while (len--)
			t_s[i++] = s[start++];
		t_s[i] = '\0';
	}
	return (t_s);
}
