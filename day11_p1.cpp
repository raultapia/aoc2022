#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <queue>
#include <vector>
#define ROUNDS 20

struct Monkey{
  std::queue<unsigned long> items;
  std::function <void (unsigned long&)> operation;
  unsigned long test;
  std::pair<int,int> next;
  unsigned int times = 0;
  int inspect(void){
    times++;
    operation(items.front());
    items.front() /= 3;
    return !(items.front()%test) ? next.first : next.second;
  }
};

int main(int argc, char const *argv[]) {
  std::ifstream file("input11.txt");
  std::string line;
  std::vector<Monkey> monkeys;

  while(file.peek() != EOF){
    Monkey m; char c; int n;
    file.seekg(28, std::ios_base::cur);
    while(file >> n) {m.items.push(n); file.ignore();} file.clear();
    file.seekg(21, std::ios_base::cur);
    file >> c; file >> n; if(file.tellg() < 0) c = 0;
    switch(c) {
      case '+': m.operation = [n](unsigned long& x){x+=n;}; break;
      case '-': m.operation = [n](unsigned long& x){x-=n;}; break;
      case '*': m.operation = [n](unsigned long& x){x*=n;}; break;
      case '/': m.operation = [n](unsigned long& x){x/=n;}; break;
      default: m.operation = [](unsigned long& x){x*=x;}; file.clear(); file.seekg(3, std::ios_base::cur);
    }
    file.seekg(22, std::ios_base::cur); file >> m.test;
    file.seekg(30, std::ios_base::cur); file >> m.next.first;
    file.seekg(31, std::ios_base::cur); file >> m.next.second;
    file.seekg(2, std::ios_base::cur);
    monkeys.push_back(m);
  }

  for(int round = 1; round <= ROUNDS; round++){
    for(Monkey& m : monkeys){
      while(!m.items.empty()){
        monkeys[m.inspect()].items.push(m.items.front());
        m.items.pop();
      }
    }
  }

  int solution = 1;
  std::vector<Monkey>::iterator p;
  p = std::max_element(monkeys.begin(), monkeys.end(), [](const Monkey& a, const Monkey& b){return a.times<b.times;});
  solution *= p->times;
  p->times = 0;
  p = std::max_element(monkeys.begin(), monkeys.end(), [](const Monkey& a, const Monkey& b){return a.times<b.times;});
  solution *= p->times;
  std::cout << "Solution = " << solution << std::endl;
  return 0;
}
