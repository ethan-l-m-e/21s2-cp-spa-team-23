#include "EntityTable.h"

EntityTable::EntityTable() {

}


void EntityTable::add(string element) {

    set.insert(element);
}

unordered_set<string> EntityTable::getAll() {
    return set;
}

bool EntityTable::isEntity(string element) {
    return set.find(element) != set.end();
}


void EntityTable::clear() {
    set.clear();
}




