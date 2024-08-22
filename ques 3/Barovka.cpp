#include<iostream>
#include<list>
#include<map>
#include<algorithm>
#include<climits>
#include<stdlib.h>
#include<utility>

class Graph{
public:
  std::map<int, std::list<std::pair<int, int> > > adjacencyList;
  std::vector<std::vector <int> >  edgeList;

  void add_edge(int u , int v, int weight){
    this->adjacencyList[u].push_back(std::make_pair(v,weight));
    this->adjacencyList[v].push_back(std::make_pair(u, weight));
  }

  void print(){
    for(auto i : this->adjacencyList){
      std::cout << i.first << " -> " << " ";
      for(auto j : i.second){
         std::cout << "( " << j.first << ", " << j.second << " )" << " ";
      }
      std::cout << std::endl;
    }
  }

  int find_vertex(int u , std::vector<int> &parent){
    if(parent[u] == u){
      return u ;
    }
    parent[u] = find_vertex(parent[u], parent);
    return parent[u];
  }

  void union_vertices(int u , int v, std::vector<int> &parent, std::vector<int> &rank){
    int rootU = find_vertex(u, parent);
    int rootV = find_vertex(v, parent);

    if(rootU != rootV){
      if(rank[rootU] < rank[rootV]){
        parent[rootU] = rootV;
      } else if(rank[rootV] < rank[rootU]){
        parent[rootV] = rootU;
      }else{
        parent[rootV] = rootU;
        rank[rootU] += 1;
      }
    }
  }

  void boruvka(){
    int verticeCount = this->adjacencyList.size();
    std::vector<int> parent(verticeCount);
    std::vector<int> rank(verticeCount, 0);
    std::vector<int> min_weight_edge(verticeCount, -1);
    int mstWeight = 0;

    for(int i = 0; i < verticeCount ; i++){
      parent[i] = i;
    }

    int componentCount = verticeCount;
    while(componentCount > 1){

      for(int i = 0 ; i < min_weight_edge.size() ; i++){
        min_weight_edge[i] = -1;
      }

