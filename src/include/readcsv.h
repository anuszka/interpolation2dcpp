#include<string>
#include<vector>

#ifndef READCSV
#define READCSV

class Data
{
private:
    void readHeaderFromFile(std::string line_);
    void readColumnsFromFile(std::string line_);
    void handleFileErrors();

public:
    std::vector<double> X, Y, Z;
    std::vector<std::string> column_headers;
    Data(){};
    Data(const std::string &file_name_);
    ~Data(){};
    void printColumnHeaders();
    void printXYZcolumns();
};

#endif