
#include "fractol.h"


void menu_init(t_fract *fract)
{
    char *iter_label = "Iterations ";
    char *inum = ft_itoa(fract->iterations);
    iter_label = ft_strjoin(iter_label, inum);
    mlx_string_put(fract->mlx, fract->win, 10, 10, \
                   0xFFFFFF, iter_label);
	char *zoom_label = "Zoom ";
	char *znum = ft_itoa((int) (1/fract->point->scale * 100));
	printf("%f\n",fract->point->scale);
	zoom_label = ft_strjoin(zoom_label, znum);
	mlx_string_put(fract->mlx, fract->win, 10, 25, \
				   0xFFFFFF, zoom_label);
	
}


int from_blue_to_cyan(double percent)
{
    int green;
    int blue;
    
    green = 255 * percent;
    blue = 255;
    return ((green << 8) | (blue));
}

int from_cyan_to_green(double percent)
{
    int green;
    int blue;
    
    green = 255;
    blue = 255 * percent;
    return ((green << 8) | (blue));
}

int from_green_to_yellow(double percent)
{
    int red;
    int green;
    
    green = 255;
    red = 255 * percent;
    return (red << 16 | green << 8);
}

int from_yellow_to_red(double percent)
{
    int red;
    int green;
    
    green = 255 * percent;
    red = 255;
    return (red << 16 | green << 8);
}

int from_black_to_red(float percent) {
    int red = 255 * percent;
    return red << 16;
}

int from_red_to_white(double percent) {
    int red = 255;
    int green = 255 * percent;
    int blue = 255 * percent;
    return ((red << 16) | (green << 8) | blue);
}

void putpixel(int **data, unsigned x, unsigned y, unsigned color) {
    if (x + y * WIN_WIDTH > WIN_HEIGHT * WIN_WIDTH)
    {
        printf("Oversize x %d, y %d\n", x, y);
        return ;
    }
    (*data)[x + y * WIN_WIDTH] = color;
}


//void mondel(t_fdf *fract, unsigned startY, unsigned endY, unsigned startX, unsigned endX);
//
//
//void multiThread(void * fr) {
//    static int a = 0;
//    t_fdf* fract = (t_fdf*)fr;
//    if (a == 0) {
//        mondel(fract, 0, 800/2, 0, 800/2);
//    }
//    if (a == 1) {
//        mondel(fract, 0, 800/2, 800/2, 800);
//    }
//    if (a == 2) {
//        mondel(fract, 800/2, 800, 0, 800/2);
//    }
//    if (a == 3) {
//        mondel(fract, 800/2, 800, 800/2, 800);
//    }
//    a++;
//    if (a == 4) {
//        a = 0;
//    }
//}

int is_in_set1(double c_re, double c_im, int iterations) {
	int i;
	double c_im_tmp;
	double Z_re;
	double Z_im;
	
	i = 0;
	Z_re = c_re;
	Z_im = c_im;
	while ((i < iterations) && ((Z_re * Z_re + Z_im * Z_im) < 4)) {
		c_im_tmp = Z_im;
		Z_im = 2 * Z_re * Z_im + c_im;
		Z_re = Z_re * Z_re - c_im_tmp * c_im_tmp + c_re;
		i++;
	}
	if (i == iterations)
		return (-1);
	return (i);
}

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

void define_fract(calc_fract_data *fdata, double *Z_re, double *Z_im) {
	if (fdata->ftype == mandelbrot)
	{
		*Z_re += fdata->c_re;
		*Z_im += fdata->c_im;
	}
	else if (fdata->ftype == julia)
	{
		*Z_re += fdata->j_re;
		*Z_im += fdata->j_im;
	}
	else if (fdata->ftype == burningship)
	{
		*Z_re = fabs(*Z_re + fdata->c_re);
		*Z_im = -fabs(*Z_im + fdata->c_im);
	}
}

