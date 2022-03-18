//
// Created by Tianyi Wang on 14/3/22.
//

#include "QP_Evaluator/ClauseEvaluators/FollowsClauseEvaluator.h"
#include "QP_Evaluator/ClauseEvaluators/FollowsTClauseEvaluator.h"
#include "QP_Evaluator/ClauseEvaluators/ParentClauseEvaluator.h"
#include "QP_Evaluator/ClauseEvaluators/ParentTClauseEvaluator.h"
#include "QP_Evaluator/ClauseEvaluators/ModifiesSClauseEvaluator.h"
#include "QP_Evaluator/ClauseEvaluators/ModifiesPClauseEvaluator.h"
#include "QP_Evaluator/ClauseEvaluators/UsesSClauseEvaluator.h"
#include "QP_Evaluator/ClauseEvaluators/UsesPClauseEvaluator.h"
#include "QP_Evaluator/ClauseEvaluators/NextClauseEvaluator.h"
#include "QP_Evaluator/ClauseEvaluators/NextTClauseEvaluator.h"

#include "TestUtilities.h"
#include <utility>
#include "catch.hpp"

using namespace std;

TEST_CASE("Test Follow clause evaluator") {
    PKB *testPKB = generateSamplePKB();
    unordered_map<string, DesignEntity> declarations = {
                                                        {"a", DesignEntity::ASSIGN},
                                                        {"r", DesignEntity::READ},
                                                        {"pn", DesignEntity::PRINT},
                                                        {"s1", DesignEntity::STMT},
                                                        {"s2", DesignEntity::STMT}
                                                        };

    Argument a0 = {ArgumentType::UNDERSCORE, "_"};
    Argument as1 = {ArgumentType::SYNONYM, "s1"};
    Argument as2 = {ArgumentType::SYNONYM, "s2"};
    Argument apn = {ArgumentType::SYNONYM, "pn"};
    Argument aa = {ArgumentType::SYNONYM, "a"};
    Argument ar = {ArgumentType::SYNONYM, "r"};
    Argument a3 = {ArgumentType::STMT_NO, "3"};
    Argument a5 = {ArgumentType::STMT_NO, "5"};
    Argument a12 = {ArgumentType::STMT_NO, "12"};

    SuchThatClause clause_0_0 = {ArgList{a0, a0},RelRef::FOLLOWS};
    SuchThatClause clause_0_3 = {ArgList{a0, a3},RelRef::FOLLOWS};
    SuchThatClause clause_3_5 = {ArgList{a3, a5},RelRef::FOLLOWS};
    SuchThatClause clause_3_s1 = {ArgList{a3, as1},RelRef::FOLLOWS};
    SuchThatClause clause_r_3 = {ArgList{ar, a3},RelRef::FOLLOWS};
    SuchThatClause clause_0_s1 = {ArgList{a0, as1},RelRef::FOLLOWS};
    SuchThatClause clause_s1_s2 = {ArgList{as1, as2},RelRef::FOLLOWS};
    SuchThatClause clause_0_12 = {ArgList{a0, a12},RelRef::FOLLOWS};
    SuchThatClause clause_s1_pn = {ArgList{as1, apn},RelRef::FOLLOWS};
    SuchThatClause clause_r_a = {ArgList{ar, aa},RelRef::FOLLOWS};



    Argument dummySelect = {ArgumentType::SYNONYM, "s"};

    Query query_0 = makeQuery(declarations, {dummySelect}, {clause_0_0});
    Query query_1 = makeQuery(declarations, {dummySelect}, {clause_0_3});
    Query query_2 = makeQuery(declarations, {dummySelect}, {clause_3_5});
    Query query_3 = makeQuery(declarations, {dummySelect}, {clause_3_s1});
    Query query_4 = makeQuery(declarations, {dummySelect}, {clause_r_3});
    Query query_5 = makeQuery(declarations, {dummySelect}, {clause_0_s1});
    Query query_6 = makeQuery(declarations, {dummySelect}, {clause_s1_s2});
    Query query_7 = makeQuery(declarations, {dummySelect}, {clause_s1_pn});
    Query query_8 = makeQuery(declarations, {dummySelect}, {clause_r_a});
    Query query_9 = makeQuery(declarations, {dummySelect}, {clause_0_12});

    SECTION("select zero synonym") {
        /**
         * Follows(_, _)
         * Type: Follows, boolean, wildcard, wildcard
         */
        auto *resultTable = new ResultTable();
        auto *suchThatClauseEvaluator = new FollowsClauseEvaluator(clause_0_0.argList, testPKB, &query_0);
        bool result = suchThatClauseEvaluator->evaluateClause(resultTable);
        delete suchThatClauseEvaluator;
        REQUIRE(result == true);
        REQUIRE(generateResultSet(QueryEvaluator::generateResultString(resultTable)).empty());

        /**
         * Follows(_, 3)
         * Type: Follows, boolean, wildcard, stmtNo
         */
        resultTable = new ResultTable();
        suchThatClauseEvaluator = new FollowsClauseEvaluator(clause_0_3.argList, testPKB, &query_1);
        result = suchThatClauseEvaluator->evaluateClause(resultTable);
        delete suchThatClauseEvaluator;
        REQUIRE(result == true);
        REQUIRE(generateResultSet(QueryEvaluator::generateResultString(resultTable)).empty());

        /**
         * Follows(3, 5)
         * Type: Follows, boolean, stmtNo, stmtNo
         */
        resultTable = new ResultTable();
        suchThatClauseEvaluator = new FollowsClauseEvaluator(clause_3_5.argList, testPKB, &query_2);
        result = suchThatClauseEvaluator->evaluateClause(resultTable);
        delete suchThatClauseEvaluator;
        REQUIRE(result == false);
        REQUIRE(generateResultSet(QueryEvaluator::generateResultString(resultTable)).empty());
    }

    SECTION("select one synonym") {
        /**
        * Follows(3, s1)
        * Type: Follows, select second arg
        */
        auto *resultTable = new ResultTable();
        auto *suchThatClauseEvaluator = new FollowsClauseEvaluator(clause_3_s1.argList, testPKB, &query_3);
        bool result = suchThatClauseEvaluator->evaluateClause(resultTable);
        delete suchThatClauseEvaluator;
        REQUIRE(result == true);
        REQUIRE(generateResultSet(QueryEvaluator::generateResultString(resultTable)) == ResultSet{"4"});

        /**
         * Follows(r, 3)
         * Type: Follows, select first arg
         */
        resultTable = new ResultTable();
        suchThatClauseEvaluator = new FollowsClauseEvaluator(clause_r_3.argList, testPKB, &query_4);
        result = suchThatClauseEvaluator->evaluateClause(resultTable);
        delete suchThatClauseEvaluator;
        REQUIRE(result == false);
        REQUIRE(generateResultSet(QueryEvaluator::generateResultString(resultTable)).empty());

        /**
         * Follows(_, s1)
         * Type: Follows, select second arg, wildcard
         */
        resultTable = new ResultTable();
        suchThatClauseEvaluator = new FollowsClauseEvaluator(clause_0_s1.argList, testPKB, &query_5);
        result = suchThatClauseEvaluator->evaluateClause(resultTable);
        delete suchThatClauseEvaluator;
        REQUIRE(result == true);
        REQUIRE(generateResultSet(QueryEvaluator::generateResultString(resultTable)) == ResultSet{"2", "3", "4", "5", "7", "10", "11"});
    }

    SECTION("select two synonyms") {
        /**
         * Follows(s1, s2)
         */
        auto *resultTable = new ResultTable();
        auto *suchThatClauseEvaluator = new FollowsClauseEvaluator(clause_s1_s2.argList, testPKB, &query_6);
        bool result = suchThatClauseEvaluator->evaluateClause(resultTable);
        delete suchThatClauseEvaluator;
        REQUIRE(result == true);
        REQUIRE(generateResultSet(QueryEvaluator::generateResultString(resultTable)) == ResultSet{"1 2", "2 3", "3 4", "4 5", "5 11", "6 7", "7 10"});
        /**
         * Follows(s1, pn)
         */
        resultTable = new ResultTable();
        suchThatClauseEvaluator = new FollowsClauseEvaluator(clause_s1_pn.argList, testPKB, &query_7);
        result = suchThatClauseEvaluator->evaluateClause(resultTable);
        delete suchThatClauseEvaluator;
        REQUIRE(result == true);
        REQUIRE(generateResultSet(QueryEvaluator::generateResultString(resultTable)) == ResultSet{"5 11", "3 4"});
        /**
         * Follows(r, a)
         */
        resultTable = new ResultTable();
        suchThatClauseEvaluator = new FollowsClauseEvaluator(clause_r_a.argList, testPKB, &query_8);
        result = suchThatClauseEvaluator->evaluateClause(resultTable);
        delete suchThatClauseEvaluator;
        REQUIRE(result == true);
        REQUIRE(generateResultSet(QueryEvaluator::generateResultString(resultTable)) == ResultSet{"1 2"});
    }

    SECTION("invalid query") {
        /**
         * Follows(_, 12)
         * Type: Follows, boolean, semantic error
         */
        auto *resultTable = new ResultTable();
        auto *suchThatClauseEvaluator = new FollowsClauseEvaluator(clause_0_12.argList, testPKB, &query_9);
        bool result = suchThatClauseEvaluator->evaluateClause(resultTable);
        delete suchThatClauseEvaluator;
        REQUIRE(result == false);
        REQUIRE(generateResultSet(QueryEvaluator::generateResultString(resultTable)).empty());
    }
}

