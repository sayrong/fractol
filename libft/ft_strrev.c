/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: balvyn-s <balvyn-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/14 21:27:08 by balvyn-s          #+#    #+#             */
/*   Updated: 2018/12/14 21:37:50 by balvyn-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static void		swap(char *c1, char *c2)
{
	char temp;

	temp = *c1;
	*c1 = *c2;
	*c2 = temp;
}

void			ft_strrev(char *s)
{
	int size;
	int i;

	size = 0;
	i = 0;
	while (s[size] != '\0')
		size++;
	while (i < size)
	{
		swap(&s[i], &s[size - 1]);
		i++;
		size--;
	}
}
