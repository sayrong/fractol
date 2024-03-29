/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: balvyn-s <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/14 20:38:06 by balvyn-s          #+#    #+#             */
/*   Updated: 2019/09/14 20:38:25 by balvyn-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int		finish(t_fract *fract)
{
	mlx_destroy_image(fract->mlx, fract->img);
	mlx_destroy_window(fract->mlx, fract->win);
	exit(0);
	return (0);
}

int		select_fractal(t_fract *fract, char *name)
{
	if (!ft_strcmp(name, "mandelbrot"))
		fract->ftype = mandelbrot;
	else if (!ft_strcmp(name, "julia"))
		fract->ftype = julia;
	else if (!ft_strcmp(name, "burningship"))
		fract->ftype = burningship;
	else if (!ft_strcmp(name, "celtic"))
		fract->ftype = celtic;
	else
		return (1);
	setup(fract);
	return (0);
}

int		basic_chec(int argc, char **argv, t_fract *fract)
{
	if (argc != 2)
	{
		ft_putstr("usage: fractol \"name of fractol\"");
		ft_putendl(" [mandelbrot,julia,burningship,celtic]");
		return (1);
	}
	if (select_fractal(fract, argv[1]))
	{
		ft_putstr("Wrong fractol name. ");
		ft_putendl("Use [mandelbrot,julia,burningship,celtic]");
		return (1);
	}
	if (setup_mlx(fract))
	{
		ft_putendl("Error init mlx");
		return (1);
	}
	return (0);
}

int		main(int argc, char **argv)
{
	t_fract		fract;
	t_viewpoint	point;
	t_complex_n	def_max;
	t_complex_n	def_min;

	fract.point = &point;
	point.max = &def_max;
	point.min = &def_min;
	point.move_x = 0;
	point.move_y = 0;
	point.scale = 1;
	if (basic_chec(argc, argv, &fract))
		return (1);
	create(&fract);
	mlx_hooks_setup(&fract);
	mlx_loop(fract.mlx);
	return (0);
}