TEST_CASE("Test Follows* clause evaluator") {
    PKB *testPKB = generateSamplePKB();
    unordered_map<string, DesignEntity> declarations = {
                                                        {"a", DesignEntity::ASSIGN},
                                                        {"r", DesignEntity::READ},
                                                        {"pn", DesignEntity::PRINT},
                                                        {"s1", DesignEntity::STMT},
                                                        {"s2", DesignEntity::STMT}
                                                        };

    Argument a0 = {ArgumentType::UNDERSCORE, "_"};
    Argument as1 = {ArgumentType::SYNONYM, "s1"};
    Argument as2 = {ArgumentType::SYNONYM, "s2"};
    Argument apn = {ArgumentType::SYNONYM, "pn"};
    Argument ar = {ArgumentType::SYNONYM, "r"};
    Argument a3 = {ArgumentType::STMT_NO, "3"};
    Argument a5 = {ArgumentType::STMT_NO, "5"};
    Argument a10 = {ArgumentType::STMT_NO, "10"};

    SuchThatClause clause_0_0 = {ArgList{a0, a0},RelRef::FOLLOWS_T};
    SuchThatClause clause_0_3 = {ArgList{a0, a3},RelRef::FOLLOWS_T};
    SuchThatClause clause_3_5 = {ArgList{a3, a5},RelRef::FOLLOWS_T};
    SuchThatClause clause_3_s1 = {ArgList{a3, as1},RelRef::FOLLOWS_T};
    SuchThatClause clause_r_3 = {ArgList{ar, a3},RelRef::FOLLOWS_T};
    SuchThatClause clause_0_s1 = {ArgList{a0, as1},RelRef::FOLLOWS_T};
    SuchThatClause clause_s1_s2 = {ArgList{as1, as2},RelRef::FOLLOWS_T};
    SuchThatClause clause_0_10 = {ArgList{a0, a10},RelRef::FOLLOWS_T};
    SuchThatClause clause_s1_pn = {ArgList{as1, apn},RelRef::FOLLOWS_T};

    Argument dummySelect = {ArgumentType::SYNONYM, "s"};

    Query query_0 = makeQuery(declarations, {dummySelect}, {clause_0_0});
    Query query_1 = makeQuery(declarations, {dummySelect}, {clause_0_3});
    Query query_2 = makeQuery(declarations, {dummySelect}, {clause_3_5});
    Query query_3 = makeQuery(declarations, {dummySelect}, {clause_3_s1});
    Query query_4 = makeQuery(declarations, {dummySelect}, {clause_r_3});
    Query query_5 = makeQuery(declarations, {dummySelect}, {clause_0_s1});
    Query query_6 = makeQuery(declarations, {dummySelect}, {clause_s1_s2});
    Query query_7 = makeQuery(declarations, {dummySelect}, {clause_s1_pn});


    SECTION("select zero synonym") {
        /**
         * Follows*(_, _)
         * Type: Follows*, boolean, wildcard, wildcard
         */
        auto *resultTable = new ResultTable();
        auto *suchThatClauseEvaluator = new FollowsTClauseEvaluator(clause_0_0.argList, testPKB, &query_0);
        bool result = suchThatClauseEvaluator->evaluateClause(resultTable);
        delete suchThatClauseEvaluator;
        REQUIRE(result == true);
        REQUIRE(generateResultSet(QueryEvaluator::generateResultString(resultTable)).empty());

        /**
         * Follows*(_, 3)
         * Type: Follows*, boolean, wildcard, stmtNo
         */
        resultTable = new ResultTable();
        suchThatClauseEvaluator = new FollowsTClauseEvaluator(clause_0_3.argList, testPKB, &query_1);
        result = suchThatClauseEvaluator->evaluateClause(resultTable);
        delete suchThatClauseEvaluator;
        REQUIRE(result == true);
        REQUIRE(generateResultSet(QueryEvaluator::generateResultString(resultTable)).empty());

        /**
         * Follows*(3, 5)
         * Type: Follows*, boolean, stmtNo, stmtNo
         */
        resultTable = new ResultTable();
        suchThatClauseEvaluator = new FollowsTClauseEvaluator(clause_3_5.argList, testPKB, &query_2);
        result = suchThatClauseEvaluator->evaluateClause(resultTable);
        delete suchThatClauseEvaluator;
        REQUIRE(result == true);
        REQUIRE(generateResultSet(QueryEvaluator::generateResultString(resultTable)).empty());
    }

    SECTION("select one synonym") {
        /**
        * Follows*(3, s1)
        * Type: Follows*, select second arg
        */
        auto *resultTable = new ResultTable();
        auto *suchThatClauseEvaluator = new FollowsTClauseEvaluator(clause_3_s1.argList, testPKB, &query_3);
        bool result = suchThatClauseEvaluator->evaluateClause(resultTable);
        delete suchThatClauseEvaluator;
        REQUIRE(result == true);
        REQUIRE(generateResultSet(QueryEvaluator::generateResultString(resultTable)) == ResultSet{"4", "5", "11"});

        /**
         * Follows*(r, 3)
         * Type: Follows*, select first arg
         */
        resultTable = new ResultTable();
        suchThatClauseEvaluator = new FollowsTClauseEvaluator(clause_r_3.argList, testPKB, &query_4);
        result = suchThatClauseEvaluator->evaluateClause(resultTable);
        delete suchThatClauseEvaluator;
        REQUIRE(result == true);
        REQUIRE(generateResultSet(QueryEvaluator::generateResultString(resultTable)) == ResultSet{"1"});

        /**
         * Select s such that Follows*(_, s)
         * Type: Follows*, select second arg, wildcard
         */
        resultTable = new ResultTable();
        suchThatClauseEvaluator = new FollowsTClauseEvaluator(clause_0_s1.argList, testPKB, &query_5);
        result = suchThatClauseEvaluator->evaluateClause(resultTable);
        delete suchThatClauseEvaluator;
        REQUIRE(result == true);
        REQUIRE(generateResultSet(QueryEvaluator::generateResultString(resultTable)) == ResultSet{ "10", "4", "11", "5", "7", "3", "2" });
    }

    SECTION("select two synonyms") {
        /**
         * Follows*(s1, s2)
         * Type: Follows*, select none
         */
        auto *resultTable = new ResultTable();
        auto *suchThatClauseEvaluator = new FollowsTClauseEvaluator(clause_s1_s2.argList, testPKB, &query_6);
        bool result = suchThatClauseEvaluator->evaluateClause(resultTable);
        delete suchThatClauseEvaluator;
        REQUIRE(result == true);
        REQUIRE(generateResultSet(QueryEvaluator::generateResultString(resultTable)) == ResultSet{"1 2", "1 3", "1 4", "1 5", "1 11",
                                                                                                  "2 3", "2 4", "2 5", "2 11", "3 4", "3 5", "3 11",
                                                                                                  "4 5", "4 11", "5 11", "6 7", "6 10", "7 10"});

        /**
         * Select s such that Follows*(s1, pn)
         * Type: follows*, select first arg
         */
        resultTable = new ResultTable();
        suchThatClauseEvaluator = new FollowsTClauseEvaluator(clause_s1_pn.argList, testPKB, &query_7);
        result = suchThatClauseEvaluator->evaluateClause(resultTable);
        delete suchThatClauseEvaluator;
        REQUIRE(result == true);
        REQUIRE(generateResultSet(QueryEvaluator::generateResultString(resultTable)) == ResultSet{"3 4", "2 4", "1 4", "1 11", "2 11", "3 11", "4 11", "5 11"});
    }
}

