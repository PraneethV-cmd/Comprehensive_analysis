#include <iostream>
#include <vector>
#include <climits>
#include <set>
#include <cstdlib>
#include <ctime>

struct edge {
    int src, des, weight;
};

std::pair<bool, std::vector<int>> bellmanFord(std::vector<edge>& graph, int vertex, int source) {
    std::vector<int> distances(vertex, INT_MAX);
    distances[source] = 0;

    for (int i = 0; i < vertex - 1; i++) {
        for (int j = 0; j < graph.size(); j++) {
            if (distances[graph[j].src] != INT_MAX && distances[graph[j].des] > distances[graph[j].src] + graph[j].weight) {
                distances[graph[j].des] = distances[graph[j].src] + graph[j].weight;
            }
        }
    }

    for (int j = 0; j < graph.size(); j++) {
        if (distances[graph[j].src] != INT_MAX && distances[graph[j].des] > distances[graph[j].src] + graph[j].weight) {
            return std::make_pair(false, std::vector<int>());
        }
    }

    return std::make_pair(true, distances);
}

int main() {
    std::set<std::pair<int, int>> container;
    std::set<std::pair<int, int>>::iterator it;

    // Uncomment the below line to store the test data in a file
    // freopen("Test_Cases_Directed_Weighted_Graph.in", "w", stdout);

    std::srand(std::time(NULL));

    int RUN = 5;
    int MAX_VERTICES = 20;
    int MAX_EDGES = 200;
    int MAXWEIGHT = 200;

    for (int i = 1; i <= RUN; i++) {
        int vertex = 1 + std::rand() % MAX_VERTICES;
        int edges = 1 + std::rand() % MAX_EDGES;

        while (edges > vertex * (vertex - 1) / 2)
            edges = 1 + std::rand() % MAX_EDGES;

        std::vector<edge> graph;

        std::printf("%d %d\n", vertex, edges);

        for (int j = 1; j <= edges; j++) {
            int src = 1 + std::rand() % vertex;
            int des = 1 + std::rand() % vertex;
            std::pair<int, int> p = std::make_pair(src, des);

            while (container.find(p) != container.end()) {
                src = 1 + std::rand() % vertex;
                des = 1 + std::rand() % vertex;
                p = std::make_pair(src, des);
            }
            container.insert(p);

            int wt = 1 + std::rand() % MAXWEIGHT;
            graph.push_back({src - 1, des - 1, wt}); // Adjusting to 0-indexed for the Bellman-Ford function
            std::printf("%d %d %d\n", src, des, wt);
        }

        int source = std::rand() % vertex;
        std::printf("Source: %d\n", source + 1); // Adjusting to 1-indexed for user understanding
        std::pair<bool, std::vector<int>> result = bellmanFord(graph, vertex, source);

        if (result.first) {
            std::cout << "No Negative Weight Cycle Exists!" << std::endl;
            for (int dist : result.second) {
                if (dist == INT_MAX) {
                    std::cout << "INF ";
                } else {
                    std::cout << dist << " ";
                }
            }
            std::cout << std::endl;
        } else {
            std::cout << "Graph Has Negative Weight Cycle" << std::endl;
        }
        std::cout << std::endl;

        container.clear();
    }

    // Uncomment the below line to store the test data in a file
    // fclose(stdout);
    return 0;
}
