#include <cstddef>
#include <cstdlib>
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
#include <cassert>
#include <list>

using namespace std;

//using powers of two enables easier checking of two directions i.e DIRECTION_1 | DIRECTION_2 is unique for each pair
enum direction{
    EAST = 1 << 0,
    SOUTH = 1 << 1,
    WEST = 1 << 2,
    NORTH = 1 << 3
};

enum corner_bend{
    EAST_SOUTH = 1 << 0,
    SOUTH_WEST = 1 << 1,
    WEST_NORTH = 1 << 2,
    NORTH_EAST = 1 << 3
};

struct dig_command{
    direction dir;
    long steps;
};

struct corner{
    pair<long, long> coords;
    corner_bend bend;

    corner(pair<long, long> coords, corner_bend bend): coords{coords}, bend{bend} {}
};

struct list_node{
    struct corner data;
    struct list_node *next, *prev;
};

struct circular_double_linked_list{
    struct list_node *head;
    struct list_node *mem_chunk;
    size_t size;

    circular_double_linked_list(size_t capacity): head{nullptr}, size{0} {
        mem_chunk = static_cast<list_node*>(malloc(sizeof(list_node)*capacity));
    //     head = mem_chunk;
    //     for(size_t i = 0; i < capacity; i++){
    //         mem_chunk[i].next = &mem_chunk[(i+1) % capacity];
    //         mem_chunk[(i+1) % capacity].prev = &mem_chunk[i];
    //     }
    }

    ~circular_double_linked_list() {free(mem_chunk);}

    void add_node(corner&& data){
        if(size == 0){
            head = mem_chunk;
            head->prev = head;
            head->next = head;
            head->data = data;
        } else{
            list_node *new_node = &mem_chunk[size];
            new_node->data = data;
            new_node->prev = head->prev;
            new_node->next = head;
            head->prev->next = new_node;
            head->prev = new_node;
        }
        size++;
    }

    void remove_node(list_node *node){
        node->prev->next = node->next;
        node->next->prev = node->prev;
        size--;
    }
};

template <typename T,typename U>                                                   
void operator+=(pair<T,U>& lhs, const pair<T,U>& rhs) {   
    lhs.first += rhs.first;
    lhs.second += rhs.second;                             
}

template <typename T,typename U>                                                   
pair<T,U> operator*(const pair<T,U>& lhs, long n) {   
    return {lhs.first * n, lhs.second * n};                     
}

//keep track of corner with their orientation, look for mathing corners (half of rectangle) and coalesce

