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
    vector<long> times, dists;
    string token;
    cin >> token;
    cin >> token;
    while(isdigit(token[0])){
        times.emplace_back(stol(token));
        cin >> token;
    }
    while(cin){
        cin >> token;
        dists.emplace_back(stol(token));
    }

    long product = 1;
    for(std::vector<long int>::size_type i = 0; i < times.size(); ++i){
        long ways_to_win = 0;
        
        long total_time = times[i];
        for(long charge_time = 0; charge_time < total_time; ++charge_time){
            long time_left = total_time - charge_time;
            long dist = charge_time*time_left;
            if(dist > dists[i]){
                ++ways_to_win;
            }
        }
        product *= ways_to_win;
    }
    cout << product << endl;
}