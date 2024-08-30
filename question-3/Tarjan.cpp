#include <iostream>
#include <list>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <stack>
#include <vector>
#include <climits>
#include <algorithm>
#include <fstream>

// Class to represent a graph
class Graph {
public:
    std::map<int, std::list<int>> adjacencyList; // Adjacency list representation of the graph
    bool isDirected;

    Graph(bool isDirected) : isDirected(isDirected) {}

    // Function to add an edge to the graph
    void add_edge(int u, int v) {
        adjacencyList[u].push_back(v);
        if (!isDirected) {
            adjacencyList[v].push_back(u);
        }
    }

    // Function to print the graph
    void print() const {
        for (const auto& i : adjacencyList) {
            std::cout << i.first << " -> ";
            for (const auto& j : i.second) {
                std::cout << j << " ";
            }
            std::cout << std::endl;
        }
    }

    // Function to get all vertices
    std::vector<int> getAllVertices() const {
        std::vector<int> allVertices;
        for (const auto& pair : adjacencyList) {
            allVertices.push_back(pair.first);
        }
        return allVertices;
    }
};

// Tarjan's Algorithm to find Strongly Connected Components
class TarjanSCC {
private:
    std::unordered_map<int, int> visitedTime;
    std::unordered_map<int, int> lowTime;
    std::unordered_set<int> onStack;
    std::stack<int> stack;
    std::unordered_set<int> visited;
    std::vector<std::unordered_set<int>> result;
    int time;

    void sccUtil(int vertex, const Graph& graph) {
        visited.insert(vertex);
        visitedTime[vertex] = lowTime[vertex] = time++;
        stack.push(vertex);
        onStack.insert(vertex);

        for (const auto& child : graph.adjacencyList.at(vertex)) {
            int v = child;
            if (visited.find(v) == visited.end()) {
                sccUtil(v, graph);
                lowTime[vertex] = std::min(lowTime[vertex], lowTime[v]);
            } else if (onStack.find(v) != onStack.end()) {
                lowTime[vertex] = std::min(lowTime[vertex], visitedTime[v]);
            }
        }

        if (visitedTime[vertex] == lowTime[vertex]) {
            std::unordered_set<int> scc;
            int v;
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
    std::vector<std::unordered_set<int>> scc(const Graph& graph) {
        time = 0;
        visitedTime.clear();
        lowTime.clear();
        onStack.clear();
        while (!stack.empty()) stack.pop();
        visited.clear();
        result.clear();

        for (int vertex : graph.getAllVertices()) {
            if (visited.find(vertex) == visited.end()) {
                sccUtil(vertex, graph);
            }
        }

        return result;
    }
};

int main() {
    std::ifstream infile("input1.txt"); // Change to the filename as needed
    if (!infile) {
        std::cerr << "Error opening file." << std::endl;
        return 1;
    }

    int num_vertices, num_edges;
    bool isDirected = true; // Assuming directed graph for Tarjan's algorithm

    infile >> num_vertices;
    infile >> num_edges;

    Graph g(isDirected);

    for (int i = 0; i < num_edges; i++) {
        int u, v;
        infile >> u >> v;
        g.add_edge(u, v);
    }

    infile.close();

    std::cout << "Graph:" << std::endl;
    g.print();

    TarjanSCC tarjanSCC;
    std::cout << "Running Tarjan's Algorithm for Strongly Connected Components:" << std::endl;
    auto result = tarjanSCC.scc(g);

    std::cout << "Strongly Connected Components:" << std::endl;
    int sccIndex = 1;
    for (const auto& scc : result) {
        std::cout << "SCC " << sccIndex++ << ": ";
        for (const auto& vertex : scc) {
            std::cout << vertex << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}
