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

using namespace std;

int main(){
    vector<string> mat;
    while(cin){
        string line;
        getline(cin, line);
        mat.push_back(line);
    }
    long rows = mat.size() - 1;
    long cols = mat[0].length();

    long sum = 0;
    for(long r = 0; r < rows; ++r){
        for(long c = 0; c < cols; ++c){
            if(isdigit(mat[r][c])){
                long num_len = 0;
                while(c + num_len < cols && isdigit(mat[r][c + num_len])){
                    ++num_len;
                }

                string num_str = mat[r].substr(c, num_len);
                long num = stol(num_str);

                for(long offset_r = -1; offset_r <= 1; ++offset_r){
                    for(long offset_c = -1; offset_c <= num_len; ++offset_c){
                        long new_r = r + offset_r;
                        long new_c = c + offset_c;
                        if(new_r >= 0 && new_r < rows && new_c >= 0 && new_c < cols){
                            char c = mat[new_r][new_c];
                            if(c != '.' && !isdigit(c)){
                                sum += num;
                            }
                        }
                    }
                }

                c += num_len - 1;
            }
        }   
    }
    cout << sum << endl;
}