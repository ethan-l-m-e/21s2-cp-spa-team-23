//
// Created by Karan Dev Sapra on 22/3/22.
//


#include "Cache.h"


Cache *Cache::singleton = nullptr;

Cache::Cache() {

}

Cache* Cache::getInstance() {

    if (Cache::singleton == nullptr) {
        Cache::singleton = new Cache();
    }

    return Cache::singleton;

}

void Cache::clearCache() {

    relationship.nextT->clear();
    relationship.affects->clear();
    relationship.affectsT.clear();

}