#include <cstdint>
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

static uint8_t hash2(string s){
    uint16_t hash = 0;
    for(unsigned char c : s){
        hash += static_cast<unsigned long>(c);
        hash *= 17;
        hash %= 256;
    }
    return static_cast<uint8_t>(hash);
}

int main(){
    string input;
    getline(cin, input);

    size_t start_i = 0;
    unsigned long total = 0;
    do{
        size_t end_i = input.find(',', start_i);
        total += hash2(input.substr(start_i, end_i-start_i));
        start_i = end_i + 1;
    } while(start_i != string::npos+1);
    
    cout << total << endl;
}