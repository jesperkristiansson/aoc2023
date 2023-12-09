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

    string line;

    getline(cin, route);

    getline(cin, line);

    while(!cin.eof()){
        getline(cin, line);

        string current = line.substr(0, 3);
        string left = line.substr(7, 3);
        string right = line.substr(12, 3);
        paths[current] = make_pair(left, right);
    }

    long steps = 0;
    string current = "AAA";
    const string end = "ZZZ";

    string::size_type route_i = 0;
    while(current != end){
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

    cout << steps << endl;
}