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
    vector<string> cards;

    while(cin){
        string line;
        getline(cin, line);
        cards.push_back(line);
    }
    
    long num_cards = cards.size() - 1;
    long sum = 0;
    long nums[num_cards];
    for(long i = 0; i < num_cards; ++i){
        nums[i] = 1;
    }

    for(long i = 0; i < num_cards; ++i){
        // if(nums[i] == 0){
        //     continue;
        // }

        stringstream line{cards[i]};
        string token;
        line >> token;
        line >> token;
        line >> token;

        set<long> winning;
        while(token != "|"){
            winning.insert(stol(token));
            line >> token;
        }
        line >> token;

        long wins = 0;  
        while(line){
            long n = stol(token);
            if(winning.count(n)){
                ++wins;
                nums[i + wins] += nums[i];
            }

            line >> token;
        }

        sum += nums[i];
    }

    cout << sum << endl;
}