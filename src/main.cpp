// https://www.gnu.org/software/gsl/doc/html/interp.html#c.gsl_interp2d_eval
// 2D Interpolation Example programs
// my_gsl_interp2d_typehe following example performs bilinear interpolation on the unit square,
// using z values of (0,1,0.5,1) going clockwise around the square.

#include "include/interpolation2d_example.h"

// int main(void)
// {
//     // interpolation2d_example();

//     interpolation2d_class_example();

// }

#include <iostream>
#include <vector>

#include "include/rapidcsv.h"

std::vector<double> collect_values(std::vector<double> v)
{
    std::vector<double> output;
    double prev_val = v[0];
    output.push_back(prev_val);
    for (const auto &value : v)
    {
        if (value > prev_val)
        {
            output.push_back(value);
            prev_val = value;
        }
    }
    return (output);
}

int main()
{
    rapidcsv::Document doc("./input/in.csv", rapidcsv::LabelParams(0, -1));

    // double value = doc.GetCell<double>(2, 3);
    // std::cout << "Value " << value << " " << std::endl;

    // std::vector<double> x = doc.GetColumn<double>("x");
    // for (const auto &value : x)
    // {
    //     std::cout << value << "\n";
    // }
    // std::vector<double> column0 = doc.GetColumn<double>(0);
    // std::vector<double> row0 = doc.GetRow<double>(0);
    // std::cout << "Column size: " << column0.size() <<  std::endl;
    // std::cout << "Row size: " << row0.size() <<  std::endl;

    // std::vector<double> x = doc.GetColumn<double>("x");
    // double prev_val = x[0];
    // std::cout << "x column values \n";
    // std::cout << prev_val << "\n";
    // for (const auto &value : x)
    // {
    //     if (value > prev_val)
    //     {
    //         std::cout << value << "\n";
    //         prev_val = value;
    //     }
    // }

    // std::vector<double> y = doc.GetColumn<double>("y");
    // prev_val = y[0];
    // std::cout << "y column values \n";
    // std::cout << prev_val << "\n";
    // for (const auto &value : y)
    // {
    //     if (value > prev_val)
    //     {
    //         std::cout << value << "\n";
    //         prev_val = value;
    //     }
    // }

    std::vector<double> x = doc.GetColumn<double>("x");
    std::vector<double> x_grid = collect_values(x);
    std::cout << "x column values \n";
    for (const auto &value : x_grid)
        std::cout << value << "\n";

    std::vector<double> y = doc.GetColumn<double>("y");
    std::vector<double> y_grid = collect_values(y);
    std::cout << "y column values \n";
    for (const auto &value : y_grid)
        std::cout << value << "\n";
}