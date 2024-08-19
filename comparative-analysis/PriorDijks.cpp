#include <iostream>
#include <queue>
#include <utility>
#include <vector>
#include <map>
#include <list>
#include <climits>

//int main() {
//    int arr[5] = {9, 2, 31, 21, 1};
//    std::vector<int> vec(arr, arr + 5);
//    
//    std::priority_queue<int, std::vector<int>, std::greater<int> > pr(vec.begin(), vec.end());
//
//    while (!pr.empty()) {
//        std::cout << pr.top() << " ";
//        pr.pop();
//    }
//    std::cout << std::endl;
//}
//

class Graph {
 
public:
  std::map<int, std::list<std::pair<int,int> > > adjacencyList;

public: 
  
  void add_edge(int u , int v , int weight) {
    adjacencyList[u].push_back(std::make_pair(v,weight));
    adjacencyList[v].push_back(std::make_pair(u,weight));
  }

  void print(){
    for(auto i : adjacencyList){
      std::cout << i.first << "->";
      for(auto j : i.second) {
        std::cout << j.first << " " << j.second << " " ;
      }
      std::cout << std::endl ;
    }
  }

  void shortest_path(int src){
    std::priority_queue<std::pair<int,int>, std::vector<std::pair<int,int> >, std::greater<std::pair<int,int> > > minPrioriQueue;

    std::map<int,int> dist;

    for(auto i : this->adjacencyList){
      dist[i.first] = INT_MAX;
    }

    minPrioriQueue.push(std::make_pair(0,src));
    dist[src] = 0 ;

    while(!minPrioriQueue.empty()){
      int u = minPrioriQueue.top().second;
      minPrioriQueue.pop();

      for(auto i : adjacencyList[u]){
        int v = i.first;
        int weight = i.second;

        if(dist[v] > dist[u] + weight){
          dist[v] = dist[u] + weight ;
          minPrioriQueue.push(std::make_pair(dist[v],v));
        }
      }
    }

    std::cout << "Vertex distance from the source" << std::endl;
    for(auto i : dist){
      std::cout << i.first << "\t" << i.second << std::endl;
    }

  } 

};

int main() 
{
  Graph g;

  g.add_edge(1,0,4);
  g.add_edge(2,0,8);
  g.add_edge(1,2,2);
  g.add_edge(1,3,6);
  g.add_edge(2,3,3);
  g.print();
  std::cout << g.adjacencyList.size() << std::endl ;
  // g.adjaceny.list() will give us the number of nodes or the vertices that we need.
  
  g.shortest_path(1);

  return 0;
}

/*
*
*first i will make the graph and then after i make the graph
  what i will b doing is that i wil be adding in the vertices from the linkedlist to the priority queue 
*
*/
