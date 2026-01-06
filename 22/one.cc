#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <limits>
#include <utility>

#include "Point.hpp"
#include "readInput.hpp"

using namespace std;

struct Brick{
    Point3D start, end;
};
std::istream &operator>>(std::istream &is, Brick &b){
    is >> b.start;
    is.ignore();
    is >> b.end;
    return is;
}

bool checkBricksOrdered(const vector<Brick> &bricks){
    for(const Brick &b : bricks){
        for(unsigned i = 0; i < Point3D::dimensions(); i++){
            if(b.start[i] > b.end[i]){
                return false;
            }
        }
    }

    return true;
}

void printBricks(const vector<Brick> &bricks){
    for(Brick b : bricks){
        cout << b.start << ", " << b.end << endl;
    }
}

Point3D maxAlongDimensions(const vector<Brick> &bricks){
    Point3D max(0, 0, 0);
    for(const auto &b : bricks){
        for(unsigned i = 0; i < Point3D::dimensions(); i++){
            max[i] = std::max({max[i], b.start[i], b.end[i]});
        }
    }

    return max;
}

bool overlaps(const Brick &b1, const Brick &b2){
    bool overlapsX = b1.start.x() <= b2.end.x() && b1.end.x() >= b2.start.x();
    bool overlapsY = b1.start.y() <= b2.end.y() && b1.end.y() >= b2.start.y();
    return overlapsX && overlapsY;
}

vector<Brick> fallDown(vector<Brick> bricks){
    std::sort(bricks.begin(), bricks.end(), [](const auto &b1, const auto &b2){return b1.end.z() < b2.end.z();});

    for(size_t i = 0; i < bricks.size(); i++){
        Brick &b1 = bricks[i];

        int maxZ = 0;
        for(long long j = (long long)i - 1; j >= 0; j--){
            const Brick &b2 = bricks[j];
            if(overlaps(b1, b2)){
                maxZ = max(maxZ, b2.end.z());
            }
        }

        int diffZ = b1.end.z() - b1.start.z();
        b1.start.z() = maxZ + 1;
        b1.end.z() = maxZ + 1 + diffZ;
    }


    return bricks;
}

long long countSafeBricks(const vector<Brick> &bricks){
    vector<bool> canBeRemoved(bricks.size(), true);

    //assume bricks is still sorted from fallDown()
    for(size_t i = 0; i < bricks.size(); i++){
        const Brick &b1 = bricks[i];

        vector<int> supportingBricks;
        for(long long j = (long long)i - 1; j >= 0; j--){
            const Brick &b2 = bricks[j];
            if(b2.end.z() == b1.start.z() - 1 && overlaps(b1, b2)){
                supportingBricks.push_back(j);
                // numSupporting++;
            }
        }
        if(supportingBricks.size() == 1){
            canBeRemoved[supportingBricks[0]] = false;
        }
    }

    long long count = 0;
    for(auto b : canBeRemoved){
        if(b){
            count++;
        }
    }

    return count;
}

int main(){
    vector<Brick> bricks = readInput_vec<Brick>();
    if(!checkBricksOrdered(bricks)){
        cerr << "Points of bricks not ordered as expected" << endl;
    }
    bricks = fallDown(bricks);

    cout << countSafeBricks(bricks) << endl;
}