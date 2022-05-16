#include <cstdio>
#include "include/interpolation2d.h"

Interpolation2D::Interpolation2D()
{
    my_gsl_interp2d_type = gsl_interp2d_bilinear;
}

Interpolation2D::~Interpolation2D()
{
    gsl_spline2d_free(spline);
    gsl_interp_accel_free(xacc);
    gsl_interp_accel_free(yacc);
    free(data_grid_z);
}

void Interpolation2D::initSpline() // Niepotrzebne?
{
    spline = gsl_spline2d_alloc(my_gsl_interp2d_type, data_grid_x_size, data_grid_y_size);
    return;
}

void Interpolation2D::setData()
{
    int M = 2;
    data_grid_x_size = (size_t)M;
    data_grid_y_size = (size_t)M;

    data_grid_x = new double[M]{0.0, 1.0};
    data_grid_y = new double[M]{0.0, 1.0};
    double *data_grid_z = (double *)malloc(data_grid_x_size * data_grid_y_size * sizeof(double));

  
    spline = gsl_spline2d_alloc(my_gsl_interp2d_type, data_grid_x_size, data_grid_y_size);
    xacc = gsl_interp_accel_alloc();
    yacc = gsl_interp_accel_alloc();
    /* set z grid values */
    gsl_spline2d_set(spline, data_grid_z, 0, 0, 0.0);
    gsl_spline2d_set(spline, data_grid_z, 0, 1, 1.0);
    gsl_spline2d_set(spline, data_grid_z, 1, 1, 0.5);
    gsl_spline2d_set(spline, data_grid_z, 1, 0, 1.0);

    return;
    // return initSpline();
}

double Interpolation2D::getInterpolation(double xi, double yj)
{
    return (gsl_spline2d_eval(spline, xi, yj, xacc, yacc));
}