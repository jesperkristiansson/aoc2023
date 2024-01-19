#include <cassert>
#include <functional>
#include <iostream>
#include <queue>
#include <string>
#include <sstream>
#include <climits>
#include <algorithm>
#include <vector>
#include <set>
#include <unordered_set>
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
    SOUTH,
    NUM_DIRECTIONS
};

struct node{
    int x, y;
    int last_dir_num;
    int total_cost;
    direction last_dir;

    node(int x, int y, direction last_dir, int last_dir_num, int total_cost)
    : x{x}, y{y}, last_dir_num{last_dir_num}, total_cost{total_cost}, last_dir{last_dir} {}

    bool operator==(const node& other) const{
        return x == other.x && y == other.y && last_dir_num == other.last_dir_num && last_dir == other.last_dir;
    }

    bool operator<(const node& other) const{
        return total_cost < other.total_cost;
    }

    bool operator>(const node& other) const{
        return total_cost > other.total_cost;
    }
};

template <>
struct std::hash<node>
{
  std::size_t operator()(const node& n) const
  {
    // Compute individual hash values for relevant fields and combine them using XOR
    // and bit shifting:

    return (hash<int>()(n.x)
             ^ (hash<int>()(n.y) << 1)
             ^ hash<int>()(n.last_dir_num) << 2)
             ^ hash<int>()(static_cast<int>(n.last_dir) << 3);
  }
};

int main(){
    vector<string> map;
    while(!cin.eof()){
        string line;
        getline(cin, line);
        map.push_back(line);
    }

    const int MAP_HEIGHT = map.size();
    const int MAP_WIDTH = map[0].size();

    long cheapest = 0;

    unordered_set<node> visited;

    priority_queue<node, vector<node>, greater<node>> queue;
    node start_node(0, 0, WEST, 0, 0);
    visited.insert(start_node);
    queue.push(std::move(start_node));
    while(true){
        assert(!queue.empty());
        const node current_node = queue.top();
        queue.pop();
        if(current_node.x == MAP_WIDTH-1 && current_node.y == MAP_HEIGHT-1){
            //done
            cheapest = current_node.total_cost;
            break;
        }

        for(int dir = 0; dir < NUM_DIRECTIONS; dir++){
            if(dir == current_node.last_dir && current_node.last_dir_num == 3){ //must turn
                continue;
            }
            if(dir - current_node.last_dir == 2 || dir - current_node.last_dir == -2){  //can't go directly back
                continue;
            }
            int new_x = current_node.x + (dir - 1) % 2;
            int new_y = current_node.y + (dir - 2) % 2;
            if(new_x < 0 || new_x >= MAP_WIDTH || new_y < 0 || new_y >= MAP_HEIGHT){
                continue;
            }
            int new_last_dir_num = dir == current_node.last_dir ? current_node.last_dir_num + 1 : 1;
            int new_total_cost = current_node.total_cost + (map[new_y][new_x] - '0');
            node new_node(new_x, new_y, static_cast<direction>(dir), new_last_dir_num, new_total_cost);
            if(visited.find(new_node) == visited.end()){
                visited.insert(new_node);
                queue.push(std::move(new_node));
            }
        }

        //break;
    }

    cout << cheapest << endl;
}