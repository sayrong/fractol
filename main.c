

#include "mlx.h"
#include <stdlib.h>

#include <stdio.h>

typedef struct s_fdf {
    void *mlx;
    void *win;
    void *img;
    float scale;
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

void mondel(t_fdf *fract, float some) {

    double ImageHeight = 800;
    double ImageWidth = 800;

    //Минимальная действительная часть
    double MinRe = -2.0 * fract->scale + some;
    //Максимальная дейсвительная часть
    double MaxRe = 1.0 * fract->scale - some;
    //Минимальная мнимая часть
    double MinIm = -1.2 * fract->scale;
    //Чтобы не было растяжения изображения
    //Предствим максимальную мнимую часть через отношение 
    double MaxIm = MinIm+(MaxRe-MinRe)*ImageHeight/ImageWidth;
    //Чтобы перевести пиксель в действительную часть и мнимую
    //c_re = MinRe + x*(MaxRe-MinRe)/(ImageWidth-1);
    //c_im = MaxIm - y*(MaxIm-MinIm)/(ImageHeight-1);

    //Упростим. 
    //Чтобы получить пропорциональность разделим всю область действительной части на ширину пиксельно
    double Re_factor = (MaxRe-MinRe)/(ImageWidth-1);
    //Также с мнимой частью
    double Im_factor = (MaxIm-MinIm)/(ImageHeight-1);
    unsigned MaxIterations = 200;

    mlx_destroy_image(fract->mlx, fract->img);
    fract->img = mlx_new_image(fract->mlx, 800, 800);

    int	bpp;
    int	size_l;
    int	endian;
    int	*data = (int *)mlx_get_data_addr(fract->img, &bpp, &size_l, &endian);

    //Проходим попиксельно по высоте
    for(unsigned y=0; y<ImageHeight; ++y)
    {
        //Вычисляем мнимую часть
        double c_im = MaxIm - y*Im_factor;
        //Проходим по всей широте
        for(unsigned x=0; x<ImageWidth; ++x)
        {
            //Вычисляем действительную часть
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
                Z_im = 2*Z_re*Z_im + c_im;
                Z_re = Z_re2 - Z_im2 + c_re;
            }
            //if(isInside) { putpixel(data, x, y); }
        }
    }
    mlx_put_image_to_window(fract->mlx, fract->win, fract->img, 0, 0);
}

// void increase(void* mlx, void* img) {
//     mlx_destroy_image(mlx, img);
    
// }

int mouse_move(int x, int y, void *param) {
    printf("Move (%d, %d)\n", x, y);
    return 1;
}

int mouse_hook(int button, int x, int y, void *param) {
    t_fdf *fract = (t_fdf *)param;
    printf("Button %d (%d, %d)\n", button, x, y);
    //scroll up
    if (button == 5) {
        fract->scale = fract->scale - 0.01; 

        float z = (y - 400) * 0.01;

        mondel(fract, z);
    }
    //scroll down
    if (button == 4) {

    }

    return 0;
}


int main(int ac, char **av)
{
    t_fdf fract;
    
    int a = ac;
    char **b = av;

    fract.mlx = mlx_init();
    fract.win = mlx_new_window(fract.mlx, 800, 800, "fractol");
    fract.img = mlx_new_image(fract.mlx, 800, 800);
    fract.scale = 1;

    

    mondel(&fract, 0);
    

    // mlx_key_hook(win, increase, 125);
    // mlx_key_hook(win, decrease, 125);

    mlx_hook(fract.win, 6, 0L, mouse_move, 0);
    mlx_hook(fract.win, 4, 0L, mouse_hook, &fract);

    mlx_loop(fract.mlx);
    return 0;
}
