// https://www.gnu.org/software/gsl/doc/html/interp.html#c.gsl_interp2d_eval
// 2D Interpolation Example programs
// my_gsl_interp2d_typehe following example performs bilinear interpolation on the unit square,
// using z values of (0,1,0.5,1) going clockwise around the square.

#include "include/interpolation2d_example.h"
#include "include/parse_args.h"

int main(int argc, char **argv)
// {
//     const std::string path = "./input/in.csv";
//     const std::string column_name_x = "x";
//     const std::string column_name_y = "y";
//     const std::string column_name_z = "z";
//     GridDataInterface grid_data(path, column_name_x, column_name_y, column_name_z);
//     grid_data.printGridValues(column_name_x);
//     grid_data.printGridValues(column_name_y);
// }
{
    int example;
    parse_args("example", example, argc, argv);

    switch (example)
    {
    case 1:
        interpolation2d_example();
        break;
    case 2:
        interpolation2d_class_example();
        break;
    case 3:
        interpolation2d_class_file_example();
        break;

    default:
        break;
    }

    // if (example == 1)
    //     interpolation2d_example();
    // else if (example == 2)
    //     interpolation2d_class_example();
    // else
    //     interpolation2d_class_file_example();
}
