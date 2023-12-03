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

using namespace std;

int main()
{
    string line;

    int sum = 0;
    int line_i = 1;
    while (cin)
    {
        getline(cin, line);
        int num_red = 0;
        int num_green = 0;
        int num_blue = 0;
        int n = line.find_first_of(':');
        stringstream ss{line.substr(n + 1)};
        bool should_be_counted = true;
        while (ss)
        {
            int num;
            string color;
            ss >> num;
            ss >> color;
            if (color.rfind("red", 0) == 0)
            {
                num_red = max(num, num_red);
            }
            else if (color.rfind("green", 0) == 0)
            {
                num_green = max(num, num_green);
            }
            else if (color.rfind("blue", 0) == 0)
            {
                num_blue = max(num, num_blue);
            }
            else
            {
                should_be_counted = false;
            }

            if(color.back() != ';' && color.back() != ','){
                break;
            }
        }
        if(should_be_counted){
            sum += num_red*num_green*num_blue;
        }
        
        ++line_i;
    }
    cout << sum << endl;
}