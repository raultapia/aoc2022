#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <queue>
#include <vector>
#define ROUNDS 10000

struct Monkey{
  std::queue<uint64_t> items;
  std::function <void (unsigned long&)> operation;
  uint64_t test;
  std::pair<uint64_t,uint64_t> next;
  uint64_t times = 0;
  uint64_t inspect(void){
    times++;
    operation(items.front());
    return !(items.front()%test) ? next.first : next.second;
  }
};

int main(int argc, char const *argv[]) {
  std::ifstream file("input11.txt");
  std::string line;
  std::vector<Monkey> monkeys;
  uint64_t cnt = 1;

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
    file.seekg(22, std::ios_base::cur); file >> m.test; cnt *= m.test;
    file.seekg(30, std::ios_base::cur); file >> m.next.first;
    file.seekg(31, std::ios_base::cur); file >> m.next.second;
    file.seekg(2, std::ios_base::cur);
    monkeys.push_back(m);
  }

  for(uint64_t round = 1; round <= ROUNDS; round++){
    for(Monkey& m : monkeys){
      while(!m.items.empty()){
        monkeys[m.inspect()].items.push(m.items.front()%cnt);
        m.items.pop();
      }
    }
  }

  uint64_t solution = 1;
  std::vector<Monkey>::iterator p;
  p = std::max_element(monkeys.begin(), monkeys.end(), [](const Monkey& a, const Monkey& b){return a.times<b.times;});
  solution *= p->times;
  p->times = 0;
  p = std::max_element(monkeys.begin(), monkeys.end(), [](const Monkey& a, const Monkey& b){return a.times<b.times;});
  solution *= p->times;
  std::cout << "Solution = " << solution << std::endl;
  return 0;
}
