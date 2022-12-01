#include <algorithm>
#include <fstream>
#include <iostream>
#include <numeric>
#include <stdlib.h>
#include <vector>
#define TOP 3

int main(int argc, char const *argv[]) {
  std::ifstream file("input01.txt");
  std::vector<std::pair<long,long>> solution(TOP);

  for(long i = 1, sum = 0; !file.eof(); i++, sum = 0){
    std::string line;
    while(1){
      std::getline(file,line);
      if(line.empty()) break;
      sum += std::stol(line);
    }
    if(sum > solution[0].first){
      solution[0].second = i;
      solution[0].first = sum;
      std::sort(solution.begin(), solution.end());
    }
  }

  for(size_t i = 0; i < solution.size(); i++) std::cout << "Elf " << solution[i].second << " is carrying " << solution[i].first << " calories" << std::endl;
  long total = 0; for(std::pair<long,long> p : solution) total += p.first;
  std::cout << "The top " << TOP << " is carrying " << total << " calories in total" << std::endl;
  return 0;
}
