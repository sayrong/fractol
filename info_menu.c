/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info_menu.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: balvyn-s <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/14 21:19:29 by balvyn-s          #+#    #+#             */
/*   Updated: 2019/09/14 21:20:12 by balvyn-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

char	*get_iteration(t_fract *fract)
{
	char	*iter_label;

	iter_label = "Iterations ";
	iter_label = ft_strjoin(iter_label, ft_itoa(fract->iterations));
	return (iter_label);
}

char	*get_zoom(t_fract *fract)
{
	char	*zoom_label;

	zoom_label = "Zoom ";
	zoom_label = ft_strjoin(zoom_label,
						ft_itoa((int)(1 / fract->point->scale * 100)));
	return (zoom_label);
}

void	menu_init(t_fract *fract)
{
	mlx_string_put(fract->mlx, fract->win, 10, 10, \
			0xFFFFFF, get_iteration(fract));
	mlx_string_put(fract->mlx, fract->win, 10, 25, \
			0xFFFFFF, get_zoom(fract));
}