int is_in_set(calc_fract_data *fdata) {
	int i;
	double c_im_tmp;
	double Z_re;
	double Z_im;
	
	i = 0;
	Z_re = fdata->c_re;
	Z_im = fdata->c_im;
	while ((i < fdata->iterations) && ((Z_re * Z_re + Z_im * Z_im) < 4)) {
		c_im_tmp = Z_im;
		Z_im = 2 * Z_re * Z_im;
		Z_re = Z_re * Z_re - c_im_tmp * c_im_tmp;
		define_fract(fdata, &Z_re, &Z_im);
		i++;
	}
	if (i == fdata->iterations)
		return (-1);
	return (i);
}



void set_im_re(int start, calc_fract_data *fdata, t_fract *fract)
{
	fdata->y = start / WIN_WIDTH;
	fdata->x = start % WIN_HEIGHT;
	fdata->c_im = fract->point->max->im - fract->point->moveY - fdata->y * fdata->im_factor;
	fdata->c_re = fract->point->min->re + fract->point->moveX + fdata->x * fdata->re_factor;
}

void initialize(t_fract *fract, calc_fract_data *fdata)
{
	fdata->re_factor = (fract->point->max->re - fract->point->min->re)/(WIN_WIDTH-1) * fract->point->scale;
	fdata->im_factor = (fract->point->max->im - fract->point->min->im)/(WIN_HEIGHT-1) * fract->point->scale;
	fdata->iterations = fract->iterations;
	fdata->pixels = fract->data;
    fdata->j_im = fract->j_im;
    fdata->j_re = fract->j_re;
    fdata->ftype = fract->ftype;
}

void color_pixel(calc_fract_data *fdata, int n) {

    
    
    int part;
    
    if (n == -1)
    {
        putpixel(&fdata->pixels, fdata->x, fdata->y, 0);
    }
    
    part = fdata->iterations / 5;
    if (n < 0)
        return ;
    if (n < part)
        putpixel(&fdata->pixels, fdata->x, fdata->y, from_blue_to_cyan((double)n/part));
    else if (n < 2 * part)
        putpixel(&fdata->pixels, fdata->x, fdata->y, from_cyan_to_green((double)n/part*2));
    else if (n < (3 * part))
        putpixel(&fdata->pixels, fdata->x, fdata->y, from_blue_to_cyan((double)n/part*3));
    else if (n < (4 * part))
        putpixel(&fdata->pixels, fdata->x, fdata->y, from_yellow_to_red((double)n/part*4));
    //else
        //putpixel(&fdata->pixels, fdata->x, fdata->y, from_red_to_white((double)n/(fdata->iterations)));
}

void calculate(t_fract *fract, int step, int num) {
	int start_point;
	int end_point;
	calc_fract_data fdata;
	int finish_iteration;
	
	initialize(fract, &fdata);
	start_point = step * num;
	end_point = start_point + step;
	while (start_point++ < end_point) {
		set_im_re(start_point, &fdata, fract);
		finish_iteration = is_in_set(&fdata);
		//color_pixel(&fdata, finish_iteration);
        if (fdata.x < WIN_WIDTH && fdata.y < WIN_WIDTH)
        {

            //int color = mlx_get_color_value(fract->mlx, finish_iteration + (255 << 16));
            int color = fract->color * finish_iteration;//(finish_iteration * fract->iterations) | ((fract->iterations % 255) << 14);
            putpixel(&fdata.pixels, fdata.x, fdata.y, color);
        }
	}
}


