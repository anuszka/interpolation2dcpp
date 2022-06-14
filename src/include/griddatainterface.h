#include <vector>
#include "readcsv.h"

#ifndef GRIDDATAINTERFACE
#define GRIDDATAINTERFACE

class GridDataInterface
{
private:
    Data *doc;
    const std::string path;
    std::vector<double> x_grid;
    std::vector<double> y_grid;
    std::vector<double> z_values;
    std::vector<double> collect_nonrepeating_values(std::vector<double> v);
    size_t x_grid_size;
    size_t y_grid_size;
    void setXgrid();
    void setYgrid();
    void setZvalues();
    void setDoc(const std::string &path_);
    enum class FileDataSorting
    {
        along_x_column_first,
        along_y_column_first
    };
    FileDataSorting file_data_sorting_direction;
    bool file_data_sorting_correct;
    bool fileDataSortingCorrect();

public:
    GridDataInterface(const std::string &pPath);
    ~GridDataInterface() {}
    std::vector<double> getXgrid() { return (x_grid); }
    std::vector<double> getYgrid() { return (y_grid); }
    std::vector<double> getZvalues() { return (z_values); }
    size_t getXgridSize() { return (x_grid_size); }
    size_t getYgridSize() { return (y_grid_size); }
    double *getXgridAsArrayPtr() { return (x_grid.data()); }
    double *getYgridAsArrayPtr() { return (y_grid.data()); }
    double *getZvaluesAsArrayPtr() { return (z_values.data()); }
    void printGridValues();
    void printZvalues();
};

#endif
