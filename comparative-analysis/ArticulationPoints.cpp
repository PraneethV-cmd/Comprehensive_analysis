#include<iostream>
#include<list>
#include<utility>
#include<vector>
#include<map>
#include<climits>
#include<algorithm>

class Graph{

public:
  std::map<int , std::list<int> > adjacencyList;
  int time = 0;

  void add_edge(int u, int v){
    adjacencyList[u].push_back(v);
    adjacencyList[v].push_back(u);
  }

  void print(){
    for(auto i : adjacencyList){
      std::cout << i.first << " -> ";
      for(auto j : adjacencyList){
        std::cout << "vertex: " << j.first << " ";
      }
      std::cout << std::endl;
    }
  }

  void findArticulationPointsHelper(int u , std::vector<bool> visited,
                              std::vector<int> discoveryTime, std::vector<int> lowTime, std::vector<int> parent, std::vector<bool> articulationPoints){
    visited[u] = true;
    time += 1;
    discoveryTime[u] = time;
    lowTime[u] = time;
    int children = 0;

    for(int v : this->adjacencyList[u]){
      if(!visited[v]){
        children += 1;
        parent[v] = u;
        findArticulationPoints(v, visited, discoveryTime, lowTime, parent, articulationPoints);
        lowTime[u] = std::min(lowTime[u], lowTime[v]);

        if(parent[u] == -1 && children > 1){
          articulationPoints[u] = true;
        }

        if(parent[u] != -1 && lowTime[v] >= discoveryTime[u]){
          articulationPoints[u] = true;
        } 
      }else if(v != parent[u]){
        lowTime[u] = std::min(lowTime[u], discoveryTime[v]);
      }
    }
  }

  void findArticulationPoints(){
    int adjSize = adjacencyList.size();
    std::vector<bool> visited(adjSize, false);
    std::vector<int> discoveryTime(adjSize, -1);
    std::vector<int> lowTime(adjSize, -1);
    std::vector<int> parent(adjSize, -1);
    std::vector<bool> articulationPoints(adjSize, false);

    for(auto i : adjacencyList){
      if (!visited[i.first]){
        findArticulationPointsHelper(i.first, visited, discoveryTime, lowTime, parent, articulationPoints);
      }
    }

    std::cout << "articulation points in the graph : " << std::endl;
    for(int i = 0 ; i < adjSize; i++){
      if(articulationPoints[i]){
        std::cout << i << " " ;
      }
    }
    std::cout << std::endl;
  }
};

int main()
{
  Graph g;
  g.add_edge(0,1);
  g.add_edge(1,2);
  g.add_edge(2,0);
  g.add_edge(1,3);
  g.add_edge(3,4);
  g.add_edge(4,5);
  g.add_edge(5,3);
  g.add_edge(5,6);
  g.add_edge(6,7);
  g.add_edge(7,8);
  g.add_edge(8,5);

  g.print();
  g.findArticulationPoints();

  return 0;
}
