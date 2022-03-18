//
// Created by Tianyi Wang on 12/3/22.
//

#include "QP_Evaluator/ClauseEvaluators/ResultClauseEvaluator.h"
#include "TestUtilities.h"
#include <utility>
#include "catch.hpp"

using namespace std;

void resetSampleResultTable(ResultTable* resultTable) {
    resultTable->clearTable();
    resultTable->setResultTable({"v", "s", "a", "pn"},
                           {{"x", "y", "z"},{"1", "2", "3"}, {"2", "2", "3"}, {"4", "11", "4"}});
}

ResultSet evaluateResultClause(ResultTable* resultTable, Query *query, PKB *testPKB) {
    auto *resultClauseEvaluator = new ResultClauseEvaluator(testPKB, query);
    resultClauseEvaluator->evaluateClause(resultTable);
    delete resultClauseEvaluator;
    return generateResultSet(QueryEvaluator::generateResultString(resultTable));
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
    Query query_0 = makeQuery(declarations, {
            Argument{ArgumentType::BOOLEAN, ""},
    });

    auto *resultTable = new ResultTable();
    SECTION("select single") {
        resetSampleResultTable(resultTable);
        REQUIRE(evaluateResultClause(resultTable, &query_1, testPKB) == ResultSet{"x", "y", "z"});

        resetSampleResultTable(resultTable);
        REQUIRE(evaluateResultClause(resultTable, &query_2, testPKB)  == ResultSet{"1", "2", "3"});
    }

    SECTION("select boolean") {
        resultTable->clearTable();
        REQUIRE(evaluateResultClause(resultTable, &query_0, testPKB) == ResultSet{"TRUE"});

        resultTable->clearTable();
        resultTable->setBooleanResult(false);
        REQUIRE(evaluateResultClause(resultTable, &query_0, testPKB) == ResultSet{"FALSE"});
    }
    delete resultTable;
}

