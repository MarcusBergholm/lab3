#include <iostream>
#include <sstream>
#include <vector>
#include <queue>

std::stringstream outbip;
std::stringstream outmatch;

namespace bipred {

    using std::cin;
    using std::cout;
    using std::cerr;

    int x, y;

    void readBipartiteGraph() {
        int e;
        cin >> x >> y; // read num of vertices
        cin >> e; // read num of edges.

        int start = 1;
        int end = x + y + 2; // calc end point and total num of vertices
        int totNumEdges = e + x + y; // calc total number of edges

        outbip << end << std::endl;
        outbip << start << " " << end << std::endl;
        outbip << totNumEdges << std::endl;

        // create the starting point edges
        for(int i = 0; i < x; ++i) {
            outbip << start << " " << 2+i << " " << 1 << std::endl;
        }

        // read and create the egdes of the bipartite graph
        int a, b;
        for (int i = 0; i < e; ++i) {
            cin >> a >> b;
            outbip << a+1 << " " << b+1 << " " << 1 << std::endl;
        }

        // create the starting point edges
        for(int i = 0; i < y; ++i) {
            outbip << x+2+i << " " << end << " " << 1 << std::endl;
        }
    }

    void writeBipMatchSolution() {
        std::stringstream out;
        std::stringstream e;
        int v, start, end, flow, edges, outEdges;

        outmatch >> v >> start >> end >> flow >> edges;
        outEdges = edges;

        out << x << " " << y << std::endl;

        int a, b;
        for(int i = 0; i < edges; ++i) {
            outmatch >> a >> b >> flow;
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

    void createGraph() {
        vector< vector<Edge*> > hotshot(v+1,vector<Edge*>());

        for(int i = 0; i < e; ++i) {
            outbip >> x >> y >> z;
            Edge *e1 = new Edge(x,y,z);
            Edge *e2 = new Edge(y,x,0);
            e1->rev = e2;
            e2->rev = e1;
            hotshot[x].push_back(e1);
            hotshot[y].push_back(e2);
        }
        vertices = hotshot;
    }

    vector<Edge*> genPath() {
        //cout << "FIND PATH" << endl;
        queue<int> queue;
        int current = first;
        queue.push(first);
        vector<Edge*> path(v+1, nullptr);

        while (!queue.empty()) {
            current = queue.front();
            queue.pop();

            for(size_t i = 0; i < vertices[current].size(); ++i) {
                Edge * e = vertices[current][i];
                if(path[e->sink] == nullptr) {
                    if(e->capacity > e->flow && e->sink != first) {
                        path[e->sink] = vertices[current][i];
                        //cout << e->origin << " ";
                        //cout << e->sink << endl;
                        queue.push(e->sink);
                    }
                }
            }
        }

        //cout << "DONE PATH" << endl;
        return path;
    }

    int findMaxFlow() {
        int tf = 0;
        while(true) {
            auto path = genPath();
            if(path[last] == nullptr) {
                break;
            }

            int pos = last;
            int rCap = (path[last]->capacity) - (path[last]->flow);
            vector<Edge*> origins;
            origins.push_back(path[last]);

            //cout << "FIND RCAP" << endl;
            while(true) {
                //cout << pos << endl;
                pos = path[pos]->origin;
                if(pos == first) {
                    break;
                }
                origins.push_back(path[pos]);
                if(rCap > (path[pos]->capacity) - (path[pos]->flow)) {
                    rCap = (path[pos]->capacity) - (path[pos]->flow);
                }
            }
            //cout << "DONE RCAP" << endl;

            for(Edge * e : origins) {
                e->flow = (e->flow) + rCap;
                e->rev->flow = (e->rev->flow) - rCap;
            }
            tf += rCap;
        }

        int maxFlow = 0;
        for(Edge * e : vertices[first]) {
            maxFlow += e->flow;
        }

        //cout << endl << "MAX FLOW" << endl << maxFlow << endl;
        //cout << endl << "TEST MAX FLOW" << endl << tf << endl;
        return tf;
    }

   void maxFlow() {
        // Read vertices, start- , end-vertice and tot edges.
        outbip >> v >> first >> last >> e;

        createGraph();
        int maxFlow = findMaxFlow();

        //Output data
        stringstream temp;
        int edges = 0;
        outmatch << v << endl;
        outmatch << first << " " << last << " " << maxFlow << endl;
        for(size_t i = 1; i < vertices.size(); ++i) {
            for(Edge * e : vertices[i]) {
                if(e->flow > 0) {
                    edges++;
                    temp << e->origin << " " << e->sink << " " << e->flow << endl;
                }
                delete e;
            }
        }
        outmatch << edges << endl;
        outmatch << temp.str();
    }

}

int main() {
    // make cin and cout faster...
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);

    bipred::readBipartiteGraph();
    maxflow::maxFlow();
    bipred::writeBipMatchSolution();

    return 0;
}
