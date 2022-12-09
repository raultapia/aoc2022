#include <cmath>
#include <fstream>
#include <iostream>
#include <set>

inline double distance(const std::pair<int,int> a, const std::pair<int,int> b){
  return sqrt(pow(a.first - b.first, 2) + pow(a.second - b.second, 2));
}

inline int sign(const int x){
  return (x > 0) - (x < 0);
}

int main(int argc, char const *argv[]) {
  std::ifstream file("input09.txt");
  char move; int n;
  std::pair<int,int> head(0,0);
  std::pair<int,int> tail(0,0);
  std::set<std::pair<int,int>> visited({{0,0}});

  while(file >> move >> n){
    while(n--){
      switch(move) {
        case 'D': head.second--; break;
        case 'L': head.first--;  break;
        case 'R': head.first++;  break;
        case 'U': head.second++;
      }
      if(distance(head,tail) >= 2){
        tail.first += sign(head.first - tail.first);
        tail.second += sign(head.second - tail.second);
        visited.insert(tail);
      }
    }
  }

  std::cout << "Solution = " << visited.size() << std::endl;
  return 0;
}
