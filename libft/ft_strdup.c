/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: balvyn-s <balvyn-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 19:33:27 by balvyn-s          #+#    #+#             */
/*   Updated: 2018/12/12 21:25:11 by balvyn-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*t_s;
	int		size;
	int		i;

	size = 0;
	i = 0;
	while (s[size])
		size++;
	t_s = (char *)malloc(size + 1);
	if (t_s)
	{
		while (i < size)
		{
			t_s[i] = s[i];
			i++;
		}
		t_s[size] = '\0';
	}
	return (t_s);
}