TEST_CASE("Test tuple results") {
    PKB *testPKB = generateSamplePKB();
    unordered_map<string, DesignEntity> declarations = {{"v", DesignEntity::VARIABLE},
                                                        {"a", DesignEntity::ASSIGN},
                                                        {"pn", DesignEntity::PRINT},
                                                        {"s", DesignEntity::STMT},
                                                        {"r", DesignEntity::READ},
                                                        {"c", DesignEntity::CALL}
    };
    Query query_1 = makeQuery(declarations, {
            Argument{ArgumentType::SYNONYM, "s"},
            Argument{ArgumentType::SYNONYM, "a"},
    });

    Query query_2 = makeQuery(declarations, {
            Argument{ArgumentType::SYNONYM, "s"},
            Argument{ArgumentType::ATTR_REF, make_pair("pn", AttrName::VAR_NAME)},
    });

    Query query_3 = makeQuery(declarations, {
            Argument{ArgumentType::SYNONYM, "pn"},
            Argument{ArgumentType::ATTR_REF, make_pair("pn", AttrName::VAR_NAME)},
    });

    Query query_4 = makeQuery(declarations, {
            Argument{ArgumentType::SYNONYM, "a"},
            Argument{ArgumentType::ATTR_REF, make_pair("a", AttrName::STMT_NO)},
    });

    Query query_5 = makeQuery(declarations, {
            Argument{ArgumentType::SYNONYM, "a"},
            Argument{ArgumentType::ATTR_REF, make_pair("a", AttrName::STMT_NO)},
            Argument{ArgumentType::ATTR_REF, make_pair("a", AttrName::STMT_NO)},
    });

    Query query_6 = makeQuery(declarations, {
            Argument{ArgumentType::SYNONYM, "s"},
            Argument{ArgumentType::ATTR_REF, make_pair("pn", AttrName::VAR_NAME)},
            Argument{ArgumentType::ATTR_REF, make_pair("pn", AttrName::VAR_NAME)},
            Argument{ArgumentType::SYNONYM, "pn"},
    });

    Query query_7 = makeQuery(declarations, {
            Argument{ArgumentType::SYNONYM, "pn"},
            Argument{ArgumentType::SYNONYM, "r"},
            Argument{ArgumentType::SYNONYM, "r"},
            Argument{ArgumentType::ATTR_REF, make_pair("pn", AttrName::VAR_NAME)},
            Argument{ArgumentType::ATTR_REF, make_pair("r", AttrName::VAR_NAME)},
    });

    Query query_8 = makeQuery(declarations, {
            Argument{ArgumentType::ATTR_REF, make_pair("r", AttrName::VAR_NAME)},
            Argument{ArgumentType::ATTR_REF, make_pair("pn", AttrName::VAR_NAME)},
            Argument{ArgumentType::SYNONYM, "pn"},
            Argument{ArgumentType::SYNONYM, "a"},
            Argument{ArgumentType::SYNONYM, "r"},
    });

    Query query_9 = makeQuery(declarations, {
            Argument{ArgumentType::ATTR_REF, make_pair("r", AttrName::VAR_NAME)},
            Argument{ArgumentType::ATTR_REF, make_pair("pn", AttrName::VAR_NAME)},
            Argument{ArgumentType::ATTR_REF, make_pair("c", AttrName::PROC_NAME)},
    });

    Query query_10 = makeQuery(declarations, {
            Argument{ArgumentType::SYNONYM, "a"},
            Argument{ArgumentType::ATTR_REF, make_pair("v", AttrName::VAR_NAME)},
    });

    auto *resultTable = new ResultTable();
    SECTION("select tuples") {
        /**
         * Select s,a
         */
        resetSampleResultTable(resultTable);
        REQUIRE(evaluateResultClause(resultTable, &query_1, testPKB) == ResultSet{"1 2", "2 2", "3 3"});
    }

    SECTION("select attrRef") {
        /**
         * Select s,pn.varName
         */
        resetSampleResultTable(resultTable);
        REQUIRE(evaluateResultClause(resultTable, &query_2, testPKB) ==
                ResultSet{"1 z", "2 x", "3 z"});

        /**
         * Select pn,pn.varName
         */
        resetSampleResultTable(resultTable);
        REQUIRE(evaluateResultClause(resultTable, &query_3, testPKB) ==
                ResultSet{"4 z", "11 x"});

        /**
         * Select a,a.stmt#
         */
        resetSampleResultTable(resultTable);
        REQUIRE(evaluateResultClause(resultTable, &query_4, testPKB) ==
                ResultSet{"2 2", "3 3"});

        /**
         * Select a,a.stmt#,a.stmt#
         */
        resetSampleResultTable(resultTable);
        REQUIRE(evaluateResultClause(resultTable, &query_5, testPKB) ==
                ResultSet{"2 2 2", "3 3 3"});

        /**
         * Select s,pn.varName,pn.varName,pn
         */
        resetSampleResultTable(resultTable);
        REQUIRE(evaluateResultClause(resultTable, &query_6, testPKB) ==
                ResultSet{"1 z z 4", "2 x x 11", "3 z z 4"});

        /**
         * Select pn, r, r, pn.varName, r.varName
         */
        resetSampleResultTable(resultTable);
        REQUIRE(evaluateResultClause(resultTable, &query_7, testPKB) ==
        ResultSet{"4 1 1 z x", "11 1 1 x x"});

        /**
         * Select r.varName, pn.varName, pn, a, r
         */
        resetSampleResultTable(resultTable);
        REQUIRE(evaluateResultClause(resultTable, &query_8, testPKB) ==
        ResultSet{"x z 4 2 1",
                  "x x 11 2 1",
                  "x z 4 3 1"});
    }

    SECTION("select from empty result table") {
        /**
         * Select <r.varName, pn.varName, cl.procName>
         */
        resultTable->clearTable();
        REQUIRE(evaluateResultClause(resultTable, &query_9, testPKB) == ResultSet{"x x pr", "x z pr"});

        /**
         * Select <a,v.varName>
         */
        resultTable->clearTable();
        REQUIRE(evaluateResultClause(resultTable, &query_10, testPKB) == ResultSet{
                "9 x", "2 x", "3 y", "10 x", "9 y", "9 z", "8 x", "3 z", "3 x", "10 y", "8 z", "10 z", "2 y", "8 y", "2 z"
        });
    }
    delete resultTable;
}