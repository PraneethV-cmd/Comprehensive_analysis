#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <unordered_set>

class Graph {
public:
    int n;
    std::vector<std::vector<int> > adjacencyMatrix;

    Graph(int n) : n(n) {
        adjacencyMatrix.resize(n * n, std::vector<int>(n * n, 0));
    }

    void addEdge(int u, int v) {
        adjacencyMatrix[u][v] = 1;
    }

    bool isWinPath() {
        std::vector<bool> visited(n * n, false);
        std::queue<int> auxQueue;
        auxQueue.push(0);
        visited[0] = true;

        while (!auxQueue.empty()) {
            int currNode = auxQueue.front();
            auxQueue.pop();

            if (currNode == n * n - 1) return true;

            for (int i = 0; i < n * n; i++) {
                if (adjacencyMatrix[currNode][i] && !visited[i]) {
                    visited[i] = true;
                    auxQueue.push(i);
                }
            }
        }
        return false;
    }

    bool isCycle(int start) {
        std::vector<bool> visited(n * n, false);
        std::vector<bool> inStack(n * n, false);
        std::stack<int> auxStack;

        auxStack.push(start);

        while (!auxStack.empty()) {
            int currNode = auxStack.top();
            auxStack.pop();

            if (!visited[currNode]) {
                visited[currNode] = true;
                inStack[currNode] = true;
            }

            for (int i = 0; i < n * n; i++) {
                if (adjacencyMatrix[currNode][i]) {
                    if (!visited[i]) {
                        auxStack.push(i);
                    } else if (inStack[i]) {
                        return true;
                    }
                }
            }

            inStack[currNode] = false;
        }

        return false;
    }

    bool hasDuplicatePositions(const std::vector<std::pair<int, int> >& snakes, const std::vector<std::pair<int, int> >& ladders) {
        std::unordered_set<int> starts, ends;

        for (auto s : snakes) {
            if (starts.count(s.first) || ends.count(s.second)) {
                return true;
            }
            starts.insert(s.first);
            ends.insert(s.second);
        }
        for (auto l : ladders) {
            if (starts.count(l.first) || ends.count(l.second)) {
                return true;
            }
            starts.insert(l.first);
            ends.insert(l.second);
        }

        return false;
    }
};

int main() {
    int n = 5;
    Graph g(n);

    std::vector<std::pair<int, int> > snakes;
    snakes.push_back(std::make_pair(16,3));
    snakes.push_back(std::make_pair(18,6));
    snakes.push_back(std::make_pair(20,8));

    std::vector<std::pair<int, int> > ladders;
    ladders.push_back(std::make_pair(2,21)); 
    ladders.push_back(std::make_pair(4,7));
    ladders.push_back(std::make_pair(10,25));
    
    // Adding ladders
    for (auto ladder : ladders) {
        g.addEdge(ladder.first - 1, ladder.second - 1);
    }

    // Adding snakes
    for (auto snake : snakes) {
        g.addEdge(snake.first - 1, snake.second - 1);
    }

    // Adding standard edges (normal moves)
    for (int i = 0; i < n * n - 1; i++) {
        for (int j = 1; j <= 6; j++) {
            if (i + j < n * n) {
                g.addEdge(i, i + j);
            }
        }
    }

    if (!g.isWinPath()) {
        std::cout << "No valid path to go to the end" << std::endl;
    } else if (g.hasDuplicatePositions(snakes, ladders)) {
        std::cout << "Duplicate positions are there." << std::endl;
    } else if (g.isCycle(0)) {
        std::cout << "Not a valid board" << std::endl;
    } else {
        std::cout << "Valid board" << std::endl;
    }

    return 0;
}

