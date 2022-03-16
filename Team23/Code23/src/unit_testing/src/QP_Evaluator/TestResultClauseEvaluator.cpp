//
// Created by Tianyi Wang on 12/3/22.
//

#include "QP_Evaluator/ClauseEvaluators/ResultClauseEvaluator.h"
#include "TestUtilities.h"
#include <utility>
#include "catch.hpp"

using namespace std;

ResultTable* getSampleResultTable() {
    return new ResultTable({"v", "s", "a", "pn"},
                           {{"x", "y", "z"},{"1", "2", "3"}, {"2", "2", "3"}, {"4", "11", "4"}});
}

TEST_CASE("Test result clause evaluator") {
    PKB *testPKB = generateSamplePKB();
    unordered_map<string, DesignEntity> declarations = {{"v", DesignEntity::VARIABLE},
                                                        {"a", DesignEntity::ASSIGN},
                                                        {"pn", DesignEntity::PRINT},
                                                        {"s", DesignEntity::STMT}
    };
    Query query_1 = makeQuery(declarations, {Argument{ArgumentType::ATTR_REF, make_pair("v", AttrName::VALUE)}});
    Query query_2 = makeQuery(declarations, {Argument{ArgumentType::ATTR_REF, make_pair("s", AttrName::VALUE)}});
    Query query_3 = makeQuery(declarations, {
        Argument{ArgumentType::ATTR_REF, make_pair("s", AttrName::VALUE)},
        Argument{ArgumentType::ATTR_REF, make_pair("a", AttrName::VALUE)},
        });

    Query query_4 = makeQuery(declarations, {
            Argument{ArgumentType::ATTR_REF, make_pair("s", AttrName::VALUE)},
            Argument{ArgumentType::ATTR_REF, make_pair("pn", AttrName::VAR_NAME)},
    });

    Query query_5 = makeQuery(declarations, {
            Argument{ArgumentType::ATTR_REF, make_pair("pn", AttrName::VALUE)},
            Argument{ArgumentType::ATTR_REF, make_pair("pn", AttrName::VAR_NAME)},
    });

    Query query_6 = makeQuery(declarations, {
            Argument{ArgumentType::BOOLEAN, ""},
    });

    SECTION("select single") {
        auto *resultTable = getSampleResultTable();
        auto *resultClauseEvaluator = new ResultClauseEvaluator(testPKB, &query_1);
        resultClauseEvaluator->evaluateClause(resultTable);
        delete resultClauseEvaluator;
        REQUIRE(generateResultSet(QueryEvaluator::generateResultString(resultTable)) == ResultSet{"x", "y", "z"});

        resultTable = getSampleResultTable();
        resultClauseEvaluator = new ResultClauseEvaluator(testPKB, &query_2);
        resultClauseEvaluator->evaluateClause(resultTable);
        delete resultClauseEvaluator;
        REQUIRE(generateResultSet(QueryEvaluator::generateResultString(resultTable)) == ResultSet{"1", "2", "3"});
    }

    SECTION("select tuples") {
        auto *resultTable = getSampleResultTable();
        auto *resultClauseEvaluator = new ResultClauseEvaluator(testPKB, &query_3);
        resultClauseEvaluator->evaluateClause(resultTable);
        delete resultClauseEvaluator;
        REQUIRE(generateResultSet(QueryEvaluator::generateResultString(resultTable)) == ResultSet{"1 2", "2 2", "3 3"});
    }

    SECTION("select attrRef") {
        auto *resultTable = getSampleResultTable();
        auto *resultClauseEvaluator = new ResultClauseEvaluator(testPKB, &query_4);
        resultClauseEvaluator->evaluateClause(resultTable);
        delete resultClauseEvaluator;
        REQUIRE(generateResultSet(QueryEvaluator::generateResultString(resultTable)) ==
                ResultSet{"1 y", "2 x", "3 y"});

        resultTable = getSampleResultTable();
        resultClauseEvaluator = new ResultClauseEvaluator(testPKB, &query_5);
        resultClauseEvaluator->evaluateClause(resultTable);
        delete resultClauseEvaluator;
        REQUIRE(generateResultSet(QueryEvaluator::generateResultString(resultTable)) ==
                ResultSet{"4 y", "11 x"});
    }

    SECTION("select boolean") {
        auto *resultTable = getSampleResultTable();
        auto *resultClauseEvaluator = new ResultClauseEvaluator(testPKB, &query_6);
        resultClauseEvaluator->evaluateClause(resultTable);
        delete resultClauseEvaluator;
        REQUIRE(generateResultSet(QueryEvaluator::generateResultString(resultTable)) == ResultSet{"TRUE"});

        resultTable = new ResultTable();
        resultTable->setBooleanResult(false);
        resultClauseEvaluator = new ResultClauseEvaluator(testPKB, &query_6);
        resultClauseEvaluator->evaluateClause(resultTable);
        delete resultClauseEvaluator;
        REQUIRE(generateResultSet(QueryEvaluator::generateResultString(resultTable)) == ResultSet{"FALSE"});

    }
}