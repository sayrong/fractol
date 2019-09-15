/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: balvyn-s <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/14 20:47:06 by balvyn-s          #+#    #+#             */
/*   Updated: 2019/09/14 20:47:14 by balvyn-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int		setup_mlx(t_fract *fract)
{
	fract->mlx = mlx_init();
	fract->win = mlx_new_window(fract->mlx, WIN_WIDTH, WIN_HEIGHT, "fractol");
	fract->img = mlx_new_image(fract->mlx, WIN_WIDTH, WIN_HEIGHT);
	fract->data = (int *)mlx_get_data_addr(fract->img,
							&fract->bpp, &fract->size_l, &fract->endian);
	if (fract->mlx == NULL || fract->win == NULL ||
		fract->img == NULL || fract->data == NULL)
		return (1);
	return (0);
}

void	setup(t_fract *fract)
{
	fract->point->max->im = 3;
	fract->point->max->re = 3.1;
	fract->point->min->im = -3;
	fract->point->min->re = -3;
	fract->iterations = 50;
	fract->color = 252;
	fract->freeze = 0;
	fract->use_dump_color = 0;
}

void	mlx_hooks_setup(t_fract *fract)
{
	mlx_hook(fract->win, 6, 0L, mouse_move, fract);
	mlx_hook(fract->win, 4, 0L, mouse_hook, fract);
	mlx_hook(fract->win, 2, 5, key_press, fract);
}
