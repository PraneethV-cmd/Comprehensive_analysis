#include <iostream>
#include <climits>
#include <vector>
#include <tuple>
#include <map>

// This class represents a graph for the Bellman-Ford algorithm
class Graph {
public:
    int vertexCount;  // Number of vertices in the graph
    std::vector<std::tuple<int, int, int>> edges; // Stores edges as (src, dest, weight)

    // Constructor to initialize the graph with a given number of vertices
    Graph(int vertices) {
        vertexCount = vertices;
    }

    // Adds an edge to the graph
    // @param u: Source vertex of the edge
    // @param v: Destination vertex of the edge
    // @param weight: Weight of the edge
    void add_edge(int u, int v, int weight) {
        edges.push_back(std::make_tuple(u, v, weight));
    }

    // Prints the edges of the graph
    // This is useful for debugging or visualizing the graph
    void print() const {
        for (const auto& edge : edges) {
            std::cout << std::get<0>(edge) << " -> " << std::get<1>(edge)
                      << " with weight " << std::get<2>(edge) << std::endl;
        }
    }

    // Finds the shortest paths from the source vertex using the Bellman-Ford algorithm
    // @param source: The starting vertex for the shortest path calculation
    // @return: A pair containing a boolean indicating if there's no negative weight cycle
    //          and a vector of shortest path distances from the source vertex
    std::pair<bool, std::vector<int>> bellmanFord(int source) const {
        std::vector<int> distances(vertexCount, INT_MAX); // Initialize distances to all vertices as infinite
        distances[source] = 0; // Distance to the source vertex is 0

        // Relax edges |V|-1 times
        for (int i = 0; i < vertexCount - 1; i++) {
            for (const auto& edge : edges) {
                int u = std::get<0>(edge);
                int v = std::get<1>(edge);
                int weight = std::get<2>(edge);

                // Update the distance to the destination vertex if a shorter path is found
                if (distances[u] != INT_MAX && distances[v] > distances[u] + weight) {
                    distances[v] = distances[u] + weight;
                }
            }
        }

        // Check for negative weight cycles
        for (const auto& edge : edges) {
            int u = std::get<0>(edge);
            int v = std::get<1>(edge);
            int weight = std::get<2>(edge);

            // If we can still relax an edge, then a negative weight cycle exists
            if (distances[u] != INT_MAX && distances[v] > distances[u] + weight) {
                return std::make_pair(false, std::vector<int>());
            }
        }

        return std::make_pair(true, distances); // No negative weight cycle found
    }
};

int main() {
    int numVertices; // Number of vertices in the graph
    int numEdges; // Number of edges in the graph

    // Input the number of vertices
    std::cout << "Enter the number of vertices: ";
    std::cin >> numVertices;

    // Input the number of edges
    std::cout << "Enter the number of edges: ";
    std::cin >> numEdges;

    // Create a graph object with the specified number of vertices
    Graph g(numVertices);

    // Input edges from the user
    std::cout << "Enter the edges (start vertex, end vertex, weight):" << std::endl;

    for (int i = 0; i < numEdges; ++i) {
        int u, v, weight;
        std::cin >> u >> v >> weight;

        // Check if the vertices are valid
        if (u < 0 || u >= numVertices || v < 0 || v >= numVertices) {
            std::cout << "Invalid vertices. Vertices should be between 0 and " << numVertices - 1 << "." << std::endl;
            --i;
            continue;
        }

        // Add the edge to the graph
        g.add_edge(u, v, weight);
    }

    // Input the source vertex for the Bellman-Ford algorithm
    int src;
    std::cout << "Enter the source vertex: ";
    std::cin >> src;

    // Check if the source vertex is valid
    if (src < 0 || src >= numVertices) {
        std::cout << "Invalid source vertex. Must be between 0 and " << numVertices - 1 << "." << std::endl;
        return 1;
    }

    // Compute shortest paths using Bellman-Ford algorithm
    auto result = g.bellmanFord(src);

    // Output the result
    if (result.first) {
        std::cout << "No Negative Weight Cycle Exists!" << std::endl;
        std::cout << "Vertex distances from the source:" << std::endl;
        for (int i = 0; i < numVertices; ++i) {
            if (result.second[i] == INT_MAX) {
                std::cout << i << ": INF" << std::endl;
            } else {
                std::cout << i << ": " << result.second[i] << std::endl;
            }
        }
    } else {
        std::cout << "Graph Has a Negative Weight Cycle" << std::endl;
    }

    return 0;
}
