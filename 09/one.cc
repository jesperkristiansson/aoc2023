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

long val_of_seq(const vector<long>& seq){
    bool all_zeroes = true;
    for(long l : seq){
        if(l != 0){
            all_zeroes = false;
            break;
        }
    }
    if(all_zeroes){
        return 0;
    }

    vector<long> new_seq;
    for(vector<long>::size_type i = 1; i < seq.size(); ++i){
        long new_val = seq[i] - seq[i-1];
        new_seq.push_back(new_val);
    }
    long val = seq[seq.size()-1] + val_of_seq(new_seq);
    return val;
}

int main(){
    vector<vector<long>> histories;
    while(!cin.eof()){
        string line;
        getline(cin, line);
        stringstream ss{line};
        long val;
        vector<long> history;
        while(!ss.eof()){
            ss >> val;
            history.push_back(val);
        }
        histories.push_back(history);
    }

    long sum = 0;
    for(const auto& history : histories){
        sum += val_of_seq(history);
    }
    cout << sum << endl;
}