void mondelNew(t_fract *fract, int step, int num) {
    double Re_factor = (fract->point->max->re - fract->point->min->re)/(WIN_WIDTH-1) * fract->point->scale;
    double Im_factor = (fract->point->max->im - fract->point->min->im)/(WIN_HEIGHT-1) * fract->point->scale;
    unsigned MaxIterations = 120;
    
    int    *data = (int *)mlx_get_data_addr(fract->img, &fract->bpp, &fract->size_l, &fract->endian);
    
    int start = step * num;
    printf("start - %d\n", start);
    int end = start + step;
    printf("end - %d\n", end);
    
    while (start++ < end) {
        int y = start / WIN_WIDTH;
        int x = start % WIN_HEIGHT;
        double c_im = fract->point->max->im - fract->point->moveY - y*Im_factor;
        double c_re = fract->point->min->re + fract->point->moveX + x*Re_factor;
		
        int isInside = 1;
//        for(unsigned n=0; n<MaxIterations; ++n)
//        {
//            //Находим абсолютеное значение Z и возводим в квадрат чтобы избавиться от корня
//            double Z_re2 = Z_re*Z_re, Z_im2 = Z_im*Z_im;
//            if(Z_re2 + Z_im2 > 4)
//            {
//                if (n < MaxIterations/2) {
//                    float p = (float)n / (MaxIterations/2);
//                    putpixel(&data, x, y, from_black_to_red(p));
//                } else {
//                    float p1 = (float)n / MaxIterations;
//                    putpixel(&data, x, y, from_red_to_white(p1));
//                }
//                isInside = 0;
//                break;
//            }
//            //вычисление квадрата комплексного числа
//            //(a+bi)^2 = a^2 - b^2 + 2abi
//            //действительная часть a^2 - b^2
//            //мнимая 2abi
//            //ко всему этому прибавляем первоначально значение
//            Z_im = 2*Z_re*Z_im + c_im;
//            Z_re = Z_re2 - Z_im2 + c_re;
//        }
//        if(isInside) { putpixel(&data, x, y, 255 << 8); }
		int n = 1;//is_in_mondelbrot_set(c_re, c_im, MaxIterations);
		if (n == -1) {
			putpixel(&data, x, y, 255 << 8);
		} else {
			if (n < MaxIterations/2) {
				float p = (float)n / (MaxIterations/2);
				putpixel(&data, x, y, from_black_to_red(p));
				} else {
				float p1 = (float)n / MaxIterations;
				putpixel(&data, x, y, from_red_to_white(p1));
				}
		}
		
		
    }
}




void multiThread(void *fr) {

//    static int num = 0;
   int step = (WIN_WIDTH * WIN_HEIGHT)/ THREADS_NUM;
//    t_fract* fract = (t_fract*)fr;
//    if (num == THREADS_NUM){
//        num = 0;
//    }
//    mondelNew(fract, step, num++);
	
	t_thread *n = (t_thread*) fr;
	//mondelNew(n->fr, step, n->i);
	calculate(n->fr, step, n->i);
	printf("NUMBER - %d\n", n->i);
}


void create(t_fract *fract) {
    
    pthread_t threads[THREADS_NUM];
	mlx_clear_window(fract->mlx, fract->win);
	int i = 0;
    while (i < THREADS_NUM)
    {
		t_thread *new = (t_thread*)malloc(sizeof(t_thread));
		new->fr = fract;
		new->i = i;
        pthread_create(threads + i, NULL, multiThread, (void *)new);
        i++;
    }
    while (i--)
    {
       pthread_join(threads[i], NULL);
    }
    mlx_put_image_to_window(fract->mlx, fract->win, fract->img, 0, 0);
    menu_init(fract);
}




