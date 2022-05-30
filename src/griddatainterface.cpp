#include "include/griddatainterface.h"
#include <iostream>

GridDataInterface::GridDataInterface(
    const std::string &pPath,
    const std::string &pColumnNameX,
    const std::string &pColumnNameY,
    const std::string &pColumnNameZ) : path(pPath),
                                       column_name_x(pColumnNameX),
                                       column_name_y(pColumnNameY),
                                       column_name_z(pColumnNameZ)
{
    setDoc(path);
    if (fileDataSortingCorrect())
    {
        setXgrid(column_name_x);
        setYgrid(column_name_y);
        setZvalues(column_name_z);
    }
}

void GridDataInterface::setDoc(const std::string path_)
{
    // File with 3 columns (x, y, z) and arbitrary column labels
    doc = new rapidcsv::Document(path_, rapidcsv::LabelParams(0, -1));
}

bool GridDataInterface::fileDataSortingCorrect()
{
    // This function checks only first two lines and columns for now.
    // This is to determine the sorting direction.

    double x0 = doc->GetCell<double>(column_name_x, 0);
    double x1 = doc->GetCell<double>(column_name_x, 1);
    double y0 = doc->GetCell<double>(column_name_y, 0);
    double y1 = doc->GetCell<double>(column_name_y, 1);
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

void GridDataInterface::setXgrid(const std::string column_name_x_)
{
    x_grid = collect_nonrepeating_values(doc->GetColumn<double>(column_name_x_));
    x_grid_size = x_grid.size();
}

void GridDataInterface::setYgrid(const std::string column_name_y_)
{
    y_grid = collect_nonrepeating_values(doc->GetColumn<double>(column_name_y_));
    y_grid_size = y_grid.size();
}

void GridDataInterface::setZvalues(const std::string column_name_z_)
{
    double z;
    if (file_data_sorting_direction == FileDataSorting::along_x_column_first)
    {

        for (int i = 0; i < (int) x_grid_size; i++)
            for (int j = 0; j < (int) y_grid_size; j++)
            {
                z = doc->GetCell<double>(column_name_z_, j * x_grid_size + i);
                z_values.push_back(z);
            }
    }
    else
    {
        for (int i = 0; i < (int) x_grid_size; i++)
            for (int j = 0; j < (int) y_grid_size; j++)
            {
                z = doc->GetCell<double>(column_name_z_, i * y_grid_size + j);
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

void GridDataInterface::printGridValues(const std::string column_name_)
{

    if (file_data_sorting_correct)
    {
        std::vector<double> grid;
        grid = (column_name_ == column_name_x) ? getXgrid() : getYgrid();
        std::cout << column_name_ << " grid values:\n";
        for (const auto &value : grid)
            std::cout << value << "\n";
        std::cout << column_name_ << " grid size: " << grid.size() << "\n";
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