TEST_CASE("Test Parent clause evaluator") {
    PKB *testPKB = generateSamplePKB();
    unordered_map<string, DesignEntity> declarations = {
                                                        {"s1", DesignEntity::STMT},
                                                        {"s2", DesignEntity::STMT},
                                                        {"w", DesignEntity::WHILE},
                                                        {"a", DesignEntity::ASSIGN}
                                                        };

    Argument a0 = {ArgumentType::UNDERSCORE, "_"};
    Argument as1 = {ArgumentType::SYNONYM, "s1"};
    Argument as2 = {ArgumentType::SYNONYM, "s2"};
    Argument aw = {ArgumentType::SYNONYM, "w"};
    Argument aa = {ArgumentType::SYNONYM, "a"};
    Argument a3 = {ArgumentType::STMT_NO, "3"};
    Argument a5 = {ArgumentType::STMT_NO, "5"};
    Argument a7 = {ArgumentType::STMT_NO, "7"};
    Argument a10 = {ArgumentType::STMT_NO, "10"};
    Argument a00 = {ArgumentType::STMT_NO, "0"};



    SuchThatClause clause0 = {ArgList{a0, a0},RelRef::PARENT};
    SuchThatClause clause1 = {ArgList{a0, a3},RelRef::PARENT};
    SuchThatClause clause_3_5 = {ArgList{a3, a5},RelRef::PARENT};
    SuchThatClause clause_5_s1 = {ArgList{a5, as1},RelRef::PARENT};
    SuchThatClause clause_w_7 = {ArgList{aw, a7},RelRef::PARENT};
    SuchThatClause clause_s1_0 = {ArgList{as1, a0},RelRef::PARENT};
    SuchThatClause clause_s1_s2 = {ArgList{as1, as2},RelRef::PARENT};
    SuchThatClause clause_0_10 = {ArgList{a00, as1},RelRef::PARENT};
    SuchThatClause clause_w_a = {ArgList{aw, aa},RelRef::PARENT};


    Argument dummySelect = {ArgumentType::SYNONYM, "s"};

    Query query_0 = makeQuery(declarations, {dummySelect}, {clause0});
    Query query_1 = makeQuery(declarations, {dummySelect}, {clause1});
    Query query_2 = makeQuery(declarations, {dummySelect}, {clause_3_5});
    Query query_3 = makeQuery(declarations, {dummySelect}, {clause_5_s1});
    Query query_4 = makeQuery(declarations, {dummySelect}, {clause_w_7});
    Query query_5 = makeQuery(declarations, {dummySelect}, {clause_s1_0});
    Query query_6 = makeQuery(declarations, {dummySelect}, {clause_s1_s2});
    Query query_7 = makeQuery(declarations, {dummySelect}, {clause_0_10});
    Query query_8 = makeQuery(declarations, {dummySelect}, {clause_w_a});


    SECTION("select zero synonym") {
        /**
         * Parent(_, _)
         * Type: Parent, boolean, wildcard, wildcard
         */
        auto *resultTable = new ResultTable();
        auto *suchThatClauseEvaluator = new ParentClauseEvaluator(clause0.argList, testPKB, &query_0);
        bool result = suchThatClauseEvaluator->evaluateClause(resultTable);
        delete suchThatClauseEvaluator;
        REQUIRE(result == true);
        REQUIRE(generateResultSet(QueryEvaluator::generateResultString(resultTable)).empty());

        /**
         * Parent(_, 3)
         * Type: Parent, boolean, wildcard, stmtNo
         */
        resultTable = new ResultTable();
        suchThatClauseEvaluator = new ParentClauseEvaluator(clause1.argList, testPKB, &query_1);
        result = suchThatClauseEvaluator->evaluateClause(resultTable);
        delete suchThatClauseEvaluator;
        REQUIRE(result == false);
        REQUIRE(generateResultSet(QueryEvaluator::generateResultString(resultTable)).empty());

        /**
         * Parent(3, 5)
         * Type: Parent, boolean, stmtNo, stmtNo
         */
        resultTable = new ResultTable();
        suchThatClauseEvaluator = new ParentClauseEvaluator(clause_3_5.argList, testPKB, &query_2);
        result = suchThatClauseEvaluator->evaluateClause(resultTable);
        delete suchThatClauseEvaluator;
        REQUIRE(result == false);
        REQUIRE(generateResultSet(QueryEvaluator::generateResultString(resultTable)).empty());
    }

    SECTION("select one synonym") {
        /**
        * Parent(5, s1)
        * Type: Parent, select second arg
        */
        auto *resultTable = new ResultTable();
        auto *suchThatClauseEvaluator = new ParentClauseEvaluator(clause_5_s1.argList, testPKB, &query_3);
        bool result = suchThatClauseEvaluator->evaluateClause(resultTable);
        delete suchThatClauseEvaluator;
        REQUIRE(result == true);
        REQUIRE(generateResultSet(QueryEvaluator::generateResultString(resultTable)) == ResultSet{"6", "7", "10"});

        /**
         * Parent(w, 7)
         * Type: Parent, select first arg
         */
        resultTable = new ResultTable();
        suchThatClauseEvaluator = new ParentClauseEvaluator(clause_w_7.argList, testPKB, &query_4);
        result = suchThatClauseEvaluator->evaluateClause(resultTable);
        delete suchThatClauseEvaluator;
        REQUIRE(result == true);
        REQUIRE(generateResultSet(QueryEvaluator::generateResultString(resultTable)) == ResultSet{"5"});

        /**
         * Select s such that Parent(s1, _)
         * Type: Parent, select second arg, wildcard
         */
        resultTable = new ResultTable();
        suchThatClauseEvaluator = new ParentClauseEvaluator(clause_s1_0.argList, testPKB, &query_5);
        result = suchThatClauseEvaluator->evaluateClause(resultTable);
        delete suchThatClauseEvaluator;
        REQUIRE(result == true);
        REQUIRE(generateResultSet(QueryEvaluator::generateResultString(resultTable)) == ResultSet{"5", "7"});
    }

    SECTION("select two synonyms") {
        /**
         * Parent(s1, s2)
         */
        auto *resultTable = new ResultTable();
        auto *suchThatClauseEvaluator = new ParentClauseEvaluator(clause_s1_s2.argList, testPKB, &query_6);
        bool result = suchThatClauseEvaluator->evaluateClause(resultTable);
        delete suchThatClauseEvaluator;
        REQUIRE(result == true);
        REQUIRE(generateResultSet(QueryEvaluator::generateResultString(resultTable)) == ResultSet{"5 10", "5 7", "5 6", "7 8", "7 9"});

        /**
         * Parent(w, a)
         */
        resultTable = new ResultTable();
        suchThatClauseEvaluator = new ParentClauseEvaluator(clause_w_a.argList, testPKB, &query_7);
        result = suchThatClauseEvaluator->evaluateClause(resultTable);
        delete suchThatClauseEvaluator;
        REQUIRE(result == true);
        REQUIRE(generateResultSet(QueryEvaluator::generateResultString(resultTable)) == ResultSet{"5 10"});

    }

    SECTION("invalid query") {
        /**
         * Parent(0, s1)
         * Type: Parent, boolean, semantic error
         */
        auto *resultTable = new ResultTable();
        auto *suchThatClauseEvaluator = new ParentClauseEvaluator(clause_0_10.argList, testPKB, &query_7);
        bool result = suchThatClauseEvaluator->evaluateClause(resultTable);
        delete suchThatClauseEvaluator;
        REQUIRE(result == false);
        REQUIRE(generateResultSet(QueryEvaluator::generateResultString(resultTable)).empty());
    }
}

