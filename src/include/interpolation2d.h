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

    void allocSpline(size_t data_grid_x_size_, size_t data_grid_y_size_);
    void allocAccel();
    void allocSplineAccel(size_t data_grid_x_size_, size_t data_grid_y_size_);
    void initSpline(double *data_grid_z_);

public:
    Interpolation2D();
    ~Interpolation2D();
    void setData();
    void setGrid();

    double getInterpolation(double xi_, double yj_);
};

#endif