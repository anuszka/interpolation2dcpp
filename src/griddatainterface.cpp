#include <iostream>
#include "include/griddatainterface.h"
#include "include/readcsv.h"

GridDataInterface::GridDataInterface(const std::string &pPath) : path(pPath)
{
    setDoc(path);
    if (fileDataSortingCorrect())
    {
        setXgrid();
        setYgrid();
        setZvalues();
    }
}

void GridDataInterface::setDoc(const std::string &path_)
{
    // File with 3 columns (x, y, z) and arbitrary column labels
    doc = new Data(path_);
}

bool GridDataInterface::fileDataSortingCorrect()
{
    // This function checks only first two lines and columns for now.
    // This is to determine the sorting direction.

    double x0 = doc->X[0];
    double x1 = doc->X[1];
    double y0 = doc->Y[0];
    double y1 = doc->Y[1];
    if ((x0 == x1) && (y0 < y1))
    {
        file_data_sorting_direction = FileDataSorting::along_y_column_first;
    }
    else if ((x0 < x1) && (y0 == y1))
    {
        file_data_sorting_direction = FileDataSorting::along_x_column_first;
    }
    else
    {
        std::cerr << "Incorrect data sorting in the file!\n";
        return (file_data_sorting_correct = false);
    }
    return (file_data_sorting_correct = true);
}

void GridDataInterface::setXgrid()
{
    x_grid = collect_nonrepeating_values(doc->X);
    x_grid_size = x_grid.size();
}

void GridDataInterface::setYgrid()
{
    y_grid = collect_nonrepeating_values(doc->Y);
    y_grid_size = y_grid.size();
}

void GridDataInterface::setZvalues()
{
    double z;
    if (file_data_sorting_direction == FileDataSorting::along_x_column_first)
    {

        for (int i = 0; i < (int)x_grid_size; i++)
            for (int j = 0; j < (int)y_grid_size; j++)
            {
                z = doc->Z[j * x_grid_size + i];
                z_values.push_back(z);
            }
    }
    else
    {
        for (int i = 0; i < (int)x_grid_size; i++)
            for (int j = 0; j < (int)y_grid_size; j++)
            {
                z = doc->Z[i * y_grid_size + j];
                z_values.push_back(z);
            }
    }
}

std::vector<double> GridDataInterface::collect_nonrepeating_values(std::vector<double> v)
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

void GridDataInterface::printGridValues()
{
    if (file_data_sorting_correct)
    {
        std::cout << "X grid values:\n";
        for (const auto &value : getXgrid())
            std::cout << value << "\n";
        std::cout << "X grid size: " << getXgrid().size() << "\n";

        std::cout << "Y grid values:\n";
        for (const auto &value : getYgrid())
            std::cout << value << "\n";
        std::cout << "Y grid size: " << getYgrid().size() << "\n";
    }
}

void GridDataInterface::printZvalues()
{

    if (file_data_sorting_correct)
    {
        std::cout << "z values, sorted:\n";
        for (const auto &value : getZvalues())
            std::cout << value << "\n";
        std::cout << "z vector size: " << getZvalues().size() << "\n";
    }
}