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

#define NUM_MAPS 7

using namespace std;

int main(){
    vector<pair<long long, long long>> seeds;
    vector<tuple<long long, long long, long long>> maps[NUM_MAPS];

    string line;

    getline(cin, line);
    stringstream ss{line};
    ss >> line;
    while(ss){
        long long start;
        long long length;
        ss >> start;
        ss >> length;
        seeds.emplace_back(start, length);
    }

    long long i = -1;
    while(cin){
        getline(cin, line);
        if(line == ""){
            ++i;
            getline(cin, line);
        } else{
            stringstream ss{line};
            tuple<long long, long long, long long> map;
            ss >> get<0>(map);
            ss >> get<1>(map);
            ss >> get<2>(map);
            maps[i].push_back(map);
        }
    }

    long long lowest{LLONG_MAX};
    for(pair<long long, long long> seed_range : seeds){
        for(long long seed = seed_range.first; seed < seed_range.first + seed_range.second; ++seed){
            long long val = seed;
            for(vector<tuple<long long, long long, long long>> map : maps){
                for(tuple<long long, long long, long long> rule : map){
                    long long diff = val - get<1>(rule);
                    if(diff >= 0 && diff < get<2>(rule)){
                        val = get<0>(rule) + diff;
                        break;
                    }
                }
            }
            lowest = min(lowest, val);
        }
    }
    cout << lowest << endl;
}