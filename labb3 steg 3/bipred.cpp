#include <iostream>
#include <sstream>


namespace bipred {

    using std::cin;
    using std::cout;
    using std::cerr;

    int x, y;

    std::stringstream readBipartiteGraph() {
        std::stringstream out;
        int e;
        cin >> x >> y; // read num of vertices
        cin >> e; // read num of edges.

        int start = 1;
        int end = x + y + 2; // calc end point and total num of vertices
        int totNumEdges = e + x + y; // calc total number of edges

        out << end << std::endl;
        out << start << " " << end << std::endl;
        out << totNumEdges << std::endl;

        // create the starting point edges
        for(int i = 0; i < x; ++i) {
            out << start << " " << 2+i << " " << 1 << std::endl;
        }

        // read and create the egdes of the bipartite graph
        int a, b;
        for (int i = 0; i < e; ++i) {
            cin >> a >> b;
            out << a+1 << " " << b+1 << " " << 1 << std::endl;
        }

        // create the starting point edges
        for(int i = 0; i < y; ++i) {
            out << x+2+i << " " << end << " " << 1 << std::endl;
        }

        return out;
    }

    void writeBipMatchSolution(std::stringstream in) {
        std::stringstream out;
        std::stringstream e;
        int v, start, end, flow, edges, outEdges;

        in >> v >> start >> end >> flow >> edges;
        outEdges = edges;

        out << x << " " << y << std::endl;

        int a, b;
        for(int i = 0; i < edges; ++i) {
            in >> a >> b >> flow;
            if(a == start || b == end) {
                outEdges--;
            } else {
                e << a-1 << " " << b-1 << std::endl;
            }
        }

        out << outEdges << std::endl;
        out << e.str();
        cout << out.str();
        cout.flush();
    }
}
