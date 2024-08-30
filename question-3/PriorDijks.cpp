#include <iostream>
#include <climits>
#include <list>
#include <vector>
#include <algorithm>
#include <map>
#include <set>
#include <queue>

//This Class is to represent a graph
class Graph {
public:
    std::map<int, std::vector<std::pair<int, int>>> adjacencyList; // Adjacency list representation of the graph 

    //This function adds an edge to the graph 
    void add_edge(int u, int v, int weight) {
        adjacencyList[u].emplace_back(v, weight);
        adjacencyList[v].emplace_back(u, weight);
    }

    //This function prints the graph
    void print() const {
        for (const auto& node : adjacencyList) {
            std::cout << node.first << " -> ";
            for (const auto& edge : node.second) {
                std::cout << "(" << edge.first << ", " << edge.second << ") ";
            }
            std::cout << std::endl;
        }
    }

    //This function is used to find the shortes path using the Dijkstra algorithm. This uses the priority queue to store vertices and maps the shortest distance.
    void shortest_path(int src) {
        std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<>> minPrioriQueue;
        std::map<int, int> dist;

        for (const auto& node : adjacencyList) {
            dist[node.first] = INT_MAX;
        }

        minPrioriQueue.push(std::make_pair(0, src));
        dist[src] = 0;

        while (!minPrioriQueue.empty()) {
            int u = minPrioriQueue.top().second;
            minPrioriQueue.pop();

            for (const auto& edge : adjacencyList[u]) {
                int v = edge.first;
                int weight = edge.second;

                if (dist[v] > dist[u] + weight) {
                    dist[v] = dist[u] + weight;
                    minPrioriQueue.push(std::make_pair(dist[v], v));
                }
            }
        }
        std::cout << "Vertex distance from the source:" << std::endl;
        for (const auto& node : dist) {
            std::cout << node.first << "\t" << node.second << std::endl;
        }
    }
};

int main() {
    int numVertices = 20; 
    int numEdges;

    std::cout << "Enter the number of edges: ";
    std::cin >> numEdges;

    Graph g;

    std::cout << "Enter the edges (start vertex, end vertex, weight):" << std::endl;
    for (int i = 0; i < numEdges; ++i) {
        int u, v, weight;
        std::cin >> u >> v >> weight;

        // This checks whether the entered vertices are valid
        if (u < 0 || u >= numVertices || v < 0 || v >= numVertices) {
            std::cout << "Invalid vertices. Vertices should be between 0 and " << numVertices - 1 << "." << std::endl;
            --i;  
            continue;
        }

        g.add_edge(u, v, weight);
    }

    int src;
    std::cout << "Enter the source vertex: ";
    std::cin >> src;

    if (src < 0 || src >= numVertices) {
        std::cout << "Invalid source vertex. Must be between 0 and " << numVertices - 1 << "." << std::endl;
        return 1;
    }

    g.shortest_path(src);

    return 0;
}