int main(){
    vector<dig_command> dig_plan;
    while(!cin.eof()){
        string line;
        getline(cin, line);
        dig_command dc;

        switch(line[0]){
            case 'R':
                dc.dir = EAST;
                break;
            case 'D':
                dc.dir = SOUTH;
                break;
            case 'L':
                dc.dir = WEST;
                break;
            case 'U':
                dc.dir = NORTH;
                break;
        }
        size_t num_end_i = line.find(' ', 2);
        dc.steps = stoi(line.substr(2, num_end_i - 2));

        // size_t hex_start_i = line.length() - 7;
        // dc.steps = stoul(line.substr(hex_start_i, 5), nullptr, 16);
        // switch(stoul(line.substr(line.length()-2), nullptr, 16)){
        //     case 0:
        //         dc.dir = EAST;
        //         break;
        //     case 1:
        //         dc.dir = SOUTH;
        //         break;
        //     case 2:
        //         dc.dir = WEST;
        //         break;
        //     case 3:
        //         dc.dir = NORTH;
        //         break;
        // }

        dig_plan.push_back(dc);
    }

    circular_double_linked_list corner_list(dig_plan.size());

    vector<corner> corners;

    pair<long, long> current_pos = make_pair(0, 0);

    pair<long, long> min_coords = current_pos;    //used for drawing
    pair<long, long> max_coords = current_pos;

    for(vector<dig_command>::size_type i = 0; i < dig_plan.size(); i++){
        const auto& dc = dig_plan[i];
        pair<long, long> delta;
        switch(dc.dir){
            case EAST:
                delta = make_pair(1, 0);
                break;
            case SOUTH:
                delta = make_pair(0, 1);
                break;
            case WEST:
                delta = make_pair(-1, 0);
                break;
            case NORTH:
                delta = make_pair(0, -1);
                break;
        }

        current_pos += delta*dc.steps;
        max_coords.first = max(max_coords.first, current_pos.first);
        max_coords.second = max(max_coords.second, current_pos.second);
        min_coords.first = min(min_coords.first, current_pos.first);
        min_coords.second = min(min_coords.second, current_pos.second);

        auto next_i = (i + 1) %  dig_plan.size();
        const direction& next_dir = dig_plan[next_i].dir;
        corner_bend bend;
        switch(dc.dir | next_dir){
            case (EAST | SOUTH):
                bend = EAST_SOUTH;
                break;
            case (SOUTH | WEST):
                bend = SOUTH_WEST;
                break;
            case (WEST | NORTH):
                bend = WEST_NORTH;
                break;
            case (NORTH | EAST):
                bend = NORTH_EAST;
                break;
        }
        //add corner
        corners.emplace_back(current_pos, bend);
        corner_list.add_node(corner(current_pos, bend));
    }

    long total = 0;
    long last_side = 0;
    
    list_node* start_p = corner_list.head;
    while(corner_list.size > 0){
        assert(corner_list.size >= 4);
        list_node *middle_1_p = start_p->next;
        list_node *middle_2_p = middle_1_p->next;
        list_node *end_p = middle_2_p->next;

        corner& start = start_p->data;
        corner& middle_1 = middle_1_p->data;
        corner& middle_2 = middle_2_p->data;
        corner& end = end_p->data;

        auto print_point = [](const pair<long, long>& coords){
            cout << "(" << coords.first << "," << coords.second << ")";
        };

        pair<long, long> delta = make_pair(0, 0);
        if(middle_1.bend == EAST_SOUTH && middle_2.bend == SOUTH_WEST){
            cout << "handling rectangle at ";
            print_point(start.coords);
            print_point(middle_1.coords);
            print_point(middle_2.coords);
            print_point(end.coords);
            cout << endl;

            delta.first = -1;
            // long side_1_1 = middle_2.coords.second - middle_1.coords.first;
            // long side_1_1 = middle_2.coords.first - middle_1.coords.second;

            long side_1 = middle_2.coords.second - middle_1.coords.second;
            long side_2_1 = middle_1.coords.first - start.coords.first;
            long side_2_2 = middle_2.coords.first - end.coords.first;
            long side_2 = min(side_2_1, side_2_2);
            last_side = side_1+1;
            total += (side_1+1)*(side_2);
            if(side_2_1 > side_2){
                middle_1.coords.first -= side_2;
            } else{
                corner_list.remove_node(start_p);
                corner_list.remove_node(middle_1_p);
            }
            if(side_2_2 > side_2){
                middle_2.coords.first -= side_2;
            } else{
                corner_list.remove_node(end_p);
                corner_list.remove_node(middle_2_p);
            }
            start_p = end_p;
        } else if(middle_1.bend == SOUTH_WEST && middle_2.bend == WEST_NORTH){
            cout << "handling rectangle at ";
            print_point(start.coords);
            print_point(middle_1.coords);
            print_point(middle_2.coords);
            print_point(end.coords);
            cout << endl;
            long side_1 = middle_1.coords.first - middle_2.coords.first;
            long side_2_1 = middle_1.coords.second - start.coords.second;
            long side_2_2 = middle_2.coords.second - end.coords.second;
            long side_2 = min(side_2_1, side_2_2);
            last_side = side_1+1;
            total += (side_1+1)*(side_2);
            if(side_2_1 > side_2){
                middle_1.coords.second -= side_2;
            } else{
                corner_list.remove_node(start_p);
                corner_list.remove_node(middle_1_p);
            }
            if(side_2_2 > side_2){
                middle_2.coords.second -= side_2;
            } else{
                corner_list.remove_node(end_p);
                corner_list.remove_node(middle_2_p);
            }
            start_p = end_p;
        } else if(middle_1.bend == WEST_NORTH && middle_2.bend == NORTH_EAST){
            cout << "handling rectangle at ";
            print_point(start.coords);
            print_point(middle_1.coords);
            print_point(middle_2.coords);
            print_point(end.coords);
            cout << endl;
            long side_1 = -(middle_2.coords.second - middle_1.coords.second);
            long side_2_1 = -(middle_1.coords.first - start.coords.first);
            long side_2_2 = -(middle_2.coords.first - end.coords.first);
            long side_2 = min(side_2_1, side_2_2);
            last_side = side_1+1;
            total += (side_1+1)*(side_2);
            if(side_2_1 > side_2){
                middle_1.coords.first -= -side_2;
            } else{
                corner_list.remove_node(start_p);
                corner_list.remove_node(middle_1_p);
            }
            if(side_2_2 > side_2){
                middle_2.coords.first -= -side_2;
            } else{
                corner_list.remove_node(end_p);
                corner_list.remove_node(middle_2_p);
            }
            start_p = end_p;
        } else if(middle_1.bend == NORTH_EAST && middle_2.bend == EAST_SOUTH){
            cout << "handling rectangle at ";
            print_point(start.coords);
            print_point(middle_1.coords);
            print_point(middle_2.coords);
            print_point(end.coords);
            cout << endl;
            long side_1 = -(middle_1.coords.first - middle_2.coords.first);
            long side_2_1 = -(middle_1.coords.second - start.coords.second);
            long side_2_2 = -(middle_2.coords.second - end.coords.second);
            long side_2 = min(side_2_1, side_2_2);
            last_side = side_1+1;
            total += (side_1+1)*(side_2);
            if(side_2_1 > side_2){
                middle_1.coords.second -= -side_2;
            } else{
                corner_list.remove_node(start_p);
                corner_list.remove_node(middle_1_p);
            }
            if(side_2_2 > side_2){
                middle_2.coords.second -= -side_2;
            } else{
                corner_list.remove_node(end_p);
                corner_list.remove_node(middle_2_p);
            }
            start_p = end_p;
        }

        start_p = start_p->next;
    }

    total += last_side;

    //assume we travel clockwise from start
    // long corner_i = 0;
    // while(corners.size() > 0){
    //     assert(corners.size() >= 4);
    //     corner& start = corners[corner_i];
    //     corner& middle_1 = corners[(corner_i + 1) % corners.size()];
    //     corner& middle_2 = corners[(corner_i + 2) % corners.size()];
    //     corner& end = corners[(corner_i + 3) % corners.size()];

    //     bool remove_corners = false;
    //     if(middle_1.bend == EAST_SOUTH && middle_2.bend == SOUTH_WEST){ //right rectangle
    //         remove_corners = true;

    //         long side_1 = middle_2.coords.second - middle_1.coords.second;
    //         long side_2_1 = middle_1.coords.first - start.coords.first;
    //         long side_2_2 = middle_2.coords.first - end.coords.first;
    //         long side_2 = min(side_2_1, side_2_2);
    //         total += side_1*side_2;
    //         if(side_2_1 > side_2){
    //             //corner new_corner(make_pair(middle_1.coords.first - side_2, middle_1.coords.second), middle_1.bend);
    //             middle_1.coords.first -= side_2;
    //         } else{
    //             corners.erase()
    //         }
    //     } else if(middle_1.bend == SOUTH_WEST && middle_2.bend == WEST_NORTH){  //lower rectangle 
    //         remove_corners = true;

    //     } else if(middle_1.bend == WEST_NORTH && middle_2.bend == NORTH_EAST){  //left rectangle
    //         remove_corners = true;

    //     } else if(middle_1.bend == NORTH_EAST && middle_2.bend == EAST_SOUTH){  //upper rectangle
    //         remove_corners = true;

    //     }

        

    //     if(remove_corners){
    //         //remove all
    //         corners.erase((corners.begin() + 1) % )
    //         if(corner_i + 3 < corners.size()){
    //             corners.erase(corners.begin() + corner_i, corners.begin() + corner_i + 4);
    //         } else{
    //             size_t end_i = (corner_i + 3) % corners.size();
    //             corners.erase(corners.begin() + corner_i, corners.end());
    //             corners.erase(corners.begin(), corners.begin() + end_i);
    //         }
    //     }

    //     corner_i = corner_i + 1 % corners.size();
    // }


    cout << total << endl;
}