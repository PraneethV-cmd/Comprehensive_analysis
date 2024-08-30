#include<iostream>
#include<utility>
#include<list>
#include<map>
#include<algorithm>
#include<vector>

class Graph {
public:
  // Data members to store the adjacency list and the number of nodes in the graph
  std::map<int, std::list<std::pair<int, int>>> adjacencyList;
  int nodeCount;

  // Constructor to initialize the graph with a given number of nodes
  Graph(int noOfNodes) : nodeCount(noOfNodes) {}

  // Function to add an undirected edge between nodes 'u' and 'v' with a given weight
  void add_edge(int u, int v, int weight) {
    this->adjacencyList[u].push_back(std::make_pair(v, weight)); // Add edge from u to v
    this->adjacencyList[v].push_back(std::make_pair(u, weight)); // Add edge from v to u (undirected graph)
  }

  // Function to print the adjacency list representation of the graph
  void print() {
    for (auto i : this->adjacencyList) { // Iterate through each node in the graph
      std::cout << i.first << " -> "; // Print the node
      for (auto j : i.second) { // Iterate through the adjacent nodes
        std::cout << j.first << " <-> " << j.second << " "; // Print the adjacent node and edge weight
      }
      std::cout << std::endl; // New line for the next node
    }
  }

  // Function to find the root of the set containing 'u' using path compression
  int find_vertex(int u, std::map<int, int>& parent) {
    if (parent[u] != u) { // If 'u' is not the root of its set
      parent[u] = find_vertex(parent[u], parent); // Recursively find the root and apply path compression
    }
    return parent[u]; // Return the root of the set containing 'u'
  }

  // Function to perform the union of two sets containing nodes 'u' and 'v' using union by rank
  void union_vertices(int u, int v, std::map<int, int>& parent, std::map<int, int>& rank) {
    int root_u = find_vertex(u, parent); // Find the root of the set containing 'u'
    int root_v = find_vertex(v, parent); // Find the root of the set containing 'v'

    if (root_u != root_v) { // If 'u' and 'v' are in different sets, merge them
      if (rank[root_u] > rank[root_v]) {
        parent[root_v] = root_u; // Attach the set containing 'v' to the set containing 'u'
      } else if (rank[root_u] < rank[root_v]) {
        parent[root_u] = root_v; // Attach the set containing 'u' to the set containing 'v'
      } else {
        parent[root_v] = root_u; // If ranks are equal, arbitrarily choose one and increment its rank
        rank[root_u] += 1;
      }
    }
  }

  // Function to implement Borůvka's algorithm for finding the Minimum Spanning Tree (MST) of the graph
  void barovka() {
    std::vector<int> min_edge(nodeCount, -1); // Vector to store the minimum edge for each component
    std::map<int, int> parent, rank; // Maps for the parent and rank of each node

    for (int i = 0; i < nodeCount; i++) {
      parent[i] = i; // Initially, each node is its own parent (disjoint set)
      rank[i] = 0;   // Initialize rank of each node to 0
    }

    int componentCount = nodeCount; // Number of components initially equals the number of nodes
    int mstWeight = 0; // Variable to store the total weight of the MST

    // Continue the algorithm until there is only one component (the MST)
    while (componentCount > 1) {
      std::fill(min_edge.begin(), min_edge.end(), -1); // Reset the minimum edge array

      // Iterate through each edge in the graph to find the minimum outgoing edge for each component
      for (auto i : adjacencyList) {
        for (auto j : i.second) {
          int root_u = find_vertex(i.first, parent); // Find the root of the set containing 'i.first'
          int root_v = find_vertex(j.first, parent); // Find the root of the set containing 'j.first'

          if (root_u != root_v) { // If the nodes are in different components
            // Update the minimum edge for the component containing 'root_u'
            if (min_edge[root_u] == -1 || min_edge[root_u] > j.second) {
              min_edge[root_u] = j.second;
            }
            // Update the minimum edge for the component containing 'root_v'
            if (min_edge[root_v] == -1 || min_edge[root_v] > j.second) {
              min_edge[root_v] = j.second;
            }
          }
        }
      }

      // Iterate over all nodes to add the selected minimum edges to the MST
      for (int j = 0; j < nodeCount; j++) {
        if (min_edge[j] != -1) { // If a minimum edge was found for this component
          for (auto i : this->adjacencyList[j]) {
            if (i.second == min_edge[j]) { // If this edge is the selected minimum edge
              int root_u = find_vertex(j, parent); // Find the root of the set containing 'j'
              int root_v = find_vertex(i.first, parent); // Find the root of the set containing 'i.first'

              if (root_u != root_v) { // If they are in different components
                mstWeight += i.second; // Add the edge weight to the MST total weight
                union_vertices(j, i.first, parent, rank); // Union the two components
                std::cout << "Added edge ( " << j << " <-> " << i.first << " ) \n";
                std::cout << "Added weight: " << i.second << "\n";
                componentCount -= 1; // Decrease the number of components
              }
            }
          }
        }
      }
    }

    std::cout << "Total weight of the minimum spanning tree is: " << mstWeight << std::endl; // Print the MST weight
  }
};

int main() {
    int V, E;
    std::cout << "Enter the number of vertices: ";
    std::cin >> V;

    Graph g(V); // Create a graph with the specified number of vertices

    std::cout << "Enter the number of edges: ";
    std::cin >> E;

    std::cout << "Enter each edge with its weight (format: u v weight):\n";
    for (int i = 0; i < E; i++) {
        int u, v, weight;
        std::cin >> u >> v >> weight;
        g.add_edge(u, v, weight); // Add each edge to the graph
    }

    std::cout << "Graph edges and weights:\n";
    g.print(); // Print the graph

    std::cout << "Starting Borůvka's algorithm:\n";
    g.barovka(); // Execute Borůvka's algorithm

    return 0;
}
