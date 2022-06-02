#include <iostream>
#include <unordered_map>
#include <iterator>
#include <cstring>
#include <fstream>
#include <unordered_set>
#include <string>
#include <sstream>
#include <queue>
#include <array>
#include <vector>
#include <queue>
#include <cassert>
#include <stack>
#include <algorithm>
#include <limits>
using namespace std;

struct connection{
  int city = 0;
  int weight = 0;
  bool isFlight = false; //can have roads of value 0 possibly
};

vector<vector<int>> cities;
vector<vector<connection>> connections;

struct city{
  vector<connection> connections;
};


int main() {
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);


  /*
  //tester code, comment out on Kattis
  ifstream cin("input.txt");
  ifstream textFile;
  textFile.open("input.txt");
  if(textFile.fail()){
    cout << "File Open Failed";
    return 0;
  }*/





  
  int n; // num cities
  int m; // num roads
  int f; // num flights
  int start; // starting city
  int finish; // ending city
  cin >> n >> m >> f >> start >> finish;

  //connection default = {.city = 0, .weight = 0};
  //vector<vector<connection>> graph(n, default);


  vector<city> graph(n + 1);

  
  int city1;
  int city2;
  int cost;
  //roads, set bool to false
  for(int i = 0; i < m; i++){
    cin >> city1 >> city2 >> cost;
    //cout << cost;
    connection temp = {.city = city2, .weight = cost, .isFlight = false};
    graph[city1].connections.push_back(temp);
    connection temp2 = {.city = city1, .weight = cost, .isFlight = false};
    graph[city2].connections.push_back(temp2);
  }
  //flights, set bool to true
  for(int i = 0; i < f; i++){
    cin >> city1 >> city2;
    connection temp = {.city = city2, .weight = 0, .isFlight = true};
    graph[city1].connections.push_back(temp);
    //connection temp2 = {.city = city1, .weight = 0, .isFlight = true};
    //graph[city2].connections.push_back(temp2);
  }

  /*

  for(int i = 0; i < graph.size(); i++){
    for(int j = 0; j < graph[i].connections.size(); j++){
      cout << i << " ";
      cout << graph[i].connections[j].city << " ";
      cout << graph[i].connections[j].weight << endl;
    }
  }

  */

  priority_queue<pair<int, int>> cityQueue;
  //first value is distance, second value is node
  //vector<int> cityDistance;
  //cityDistance[start] = 0;
  cityQueue.push(make_pair(0,start));
  //bool usedFlight = false;
  //unordered_map<int, bool> visited;
  
  vector<long long> destCost(n);
  vector<long long> flightCost(n);
  for(int i = 0; i < n; i++){
    destCost[i] = 100000000000;
    flightCost[i] = 10000000000;
    //destCost[i] = 1000000000;
    //flightCost[i] = 1000000000;
  }

  destCost[start] = 0;

  //graph[edge.city].destCost = destCost[graph[edge.city]]
  
  

  while(cityQueue.empty() == false){
    int currentCity = cityQueue.top().second;
    //visited[currentCity] = true;
    //destCost[currentCity] = cityQueue.top().second;
    cityQueue.pop();

    //check all edges
    for(int i = 0; i < graph[currentCity].connections.size(); i++){
      connection edge = graph[currentCity].connections[i];


      if(edge.isFlight == false){
        if(destCost[edge.city] > destCost[currentCity] + edge.weight){
          destCost[edge.city] = destCost[currentCity] + edge.weight;
          //cout << "1 " << destCost[edge.city] << endl;
          //if(visited.count(edge.city) == 0){
            cityQueue.push(make_pair((-1)*edge.weight, edge.city));
          //}
        }

        if(flightCost[edge.city] > flightCost[currentCity] + edge.weight){
          flightCost[edge.city] = flightCost[currentCity] + edge.weight;
          //cout << "2 " << flightCost[edge.city] << endl;
          //if(visited.count(edge.city) == 0){
            cityQueue.push(make_pair((-1)*edge.weight, edge.city));
          //}
        }

  
        
        
      }

      //this part still isn't right
      /*
      if(edge.isFlight == true){
        cout << "HERE";
      }
      */
      if(edge.isFlight == true){
        //cout << "HERE" << flightCost[edge.city] << " " << destCost[currentCity] << " + " << edge.weight << endl;
        if(flightCost[edge.city] > destCost[currentCity]){
          //cout << "HERE";
          flightCost[edge.city] = destCost[currentCity];
          //cout << "3 " << flightCost[edge.city] << endl;
          //cout << "edge.city: " << edge.city << endl;
          //if(visited.count(edge.city) == 0){
            cityQueue.push(make_pair(0, edge.city));
          //}
        }
      }
      
    }


    
  }


if(flightCost[finish] < 0){
  cout << destCost[finish];
}
  
if(destCost[finish] <= flightCost[finish]){
  cout << destCost[finish];
    }
else{
  cout << flightCost[finish];
}

  //cout << endl;
  
  //cout << destCost[finish] << endl;

  //cout << flightCost[finish] << endl;
  
  
  
}