/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: balvyn-s <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/14 20:52:57 by balvyn-s          #+#    #+#             */
/*   Updated: 2019/09/14 20:53:14 by balvyn-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	putpixel(int **data, unsigned x, unsigned y, unsigned color)
{
	if (x + y * (WIN_WIDTH) >= (WIN_HEIGHT) * (WIN_WIDTH))
	{
		perror("Out of image array bounds\n");
		return ;
	}
	(*data)[x + y * (WIN_WIDTH)] = color;
}

void	color_pixel(calc_fract_data *fdata, int fin_iter)
{
	int part;

	if (fin_iter == -1)
	{
		putpixel(&fdata->pixels, fdata->x, fdata->y, 0);
		return ;
	}
	part = fdata->iterations / 5;
	if (fin_iter < 0)
		return ;
	if (fin_iter < part)
		putpixel(&fdata->pixels, fdata->x, fdata->y,
			from_blue_to_cyan((double)fin_iter / part));
	else if (fin_iter < 2 * part)
		putpixel(&fdata->pixels, fdata->x, fdata->y,
			from_cyan_to_green((double)fin_iter / part * 2));
	else if (fin_iter < 3 * part)
		putpixel(&fdata->pixels, fdata->x, fdata->y,
			from_blue_to_cyan((double)fin_iter / part * 3));
	else if (fin_iter < 4 * part)
		putpixel(&fdata->pixels, fdata->x, fdata->y,
			from_yellow_to_red((double)fin_iter / part * 4));
}
