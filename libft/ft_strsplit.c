/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: balvyn-s <balvyn-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 19:42:22 by balvyn-s          #+#    #+#             */
/*   Updated: 2018/12/08 16:48:16 by balvyn-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int			count_words(char const *s, char c)
{
	const char	*tmp;
	int			tik;
	int			count;

	tik = 1;
	tmp = s;
	count = 0;
	while (*tmp != '\0')
	{
		if (tik == 1 && *tmp != c)
		{
			tik = 0;
			count++;
		}
		else if (*tmp == c)
		{
			tik = 1;
		}
		tmp++;
	}
	return (count);
}

static	char		*get_string(char const *s, char c, int *index)
{
	int		wc;
	int		t_index;
	char	*tmp;
	int		i;

	wc = 0;
	i = 0;
	t_index = *index;
	while (s[*index] != c && s[*index] != '\0')
	{
		wc++;
		(*index)++;
	}
	tmp = (char*)malloc(sizeof(char) * (wc + 1));
	while (wc--)
	{
		tmp[i] = s[t_index];
		i++;
		t_index++;
	}
	tmp[i] = '\0';
	return (tmp);
}

char				**ft_strsplit(char const *s, char c)
{
	char	**ar;
	int		str_count;
	int		index;
	int		i;

	i = 0;
	index = 0;
	if (s == NULL)
		return (NULL);
	str_count = count_words(s, c);
	ar = (char **)malloc(sizeof(char *) * str_count + 1);
	if (ar == NULL)
	{
		return (NULL);
	}
	while (s[index] != '\0')
	{
		if (s[index] != c)
			ar[i++] = get_string(s, c, &index);
		else
			index++;
	}
	ar[i] = NULL;
	return (ar);
}
