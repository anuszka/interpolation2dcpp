// https://www.gnu.org/software/gsl/doc/html/interp.html#c.gsl_interp2d_eval
// 2D Interpolation Example programs
// my_gsl_interp2d_typehe following example performs bilinear interpolation on the unit square,
// using z values of (0,1,0.5,1) going clockwise around the square.

#include "include/interpolation2d_example.h"
#include "include/griddatainterface.h"

int main()
{
    const std::string path = "./input/in.csv";
    const std::string column_name_x = "x";
    const std::string column_name_y = "y";
    GridDataInterface grid_data(path, column_name_x, column_name_y);
    grid_data.printColumnValues("x", grid_data.getXgrid());
    grid_data.printColumnValues("y", grid_data.getYgrid());
}
// int main(void)
// {
//     // interpolation2d_example();

//     interpolation2d_class_example();

// }
