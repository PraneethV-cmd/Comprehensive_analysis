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

        }
      }
    }
  }

};

int main()
{
  int n = 10;
  Graph g(n);
}
