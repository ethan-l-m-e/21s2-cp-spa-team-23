//
// Created by Tianyi Wang on 12/3/22.
//

#include "QP_Evaluator/ClauseEvaluators/ResultClauseEvaluator.h"
#include "TestUtilities.h"
#include <utility>
#include "catch.hpp"


void resetSampleResultTable(ResultTable* resultTable) {
    resultTable->clearTable();
    resultTable->setResultTable({"v", "s", "a", "pn"},
                           {{"x", "y", "z"},{"1", "2", "3"}, {"2", "2", "3"}, {"4", "11", "4"}});
}

ResultSet evaluateResultClause(unordered_map<string, DesignEntity>* declarations, ResultTable* resultTable, Clause* clause, PKB* pkb) {
    auto *resultClauseEvaluator = new ResultClauseEvaluator(declarations, clause, pkb);
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

    Argument av = {ArgumentType::SYNONYM, "v"};
    Argument as = {ArgumentType::SYNONYM, "s"};
    Argument a0 = {ArgumentType::BOOLEAN, ""};

    ResultClause clause_v = {ArgList{av}};
    ResultClause clause_s = {ArgList{as}};
    ResultClause clause_0 = {ArgList{a0}};

    auto *resultTable = new ResultTable();
    SECTION("select single") {
        resetSampleResultTable(resultTable);
        REQUIRE(evaluateResultClause(&declarations, resultTable, &clause_v, testPKB) == ResultSet{"x", "y", "z"});

        resetSampleResultTable(resultTable);
        REQUIRE(evaluateResultClause(&declarations, resultTable, &clause_s, testPKB)  == ResultSet{"1", "2", "3"});
    }

    SECTION("select boolean") {
        resultTable->clearTable();
        REQUIRE(evaluateResultClause(&declarations, resultTable, &clause_0, testPKB) == ResultSet{"TRUE"});

        resultTable->clearTable();
        resultTable->setBooleanResult(false);
        REQUIRE(evaluateResultClause(&declarations, resultTable, &clause_0, testPKB) == ResultSet{"FALSE"});
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

    Argument aa = {ArgumentType::SYNONYM, "a"};
    Argument aa1 = {ArgumentType::ATTR_REF, make_pair("a", AttrName::STMT_NO)};
    Argument as = {ArgumentType::SYNONYM, "s"};
    Argument ar = {ArgumentType::SYNONYM, "r"};
    Argument ar1 = {ArgumentType::ATTR_REF, make_pair("r", AttrName::VAR_NAME)};
    Argument a0 = {ArgumentType::BOOLEAN, ""};
    Argument apn = {ArgumentType::SYNONYM, "pn"};
    Argument apn1 = {ArgumentType::ATTR_REF, make_pair("pn", AttrName::VAR_NAME)};
    Argument ac1 = {ArgumentType::ATTR_REF, make_pair("c", AttrName::PROC_NAME)};
    Argument av1 = {ArgumentType::ATTR_REF, make_pair("v", AttrName::VAR_NAME)};

    ResultClause clause_s_a = {ArgList{as, aa}};
    ResultClause clause_s_pn1 = {ArgList{as, apn1}};
    ResultClause clause_pn_pn1 = {ArgList{apn, apn1}};
    ResultClause clause_a_a1 = {ArgList{aa, aa1}};
    ResultClause clause_a_a1_a1 = {ArgList{aa, aa1, aa1}};
    ResultClause clause_s_pn1_pn1_pn = {ArgList{as, apn1, apn1, apn}};
    ResultClause clause_pn_r_r_pn1_r1 = {ArgList{apn, ar, ar, apn1, ar1}};
    ResultClause clause_r1_pn1_pn_a_r = {ArgList{ar1, apn1, apn, aa, ar}};
    ResultClause clause_r1_pn1_c1 = {ArgList{ar1, apn1, ac1}};
    ResultClause clause_a_v1 = {ArgList{aa, av1}};

    auto *resultTable = new ResultTable();
    SECTION("select tuples") {
        /**
         * Select s,a
         */
        resetSampleResultTable(resultTable);
        REQUIRE(evaluateResultClause(&declarations, resultTable, &clause_s_a, testPKB) == ResultSet{"1 2", "2 2", "3 3"});
    }

    SECTION("select attrRef") {
        /**
         * Select s,pn.varName
         */
        resetSampleResultTable(resultTable);
        REQUIRE(evaluateResultClause(&declarations, resultTable, &clause_s_pn1, testPKB) ==
                ResultSet{"1 z", "2 x", "3 z"});

        /**
         * Select pn,pn.varName
         */
        resetSampleResultTable(resultTable);
        REQUIRE(evaluateResultClause(&declarations, resultTable, &clause_pn_pn1, testPKB) ==
                ResultSet{"4 z", "11 x"});

        /**
         * Select a,a.stmt#
         */
        resetSampleResultTable(resultTable);
        REQUIRE(evaluateResultClause(&declarations, resultTable, &clause_a_a1, testPKB) ==
                ResultSet{"2 2", "3 3"});

        /**
         * Select a,a.stmt#,a.stmt#
         */
        resetSampleResultTable(resultTable);
        REQUIRE(evaluateResultClause(&declarations, resultTable, &clause_a_a1_a1, testPKB) ==
                ResultSet{"2 2 2", "3 3 3"});

        /**
         * Select s,pn.varName,pn.varName,pn
         */
        resetSampleResultTable(resultTable);
        REQUIRE(evaluateResultClause(&declarations, resultTable, &clause_s_pn1_pn1_pn, testPKB) ==
                ResultSet{"1 z z 4", "2 x x 11", "3 z z 4"});

        /**
         * Select pn, r, r, pn.varName, r.varName
         */
        resetSampleResultTable(resultTable);
        REQUIRE(evaluateResultClause(&declarations, resultTable, &clause_pn_r_r_pn1_r1, testPKB) ==
        ResultSet{"4 1 1 z x", "11 1 1 x x"});

        /**
         * Select r.varName, pn.varName, pn, a, r
         */
        resetSampleResultTable(resultTable);
        REQUIRE(evaluateResultClause(&declarations, resultTable, &clause_r1_pn1_pn_a_r, testPKB) ==
        ResultSet{"x z 4 2 1",
                  "x x 11 2 1",
                  "x z 4 3 1"});
    }

    SECTION("select from empty result table") {
        /**
         * Select <r.varName, pn.varName, cl.procName>
         */
        resultTable->clearTable();
        REQUIRE(evaluateResultClause(&declarations, resultTable, &clause_r1_pn1_c1, testPKB) == ResultSet{"x x pr", "x z pr"});

        /**
         * Select <a,v.varName>
         */
        resultTable->clearTable();
        REQUIRE(evaluateResultClause(&declarations, resultTable, &clause_a_v1, testPKB) == ResultSet{
                "9 x", "2 x", "3 y", "2 b", "10 y", "2 y", "10 z", "8 x", "8 a", "3 x",
                "9 y", "9 b", "8 z", "9 z", "2 z", "9 a", "3 z", "10 a", "8 b", "2 a",
                "3 a", "10 x", "8 y", "10 b", "3 b"
        });
    }
    delete resultTable;
    
}