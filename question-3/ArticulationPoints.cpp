#include <iostream>
#include <climits>
#include <vector>
#include <map>
#include <set>

class Graph {
public:
    std::map<int, std::vector<int>> adjacencyList;// Adjacency list representation of the graph

    std::set<int> vertices;

    // This function adds an edge to the graph
    void add_edge(int u, int v) {
        adjacencyList[u].push_back(v);
        adjacencyList[v].push_back(u);
        vertices.insert(u);
        vertices.insert(v);
    }

    // This function prints the graph
    void print() const {
        for (const auto& node : adjacencyList) {
            std::cout << node.first << " -> ";
            for (const auto& neighbor : node.second) {
                std::cout << neighbor << " ";
            }
            std::cout << std::endl;
        }
    }

    // This function finds the articulation points using DFS
    void findpoints(int u, std::map<int, bool>& visited,
                                      std::map<int, int>& discoveryTime, std::map<int, int>& lowTime, 
                                      std::map<int, int>& parent, std::map<int, bool>& articulationPoints) {
        static int time = 0;
        visited[u] = true;
        discoveryTime[u] = lowTime[u] = ++time;
        int children = 0;

        for (int v : adjacencyList[u]) {
            if (!visited[v]) {
                children++;
                parent[v] = u;
                findpoints(v, visited, discoveryTime, lowTime, parent, articulationPoints);

                lowTime[u] = std::min(lowTime[u], lowTime[v]);

                if (parent[u] == -1 && children > 1)
                    articulationPoints[u] = true;

                if (parent[u] != -1 && lowTime[v] >= discoveryTime[u])
                    articulationPoints[u] = true;

            } else if (v != parent[u]) {
                lowTime[u] = std::min(lowTime[u], discoveryTime[v]);
            }
        }
    }

    // Function to find all articulation points in the graph and prints it.
    void articulationpoints() {
        std::map<int, bool> visited;
        std::map<int, int> discoveryTime;
        std::map<int, int> lowTime;
        std::map<int, int> parent;
        std::map<int, bool> articulationPoints;

        for (int vertex : vertices) {
            visited[vertex] = false;
            discoveryTime[vertex] = -1;
            lowTime[vertex] = -1;
            parent[vertex] = -1;
            articulationPoints[vertex] = false;
        }

        for (int vertex : vertices) {
            if (!visited[vertex]) {
                findpoints(vertex, visited, discoveryTime, lowTime, parent, articulationPoints);
            }
        }

        std::cout << "Articulation points in the graph: ";
        for (int vertex : vertices) {
            if (articulationPoints[vertex]) {
                std::cout << vertex << " ";
            }
        }
        std::cout << std::endl;
    }
};

int main() {
    int numVertices, numEdges;

    std::cout << "Enter the number of vertices: ";
    std::cin >> numVertices;

    std::cout << "Enter the number of edges: ";
    std::cin >> numEdges;

    Graph g;

    std::cout << "Enter the edges (start vertex, end vertex):" << std::endl;
    for (int i = 0; i < numEdges; ++i) {
        int u, v;
        std::cin >> u >> v;

        if (u < 0 || v < 0) {
            std::cout << "Invalid vertices. Vertices should be non-negative." << std::endl;
            --i;
            continue;
        }

        g.add_edge(u, v);
    }

    std::cout << "Graph structure:\n";
    g.print();

    std::cout << "\nFinding articulation points in the graph...\n";
    g.articulationpoints();

    return 0;
}
