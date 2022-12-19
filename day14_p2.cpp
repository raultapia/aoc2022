#include <fstream>
#include <iostream>
#include <set>
#include <unordered_map>

inline int sign(const int x){
  return (x > 0) - (x < 0);
}

struct Sand : public std::pair<int,int>{
  const std::pair<int,int> origin{500,0};
  std::unordered_map<char,std::pair<int,int>> neighbour;
  Sand(){ reset(); }
  void reset(void){
    first = origin.first;
    second = origin.second;
    updateNeighbour();
  }
  void updateNeighbour(void){
    neighbour['D'] = std::pair<int,int>(first,second+1);
    neighbour['L'] = std::pair<int,int>(first-1,second+1);
    neighbour['R'] = std::pair<int,int>(first+1,second+1);
  }
  std::pair<int,int> get(char x){
    return neighbour[x];
  }
  void go(char x){
    first = neighbour[x].first;
    second = neighbour[x].second;
    updateNeighbour();
  }
};

struct Scan{
  Sand s;
  std::set<std::pair<int,int>> rock;
  unsigned int initNumber = 0;
  unsigned int maxHeight = 0;
  void simulate(void){
    const std::pair<int,int> origin{500,0};
    while(!rock.count(origin)){
      do{
        if( !rock.count(s.get('D')) ){ s.go('D'); continue; }
        if( !rock.count(s.get('L')) ){ s.go('L'); continue; }
        if( !rock.count(s.get('R')) ){ s.go('R'); continue; }
        rock.insert(s); s.reset();
      }while((unsigned int)s.second < maxHeight+1 && !rock.count(origin));
      rock.insert(s); s.reset();
    }
  }
};

int main(int argc, char const *argv[]) {
  std::ifstream file("input14.txt");
  std::string line;
  std::pair<int,int> p0, p1;
  Scan simulator;

  while(file.peek() != EOF){
    file >> p0.first; file.ignore(1); file >> p0.second;
    while(file.peek() != '\n'){
      file.ignore(4); file >> p1.first; file.ignore(1); file >> p1.second;
      simulator.rock.insert(p0);
      while(p0 != p1){
        p0.first += sign(p1.first - p0.first);
        p0.second += sign(p1.second - p0.second);
        simulator.rock.insert(p0);
      }
      if((unsigned int)p0.second > simulator.maxHeight) simulator.maxHeight = p0.second;
    }
    file.ignore(1);
  }
  simulator.initNumber = simulator.rock.size();
  simulator.simulate();

  std::cout << "Solution = " << simulator.rock.size() - simulator.initNumber << std::endl;
  return 0;
}
