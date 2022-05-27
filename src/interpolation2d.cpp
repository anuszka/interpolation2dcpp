#include <gsl/gsl_math.h>
#include <gsl/gsl_interp2d.h>
#include <gsl/gsl_spline2d.h>
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

void Interpolation2D::allocSpline(size_t data_grid_x_size_, size_t data_grid_y_size_)
{
    spline = gsl_spline2d_alloc(my_gsl_interp2d_type, data_grid_x_size_, data_grid_y_size_);
    return;
}

void Interpolation2D::allocAccel()
{
    xacc = gsl_interp_accel_alloc();
    yacc = gsl_interp_accel_alloc();
    return;
}

void Interpolation2D::allocSplineAccel(size_t data_grid_x_size_, size_t data_grid_y_size_)
{
    allocSpline(data_grid_x_size_, data_grid_y_size_);
    allocAccel();
}

void Interpolation2D::initSpline(double *data_grid_z_)
{
    gsl_spline2d_init(spline, data_grid_x, data_grid_y, data_grid_z_, data_grid_x_size, data_grid_y_size);
}

void Interpolation2D::setGrid()
{
    size_t M = 2;
    data_grid_x_size = M;
    data_grid_y_size = M;
    data_grid_x = new double[data_grid_x_size]{0.0, 1.0};
    data_grid_y = new double[data_grid_y_size]{0.0, 1.0};
    data_grid_z = new double[data_grid_x_size * data_grid_y_size];
    
    return(allocSplineAccel(data_grid_x_size, data_grid_y_size));
}

void Interpolation2D::setData()
{
    setGrid();
    /* set z grid values */
    // for(xi...)
    //  for(yi...)
    gsl_spline2d_set(spline, data_grid_z, 0, 0, 0.0);
    gsl_spline2d_set(spline, data_grid_z, 0, 1, 1.0);
    gsl_spline2d_set(spline, data_grid_z, 1, 1, 0.5);
    gsl_spline2d_set(spline, data_grid_z, 1, 0, 1.0);

    return(initSpline(data_grid_z));
}

double Interpolation2D::getInterpolation(double xi_, double yj_)
{
    return (gsl_spline2d_eval(spline, xi_, yj_, xacc, yacc));
}