TEST_CASE("Test Parent* clause evaluator") {
    PKB *testPKB = generateSamplePKB();
    unordered_map<string, DesignEntity> declarations = {
                                                        {"s1", DesignEntity::STMT},
                                                        {"s2", DesignEntity::STMT},
                                                        {"ifs", DesignEntity::IF},
    };

    Argument a0 = {ArgumentType::UNDERSCORE, "_"};
    Argument as1 = {ArgumentType::SYNONYM, "s1"};
    Argument as2 = {ArgumentType::SYNONYM, "s2"};
    Argument ai = {ArgumentType::SYNONYM, "ifs"};
    Argument a3 = {ArgumentType::STMT_NO, "3"};
    Argument a5 = {ArgumentType::STMT_NO, "5"};
    Argument a7 = {ArgumentType::STMT_NO, "7"};
    Argument a10 = {ArgumentType::STMT_NO, "10"};

    SuchThatClause clause0 = {ArgList{a0, a0},RelRef::PARENT_T};
    SuchThatClause clause1 = {ArgList{a0, a3},RelRef::PARENT_T};
    SuchThatClause clause_3_5 = {ArgList{a3, a5},RelRef::PARENT_T};
    SuchThatClause clause_5_s1 = {ArgList{a5, as1},RelRef::PARENT_T};
    SuchThatClause clause_i_7 = {ArgList{ai, a7},RelRef::PARENT_T};
    SuchThatClause clause_s1_0 = {ArgList{as1, a0},RelRef::PARENT_T};
    SuchThatClause clause_s1_s2 = {ArgList{as1, as2},RelRef::PARENT_T};
    SuchThatClause clause_0_10 = {ArgList{a0, a10},RelRef::PARENT_T};


    Argument dummySelect = {ArgumentType::SYNONYM, "s"};

    Query query_0 = makeQuery(declarations, {dummySelect}, {clause0});
    Query query_1 = makeQuery(declarations, {dummySelect}, {clause1});
    Query query_2 = makeQuery(declarations, {dummySelect}, {clause_3_5});
    Query query_3 = makeQuery(declarations, {dummySelect}, {clause_5_s1});
    Query query_4 = makeQuery(declarations, {dummySelect}, {clause_i_7});
    Query query_5 = makeQuery(declarations, {dummySelect}, {clause_s1_0});
    Query query_6 = makeQuery(declarations, {dummySelect}, {clause_s1_s2});
    Query query_7 = makeQuery(declarations, {dummySelect}, {clause_0_10});

    SECTION("select zero synonym") {
        /**
         * Parent*(_, _)
         * Type: Parent*, boolean, wildcard, wildcard
         */
        auto *resultTable = new ResultTable();
        auto *suchThatClauseEvaluator = new ParentTClauseEvaluator(clause0.argList, testPKB, &query_0);
        bool result = suchThatClauseEvaluator->evaluateClause(resultTable);
        delete suchThatClauseEvaluator;
        REQUIRE(result == true);
        REQUIRE(generateResultSet(QueryEvaluator::generateResultString(resultTable)).empty());

        /**
         * Parent*(_, 3)
         * Type: Parent*, boolean, wildcard, stmtNo
         */
        resultTable = new ResultTable();
        suchThatClauseEvaluator = new ParentTClauseEvaluator(clause1.argList, testPKB, &query_1);
        result = suchThatClauseEvaluator->evaluateClause(resultTable);
        delete suchThatClauseEvaluator;
        REQUIRE(result == false);
        REQUIRE(generateResultSet(QueryEvaluator::generateResultString(resultTable)).empty());

        /**
         * Parent*(3, 5)
         * Type: Parent*, boolean, stmtNo, stmtNo
         */
        resultTable = new ResultTable();
        suchThatClauseEvaluator = new ParentTClauseEvaluator(clause_3_5.argList, testPKB, &query_2);
        result = suchThatClauseEvaluator->evaluateClause(resultTable);
        delete suchThatClauseEvaluator;
        REQUIRE(result == false);
        REQUIRE(generateResultSet(QueryEvaluator::generateResultString(resultTable)).empty());
    }

    SECTION("select one synonym") {
        /**
        * Parent*(5, s1)
        */
        auto *resultTable = new ResultTable();
        auto *suchThatClauseEvaluator = new ParentTClauseEvaluator(clause_5_s1.argList, testPKB, &query_3);
        bool result = suchThatClauseEvaluator->evaluateClause(resultTable);
        delete suchThatClauseEvaluator;
        REQUIRE(result == true);
        REQUIRE(generateResultSet(QueryEvaluator::generateResultString(resultTable)) == ResultSet{"6", "7", "8", "9", "10"});

        /**
         * Parent*(ifs, 7)
         */
        resultTable = new ResultTable();
        suchThatClauseEvaluator = new ParentTClauseEvaluator(clause_i_7.argList, testPKB, &query_4);
        result = suchThatClauseEvaluator->evaluateClause(resultTable);
        delete suchThatClauseEvaluator;
        REQUIRE(result == false);
        REQUIRE(generateResultSet(QueryEvaluator::generateResultString(resultTable)).empty());

        /**
         * Select s such that Parent*(s1, _)
         */
        resultTable = new ResultTable();
        suchThatClauseEvaluator = new ParentTClauseEvaluator(clause_s1_0.argList, testPKB, &query_5);
        result = suchThatClauseEvaluator->evaluateClause(resultTable);
        delete suchThatClauseEvaluator;
        REQUIRE(result == true);
        REQUIRE(generateResultSet(QueryEvaluator::generateResultString(resultTable)) == ResultSet{"5", "7"});
    }

    SECTION("select two synonyms") {
        /**
         * Parent*(s1, s2)
         */
        auto *resultTable = new ResultTable();
        auto *suchThatClauseEvaluator = new ParentTClauseEvaluator(clause_s1_s2.argList, testPKB, &query_6);
        bool result = suchThatClauseEvaluator->evaluateClause(resultTable);
        delete suchThatClauseEvaluator;
        REQUIRE(result == true);
        REQUIRE(generateResultSet(QueryEvaluator::generateResultString(resultTable)) == ResultSet{"5 6", "5 7", "5 8", "5 9", "5 10", "7 8", "7 9"});
    }
}

