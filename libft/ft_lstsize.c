/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: balvyn-s <balvyn-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/14 21:48:26 by balvyn-s          #+#    #+#             */
/*   Updated: 2018/12/14 22:27:50 by balvyn-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *begin_list)
{
	t_list	*temp;
	int		i;

	i = 1;
	if (begin_list == NULL)
		return (0);
	temp = begin_list;
	while (temp->next != NULL)
	{
		temp = temp->next;
		i++;
	}
	return (i);
}
