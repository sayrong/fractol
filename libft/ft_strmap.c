/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: balvyn-s <balvyn-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 19:38:31 by balvyn-s          #+#    #+#             */
/*   Updated: 2018/12/05 21:58:04 by balvyn-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	size_t	size;
	char	*t_s;

	if (s == NULL)
		return (NULL);
	size = ft_strlen(s);
	t_s = (char *)malloc(sizeof(char) * size + 1);
	if (t_s)
	{
		t_s[size] = '\0';
		while (size--)
			t_s[size] = f(s[size]);
	}
	return (t_s);
}
