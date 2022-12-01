#include <fstream>
#include <iostream>
#include <stdlib.h>

int main(int argc, char const *argv[]) {
  std::ifstream file("input01.txt");
  std::pair<long,long> solution;

  for(long i = 1, sum = 0; !file.eof(); i++, sum = 0){
    std::string line;
    while(1){
      std::getline(file,line);
      if(line.empty()) break;
      sum += std::stol(line);
    }
    if(sum > solution.first){
      solution.second = i;
      solution.first = sum;
    }
  }

  std::cout << "Elf " << solution.second << " is carrying " << solution.first << " calories" << std::endl;
  return 0;
}
