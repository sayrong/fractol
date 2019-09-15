/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: balvyn-s <balvyn-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 19:10:28 by balvyn-s          #+#    #+#             */
/*   Updated: 2018/12/03 19:52:43 by balvyn-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*list;
	void	*new_data;

	list = malloc(sizeof(t_list));
	if (list)
	{
		list->next = NULL;
		if (content == NULL)
		{
			list->content = NULL;
			list->content_size = 0;
			return (list);
		}
		new_data = malloc(content_size);
		ft_memcpy(new_data, content, content_size);
		list->content = new_data;
		list->content_size = content_size;
	}
	return (list);
}
