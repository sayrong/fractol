/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: balvyn-s <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/14 21:18:25 by balvyn-s          #+#    #+#             */
/*   Updated: 2019/09/14 21:18:44 by balvyn-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	btn_increase_pressed(int button, t_fract *fract)
{
	if (button == K_MINUS)
	{
		if (fract->iterations - iter_increase() > 1)
			fract->iterations -= iter_increase();
	}
	else
		fract->iterations += iter_increase();
}

void	reset(t_fract *fract)
{
	fract->point->scale = 1;
	fract->point->move_x = 0;
	fract->point->move_y = 0;
	fract->iterations = 50;
}

void	color_change(t_fract *fract)
{
	if (fract->color == -2147483648)
		fract->color = 252;
	else
		fract->color *= 1.1;
}

void	change_fract(t_fract *fract, int button)
{
	if (button == K_1)
		fract->ftype = mandelbrot;
	else if (button == K_2)
		fract->ftype = julia;
	else if (button == K_3)
		fract->ftype = burningship;
}

int		iter_increase(void)
{
	if (WIN_WIDTH < 400)
		return (50);
	return (10);
}
