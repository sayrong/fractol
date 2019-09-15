/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: balvyn-s <balvyn-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 19:47:33 by balvyn-s          #+#    #+#             */
/*   Updated: 2018/12/05 21:05:22 by balvyn-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		get_bspaces(char const *s, size_t size)
{
	int back;

	back = 0;
	while (s[size - 1] == ' ' || s[size - 1] == '\n' || s[size - 1] == '\t')
	{
		size--;
		back++;
	}
	return (back);
}

static int		get_fspaces(char const *s)
{
	int front;

	front = 0;
	while (*s == ' ' || *s == '\n' || *s == '\t')
	{
		front++;
		s++;
	}
	return (front);
}

char			*ft_strtrim(char const *s)
{
	char	*t_s;
	size_t	size;
	int		front;
	int		back;

	if (s == NULL)
		return (NULL);
	size = ft_strlen(s);
	back = get_bspaces(s, size);
	front = get_fspaces(s);
	if ((size_t)back == size)
		back = 0;
	t_s = ft_strsub(s, front, size - front - back);
	return (t_s);
}
