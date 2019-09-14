/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_helper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: balvyn-s <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/14 21:07:16 by balvyn-s          #+#    #+#             */
/*   Updated: 2019/09/14 21:08:06 by balvyn-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	set_im_re(int start, calc_fract_data *fdata, t_fract *fract)
{
	fdata->y = start / (WIN_WIDTH);
	fdata->x = start % (WIN_HEIGHT);
	fdata->c_im = fract->point->max->im - fract->point->moveY
		- fdata->y * fdata->im_factor;
	fdata->c_re = fract->point->min->re + fract->point->moveX
		+ fdata->x * fdata->re_factor;
}

void	initialize(t_fract *fract, calc_fract_data *fdata)
{
	fdata->re_factor = (fract->point->max->re - fract->point->min->re)
		/ WIN_WIDTH * fract->point->scale;
	fdata->im_factor = (fract->point->max->im - fract->point->min->im)
		/ WIN_HEIGHT * fract->point->scale;
	fdata->iterations = fract->iterations;
	fdata->pixels = fract->data;
	fdata->j_im = fract->j_im;
	fdata->j_re = fract->j_re;
	fdata->ftype = fract->ftype;
}

void	clear_image(t_fract *fract)
{
	mlx_destroy_image(fract->mlx, fract->img);
	fract->img = mlx_new_image(fract->mlx, WIN_WIDTH, WIN_HEIGHT);
	mlx_clear_window(fract->mlx, fract->win);
	fract->data = (int *)mlx_get_data_addr(fract->img, &fract->bpp,
									&fract->size_l, &fract->endian);
}

void	scale(t_fract *fract, double scale, int x, int y)
{
	double width;
	double height;
	double new_width;
	double new_height;

	width = (fract->point->max->re - fract->point->min->re)
		* fract->point->scale;
	height = (fract->point->max->im - fract->point->min->im)
		* fract->point->scale;
	fract->point->scale *= scale;
	new_width = (fract->point->max->re - fract->point->min->re)
		* fract->point->scale;
	new_height = (fract->point->max->im - fract->point->min->im)
		* fract->point->scale;
	fract->point->moveX += ((double)x / WIN_WIDTH) * (width - new_width);
	fract->point->moveY += ((double)y / WIN_HEIGHT) * (height - new_height);
}
