#include "include/griddatainterface.h"
#include <iostream>

GridDataInterface::GridDataInterface(
    const std::string &pPath,
    const std::string &pColumnNameX,
    const std::string &pColumnNameY) : path(pPath),
                                       column_name_x(pColumnNameX),
                                       column_name_y(pColumnNameY)
{
    doc = new rapidcsv::Document(path, rapidcsv::LabelParams(0, -1));
    x_grid = collect_values(doc->GetColumn<double>(column_name_x));
    y_grid = collect_values(doc->GetColumn<double>(column_name_y));
}

std::vector<double> GridDataInterface::collect_values(std::vector<double> v)
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

void GridDataInterface::printColumnValues(const std::string &pColumnName, std::vector<double> column)
{
    std::cout << pColumnName << " column values:\n";
    for (const auto &value : column)
        std::cout << value << "\n";
}