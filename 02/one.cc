#include <iostream>
#include <string>
#include <sstream>
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
        int num_red = 12;
        int num_green = 13;
        int num_blue = 14;
        int n = line.find_first_of(':');
        stringstream ss{line.substr(n + 1)};
        bool possible = true;
        while (ss)
        {
            int num;
            string color;
            ss >> num;
            ss >> color;
            //cout << num << ' ' << color << endl;
            if (color.rfind("red", 0) == 0)
            {
                if (num > num_red)
                {
                    possible = false;
                }
            }
            else if (color.rfind("green", 0) == 0)
            {
                if (num > num_green)
                {
                    possible = false;
                }
            }
            else if (color.rfind("blue", 0) == 0)
            {
                if (num > num_blue)
                {
                    possible = false;
                }
            }
            else
            {
                possible = false;
            }

            if(color.back() != ';' && color.back() != ','){
                break;
            }
        }
        if(possible){
            sum += line_i;
        }
        ++line_i;
    }
    cout << sum << endl;
}