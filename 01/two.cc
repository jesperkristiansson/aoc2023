#include <iostream>
#include <string>

using namespace std;

int main(){
    string line;
    long sum = 0;
    const char *digits = "0123456789";
    while(cin >> line){
        int first = -1;
        int last;
        for(size_t i = 0; i < line.length(); ++i){
            string substr = line.substr(i);

            if(substr[0] == '0'){
                if(first == -1){
                    first = 0;
                }
                last = 0;
            } else if(substr[0] == '1' || substr.rfind("one", 0) == 0){
                if(first == -1){
                    first = 1;
                }
                last = 1;
            } else if(substr[0] == '2' || substr.rfind("two", 0) == 0){
                if(first == -1){
                    first = 2;
                }
                last = 2;
            } else if(substr[0] == '3' || substr.rfind("three", 0) == 0){
                if(first == -1){
                    first = 3;
                }
                last = 3;
            } else if(substr[0] == '4' || substr.rfind("four", 0) == 0){
                if(first == -1){
                    first = 4;
                }
                last = 4;
            } else if(substr[0] == '5' || substr.rfind("five", 0) == 0){
                if(first == -1){
                    first = 5;
                }
                last = 5;
            } else if(substr[0] == '6' || substr.rfind("six", 0) == 0){
                if(first == -1){
                    first = 6;
                }
                last = 6;
            } else if(substr[0] == '7' || substr.rfind("seven", 0) == 0){
                if(first == -1){
                    first = 7;
                }
                last = 7;
            } else if(substr[0] == '8' || substr.rfind("eight", 0) == 0){
                if(first == -1){
                    first = 8;
                }
                last = 8;
            } else if(substr[0] == '9' || substr.rfind("nine", 0) == 0){
                if(first == -1){
                    first = 9;
                }
                last = 9;
            }
        }

        sum += first * 10 + last;
    }
    cout << sum << endl;
}