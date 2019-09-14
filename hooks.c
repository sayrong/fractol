/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: balvyn-s <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/14 21:12:36 by balvyn-s          #+#    #+#             */
/*   Updated: 2019/09/14 21:13:21 by balvyn-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int		key_press(int button, void *param)
{
	t_fract *fract;

	fract = (t_fract *)param;
	if (button == KB_ESC)
		finish(fract);
	else if (button >= K_LEFT && button <= K_UP)
		move_fr(button, fract);
	else if (button == K_MINUS || button == K_PLUS)
		btn_increase_pressed(button, fract);
	else if (button == K_Q)
		reset(fract);
	else if (button == K_E)
		color_change(fract);
	else if (button == K_W)
		fract->use_dump_color = !fract->use_dump_color;
	else if (button == K_1 || button == K_2 || button == K_3)
		change_fract(fract, button);
	else if (button == K_SPACE)
		scale(fract, 0.9, WIN_WIDTH / 2, WIN_HEIGHT / 2);
	else if (button == K_Z)
		scale(fract, 1.1, WIN_WIDTH / 2, WIN_HEIGHT / 2);
	create(fract);
	return (0);
}

int		mouse_hook(int button, int x, int y, void *param)
{
	t_fract	*fract;

	fract = (t_fract *)param;
	if (button == SCROLL_UP)
	{
		scale(fract, 0.9, x, y);
		if (fract->point->scale < 0.9)
			fract->iterations += iter_increase();
	}
	else if (button == SCROLL_DOWN)
	{
		scale(fract, 1.1, x, y);
		if (fract->iterations > 50)
			fract->iterations -= iter_increase();
	}
	else if (button == MOUSE_LEFT)
	{
		if (fract->freeze == 0)
			fract->freeze = 1;
		else
			fract->freeze = 0;
	}
	create(fract);
	return (0);
}

int		mouse_move(int x, int y, void *param)
{
	t_fract	*fract;
	double	re_factor;
	double	im_factor;

	fract = (t_fract *)param;
	re_factor = (fract->point->max->re - fract->point->min->re) / WIN_WIDTH;
	im_factor = (fract->point->max->im - fract->point->min->im) / WIN_HEIGHT;
	if (fract->ftype == julia && fract->freeze == 0)
	{
		fract->j_im = fract->point->max->im - y * im_factor;
		fract->j_re = fract->point->min->re + x * re_factor;
		create(fract);
	}
	return (1);
}

void	move_fr(int button, t_fract *fract)
{
	double move_x;
	double move_y;

	move_x = (fract->point->max->re - fract->point->min->re)
		* fract->point->scale * 0.1;
	move_y = (fract->point->max->im - fract->point->min->im)
		* fract->point->scale * 0.1;
	if (button == K_UP)
		fract->point->move_y -= move_y;
	else if (button == K_DOWN)
		fract->point->move_y += move_y;
	else if (button == K_LEFT)
		fract->point->move_x -= move_x;
	else if (button == K_RIGHT)
		fract->point->move_x += move_x;
}