TEST_CASE("Test ModifiesS clause evaluator") {
    PKB *testPKB = generateSamplePKB();
    unordered_map<string, DesignEntity> declarations = {
            {"s1", DesignEntity::STMT},
            {"s2", DesignEntity::STMT},
            {"w", DesignEntity::WHILE},
            {"a", DesignEntity::ASSIGN},
            {"pn", DesignEntity::PRINT},
            {"r", DesignEntity::READ},
            {"c", DesignEntity::CONSTANT},
            {"v", DesignEntity::VARIABLE},
    };

    Argument a0 = {ArgumentType::UNDERSCORE, "_"};
    Argument as1 = {ArgumentType::SYNONYM, "s1"};
    Argument aw = {ArgumentType::SYNONYM, "w"};
    Argument ar = {ArgumentType::SYNONYM, "r"};
    Argument av = {ArgumentType::SYNONYM, "v"};
    Argument a6 = {ArgumentType::STMT_NO, "6"};
    Argument ax = {ArgumentType::IDENT, "x"};
    Argument ax1 = {ArgumentType::IDENT, "x1"};
    Argument a7 = {ArgumentType::STMT_NO, "7"};

    SuchThatClause clause_6_v = {ArgList{a6, av},RelRef::MODIFIES_S};
    SuchThatClause clause_r_x = {ArgList{ar, ax},RelRef::MODIFIES_S};
    SuchThatClause clause_s1_0 = {ArgList{as1, a0},RelRef::MODIFIES_S};
    SuchThatClause clause_s1_x1 = {ArgList{as1, ax1},RelRef::MODIFIES_S};
    SuchThatClause clause_s1_x = {ArgList{as1, ax},RelRef::MODIFIES_S};
    SuchThatClause clause_s1_v = {ArgList{as1, av},RelRef::MODIFIES_S};
    SuchThatClause clause_w_v = {ArgList{aw, av},RelRef::MODIFIES_S};

    Argument dummySelect = {ArgumentType::SYNONYM, "s"};

    Query query_0 = makeQuery(declarations, {dummySelect}, {clause_6_v});
    Query query_1 = makeQuery(declarations, {dummySelect}, {clause_r_x});
    Query query_2 = makeQuery(declarations, {dummySelect}, {clause_s1_x});
    Query query_3 = makeQuery(declarations, {dummySelect}, {clause_s1_0});
    Query query_4 = makeQuery(declarations, {dummySelect}, {clause_s1_v});
    Query query_5 = makeQuery(declarations, {dummySelect}, {clause_w_v});
    Query query_6 = makeQuery(declarations, {dummySelect}, {clause_s1_x1});

    SECTION("select zero synonym") {
    }

    SECTION("select one synonym") {
        /**
         * Modifies(5, v)
         * Type: Modifies, select second arg
         */
        auto *resultTable = new ResultTable();
        auto *suchThatClauseEvaluator = new ModifiesSClauseEvaluator(clause_6_v.argList, testPKB, &query_0);
        bool result = suchThatClauseEvaluator->evaluateClause(resultTable);
        delete suchThatClauseEvaluator;
        REQUIRE(result == true);
        REQUIRE(generateResultSet(QueryEvaluator::generateResultString(resultTable)) == ResultSet{"x"});

        /**
         * Modifies(r, "x")
         * Type: Modifies, select first arg, read
         */
        resultTable = new ResultTable();
        suchThatClauseEvaluator = new ModifiesSClauseEvaluator(clause_r_x.argList, testPKB, &query_1);
        result = suchThatClauseEvaluator->evaluateClause(resultTable);
        delete suchThatClauseEvaluator;
        REQUIRE(result == true);
        REQUIRE(generateResultSet(QueryEvaluator::generateResultString(resultTable)) == ResultSet{"1"});

        /**
         * Modifies(s1, "x")
         * Type: Modifies, select second arg, read
         */
        resultTable = new ResultTable();
        suchThatClauseEvaluator = new ModifiesSClauseEvaluator(clause_s1_x.argList, testPKB, &query_2);
        result = suchThatClauseEvaluator->evaluateClause(resultTable);
        delete suchThatClauseEvaluator;
        REQUIRE(result == true);
        REQUIRE(generateResultSet(QueryEvaluator::generateResultString(resultTable)) == ResultSet{"1", "5", "6", "9"});

        /**
         * Modifies(s1, _)
         * Type: Modifies, select first arg, assign
         */
        resultTable = new ResultTable();
        suchThatClauseEvaluator = new ModifiesSClauseEvaluator(clause_s1_0.argList, testPKB, &query_3);
        result = suchThatClauseEvaluator->evaluateClause(resultTable);
        delete suchThatClauseEvaluator;
        REQUIRE(result == true);
        REQUIRE(generateResultSet(QueryEvaluator::generateResultString(resultTable)) ==
                ResultSet{"1", "2", "3", "5", "6", "8", "9", "10"});
    }

    SECTION("select two synonyms") {
        /**
         * Modifies(s1, v)
         * Type: Modifies, select second arg
         */
        auto *resultTable = new ResultTable();
        auto *suchThatClauseEvaluator = new ModifiesSClauseEvaluator(clause_s1_v.argList, testPKB, &query_4);
        bool result = suchThatClauseEvaluator->evaluateClause(resultTable);
        delete suchThatClauseEvaluator;
        REQUIRE(result == true);
        REQUIRE(generateResultSet(QueryEvaluator::generateResultString(resultTable)) == ResultSet{{ "9 x", "3 z", "6 x", "1 x", "5 y", "5 x", "10 z", "5 z", "8 y", "2 y"}});

        /**
         * Select v such that Modifies(w, v)
         * Type: Modifies, select second arg
         */
        resultTable = new ResultTable();
        suchThatClauseEvaluator = new ModifiesSClauseEvaluator(clause_w_v.argList, testPKB, &query_5);
        result = suchThatClauseEvaluator->evaluateClause(resultTable);
        delete suchThatClauseEvaluator;
        REQUIRE(result == true);
        REQUIRE(generateResultSet(QueryEvaluator::generateResultString(resultTable)) == ResultSet{"5 x", "5 z", "5 y"});

        /**
         * Select s such that Modifies(s1, v)
         * Type: Modifies, select first arg
         */
        resultTable = new ResultTable();
        suchThatClauseEvaluator = new ModifiesSClauseEvaluator(clause_s1_v.argList, testPKB, &query_6);
        result = suchThatClauseEvaluator->evaluateClause(resultTable);
        delete suchThatClauseEvaluator;
        REQUIRE(result == true);
        REQUIRE(generateResultSet(QueryEvaluator::generateResultString(resultTable)) == ResultSet{"9 x", "3 z", "6 x", "1 x", "5 y", "5 x", "10 z", "5 z", "8 y", "2 y"});
    }

    SECTION("invalid query") {
        /**
         * Modifies(s1, "x1")
         * Type: Modifies, select first arg, assign
         */
        auto *resultTable = new ResultTable();
        auto *suchThatClauseEvaluator = new ModifiesSClauseEvaluator(clause_s1_x1.argList, testPKB, &query_6);
        bool result = suchThatClauseEvaluator->evaluateClause(resultTable);
        delete suchThatClauseEvaluator;
        REQUIRE(result == false);
        REQUIRE(generateResultSet(QueryEvaluator::generateResultString(resultTable)).empty());
    }
}

TEST_CASE("Test UsesS clause evaluator") {
    PKB *testPKB = generateSamplePKB();
    unordered_map<string, DesignEntity> declarations = {
            {"s1", DesignEntity::STMT},
            {"s2", DesignEntity::STMT},
            {"w", DesignEntity::WHILE},
            {"a", DesignEntity::ASSIGN},
            {"pn", DesignEntity::PRINT},
            {"r", DesignEntity::READ},
            {"c", DesignEntity::CONSTANT},
            {"v", DesignEntity::VARIABLE},
    };

    Argument a0 = {ArgumentType::UNDERSCORE, "_"};
    Argument as1 = {ArgumentType::SYNONYM, "s1"};
    Argument ar = {ArgumentType::SYNONYM, "r"};
    Argument av = {ArgumentType::SYNONYM, "v"};
    Argument aa = {ArgumentType::SYNONYM, "a"};
    Argument apn = {ArgumentType::SYNONYM, "pn"};
    Argument a2 = {ArgumentType::STMT_NO, "2"};
    Argument ax = {ArgumentType::IDENT, "x"};
    Argument a7 = {ArgumentType::STMT_NO, "7"};
    Argument az = {ArgumentType::IDENT, "z"};

    SuchThatClause clause_2_v = {ArgList{a2, av},RelRef::USES_S};
    SuchThatClause clause_s1_x = {ArgList{as1, ax},RelRef::USES_S};
    SuchThatClause clause_a_0 = {ArgList{aa, a0},RelRef::USES_S};
    SuchThatClause clause_a_z = {ArgList{aa, az},RelRef::USES_S};
    SuchThatClause clause_7_v = {ArgList{a7, av},RelRef::USES_S};
    SuchThatClause clause_s1_v = {ArgList{as1, av},RelRef::USES_S};
    SuchThatClause clause_a_v = {ArgList{aa, av},RelRef::USES_S};
    SuchThatClause clause_pn_v = {ArgList{apn, av},RelRef::USES_S};
    SuchThatClause clause_r_v = {ArgList{ar, av},RelRef::USES_S};

    Argument dummySelect = {ArgumentType::SYNONYM, "s"};

    Query query_0 = makeQuery(declarations, {dummySelect}, {clause_2_v});
    Query query_1 = makeQuery(declarations, {dummySelect}, {clause_s1_x});
    Query query_2 = makeQuery(declarations, {dummySelect}, {clause_a_0});
    Query query_3 = makeQuery(declarations, {dummySelect}, {clause_a_z});
    Query query_4 = makeQuery(declarations, {dummySelect}, {clause_s1_v});
    Query query_5 = makeQuery(declarations, {dummySelect}, {clause_a_v});
    Query query_6 = makeQuery(declarations, {dummySelect}, {clause_pn_v});
    Query query_7 = makeQuery(declarations, {dummySelect}, {clause_r_v});
    Query query_8 = makeQuery(declarations, {dummySelect}, {clause_7_v});

    SECTION("select zero synonym") {
    }

    SECTION("select one synonym") {
        /**
         * Select v such that Uses(2, v)
         * Type: Uses, select second arg
         */
        auto *resultTable = new ResultTable();
        auto *suchThatClauseEvaluator = new UsesSClauseEvaluator(clause_2_v.argList, testPKB, &query_0);
        bool result = suchThatClauseEvaluator->evaluateClause(resultTable);
        delete suchThatClauseEvaluator;
        REQUIRE(result == true);
        REQUIRE(generateResultSet(QueryEvaluator::generateResultString(resultTable)) == ResultSet{"x", "y"});

        /**
         * Select s such that Uses(s1, "x")
         * Type: Uses, select first arg
         */
        resultTable = new ResultTable();
        suchThatClauseEvaluator = new UsesSClauseEvaluator(clause_s1_x.argList, testPKB, &query_1);
        result = suchThatClauseEvaluator->evaluateClause(resultTable);
        delete suchThatClauseEvaluator;
        REQUIRE(result == true);
        REQUIRE(generateResultSet(QueryEvaluator::generateResultString(resultTable)) == ResultSet{"2", "5", "7", "8", "11"});

        /**
         * Select a such that Uses(a, _)
         * Type: Uses, select first arg, wildcard
         */
        resultTable = new ResultTable();
        suchThatClauseEvaluator = new UsesSClauseEvaluator(clause_a_0.argList, testPKB, &query_2);
        result = suchThatClauseEvaluator->evaluateClause(resultTable);
        delete suchThatClauseEvaluator;
        REQUIRE(result == true);
        REQUIRE(generateResultSet(QueryEvaluator::generateResultString(resultTable)) == ResultSet{"2", "8", "10", "3", "9"});

        /**
         * Select a such that Uses(a, "z") {}
         * Type: Uses, select first arg, assign
         */
        resultTable = new ResultTable();
        suchThatClauseEvaluator = new UsesSClauseEvaluator(clause_a_z.argList, testPKB, &query_3);
        result = suchThatClauseEvaluator->evaluateClause(resultTable);
        delete suchThatClauseEvaluator;
        REQUIRE(result == true);
        REQUIRE(generateResultSet(QueryEvaluator::generateResultString(resultTable)) == ResultSet{{"8", "9", "10"}});
    }

    SECTION("select two synonyms") {
        /**
         * Select s such that Uses(s1, v)
         * Type: Uses, select first arg
         */
        auto *resultTable = new ResultTable();
        auto *suchThatClauseEvaluator = new UsesSClauseEvaluator(clause_s1_v.argList, testPKB, &query_4);
        bool result = suchThatClauseEvaluator->evaluateClause(resultTable);
        delete suchThatClauseEvaluator;
        REQUIRE(result == true);
        REQUIRE(generateResultSet(QueryEvaluator::generateResultString(resultTable)) == ResultSet{{"6 y", "11 x", "7 z", "8 x", "5 z", "9 z", "7 y", "9 y", "7 x", "8 z", "5 x", "4 z", "10 z", "5 y", "2 x", "3 y", "2 y"}});

        /**
         * Select a such that Uses(a, v)
         * Type: Uses, select first arg
         */
        resultTable = new ResultTable();
        suchThatClauseEvaluator = new UsesSClauseEvaluator(clause_a_v.argList, testPKB, &query_5);
        result = suchThatClauseEvaluator->evaluateClause(resultTable);
        delete suchThatClauseEvaluator;
        REQUIRE(result == true);
        REQUIRE(generateResultSet(QueryEvaluator::generateResultString(resultTable)) == ResultSet{"9 z", "3 y", "2 x", "9 y", "10 z", "8 x", "8 z", "2 y"});

        /**
         * Select v such that Uses(pn, v)
         * Type: Uses, select second arg
         */
        resultTable = new ResultTable();
        suchThatClauseEvaluator = new UsesSClauseEvaluator(clause_pn_v.argList, testPKB, &query_6);
        result = suchThatClauseEvaluator->evaluateClause(resultTable);
        delete suchThatClauseEvaluator;
        REQUIRE(result == true);
        REQUIRE(generateResultSet(QueryEvaluator::generateResultString(resultTable)) == ResultSet{"11 x", "4 z"});

        /**
         * Select v such that Uses(r, v)
         * Type: Uses, select second arg
         */
        resultTable = new ResultTable();
        suchThatClauseEvaluator = new UsesSClauseEvaluator(clause_r_v.argList, testPKB, &query_7);
        result = suchThatClauseEvaluator->evaluateClause(resultTable);
        delete suchThatClauseEvaluator;
        REQUIRE(result == false);
        REQUIRE(generateResultSet(QueryEvaluator::generateResultString(resultTable)).empty());
    }
}