void mondel(t_fract *fract, unsigned startY, unsigned endY, unsigned startX, unsigned endX) {

    double ImageHeight = 800;
    double ImageWidth = 800;

    
    //Минимальная действительная часть
    double MinRe = fract->point->min->re;//-2.0;
    //Максимальная дейсвительная часть
    double MaxRe = fract->point->max->re;//1.0;
    //Минимальная мнимая часть
    double MinIm = fract->point->min->im;//(-1.2);
    //Чтобы не было растяжения изображения
    //Предствим максимальную мнимую часть через отношение 
    double MaxIm = fract->point->max->im;//(1.2); //MinIm+(MaxRe-MinRe)*ImageHeight/ImageWidth;
    //Чтобы перевести пиксель в действительную часть и мнимую
    //c_re = MinRe + x*(MaxRe-MinRe)/(ImageWidth-1);
    //c_im = MaxIm - y*(MaxIm-MinIm)/(ImageHeight-1);

    
//    if (some != 0) {
//        double dif = (MaxIm - MinIm) * 0.1;
//        MinIm += dif;
//        MaxIm += dif;
//    }
//
    //Упростим.
    //Чтобы получить пропорциональность разделим всю область действительной части на ширину пиксельно
    double Re_factor = (MaxRe-MinRe)/(ImageWidth-1);
    //Также с мнимой частью
    double Im_factor = (MaxIm-MinIm)/(ImageHeight-1);
    unsigned MaxIterations = 150;

    //mlx_destroy_image(fract->mlx, fract->img);
    //fract->img = mlx_new_image(fract->mlx, 800, 800);

    int	bpp;
    int	size_l;
    int	endian;
    int	*data = (int *)mlx_get_data_addr(fract->img, &bpp, &size_l, &endian);
    
    
//    ft_bzero(data, 800*800 * 4);
//    mlx_put_image_to_window(fract->mlx, fract->win, fract->img, 0, 0);
    //int a = mlx_clear_window(fract->mlx, fract->win);
    
    //Проходим попиксельно по высоте
    for(unsigned y=startY; y<endY; ++y)
    {
        //Вычисляем мнимую часть
		double c_im = MaxIm - y*Im_factor * fract->point->scale - fract->point->moveY;
        //Проходим по всей широте
        for(unsigned x=startX; x<endX; ++x)
        {
            //Вычисляем действительную часть
			double c_re = MinRe + x*Re_factor * fract->point->scale + fract->point->moveX;

            //Проверяем на принадлежность
            double Z_re = c_re, Z_im = c_im;
            int isInside = 1; 
            for(unsigned n=0; n<MaxIterations; ++n)
            {
                //Находим абсолютеное значение Z и возводим в квадрат чтобы избавиться от корня
                double Z_re2 = Z_re*Z_re, Z_im2 = Z_im*Z_im;
                if(Z_re2 + Z_im2 > 4)
                {
                    if (n < MaxIterations/2) {
                        float p = (float)n / (MaxIterations/2);
                        putpixel(&data, x, y, from_black_to_red(p));
                    } else {
                        float p1 = (float)n / MaxIterations;
                        putpixel(&data, x, y, from_red_to_white(p1));
                    }
                    isInside = 0;
                    break;
                }
                //вычисление квадрата комплексного числа
                //(a+bi)^2 = a^2 - b^2 + 2abi
                //действительная часть a^2 - b^2
                //мнимая 2abi
                //ко всему этому прибавляем первоначально значение
                Z_im = 2*Z_re*Z_im + c_im;
                Z_re = Z_re2 - Z_im2 + c_re;
            }
            if(isInside) { putpixel(&data, x, y, 255 << 8); }
        }
        //putpixel(&data, x, y, 255 << 8);
    }
    putpixel(&data, 400, 400, 255 << 8);
    //mlx_put_image_to_window(fract->mlx, fract->win, fract->img, 0, 0);
}



//int isIncludedInMandelbrot() {
//
//}


void julia1(t_fract *fract, double re, double im) {
	double ImageHeight = 800;
	double ImageWidth = 800;
	
	double newRe, newIm, oldRe, oldIm;   //real and imaginary parts of new and old
	
	//Минимальная действительная часть
	double MinRe = fract->point->min->re;//-2.0;
	//Максимальная дейсвительная часть
	double MaxRe = fract->point->max->re;//1.0;
	//Минимальная мнимая часть
	double MinIm = fract->point->min->im;//(-1.2);
	//Чтобы не было растяжения изображения
	//Предствим максимальную мнимую часть через отношение
	double MaxIm = fract->point->max->im;
	
	double Re_factor = (MaxRe-MinRe)/(ImageWidth-1);
	double Im_factor = (MaxIm-MinIm)/(ImageHeight-1);
	
	double cRe, cIm;
	
	cRe = re;//-0.7;
	cIm = im;//0.27015;
	
	int MaxIterations = 2000;
	
	mlx_destroy_image(fract->mlx, fract->img);
	fract->img = mlx_new_image(fract->mlx, 800, 800);
	
	
	int	bpp;
	int	size_l;
	int	endian;
	int	*data = (int *)mlx_get_data_addr(fract->img, &bpp, &size_l, &endian);
	
	
	for (int y = 0; y < ImageHeight; y++) {
		//Вычисляем мнимую часть
		double c_im = MaxIm - y*Im_factor;
		
		for (int x = 0; x < ImageWidth; x++) {
			
			double c_re = MinRe + x*Re_factor;
			//Проверяем на принадлежность
			double Z_re = c_re, Z_im = c_im;
			int isInside = 1;
			
			for(unsigned n=0; n<MaxIterations; ++n)
			{
				//Находим абсолютеное значение Z и возводим в квадрат чтобы избавиться от корня
				double Z_re2 = Z_re*Z_re, Z_im2 = Z_im*Z_im;
				if(Z_re2 + Z_im2 > 4)
				{
					if (n < MaxIterations/2) {
						float p = (float)n / (MaxIterations/2);
						putpixel(&data, x, y, from_black_to_red(p));
					} else {
						float p1 = (float)n / MaxIterations;
						putpixel(&data, x, y, from_red_to_white(p1));
					}
					isInside = 0;
					break;
				}
				//вычисление квадрата комплексного числа
				//(a+bi)^2 = a^2 - b^2 + 2abi
				//действительная часть a^2 - b^2
				//мнимая 2abi
				//ко всему этому прибавляем первоначально значение
				Z_im = 2*Z_re*Z_im + cIm;
				Z_re = Z_re2 - Z_im2 + cRe;
			}
			
		}
	}
	mlx_put_image_to_window(fract->mlx, fract->win, fract->img, 0, 0);
	
}


