/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: balvyn-s <balvyn-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 18:58:15 by balvyn-s          #+#    #+#             */
/*   Updated: 2018/12/05 22:22:58 by balvyn-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd(t_list **alist, t_list *new)
{
	if (alist == NULL)
		return ;
	if (*alist == NULL)
		*alist = new;
	else if (*alist && new)
	{
		new->next = *alist;
		*alist = new;
	}
}
