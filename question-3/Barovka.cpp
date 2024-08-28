#include<iostream>
#include<utility>
#include<list>
#include<map>
#include<algorithm>
#include<vector>

class Graph {
public:
  std::map<int, std::list<std::pair<int, int> > > adjacencyList;
  int nodeCount;

  Graph(int noOfNodes) : nodeCount(noOfNodes){}

  void add_edge(int u , int v, int weight){
    this->adjacencyList[u].push_back(std::make_pair(v,weight));
    this->adjacencyList[v].push_back(std::make_pair(u,weight));
  }

  void print(){
    for(auto i : this->adjacencyList){
      std::cout << i.first << "->" << " " ;
      for(auto j : i.second){
        std::cout << j.first << " <-> " << j.second << " ";
      }
      std::cout << std::endl;
    }
  }

  int find_vertex(int u , std::map<int, int> &parent){
    if(parent[u] != u){
      parent[u] = find_vertex(parent[u], parent); 
    }
    return parent[u];
  }

  void union_vertices(int u , int v, std::map<int, int> &parent, std::map<int, int> &rank){
    int root_u = find_vertex(u,parent);
    int root_v = find_vertex(v,parent);

    if(root_u != root_v){
      if(rank[root_u] > rank[root_v]){
        parent[root_v] = root_u;
      }else if(rank[root_u] < rank[root_v]){
        parent[root_u] = root_v;
      }else{
        parent[root_v] = root_u;
        rank[root_u] += 1;
      }
    }
  }

  void barovka(){
    std::vector<int> min_edge(nodeCount, -1);
    std::map<int, int> parent, rank;

    for(int i = 0; i < nodeCount ; i++){
      parent[i] = i;
      rank[i] = 0;
    }

    int componentCount = nodeCount;
    int mstWeight = 0;

    while(componentCount > 1){
      std::fill(min_edge.begin(), min_edge.end(), -1);

      for(auto i : adjacencyList){
        for(auto j : i.second){
          int root_u = find_vertex(i.first,parent);
          int root_v = find_vertex(j.first,parent);

          if(root_u != root_v){
            if(min_edge[root_u] == -1 || min_edge[root_u] > j.second){
              min_edge[root_u] = j.second;
            }
            if(min_edge[root_v] == -1 || min_edge[root_v] > j.second){
              min_edge[root_v] = j.second;
            }
          }
        }
      }

      for(int j = 0 ; j < nodeCount ; j++){
        if(min_edge[j] != -1){
          for(auto i : this->adjacencyList[j]){
            if (i.second == min_edge[j]){
              int root_u = find_vertex(j, parent);
              int root_v = find_vertex(i.first, parent);

              if(root_u != root_v){
                mstWeight += i.second;
                union_vertices(j, i.first, parent,rank);
                std::cout << "added edge ( " << j << " <-> " << i.first << " ) \n";
                std::cout << "added weight: " << i.second << "\n";
                componentCount -= 1;
              }
            }
          }
        }
      }
    }

    std::cout << "total weight of the minimum spanning tree is : " << mstWeight << std::endl;
  }
};

int main() {
    Graph g(9);

    g.add_edge(0, 1, 4);
    g.add_edge(0, 6, 7);
    g.add_edge(1, 6, 11);
    g.add_edge(1, 7, 20);
    g.add_edge(1, 2, 9);
    g.add_edge(2, 3, 6);
    g.add_edge(2, 4, 2);
    g.add_edge(3, 4, 10);
    g.add_edge(3, 5, 5);
    g.add_edge(4, 5, 15);
    g.add_edge(4, 7, 1);
    g.add_edge(4, 8, 5);
    g.add_edge(5, 8, 12);
    g.add_edge(6, 7, 1);
    g.add_edge(7, 8, 3);

    g.barovka();

    return 0;
}
