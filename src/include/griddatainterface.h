#include "rapidcsv.h"
#include <vector>

#ifndef GRIDDATAINTERFACE
#define GRIDDATAINTERFACE

class GridDataInterface
{
private:
    rapidcsv::Document *doc;
    const std::string path;
    const std::string column_name_x;
    const std::string column_name_y;
    std::vector<double> x_grid;
    std::vector<double> y_grid;
    std::vector<double> collect_values(std::vector<double> v);

public:
    GridDataInterface(
        const std::string &pPath,
        const std::string &pColumnNameX,
        const std::string &pColumnNameY
        );
    ~GridDataInterface() {}
    std::vector<double> getXgrid() { return (x_grid); }
    std::vector<double> getYgrid() { return (y_grid); }
    void printColumnValues(const std::string &pColumnName, std::vector<double> column);
};

#endif
