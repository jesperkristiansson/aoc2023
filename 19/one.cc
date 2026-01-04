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

struct item{
    int parts[4];   //indexed with enum item_part
};

int main(){
    map<string, workflow> workflows;
    vector<item> items;

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

    //create items
    while(!cin.eof()){
        string line;
        getline(cin, line);
        auto m_i = line.find('m');
        auto a_i = line.find('a');
        auto s_i = line.find('s');
        item i;
        i.parts[X] = stoi(line.substr(3, m_i - 4));
        i.parts[M] = stoi(line.substr(m_i + 2, a_i - m_i - 3));
        i.parts[A] = stoi(line.substr(a_i + 2, s_i - a_i - 3));
        i.parts[S] = stoi(line.substr(s_i + 2, line.size() - s_i - 3));
        items.push_back(i);
    }

    long total = 0;
    for(auto item : items){
        //send through each rule
        string current_workflow = "in";
        while(current_workflow != "A" && current_workflow != "R"){
            const workflow& wf = workflows[current_workflow];
            for(const auto& rule : wf){
                bool apply_rule;
                if(rule.unconditional){
                    apply_rule = true;
                } else{
                    int diff = item.parts[rule.part] - rule.operand_val;
                    apply_rule = (rule.less_than && diff < 0) || (!rule.less_than && diff > 0);
                }

                if(apply_rule){
                    current_workflow = rule.target;
                    break;
                }
            }
        }

        if(current_workflow == "A"){
            total += item.parts[X] + item.parts[M] + item.parts[A] + item.parts[S];
        }
    }

    cout << total << endl;
}