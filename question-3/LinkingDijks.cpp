#include <iostream>
#include <list>
#include <utility>
#include <vector>
#include <map>
#include <set>
#include <climits>
#include <algorithm>

//This Class is to represent a graph
class Graph {
public:
    std::map<int, std::list<std::pair<int, int>>> adjacencyList;// Adjacency list representation of the graph 

    //This function adds an edge to the graph 
    void add_edge(int u, int v, int weight) {
        adjacencyList[u].push_back(std::make_pair(v, weight));
        adjacencyList[v].push_back(std::make_pair(u, weight));
    }

    //This function prints the graph
    void print() {
        for (auto i : adjacencyList) {
            std::cout << i.first << " -> ";
            for (auto j : i.second) {
                std::cout << "Vertex: " << j.first << ", Weight: " << j.second << " ";
            }
            std::cout << std::endl;
        }
    }

    //This function is used to find the shortest path using the Dijkstra algorithm. THis uses the minimum distance list to store vertices and maps the shortest distance.
    void naive_dijkstra(int src) {
        std::list<std::pair<int, int>> minList;
        std::map<int, int> dist;
        for (auto i : this->adjacencyList) {
            dist[i.first] = INT_MAX;
        }
        minList.push_front(std::make_pair(0, src));
        dist[src] = 0;

        while (!minList.empty()) {
            auto minElem = std::min_element(minList.begin(), minList.end());
            int u = minElem->second;
            minList.erase(minElem);

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
    
    int src;
    std::cout << "Enter the source vertex for Dijkstra's algorithm: ";
    std::cin >> src;
    
    std::cout << "Running Dijkstra's algorithm from source: " << src << std::endl;
    g.naive_dijkstra(src);

    return 0;
}