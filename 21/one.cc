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

#include "readInput.hpp"
#include "Grid.hpp"

using namespace std;

using Map = Grid<char>;

Point findStart(const Map &map){
    return map.findFirst('S').value();
}

int findReachableTiles(Map &map, const Point &start, int numSteps){
    int reachableTiles = 0;

    bool countEvenSteps = numSteps % 2 == 0;

    set<Point> currentBatch{start};
    for(int i = 0; i <= numSteps && !currentBatch.empty(); i++){
        set<Point> nextBatch;

        bool isEvenStep = i % 2 == 0;
        bool countStep = isEvenStep && countEvenSteps;
        if(countStep){
            reachableTiles += currentBatch.size();
        }

        for(Point p : currentBatch){
            map.at(p) = '-';

            for(Direction d : {NORTH, EAST, SOUTH, WEST}){
                Point neighbor = p + d;
                if(map.contains(neighbor) && map.at(neighbor) == '.'){
                    nextBatch.insert(neighbor);
                }
            }
        }
        currentBatch = nextBatch;
    }

    return reachableTiles;
}

int main(){
    auto input_mat = readInput_mat<char>();
    Map map(input_mat);
    Point start = findStart(map);
    cout << findReachableTiles(map, start, 64) << endl;
}
