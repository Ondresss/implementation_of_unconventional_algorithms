//
// Created by andrew on 4/8/26.
//
#include <cstdlib>
#include "IFS.h"
int main(void) {

    IFS ifs(IFS::Point{std::vector<double>({0.0f,0.0f,0.0f})});
    ifs.run(20000);
    ifs.visualize();
    std::exit(EXIT_SUCCESS);
}