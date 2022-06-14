#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
// #include <system_error>
#include "include/readcsv.h"

void Data::readHeaderFromFile(std::string line_)
{
    std::string str;
    std::stringstream lineStream(line_);
    for (int i = 0; i < 3; ++i)
    {
        std::getline(lineStream, str, ',');
        column_headers.push_back(str);
    }
}

void Data::printColumnHeaders()
{
    for (const auto &value : column_headers)
        std::cout << value << " ";
    std::cout << "\n";
}

void Data::readColumnsFromFile(std::string line_)
{
    std::string str;
    std::stringstream lineStream(line_);
    std::getline(lineStream, str, ',');
    X.push_back(std::stod(str));
    std::getline(lineStream, str, ',');
    Y.push_back(std::stod(str));
    std::getline(lineStream, str, '\n');
    Z.push_back(std::stod(str));
}

void Data::printXYZcolumns()
{
    for (int i = 0; i < (int)X.size(); ++i)
    {
        std::cout << X[i] << " " << Y[i] << " " << Z[i] << "\n";
    }
}

void Data::handleFileErrors()
{
    std::error_code e(errno, std::system_category());
    std::cerr << e.message() << "\n";
}

Data::Data(const std::string &file_name_)
{
    std::string line;
    std::ifstream file(file_name_.c_str());
    
    static bool first_line = true;
    if (!file.good())
        handleFileErrors();
    else
        while (std::getline(file, line))
        {
            if (first_line)
            {
                readHeaderFromFile(line);
                first_line = false;
            }
            else
                readColumnsFromFile(line);
        }
}