void scale(t_fract *fract, double scale, int x, int y) {
    double width;
    double height;
    double newWidth;
    double newHeight;
    
    width = (fract->point->max->re - fract->point->min->re) * fract->point->scale;
    height = (fract->point->max->im - fract->point->min->im) * fract->point->scale;
    
    fract->point->scale *= scale;
    
    newWidth = (fract->point->max->re - fract->point->min->re) * fract->point->scale;
    newHeight = (fract->point->max->im - fract->point->min->im) * fract->point->scale;
    
    fract->point->moveX += ((double)x / WIN_WIDTH) * (width - newWidth);
    fract->point->moveY += ((double)y / WIN_HEIGHT) * (height - newHeight);
}

int mouse_move(int x, int y, void *param) {
    printf("Move (%d, %d)\n", x, y);
	
	t_fract *fract = (t_fract *)param;
	
	//Минимальная действительная часть
	double MinRe = -2.0;
	//Максимальная дейсвительная часть
	double MaxRe = 1.0;
	//Минимальная мнимая часть
	double MinIm = -1.2;
	//Чтобы не было растяжения изображения
	//Предствим максимальную мнимую часть через отношение
	double MaxIm = 1.2;
	
	double Re_factor = (MaxRe-MinRe)/(WIN_WIDTH-1);
	double Im_factor = (MaxIm-MinIm)/(WIN_HEIGHT-1);
	
	
	double c_im = MaxIm - y*Im_factor;
	double c_re = MinRe + x*Re_factor;
	
	if (fract->ftype == julia)
    {
        fract->j_im = c_im;
        fract->j_re = c_re;
        create(fract);
    }
//	julia(fract, c_re, c_im);
	
    return 1;
}

#define K_MINUS 27
#define K_PLUS 24
#define K_Q 12
#define K_A 0
#define K_Z 6
#define K_X 7

#define K_UP 126
#define K_DOWN 125
#define K_LEFT 123
#define K_RIGHT 124
#define K_1 18
#define K_2 19
#define K_3 20

void move_fr(int button, t_fract *fract)
{
	double moveX;
	double moveY;
	
	moveX = (fract->point->max->re - fract->point->min->re) * fract->point->scale * 0.1;
	moveY = (fract->point->max->im - fract->point->min->im) * fract->point->scale * 0.1;
	if (button == K_UP)
		fract->point->moveY -= moveY;
	else if (button == K_DOWN)
		fract->point->moveY += moveY;
	else if (button == K_LEFT)
		fract->point->moveX -= moveX;
	else if (button == K_RIGHT)
		fract->point->moveX += moveX;
}

