#include <iostream>
#include <list>
#include <utility>
#include <vector>
#include <map>
#include <set>
#include <climits>
#include <algorithm>

// Class to represent a graph
class Graph {
public:
    std::map<int, std::list<std::pair<int, int>>> adjacencyList; // Adjacency list representation

    // Add an edge to the graph
    void add_edge(int u, int v, int weight) {
        adjacencyList[u].push_back(std::make_pair(v, weight));
        adjacencyList[v].push_back(std::make_pair(u, weight));
    }

    // Print the graph
    void print() {
        for (auto i : adjacencyList) {
            std::cout << i.first << " -> ";
            for (auto j : i.second) {
                std::cout << "Vertex: " << j.first << ", Weight: " << j.second << " ";
            }
            std::cout << std::endl;
        }
    }

    // Get all vertices
    std::vector<int> getAllVertices() {
        std::vector<int> vertexList;
        for (auto& pair : adjacencyList) {
            vertexList.push_back(pair.first);
        }
        return vertexList;
    }

    // Find bridges in the graph
    std::set<std::pair<int, int>> getBridges() {
        std::set<std::pair<int, int>> bridges;
        std::map<int, int> discovery;
        std::map<int, int> low;
        std::map<int, int> parent;
        std::map<int, bool> visited;
        int time = 0;

        for (int vertex : getAllVertices()) {
            if (!visited[vertex]) {
                BridgeUtil(vertex, discovery, low, parent, visited, bridges, time);
            }
        }

        return bridges;
    }

private:
    void BridgeUtil(int u, std::map<int, int>& discovery, std::map<int, int>& low, 
                    std::map<int, int>& parent, std::map<int, bool>& visited, 
                    std::set<std::pair<int, int>>& bridges, int& time) {
        visited[u] = true;
        discovery[u] = low[u] = ++time;

        for (auto& neighbor : adjacencyList[u]) {
            int v = neighbor.first;
            if (!visited[v]) {
                parent[v] = u;
                BridgeUtil(v, discovery, low, parent, visited, bridges, time);

                low[u] = std::min(low[u], low[v]);

                if (low[v] > discovery[u]) {
                    bridges.insert(std::make_pair(u, v));
                }
            } else if (v != parent[u]) {
                low[u] = std::min(low[u], discovery[v]);
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
    
    std::set<std::pair<int, int>> bridges = g.getBridges();
    
    std::cout << "Bridges in the graph:" << std::endl;
    for (const auto& bridge : bridges) {
        std::cout << bridge.first << " -- " << bridge.second << std::endl;
    }

    return 0;
}
