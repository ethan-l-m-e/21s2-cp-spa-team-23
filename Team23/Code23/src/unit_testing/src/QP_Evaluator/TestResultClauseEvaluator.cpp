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

TEST_CASE("Test single") {
    PKB *testPKB = generateSamplePKB();
    unordered_map<string, DesignEntity> declarations = {{"v", DesignEntity::VARIABLE},
                                                        {"a", DesignEntity::ASSIGN},
                                                        {"pn", DesignEntity::PRINT},
                                                        {"s", DesignEntity::STMT}
    };
    Query query_1 = makeQuery(declarations, {Argument{ArgumentType::SYNONYM, "v"}});
    Query query_2 = makeQuery(declarations, {Argument{ArgumentType::SYNONYM, "s"}});
    Query query_3 = makeQuery(declarations, {
        Argument{ArgumentType::SYNONYM, "s"},
        Argument{ArgumentType::SYNONYM, "a"},
        });

    Query query_4 = makeQuery(declarations, {
            Argument{ArgumentType::SYNONYM, "s"},
            Argument{ArgumentType::ATTR_REF, make_pair("pn", AttrName::VAR_NAME)},
    });

    Query query_5 = makeQuery(declarations, {
            Argument{ArgumentType::SYNONYM, "pn"},
            Argument{ArgumentType::ATTR_REF, make_pair("pn", AttrName::VAR_NAME)},
    });

    Query query_6 = makeQuery(declarations, {
            Argument{ArgumentType::SYNONYM, "a"},
            Argument{ArgumentType::ATTR_REF, make_pair("a", AttrName::STMT_NO)},
    });

    Query query_0 = makeQuery(declarations, {
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

    SECTION("select boolean") {
        auto *resultTable = getSampleResultTable();
        auto *resultClauseEvaluator = new ResultClauseEvaluator(testPKB, &query_0);
        resultClauseEvaluator->evaluateClause(resultTable);
        delete resultClauseEvaluator;
        REQUIRE(generateResultSet(QueryEvaluator::generateResultString(resultTable)) == ResultSet{"TRUE"});

        resultTable = new ResultTable();
        resultTable->setBooleanResult(false);
        resultClauseEvaluator = new ResultClauseEvaluator(testPKB, &query_0);
        resultClauseEvaluator->evaluateClause(resultTable);
        delete resultClauseEvaluator;
        REQUIRE(generateResultSet(QueryEvaluator::generateResultString(resultTable)) == ResultSet{"FALSE"});

    }
}

TEST_CASE("Test tuple results") {

    PKB *testPKB = generateSamplePKB();
    unordered_map<string, DesignEntity> declarations = {{"v", DesignEntity::VARIABLE},
                                                        {"a", DesignEntity::ASSIGN},
                                                        {"pn", DesignEntity::PRINT},
                                                        {"s", DesignEntity::STMT},
                                                        {"r", DesignEntity::READ}
    };
    Query query_3 = makeQuery(declarations, {
            Argument{ArgumentType::SYNONYM, "s"},
            Argument{ArgumentType::SYNONYM, "a"},
    });

    Query query_4 = makeQuery(declarations, {
            Argument{ArgumentType::SYNONYM, "s"},
            Argument{ArgumentType::ATTR_REF, make_pair("pn", AttrName::VAR_NAME)},
    });

    Query query_5 = makeQuery(declarations, {
            Argument{ArgumentType::SYNONYM, "pn"},
            Argument{ArgumentType::ATTR_REF, make_pair("pn", AttrName::VAR_NAME)},
    });

    Query query_6 = makeQuery(declarations, {
            Argument{ArgumentType::SYNONYM, "a"},
            Argument{ArgumentType::ATTR_REF, make_pair("a", AttrName::STMT_NO)},
    });

    Query query_7 = makeQuery(declarations, {
            Argument{ArgumentType::SYNONYM, "a"},
            Argument{ArgumentType::ATTR_REF, make_pair("a", AttrName::STMT_NO)},
            Argument{ArgumentType::ATTR_REF, make_pair("a", AttrName::STMT_NO)},
    });

    Query query_8 = makeQuery(declarations, {
            Argument{ArgumentType::SYNONYM, "s"},
            Argument{ArgumentType::ATTR_REF, make_pair("pn", AttrName::VAR_NAME)},
            Argument{ArgumentType::ATTR_REF, make_pair("pn", AttrName::VAR_NAME)},
            Argument{ArgumentType::SYNONYM, "pn"},
    });

    Query query_9 = makeQuery(declarations, {
            Argument{ArgumentType::SYNONYM, "pn"},
            Argument{ArgumentType::SYNONYM, "r"},
            Argument{ArgumentType::SYNONYM, "r"},
            Argument{ArgumentType::ATTR_REF, make_pair("pn", AttrName::VAR_NAME)},
            Argument{ArgumentType::ATTR_REF, make_pair("r", AttrName::VAR_NAME)},
    });

    Query query_10 = makeQuery(declarations, {
            Argument{ArgumentType::ATTR_REF, make_pair("r", AttrName::VAR_NAME)},
            Argument{ArgumentType::ATTR_REF, make_pair("pn", AttrName::VAR_NAME)},
            Argument{ArgumentType::SYNONYM, "pn"},
            Argument{ArgumentType::SYNONYM, "a"},
            Argument{ArgumentType::SYNONYM, "r"},
    });


    SECTION("select tuples") {
        /**
         * Select s,a
         */
        auto *resultTable = getSampleResultTable();
        auto *resultClauseEvaluator = new ResultClauseEvaluator(testPKB, &query_3);
        resultClauseEvaluator->evaluateClause(resultTable);
        delete resultClauseEvaluator;
        REQUIRE(generateResultSet(QueryEvaluator::generateResultString(resultTable)) == ResultSet{"1 2", "2 2", "3 3"});
    }

    SECTION("select attrRef") {
        /**
         * Select s,pn.varName
         */
        auto *resultTable = getSampleResultTable();
        auto *resultClauseEvaluator = new ResultClauseEvaluator(testPKB, &query_4);
        resultClauseEvaluator->evaluateClause(resultTable);
        delete resultClauseEvaluator;
        REQUIRE(generateResultSet(QueryEvaluator::generateResultString(resultTable)) ==
                ResultSet{"1 z", "2 x", "3 z"});

        /**
         * Select pn,pn.varName
         */
        resultTable = getSampleResultTable();
        resultClauseEvaluator = new ResultClauseEvaluator(testPKB, &query_5);
        resultClauseEvaluator->evaluateClause(resultTable);
        delete resultClauseEvaluator;
        REQUIRE(generateResultSet(QueryEvaluator::generateResultString(resultTable)) ==
                ResultSet{"4 z", "11 x"});

        /**
         * Select a,a.stmt#
         */
        resultTable = getSampleResultTable();
        resultClauseEvaluator = new ResultClauseEvaluator(testPKB, &query_6);
        resultClauseEvaluator->evaluateClause(resultTable);
        delete resultClauseEvaluator;
        REQUIRE(generateResultSet(QueryEvaluator::generateResultString(resultTable)) ==
                ResultSet{"2 2", "3 3"});

        /**
         * Select a,a.stmt#,a.stmt#
         */
        resultTable = getSampleResultTable();
        resultClauseEvaluator = new ResultClauseEvaluator(testPKB, &query_7);
        resultClauseEvaluator->evaluateClause(resultTable);
        delete resultClauseEvaluator;
        REQUIRE(generateResultSet(QueryEvaluator::generateResultString(resultTable)) ==
                ResultSet{"2 2 2", "3 3 3"});

        /**
         * Select s,pn.varName,pn.varName,pn
         */
        resultTable = getSampleResultTable();
        resultClauseEvaluator = new ResultClauseEvaluator(testPKB, &query_8);
        resultClauseEvaluator->evaluateClause(resultTable);
        delete resultClauseEvaluator;
        REQUIRE(generateResultSet(QueryEvaluator::generateResultString(resultTable)) ==
                ResultSet{"1 z z 4", "2 x x 11", "3 z z 4"});

        /**
         * Select pn, r, r, pn.varName, r.varName
         */
        resultTable = getSampleResultTable();
        resultClauseEvaluator = new ResultClauseEvaluator(testPKB, &query_9);
        resultClauseEvaluator->evaluateClause(resultTable);
        delete resultClauseEvaluator;
        REQUIRE(generateResultSet(QueryEvaluator::generateResultString(resultTable)) ==
        ResultSet{"4 1 1 z x", "11 1 1 x x"});


        /**
         * Select r.varName, pn.varName, pn, a, r
         */
        resultTable = getSampleResultTable();
        resultClauseEvaluator = new ResultClauseEvaluator(testPKB, &query_10);
        resultClauseEvaluator->evaluateClause(resultTable);
        delete resultClauseEvaluator;
        REQUIRE(generateResultSet(QueryEvaluator::generateResultString(resultTable)) ==
        ResultSet{"x z 4 2 1",
                  "x x 11 2 1",
                  "x z 4 3 1"});
    }
}