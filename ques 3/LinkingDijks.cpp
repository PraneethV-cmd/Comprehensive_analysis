#include <iostream>
#include <list>
#include <utility>
#include <vector>
#include <map>
#include <set>
#include <climits>
#include <algorithm>
#include <cstdlib>
#include <ctime>

#define RUN 5
#define MAX_VERTICES 20
#define MAX_EDGES 200
#define MAXWEIGHT 200

class Graph {
public:
    std::map<int, std::list<std::pair<int, int>>> adjacencyList;

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
    srand(time(NULL));

    for (int i = 1; i <= RUN; i++) {
        int NUM = 1 + rand() % MAX_VERTICES;
        int NUMEDGE = 1 + rand() % MAX_EDGES;
        while (NUMEDGE > NUM * (NUM - 1) / 2)
            NUMEDGE = 1 + rand() % MAX_EDGES;

        std::cout << "Test case " << i << ":" << std::endl;
        std::cout << "Vertices: " << NUM << ", Edges: " << NUMEDGE << std::endl;

        Graph g;
        std::set<std::pair<int, int>> container;

        for (int j = 1; j <= NUMEDGE; j++) {
            int a = rand() % NUM;
            int b = rand() % NUM;
            std::pair<int, int> p = std::make_pair(a, b);
            std::pair<int, int> reverse_p = std::make_pair(b, a);
            
            while (container.find(p) != container.end() ||
                   container.find(reverse_p) != container.end()) {
                a = rand() % NUM;
                b = rand() % NUM;
                p = std::make_pair(a, b);
                reverse_p = std::make_pair(b, a);
            }
            container.insert(p);
            
            int wt = 1 + rand() % MAXWEIGHT;
            g.add_edge(a, b, wt);
        }

        std::cout << "Graph:" << std::endl;
        g.print();

        int src = rand() % NUM;
        std::cout << "Running Dijkstra's algorithm from source: " << src << std::endl;
        g.naive_dijkstra(src);

        std::cout << "\n";
    }

    return 0;
}