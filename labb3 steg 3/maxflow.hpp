#ifndef maxflow_hpp
#define maxflow_hpp

#include <iostream>
#include <sstream>
#include <vector>
#include <queue>

namespace maxflow {

    using namespace std;


    struct Edge {
        int origin;
        int sink;
        int capacity;
        int flow;
        Edge * rev;
        Edge(int x, int x1, int x2) :
            origin(x),
            sink(x1),
            capacity(x2),
            flow(0)
        {}
    };

    vector< vector<Edge*> > vertices;
    int v, first, last, e;
    int x, y, z;

    void createGraph(stringstream in);
    vector<Edge*> genPath();
    int findMaxFlow();
    stringstream maxFlow(stringstream in);
}

#endif
