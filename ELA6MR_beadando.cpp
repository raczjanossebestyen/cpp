#include <iostream>
#include <list>

struct Character {
    char id;
    int num;
};

std::list<Character> bag(std::string input) {
    std::list<Character> chars;
    for(int i = 0; i <input.length(); i++) {
        bool flag = true;
        for(struct Character &c : chars) {
            if(c.id == input[i]) {
                c.num++;
                flag = false;
                break;
            }
        }
        if(flag) {
            struct Character c;
            c.id = input[i];
            c.num = 1;
            chars.push_back(c);
        }
    }
    return chars;
}

bool isValid(std::list<Character> chars) {
    bool flag = false;
    int first = chars.front().num;
    chars.erase(chars.begin());
    for(struct Character y : chars) {
        if(y.num == first) {}
        else {
            if(first == 1 && chars.front().num == 2) {
                chars.erase(chars.begin());
                if(chars.front().num == 1) {
                flag = true;
                }
            }
            else if(first == 2 && chars.front().num == 1) {
                chars.erase(chars.begin());
                if(chars.front().num == 2) {
                flag = true;
                }
            }
            else if((first == 1 || y.num == first - 1) && y.id == chars.front().id && !flag) {
                first = y.num;
                flag = true;
            }
            else if((y.num == first+1 || y.num == 1) && !flag) {
                flag = true;
            }
            else {
                return false;
            }
        }
    }
    return true;

}

int main(int argc, char *args[]) {
    std::list<Character> chars = bag(args[1]);
    if(isValid(chars)) {
        std::cout<< "Valid"<<std::endl;
    }
    else {
        std::cout<< "Invalid"<<std::endl;
    }
}