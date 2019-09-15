/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstback.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: balvyn-s <balvyn-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/14 20:54:23 by balvyn-s          #+#    #+#             */
/*   Updated: 2018/12/15 15:24:03 by balvyn-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstback(t_list **begin_list, void *data, size_t content_size)
{
	t_list *current;

	if (begin_list == NULL)
		return ;
	current = *begin_list;
	if (current == NULL)
	{
		*begin_list = ft_lstnew(data, content_size);
	}
	else
	{
		while (current->next != NULL)
		{
			current = current->next;
		}
		current->next = ft_lstnew(data, content_size);
	}
}
