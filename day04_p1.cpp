#include <fstream>
#include <iostream>

int main(int argc, char const *argv[]) {
  std::ifstream file("input04.txt");
  unsigned long overlap = 0;
  std::string line;
  std::pair<int,int> a,b;

  while(file >> line){
    sscanf(line.c_str(), "%d-%d,%d-%d", &a.first, &a.second, &b.first, &b.second);
    if((a.first <= b.first && a.second >= b.second) || (b.first <= a.first && b.second >= a.second)) overlap++;
  }

  std::cout << "Total = " << overlap << std::endl;
  return 0;
}
