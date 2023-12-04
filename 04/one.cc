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

using namespace std;

int main(){
    string token;
    long sum = 0;
    long i = 1;

    cin >> token;
    while(cin){
        cin >> token;
        cin >> token;

        set<long> winning;
        while(token != "|"){
            winning.insert(stol(token));
            cin >> token;
        }
        cin >> token;

        long wins = 0;  
        while(token != "Card"){
            long n = stol(token);
            if(winning.count(n)){
                ++wins;
            }

            if(!cin){
                break;
            }
            cin >> token;
        }

        if(wins > 0){
            sum += 1 << (wins - 1);
        }
        ++i;
    }
    cout << sum << endl;
}