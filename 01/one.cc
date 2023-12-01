#include <iostream>
#include <string>

using namespace std;

int main(){
    string line;
    long sum = 0;
    const char *digits = "0123456789";
    while(cin >> line){
        size_t first_n = line.find_first_of(digits);
        size_t last_n = line.find_last_of(digits);
        string num_str{line[first_n], line[last_n]};
        int num = stoi(num_str);
        sum += num;
    }
    cout << sum << endl;
}