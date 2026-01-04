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
#include <fstream>

using namespace std;

enum direction{
    WEST = 'L',
    NORTH = 'U',
    EAST = 'R',
    SOUTH = 'D'
};

struct dig_command{
    direction dir;
    int steps;
};

template <typename T,typename U>                                                   
void operator+=(pair<T,U>& lhs, const pair<T,U>& rhs) {   
    lhs.first += rhs.first;
    lhs.second += rhs.second;                             
}

int main(){
    vector<dig_command> dig_plan;
    while(!cin.eof()){
        string line;
        getline(cin, line);
        dig_command dc;

        dc.dir = static_cast<direction>(line[0]);
        size_t num_end_i = line.find(' ', 2);
        dc.steps = stoi(line.substr(2, num_end_i - 2));
        
        dig_plan.push_back(dc);
    }

    set<pair<int, int>> holes;
    pair<int, int> current_pos = make_pair(0, 0);
    holes.insert(current_pos);

    pair<int, int> min_coords = current_pos;    //used for drawing
    pair<int, int> max_coords = current_pos;

    for(const auto& dc : dig_plan){
        pair<int, int> delta;
        switch(dc.dir){
            case WEST:
                delta = make_pair(-1, 0);
                break;
            case NORTH:
                delta = make_pair(0, -1);
                break;
            case EAST:
                delta = make_pair(1, 0);
                break;
            case SOUTH:
                delta = make_pair(0, 1);
                break;
        }
        for(int i = 0; i < dc.steps; i++){
            current_pos += delta;
            holes.insert(current_pos);
        }
        max_coords.first = max(max_coords.first, current_pos.first);
        max_coords.second = max(max_coords.second, current_pos.second);
        min_coords.first = min(min_coords.first, current_pos.first);
        min_coords.second = min(min_coords.second, current_pos.second);
    }

    const int DIG_SITE_WIDTH = max_coords.first - min_coords.first+1;
    const int DIG_SITE_HEIGHT = max_coords.second - min_coords.second+1;
    bool dig_site[DIG_SITE_HEIGHT][DIG_SITE_WIDTH];
    memset(dig_site, 0, sizeof(dig_site));

    for(const auto& hole : holes){
        dig_site[hole.second - min_coords.second][hole.first - min_coords.first] = true;
    }

    ofstream of{"out"};
    long count = 0;
    for(int y = 0; y < DIG_SITE_HEIGHT; y++){
        bool counting_empty = false;
        for(int x = 0; x < DIG_SITE_WIDTH; x++){
            if(dig_site[y][x]){
                count++;
                of << '#';

                bool from_up = y > 0 && dig_site[y-1][x];
                while(x < DIG_SITE_WIDTH-1 && dig_site[y][x+1]){
                    of << '#';
                    count++;
                    x++;
                }
                bool to_down = y < DIG_SITE_HEIGHT-1 && dig_site[y+1][x];

                if(from_up == to_down){
                    counting_empty = !counting_empty;
                }
            } else if(counting_empty){
                of << '#';
                ++count;
            } else{
                of << '.';
            }
        }
        of << endl;
    }

    cout << count << endl;
}