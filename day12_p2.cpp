#include <algorithm>
#include <climits>
#include <fstream>
#include <iostream>
#include <queue>
#include <vector>

struct Node{
  char elevation;
  unsigned int distance = UINT_MAX;
  Node(char e) : elevation{(e == 'S') ? 'a' : ((e == 'E') ? 'z' : e)} {}
};

struct Map{
  std::vector<std::pair<int,int>> start;
  std::pair<int,int> end;
  std::vector<std::vector<Node>> nodes;
  void addNodes(std::string s){
    std::vector<Node> x;
    for(const char c : s) x.push_back(Node(c));
    nodes.push_back(x);
  }
  std::pair<size_t,size_t> size(void) const{
    return std::pair<size_t,size_t>(nodes.size(), nodes[0].size());
  }
  Node& at(std::pair<int,int> p){
    return nodes[p.first][p.second];
  }
  Node& at(std::pair<int,int> p, std::pair<int,int> offset){
    return nodes[p.first+offset.first][p.second+offset.second];
  }
};

int main(int argc, char const *argv[]) {
  std::ifstream file("input12.txt");
  std::string line;
  Map map;

  for(int i = 0; file >> line; i++){
    if(line.find("S") != std::string::npos) map.start.push_back({i,line.find("S")});
    if(line.find("E") != std::string::npos) map.end = {i,line.find("E")};
    while(line.find("a") != std::string::npos){
      map.start.push_back({i,line.find("a")});
      line.replace(line.find("a"), 1, "S");
    }
    map.addNodes(line);
  }

  const int ROWS = map.size().first;
  const int COLS = map.size().second;
  std::queue<std::pair<int,int>> q;
  unsigned int solution = UINT_MAX;
  for(const std::pair<int,int>& start : map.start){
    q.push(start);
    map.at(start).distance = 0;

    while(!q.empty()){
      std::pair<int,int> p = q.front();
      q.pop();
      if(p.first > 0       && map.at(p,{-1,0}).elevation <= map.at(p).elevation + 1 && map.at(p,{-1,0}).distance > map.at(p).distance + 1) { map.at(p,{-1,0}).distance = map.at(p).distance + 1; q.push({p.first-1,p.second}); }
      if(p.first < ROWS-1  && map.at(p,{+1,0}).elevation <= map.at(p).elevation + 1 && map.at(p,{+1,0}).distance > map.at(p).distance + 1) { map.at(p,{+1,0}).distance = map.at(p).distance + 1; q.push({p.first+1,p.second}); }
      if(p.second > 0      && map.at(p,{0,-1}).elevation <= map.at(p).elevation + 1 && map.at(p,{0,-1}).distance > map.at(p).distance + 1) { map.at(p,{0,-1}).distance = map.at(p).distance + 1; q.push({p.first,p.second-1}); }
      if(p.second < COLS-1 && map.at(p,{0,+1}).elevation <= map.at(p).elevation + 1 && map.at(p,{0,+1}).distance > map.at(p).distance + 1) { map.at(p,{0,+1}).distance = map.at(p).distance + 1; q.push({p.first,p.second+1}); }
    }

    if(map.at(map.end).distance < solution) solution = map.at(map.end).distance;
  }

  std::cout << "Solution: " << solution << std::endl;
  return 0;
}
