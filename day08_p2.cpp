#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>

int main(int argc, char const *argv[]) {
    std::ifstream file("input08.txt");
    std::string line;
    unsigned int highest = 0;
    file >> line;
    file.seekg(std::ios::beg);
    const size_t n = line.size();

    std::vector<std::vector<char>> rows(n);
    for(std::vector<char>& row : rows){
        row.resize(n);
        for(char& r : row) file >> r;
    }

    std::vector<std::vector<char>> cols(n);
    int i = -1;
    for(std::vector<char>& col : cols){
        int k = 0; i++;
        col.resize(n);
        for(char& c : col) c = rows[k++][i];
    }

    std::vector<char>::iterator it;
    std::vector<char>::reverse_iterator itr;
    for(size_t i = 1; i < n-1; i++){
        for(size_t k = 1, score; k < n-1 && (score = 1); k++, highest = (score > highest) ? score : highest){
            for(it = rows[i].begin()+k+1; it < rows[i].end(); it++) if(*it >= rows[i][k]) {it++; break;};
            score *= it - (rows[i].begin()+k+1);

            for(itr = rows[i].rbegin()+n-k; itr < rows[i].rend(); itr++) if(*itr >= rows[i][k]) {itr++; break;};
            score *= itr - (rows[i].rbegin()+n-k);

            for(it = cols[k].begin()+i+1; it < cols[k].end(); it++) if(*it >= cols[k][i]) {it++; break;};
            score *= it - (cols[k].begin()+i+1);

            for(itr = cols[k].rbegin()+n-i; itr < cols[k].rend(); itr++) if(*itr >= cols[k][i]) {itr++; break;};
            score *= itr - (cols[k].rbegin()+n-i);
        }
    }

    std::cout << "Highest score = " << highest << std::endl;
    return 0;
}
