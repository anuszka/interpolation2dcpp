#include <gsl/gsl_math.h>
#include <gsl/gsl_interp2d.h>
#include <gsl/gsl_spline2d.h>

#ifndef INTERPOLATION2D
#define INTERPOLATION2D

class Interpolation2D
{
private:
    const gsl_interp2d_type *my_gsl_interp2d_type;
    gsl_spline2d *spline;
    gsl_interp_accel *xacc;
    gsl_interp_accel *yacc;

    double *data_grid_x;
    double *data_grid_y;

    size_t data_grid_x_size;
    size_t data_grid_y_size;

    double *data_grid_z;

public:
    Interpolation2D();
    ~Interpolation2D();
    void setData();
    void initSpline();
    double getInterpolation(double, double);
};

#endif