#include <fstream>
#include <iostream>
#include <unordered_set>

int main(int argc, char const *argv[]) {
  const std::unordered_set<int> set({20, 60, 100, 140, 180, 220});
  std::ifstream file("input10.txt");
  std::string cmd;
  unsigned long cycle;
  long x = 1, v;
  int total = 0;

  while(file >> cmd){
    if(set.count(++cycle)) total += cycle*x;
    if(cmd[0] == 'n') continue;
    if(set.count(++cycle)) total += cycle*x;
    file >> v; x += v;
  }

  std::cout << "Solution = " << total << std::endl;
  return 0;
}
