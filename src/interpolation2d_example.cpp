#include <stdio.h>
#include <stdlib.h>
#include <gsl/gsl_math.h>
#include <gsl/gsl_interp2d.h>
#include <gsl/gsl_spline2d.h>
#include "include/interpolation2d_example.h"
#include "include/interpolation2d.h"
#include "include/griddatainterface.h"

void interpolation2d_example(size_t N_)
{
    // From:
    // https://www.gnu.org/software/gsl/doc/html/interp.html#c.gsl_interp2d_eval
    // 2D Interpolation Example programs
    // the following example performs bilinear interpolation on the unit square,
    // using z values of (0,1,0.5,1) going clockwise around the square.

    const gsl_interp2d_type *my_gsl_interp2d_type = gsl_interp2d_bilinear;
    const size_t N = N_; /* number of points to interpolate */
    // const double data_grid_x[] = {0.0, 1.0}; /* define unit square */
    // const double data_grid_y[] = {0.0, 1.0};

    const size_t M = 2;

    // Note that I changed the original example from GSL documentation:
    // Here, the grid point values are 0. and 10. to make it clear that
    // the int numbers 0 and 1 in gsl_spline2d_set() are grid point numbering and not grid point values.
    double *data_grid_x = new double[M]{0.0, 10.0};
    double *data_grid_y = new double[M]{0.0, 10.0};

    size_t data_grid_x_size = M; /* x grid points */
    size_t data_grid_y_size = M; /* y grid points */

    double *data_grid_z = (double *)malloc(data_grid_x_size * data_grid_y_size * sizeof(double));

    gsl_spline2d *spline = gsl_spline2d_alloc(my_gsl_interp2d_type, data_grid_x_size, data_grid_y_size);
    gsl_interp_accel *xacc = gsl_interp_accel_alloc();
    gsl_interp_accel *yacc = gsl_interp_accel_alloc();
    size_t i, j;

    /* set z grid values */
    // The int numbers 0 and 1 in gsl_spline2d_set() are grid point numbering and not grid point values.
    gsl_spline2d_set(spline, data_grid_z, 0, 0, 0.0);
    gsl_spline2d_set(spline, data_grid_z, 0, 1, 1.0);
    gsl_spline2d_set(spline, data_grid_z, 1, 1, 0.5);
    gsl_spline2d_set(spline, data_grid_z, 1, 0, 1.0);

    /* initialize interpolation */
    gsl_spline2d_init(spline, data_grid_x, data_grid_y, data_grid_z, data_grid_x_size, data_grid_y_size);

    /* interpolate N values in x and y and print out grid for plotting */
    for (i = 0; i < N; ++i)
    {
        // Differently than in the original example in GSL documentation,
        // I rescaled the interpolation point positions according to the grid limits (which are here data_grid_x[1] and data_grid_y[1]).
        double xi = data_grid_x[1] * i / (N - 1.0);

        for (j = 0; j < N; ++j)
        {
            double yj = data_grid_y[1] * j / (N - 1.0);
            double zij = gsl_spline2d_eval(spline, xi, yj, xacc, yacc);
            // Get derivative
            double dzdx = gsl_spline2d_eval_deriv_x(spline, xi, yj, xacc, yacc);
            double dzdy = gsl_spline2d_eval_deriv_y(spline, xi, yj, xacc, yacc);
            printf("%f,%f,%f,%f,%f\n", xi, yj, zij, dzdx, dzdy); // I format the output for CSV file
        }
        // printf("\n");
    }
    gsl_spline2d_free(spline);
    gsl_interp_accel_free(xacc);
    gsl_interp_accel_free(yacc);
    free(data_grid_z);
}

void interpolation2d_class_file_example(size_t N_)
{
    const std::string path = "./input/in.csv";
    
    GridDataInterface grid_data(path);

    Interpolation2D myinterp;
    myinterp.setData(grid_data);

    const size_t N = N_;  /* number of points to interpolate */

    double xmax = grid_data.getXgrid().back();
    double ymax = grid_data.getYgrid().back();

    for (size_t i = 0; i < N; ++i)
    {
        double xi = xmax * i / (N - 1.0);

        for (size_t j = 0; j < N; ++j)
        {
            double yj = ymax * j / (N - 1.0);
            double zij = myinterp.getInterpolation(xi, yj);
            // Get derivative
            double dzdx = myinterp.getInterpolationDerivX(xi, yj);
            double dzdy = myinterp.getInterpolationDerivY(xi, yj);
            printf("%f,%f,%f,%f,%f\n", xi, yj, zij, dzdx, dzdy);
        }
    }
}