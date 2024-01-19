#include <cassert>
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

enum direction{
    WEST,
    NORTH,
    EAST,
    SOUTH
};

struct beam{
    int x, y;
    enum direction dir;

    beam(int x, int y, enum direction dir): x{x}, y{y}, dir{dir} {}

    bool in_bounds(int width, int height) const{
        return x >= 0 && x < width && y >= 0 && y < height;
    }

    beam move(enum direction dir) const{
        int new_x = x + (dir - 1) % 2;
        int new_y = y + (dir - 2) % 2;
        return beam(new_x, new_y, dir);
    }
};

static long energize(vector<string> map, const int MAP_HEIGHT, const int MAP_WIDTH, beam start_beam){
    uint8_t visited[MAP_HEIGHT][MAP_WIDTH];
    memset(visited, 0, sizeof(visited));
    // for(const auto& a : visited){
    //     for(const auto& b : a){
    //         assert(!b);
    //     }
    // }

    vector<beam> beams;     //beam = x, y, direction
    beams.push_back(start_beam);

    long num_visited = 0;
    while(beams.size() > 0){
        vector<beam> next_beams;
        for(const auto& beam : beams){
            if(!beam.in_bounds(MAP_WIDTH, MAP_HEIGHT)){
                continue;
            }

            //mark as visited
            if(visited[beam.y][beam.x] == 0){
                ++num_visited;
            } else if(visited[beam.y][beam.x] & 1 << beam.dir){
                continue;
            }
            visited[beam.y][beam.x] |= 1 << beam.dir;

            //potentially change direction
            switch(map[beam.y][beam.x]){
                case '|':
                    if(beam.dir % 2 == 0){  //west or east
                        next_beams.push_back(beam.move(NORTH));
                        next_beams.push_back(beam.move(SOUTH));
                    } else{
                        next_beams.push_back(beam.move(beam.dir));
                    }
                    break;
                case '-':
                    if(beam.dir % 2 == 1){  //north or south
                        next_beams.push_back(beam.move(WEST));
                        next_beams.push_back(beam.move(EAST));
                    } else{
                        next_beams.push_back(beam.move(beam.dir));
                    }
                    break;
                case '/':
                    {
                        direction new_dir = static_cast<direction>(beam.dir + (6 - 2*beam.dir)-3);
                        next_beams.push_back(beam.move(new_dir));
                    }
                    break;
                case '\\':
                    {
                        direction new_dir = static_cast<direction>(beam.dir - ((beam.dir % 2)*2 - 1));
                        next_beams.push_back(beam.move(new_dir));
                    }
                    break;
                default:
                    if(map[beam.y][beam.x] != '.'){
                        cout << map[beam.y][beam.x] << endl;
                        assert(false);
                    }
                    next_beams.push_back(beam.move(beam.dir));
            }
        }

        beams = next_beams;
    }

    return num_visited;
}

int main(){
    vector<string> map;
    while(!cin.eof()){
        string line;
        getline(cin, line);
        map.push_back(line);
    }
    
    const int MAP_HEIGHT = map.size();
    const int MAP_WIDTH = map[0].size();

    long num_visited = 0;
    for(int y = 0; y < MAP_HEIGHT; y++){
        long candidate;
        candidate = energize(map, MAP_HEIGHT, MAP_WIDTH, beam(0, y, EAST));
        num_visited = max(num_visited, candidate);
        candidate = energize(map, MAP_HEIGHT, MAP_WIDTH, beam(MAP_WIDTH-1, y, WEST));
        num_visited = max(num_visited, candidate);
    }
    for(int x = 0; x < MAP_WIDTH; x++){
        long candidate;
        candidate = energize(map, MAP_HEIGHT, MAP_WIDTH, beam(x, 0, SOUTH));
        num_visited = max(num_visited, candidate);
        candidate = energize(map, MAP_HEIGHT, MAP_WIDTH, beam(x, MAP_HEIGHT-1, NORTH));
        num_visited = max(num_visited, candidate);
    }

    cout << num_visited << endl;
}