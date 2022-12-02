#include <algorithm>
#include <array>
#include <fstream>
#include <iostream>
#include <unordered_map>

inline int get_index(std::array<char,3> vec, char value){
    return (std::find(vec.begin(), vec.end(), value) - vec.begin());
}

int main(int argc, char const *argv[]) {
  std::ifstream file("input02.txt");
  std::unordered_map<char,std::array<char,3>> round = {{'X',{'B','C','A'}}, {'Y',{'A','B','C'}}, {'Z',{'C','A','B'}}};
  char result, oponent;
  unsigned long score = 0;

  while(file >> oponent >> result) score += 1+get_index(round[result],oponent) + 3*(result-'X');
  std::cout << "Total score = " << score << std::endl;

  return 0;
}