int key_press(int button, void *param)
{
    t_fract *fract = (t_fract *)param;
    printf("Button %d\n", button);
    
	if (button >= 123 && button <= 126) {
		move_fr(button,fract);
	} else if (button == K_MINUS)
        fract->iterations -= 1;
    else if (button == K_PLUS)
        fract->iterations += 1;
    else if (button == K_Q)
    {
        fract->point->scale = 1;
        fract->point->moveX = 0;
        fract->point->moveY = 0;
        fract->iterations = 50;
    } else if (button == K_UP) {
        fract->color *= 1.1;
    } else if (button == K_DOWN)
    {
        fract->color = abs(fract->color / 1.1);
    } else if (button == K_1)
        fract->ftype = mandelbrot;
    else if (button == K_2)
        fract->ftype = julia;
	else if (button == K_3)
        fract->ftype = burningship;
    else if (button == K_A)
    {
        fract->point->max->im = 2;
        fract->point->max->re = 2;
        fract->point->min->im = -2;
        fract->point->min->re = -2;
    }
    create(fract);
    return 0;
}

int mouse_hook(int button, int x, int y, void *param) {
    t_fract *fract = (t_fract *)param;
    printf("Button %d (%d, %d)\n", button, x, y);
    //scroll up
    if (button == 5) {
        
        scale(fract, 0.9, x, y);
        fract->iterations += 50;
    }
    //scroll down
    if (button == 4) {
        
        scale(fract, 1.1, x, y);
        fract->iterations -= 50;
    }
	
	create(fract);
	
	if (button == 1) {
		
//		int	bpp;
//		int	size_l;
//		int	endian;
//		int	*data = (int *)mlx_get_data_addr(fract->img, &bpp, &size_l, &endian);
//		ft_bzero(data, 800*800 * 3);
//		char *aa = (char*)data;
//		int size = 800 * 800;
////		while (size--) {
////			aa[size] = 0;
////		}
//
////		while (size--) {
////			data[size] = 0;
////		}
//
//
//		//putpixel(&data, 200, 200, 255 << 8);
//		mlx_put_image_to_window(fract->mlx, fract->win, fract->img, 0, 0);
		
		
	}
    
	

    return 0;
}


void ship(t_fract *fract) {
	double ImageHeight = 800;
	double ImageWidth = 800;
	
	double newRe, newIm, oldRe, oldIm;   //real and imaginary parts of new and old
	
	//Минимальная действительная часть
	double MinRe = -2.0;
	//Максимальная дейсвительная часть
	double MaxRe = 2.0;
	//Минимальная мнимая часть
	double MinIm = 2;
	//Чтобы не было растяжения изображения
	//Предствим максимальную мнимую часть через отношение
	double MaxIm = -2;
	
	double Re_factor = (MaxRe-MinRe)/(ImageWidth-1);
	double Im_factor = (MaxIm-MinIm)/(ImageHeight-1);
	
	double cRe, cIm;
	

	
	int MaxIterations = 100;
	
	mlx_destroy_image(fract->mlx, fract->img);
	fract->img = mlx_new_image(fract->mlx, 800, 800);
	
	
	int	bpp;
	int	size_l;
	int	endian;
	int	*data = (int *)mlx_get_data_addr(fract->img, &bpp, &size_l, &endian);
	
	
	for (int y = 0; y < ImageHeight; y++) {
		//Вычисляем мнимую часть
		double c_im = MaxIm - y*Im_factor;
		
		for (int x = 0; x < ImageWidth; x++) {
			
			double c_re = MinRe + x*Re_factor;
			//Проверяем на принадлежность
			double Z_re = c_re, Z_im = c_im;
			int isInside = 1;
			
			for(unsigned n=0; n<MaxIterations; ++n)
			{
				//Находим абсолютеное значение Z и возводим в квадрат чтобы избавиться от корня
				double Z_re2 = Z_re*Z_re, Z_im2 = Z_im*Z_im;
				if(Z_re2 + Z_im2 > 4)
				{
					if (n < MaxIterations/2) {
						float p = (float)n / (MaxIterations/2);
						putpixel(&data, x, y, from_black_to_red(p));
					} else {
						float p1 = (float)n / MaxIterations;
						putpixel(&data, x, y, from_red_to_white(p1));
					}
					isInside = 0;
					break;
				}
				//вычисление квадрата комплексного числа
				//(a+bi)^2 = a^2 - b^2 + 2abi
				//действительная часть a^2 - b^2
				//мнимая 2abi
				//ко всему этому прибавляем первоначально значение
				Z_im = fabs(2*Z_re*Z_im) + c_im;
				Z_re = fabs(Z_re2 - Z_im2 + c_re);
			}
			//if(isInside) { putpixel(&data, x, y, 255 << 8); }
		}
	}
	mlx_put_image_to_window(fract->mlx, fract->win, fract->img, 0, 0);
	
}

