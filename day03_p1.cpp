#include <algorithm>
#include <fstream>
#include <iostream>

int main(int argc, char const *argv[]) {
  std::ifstream file("input03.txt");
  std::string s;
  unsigned long priority = 0;

  while(file >> s){
    std::string s1 = s.substr(0,s.length()/2);
    std::string s2 = s.substr(s.length()/2, s.length());

    std::sort(s1.begin(), s1.end());
    std::sort(s2.begin(), s2.end());
    std::set_intersection(s1.begin(), s1.end(), s2.begin(), s2.end(), s1.begin());
    priority += ((s1[0] > '^') ? s1[0]-'`' : s1[0]-'&');
  }

  std::cout << "Total priority = " << priority << std::endl;
  return 0;
}
