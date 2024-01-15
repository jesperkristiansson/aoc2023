#include <cstddef>
#include <iostream>
#include <numeric>
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
    vector<vector<string>> items;
    {
        vector<string> current_item;
        while(!cin.eof()){
            string s;
            getline(cin, s);
            if(s == ""){
                items.push_back(current_item);
                current_item.clear();
            } else{
                current_item.push_back(s);
            }
        }
        items.push_back(current_item);
    }

    size_t sum = 0;
    for(auto map : items){
        const size_t map_height = map.size();
        const size_t map_width = map[0].length();

        //find horizontal mirror
        for(size_t c = 1; c < map_width; ++c){
            size_t chars_left = c;
            size_t chars_right = map_width - chars_left;
            size_t chars_to_check = min(chars_left, chars_right);

            bool smudge_removed = false;
            //check that each row is mirrored
            bool is_mirrored = true;
            for(size_t r = 0; r < map_height; ++r){
                const string& line = map[r];
                for(size_t i = 0; i < chars_to_check; ++i){
                    if(line[c - 1 - i] != line[c + i]){
                        if(!smudge_removed){
                            smudge_removed = true;
                        } else{
                            is_mirrored = false;
                            break;
                        }
                    }
                }
                if(!is_mirrored){
                    break;
                }
            }
            if(smudge_removed && is_mirrored){
                sum += c;
                break;
            }
        }

        //find vertical mirror
        for(size_t r = 1; r < map_height; ++r){
            size_t chars_up = r;
            size_t chars_down = map_height - chars_up;
            size_t chars_to_check = min(chars_up, chars_down);

            bool smudge_removed = false;
            //check that each row is mirrored
            bool is_mirrored = true;
            for(size_t i = 0; i < chars_to_check; ++i){
                string line1 = map[r - 1 - i];
                string line2 = map[r + i];
                for(size_t c = 0; c < map_width; ++c){
                    if(line1[c] != line2[c]){
                        if(!smudge_removed){
                            smudge_removed = true;
                        } else{
                            is_mirrored = false;
                            break;
                        }
                    }
                }
            }
            if(smudge_removed && is_mirrored){
                sum += 100*r;
                break;
            }
        }
    }
    cout << "total: " << sum << endl;
}