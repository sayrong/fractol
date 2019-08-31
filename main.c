

#include "mlx.h"
#include <stdlib.h>


void putpixel(int **data, unsigned x, unsigned y) {
    (*data)[x + y * 500] = 16777215;
}

void mondel(int **data) {

    double ImageHeight = 500;
    double ImageWidth = 500;

    double MinRe = -2.0;
    double MaxRe = 1.0;
    double MinIm = -1.2;
    double MaxIm = MinIm+(MaxRe-MinRe)*ImageHeight/ImageWidth;
    double Re_factor = (MaxRe-MinRe)/(ImageWidth-1);
    double Im_factor = (MaxIm-MinIm)/(ImageHeight-1);
    unsigned MaxIterations = 5;

    for(unsigned y=0; y<ImageHeight; ++y)
    {
        double c_im = MaxIm - y*Im_factor;
        for(unsigned x=0; x<ImageWidth; ++x)
        {
            double c_re = MinRe + x*Re_factor;

            double Z_re = c_re, Z_im = c_im;
            int isInside = 1; 
            for(unsigned n=0; n<MaxIterations; ++n)
            {
                double Z_re2 = Z_re*Z_re, Z_im2 = Z_im*Z_im;
                if(Z_re2 + Z_im2 > 4)
                {
                    isInside = 0;
                    break;
                }
                Z_im = 2*Z_re*Z_im + c_im;
                Z_re = Z_re2 - Z_im2 + c_re;
            }
            if(isInside) { putpixel(data, x, y); }
        }
    }

}



int main(int ac, char **av)
{
    int a = ac;
    char **b = av;

    void *mlx = mlx_init();
    void *win = mlx_new_window(mlx, 500, 500, "fractol");
    void *img_ptr = mlx_new_image(mlx, 500, 500);

    mlx_put_image_to_window(mlx, win, img_ptr, 0, 0);

    int	bpp;
    int	size_l;
    int	endian;

    int	*data = (int *)mlx_get_data_addr(img_ptr, &bpp, &size_l, &endian);

    mondel(&data);
    
    mlx_put_image_to_window(mlx, win, img_ptr, 0, 0);

    mlx_loop(mlx);
    return 0;
}
