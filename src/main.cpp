#include "include/interpolation2d_example.h"
#include "include/parse_args.h"

int main(int argc, char **argv)
{
    int example;
    int N;
    parse_args("example", example, argc, argv);
    parse_args("N", N, argc, argv);

    switch (example)
    {
    case 1:
        interpolation2d_class_file_example();
        break;
    case 2:
        interpolation2d_example((size_t) N);
        break;

    default:
        break;
    }
}
