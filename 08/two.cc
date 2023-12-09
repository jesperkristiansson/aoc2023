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
    string route;
    map<string, pair<string, string>> paths;
    vector<string> ends_with_A;

    string line;

    getline(cin, route);

    getline(cin, line);

    while(!cin.eof()){
        getline(cin, line);

        string current = line.substr(0, 3);
        string left = line.substr(7, 3);
        string right = line.substr(12, 3);
        paths[current] = make_pair(left, right);

        if(current[2] == 'A'){
            ends_with_A.push_back(current);
        }
    }

    long loop_lengths[ends_with_A.size()];
    long steps_from_end[ends_with_A.size()];
    for(vector<long>::size_type i = 0; i < ends_with_A.size(); ++i){
        long steps = 0;
        string current = ends_with_A[i];

        string::size_type route_i = 0;
        while(current[2] != 'Z'){
            ++steps;

            if(route_i >= route.size()){
                route_i = 0;
            }

            if(route[route_i++] == 'L'){
                current = paths[current].first;
            } else{
                current = paths[current].second;
            }
        }
        loop_lengths[i] = steps;
        steps_from_end[i] = steps;
    }

    long steps = 0;
    bool all_at_end = false;

    while(!all_at_end){
        all_at_end = true;
        long minS = LONG_MAX;
        for(long& steps_left : steps_from_end){
            minS = min(minS, steps_left);
        }
        steps += minS;
        for(vector<long>::size_type i = 0; i < ends_with_A.size(); i++){
            long& steps_left = steps_from_end[i];
            steps_left -= minS;
            if(steps_left == 0){
                steps_left = loop_lengths[i];
            } else{
                all_at_end = false;
            }
        }
    }

    cout << steps << endl;
}