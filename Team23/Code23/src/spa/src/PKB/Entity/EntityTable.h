#ifndef SPA_ENTITYTABLE_H
#define SPA_ENTITYTABLE_H

#include <stdio.h>
#include <unordered_set>
#include <string>

using namespace std;

class EntityTable {

private:
    unordered_set<string> set;
public:
    EntityTable();
    void add(string element);
    unordered_set<string> getAll();
    bool isEntity(string element);
    void clear();

};

#endif //SPA_ENTITYTABLE_H
