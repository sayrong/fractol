/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: balvyn-s <balvyn-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/08 15:33:05 by balvyn-s          #+#    #+#             */
/*   Updated: 2018/12/08 16:34:41 by balvyn-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		size;
	char	*t_s;
	int		i;

	if (s == NULL)
		return (NULL);
	i = 0;
	size = ft_strlen(s);
	t_s = (char *)malloc(sizeof(char) * size + 1);
	if (t_s)
	{
		t_s[size] = '\0';
		while (i < size)
		{
			t_s[i] = f(i, s[i]);
			i++;
		}
	}
	return (t_s);
}
