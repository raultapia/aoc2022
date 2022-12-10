#include <array>
#include <fstream>
#include <iostream>
#define ROWS 6
#define COLS 40

int main(int argc, char const *argv[]) {
  std::ifstream file("input10.txt");
  std::string cmd;
  long x = 1, v, k = 0;
  std::array<char,ROWS*COLS> screen;

  while(file >> cmd){
    screen[k++] = (abs(k%COLS-x) < 2) ? '#':' ';
    if(cmd[0] == 'n') continue;
    screen[k++] = (abs(k%COLS-x) < 2) ? '#':' ';
    file >> v; x += v;
  }

  for(size_t k = 0; k < ROWS*COLS; k++){
    std::cout << screen[k];
    if(!((k+1)%COLS)) std::cout << std::endl;
  }
  return 0;
}
