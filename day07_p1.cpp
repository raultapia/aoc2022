#include <fstream>
#include <iostream>
#include <vector>
#define LIMIT 100000

struct Directory {
    Directory() : name{"/"}, parentDirectory{nullptr} {}
    Directory(std::string name, Directory* parent) : name{name}, parentDirectory{parent} {}
    void addSubdirectory(std::string name){
      subdirectories.push_back( Directory(name, this) );
    }
    void addFile(unsigned int s){
      size += s;
      if(parentDirectory != nullptr) parentDirectory->addFile(s);
    }
    Directory* goUp(void){
      return parentDirectory;
    }
    Directory* goDown(std::string dst){
        for(Directory& s : subdirectories) if(s.name == dst) return &s;
        return nullptr;
    }
    unsigned int sumIfSmall(unsigned int limit){
        unsigned int ret = (size <= limit) ? size : 0;
        for(Directory& s : subdirectories) ret += s.sumIfSmall(limit);
        return ret;
    }
    std::string name;
    unsigned int size = 0;
    std::vector<Directory> subdirectories;
    Directory* parentDirectory;
};

int main(int argc, char const *argv[]) {
    std::ifstream file("input07.txt");
    std::string line;
    Directory root;
    Directory *ptr = &root;

    std::getline(file,line);
    std::getline(file,line);

    while(!file.eof()){
        if(line == "$ ls"){
          while(std::getline(file,line) && line[0] != '$'){
              if(line[0] == 'd') ptr->addSubdirectory( line.substr(4) );
              else ptr->addFile( std::stoi(line.substr(0,line.find(" "))) );
          }
          continue;
        }
        else if(line == "$ cd ..") ptr = ptr->goUp();
        else ptr = ptr->goDown(line.substr(5));
        std::getline(file,line);
    }

    std::cout << "Solution = " << root.sumIfSmall(LIMIT) << std::endl;
    return 0;
}
