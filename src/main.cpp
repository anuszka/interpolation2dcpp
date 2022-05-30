#include "include/interpolation2d_example.h"
#include "include/parse_args.h"

int main(int argc, char **argv)
{
    int example;
    parse_args("example", example, argc, argv);

    switch (example)
    {
    case 1:
        interpolation2d_example();
        break;
    case 2:
        interpolation2d_class_file_example();
        break;

    default:
        break;
    }
}
