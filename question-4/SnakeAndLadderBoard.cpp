#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <unordered_set>
#include <limits>

// Define a Graph class to represent the game board.
class Graph {
public:
    int n; 
    std::vector<std::vector<int>> adjacencyMatrix; // Adjacency matrix to represent graph connections.

    Graph(int n) : n(n) {
        adjacencyMatrix.resize(n * n, std::vector<int>(n * n, 0));
    }

    // Function to add an edge between two nodes u and v.
    void addEdge(int u, int v) {
        if (u >= 0 && u < n * n && v >= 0 && v < n * n) {
            adjacencyMatrix[u][v] = 1;
        }
    }

    // Function to check if there's a path from the start (0) to the end (n * n - 1) of the board.
    bool isWinPath() {
        std::vector<bool> visited(n * n, false);
        std::queue<int> auxQueue;
        auxQueue.push(0);
        visited[0] = true;

        while (!auxQueue.empty()) {
            int currNode = auxQueue.front();
            auxQueue.pop();
            
            // If we reach the last node, there's a winning path.
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
    // Function to check for cycles starting from a given node.
    //Each node is placed in the recursion stack and checked for cycles.If present True is returned else False.
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

    // Function to check for duplicate snake or ladder positions.
    bool hasDuplicatePositions(const std::vector<std::pair<int, int>>& snakes, const std::vector<std::pair<int, int>>& ladders) {
        std::unordered_set<int> starts, ends;

        // Check for duplicate start or end positions in snakes.
        for (auto s : snakes) {
            if (starts.count(s.first) || ends.count(s.second)) {
                return true;
            }
            starts.insert(s.first);
            ends.insert(s.second);
        }

        // Check for duplicate start or end positions in ladders.
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

// Function to validate snake and ladder positions.
//It verifies that snake should move down and not start at end or finish at start . At the same time ladder should move up and not start at start and finish at end
bool isValidSnakeOrLadder(const std::vector<std::pair<int, int>>& snakes, const std::vector<std::pair<int, int>>& ladders, int n) {
    for (const auto& snake : snakes) {
        if (snake.first <= snake.second || snake.first == n * n || snake.second == 1) {
            return false;  
        }
    }
    for (const auto& ladder : ladders) {
        if (ladder.first >= ladder.second || ladder.first == 1 || ladder.second == n * n) {
            return false;          }
    }
    return true;
}

// Function to ensure the number of snakes and ladders is reasonable based on the board size.
bool isReasonableNumber(const std::vector<std::pair<int, int>>& snakes, const std::vector<std::pair<int, int>>& ladders, int n) {
    int total = snakes.size() + ladders.size();
    return total <= n * n / 4;  
}

int main() {
    int n;
    std::cout << "Enter the size of the board (n x n): ";
    if (!(std::cin >> n) || n <= 0) {
        std::cout << "Invalid board size. Please enter a positive integer." << std::endl;
        return 1; 
    }

    Graph g(n); 

    std::vector<std::pair<int, int>> snakes;
    std::vector<std::pair<int, int>> ladders;

    // Input snake positions.
    std::cout << "Enter snake positions (start end), -1 -1 to finish:" << std::endl;
    while (true) {
        int x, y;
        if (!(std::cin >> x >> y)) {
            std::cout << "Invalid input. Please enter integers." << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        if (x == -1 || y == -1) break;
        if (x < 1 || x > n * n || y < 1 || y > n * n) {
            std::cout << "Invalid position. Must be between 1 and " << n * n << std::endl;
            continue;
        }
        snakes.push_back(std::make_pair(x, y)); 
    }

    // Input ladder positions.
    std::cout << "Enter ladder positions (start end), -1 -1 to finish:" << std::endl;
    while (true) {
        int x, y;
        if (!(std::cin >> x >> y)) {
            std::cout << "Invalid input. Please enter integers." << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        if (x == -1 || y == -1) break;
        if (x < 1 || x > n * n || y < 1 || y > n * n) {
            std::cout << "Invalid position. Must be between 1 and " << n * n << std::endl;
            continue;
        }
        ladders.push_back(std::make_pair(x, y)); 
    }

    // Add ladder edges to the graph.
    for (auto ladder : ladders) {
        g.addEdge(ladder.first - 1, ladder.second - 1);
    }

    // Add snake edges to the graph.
    for (auto snake : snakes) {
        g.addEdge(snake.first - 1, snake.second - 1);
    }

    // Add standard edges representing normal moves on the board.
    for (int i = 0; i < n * n - 1; i++) {
        for (int j = 1; j <= 6; j++) {
            if (i + j < n * n) {
                g.addEdge(i, i + j);
            }
        }
    }

    // Check if the board setup is valid.
    if (!isValidSnakeOrLadder(snakes, ladders, n)) {
        std::cout << "Invalid snake or ladder placement" << std::endl;
    } else if (!isReasonableNumber(snakes, ladders, n)) {
        std::cout << "Too many snakes and ladders for the board size" << std::endl;
    } else if (!g.isWinPath()) {
        std::cout << "No valid path to go to the end" << std::endl;
    } else if (g.hasDuplicatePositions(snakes, ladders)) {
        std::cout << "Duplicate positions are there, not a valid board" << std::endl;
    } else if (g.isCycle(0)) {
        std::cout << "Not a valid board due to cycles" << std::endl;
    } else {
        std::cout << "Valid board" << std::endl; 
    }

    return 0;
}
