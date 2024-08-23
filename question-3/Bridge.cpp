#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <ctime>
#include <cstdlib>

class Vertex {
public:
    int id;
    std::vector<Vertex*> adjacentVertices;

    Vertex(int id) : id(id) {}

    void addAdjacentVertex(Vertex* vertex) {
        adjacentVertices.push_back(vertex);
    }

    std::vector<Vertex*>& getAdjacentVertices() {
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
    std::map<int, Vertex*> vertices;
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

    std::vector<Vertex*> getAllVertices() {
        std::vector<Vertex*> vertexList;
        for (auto& pair : vertices) {
            vertexList.push_back(pair.second);
        }
        return vertexList;
    }
};

class Bridge {
    int time;

    void BridgeUtil(Vertex* vertex, std::set<Edge>& result, std::map<Vertex*, int>& discovery, 
                    std::map<Vertex*, int>& low, std::map<Vertex*, Vertex*>& parent, std::map<Vertex*, bool>& visited) {
        visited[vertex] = true;
        discovery[vertex] = low[vertex] = ++time;

        for (Vertex* child : vertex->getAdjacentVertices()) {
            if (!visited[child]) {
                parent[child] = vertex;
                BridgeUtil(child, result, discovery, low, parent, visited);

                low[vertex] = std::min(low[vertex], low[child]);

                if (low[child] > discovery[vertex]) {
                    result.insert(Edge(vertex, child));
                }
            } else if (child != parent[vertex]) {
                low[vertex] = std::min(low[vertex], discovery[child]);
            }
        }
    }

public:
    std::set<Edge> getBridge(Graph& graph) {
        std::set<Edge> result;
        std::map<Vertex*, int> discovery;
        std::map<Vertex*, int> low;
        std::map<Vertex*, Vertex*> parent;
        std::map<Vertex*, bool> visited;

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
    std::srand(std::time(NULL));

    const int RUN = 5;
    const int MAX_VERTICES = 20;
    const int MAX_EDGES = 200;

    for (int i = 1; i <= RUN; i++) {
        int NUM = 1 + std::rand() % MAX_VERTICES;
        int NUMEDGE = 1 + std::rand() % MAX_EDGES;

        while (NUMEDGE > NUM * (NUM - 1) / 2)
            NUMEDGE = 1 + std::rand() % MAX_EDGES;

        std::printf("Run %d: %d vertices, %d edges\n", i, NUM, NUMEDGE);

        Graph graph(false);
        std::set<std::pair<int, int>> container;

        for (int j = 1; j <= NUMEDGE; j++) {
            int a = std::rand() % NUM;
            int b = std::rand() % NUM;
            std::pair<int, int> p = std::make_pair(a, b);
            std::pair<int, int> reverse_p = std::make_pair(b, a);

            while (a == b || container.find(p) != container.end() || container.find(reverse_p) != container.end()) {
                a = std::rand() % NUM;
                b = std::rand() % NUM;
                p = std::make_pair(a, b);
                reverse_p = std::make_pair(b, a);
            }
            container.insert(p);
            graph.addEdge(a, b);
        }

        Bridge bridgeFinder;
        std::set<Edge> result = bridgeFinder.getBridge(graph);

        for (const Edge& edge : result) {
            std::cout << "Bridge between " << edge.src->id << " and " << edge.dest->id << std::endl;
        }

        std::cout << std::endl;
    }

    return 0;
}
