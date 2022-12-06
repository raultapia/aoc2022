#include <fstream>
#include <iostream>
#include <queue>
#include <unordered_set>
#define LENGTH 14

int main(int argc, char const *argv[]) {
    std::ifstream file("input06.txt");
    std::string buffer;
    std::queue<char> queue;
    std::unordered_set<char> set;
    unsigned long cnt = 0;

    file >> buffer;
    for(const char c : buffer){
      cnt++;
      queue.push(c);
      if(!set.insert(c).second){
        while(queue.front() != c){
          set.erase(queue.front());
          queue.pop();
        }
        queue.pop();
      }
      if(queue.size() == LENGTH) break;
    }

    std::cout << "Solution = " << cnt << std::endl;
    return 0;
}
