#ifndef bipred_hpp
#define bipred_hpp

#include <iostream>
#include <sstream>

using std::cin;
using std::cout;
using std::cerr;

namespace bipred {

    int x, y;
    std::stringstream readBipartiteGraph();
    void writeBipMatchSolution(std::stringstream in);

}

#endif
