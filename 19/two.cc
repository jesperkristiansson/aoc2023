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

using namespace std;

//index to array of parts in items
enum item_part{
    X = 0,
    M,
    A,
    S
};

struct rule{
    enum item_part part;
    bool unconditional;
    bool less_than; //true if operand is <, false if operand is >
    int operand_val;
    string target;
};

typedef vector<rule> workflow;

struct range{
    // these are inclusive
    int start, end;

    int len() const{
        return end - start + 1;
    }
};

long long getSuccessfulCombinations(const map<string, workflow> &workflows, const string &current, std::vector<range> ranges){
    long long totalCombinations = (long long)ranges[X].len() * ranges[M].len() * ranges[A].len() * ranges[S].len();
    if(current == "A"){
        return totalCombinations;
    }

    if(current == "R"){
        return 0;
    }

    auto it = workflows.find(current);
    if(it == workflows.end()){
        //panic
        return -1;
    }
    const workflow &wf = it->second;

    if(totalCombinations <= 0){
        cout << "no possible combinations left" << endl;
        return 0;
    }

    long long successfulCombinations = 0;
    for(rule r : wf){
        if(r.unconditional){
            successfulCombinations += getSuccessfulCombinations(workflows, r.target, ranges);
        } else if(r.less_than){
            auto rangesLower = ranges;
            rangesLower[r.part].end = r.operand_val-1;
            auto rangesUpper = ranges;
            rangesUpper[r.part].start = r.operand_val;

            successfulCombinations += getSuccessfulCombinations(workflows, r.target, rangesLower);
            ranges = rangesUpper;
        } else{
            auto rangesLower = ranges;
            rangesLower[r.part].end = r.operand_val;
            auto rangesUpper = ranges;
            rangesUpper[r.part].start = r.operand_val+1;

            successfulCombinations += getSuccessfulCombinations(workflows, r.target, rangesUpper);
            ranges = rangesLower;
        }
    }

    return successfulCombinations;
}

long long getSuccessfulCombinations(const map<string, workflow> &workflows){
    vector<range> initialRanges(4);
    initialRanges[item_part::X] = {.start = 1, .end = 4000};
    initialRanges[item_part::M] = {.start = 1, .end = 4000};
    initialRanges[item_part::A] = {.start = 1, .end = 4000};
    initialRanges[item_part::S] = {.start = 1, .end = 4000};
    return getSuccessfulCombinations(workflows, "in", initialRanges);
}

int main(){
    map<string, workflow> workflows;

    //create workflows
    while(true){
        string line;
        getline(cin, line);
        if(line == ""){
            break;
        }

        auto name_end_i = line.find('{');
        string name = line.substr(0, name_end_i);

        workflow wf;
        auto index = name_end_i + 1;
        while(index < line.length()){
            auto rule_end_i = line.find_first_of(",}", index);
            string rule_str = line.substr(index, rule_end_i - index);

            rule r;
            auto colon_i = rule_str.find_first_of(':');
            r.unconditional = colon_i == string::npos;
            if(r.unconditional){
                r.target = rule_str;
            } else {
                switch(rule_str[0]){
                    case 'x':
                        r.part = X;
                        break;
                    case 'm':
                        r.part = M;
                        break;
                    case 'a':
                        r.part = A;
                        break;
                    case 's':
                        r.part = S;
                        break;
                }
                r.less_than = rule_str[1] == '<';
                r.operand_val = stoi(rule_str.substr(2, colon_i - 2));
                r.target = rule_str.substr(colon_i+1);
            }

            wf.push_back(r);
            index = rule_end_i + 1;
        }

        workflows.insert({name, wf});
    }
    //ignore rest of input(items)

    long long total = getSuccessfulCombinations(workflows);

    cout << total << endl;
}