TEST_CASE("Test ModifiesP clause evaluator") {
    PKB *testPKB = generateSamplePKB();
    unordered_map<string, DesignEntity> declarations = {
            {"p", DesignEntity::PROCEDURE},
            {"v", DesignEntity::VARIABLE},
    };

    Argument a0 = {ArgumentType::UNDERSCORE, "_"};
    Argument av = {ArgumentType::SYNONYM, "v"};
    Argument aprop = {ArgumentType::IDENT, "prop"};
    Argument ap = {ArgumentType::SYNONYM, "p"};
    Argument ax = {ArgumentType::IDENT, "x"};
    Argument ax1 = {ArgumentType::IDENT, "x1"};

    SuchThatClause clause_prop_v = {ArgList{aprop, av},RelRef::MODIFIES_P};
    SuchThatClause clause_p_x = {ArgList{ap, ax},RelRef::MODIFIES_P};
    SuchThatClause clause_p_v = {ArgList{ap, av},RelRef::MODIFIES_P};
    SuchThatClause clause_p_x1 = {ArgList{ap, ax1},RelRef::MODIFIES_P};

    Argument dummySelect = {ArgumentType::SYNONYM, "s"};

    Query query_0 = makeQuery(declarations, {dummySelect}, {clause_prop_v});
    Query query_1 = makeQuery(declarations, {dummySelect}, {clause_p_x});
    Query query_2 = makeQuery(declarations, {dummySelect}, {clause_p_v});
    Query query_3 = makeQuery(declarations, {dummySelect}, {clause_p_x1});

    SECTION("select zero synonym") {
    }

    SECTION("select one synonym") {
        /**
         * Modifies("prop", v)
         * Type: Modifies, select second arg
         */
        auto *resultTable = new ResultTable();
        auto *suchThatClauseEvaluator = new ModifiesPClauseEvaluator(clause_prop_v.argList, testPKB, &query_0);
        bool result = suchThatClauseEvaluator->evaluateClause(resultTable);
        delete suchThatClauseEvaluator;
        REQUIRE(result == true);
        REQUIRE(generateResultSet(QueryEvaluator::generateResultString(resultTable)) == ResultSet{ "x", "z", "y" });

        /**
         * Modifies(p, "x")
         * Type: Modifies, select first arg, read
         */
        resultTable = new ResultTable();
        suchThatClauseEvaluator = new ModifiesPClauseEvaluator(clause_p_x.argList, testPKB, &query_1);
        result = suchThatClauseEvaluator->evaluateClause(resultTable);
        delete suchThatClauseEvaluator;
        REQUIRE(result == true);
        REQUIRE(generateResultSet(QueryEvaluator::generateResultString(resultTable)) == ResultSet{"prop", "pr"});
    }

    SECTION("select two synonyms") {
        /**
         * Modifies(p, v)
         * Type: Modifies, select second arg
         */
        auto *resultTable = new ResultTable();
        auto *suchThatClauseEvaluator = new ModifiesPClauseEvaluator(clause_p_v.argList, testPKB, &query_2);
        bool result = suchThatClauseEvaluator->evaluateClause(resultTable);
        delete suchThatClauseEvaluator;
        REQUIRE(result == true);
        REQUIRE(generateResultSet(QueryEvaluator::generateResultString(resultTable)) == ResultSet{{"prop x", "prop y", "prop z", "pr x"}});
        }

    SECTION("invalid query") {
        /**
         * Modifies(p, "x1")
         * Type: Modifies, select first arg, assign
         */
        auto *resultTable = new ResultTable();
        auto *suchThatClauseEvaluator = new ModifiesPClauseEvaluator(clause_p_x1.argList, testPKB, &query_3);
        bool result = suchThatClauseEvaluator->evaluateClause(resultTable);
        delete suchThatClauseEvaluator;
        REQUIRE(result == false);
        REQUIRE(generateResultSet(QueryEvaluator::generateResultString(resultTable)).empty());
    }
}

