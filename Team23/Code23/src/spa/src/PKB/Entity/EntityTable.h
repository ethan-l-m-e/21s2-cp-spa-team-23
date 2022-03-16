#pragma once

#include<stdio.h>
#include <unordered_set>

#include "PKB/PKBHelper.h"

using namespace std;


template<class T>
class EntityTable {


private:
    unordered_set<T> set;

    bool isEntityNormal(T element) {
        return set.find(element) != set.end();
    }

public:

    EntityTable() {

    }


    void add(T element) {

        set.insert(element);
    }

    unordered_set<string> getAll() {
        return convertSetGenericsToSetStrings(set);
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


template<> inline string EntityTable<string>::convert(string s, string&) {
    return s;
}

template<> inline int EntityTable<int>::convert(string s, int&) {
    return std::stoi(s);
}

