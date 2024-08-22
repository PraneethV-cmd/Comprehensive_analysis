#include <bits/stdc++.h>
using namespace std;

class Graph {
public:
    map<int, list<int>> adjacencyList;

public:
    void add_edge(int u, int v) {
        adjacencyList[u].push_back(v);
        adjacencyList[v].push_back(u);
    }

    void print() {
        for (auto i : adjacencyList) {
            cout << i.first << " -> ";
            for (auto j : i.second) {
                cout << "vertex: " << j << " ";
            }
            cout << endl;
        }
    }

    void findArticulationPointsHelper(int u, vector<bool>& visited,
        vector<int>& discoveryTime, vector<int>& lowTime, vector<int>& parent, vector<bool>& articulationPoints) {
        static int time = 0;
        visited[u] = true;
        discoveryTime[u] = lowTime[u] = ++time;
        int children = 0;

        for (int v : adjacencyList[u]) {
            if (!visited[v]) {
                children++;
                parent[v] = u;
                findArticulationPointsHelper(v, visited, discoveryTime, lowTime, parent, articulationPoints);

                lowTime[u] = min(lowTime[u], lowTime[v]);

                if (parent[u] == -1 && children > 1)
                    articulationPoints[u] = true;

                if (parent[u] != -1 && lowTime[v] >= discoveryTime[u])
                    articulationPoints[u] = true;

            } else if (v != parent[u]) {
                lowTime[u] = min(lowTime[u], discoveryTime[v]);
            }
        }
    }

    void findArticulationPoints() {
        int adjSize = adjacencyList.size();
        vector<bool> visited(adjSize, false);
        vector<int> discoveryTime(adjSize, -1);
        vector<int> lowTime(adjSize, -1);
        vector<int> parent(adjSize, -1);
        vector<bool> articulationPoints(adjSize, false);

        for (auto i : adjacencyList) {
            if (!visited[i.first]) {
                findArticulationPointsHelper(i.first, visited, discoveryTime, lowTime, parent, articulationPoints);
            }
        }

        cout << "Articulation points in the graph: ";
        for (int i = 0; i < adjSize; i++) {
            if (articulationPoints[i]) {
                cout << i << " ";
            }
        }
        cout << endl;
    }
};

#define RUN 5
#define MAX_VERTICES 20
#define MAX_EDGES 200

int main() {
    set<pair<int, int>> container;
    set<pair<int, int>>::iterator it;

    srand(time(NULL));

    int NUM; // Number of Vertices
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

            while (container.find(p) != container.end()
                   || container.find(reverse_p) != container.end()
                   || a == b) { // Ensuring no self-loops
                a = rand() % NUM;
                b = rand() % NUM;
                p = make_pair(a, b);
                reverse_p = make_pair(b, a);
            }
            container.insert(p);
        }

        for (it = container.begin(); it != container.end(); ++it) {
            g.add_edge(it->first, it->second);
            printf("%d %d\n", it->first, it->second);
        }

        container.clear();

        // Print the graph and find articulation points
        cout << "Graph structure:\n";
        g.print();

        cout << "Articulation Points:\n";
        g.findArticulationPoints();
        cout << endl;
    }

    return 0;
}
