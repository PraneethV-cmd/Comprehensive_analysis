#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <stack>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <set>

class Vertex {
public:
    int data;
    std::vector<Vertex*> adj;

    Vertex(int data) : data(data) {}

    void addEdge(Vertex* vertex) {
        adj.push_back(vertex);
    }
};

class Graph {
public:
    std::unordered_map<int, Vertex*> vertices;
    bool isDirected;

    Graph(bool isDirected) : isDirected(isDirected) {}

    void addEdge(int src, int dest) {
        if (vertices.find(src) == vertices.end()) {
            vertices[src] = new Vertex(src);
        }
        if (vertices.find(dest) == vertices.end()) {
            vertices[dest] = new Vertex(dest);
        }
        vertices[src]->addEdge(vertices[dest]);
        if (!isDirected) {
            vertices[dest]->addEdge(vertices[src]);
        }
    }

    std::vector<Vertex*> getAllVertex() {
        std::vector<Vertex*> allVertices;
        for (auto& kv : vertices) {
            allVertices.push_back(kv.second);
        }
        return allVertices;
    }
};

class TarjanSCC {
private:
    std::unordered_map<Vertex*, int> visitedTime;
    std::unordered_map<Vertex*, int> lowTime;
    std::unordered_set<Vertex*> onStack;
    std::stack<Vertex*> stack;
    std::unordered_set<Vertex*> visited;
    std::vector<std::unordered_set<Vertex*>> result;
    int time;

    void sccUtil(Vertex* vertex) {
        visited.insert(vertex);
        visitedTime[vertex] = lowTime[vertex] = time++;
        stack.push(vertex);
        onStack.insert(vertex);

        for (Vertex* child : vertex->adj) {
            if (visited.find(child) == visited.end()) {
                sccUtil(child);
                lowTime[vertex] = std::min(lowTime[vertex], lowTime[child]);
            } else if (onStack.find(child) != onStack.end()) {
                lowTime[vertex] = std::min(lowTime[vertex], visitedTime[child]);
            }
        }

        if (visitedTime[vertex] == lowTime[vertex]) {
            std::unordered_set<Vertex*> scc;
            Vertex* v;
            do {
                v = stack.top();
                stack.pop();
                onStack.erase(v);
                scc.insert(v);
            } while (v != vertex);
            result.push_back(scc);
        }
    }

public:
    std::vector<std::unordered_set<Vertex*>> scc(Graph& graph) {
        time = 0;
        visitedTime.clear();
        lowTime.clear();
        onStack.clear();
        while (!stack.empty()) stack.pop();
        visited.clear();
        result.clear();

        for (Vertex* vertex : graph.getAllVertex()) {
            if (visited.find(vertex) == visited.end()) {
                sccUtil(vertex);
            }
        }

        return result;
    }
};

#define RUN 5
#define MAX_VERTICES 20
#define MAX_EDGES 200

int main() {
    srand(time(0));

    for (int i = 1; i <= RUN; i++) {
        int NUM = 1 + rand() % MAX_VERTICES;
        int NUMEDGE = 1 + rand() % MAX_EDGES;

        while (NUMEDGE > NUM * (NUM - 1)) {
            NUMEDGE = 1 + rand() % MAX_EDGES;
        }

        std::cout << "Test Case " << i << ":\n";
        std::cout << "Number of vertices: " << NUM << ", Number of edges: " << NUMEDGE << "\n";

        Graph graph(true);
        std::set<std::pair<int, int>> container;

        for (int j = 1; j <= NUMEDGE; j++) {
            int a = 1 + rand() % NUM;
            int b = 1 + rand() % NUM;
            std::pair<int, int> p = std::make_pair(a, b);

            while (container.find(p) != container.end()) {
                a = 1 + rand() % NUM;
                b = 1 + rand() % NUM;
                p = std::make_pair(a, b);
            }
            container.insert(p);
            graph.addEdge(a, b);
        }

        for (const auto& edge : container) {
            std::cout << edge.first << " -> " << edge.second << "\n";
        }

        TarjanSCC tarjanSCC;
        auto result = tarjanSCC.scc(graph);

        std::cout << "\nStrongly Connected Components:\n";
        for (const auto& scc : result) {
            for (const auto& vertex : scc) {
                std::cout << vertex->data << " ";
            }
            std::cout << "\n";
        }
        std::cout << "\n\n";
    }

    return 0;
}
