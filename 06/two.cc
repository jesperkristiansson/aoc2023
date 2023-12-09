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
    vector<string> times, dists;
    string token;
    cin >> token;
    cin >> token;
    while(isdigit(token[0])){
        times.emplace_back(token);
        cin >> token;
    }
    while(cin){
        cin >> token;
        dists.emplace_back(token);
    }

    string time_str, dist_str;
    for(std::vector<long int>::size_type i = 0; i < times.size(); ++i){
        time_str += times[i];
        dist_str += dists[i];
    }
    
    long total_time = stol(time_str);
    long dist_to_beat = stol(dist_str);

    long ways_to_win = 0;
    for(long charge_time = 0; charge_time < total_time; ++charge_time){
        long time_left = total_time - charge_time;
        long dist = charge_time*time_left;
        if(dist > dist_to_beat){
            ++ways_to_win;
        }
    }
    cout << ways_to_win << endl;
}