#include <iostream>
#include <list>
#include <map>
#include <vector>
#include <climits>
#include <utility>
#include <set>
#include <cstdlib>
#include <ctime>

class Graph {
public:
    std::map<int, std::list<std::pair<int, int>>> adjacencyList;

    void add_edge(int u, int v, int weight) {
        this->adjacencyList[u].push_back(std::make_pair(v, weight));
        this->adjacencyList[v].push_back(std::make_pair(u, weight));
    }

    void print() {
        for (auto& i : this->adjacencyList) {
            std::cout << i.first << " -> ";
            for (auto& j : i.second) {
                std::cout << "( " << j.first << ", " << j.second << " ) ";
            }
            std::cout << std::endl;
        }
    }

    int find_vertex(int u, std::vector<int>& parent) {
        if (parent[u] == u) {
            return u;
        }
        parent[u] = find_vertex(parent[u], parent);
        return parent[u];
    }

    void union_vertices(int u, int v, std::vector<int>& parent, std::vector<int>& rank) {
        int rootU = find_vertex(u, parent);
        int rootV = find_vertex(v, parent);

        if (rootU != rootV) {
            if (rank[rootU] < rank[rootV]) {
                parent[rootU] = rootV;
            } else if (rank[rootV] < rank[rootU]) {
                parent[rootV] = rootU;
            } else {
                parent[rootV] = rootU;
                rank[rootU] += 1;
            }
        }
    }

    void boruvka() {
        int verticeCount = this->adjacencyList.size();
        std::vector<int> parent(verticeCount);
        std::vector<int> rank(verticeCount, 0);
        std::vector<int> min_weight_edge(verticeCount, -1);
        int mstWeight = 0;

        for (int i = 0; i < verticeCount; i++) {
            parent[i] = i;
        }

        int componentCount = verticeCount;
        while (componentCount > 1) {

            for (int i = 0; i < verticeCount; i++) {
                min_weight_edge[i] = -1;
            }

            for (int u = 0; u < verticeCount; u++) {
                for (auto& adj : this->adjacencyList[u]) {
                    int v = adj.first;
                    int weight = adj.second;

                    int set_u = find_vertex(u, parent);
                    int set_v = find_vertex(v, parent);

                    if (set_u != set_v) {
                        if (min_weight_edge[set_u] == -1 || this->adjacencyList[u][min_weight_edge[set_u]].second > weight) {
                            min_weight_edge[set_u] = v;
                        }

                        if (min_weight_edge[set_v] == -1 || this->adjacencyList[v][min_weight_edge[set_v]].second > weight) {
                            min_weight_edge[set_v] = u;
                        }
                    }
                }
            }

            for (int i = 0; i < verticeCount; i++) {
                if (min_weight_edge[i] != -1) {
                    int u = i;
                    int v = min_weight_edge[i];
                    int weight = this->adjacencyList[u].front().second;

                    int set_u = find_vertex(u, parent);
                    int set_v = find_vertex(v, parent);

                    if (set_u != set_v) {
                        std::cout << "Edge (" << u << ", " << v << ") with weight " << weight << " is in MST" << std::endl;
                        mstWeight += weight;
                        union_vertices(set_u, set_v, parent, rank);
                        componentCount--;
                    }
                }
            }
        }
        std::cout << "Total weight of MST is " << mstWeight << std::endl;
    }
};

#define RUN 5
#define MAX_VERTICES 20
#define MAX_EDGES 200
#define MAXWEIGHT 200

int main() {
    srand(time(NULL));

    for (int i = 1; i <= RUN; i++) {
        Graph g;
        std::set<std::pair<int, int>> container;

        int NUM = 1 + rand() % MAX_VERTICES;
        int NUMEDGE = 1 + rand() % MAX_EDGES;

        while (NUMEDGE > NUM * (NUM - 1) / 2)
            NUMEDGE = 1 + rand() % MAX_EDGES;

        std::cout << "Graph " << i << ": " << NUM << " vertices, " << NUMEDGE << " edges" << std::endl;

        for (int j = 1; j <= NUMEDGE; j++) {
            int a = rand() % NUM;
            int b = rand() % NUM;
            std::pair<int, int> p = std::make_pair(a, b);
            std::pair<int, int> reverse_p = std::make_pair(b, a);

            while (container.find(p) != container.end() || container.find(reverse_p) != container.end() || a == b) {
                a = rand() % NUM;
                b = rand() % NUM;
                p = std::make_pair(a, b);
                reverse_p = std::make_pair(b, a);
            }
            container.insert(p);
        }

        for (auto it = container.begin(); it != container.end(); ++it) {
            int wt = 1 + rand() % MAXWEIGHT;
            g.add_edge(it->first, it->second, wt);
            std::cout << it->first << " " << it->second << " " << wt << std::endl;
        }

        container.clear();

        std::cout << "Graph structure:\n";
        g.print();

        std::cout << "Minimum Spanning Tree using Boruvka's algorithm:\n";
        g.boruvka();
        std::cout << std::endl;
    }

    return 0;
}
