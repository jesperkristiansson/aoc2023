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

enum hand_value{
    FIVE,
    FOUR,
    HOUSE,
    THREE,
    TWO_PAIR,
    PAIR,
    HIGH
};
struct hand{
    string cards;
    enum hand_value value;
    long bid;
};

enum hand_value get_value(string cards){
    map<char, int> count;
    for(char c : cards){
        if(count.count(c) == 0){
            count[c] = 0;
        }
        ++count[c];
    }

    bool has_three = false;
    int num_pair = 0;
    for(const auto& kv : count){
        //five
        if(kv.second == 5){
            return FIVE;
        }
        //four
        if(kv.second == 4){
            return FOUR;
        }
        if(kv.second == 3){
            has_three = true;
        }
        if(kv.second == 2){
            ++num_pair;
        }
    }

    if(has_three){
        //house
        if(num_pair == 1){
            return HOUSE;
        }
        //three
        return THREE;
    }

    //two pair
    if(num_pair == 2){
        return TWO_PAIR;
    }
    //pair
    if(num_pair == 1){
        return PAIR;
    }

    //high
    return HIGH;
}

enum hand_value best_value(string cards){
    char most_common = 'A';
    int best_cnt = 0;
    for(char c : cards){
        if(c != 'J'){
            int cnt = count(cards.begin(), cards.end(), c);
            if(cnt > best_cnt){
                best_cnt = cnt;
                most_common = c;
            }
        }
    }
    replace(cards.begin(), cards.end(), 'J', most_common);
    return get_value(cards);
}

int main(){
    vector<hand> hands;

    while(cin){
        hand hand;
        cin >> hand.cards;
        if(hand.cards == ""){
            break;
        }
        cin >> hand.bid;
        hand.value = best_value(hand.cards);
        hands.push_back(hand);
        //cout << hand.cards << ": " << hand.value << endl;
    }

    string value_order{"AKQT98765432J"};

    auto comparator = [&value_order](const hand& h1, const hand& h2){
        if(h2.value == h1.value){
            for(string::size_type i = 0; i < h1.cards.length(); i++){
                char c1 = h1.cards[i];
                char c2 = h2.cards[i];
                int pos1 = value_order.find_first_of(c1);
                int pos2 = value_order.find_first_of(c2);
                if(pos1 != pos2){
                    return pos1 > pos2;
                }
            }
        }
        return h1.value > h2.value;
    };
    sort(hands.begin(), hands.end(), comparator);
    long sum = 0;
    for(vector<hand>::size_type i = 0; i < hands.size(); ++i){
        sum += hands[i].bid * (i+1);
    }
    cout << sum << endl;
}