#include <iostream>
#include <list>
#include <utility>
#include <vector>
#include <map>
#include <set>
#include <climits>
#include <algorithm>
#include <stack>

// This class represents a graph
class Graph {
public:
    std::map<int, std::list<std::pair<int, int>>> adjacencyList; // Adjacency list representation of the graph

    // This function adds an edge to the graph
    void add_edge(int u, int v, int weight) {
        adjacencyList[u].push_back(std::make_pair(v, weight));
        adjacencyList[v].push_back(std::make_pair(u, weight));
    }

    // This function prints the graph
    void print() {
        for (auto i : adjacencyList) {
            std::cout << i.first << " -> ";
            for (auto j : i.second) {
                std::cout << "Vertex: " << j.first << ", Weight: " << j.second << " ";
            }
            std::cout << std::endl;
        }
    }

    // Kosaraju's Algorithm for finding Strongly Connected Components (SCCs)
    void kosaraju() {
        std::stack<int> Stack;
        std::map<int, bool> visited;
        std::map<int, std::list<int>> transpose;

        // Step 1: Fill vertices in stack according to their finishing times
        for (auto i : adjacencyList) {
            if (!visited[i.first]) {
                fillOrder(i.first, visited, Stack);
            }
        }

        // Step 2: Get the transpose of the graph
        transposeGraph(transpose);

        // Step 3: Process all vertices in order defined by stack
        visited.clear();
        std::cout << "Strongly Connected Components:" << std::endl;
        while (!Stack.empty()) {
            int v = Stack.top();
            Stack.pop();

            if (!visited[v]) {
                std::set<int> component;
                DFS(transpose, v, visited, component);
                for (int vertex : component) {
                    std::cout << vertex << " ";
                }
                std::cout << std::endl;
            }
        }
    }

private:
    // A recursive function to fill the stack with vertices according to their finishing times
    void fillOrder(int v, std::map<int, bool>& visited, std::stack<int>& Stack) {
        visited[v] = true;
        for (auto i : adjacencyList[v]) {
            if (!visited[i.first]) {
                fillOrder(i.first, visited, Stack);
            }
        }
        Stack.push(v);
    }

    // Function to get the transpose of the graph
    void transposeGraph(std::map<int, std::list<int>>& transpose) {
        for (auto i : adjacencyList) {
            for (auto j : i.second) {
                transpose[j.first].push_back(i.first);
            }
        }
    }

    // A function to perform DFS on the transposed graph and collect all vertices in a component
    void DFS(std::map<int, std::list<int>>& transpose, int v, std::map<int, bool>& visited, std::set<int>& component) {
        visited[v] = true;
        component.insert(v);
        for (auto i : transpose[v]) {
            if (!visited[i]) {
                DFS(transpose, i, visited, component);
            }
        }
    }
};

int main() {
    Graph g;
    int num_vertices, num_edges;

    std::cout << "Enter the number of vertices: ";
    std::cin >> num_vertices;

    std::cout << "Enter the number of edges: ";
    std::cin >> num_edges;

    std::cout << "Enter the edges in the format 'source destination weight':" << std::endl;
    for (int i = 0; i < num_edges; i++) {
        int u, v, weight;
        std::cin >> u >> v >> weight;
        g.add_edge(u, v, weight);
    }

    std::cout << "Graph:" << std::endl;
    g.print();

    std::cout << "Running Kosaraju's algorithm to find Strongly Connected Components (SCCs)..." << std::endl;
    g.kosaraju();

    return 0;
}
