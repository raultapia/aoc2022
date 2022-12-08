#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>

int main(int argc, char const *argv[]) {
    std::ifstream file("input08.txt");
    std::string line;
    file >> line;
    file.seekg(std::ios::beg);
    const size_t n = line.size();
    unsigned int visible = 4*(n-2) + 4;

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

    for(size_t i = 1; i < n-1; i++){
        for(size_t k = 1; k < n-1; k++){
            if(std::find_if(rows[i].begin(), rows[i].begin()+k, [&](const char& x){return x >= rows[i][k];}) == rows[i].begin()+k) visible++;
            else if(std::find_if(rows[i].begin()+k+1, rows[i].end(), [&](const char& x){return x >= rows[i][k];}) == rows[i].end()) visible++;
            else if(std::find_if(cols[k].begin(), cols[k].begin()+i, [&](const char& x){return x >= cols[k][i];}) == cols[k].begin()+i) visible++;
            else if(std::find_if(cols[k].begin()+i+1, cols[k].end(), [&](const char& x){return x >= cols[k][i];}) == cols[k].end()) visible++;
        }
    }

    std::cout << "Visible trees = " << visible << std::endl;
    return 0;
}
