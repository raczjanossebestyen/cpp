#ifndef LIST_VIEW
#define LIST_VIEW

#include <list>
#include <map>
#include <vector>
#include <iterator>
#include <functional>
#include <algorithm>


template<class T, class Comp>
class array_view
{

	protected:
    std::list<T>& list;
	Comp vec;

    public:

    array_view(std::list<T>& list2) : list(list2){
    	
        for(typename std::list<T>::iterator i = list2.begin(); i != list2.end(); ++i){
            vec.push_back(i);
        }
    };

    void push_back(const T& t){
        list.push_back(t);
        vec.push_back(--list.end()); //4-es�rt az rbegin() nem volt j� mert reverseiteratort adott
    }

    T& at(int idx){
        return *vec.at(idx);
    }

    const T& at(int idx) const{       
        return *vec.at(idx);
    }
    
    //3-as
    T& operator[](int idx){
        return *vec.at(idx);
    }

    const T& operator[](int idx) const{       
        return *vec.at(idx);
    }

};

//4-es
//5-�s�rt alap template param�ter is kell

template <class T, class param = std::less<T>() >
struct Compare {
    bool operator()(typename std::list<T>::iterator a, typename std::list<T>::iterator b) {
        return *a < *b; // A k�t iter�tor �ltal mutatott elemek �sszehasonl�t�sa
    }
};

// Specializ�ljuk a Compare-t std::greater<T> t�pusra
template <class T>
struct Compare<T, std::greater<T> > {
    bool operator()(typename std::list<T>::iterator a, typename std::list<T>::iterator b) {
        return *a > *b;  // Ha std::greater<T> van, akkor cs�kken� rendez�s
    }
};

template<class T, class Comp = std::vector<typename std::list<T>::iterator> > //m�g a space is sz�m�t a v�g�n a 2 > jel k�z�tt
class vector_view : public array_view<T, Comp> {
	
	public:
		vector_view(std::list<T>& list2) : array_view<T, Comp>(list2) {};
		
		//5-�s
		void sort(){
			std::sort( this->vec.begin(), this->vec.end(), Compare<T>() );
		}
		
		void sort(std::greater<T> param){
			std::sort( this->vec.begin(), this->vec.end(), Compare<T, std::greater<T> >() );
		}
};





#endif
