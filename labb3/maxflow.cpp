#include <iostream>
#include <sstream>
#include <vector>
#include <list>
#include <queue>

using namespace std;

int v, first, last, e;

int x, y, z;

struct Edge {
	int sink;
	int capacity;
	int rCapacity;
	int flow;
	bool visited;
	Edge() : 
		sink(0), 
		capacity(0), 
		rCapacity(0), 
		flow(0),
		visited(false){}
	Edge(int x1, int x2) : 
		sink(x1), 
		capacity(x2), 
		rCapacity(x2), 
		flow(0),
		visited(false){}
};


vector< vector<Edge> > createGraph() {
	cin >> v >> first >> last >> e;
	// vector< list<Edge> > vertices(v + 1);
	vector< vector<Edge> > vertices(v,vector<Edge>());

	for (int i = 0; i < e; ++i) {
		cin >> x >> y >> z;
		Edge e1(x,z);
		Edge e2(y,z);
		vertices[x-1].push_back(e2);
		vertices[y-1].push_back(e1);
	}
	return vertices;
}

Edge bfs(vector< vector< Edge > > vertices) {
	queue<Edge> queue;
	Edge curry;
	for (int i = 0; i < vertices[0].size(); ++i) {
		queue.push(vertices[0][i]);
	}
	while (!queue.empty()) {
		curry = queue.front();
		cout << curry.sink << endl;
		curry.visited = true;
		// for (int i = 0; i < vertices[curry.sink].size(); ++i) {
		// 	if(!(vertices[curry.sink][i].visited)) {
		// 		queue.push(vertices[curry.sink][i]);
		// 	}
		// }
		queue.pop();
	}

	return curry;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	bfs(createGraph());
	return 0;
}
