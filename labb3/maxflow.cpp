#include <iostream>
#include <sstream>
#include <vector>
#include <queue>

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
        cin >> x >> y >> z;
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

int main() {
    // haxxzor out in
    ios::sync_with_stdio(false);
    cin.tie(0);

    // Read vertices, start- , end-vertice and tot edges.
    cin >> v >> first >> last >> e;

    createGraph();
    int maxFlow = findMaxFlow();

    //Output data
    stringstream out;
    stringstream temp;
    int edges = 0;
    out << v << endl;
    out << first << " " << last << " " << maxFlow << endl;
    for(size_t i = 1; i < vertices.size(); ++i) {
        for(Edge * e : vertices[i]) {
            if(e->flow > 0) {
                edges++;
                temp << e->origin << " " << e->sink << " " << e->flow << endl;
            }
            delete e;
        }
    }
    out << edges << endl;
    out << temp.str();
    cout << out.str();
    return 0;
}


// 9
// 1 9
// 11
// 1 2 1
// 1 5 7
// 2 3 1
// 3 4 1
// 3 8 2
// 3 7 1
// 3 6 4
// 4 5 1
// 6 9 1
// 7 9 2
// 8 7 1
