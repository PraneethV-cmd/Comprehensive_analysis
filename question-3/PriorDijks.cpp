#include <iostream>
#include <climits>
#include <list>
#include <vector>
#include <algorithm>
#include <map>
#include <set>
#include <queue>

class Graph {
public:
    std::map<int, std::vector<std::pair<int, int>>> adjacencyList;

public:
    void add_edge(int u, int v, int weight) {
        adjacencyList[u].push_back(std::make_pair(v, weight));
        adjacencyList[v].push_back(std::make_pair(u, weight));
    }

    void print() {
        for (const auto& i : adjacencyList) {
            std::cout << i.first << "->";
            for (const auto& j : i.second) {
                std::cout << j.first << " " << j.second << " ";
            }
            std::cout << std::endl;
        }
    }

    void shortest_path(int src) {
        std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> minPrioriQueue;
        std::map<int, int> dist;

        for (const auto& i : adjacencyList) {
            dist[i.first] = INT_MAX;
        }

        minPrioriQueue.push(std::make_pair(0, src));
        dist[src] = 0;

        while (!minPrioriQueue.empty()) {
            int u = minPrioriQueue.top().second;
            minPrioriQueue.pop();

            for (const auto& i : adjacencyList[u]) {
                int v = i.first;
                int weight = i.second;

                if (dist[v] > dist[u] + weight) {
                    dist[v] = dist[u] + weight;
                    minPrioriQueue.push(std::make_pair(dist[v], v));
                }
            }
        }

        std::cout << "Vertex distance from the source" << std::endl;
        for (const auto& i : dist) {
            std::cout << i.first << "\t" << i.second << std::endl;
        }
    }
};

#define RUN 5
#define MAX_VERTICES 20
#define MAX_EDGES 200
#define MAXWEIGHT 200

int main() {
    std::set<std::pair<int, int>> container;

    // For random values every time
    std::srand(std::time(NULL));

    int NUM;    // Number of Vertices
    int NUMEDGE; // Number of Edges

    for (int i = 1; i <= RUN; i++) {
        Graph g;

        NUM = 1 + std::rand() % MAX_VERTICES;
        NUMEDGE = 1 + std::rand() % MAX_EDGES;

        while (NUMEDGE > NUM * (NUM - 1) / 2)
            NUMEDGE = 1 + std::rand() % MAX_EDGES;

        std::printf("%d %d\n", NUM, NUMEDGE);

        for (int j = 1; j <= NUMEDGE; j++) {
            int a = std::rand() % NUM;
            int b = std::rand() % NUM;
            std::pair<int, int> p = std::make_pair(a, b);
            std::pair<int, int> reverse_p = std::make_pair(b, a);

            while (container.find(p) != container.end() ||
                   container.find(reverse_p) != container.end()) {
                a = std::rand() % NUM;
                b = std::rand() % NUM;
                p = std::make_pair(a, b);
                reverse_p = std::make_pair(b, a);
            }
            container.insert(p);
        }

        for (auto it = container.begin(); it != container.end(); ++it) {
            int wt = 1 + std::rand() % MAXWEIGHT;
            g.add_edge(it->first, it->second, wt);
            std::printf("%d %d %d\n", it->first, it->second, wt);
        }

        container.clear();

        // Choose a random source vertex and find the shortest paths
        int src = std::rand() % NUM;
        std::cout << "Source Vertex: " << src << std::endl;
        g.shortest_path(src);
        std::cout << std::endl;
    }

    return 0;
}
