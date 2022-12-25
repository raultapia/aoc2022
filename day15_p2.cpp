#include <fstream>
#include <iostream>
#include <set>
#include <vector>

struct Interval{
  int min;
  int max;
  Interval(const int min, const int max) : min{min}, max{max} {}
  size_t sizeBetween(int a, int b) const{
    return (max > b ? b : max) - (min < a ? a : min) + 1;
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
  size_t sizeBetween(int min, int max) const{
    size_t ret = 0;
    for(const Interval& v : vec) ret += v.sizeBetween(min,max);
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
  const int min = 0;
  const int max = 4000000;
  std::ifstream file("input15.txt");
  std::pair<int,int> s;
  std::pair<int,int> b;
  std::vector<std::pair<int,int>> sensor;
  std::vector<std::pair<int,int>> beacon;
  unsigned long solution = 0;

  while(file.peek() != EOF){
    file.ignore(12); file >> s.first; file.ignore(4); file >> s.second; sensor.push_back(s);
    file.ignore(25); file >> b.first; file.ignore(4); file >> b.second; beacon.push_back(b);
    file.ignore(1);
  }

  IntervalVector intervals;
  for(unsigned long y = min; y <= max; y++){
    intervals.vec.clear();
    for(size_t k = 0; k < sensor.size(); k++){
      int d = distance(beacon[k], sensor[k]) - abs(y - sensor[k].second);
      if(d > 0) intervals.insert(Interval(sensor[k].first-d, sensor[k].first+d));
    }
    if(intervals.sizeBetween(min,max) < max-min+1) solution = y + 4000000UL*(unsigned long)(std::min(intervals.vec[0].max, intervals.vec[1].max)+1);
  }

  std::cout << "Solution = " << solution << std::endl;
  return 0;
}
