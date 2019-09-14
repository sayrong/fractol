/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: balvyn-s <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/14 20:51:30 by balvyn-s          #+#    #+#             */
/*   Updated: 2019/09/14 20:51:57 by balvyn-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fractol.h>

int		from_blue_to_cyan(double percent)
{
	int green;
	int blue;

	if (percent < 0.3)
		percent *= 2;
	green = 255 * percent;
	blue = 255;
	return ((green << 8) | (blue));
}

int		from_cyan_to_green(double percent)
{
	int green;
	int blue;

	green = 255;
	blue = 255 * percent;
	return ((green << 8) | (blue));
}

int		from_green_to_yellow(double percent)
{
	int red;
	int green;

	green = 255;
	red = 255 * percent;
	return (red << 16 | green << 8);
}

int		from_yellow_to_red(double percent)
{
	int red;
	int green;

	green = 255 * percent;
	red = 255;
	return (red << 16 | green << 8);
}

void	color_dump(t_fract *fract, calc_fract_data *fdata, int fin_iter)
{
	int color;

	color = 0;
	color = fract->color * fin_iter;
	putpixel(&fdata->pixels, fdata->x, fdata->y, color);
}
