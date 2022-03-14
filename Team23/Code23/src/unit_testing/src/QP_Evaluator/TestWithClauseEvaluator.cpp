//
// Created by Tianyi Wang on 14/3/22.
//

//#include "QP_Evaluator/ClauseEvaluators/WithClauseEvaluator.h"
#include "TestUtilities.h"
#include <utility>
#include "catch.hpp"

using namespace std;

TEST_CASE("Test with clause evaluator") {
    PKB *testPKB = generateSamplePKB();
    unordered_map<string, DesignEntity> declarations = {
            {"p", DesignEntity::PROCEDURE},
            {"v", DesignEntity::VARIABLE},
    };

    Argument a0 = {ArgumentType::UNDERSCORE, "_"};

    SuchThatClause clause_0_0 = {ArgList{a0, a0},RelRef::NEXT_T};

    Argument dummySelect = {ArgumentType::ATTR_REF, make_pair("s", AttrName::VALUE)};

    Query query_0 = makeQuery(declarations, {dummySelect}, {clause_0_0});

    SECTION("select zero synonym") {
    }

    SECTION("select one synonym") {
    }

    SECTION("select two synonyms") {
    }

    SECTION("invalid query") {
    }
}