//
//  fractol.h
//  fract
//
//  Created by Babette Alvyn sharp on 09/09/2019.
//  Copyright © 2019 Babette Alvyn sharp. All rights reserved.
//

#ifndef FRACTOL_H
#define FRACTOL_H

#include "mlx.h"
#include <stdlib.h>

#include <stdio.h>
#include "libft.h"
#include <pthread.h>

#define WIN_WIDTH 400
#define WIN_HEIGHT 400
#define THREADS_NUM 8

typedef enum {
	mandelbrot,
	julia,
	burningship
}		e_ftype;

typedef struct s_complex_n {
	double re;
	double im;
}              t_complex_n;

typedef struct s_viewpoint {
	t_complex_n *min;
	t_complex_n *max;
	double moveX;
	double moveY;
	double scale;
}              t_viewpoint;

typedef struct s_fract {
	void *mlx;
	void *win;
	void *img;
	int *data;
	int    bpp;
	int    size_l;
	int    endian;
	t_viewpoint *point;
	int threadNumber;
	e_ftype ftype;
    int color;
	unsigned int iterations;
    double j_im;
    double j_re;
	int freeze;
	int use_dump_color;
}               t_fract;

typedef struct s_mondel {
	double c_im;
};

typedef struct s_thread {
	t_fract *fr;
	int i;
} t_thread;

#endif
