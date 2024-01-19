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
#include <cassert>

using namespace std;

static uint8_t hash2(const string& s){
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

    array<vector<pair<string, uint8_t>>, 256> map;

    size_t start_pos = 0;
    do{
        size_t operand_pos = input.find_first_of("-=", start_pos);
        size_t end_pos = input.find(',', operand_pos);
        const string& item = input.substr(start_pos, operand_pos-start_pos);
        uint8_t box_num = hash2(item);
        auto& box = map[box_num];
        auto matches_item = [&](const pair<string, uint8_t>& box_item){ return box_item.first == item;};
        if(input[operand_pos] == '-'){
            auto remove_it = remove_if(box.begin(), box.end(), matches_item);
            box.erase(remove_it, box.end());
        } else{ //operand is '='
            uint8_t focal_length = input[operand_pos+1] - '0';
            auto find_it = find_if(box.begin(), box.end(), matches_item);
            if(find_it != box.end()){
                find_it->second = focal_length;
            } else{
                box.push_back(make_pair<>(item, focal_length));
            }
        }
        start_pos = end_pos + 1;
    } while(start_pos != string::npos+1);
    
    unsigned long total = 0;
    for(int box_number = 0; box_number < 256; ++box_number){
        const auto& box = map[box_number];
        for(int slot_number = 0; slot_number < box.size(); ++slot_number){
            const auto& lens = box[slot_number];
            total += (box_number+1)*(slot_number+1)*lens.second;
        }
    }

    cout << total << endl;
}