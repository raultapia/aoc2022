#include <array>
#include <fstream>
#include <iostream>
#include <unordered_map>

int main(int argc, char const *argv[]) {
  std::ifstream file("input02.txt");
  std::unordered_map<char,std::array<char,2>> round = {{'X',{'C','A'}}, {'Y',{'A','B'}}, {'Z',{'B','C'}}};
  char me, oponent;
  unsigned long score = 0;

  while(file >> oponent >> me) score += (me-'W') + 6*(round[me][0]==oponent) + 3*(round[me][1]==oponent);
  std::cout << "Total score = " << score << std::endl;

  return 0;
}
