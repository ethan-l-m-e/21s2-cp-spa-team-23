//
// Created by Karan Dev Sapra on 17/2/22.
//


#include "Cache/Cache.h"

#include "TNode/TNode.h"

#include "QP_Evaluator/TestUtilities.h"

#include "catch.hpp"

using namespace std;

Cache *cache = Cache::getInstance();

TEST_CASE("can do yourself lol") {
    cache->clearCache();

    cache->relationship.affects->setRelationship("1","2");

}