#include <algorithm>
#include <fstream>
#include <iostream>
#define N 3

std::string recursive_intersection(std::vector<std::string> x){
  std::string s1 = x.back(); x.pop_back();
  std::string s2 = (x.size() == 1) ? x[0] : recursive_intersection(x);
  std::string::iterator end = std::set_intersection(s1.begin(), s1.end(), s2.begin(), s2.end(), s1.begin());
  return std::string(s1.begin(), end);
}

int main(int argc, char const *argv[]) {
  std::ifstream file("input03.txt");
  std::array<std::string,N> s;
  unsigned long priority = 0;

  while(true){
    for(std::string& e : s) file >> e;
    if(file.eof()) break;
    for(std::string& e : s) std::sort(e.begin(), e.end());
    char r = recursive_intersection({s.begin(),s.end()})[0];
    priority += ((r > '^') ? r-'`' : r-'&');
  }

  std::cout << "Total priority = " << priority << std::endl;
  return 0;
}
