#include <iostream>
#include <climits>
#include <list>
#include <vector>
#include <algorithm>
#include <map>
#include <set>

class Graph {
public:
    std::map<int, std::list<int>> adjacencyList;

public:
    void add_edge(int u, int v) {
        adjacencyList[u].push_back(v);
        adjacencyList[v].push_back(u);
    }

    void print() {
        for (const auto& i : adjacencyList) {
            std::cout << i.first << " -> ";
            for (const auto& j : i.second) {
                std::cout << "vertex: " << j << " ";
            }
            std::cout << std::endl;
        }
    }

    void findArticulationPointsHelper(int u, std::vector<bool>& visited,
                                      std::vector<int>& discoveryTime, std::vector<int>& lowTime, 
                                      std::vector<int>& parent, std::vector<bool>& articulationPoints) {
        static int time = 0;
        visited[u] = true;
        discoveryTime[u] = lowTime[u] = ++time;
        int children = 0;

        for (int v : adjacencyList[u]) {
            if (!visited[v]) {
                children++;
                parent[v] = u;
                findArticulationPointsHelper(v, visited, discoveryTime, lowTime, parent, articulationPoints);

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

    void findArticulationPoints() {
        int adjSize = adjacencyList.size();
        std::vector<bool> visited(adjSize, false);
        std::vector<int> discoveryTime(adjSize, -1);
        std::vector<int> lowTime(adjSize, -1);
        std::vector<int> parent(adjSize, -1);
        std::vector<bool> articulationPoints(adjSize, false);

        for (const auto& i : adjacencyList) {
            if (!visited[i.first]) {
                findArticulationPointsHelper(i.first, visited, discoveryTime, lowTime, parent, articulationPoints);
            }
        }

        std::cout << "Articulation points in the graph: ";
        for (int i = 0; i < adjSize; i++) {
            if (articulationPoints[i]) {
                std::cout << i << " ";
            }
        }
        std::cout << std::endl;
    }
};

#define RUN 5
#define MAX_VERTICES 20
#define MAX_EDGES 200

int main() {
    std::set<std::pair<int, int>> container;

    std::srand(std::time(NULL));

    int NUM; // Number of Vertices
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

            while (container.find(p) != container.end()
                   || container.find(reverse_p) != container.end()
                   || a == b) { // Ensuring no self-loops
                a = std::rand() % NUM;
                b = std::rand() % NUM;
                p = std::make_pair(a, b);
                reverse_p = std::make_pair(b, a);
            }
            container.insert(p);
        }

        for (auto it = container.begin(); it != container.end(); ++it) {
            g.add_edge(it->first, it->second);
            std::printf("%d %d\n", it->first, it->second);
        }

        container.clear();

        // Print the graph and find articulation points
        std::cout << "Graph structure:\n";
        g.print();

        std::cout << "Articulation Points:\n";
        g.findArticulationPoints();
        std::cout << std::endl;
    }

    return 0;
}
