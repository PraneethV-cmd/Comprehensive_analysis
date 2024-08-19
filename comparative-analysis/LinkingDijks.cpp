#include <iostream>
#include <list>
#include <utility>
#include <vector>
#include <map>
#include <climits>
#include <algorithm> // For std::min_element and std::remove_if

class Graph {

public:
    std::map<int, std::list<std::pair<int, int> > > adjacencyList;

    void add_edge(int u, int v, int weight) {
        adjacencyList[u].push_back(std::make_pair(v, weight));
        adjacencyList[v].push_back(std::make_pair(u, weight));
    }

    void print() {
        for (auto i : adjacencyList) {
            std::cout << i.first << " -> ";
            for (auto j : i.second) {
                std::cout << "Vertex: " << j.first << ", Weight: " << j.second << " ";
            }
            std::cout << std::endl;
        }
    }

    void naive_dijkstra(int src) {
        std::list<std::pair<int, int> > minList;
        std::map<int, int> dist;

        for (auto i : this->adjacencyList) {
            dist[i.first] = INT_MAX;
        }

        minList.push_front(std::make_pair(0, src));
        dist[src] = 0;

        while (!minList.empty()) {
            // Find the minimum element
            auto minElem = std::min_element(minList.begin(), minList.end());
            int u = minElem->second;

            // Remove the minimum element
            minList.erase(minElem);

            // Process adjacent vertices
            for (auto i : adjacencyList[u]) {
                int v = i.first;
                int weight = i.second;

                if (dist[v] > dist[u] + weight) {
                    dist[v] = dist[u] + weight;
                    minList.push_front(std::make_pair(dist[v], v));
                }
            }
        }

        std::cout << "Vertex distance from the source" << std::endl;
        for (auto i : dist) {
            std::cout << i.first << "\t" << i.second << std::endl;
        }
    }
};

int main() {
    Graph g;

    // Adding edges for a graph with 7 nodes
    g.add_edge(0, 1, 4);
    g.add_edge(0, 2, 3);
    g.add_edge(1, 2, 1);
    g.add_edge(1, 3, 2);
    g.add_edge(2, 3, 4);
    g.add_edge(3, 4, 2);
    g.add_edge(4, 5, 6);
    g.add_edge(4, 6, 7);
    g.add_edge(5, 6, 3);

    g.print();

    // Run naive Dijkstra's algorithm from source node 0
    g.naive_dijkstra(0);

    return 0;
}

