#include <fstream>
#include <iostream>
#include <set>
#include <vector>

struct Interval{
  int min;
  int max;
  Interval(const int min, const int max) : min{min}, max{max} {}
  size_t size(void) const{
    return max - min + 1;
  }
  bool contains(const int x) const{
    return x >= min && x <= max;
  }
  bool overlaps(const Interval& interval) const{
    return contains(interval.min) || contains(interval.max) || interval.contains(min) || interval.contains(max);
  }
  void extend(const Interval& interval){
    if(interval.max > max) max = interval.max;
    if(interval.min < min) min = interval.min;
  }
};

struct IntervalVector{
  std::vector<Interval> vec;
  size_t size(void) const{
    size_t ret = 0;
    for(const Interval& v : vec) ret += v.size();
    return ret;
  }
  void insert(const Interval& x){
    for(size_t i = 0; i < vec.size(); i++){
      if(vec[i].overlaps(x)){
        vec[i].extend(x);
        update(i);
        return;
      }
    }
    vec.push_back(x);
  }
  void update(const size_t i){
    for(size_t j = 0; j < vec.size(); j++){
      if(i == j) continue;
      if(vec[j].overlaps(vec[i])){
        vec[j].extend(vec[i]);
        vec.erase(vec.begin()+i);
        if(j < i) update(j); else update(j-1);
        return;
      }
    }
  }
};

inline int distance(const std::pair<int,int>& a, const std::pair<int,int>& b){
  return abs(a.first - b.first) + abs(a.second - b.second);
}

int main(int argc, char const *argv[]) {
  const int y = 2000000;
  std::ifstream file("input15.txt");
  std::pair<int,int> sensor;
  std::pair<int,int> beacon;
  std::set<std::pair<int,int>> blacklist;

  IntervalVector intervals;
  while(file.peek() != EOF){
    file.ignore(12); file >> sensor.first; file.ignore(4); file >> sensor.second;
    file.ignore(25); file >> beacon.first; file.ignore(4); file >> beacon.second; file.ignore(1);
    int d = distance(beacon, sensor) - abs(y - sensor.second);
    if(d > 0) intervals.insert(Interval(sensor.first-d, sensor.first+d));
    if(beacon.second == y) blacklist.insert(beacon);
  }

  std::cout << "Solution = " << intervals.size() - blacklist.size() << std::endl;
  return 0;
}
