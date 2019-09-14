/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: balvyn-s <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/14 20:56:00 by balvyn-s          #+#    #+#             */
/*   Updated: 2019/09/14 20:56:56 by balvyn-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	create(t_fract *fract)
{
	t_thread	new[THREADS_NUM];
	pthread_t	threads[THREADS_NUM];
	int			i;

	clear_image(fract);
	i = 0;
	while (i < THREADS_NUM)
	{
		new[i].fr = fract;
		new[i].i = i;
		pthread_create(threads + i, NULL, multi_thread, (void*)&new[i]);
		i++;
	}
	while (i--)
		pthread_join(threads[i], NULL);
	mlx_put_image_to_window(fract->mlx, fract->win, fract->img, 0, 0);
	menu_init(fract);
}

void	multi_thread(void *fr)
{
	int			step;
	t_thread	*n;

	step = (WIN_WIDTH * WIN_HEIGHT) / THREADS_NUM;
	n = (t_thread*)fr;
	calculate(n->fr, step, n->i);
}

void	calculate(t_fract *fract, int step, int num)
{
	int				start_point;
	int				end_point;
	int				finish_iteration;
	t_calc_fract_data	fdata;

	initialize(fract, &fdata);
	start_point = step * num;
	end_point = start_point + step;
	while (start_point < end_point)
	{
		set_im_re(start_point, &fdata, fract);
		finish_iteration = is_in_set(&fdata);
		if (fract->use_dump_color == 0)
			color_pixel(&fdata, finish_iteration);
		else
			color_dump(fract, &fdata, finish_iteration);
		start_point++;
	}
}

int		is_in_set(t_calc_fract_data *fdata)
{
	int		i;
	double	c_im_tmp;
	double	z_re;
	double	z_im;

	i = 0;
	z_re = fdata->c_re;
	z_im = fdata->c_im;
	while ((i < fdata->iterations) && ((z_re * z_re + z_im * z_im) < 4))
	{
		c_im_tmp = z_im;
		z_im = 2 * z_re * z_im;
		z_re = z_re * z_re - c_im_tmp * c_im_tmp;
		define_fract(fdata, &z_re, &z_im);
		i++;
	}
	if (i == fdata->iterations)
		return (-1);
	return (i);
}

void	define_fract(t_calc_fract_data *fdata, double *z_re, double *z_im)
{
	if (fdata->ftype == mandelbrot)
	{
		*z_re += fdata->c_re;
		*z_im += fdata->c_im;
	}
	else if (fdata->ftype == julia)
	{
		*z_re += fdata->j_re;
		*z_im += fdata->j_im;
	}
	else if (fdata->ftype == burningship)
	{
		*z_re = fabs(*z_re + fdata->c_re);
		*z_im = -fabs(*z_im + fdata->c_im);
	}
}
