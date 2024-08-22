#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <ctime>
#include <cstdlib>

using namespace std;

class Vertex {
public:
    int id;
    vector<Vertex*> adjacentVertices;

    Vertex(int id) : id(id) {}

    void addAdjacentVertex(Vertex* vertex) {
        adjacentVertices.push_back(vertex);
    }

    vector<Vertex*>& getAdjacentVertices() {
        return adjacentVertices;
    }
};

class Edge {
public:
    Vertex* src;
    Vertex* dest;

    Edge(Vertex* src, Vertex* dest) : src(src), dest(dest) {}

    bool operator<(const Edge& e) const {
        if (src->id != e.src->id) {
            return src->id < e.src->id;
        }
        return dest->id < e.dest->id;
    }
};

class Graph {
public:
    map<int, Vertex*> vertices;
    bool isDirected;

    Graph(bool isDirected) : isDirected(isDirected) {}

    void addEdge(int src, int dest) {
        if (vertices.find(src) == vertices.end()) {
            vertices[src] = new Vertex(src);
        }
        if (vertices.find(dest) == vertices.end()) {
            vertices[dest] = new Vertex(dest);
        }
        vertices[src]->addAdjacentVertex(vertices[dest]);
        if (!isDirected) {
            vertices[dest]->addAdjacentVertex(vertices[src]);
        }
    }

    vector<Vertex*> getAllVertices() {
        vector<Vertex*> vertexList;
        for (auto& pair : vertices) {
            vertexList.push_back(pair.second);
        }
        return vertexList;
    }
};

class Bridge {
    int time;

    void BridgeUtil(Vertex* vertex, set<Edge>& result, map<Vertex*, int>& discovery, 
                    map<Vertex*, int>& low, map<Vertex*, Vertex*>& parent, map<Vertex*, bool>& visited) {
        visited[vertex] = true;
        discovery[vertex] = low[vertex] = ++time;

        for (Vertex* child : vertex->getAdjacentVertices()) {
            if (!visited[child]) {
                parent[child] = vertex;
                BridgeUtil(child, result, discovery, low, parent, visited);

                low[vertex] = min(low[vertex], low[child]);

                if (low[child] > discovery[vertex]) {
                    result.insert(Edge(vertex, child));
                }
            } else if (child != parent[vertex]) {
                low[vertex] = min(low[vertex], discovery[child]);
            }
        }
    }

public:
    set<Edge> getBridge(Graph& graph) {
        set<Edge> result;
        map<Vertex*, int> discovery;
        map<Vertex*, int> low;
        map<Vertex*, Vertex*> parent;
        map<Vertex*, bool> visited;

        time = 0;

        for (Vertex* vertex : graph.getAllVertices()) {
            if (!visited[vertex]) {
                BridgeUtil(vertex, result, discovery, low, parent, visited);
            }
        }

        return result;
    }
};

int main() {
    srand(time(NULL));

    const int RUN = 5;
    const int MAX_VERTICES = 20;
    const int MAX_EDGES = 200;

    for (int i = 1; i <= RUN; i++) {
        int NUM = 1 + rand() % MAX_VERTICES;
        int NUMEDGE = 1 + rand() % MAX_EDGES;

        while (NUMEDGE > NUM * (NUM - 1) / 2)
            NUMEDGE = 1 + rand() % MAX_EDGES;

        printf("Run %d: %d vertices, %d edges\n", i, NUM, NUMEDGE);

        Graph graph(false);
        set<pair<int, int>> container;

        for (int j = 1; j <= NUMEDGE; j++) {
            int a = rand() % NUM;
            int b = rand() % NUM;
            pair<int, int> p = make_pair(a, b);
            pair<int, int> reverse_p = make_pair(b, a);

            while (a == b || container.find(p) != container.end() || container.find(reverse_p) != container.end()) {
                a = rand() % NUM;
                b = rand() % NUM;
                p = make_pair(a, b);
                reverse_p = make_pair(b, a);
            }
            container.insert(p);
            graph.addEdge(a, b);
        }

        Bridge bridgeFinder;
        set<Edge> result = bridgeFinder.getBridge(graph);

        for (const Edge& edge : result) {
            cout << "Bridge between " << edge.src->id << " and " << edge.dest->id << endl;
        }

        cout << endl;
    }

    return 0;
}
