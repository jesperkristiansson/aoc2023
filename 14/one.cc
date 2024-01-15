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

using namespace std;

int main(){
    vector<string> map;
    while(!cin.eof()){
        string s;
        getline(cin, s);
        map.push_back(s);
    }

    const size_t map_height = map.size();
    const size_t map_width = map[0].length();

    long sum = 0;
    for(size_t c = 0; c < map_width; ++c){
        size_t weight_top = map_height;
        size_t count = 0;
        for(size_t r = 0; r < map_height; ++r){
            char type = map[r][c];
            if(type == 'O'){
                ++count;
            } else if(type == '#'){
                size_t weight_bottom = weight_top - count;
                size_t weight = (weight_top*(weight_top+1) - weight_bottom*(weight_bottom + 1))/2;
                sum += weight;

                weight_top = map_height - (r + 1);
                count = 0;
            }
        }
        size_t weight_bottom = weight_top - count;
        size_t weight = (weight_top*(weight_top+1) - weight_bottom*(weight_bottom + 1))/2;
        sum += weight;
    }

    cout << sum << endl;
}