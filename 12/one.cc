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

static bool check_match(const string& s, const vector<int>& contigs){
    string::size_type string_i = 0;
    for(int contig : contigs){
        while(string_i < s.length() && s[string_i] != '#'){
            ++string_i;
        }

        for(int i = 0; i < contig; ++i){
            if(string_i == s.length() || s[string_i] != '#'){
                return false;
            }
            ++string_i;
        }

        if(string_i < s.length() && s[string_i] == '#'){
            return false;
        }
    }

    while(string_i < s.length()){
        if(s[string_i] == '#'){
            return false;
        }
        ++string_i;
    }

    return true;
}

static int valid_permutations(const string& s, const vector<int>& contigs){
    auto pos = s.find("?");
    if(pos == string::npos){
        return check_match(s, contigs);
    }

    string new_str{s};
    new_str[pos] = '.';
    int n1 = valid_permutations(new_str, contigs);
    new_str[pos] = '#';
    int n2 = valid_permutations(new_str, contigs);
    return n1 + n2;
}

int main(){
    long sum = 0;
    while(!cin.eof()){
        string record, contig_str;
        cin >> record;
        cin >> contig_str;
        
        stringstream ss{contig_str};
        vector<int> contigs;
        while(getline(ss, contig_str, ',')){
            contigs.push_back(stoi(contig_str));
        }

        sum += valid_permutations(record, contigs);
    }

    cout << sum << endl;
}