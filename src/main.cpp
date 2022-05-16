// https://www.gnu.org/software/gsl/doc/html/interp.html#c.gsl_interp2d_eval
// 2D Interpolation Example programs
// my_gsl_interp2d_typehe following example performs bilinear interpolation on the unit square,
// using z values of (0,1,0.5,1) going clockwise around the square.

#include <stdio.h>
#include <stdlib.h>

// #include <gsl/gsl_math.h>
// #include <gsl/gsl_interp2d.h>
// #include <gsl/gsl_spline2d.h>

#include "include/interpolation2d.h"

int main(void)
{
    Interpolation2D myinterp;
    myinterp.setData();

    const size_t N = 100; /* number of points to interpolate */
    size_t i, j;

    for (i = 0; i < N; ++i)
    {
        double xi = i / (N - 1.0);

        for (j = 0; j < N; ++j)
        {
            double yj = j / (N - 1.0);
            double zij = myinterp.getInterpolation(xi, yj);

            printf("%f %f %f\n", xi, yj, zij);
        }
        printf("\n");
    }

    // const gsl_interp2d_type *my_gsl_interp2d_type = gsl_interp2d_bilinear;
    // const size_t N = 100;                    /* number of points to interpolate */
    // //const double data_grid_x[] = {0.0, 1.0}; /* define unit square */
    // //const double data_grid_y[] = {0.0, 1.0};

    // const size_t M = 2;

    // double *data_grid_x = new double[M]{0.0, 1.0};
    // double *data_grid_y = new double[M]{0.0, 1.0};

    // size_t data_grid_x_size = M; /* x grid points */
    // size_t data_grid_y_size = M; /* y grid points */
    
    // double *data_grid_z = (double *)malloc(data_grid_x_size * data_grid_y_size * sizeof(double));
    // // double *data_grid_z = (double *)malloc(data_grid_x_size * data_grid_y_size * sizeof(double));
    
    // gsl_spline2d *spline = gsl_spline2d_alloc(my_gsl_interp2d_type, data_grid_x_size, data_grid_y_size);
    // gsl_interp_accel *xacc = gsl_interp_accel_alloc();
    // gsl_interp_accel *yacc = gsl_interp_accel_alloc();
    // size_t i, j;

    // /* set z grid values */
    // gsl_spline2d_set(spline, data_grid_z, 0, 0, 0.0);
    // gsl_spline2d_set(spline, data_grid_z, 0, 1, 1.0);
    // gsl_spline2d_set(spline, data_grid_z, 1, 1, 0.5);
    // gsl_spline2d_set(spline, data_grid_z, 1, 0, 1.0);

    // /* initialize interpolation */
    // gsl_spline2d_init(spline, data_grid_x, data_grid_y, data_grid_z, data_grid_x_size, data_grid_y_size);

    // /* interpolate N values in x and y and print out grid for plotting */
    // for (i = 0; i < N; ++i)
    // {
    //     double xi = i / (N - 1.0);

    //     for (j = 0; j < N; ++j)
    //     {
    //         double yj = j / (N - 1.0);
    //         double zij = gsl_spline2d_eval(spline, xi, yj, xacc, yacc);

    //         printf("%f %f %f\n", xi, yj, zij);
    //     }
    //     printf("\n");
    // }

    // printf("data_grid_x_size = %d, data_grid_y_size =  %d\n", (int)data_grid_x_size, (int)data_grid_y_size);
    // gsl_spline2d_free(spline);
    // gsl_interp_accel_free(xacc);
    // gsl_interp_accel_free(yacc);
    // free(data_grid_z);

    return 0;
}