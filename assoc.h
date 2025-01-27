#ifndef ASSOC
#define ASSOC

#include <list>
#include <map>
#include <vector>
#include <iterator>
#include <functional>
#include <algorithm>
#include <complex>
#include <iostream>

/*
template <typename T, typename U>
struct isSame { 
    static const bool value = false; 
};

template <typename T>
struct isSame<T, T> { 
    static const bool value = true; 
};
*/

template <class T, class U>
struct Compare {
	bool operator()(const T& lhs, const T& rhs) const {
        return std::less<T>()(lhs, rhs); 
    }
};
/*
template <class T>
struct Compare<T, T> {
	bool operator()(const std::complex<int>& lhs, const std::complex<int>& rhs) const {
        // A komplex sz�mokat a val�s r�szek �s ha azok egyenl�k, a k�pzetes r�szek szerint hasonl�tjuk �ssze
        if (lhs.real() != rhs.real()) {
            return lhs.real() < rhs.real();
        }
        return lhs.imag() < rhs.imag();
    }
};*/

template <>
struct Compare<std::complex<int>, std::complex<int>> {
    bool operator()(const std::complex<int>& lhs, const std::complex<int>& rhs) const {
        // Komplex számok összehasonlítása: először a valós rész, ha azok egyenlőek, akkor a képzetes rész
        if (lhs.real() != rhs.real()) {
            return lhs.real() < rhs.real();
        }
        return lhs.imag() < rhs.imag();
    }
};


template<class K, class Container, class T = int, class Comp = std::less<K> > //T t�pus, K kulcs
class association{
	
	Container& cont;	
	
	std::map<K, typename Container::iterator, Compare<K, std::complex<int> > > map;
	
	public:
		association(Container& Cont) : cont(Cont){
			
		}	
		
		void associate(K key, typename Container::iterator it){			
			map[key] = it;
		}
		
		T& find(K key){
			if(map.find(key) == map.end()){
				T t;
				//std::cout<< "blabla";
				cont.push_back(t);
				map[key] = --cont.end();
			}
			//bool b = 5 == 5;//map.find(key) == --map.end();
			//std::cout << b;
			return *map[key];	
		}
		
		const T& find(K key) const{				
			if(map.find(key) == map.end()){
				//std::cout<< "blabla";
				T t;
				cont.push_back(t);
				map[key] = --cont.end();
			}
			return *map[key];
		}
		
		T& operator[](K key){
			if(map.find(key) == map.end()){
				//std::cout<< "blabla";
				T t;
				cont.push_back(t);
				map[key] = --cont.end();
			}
			return *map[key];
		}
		
		const T& operator[](K key) const{
			return *map[key];
		}
		
		bool has(K key){			
			return map.find(key) != map.end() ? true : false;	
		}
		
		int size(){
			return map.size();
		}

		const int size() const{
			return map.size();
		}
};


#endif
