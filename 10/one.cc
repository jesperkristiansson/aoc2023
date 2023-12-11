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

#define WEST 0
#define NORTH 1
#define EAST 2
#define SOUTH 3

//the directions in which each pipe is connected (west, north, east, south)
bool pipe_connections[256][4];

void init_row(unsigned char c, bool bool1, bool bool2, bool bool3, bool bool4){
    pipe_connections[c][0] = bool1;
    pipe_connections[c][1] = bool2;
    pipe_connections[c][2] = bool3;
    pipe_connections[c][3] = bool4;
}

int main(){
    //read input
    vector<string> pipes;
    while(!cin.eof()){
        string line;
        getline(cin, line);
        pipes.push_back(line);
    }

    //init "map" for pipe connections
    init_row('-', true, false, true, false);
    init_row('7', true, false, false, true);
    init_row('F', false, false, true, true);
    init_row('J', true, true, false, false);
    init_row('L', false, true, true, false);
    init_row('|', false, true, false, true);

    int y = -1;
    int x = -1;
    for(y = 0; y < (int)pipes.size(); ++y){
        const string& line = pipes[y];
        for(x = 0; x < (int)line.length(); ++x){
            if(line[x] == 'S'){
                break;
            }
        }
        if(line[x] == 'S'){
            break;
        }
    }
    assert(x != -1);
    assert(y != -1);

    //find a connected pipe, assumes start pipe is not at an edge
    int direction_from;
    if(pipe_connections[(unsigned char)pipes[y][x-1]][EAST]){
        --x;
        direction_from = EAST;
    } else if(pipe_connections[(unsigned char)pipes[y][x+1]][WEST]){
        ++x;
        direction_from = WEST;
    } else{
        --y;
        direction_from = SOUTH;
    }

    int loop_length = 1;
    while(pipes[y][x] != 'S'){
        ++loop_length;

        if(direction_from != WEST && pipe_connections[(unsigned char)pipes[y][x]][WEST]){
            --x;
            direction_from = EAST;
        } else if(direction_from != EAST && pipe_connections[(unsigned char)pipes[y][x]][EAST]){
            ++x;
            direction_from = WEST;
        } else if(direction_from != NORTH && pipe_connections[(unsigned char)pipes[y][x]][NORTH]){
            --y;
            direction_from = SOUTH;
        } else{
            ++y;
            direction_from = NORTH;
        }
    }

    int furthest = loop_length / 2;
    cout << furthest << endl;
}