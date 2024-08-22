#include <iostream>
#include <vector>
#include <stack>
#include <unordered_set>
#include <unordered_map>
#include <set>
#include <cstdlib>
#include <ctime>

class Vertex {
public:
    int id;
    std::vector<std::pair<Vertex*, int>> adjVertices; // Pair of adjacent vertex and edge weight

    Vertex(int id) : id(id) {}

    void addEdge(Vertex* v, int weight) {
        adjVertices.push_back({v, weight});
    }
};

class Graph {
private:
    std::unordered_map<int, Vertex*> vertices;
    bool directed;

public:
    Graph(bool directed = false) : directed(directed) {}

    void addEdge(int from, int to, int weight) {
        if (vertices.find(from) == vertices.end())
            vertices[from] = new Vertex(from);
        if (vertices.find(to) == vertices.end())
            vertices[to] = new Vertex(to);
        vertices[from]->addEdge(vertices[to], weight);
    }

    std::vector<Vertex*> getAllVertices() {
        std::vector<Vertex*> result;
        for (auto& pair : vertices) {
            result.push_back(pair.second);
        }
        return result;
    }

    Vertex* getVertex(int id) {
        return vertices[id];
    }

    Graph reverseGraph() {
        Graph reversedGraph(true);
        for (auto& pair : vertices) {
            Vertex* v = pair.second;
            for (auto& adj : v->adjVertices) {
                reversedGraph.addEdge(adj.first->id, v->id, adj.second);
            }
        }
        return reversedGraph;
    }
};

class StronglyConnectedComponent {
public:
    std::vector<std::set<Vertex*>> scc(Graph& graph) {
        std::stack<Vertex*> finishStack;
        std::unordered_set<Vertex*> visited;

        for (Vertex* vertex : graph.getAllVertices()) {
            if (visited.find(vertex) == visited.end()) {
                DFSUtil(vertex, visited, finishStack);
            }
        }

        Graph reverseGraph = graph.reverseGraph();

        visited.clear();
        std::vector<std::set<Vertex*>> result;
        while (!finishStack.empty()) {
            Vertex* vertex = reverseGraph.getVertex(finishStack.top()->id);
            finishStack.pop();
            if (visited.find(vertex) == visited.end()) {
                std::set<Vertex*> component;
                DFSUtilForReverseGraph(vertex, visited, component);
                result.push_back(component);
            }
        }
        return result;
    }

private:
    void DFSUtil(Vertex* vertex, std::unordered_set<Vertex*>& visited, std::stack<Vertex*>& finishStack) {
        visited.insert(vertex);
        for (auto& adj : vertex->adjVertices) {
            if (visited.find(adj.first) == visited.end()) {
                DFSUtil(adj.first, visited, finishStack);
            }
        }
        finishStack.push(vertex);
    }

    void DFSUtilForReverseGraph(Vertex* vertex, std::unordered_set<Vertex*>& visited, std::set<Vertex*>& component) {
        visited.insert(vertex);
        component.insert(vertex);
        for (auto& adj : vertex->adjVertices) {
            if (visited.find(adj.first) == visited.end()) {
                DFSUtilForReverseGraph(adj.first, visited, component);
            }
        }
    }
};

int main() {
    std::srand(std::time(0));

    const int RUN = 5;
    const int MAX_VERTICES = 20;
    const int MAX_EDGES = 200;
    const int MAXWEIGHT = 200;

    for (int i = 1; i <= RUN; i++) {
        int NUM = 1 + std::rand() % MAX_VERTICES;
        int NUMEDGE = 1 + std::rand() % MAX_EDGES;

        while (NUMEDGE > NUM * (NUM - 1) / 2)
            NUMEDGE = 1 + std::rand() % MAX_EDGES;

        Graph graph(true);

        std::set<std::pair<int, int>> container;

        for (int j = 1; j <= NUMEDGE; j++) {
            int a = 1 + std::rand() % NUM;
            int b = 1 + std::rand() % NUM;
            std::pair<int, int> p = std::make_pair(a, b);

            while (container.find(p) != container.end() || a == b) {
                a = 1 + std::rand() % NUM;
                b = 1 + std::rand() % NUM;
                p = std::make_pair(a, b);
            }
            container.insert(p);
            int wt = 1 + std::rand() % MAXWEIGHT;
            graph.addEdge(a, b, wt);
        }

        StronglyConnectedComponent scc;
        std::vector<std::set<Vertex*>> result = scc.scc(graph);

        std::cout << "Graph " << i << ": " << NUM << " vertices, " << NUMEDGE << " edges" << std::endl;
        std::cout << "Strongly Connected Components:" << std::endl;

        for (const auto& component : result) {
            for (Vertex* v : component) {
                std::cout << v->id << " ";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }

    return 0;
}