void setup_modelbrot(t_fract* fract) {
    fract->point->max->im = 1;
    fract->point->max->re = 1;
    fract->point->min->im = -1;
    fract->point->min->re = -2;
}


int setup_mlx(t_fract* fract)
{
    fract->mlx = mlx_init();
    fract->win = mlx_new_window(fract->mlx, WIN_WIDTH, WIN_HEIGHT, "fractol");
    fract->img = mlx_new_image(fract->mlx, WIN_WIDTH, WIN_HEIGHT);
    fract->data = (int *)mlx_get_data_addr(fract->img, &fract->bpp, &fract->size_l, &fract->endian);
    if (fract->mlx == NULL || fract->win == NULL || fract->img == NULL || fract->data == NULL)
        return (1);
    return (0);
}

int select_fractal(t_fract *fract, char *name)
{
    if (!ft_strcmp(name, "mandelbrot"))
    {
        fract->ftype = mandelbrot;
        setup_modelbrot(fract);
    }
    else if (!ft_strcmp(name, "julia"))
    {
        fract->ftype = julia;
    }
    else if (!ft_strcmp(name, "burningship"))
    {
        fract->ftype = burningship;
    } else {
        return (1);
    }
    fract->iterations = 50;
    fract->color = 252;
    return (0);
}

void init_fract(t_fract **fract) {
    t_fract new;
    t_viewpoint point;
    t_complex_n defMax;
    t_complex_n defMin;
    
    new.point = &point;
    point.max = &defMax;
    point.min = &defMin;
    point.moveX = 0;
    point.moveY = 0;
    point.scale = 1;
    *fract = &new;
}

int main(int argc, char **argv) {
    t_fract *fract;
    
    t_fract new;
    t_viewpoint point;
    t_complex_n defMax;
    t_complex_n defMin;
    
    new.point = &point;
    point.max = &defMax;
    point.min = &defMin;
    point.moveX = 0;
    point.moveY = 0;
    point.scale = 1;
    fract = &new;
    
    if (argc != 2)
    {
        ft_putendl("usage: fractol \"name of fractol\" [mandelbrot,julia,burningship]");
        return (1);
    }
    //init_fract(&fract);
    if (select_fractal(fract, argv[1]))
    {
        ft_putendl("Wrong fractol name. Use [mandelbrot,julia,burningship]");
        return (1);
    }
    if (setup_mlx(fract))
    {
        ft_putendl("Error init mlx");
        return (1);
    }
    create(fract);
    mlx_hook(fract->win, 6, 0L, mouse_move, fract);
    mlx_hook(fract->win, 4, 0L, mouse_hook, fract);
    mlx_hook(fract->win, 2, 5, key_press, fract);
    mlx_loop(fract->mlx);
    return (0);
}


int main1(int ac, char **av)
{
    t_fract fract;
    
    t_viewpoint point;
    t_complex_n defMax;
    t_complex_n defMin;
    
    defMax.re = 1.0;
    defMax.im = 1.2;
    defMin.re = -2.0;
    defMin.im = -1.2;
	
    point.max = &defMax;
    point.min = &defMin;
    
    point.moveX = 0;
    point.moveY = 0;
    point.scale = 1;
    
    int a = ac;
    char **b = av;

    fract.mlx = mlx_init();
    fract.win = mlx_new_window(fract.mlx, 800, 800, "fractol");
    fract.img = mlx_new_image(fract.mlx, 800, 800);
    fract.point = &point;

    //mondel(&fract);
    
    //create(&fract);
	
	//julia(&fract, -0.7, 0.27015);
	
	ship(&fract);
	
    // mlx_key_hook(win, increase, 125);
    // mlx_key_hook(win, decrease, 125);

    mlx_hook(fract.win, 6, 0L, mouse_move, &fract);
    mlx_hook(fract.win, 4, 0L, mouse_hook, &fract);

    mlx_loop(fract.mlx);
    return 0;
}
