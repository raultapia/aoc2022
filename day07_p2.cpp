#include <fstream>
#include <iostream>
#include <vector>
#define TOTAL_SPACE 70000000
#define REQUIRED_SPACE 30000000

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
    void selectToRemove(Directory** best, unsigned int space){
        if(size > space && size < (*best)->size) *best = this;
        for(Directory& s : subdirectories) s.selectToRemove(best, space);
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
    ptr = &root;

    root.selectToRemove(&ptr, REQUIRED_SPACE - (TOTAL_SPACE - root.size));
    std::cout << "Remove [" << ptr->name << "] of size " << ptr->size << std::endl;
    return 0;
}
