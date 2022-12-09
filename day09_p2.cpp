#include <array>
#include <cmath>
#include <fstream>
#include <iostream>
#include <set>
#define LENGTH (9+1)

inline double distance(const std::pair<int,int> a, const std::pair<int,int> b){
  return sqrt(pow(a.first - b.first, 2) + pow(a.second - b.second, 2));
}

inline int sign(const int x){
  return (x > 0) - (x < 0);
}

int main(int argc, char const *argv[]) {
  std::ifstream file("input09.txt");
  char move; int n;
  std::array<std::pair<int,int>,LENGTH> rope;
  std::set<std::pair<int,int>> visited({{0,0}});

  while(file >> move >> n){
    while(n--){
      switch(move) {
        case 'D': rope[0].second--; break;
        case 'L': rope[0].first--;  break;
        case 'R': rope[0].first++;  break;
        case 'U': rope[0].second++;
      }
      for(size_t i = 1; i < LENGTH; i++){
        if(distance(rope[i-1],rope[i]) >= 2){
          rope[i].first += sign(rope[i-1].first - rope[i].first);
          rope[i].second += sign(rope[i-1].second - rope[i].second);
          if(i == LENGTH-1) visited.insert(rope[i]);
        }
      }
    }
  }

  std::cout << "Solution = " << visited.size() << std::endl;
  return 0;
}
