#include <gsl/gsl_math.h>
#include <gsl/gsl_interp2d.h>
#include <gsl/gsl_spline2d.h>
#include <cstdio>
#include <iostream>
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

void Interpolation2D::initSpline(
    double *data_grid_x_,
    double *data_grid_y_,
    double *data_grid_z_,
    size_t data_grid_x_size_,
    size_t data_grid_y_size_)
{
    gsl_spline2d_init(
        spline,
        data_grid_x_,
        data_grid_y_,
        data_grid_z_,
        data_grid_x_size_,
        data_grid_y_size_);
}



void Interpolation2D::setGrid(
    double *data_grid_x_,
    size_t data_grid_x_size_,
    double *data_grid_y_,
    size_t data_grid_y_size_)
{
    data_grid_x = data_grid_x_;
    data_grid_x_size = data_grid_x_size_;
    data_grid_y = data_grid_y_;
    data_grid_y_size = data_grid_y_size_;
    data_grid_z = new double[data_grid_x_size * data_grid_y_size];
    return (allocSplineAccel(data_grid_x_size, data_grid_y_size));
}



void Interpolation2D::setData(GridDataInterface grid_data_)
{
    setData(
        grid_data_.getXgridAsArrayPtr(),
        grid_data_.getXgridSize(),
        grid_data_.getYgridAsArrayPtr(),
        grid_data_.getYgridSize(),
        grid_data_.getZvaluesAsArrayPtr());
}

void Interpolation2D::setData(
    double *data_grid_x_,
    size_t data_grid_x_size_,
    double *data_grid_y_,
    size_t data_grid_y_size_,
    double *data_values_z_)
{
    setGrid(data_grid_x_, data_grid_x_size_, data_grid_y_, data_grid_y_size_);
    /* set z grid values */
    for (int xi = 0; xi < (int)data_grid_x_size; xi++)
        for (int yi = 0; yi < (int)data_grid_y_size; yi++)
        {
            gsl_spline2d_set(
                spline,
                data_grid_z,
                xi,
                yi,
                data_values_z_[(int)data_grid_y_size * xi + yi]);
        }
    return (initSpline(data_grid_x,
                       data_grid_y,
                       data_grid_z,
                       data_grid_x_size,
                       data_grid_y_size));
}

double Interpolation2D::getInterpolation(double xi_, double yj_)
{
    return (gsl_spline2d_eval(spline, xi_, yj_, xacc, yacc));
}

double Interpolation2D::getInterpolationDerivX(double xi_, double yj_)
{
    return (gsl_spline2d_eval_deriv_x(spline, xi_, yj_, xacc, yacc));
}

double Interpolation2D::getInterpolationDerivY(double xi_, double yj_)
{
    return (gsl_spline2d_eval_deriv_y(spline, xi_, yj_, xacc, yacc));
}