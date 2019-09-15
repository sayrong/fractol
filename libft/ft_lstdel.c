/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: balvyn-s <balvyn-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 19:00:19 by balvyn-s          #+#    #+#             */
/*   Updated: 2018/12/03 19:53:33 by balvyn-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list *data;

	if (!alst)
		return ;
	while (*alst)
	{
		data = *alst;
		*alst = (*alst)->next;
		del(data->content, data->content_size);
		free(data);
	}
	*alst = NULL;
}
