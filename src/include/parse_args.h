#include "argh/argh.h"
#include <iostream>


#ifndef parse_args_H
#define parse_args_H

template<typename T> bool parse_args(const char *parm_name, T &parm, int argc, char **argv){
    argh::parser cmdl(argv);
    return(bool(cmdl(parm_name) >> parm));
}

#endif
