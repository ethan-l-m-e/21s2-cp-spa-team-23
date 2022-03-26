//
// Created by Tianyi Wang on 14/3/22.
//

#include "QP_Evaluator/ClauseEvaluators/WithClauseEvaluator.h"
#include "TestUtilities.h"
#include <utility>
#include "catch.hpp"

using namespace std;

bool evaluateWithClause(unordered_map<string, DesignEntity>* declarations, ResultTable* resultTable, Clause* clause, PKB* pkb) {
    auto *withClauseEvaluator = new WithClauseEvaluator(declarations, clause, pkb);
    bool result = withClauseEvaluator->evaluateClause(resultTable);
    delete withClauseEvaluator;
    return result;
}

TEST_CASE("Test with clause evaluator") {
    PKB *testPKB = generateSamplePKB();
    unordered_map<string, DesignEntity> declarations = {
            {"p", DesignEntity::PROCEDURE},
            {"v", DesignEntity::VARIABLE},
            {"pn", DesignEntity::PRINT},
            {"r", DesignEntity::READ},
    };

    Argument a1 = {ArgumentType::STMT_NO, "1"};
    Argument ax = {ArgumentType::IDENT, "x"};
    Argument ay = {ArgumentType::IDENT, "y"};
    Argument az = {ArgumentType::IDENT, "z"};
    Argument a11 = {ArgumentType::STMT_NO, "11"};
    Argument apn_stmt = {ArgumentType::ATTR_REF, make_pair("pn", AttrName::STMT_NO)};
    Argument apn_var = {ArgumentType::ATTR_REF, make_pair("pn", AttrName::VAR_NAME)};
    Argument ar_var = {ArgumentType::ATTR_REF, make_pair("r", AttrName::VAR_NAME)};
    Argument av = {ArgumentType::ATTR_REF, make_pair("v", AttrName::VAR_NAME)};

    WithClause clause_1_1 = {ArgList{a1, a1}};
    WithClause clause_x_y = {ArgList{ax, ay}};
    WithClause clause_pn_stmt_11 = {ArgList{apn_stmt, a11}};
    WithClause clause_pn_var_x = {ArgList{apn_var, ax}};
    WithClause clause_pn_var_r_var = {ArgList{apn_var, ar_var}};
    WithClause clause_pn_var_v = {ArgList{apn_var, av}};
    WithClause clause_z_pn_var = {ArgList{az, apn_var}};

    auto *resultTable = new ResultTable();

    SECTION("select zero synonym") {
        /**
        * with 1 = 1
        */
        resultTable->clearTable();
        REQUIRE(evaluateWithClause(&declarations, resultTable, &clause_1_1, testPKB) == true);
        REQUIRE(generateResultSet(QueryEvaluator::generateResultString(resultTable)).empty());

        /**
        * with "x" = "y"
        */
        resultTable->clearTable();
        REQUIRE(evaluateWithClause(&declarations, resultTable, &clause_x_y, testPKB) == false);
        REQUIRE(generateResultSet(QueryEvaluator::generateResultString(resultTable)).empty());
    }

    SECTION("select one synonym") {
        /**
        * with pn.stmt# = 11
        */
        resultTable->clearTable();
        REQUIRE(evaluateWithClause(&declarations, resultTable, &clause_pn_stmt_11, testPKB) == true);
        REQUIRE(generateResultSet(QueryEvaluator::generateResultString(resultTable)) == ResultSet{"11"});

        /**
        * with pn.varName = "x"
        */
        resultTable->clearTable();
        REQUIRE(evaluateWithClause(&declarations, resultTable, &clause_pn_var_x, testPKB) == true);
        REQUIRE(generateResultSet(QueryEvaluator::generateResultString(resultTable)) == ResultSet{"11"});

        /**
       * with "z" = pn.varName
       */
        resultTable->clearTable();
        REQUIRE(evaluateWithClause(&declarations, resultTable, &clause_z_pn_var, testPKB) == true);
        REQUIRE(generateResultSet(QueryEvaluator::generateResultString(resultTable)) == ResultSet{"4"});

    }

    SECTION("select two synonyms") {
        /**
        * with pn.varName = r.varName
        */
        resultTable->clearTable();
        REQUIRE(evaluateWithClause(&declarations, resultTable, &clause_pn_var_r_var, testPKB) == true);
        REQUIRE(generateResultSet(QueryEvaluator::generateResultString(resultTable)) == ResultSet{"11 1"});

        /**
        * with pn.varName = v.varName
        */
        resultTable->clearTable();
        REQUIRE(evaluateWithClause(&declarations, resultTable, &clause_pn_var_v, testPKB) == true);
        REQUIRE(generateResultSet(QueryEvaluator::generateResultString(resultTable)) == ResultSet{"4 z", "11 x"});
    }
}