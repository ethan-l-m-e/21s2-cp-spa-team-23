#pragma once

#include<stdio.h>
#include <unordered_set>

#include "PKB/PKBHelper.h"

using namespace std;


template<class T>
class GenericEntity {


private:
    unordered_set<T> set;

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

    bool isEntityNormal(T element) {
        return set.find(element) != set.end();
    }
    bool isEntity(string element) {
        return isEntityNormal(static_cast<T>(element));
    }


    void clear() {
        set.clear();
    }


};

//template<class T>
//GenericEntity<T>::GenericEntity() {
//
//}



