#include <bits/stdc++.h>
using namespace std;

class Graph {
public:
    map<int, vector<pair<int, int>>> adjacencyList;

public:
    void add_edge(int u, int v, int weight) {
        adjacencyList[u].push_back(make_pair(v, weight));
        adjacencyList[v].push_back(make_pair(u, weight));
    }

    void print() {
        for (auto i : adjacencyList) {
            cout << i.first << "->";
            for (auto j : i.second) {
                cout << j.first << " " << j.second << " ";
            }
            cout << endl;
        }
    }

    void shortest_path(int src) {
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> minPrioriQueue;
        map<int, int> dist;

        for (auto i : adjacencyList) {
            dist[i.first] = INT_MAX;
        }

        minPrioriQueue.push(make_pair(0, src));
        dist[src] = 0;

        while (!minPrioriQueue.empty()) {
            int u = minPrioriQueue.top().second;
            minPrioriQueue.pop();

            for (auto i : adjacencyList[u]) {
                int v = i.first;
                int weight = i.second;

                if (dist[v] > dist[u] + weight) {
                    dist[v] = dist[u] + weight;
                    minPrioriQueue.push(make_pair(dist[v], v));
                }
            }
        }

        cout << "Vertex distance from the source" << endl;
        for (auto i : dist) {
            cout << i.first << "\t" << i.second << endl;
        }
    }
};

#define RUN 5
#define MAX_VERTICES 20
#define MAX_EDGES 200
#define MAXWEIGHT 200

int main() {
    set<pair<int, int>> container;
    set<pair<int, int>>::iterator it;

    //For random values every time
    srand(time(NULL));

    int NUM;    // Number of Vertices
    int NUMEDGE; // Number of Edges

    for (int i = 1; i <= RUN; i++) {
        Graph g;

        NUM = 1 + rand() % MAX_VERTICES;
        NUMEDGE = 1 + rand() % MAX_EDGES;

        while (NUMEDGE > NUM * (NUM - 1) / 2)
            NUMEDGE = 1 + rand() % MAX_EDGES;

        printf("%d %d\n", NUM, NUMEDGE);

        for (int j = 1; j <= NUMEDGE; j++) {
            int a = rand() % NUM;
            int b = rand() % NUM;
            pair<int, int> p = make_pair(a, b);
            pair<int, int> reverse_p = make_pair(b, a);

            while (container.find(p) != container.end() ||
                    container.find(reverse_p) != container.end()) {
                a = rand() % NUM;
                b = rand() % NUM;
                p = make_pair(a, b);
                reverse_p = make_pair(b, a);
            }
            container.insert(p);
        }

        for (it = container.begin(); it != container.end(); ++it) {
            int wt = 1 + rand() % MAXWEIGHT;
            g.add_edge(it->first, it->second, wt);
            printf("%d %d %d\n", it->first, it->second, wt);
        }

        container.clear();

        // Choose a random source vertex and find the shortest paths
        int src = rand() % NUM;
        cout << "Source Vertex: " << src << endl;
        g.shortest_path(src);
        cout << endl;
    }

    return 0;
}