TEST_CASE("Test UsesP clause evaluator") {
    PKB *testPKB = generateSamplePKB();
    unordered_map<string, DesignEntity> declarations = {
            {"p", DesignEntity::PROCEDURE},
            {"v", DesignEntity::VARIABLE},
    };

    Argument a0 = {ArgumentType::UNDERSCORE, "_"};
    Argument av = {ArgumentType::SYNONYM, "v"};
    Argument aprop = {ArgumentType::IDENT, "prop"};
    Argument ap = {ArgumentType::SYNONYM, "p"};
    Argument ax = {ArgumentType::IDENT, "x"};
    Argument ax1 = {ArgumentType::IDENT, "x1"};

    SuchThatClause clause_prop_v = {ArgList{aprop, av},RelRef::USES_P};
    SuchThatClause clause_p_x = {ArgList{ap, ax},RelRef::USES_P};
    SuchThatClause clause_p_v = {ArgList{ap, av},RelRef::USES_P};
    SuchThatClause clause_p_x1 = {ArgList{ap, ax1},RelRef::USES_P};

    Argument dummySelect = {ArgumentType::SYNONYM, "s"};

    Query query_0 = makeQuery(declarations, {dummySelect}, {clause_prop_v});
    Query query_1 = makeQuery(declarations, {dummySelect}, {clause_p_x});
    Query query_2 = makeQuery(declarations, {dummySelect}, {clause_p_v});
    Query query_3 = makeQuery(declarations, {dummySelect}, {clause_p_x1});

    SECTION("select zero synonym") {
    }

    SECTION("select one synonym") {
        /**
         * Uses("prop", v)
         * Type: Uses, select second arg
         */
        auto *resultTable = new ResultTable();
        auto *suchThatClauseEvaluator = new UsesPClauseEvaluator(clause_prop_v.argList, testPKB, &query_0);
        bool result = suchThatClauseEvaluator->evaluateClause(resultTable);
        delete suchThatClauseEvaluator;
        REQUIRE(result == true);
        REQUIRE(generateResultSet(QueryEvaluator::generateResultString(resultTable)) == ResultSet{"x", "z", "y"});

        /**
         * Uses(p, "x")
         * Type: Uses, select first arg
         */
        resultTable = new ResultTable();
        suchThatClauseEvaluator = new UsesPClauseEvaluator(clause_p_x.argList, testPKB, &query_1);
        result = suchThatClauseEvaluator->evaluateClause(resultTable);
        delete suchThatClauseEvaluator;
        REQUIRE(result == true);
        REQUIRE(generateResultSet(QueryEvaluator::generateResultString(resultTable)) == ResultSet{"prop"});
    }

    SECTION("select two synonyms") {
        /**
         * Uses(p, v)
         */
        auto *resultTable = new ResultTable();
        auto *suchThatClauseEvaluator = new UsesPClauseEvaluator(clause_p_v.argList, testPKB, &query_2);
        bool result = suchThatClauseEvaluator->evaluateClause(resultTable);
        delete suchThatClauseEvaluator;
        REQUIRE(result == true);
        REQUIRE(generateResultSet(QueryEvaluator::generateResultString(resultTable)) == ResultSet{{"prop x", "prop y", "prop z", "pr y"}});
    }

    SECTION("invalid query") {
        /**
         * Uses(p, "x1")
         */
        auto *resultTable = new ResultTable();
        auto *suchThatClauseEvaluator = new UsesPClauseEvaluator(clause_p_x1.argList, testPKB, &query_3);
        bool result = suchThatClauseEvaluator->evaluateClause(resultTable);
        delete suchThatClauseEvaluator;
        REQUIRE(result == false);
        REQUIRE(generateResultSet(QueryEvaluator::generateResultString(resultTable)).empty());
    }
}

TEST_CASE("Test Next clause evaluator") {
    PKB *testPKB = generateSamplePKB();
    unordered_map<string, DesignEntity> declarations = {
            {"w", DesignEntity::WHILE},
            {"a", DesignEntity::ASSIGN},
            {"s1", DesignEntity::STMT},
            {"ifs", DesignEntity::IF},
    };

    Argument a0 = {ArgumentType::UNDERSCORE, "_"};
    Argument a5 = {ArgumentType::STMT_NO, "5"};
    Argument a9 = {ArgumentType::STMT_NO, "9"};
    Argument a10 = {ArgumentType::STMT_NO, "10"};
    Argument a11 = {ArgumentType::STMT_NO, "11"};
    Argument as1 = {ArgumentType::SYNONYM, "s1"};
    Argument aifs = {ArgumentType::SYNONYM, "ifs"};
    Argument aw = {ArgumentType::SYNONYM, "w"};
    Argument aa = {ArgumentType::SYNONYM, "a"};


    SuchThatClause clause_0_0 = {ArgList{a0, a0},RelRef::NEXT};
    SuchThatClause clause_10_5 = {ArgList{a10, a5},RelRef::NEXT};
    SuchThatClause clause_10_11 = {ArgList{a10, a11},RelRef::NEXT};
    SuchThatClause clause_11_0 = {ArgList{a11, a0},RelRef::NEXT};
    SuchThatClause clause_5_s1 = {ArgList{a5, as1},RelRef::NEXT};
    SuchThatClause clause_ifs_9 = {ArgList{aifs, a9},RelRef::NEXT};
    SuchThatClause clause_a_9 = {ArgList{aa, a9},RelRef::NEXT};
    SuchThatClause clause_ifs_s1 = {ArgList{aifs, as1},RelRef::NEXT};
    SuchThatClause clause_s1_w = {ArgList{as1, aw},RelRef::NEXT};

    Argument dummySelect = {ArgumentType::SYNONYM, "s"};

    Query query_0 = makeQuery(declarations, {dummySelect}, {clause_0_0});
    Query query_1 = makeQuery(declarations, {dummySelect}, {clause_10_5});
    Query query_2 = makeQuery(declarations, {dummySelect}, {clause_10_11});
    Query query_3 = makeQuery(declarations, {dummySelect}, {clause_11_0});
    Query query_4 = makeQuery(declarations, {dummySelect}, {clause_5_s1});
    Query query_5 = makeQuery(declarations, {dummySelect}, {clause_ifs_9});
    Query query_6 = makeQuery(declarations, {dummySelect}, {clause_a_9});
    Query query_7 = makeQuery(declarations, {dummySelect}, {clause_ifs_s1});
    Query query_8 = makeQuery(declarations, {dummySelect}, {clause_s1_w});

    SECTION("select zero synonym") {
        /**
        * Next(10, 5)
        */
        auto *resultTable = new ResultTable();
        auto *suchThatClauseEvaluator = new NextClauseEvaluator(clause_10_5.argList, testPKB, &query_1);
        bool result = suchThatClauseEvaluator->evaluateClause(resultTable);
        delete suchThatClauseEvaluator;
        REQUIRE(result == true);
        REQUIRE(generateResultSet(QueryEvaluator::generateResultString(resultTable)).empty());

        /**
        * Next(10, 11)
        */
        resultTable = new ResultTable();
        suchThatClauseEvaluator = new NextClauseEvaluator(clause_10_11.argList, testPKB, &query_2);
        result = suchThatClauseEvaluator->evaluateClause(resultTable);
        delete suchThatClauseEvaluator;
        REQUIRE(result == false);
        REQUIRE(generateResultSet(QueryEvaluator::generateResultString(resultTable)).empty());

        /**
        * Next(11, _)
        */
        resultTable = new ResultTable();
        suchThatClauseEvaluator = new NextClauseEvaluator(clause_11_0.argList, testPKB, &query_3);
        result = suchThatClauseEvaluator->evaluateClause(resultTable);
        delete suchThatClauseEvaluator;
        REQUIRE(result == false);
        REQUIRE(generateResultSet(QueryEvaluator::generateResultString(resultTable)).empty());
    }

    SECTION("select one synonym") {
        /**
         * Next(5, s1)
         */
        auto *resultTable = new ResultTable();
        auto *suchThatClauseEvaluator = new NextClauseEvaluator(clause_5_s1.argList, testPKB, &query_4);
        bool result = suchThatClauseEvaluator->evaluateClause(resultTable);
        delete suchThatClauseEvaluator;
        REQUIRE(result == true);
        REQUIRE(generateResultSet(QueryEvaluator::generateResultString(resultTable)) == ResultSet{{"6", "11"}});

        /**
         * Next(ifs, 9)
         */
        resultTable = new ResultTable();
        suchThatClauseEvaluator = new NextClauseEvaluator(clause_ifs_9.argList, testPKB, &query_5);
        result = suchThatClauseEvaluator->evaluateClause(resultTable);
        delete suchThatClauseEvaluator;
        REQUIRE(result == true);
        REQUIRE(generateResultSet(QueryEvaluator::generateResultString(resultTable)) == ResultSet{{"7"}});

        /**
         * Next(a, 9)
         */
        resultTable = new ResultTable();
        suchThatClauseEvaluator = new NextClauseEvaluator(clause_a_9.argList, testPKB, &query_6);
        result = suchThatClauseEvaluator->evaluateClause(resultTable);
        delete suchThatClauseEvaluator;
        REQUIRE(result == false);
        REQUIRE(generateResultSet(QueryEvaluator::generateResultString(resultTable)).empty());
    }

    SECTION("select two synonyms") {
        /**
         * Next(ifs, s1)
         */
        auto *resultTable = new ResultTable();
        auto *suchThatClauseEvaluator = new NextClauseEvaluator(clause_ifs_s1.argList, testPKB, &query_7);
        bool result = suchThatClauseEvaluator->evaluateClause(resultTable);
        delete suchThatClauseEvaluator;
        REQUIRE(result == true);
        REQUIRE(generateResultSet(QueryEvaluator::generateResultString(resultTable)) == ResultSet{{"7 8", "7 9"}});

        /**
         * Next(s1, w)
         */
        resultTable = new ResultTable();
        suchThatClauseEvaluator = new NextClauseEvaluator(clause_s1_w.argList, testPKB, &query_8);
        result = suchThatClauseEvaluator->evaluateClause(resultTable);
        delete suchThatClauseEvaluator;
        REQUIRE(result == true);
        REQUIRE(generateResultSet(QueryEvaluator::generateResultString(resultTable)) == ResultSet{{"10 5", "4 5"}});
    }

    SECTION("invalid query") {
    }
}

