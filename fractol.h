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
#include "libft.h"
#include <pthread.h>
#include <stdio.h>

#define WIN_WIDTH 800
#define WIN_HEIGHT 800
#define THREADS_NUM 8
#define K_MINUS 27
#define K_PLUS 24
#define K_Q 12
#define K_W 13
#define K_E 14
#define K_Z 6
#define K_UP 126
#define K_DOWN 125
#define K_LEFT 123
#define K_RIGHT 124
#define K_1 18
#define K_2 19
#define K_3 20
#define K_SPACE 49
#define SCROLL_UP 5
#define SCROLL_DOWN 4
#define MOUSE_LEFT 1

typedef	enum {
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

typedef struct {
	int x;
	int y;
	double re_factor;
	double im_factor;
	double c_re;
	double c_im;
	double j_re;
	double j_im;
	int iterations;
	e_ftype ftype;
	int *pixels;
} calc_fract_data;


int from_blue_to_cyan(double percent);
int from_cyan_to_green(double percent);
int from_green_to_yellow(double percent);
int from_yellow_to_red(double percent);
void color_dump(t_fract *fract, calc_fract_data *fdata, int fin_iter);

void create(t_fract *fract);
void multi_thread(void *fr);
void calculate(t_fract *fract, int step, int num);
int is_in_set(calc_fract_data *fdata);
void define_fract(calc_fract_data *fdata, double *Z_re, double *Z_im);

int key_press(int button, void *param);
int mouse_hook(int button, int x, int y, void *param);
int mouse_move(int x, int y, void *param);
void move_fr(int button, t_fract *fract);

void btn_increase_pressed(int button, t_fract *fract);
void reset(t_fract *fract);
void color_change(t_fract *fract);
void change_fract(t_fract *fract, int button);
int iter_increase();

void putpixel(int **data, unsigned x, unsigned y, unsigned color);
void color_pixel(calc_fract_data *fdata, int fin_iter);

void set_im_re(int start, calc_fract_data *fdata, t_fract *fract);
void initialize(t_fract *fract, calc_fract_data *fdata);
void clear_image(t_fract *fract);

int setup_mlx(t_fract* fract);
void setup(t_fract* fract);
void mlx_hooks_setup(t_fract *fract);

void menu_init(t_fract *fract);
char *get_iteration(t_fract *fract);
char *get_zoom(t_fract *fract);


#endif
