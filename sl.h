#ifndef SL__H
#define SL__H

#include <functional>
#include <list> 
#include <algorithm>

template<class T,  class Comp = std::less<T> > //comp a rendezesi kriterium
class SortedList {
    std::list<T> c;
public:

typedef typename std::list<T>::const_iterator iterator;

//copy def ctor jo
//default ctror jo

template<class Iterator>
SortedList(Iterator first, Iterator last) : c(first, last) {
    c.sort(Comp());
}

SortedList() { }

void insert(const T& t) {
    c.insert(
        std::lower_bound( c.begin(), c.end(), t, Comp()), //t-vel megegyezo elemeknek hol kene kezdodnie egy rendezett intervallumban. A comp parameter egz overload hivas miatt van benne
    t);
}

int size() const{
    return c.size(); 
}

const T& front() const {
    return c.front();
}

void remove(const T& t) {
//    c.remove(t); //ez egyenlosegvizsgalattal keresi meg t-t, de nekunk a rendezes szerint kell
    std::pair<typename std::list<T>::iterator,
              typename std::list<T>::iterator> p =
                std::equal_range( c.begin(), c.end(), t, Comp() ); //megadja a t-vel egyezo intervallumot, elso a lowerbount, masodik ay upperbount
    c.erase( p.first, p.second ); // ez a megoldas azert jobb mert az osses kivalasztott ertekut torli
}



const T& back() const {
    return c.back();
}

iterator begin() const{
    return c.begin(); //kell egy iterator, de azt ne lehessen modositani
}

iterator end() const{
    return c.end();
}

};

#endif