TEST_CASE("Test NextT clause evaluator") {
    PKB *testPKB = generateSamplePKB();
    unordered_map<string, DesignEntity> declarations = {
            {"w", DesignEntity::WHILE},
            {"a", DesignEntity::ASSIGN},
            {"s1", DesignEntity::STMT},
            {"ifs", DesignEntity::IF},
            {"pn", DesignEntity::PRINT},
            {"r", DesignEntity::READ},

    };

    Argument a0 = {ArgumentType::UNDERSCORE, "_"};
    Argument a5 = {ArgumentType::STMT_NO, "5"};
    Argument a6 = {ArgumentType::STMT_NO, "6"};
    Argument a9 = {ArgumentType::STMT_NO, "9"};
    Argument a10 = {ArgumentType::STMT_NO, "10"};
    Argument a11 = {ArgumentType::STMT_NO, "11"};
    Argument as1 = {ArgumentType::SYNONYM, "s1"};
    Argument aifs = {ArgumentType::SYNONYM, "ifs"};
    Argument aw = {ArgumentType::SYNONYM, "w"};
    Argument aa = {ArgumentType::SYNONYM, "a"};
    Argument ar = {ArgumentType::SYNONYM, "r"};
    Argument apn = {ArgumentType::SYNONYM, "pn"};


    SuchThatClause clause_0_0 = {ArgList{a0, a0},RelRef::NEXT_T};
    SuchThatClause clause_6_6 = {ArgList{a6, a6},RelRef::NEXT_T};
    SuchThatClause clause_10_11 = {ArgList{a10, a11},RelRef::NEXT_T};
    SuchThatClause clause_11_0 = {ArgList{a11, a0},RelRef::NEXT_T};
    SuchThatClause clause_5_s1 = {ArgList{a5, as1},RelRef::NEXT_T};
    SuchThatClause clause_ifs_11 = {ArgList{aifs, a11},RelRef::NEXT_T};
    SuchThatClause clause_a_9 = {ArgList{aa, a9},RelRef::NEXT_T};
    SuchThatClause clause_ifs_s1 = {ArgList{aifs, as1},RelRef::NEXT_T};
    SuchThatClause clause_s1_w = {ArgList{as1, aw},RelRef::NEXT_T};
    SuchThatClause clause_r_pn = {ArgList{ar, apn},RelRef::NEXT_T};

    Argument dummySelect = {ArgumentType::SYNONYM, "s"};

    Query query_0 = makeQuery(declarations, {dummySelect}, {clause_0_0});
    Query query_1 = makeQuery(declarations, {dummySelect}, {clause_6_6});
    Query query_2 = makeQuery(declarations, {dummySelect}, {clause_10_11});
    Query query_3 = makeQuery(declarations, {dummySelect}, {clause_11_0});
    Query query_4 = makeQuery(declarations, {dummySelect}, {clause_5_s1});
    Query query_5 = makeQuery(declarations, {dummySelect}, {clause_ifs_11});
    Query query_6 = makeQuery(declarations, {dummySelect}, {clause_a_9});
    Query query_7 = makeQuery(declarations, {dummySelect}, {clause_ifs_s1});
    Query query_8 = makeQuery(declarations, {dummySelect}, {clause_s1_w});
    Query query_9 = makeQuery(declarations, {dummySelect}, {clause_r_pn});

    SECTION("select zero synonym") {
        /**
        * Next*(6, 6)
        */
        auto *resultTable = new ResultTable();
        auto *suchThatClauseEvaluator = new NextTClauseEvaluator(clause_6_6.argList, testPKB, &query_1);
        bool result = suchThatClauseEvaluator->evaluateClause(resultTable);
        delete suchThatClauseEvaluator;
        REQUIRE(result == true);
        REQUIRE(generateResultSet(QueryEvaluator::generateResultString(resultTable)).empty());

        /**
        * Next*(10, 11)
        */
        resultTable = new ResultTable();
        suchThatClauseEvaluator = new NextTClauseEvaluator(clause_10_11.argList, testPKB, &query_2);
        result = suchThatClauseEvaluator->evaluateClause(resultTable);
        delete suchThatClauseEvaluator;
        REQUIRE(result == true);
        REQUIRE(generateResultSet(QueryEvaluator::generateResultString(resultTable)).empty());

        /**
        * Next*(11, _)
        */
        resultTable = new ResultTable();
        suchThatClauseEvaluator = new NextTClauseEvaluator(clause_11_0.argList, testPKB, &query_3);
        result = suchThatClauseEvaluator->evaluateClause(resultTable);
        delete suchThatClauseEvaluator;
        REQUIRE(result == false);
        REQUIRE(generateResultSet(QueryEvaluator::generateResultString(resultTable)).empty());
    }

    SECTION("select one synonym") {
        /**
         * Next*(5, s1)
         */
        auto *resultTable = new ResultTable();
        auto *suchThatClauseEvaluator = new NextTClauseEvaluator(clause_5_s1.argList, testPKB, &query_4);
        bool result = suchThatClauseEvaluator->evaluateClause(resultTable);
        delete suchThatClauseEvaluator;
        REQUIRE(result == true);
        REQUIRE(generateResultSet(QueryEvaluator::generateResultString(resultTable)) == ResultSet{{"5", "6", "7", "8", "9", "10", "11"}});

        /**
         * Next*(ifs, 11)
         */
        resultTable = new ResultTable();
        suchThatClauseEvaluator = new NextTClauseEvaluator(clause_ifs_11.argList, testPKB, &query_5);
        result = suchThatClauseEvaluator->evaluateClause(resultTable);
        delete suchThatClauseEvaluator;
        REQUIRE(result == true);
        REQUIRE(generateResultSet(QueryEvaluator::generateResultString(resultTable)) == ResultSet{{"7"}});

        /**
         * Next*(a, 9)
         */
        resultTable = new ResultTable();
        suchThatClauseEvaluator = new NextTClauseEvaluator(clause_a_9.argList, testPKB, &query_6);
        result = suchThatClauseEvaluator->evaluateClause(resultTable);
        delete suchThatClauseEvaluator;
        REQUIRE(result == true);
        REQUIRE(generateResultSet(QueryEvaluator::generateResultString(resultTable))
                == ResultSet{{"2", "3", "8", "9", "10"}}
        );
    }

    SECTION("select two synonyms") {
        /**
         * Next*(ifs, s1)
         */
        auto *resultTable = new ResultTable();
        auto *suchThatClauseEvaluator = new NextTClauseEvaluator(clause_ifs_s1.argList, testPKB, &query_7);
        bool result = suchThatClauseEvaluator->evaluateClause(resultTable);
        delete suchThatClauseEvaluator;
        REQUIRE(result == true);
        REQUIRE(generateResultSet(QueryEvaluator::generateResultString(resultTable)) ==
        ResultSet{{"7 8", "7 9", "7 10", "7 5", "7 6", "7 7", "7 11"}}
        );

        /**
         * Next*(s1, w)
         */
        resultTable = new ResultTable();
        suchThatClauseEvaluator = new NextTClauseEvaluator(clause_s1_w.argList, testPKB, &query_8);
        result = suchThatClauseEvaluator->evaluateClause(resultTable);
        delete suchThatClauseEvaluator;
        REQUIRE(result == true);
        REQUIRE(generateResultSet(QueryEvaluator::generateResultString(resultTable)) ==
        ResultSet{{"1 5", "2 5", "3 5", "4 5", "5 5", "6 5", "7 5", "8 5", "9 5", "10 5"}}
        );

        /**
         * Next*(r, pn)
         */
        resultTable = new ResultTable();
        suchThatClauseEvaluator = new NextTClauseEvaluator(clause_r_pn.argList, testPKB, &query_9);
        result = suchThatClauseEvaluator->evaluateClause(resultTable);
        delete suchThatClauseEvaluator;
        REQUIRE(result == true);
        REQUIRE(generateResultSet(QueryEvaluator::generateResultString(resultTable)) ==
                ResultSet{{"1 4", "1 11"}}
        );
    }

    SECTION("invalid query") {
    }
}