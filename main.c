

#include "mlx.h"
#include <stdlib.h>

#include <stdio.h>
#include "libft.h"
#include <pthread.h>

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

typedef struct s_fdf {
    void *mlx;
    void *win;
    void *img;
    t_viewpoint *point;
}               t_fdf;




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
    (*data)[x + y * 800] = color;
}


void multiThread(int number) {
	int ImageHeight = 800;
	int ImageWidth = 800;
	
	int img_h_per_thread = 800 / 4;
	int img_w_per_thread = 800 / 4;
	
	for(unsigned y = img_h_per_thread * number; y < ImageHeight; ++y) {
		for(unsigned x=0; x<ImageWidth; ++x) {
			
		}
	}
}




void create() {
	
	pthread_t threads[4];
	
	int i = 0;
	for (i = 0; i < 4; i++) {
		pthread_create(threads + i, NULL, multiThread, (void *)i);
	}
}




void mondel(t_fdf *fract) {

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
    unsigned MaxIterations = 40;

    //mlx_destroy_image(fract->mlx, fract->img);
    //fract->img = mlx_new_image(fract->mlx, 800, 800);

    int	bpp;
    int	size_l;
    int	endian;
    int	*data = (int *)mlx_get_data_addr(fract->img, &bpp, &size_l, &endian);
    
    
    ft_bzero(data, 800*800 * 4);
	mlx_put_image_to_window(fract->mlx, fract->win, fract->img, 0, 0);
    //int a = mlx_clear_window(fract->mlx, fract->win);
    
    //Проходим попиксельно по высоте
    for(unsigned y=0; y<ImageHeight; ++y)
    {
        //Вычисляем мнимую часть
		double c_im = MaxIm - y*Im_factor * fract->point->scale - fract->point->moveY;
        //Проходим по всей широте
        for(unsigned x=0; x<ImageWidth; ++x)
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
            //if(isInside) { putpixel(data, x, y); }
        }
    }
    putpixel(&data, 400, 400, 255 << 8);
    mlx_put_image_to_window(fract->mlx, fract->win, fract->img, 0, 0);
}

// void increase(void* mlx, void* img) {
//     mlx_destroy_image(mlx, img);
    
// }

void scale(t_fdf *fract, double scale, int x, int y) {
    double width;
    double height;
    double newWidth;
    double newHeight;
    
    width = (fract->point->max->re - fract->point->min->re) * fract->point->scale;
    height = (fract->point->max->im - fract->point->min->im) * fract->point->scale;
    
    fract->point->scale *= scale;
    
    newWidth = (fract->point->max->re - fract->point->min->re) * fract->point->scale;
    newHeight = (fract->point->max->im - fract->point->min->im) * fract->point->scale;
    
    fract->point->moveX += ((double)x / 800) * (width - newWidth);
    fract->point->moveY += ((double)y / 800) * (height - newHeight);
}

int mouse_move(int x, int y, void *param) {
    printf("Move (%d, %d)\n", x, y);
    return 1;
}

int mouse_hook(int button, int x, int y, void *param) {
    t_fdf *fract = (t_fdf *)param;
    printf("Button %d (%d, %d)\n", button, x, y);
    //scroll up
    if (button == 5) {
        
        scale(fract, 0.9, x, y);
        
    }
    //scroll down
    if (button == 4) {
        
        scale(fract, 1.1, x, y);
        
    }
	
	mondel(fract);
	
	if (button == 1) {
		
		int	bpp;
		int	size_l;
		int	endian;
		int	*data = (int *)mlx_get_data_addr(fract->img, &bpp, &size_l, &endian);
		ft_bzero(data, 800*800 * 3);
		char *aa = (char*)data;
		int size = 800 * 800;
//		while (size--) {
//			aa[size] = 0;
//		}
		
//		while (size--) {
//			data[size] = 0;
//		}

		
		//putpixel(&data, 200, 200, 255 << 8);
		mlx_put_image_to_window(fract->mlx, fract->win, fract->img, 0, 0);
	}
    
	

    return 0;
}



int main(int ac, char **av)
{
    t_fdf fract;
    
    t_viewpoint point;
    t_complex_n defMax;
    t_complex_n defMin;
    
    defMax.re = 1.0;
    defMax.im = 1.2;
    defMin.re = -2.0;
    defMin.im = -1.2;
    
//    defMax.re = 0.54999216243581273;
//    defMax.im = 0.68203202655607631;
//    defMin.re = 0.049676711445815321;
//    defMin.im = 0.28177966576407854;
    
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

    mondel(&fract);
    

    // mlx_key_hook(win, increase, 125);
    // mlx_key_hook(win, decrease, 125);

    mlx_hook(fract.win, 6, 0L, mouse_move, 0);
    mlx_hook(fract.win, 4, 0L, mouse_hook, &fract);

    mlx_loop(fract.mlx);
    return 0;
}
