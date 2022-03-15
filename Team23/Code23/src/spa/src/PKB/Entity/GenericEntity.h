#pragma once

#include<stdio.h>
#include <unordered_set>

//#include "PKB/PKBHelper.h"

using namespace std;


template<class T>
class GenericEntity {


private:
    unordered_set<T> set;

    bool isEntityNormal(T element) {
        return set.find(element) != set.end();
    }

public:

    GenericEntity() {

    }


    void add(T element) {

        set.insert(element);
    }

    unordered_set<string> getAll() {
        return convertSetGenericToSetStrings(set);
    }

    unordered_set<T> getAllNormal() {
        return set;
    }


    bool isEntity(string element) {
        T t;
        return isEntityNormal(convert(element, t));
    }

    T convert(string s, T&);





    void clear() {
        set.clear();
    }


};


template<>
string GenericEntity<string>::convert(string s, string&) {
    return s;
}

template<>
int GenericEntity<int>::convert(string s, int&) {
    return std::stoi(s);
}

