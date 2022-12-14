#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>

int compare_packets(std::pair<std::string,std::string> packet){
  std::pair<std::string::iterator,std::string::iterator> it;
  std::pair<std::string,std::string> subpacket;
  packet.first = packet.first.substr(1,packet.first.size()-2);
  packet.second = packet.second.substr(1,packet.second.size()-2);

  for(it.first = packet.first.begin(), it.second = packet.second.begin(); it.first < packet.first.end() && it.second < packet.second.end(); it.first++, it.second++){
    if(*it.first != '[' && *it.second != '[' && *it.first != *it.second) return ((*it.first < *it.second) ? +1 : -1);
    if(*it.first == '[' || *it.second == '['){
      if(*it.first == '['){
        int cnt = 1, size1 = 0;
        while(cnt > 0){
          if(*(it.first+(++size1)) == '[') cnt++;
          if(*(it.first+size1) == ']') cnt--;
        }
        subpacket.first = packet.first.substr(it.first-packet.first.begin(),size1+1);
        it.first += size1;
      }
      else subpacket.first = std::string("[") + *it.first + std::string("]");

      if(*it.second == '['){
        int cnt = 1, size2 = 0;
        while(cnt > 0){
          if(*(it.second+(++size2)) == '[') cnt++;
          if(*(it.second+size2) == ']') cnt--;
        }
        subpacket.second = packet.second.substr(it.second-packet.second.begin(),size2+1);
        it.second += size2;
      }
      else subpacket.second = std::string("[") + *it.second + std::string("]");

      int ret = compare_packets(subpacket); if(ret) return ret;
    }
  }
  return ((+1)*(it.first == packet.first.end()) + (-1)*(it.second == packet.second.end()));
}

int main(int argc, char const *argv[]) {
  std::ifstream file("input13.txt");
  std::pair<std::string,std::string> line; size_t i;
  std::vector<std::string> packets;
  const std::pair<std::string,std::string> dividers({"[[2]]","[[6]]"});

  for(unsigned int k = 1; !file.eof(); k++){
    file >> line.first >> line.second;
    while((i = line.first.find("10")) != std::string::npos) line.first.replace(i,2,":");
    while((i = line.second.find("10")) != std::string::npos) line.second.replace(i,2,":");
    packets.push_back(line.first);
    packets.push_back(line.second);
    file.ignore(2);
  }
  packets.push_back(dividers.first);
  packets.push_back(dividers.second);

  bool change = true;
  while(change){
    change = false;
    for(std::vector<std::string>::iterator it = packets.begin(); it < packets.end()-1; it++){
      if(compare_packets({*it, *(it+1)}) < 0){
        std::swap(*it, *(it+1));
        change = true;
      }
    }
  }

  std::vector<std::string>::iterator a = std::find(packets.begin(), packets.end(), dividers.first);
  std::vector<std::string>::iterator b = std::find(packets.begin(), packets.end(), dividers.second);
  std::cout << "Solution = " << (a-packets.begin()+1) * (b-packets.begin()+1) << std::endl;
  return 0;
}
