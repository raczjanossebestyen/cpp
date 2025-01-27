#ifndef PSTACK__H
#define PSTACK__H

#include <functional>
#include <map>
#include <stack>

template<class T,  class Pr = int, class Comp = std::less<Pr> > 
class priority_stack {

    typedef std::map<Pr, std::stack<T>, Comp> prs;
    prs ps;

    public:

    void push(const Pr& p, const T& t) {
        ps[ p ].push( t );
    }

    int size(const Pr& p) const{
        //ps[ p ].size(); ellentmond a const indexelesenek mert ha p nincs a mapben akkor megvaltoztatna a const-ot
        return ps.find(p) ->second.size(); // a find ey map iteratort ad, annak a masodik tagja kell ami a stack. ennek a stacknak adjuk vissza a meretet
    }

    T& top() {
        return ps.rbegin() -> second.top(); //rbegin: utolso valid elem, az end iterator az utolso utanira
    }

    const T& top() const{
        return ps.rbegin() -> second.top();
    }

    int size() const {
        int ret= 0;
        for(typename prs::const_iterator i = ps.begin(); i!= ps.end(); ++i) {
            ret += i -> second.size();
        }
        return ret;
    }

    void pop() {
        //ps.rbegin()->second.pop(); onmagaban nem nem jo mert maradhat ures prioritas bizonyos esetekben
        const Pr& p = ps.rbegin()->first;
        ps.rbegin()->second.pop();
        if( ps.begin()->second.empty()) {
        ps.erase( p );
        }
    }

};


#endif