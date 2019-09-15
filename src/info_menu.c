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
	char	*num;

	iter_label = "Iterations ";
	num = ft_itoa(fract->iterations);
	iter_label = ft_strjoin(iter_label, num);
	free(num);
	return (iter_label);
}

char	*get_zoom(t_fract *fract)
{
	char	*zoom_label;
	int		number;
	char	*num;

	zoom_label = "Zoom ";
	number = (int)(1 / fract->point->scale * 100);
	num = ft_itoa(number);
	if (number < 0)
		zoom_label = ft_strjoin(zoom_label, "too much");
	else
		zoom_label = ft_strjoin(zoom_label,
						num);
	free(num);
	return (zoom_label);
}

void	menu_init(t_fract *fract)
{
	char *iter;
	char *zoom;

	iter = get_iteration(fract);
	zoom = get_zoom(fract);
	mlx_string_put(fract->mlx, fract->win, 10, 10, \
			0xFFFFFF, iter);
	mlx_string_put(fract->mlx, fract->win, 10, 25, \
			0xFFFFFF, zoom);
	free(iter);
	free(zoom);
}
