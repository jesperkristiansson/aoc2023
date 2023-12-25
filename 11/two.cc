#include <cstddef>
#include <iostream>
#include <string>
#include <sstream>
#include <climits>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <limits>
#include <utility>
#include <cctype>
#include <cstring>
#include <cassert>

#define GROWTH_RATE 1000000 

using namespace std;

int main(){
    vector<string> space;
    vector<pair<int, int>> stars;
    int current_row = 0;
    while(!cin.eof()){
        string line;
        getline(cin, line);
        for(string::size_type current_col = 0; current_col < line.size(); ++current_col){
            if(line[current_col] == '#'){
                stars.emplace_back(current_row, current_col);
            }
        }
        space.push_back(line);
        ++current_row;
    }

    int empty_rows_above[space.size()];
    int empty_cols_left[space[0].length()];
    int total_empty_rows = 0;
    int total_empty_cols = 0;

    for(vector<string>::size_type i = 0; i < space.size(); ++i){
        const string& row = space[i];
        empty_rows_above[i] = total_empty_rows;
        if(count(row.begin(), row.end(), '#') == 0){
            ++total_empty_rows;
        }
    }

    for(string::size_type c = 0; c < space[0].size(); ++c){
        bool isEmpty = true;
        for(vector<string>::size_type r = 0; r < space[0].size(); ++r){
            if(space[r][c] == '#'){
                isEmpty = false;
                break;
            }
        }

        empty_cols_left[c] = total_empty_cols;
        if(isEmpty){
            ++total_empty_cols;
        }
    }

    long sum = 0;
    for(vector<pair<int, int>>::size_type i1 = 0; i1 < stars.size(); ++i1){
        for(vector<pair<int, int>>::size_type i2 = i1 + 1; i2 < stars.size(); ++i2){
            pair<int, int>& star1 = stars[i1];
            pair<int, int>& star2 = stars[i2];
            assert(star1 != star2);
            
            int diff_rows = abs(star2.first - star1.first);
            int diff_cols = abs(star2.second - star1.second);
            int empty_rows_between = abs(empty_rows_above[star2.first] - empty_rows_above[star1.first]);
            int empty_cols_between = abs(empty_cols_left[star2.second] - empty_cols_left[star1.second]);

            long dist_rows = (diff_rows - empty_rows_between) + empty_rows_between*GROWTH_RATE;
            long dist_cols = (diff_cols - empty_cols_between) + empty_cols_between*GROWTH_RATE;

            int min = dist_rows + dist_cols;
            sum += min;
        }
    }
    cout << sum << endl;
}