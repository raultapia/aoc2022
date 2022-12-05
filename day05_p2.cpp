#include <fstream>
#include <iostream>
#include <stack>
#include <vector>

int main(int argc, char const *argv[]) {
    std::ifstream file("input05.txt");
    std::stack<std::string> lines;
    std::string line;
    unsigned int cnt, from, to;

    while(std::getline(file, line)) {
        if(line.empty()) break;
        lines.push(line);
    }

    const size_t n = (lines.top().end()[-2])-'0'; lines.pop();
    std::vector<std::stack<char> > stack(n);
    while(!lines.empty()) {
        for(size_t i = 0; i < n; i++) {
            char c = lines.top()[4*i+1];
            if(c > '@') stack[i].push(c);
        }
        lines.pop();
    }

    std::stack<char> aux;
    while(std::getline(file, line)) {
        sscanf(line.c_str(), "move %d from %d to %d", &cnt, &from, &to);
        for(unsigned int i = 0; i < cnt; i++) {
            aux.push(stack[from-1].top());
            stack[from-1].pop();
        }
        while(!aux.empty()) {
            stack[to-1].push(aux.top());
            aux.pop();
        }
    }

    std::cout << "Solution = "; for(std::stack<char> s : stack) std::cout << s.top(); std::cout << std::endl;
    return 0;
}
