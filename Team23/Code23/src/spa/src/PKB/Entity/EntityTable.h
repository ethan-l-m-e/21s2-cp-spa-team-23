#pragma once

#include<stdio.h>
#include <unordered_set>

#include "PKB/PKBHelper.h"

using namespace std;



class EntityTable {


private:
    unordered_set<string> set;

public:

    EntityTable() {

    }


    void add(string element) {

        set.insert(element);
    }

    unordered_set<string> getAll() {
        return set;
    }

    bool isEntity(string element) {
        return set.find(element) != set.end();
    }


    void clear() {
        set.clear();
    }


};


