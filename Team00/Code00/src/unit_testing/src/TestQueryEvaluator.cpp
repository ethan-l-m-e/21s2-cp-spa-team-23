//
// Created by Tianyi Wang on 14/2/22.
//

#include "pql/QueryEvaluator.h"

#include <utility>
#include "catch.hpp"
#include "Parser.h"

using namespace std;
using ArgList = std::vector<Argument>;
using ResultSet = std::unordered_set<string>;

PKB* generateSamplePKB() {
    PKB *testPKB = PKB::getInstance();
/**
 * Procedure p {
 * 01 read x;
 * 02 y = yeast + zealous + x;
 * 03 zealous = 3;
 * 04 print xylophone;
 * 05 while (z == 1) {
 * 06    x = 5 + x;
 *    };
 * }
 */
    testPKB->clearPKB();
    testPKB->addProcedure("p");
    testPKB->addVariable("x");
    testPKB->addVariable("y");
    testPKB->addVariable("z");
    testPKB->addVariable("xylophone");
    testPKB->addVariable("yeast");
    testPKB->addVariable("zealous");
    testPKB->addConstant("1");
    testPKB->addConstant("3");
    testPKB->addConstant("5");


    testPKB->addReadStatement(1);
    testPKB->addAssignStatement(2);
    testPKB->addAssignStatement(3);
    testPKB->addPrintStatement(4);
    testPKB->addWhileStatement(5);
    testPKB->addAssignStatement(6);

    testPKB->setFollows(1, 2);
    testPKB->setFollows(2, 3);
    testPKB->setFollows(3, 4);
    testPKB->setFollows(4, 5);
    testPKB->setParent(5, 6);

    testPKB->setFollowsT(1,2);
    testPKB->setFollowsT(1,3);
    testPKB->setFollowsT(1,4);
    testPKB->setFollowsT(1,5);
    testPKB->setFollowsT(2,3);
    testPKB->setFollowsT(2,4);
    testPKB->setFollowsT(2,5);
    testPKB->setFollowsT(3,4);
    testPKB->setFollowsT(3,5);
    testPKB->setFollowsT(4,5);
    testPKB->setParentT(5,6);

    testPKB->setModifies(1, {"x"});
    testPKB->setModifies(2, {"y"});
    testPKB->setModifies(3, {"zealous"});
    testPKB->setModifies(6, {"x"});
    testPKB->setModifies(5, {"x"});


    testPKB->setUses(2, {"yeast", "zealous", "x"});
    testPKB->setUses(4, {"xylophone"});
    testPKB->setUses(5, {"z", "x"});
    testPKB->setUses(6, {"x"});

    return testPKB;
}

Query makeQuery(unordered_map<string, DesignEntity>& declarations, string synonym) {
    Query query;
    query.setDeclarations(declarations);
    query.setSynonym(std::move(synonym));
    return query;
}

Query makeQuery(unordered_map<string, DesignEntity>& declarations, string synonym, vector<SuchThatClause> suchThatClauses, vector<PatternClause> patternClauses) {
    Query query;
    query.setDeclarations(declarations);
    query.setSynonym(std::move(synonym));
    query.setSuchThatClauses(std::move(suchThatClauses));
    query.setPatternClauses(std::move(patternClauses));
    return query;
}

Query makeQuery(unordered_map<string, DesignEntity>& declarations, string synonym, vector<SuchThatClause> suchThatClauses) {
    Query query;
    query.setDeclarations(declarations);
    query.setSynonym(std::move(synonym));
    query.setSuchThatClauses(std::move(suchThatClauses));
    return query;
}

ResultSet generateResultSet (list<string> result) {
    return {std::begin(result), std::end(result)};
}


TEST_CASE("Select query with no clauses") {
    PKB *testPKB = generateSamplePKB();
    unordered_map<string, DesignEntity> declarations = {{"v", DesignEntity::VARIABLE},
                                                           {"a", DesignEntity::ASSIGN},
                                                           {"pn", DesignEntity::PRINT},
                                                           {"s", DesignEntity::STMT}
                                                           };
    Query query_1 = makeQuery(declarations, "v");
    Query query_2 = makeQuery(declarations, "s");
    Query query_3 = makeQuery(declarations, "pn");
    Query query_4 = makeQuery(declarations, "a");
    Query query_5 = makeQuery(declarations, "x");

    auto qe = QueryEvaluator(testPKB);

    /**
     * Select v
     * Type: select all variables
     */
    list<string> result1 = qe.evaluate(&query_1);
    REQUIRE(generateResultSet(result1) == ResultSet {"x", "y", "xylophone", "yeast", "z", "zealous"});

    /**
     * Select s
     * Type: select all statements
     */
    list<string> result2 = qe.evaluate(&query_2);
    REQUIRE(generateResultSet(result2) == ResultSet {"1", "2", "3", "4", "5", "6"});

    /**
     * Select pn
     * Type: select all print
     */
    list<string> result3 = qe.evaluate(&query_3);
    REQUIRE(generateResultSet(result3) == ResultSet {"4"});

    /**
     * Select a
     * Type: select all assign
     */
    list<string> result4 = qe.evaluate(&query_4);
    REQUIRE(generateResultSet(result4) == ResultSet {"2", "3", "6"});

    /*
    list<string> result5 = qe.evaluate(&query_5);

    REQUIRE(generateResultSet(result5).empty());
    */

}

TEST_CASE("Follows/Parent/Follows* clause: 0 or 1 synonym") {
    PKB *testPKB = generateSamplePKB();
    unordered_map<string, DesignEntity> declarations = {{"s", DesignEntity::STMT}};
    Argument a0 = {ArgumentType::UNDERSCORE, "_"};
    Argument as = {ArgumentType::SYNONYM, "s"};
    Argument a3 = {ArgumentType::STMT_NO, "3"};
    Argument a5 = {ArgumentType::STMT_NO, "5"};
    Argument a6 = {ArgumentType::STMT_NO, "6"};
    Argument a10 = {ArgumentType::STMT_NO, "10"};
    Argument a00 = {ArgumentType::STMT_NO, "0"};

    SuchThatClause clause1 = {ArgList{a3, as},RelRef::FOLLOWS};
    SuchThatClause clause2 = {ArgList{as, a3},RelRef::FOLLOWS};
    SuchThatClause clause3 = {ArgList{a0, as},RelRef::FOLLOWS};
    SuchThatClause clause4 = {ArgList{a0, a0},RelRef::FOLLOWS};
    SuchThatClause clause5 = {ArgList{as, a6},RelRef::PARENT};
    SuchThatClause clause6 = {ArgList{a5, as},RelRef::PARENT};
    SuchThatClause clause7 = {ArgList{as, a0},RelRef::PARENT};
    SuchThatClause clause8 = {ArgList{a0, as},RelRef::PARENT};
    SuchThatClause clause9 = {ArgList{a0, a10},RelRef::FOLLOWS};
    SuchThatClause clause10 = {ArgList{a00, as},RelRef::PARENT};

    Query query_1 = makeQuery(declarations, "s", {clause1});
    Query query_2 = makeQuery(declarations, "s", {clause2});
    Query query_3 = makeQuery(declarations, "s", {clause3});
    Query query_4 = makeQuery(declarations, "s", {clause4});
    Query query_5 = makeQuery(declarations, "s", {clause5});
    Query query_6 = makeQuery(declarations, "s", {clause6});
    Query query_7 = makeQuery(declarations, "s", {clause7});
    Query query_8 = makeQuery(declarations, "s", {clause8});
    Query query_9 = makeQuery(declarations, "s", {clause9});
    Query query_10 = makeQuery(declarations, "s", {clause10});

    auto qe = QueryEvaluator(testPKB);

    SECTION("valid cases") {
        /**
         * Select s such that Follows(3, s)
         * Type: follows, select second arg
         */
        list<string> result1 = qe.evaluate(&query_1);
        REQUIRE(generateResultSet(result1) == ResultSet{"4"});

        /**
         * Select s such that Follows(s, 3)
         * Type: follows, select first arg
         */
        list<string> result2 = qe.evaluate(&query_2);
        REQUIRE(generateResultSet(result2) == ResultSet{"2"});

        /**
         * Select s such that Follows(_, s)
         * Type: follows, select second arg, wildcard
         */
        list<string> result3 = qe.evaluate(&query_3);
        REQUIRE(generateResultSet(result3) == ResultSet{"2", "3", "4", "5"});
        /**
         * Select s such that Follows(_, _)
         * Type: follows, boolean, wildcard
         */
        list<string> result4 = qe.evaluate(&query_4);
        REQUIRE(generateResultSet(result4) == ResultSet{"1", "2", "3", "4", "5", "6"});

        /**
         * Select s such that Parent(s, 6)
         * Type: parent, select first arg
         */
        list<string> result5 = qe.evaluate(&query_5);
        REQUIRE(generateResultSet(result5) == ResultSet{"5"});
        /**
         * Select s such that Parent(5, s)
         * Type: parent, select second arg
         */
        list<string> result6 = qe.evaluate(&query_6);
        REQUIRE(generateResultSet(result6) == ResultSet{"6"});

        /**
         * Select s such that Parent(s, _)
         * Type: parent, select first arg, wildcard
         */
        list<string> result7 = qe.evaluate(&query_7);
        REQUIRE(generateResultSet(result7) == ResultSet{"5"});
        /**
         * Select s such that Parent(_, s)
         * Type: parent, select second arg, wildcard
         */
        list<string> result8 = qe.evaluate(&query_8);
        REQUIRE(generateResultSet(result8) == ResultSet{"6"});
    }

    SECTION("invalid cases") {
        /**
         * Select s such that Follows(_, 10)
         * Type: follows, boolean, semantic error
         */
        list<string> result9 = qe.evaluate(&query_9);
        REQUIRE(generateResultSet(result9).empty());

        /**
         * Select s such that Parent(0, s)
         * Type: follows, one synonym, semantic error
         */
        list<string> result10 = qe.evaluate(&query_10);
        REQUIRE(generateResultSet(result10).empty());
    }

}

TEST_CASE("Follows/Parent/Follows* clause: 1 synonym with stmt type") {
    PKB *testPKB = generateSamplePKB();
    unordered_map<string, DesignEntity> declarations = {{"s", DesignEntity::STMT},
                                                           {"a", DesignEntity::ASSIGN},
                                                           {"pn", DesignEntity::PRINT},
                                                           {"r", DesignEntity::READ},
                                                           {"c", DesignEntity::CONSTANT},};
    Argument a0 = {ArgumentType::UNDERSCORE, "_"};
    Argument a1 = {ArgumentType::STMT_NO, "1"};
    Argument a2 = {ArgumentType::STMT_NO, "2"};
    Argument a3 = {ArgumentType::STMT_NO, "3"};
    Argument a5 = {ArgumentType::STMT_NO, "5"};
    Argument as = {ArgumentType::SYNONYM, "s"};
    Argument aa = {ArgumentType::SYNONYM, "a"};
    Argument apn = {ArgumentType::SYNONYM, "pn"};
    Argument ar = {ArgumentType::SYNONYM, "r"};
    Argument ac = {ArgumentType::SYNONYM, "c"};

    SuchThatClause clause_0_a = {ArgList{a0, aa}, RelRef::FOLLOWS};
    SuchThatClause clause_1_a = {ArgList{a1, aa},RelRef::FOLLOWS_T};
    SuchThatClause clause_a_2 = {ArgList{aa, a2},RelRef::FOLLOWS};
    SuchThatClause clause_pn_0 = {ArgList{apn, a0},RelRef::FOLLOWS};
    SuchThatClause clause_2_pn = {ArgList{a2, apn},RelRef::FOLLOWS};
    SuchThatClause clause_r_2 = {ArgList{ar, a2},RelRef::FOLLOWS};
    SuchThatClause clause_5_r = {ArgList{a5, ar},RelRef::FOLLOWS};
    SuchThatClause clause_5_a = {ArgList{a5, aa},RelRef::PARENT};
    SuchThatClause clause_3_c = {ArgList{a3, ac},RelRef::FOLLOWS};

    Query query_1 = makeQuery(declarations, "a", {clause_0_a});
    Query query_2 = makeQuery(declarations, "a", {clause_1_a});
    Query query_3 = makeQuery(declarations, "a", {clause_a_2});
    Query query_4 = makeQuery(declarations, "pn", {clause_pn_0});
    Query query_5 = makeQuery(declarations, "pn", {clause_2_pn});
    Query query_6 = makeQuery(declarations, "r", {clause_r_2});
    Query query_7 = makeQuery(declarations, "r", {clause_5_r});
    Query query_8 = makeQuery(declarations, "a", {clause_5_a});
    Query query_9 = makeQuery(declarations, "a", {clause_3_c});

    auto qe = QueryEvaluator(testPKB);

    SECTION("valid cases") {
        /**
         * Select a such that Follows(_, a)
         * Type: follows, select second arg, wildcard, assign
         */
        list<string> result1 = qe.evaluate(&query_1);
        REQUIRE(generateResultSet(result1) == ResultSet{"2", "3"});

        /**
         * Select a such that Follows*(1, a)
         * Type: follows*, select second arg, assign
         */
        list<string> result2 = qe.evaluate(&query_2);
        REQUIRE(generateResultSet(result2) == ResultSet{"2", "3"});

        /**
         * Select a such that Follows(a, 2)
         * Type: follows, select first arg, assign
         */
        list<string> result3 = qe.evaluate(&query_3);
        REQUIRE(generateResultSet(result3).empty());

        /**
         * Select pn such that Follows(pn, _)
         * Type: follows, select first arg, wildcard, print
         */
        list<string> result4 = qe.evaluate(&query_4);
        REQUIRE(generateResultSet(result4) == ResultSet{"4"});

        /**
         * Select pn such that Follows(2, pn)
         * Type: follows, select second arg, print
         */
        list<string> result5 = qe.evaluate(&query_5);
        REQUIRE(generateResultSet(result5).empty());

        /**
         * Select r such that Follows(r, 2)
         * Type: follows, select first arg, read
         */
        list<string> result6 = qe.evaluate(&query_6);
        REQUIRE(generateResultSet(result6) == ResultSet{"1"});

        /**
         * Select r such that Follows(5, r)
         * Type: follows, select second arg, read
         */
        list<string> result7 = qe.evaluate(&query_7);
        REQUIRE(generateResultSet(result7).empty());

        /**
         * Select a such that Parent(5, a)
         * Type: parent, select second arg, assign
         */
        list<string> result8 = qe.evaluate(&query_8);
        REQUIRE(generateResultSet(result8) == ResultSet{"6"});
    }

    SECTION("invalid cases") {
        /**
         * Select a such that Follows(3, c)
         * Type: parent, select second arg, assign
         */
        list<string> result9 = qe.evaluate(&query_9);
        REQUIRE(generateResultSet(result9).empty());
    }

}

TEST_CASE("Follows/Parent/Follows* clause: 2 synonyms") {
    PKB *testPKB = generateSamplePKB();
    unordered_map<string, DesignEntity> declarations = {{"s1", DesignEntity::STMT},
                                                           {"s2", DesignEntity::STMT},
                                                           {"s", DesignEntity::STMT}};
    Argument as1 = {ArgumentType::SYNONYM, "s1"};
    Argument as2 = {ArgumentType::SYNONYM, "s2"};

    SuchThatClause clause1 = {ArgList{as1, as2},RelRef::FOLLOWS};
    SuchThatClause clause2 = {ArgList{as1, as2},RelRef::PARENT};
    SuchThatClause clause3 = {ArgList{as1, as2},RelRef::FOLLOWS_T};

    Query query_1;
    query_1.setDeclarations(declarations);
    query_1.setSynonym("s");
    query_1.setSuchThatClauses(vector<SuchThatClause>{clause1});

    Query query_2;
    query_2.setDeclarations(declarations);
    query_2.setSynonym("s2");
    query_2.setSuchThatClauses(vector<SuchThatClause>{clause1});

    Query query_3;
    query_3.setDeclarations(declarations);
    query_3.setSynonym("s1");
    query_3.setSuchThatClauses(vector<SuchThatClause>{clause2});

    Query query_4;
    query_4.setDeclarations(declarations);
    query_4.setSynonym("s2");
    query_4.setSuchThatClauses(vector<SuchThatClause>{clause2});

    Query query_5;
    query_5.setDeclarations(declarations);
    query_5.setSynonym("s2");
    query_5.setSuchThatClauses(vector<SuchThatClause>{clause3});


    auto qe = QueryEvaluator(testPKB);

    /**
     * Select s such that Follows(s1, s2)
     * Type: follows, select none
     */
    list<string> result1 = qe.evaluate(&query_1);
    REQUIRE(generateResultSet(result1) == ResultSet{"1", "2", "3", "4", "5", "6"});

    /**
     * Select s2 such that Follows(s1, s2)
     * Type: follows, select second arg
     */
    list<string> result2 = qe.evaluate(&query_2);
    REQUIRE(generateResultSet(result2) == ResultSet{"2", "3", "4", "5"});

    /**
     * Select s1 such that Parent(s1, s2)
     * Type: parent, select first arg
     */
    list<string> result3 = qe.evaluate(&query_3);
    REQUIRE(generateResultSet(result3) == ResultSet{"5"});

    /**
     * Select s2 such that Parent(s1, s2)
     * Type: parent, select second arg
     */
    list<string> result4 = qe.evaluate(&query_4);
    REQUIRE(generateResultSet(result4) == ResultSet{"6"});

    /**
     * Select s2 such that Follows*(s1, s2)
     * Type: follows*, select second arg
     */
    list<string> result5 = qe.evaluate(&query_5);
    REQUIRE(generateResultSet(result5) == ResultSet{"2", "3", "4", "5"});
}

TEST_CASE("Follows/Parent/Follows* clause: 2 synonyms with type") {
    PKB *testPKB = generateSamplePKB();
    unordered_map<string, DesignEntity> declarations = {{"s", DesignEntity::STMT},
                                                           {"a", DesignEntity::ASSIGN},
                                                           {"pn", DesignEntity::PRINT},
                                                           {"r", DesignEntity::READ},
                                                           {"w", DesignEntity::WHILE},};
    Argument as = {ArgumentType::SYNONYM, "s"};
    Argument aa = {ArgumentType::SYNONYM, "a"};
    Argument apn = {ArgumentType::SYNONYM, "pn"};
    Argument ar = {ArgumentType::SYNONYM, "r"};
    Argument aw = {ArgumentType::SYNONYM, "w"};

    SuchThatClause clauseT_s_pn = {ArgList{as, apn},RelRef::FOLLOWS_T};
    SuchThatClause clause_s_pn = {ArgList{as, apn},RelRef::FOLLOWS};
    SuchThatClause clause_r_a = {ArgList{ar, aa},RelRef::FOLLOWS};
    SuchThatClause clause_w_a = {ArgList{aw, aa},RelRef::PARENT};

    Query query_1 = makeQuery(declarations, "s", {clauseT_s_pn});
    Query query_2 = makeQuery(declarations, "pn", {clause_s_pn});
    Query query_3 = makeQuery(declarations, "r", {clause_r_a});
    Query query_4 = makeQuery(declarations, "w", {clause_w_a});

    auto qe = QueryEvaluator(testPKB);

    /**
     * Select s such that Follows*(s, p)
     * Type: follows*, select first arg
     */
    list<string> result1 = qe.evaluate(&query_1);
    REQUIRE(generateResultSet(result1) == ResultSet {"1", "2", "3"});

    /**
     * Select p such that Follows(s, p)
     * Type: follows, select second arg
     */
    list<string> result2 = qe.evaluate(&query_2);
    REQUIRE(generateResultSet(result2) == ResultSet {"4"});

    /**
     * Select r such that Follows(r, a)
     * Type: parent, select first arg
     */
    list<string> result3 = qe.evaluate(&query_3);
    REQUIRE(generateResultSet(result3) == ResultSet {"1"});

    /**
     * Select w such that Parent(w, a)
     * Type: parent, select first arg
     */
    list<string> result4 = qe.evaluate(&query_4);
    REQUIRE(generateResultSet(result4) == ResultSet {"5"});

}

TEST_CASE("Modifies/Uses clause: 1 synonym with stmt type") {
    PKB *testPKB = generateSamplePKB();
    unordered_map<string, DesignEntity> declarations = {{"s", DesignEntity::STMT},
                                                           {"a", DesignEntity::ASSIGN},
                                                           {"pn", DesignEntity::PRINT},
                                                           {"r", DesignEntity::READ},
                                                           {"c", DesignEntity::CONSTANT},
                                                           {"v", DesignEntity::VARIABLE},
                                                           };
    Argument a0 = {ArgumentType::UNDERSCORE, "_"};
    Argument a1 = {ArgumentType::STMT_NO, "1"};
    Argument a2 = {ArgumentType::STMT_NO, "2"};
    Argument a3 = {ArgumentType::STMT_NO, "3"};
    Argument a5 = {ArgumentType::STMT_NO, "5"};
    Argument a6 = {ArgumentType::STMT_NO, "6"};
    Argument as = {ArgumentType::SYNONYM, "s"};
    Argument aa = {ArgumentType::SYNONYM, "a"};
    Argument apn = {ArgumentType::SYNONYM, "pn"};
    Argument ar = {ArgumentType::SYNONYM, "r"};
    Argument ac = {ArgumentType::SYNONYM, "c"};
    Argument av = {ArgumentType::SYNONYM, "v"};
    Argument ax = {ArgumentType::IDENT, "x"};
    Argument az = {ArgumentType::IDENT, "z"};

    SuchThatClause clause_2_v = {ArgList{a2, av},RelRef::USES_S};
    SuchThatClause clauseU_s_x = {ArgList{as, ax},RelRef::USES_S};
    SuchThatClause clause_a_0 = {ArgList{aa, a0},RelRef::USES_S};
    SuchThatClause clause_a_z = {ArgList{aa, az},RelRef::USES_S};
    SuchThatClause clause_6_v = {ArgList{a6, av},RelRef::MODIFIES_S};
    SuchThatClause clause_r_x = {ArgList{ar, ax},RelRef::MODIFIES_S};
    SuchThatClause clauseM_s_x = {ArgList{as, ax},RelRef::MODIFIES_S};
    SuchThatClause clause_s_0 = {ArgList{as, a0},RelRef::MODIFIES_S};

    Query query_1 = makeQuery(declarations, "v", {clause_2_v});
    Query query_2 = makeQuery(declarations, "s", {clauseU_s_x});
    Query query_3 = makeQuery(declarations, "a", {clause_a_0});
    Query query_4 = makeQuery(declarations, "a", {clause_a_z});
    Query query_5 = makeQuery(declarations, "v", {clause_6_v});
    Query query_6 = makeQuery(declarations, "r", {clause_r_x});
    Query query_7 = makeQuery(declarations, "s", {clauseM_s_x});
    Query query_8 = makeQuery(declarations, "s", {clause_s_0});

    auto qe = QueryEvaluator(testPKB);
    /**
     * Select v such that Uses(2, v)
     * Type: uses, select second arg
     */
    list<string> result1 = qe.evaluate(&query_1);
    REQUIRE(generateResultSet(result1) == ResultSet {"yeast", "zealous", "x"});

    /**
     * Select s such that Uses(s, "x")
     * Type: uses, select first arg
     */
    list<string> result2 = qe.evaluate(&query_2);
    REQUIRE(generateResultSet(result2) == ResultSet {"2", "5", "6"});

    /**
     * Select a such that Uses(a, _) {"2", "6"}
     * Type: uses, select first arg, wildcard
     */
    list<string> result3 = qe.evaluate(&query_3);
    REQUIRE(generateResultSet(result3) == ResultSet {"2", "6"});

    /**
     * Select a such that Uses(a, "z") {}
     * Type: uses, select first arg, assign
     */
    list<string> result4 = qe.evaluate(&query_4);
    REQUIRE(generateResultSet(result4).empty());

    /**
     * Select v such that Modifies(6, v)
     * Type: modifies, select second arg
     */
    list<string> result5 = qe.evaluate(&query_5);
    REQUIRE(generateResultSet(result5) == ResultSet {"x"});

    /**
     * Select r such that Modifies(r, "x")
     * Type: modifies, select first arg, read
     */
    list<string> result6 = qe.evaluate(&query_6);
    REQUIRE(generateResultSet(result6) == ResultSet {"1"});

    /**
     * Select s such that Modifies(s, "x")
     * Type: modifies, select second arg, read
     */
    list<string> result7 = qe.evaluate(&query_7);
    REQUIRE(generateResultSet(result7) == ResultSet {"1", "5", "6"});

    /**
     * Select s such that Modifies(s, _) {"1", "2", "3", "6"}
     * Type: modifies, select first arg, assign
     */
    list<string> result8 = qe.evaluate(&query_8);
    REQUIRE(generateResultSet(result8) == ResultSet {"1", "2", "3", "5", "6"});

}

TEST_CASE("Modifies/Uses clause: 2 synonyms with stmt type") {
    PKB *testPKB = generateSamplePKB();
    unordered_map<string, DesignEntity> declarations = {{"s", DesignEntity::STMT},
                                                           {"a", DesignEntity::ASSIGN},
                                                           {"pn", DesignEntity::PRINT},
                                                           {"r", DesignEntity::READ},
                                                           {"c", DesignEntity::CONSTANT},
                                                           {"v", DesignEntity::VARIABLE},
                                                           {"w", DesignEntity::WHILE},
    };
    Argument a0 = {ArgumentType::UNDERSCORE, "_"};
    Argument aa = {ArgumentType::SYNONYM, "a"};
    Argument apn = {ArgumentType::SYNONYM, "pn"};
    Argument ar = {ArgumentType::SYNONYM, "r"};
    Argument ac = {ArgumentType::SYNONYM, "c"};
    Argument av = {ArgumentType::SYNONYM, "v"};
    Argument aw = {ArgumentType::SYNONYM, "w"};
    Argument as = {ArgumentType::SYNONYM, "s"};

    SuchThatClause clauseU_s_v = {ArgList{as, av},RelRef::USES_S};
    SuchThatClause clause_a_v = {ArgList{aa, av},RelRef::USES_S};
    SuchThatClause clause_pn_v = {ArgList{apn, av},RelRef::USES_S};
    SuchThatClause clause_r_v = {ArgList{ar, av},RelRef::USES_S};
    SuchThatClause clauseM_s_v = {ArgList{as, av},RelRef::MODIFIES_S};
    SuchThatClause clause_w_v = {ArgList{aw, av},RelRef::MODIFIES_S};

    Query query_1 = makeQuery(declarations, "s", {clauseU_s_v});
    Query query_2 = makeQuery(declarations, "a", {clause_a_v});
    Query query_3 = makeQuery(declarations, "v", {clause_pn_v});
    Query query_4 = makeQuery(declarations, "v", {clause_r_v});
    Query query_5 = makeQuery(declarations, "v", {clauseM_s_v});
    Query query_6 = makeQuery(declarations, "v", {clause_w_v});
    Query query_7 = makeQuery(declarations, "s", {clauseM_s_v});
    Query query_8 = makeQuery(declarations, "c", {clauseM_s_v});

    auto qe = QueryEvaluator(testPKB);
    /**
     * Select s such that Uses(s, v)
     * Type: uses, select first arg
     */
    list<string> result1 = qe.evaluate(&query_1);
    REQUIRE(generateResultSet(result1) == ResultSet {"2", "4", "5", "6"});

    /**
     * Select a such that Uses(a, v)
     * Type: uses, select first arg
     */
    list<string> result2 = qe.evaluate(&query_2);
    REQUIRE(generateResultSet(result2) == ResultSet {"2", "6"});

    /**
     * Select v such that Uses(p, v)
     * Type: uses, select second arg
     */
    list<string> result3 = qe.evaluate(&query_3);
    REQUIRE(generateResultSet(result3) == ResultSet {"xylophone"});

    /**
     * Select v such that Uses(r, v)
     * Type: uses, select second arg
     */
    list<string> result4 = qe.evaluate(&query_4);
    REQUIRE(generateResultSet(result4).empty()); //TODO: HANDLE ERROR

    /**
     * Select v such that Modifies(s, v)
     * Type: modifies, select second arg
     */
    list<string> result5 = qe.evaluate(&query_5);
    REQUIRE(generateResultSet(result5) == ResultSet {"x", "y", "zealous"});

    /**
     * Select v such that Modifies(w, v)
     * Type: modifies, select second arg
     */
    list<string> result6 = qe.evaluate(&query_6);
    REQUIRE(generateResultSet(result6) == ResultSet {"x"});

    /**
     * Select s such that Modifies(s, v)
     * Type: modifies, select first arg
     */
    list<string> result7 = qe.evaluate(&query_7);
    REQUIRE(generateResultSet(result7) == ResultSet {"1", "2", "3", "5", "6"});

    /**
     * Select c such that Modifies(s, v)
     * Type: modifies, select no arg
     */
    list<string> result8 = qe.evaluate(&query_8);
    REQUIRE(generateResultSet(result8) == ResultSet {"1", "3", "5"});

}

TEST_CASE("Merge synonyms") {
    PKB *testPKB = generateSamplePKB();
    unordered_map<string, DesignEntity> declarations = {
            {"s1", DesignEntity::STMT},
            {"s2", DesignEntity::STMT},
            {"s3", DesignEntity::STMT},
    };

    Argument as1 = {ArgumentType::SYNONYM, "s1"};
    Argument as2 = {ArgumentType::SYNONYM, "s2"};
    Argument as3 = {ArgumentType::SYNONYM, "s3"};
    Argument a0 = {ArgumentType::UNDERSCORE, "_"};
    Argument a4 = {ArgumentType::STMT_NO, "4"};
    Argument a5 = {ArgumentType::STMT_NO, "5"};

    SuchThatClause clause_s1_s2 = {ArgList{as1, as2},RelRef::FOLLOWS};
    SuchThatClause clause_s2_s3 = {ArgList{as2, as3},RelRef::FOLLOWS};
    SuchThatClause clause_s2_5 = {ArgList{as2, a5},RelRef::FOLLOWS};
    SuchThatClause clause_s1_s3 = {ArgList{as1, as3},RelRef::FOLLOWS};
    SuchThatClause clause_s1_0 = {ArgList{as1, a0},RelRef::FOLLOWS};
    SuchThatClause clause_s2_0 = {ArgList{as2, a0},RelRef::FOLLOWS};
    SuchThatClause clause_4_5 = {ArgList{a4, a5},RelRef::FOLLOWS};

    Query query_0 = makeQuery(declarations, "s1", {clause_s1_s2, clause_4_5});
    Query query_1 = makeQuery(declarations, "s1", {clause_s1_s2, clause_s2_5});
    Query query_2 = makeQuery(declarations, "s1", {clause_s1_s3, clause_s2_5});
    Query query_3 = makeQuery(declarations, "s2", {clause_s1_s2, clause_s2_s3});
    Query query_4 = makeQuery(declarations, "s1", {clause_s2_5, clause_s1_s2});
    Query query_5 = makeQuery(declarations, "s1", {clause_s1_0, clause_s2_0, clause_s1_s2});
    Query query_6 = makeQuery(declarations, "s1", {clause_s2_5, clause_s1_s3});
    
    auto qe = QueryEvaluator(testPKB);

    /**
     * Select s1 such that Follows(s1, s2) such that Follows(4, 5)
     * Type: boolean clause, no merge needed
     */
    list<string> result_0 = qe.evaluate(&query_0);
    REQUIRE(generateResultSet(result_0) == ResultSet {"1","2","3","4"});

    /**
     * elect s1 such that Follows(s1, s2) such that Follows(s2, 5)
     * Type: join string, value exists
     */
    list<string> result_1 = qe.evaluate(&query_1);
    REQUIRE(generateResultSet(result_1) == ResultSet {"3"});

    /**
     * Select s1 such that Follows(s1, s3) such that Follows(s2, 5)
     * Type: join string, value doesn't exist
     */
    list<string> result_2 = qe.evaluate(&query_2);
    REQUIRE(generateResultSet(result_2) == ResultSet {"1","2","3","4"});

    /**
    * Select s2 such that Follows(s1, s2) such that Follows(s2, s3)
    * Type: join tuples, left value exists
    */
    list<string> result_3 = qe.evaluate(&query_3);
    REQUIRE(generateResultSet(result_3) == ResultSet {"2","3","4"});

    /**
     * Select s1 such that Follows(s2, 5) such that Follows(s1, s2)
     * Type: join tuples, right value exists
     */
    list<string> result_4 = qe.evaluate(&query_4);
    REQUIRE(generateResultSet(result_4) == ResultSet {"3"});

    /**
     * Select s1 such that Follows(s1, _) such that Follows(s2, _) such that Follows(s1, s2)
     * Type: join tuples, both value exist
     */
    list<string> result_5 = qe.evaluate(&query_5);
    REQUIRE(generateResultSet(result_5) == ResultSet {"1","2","3"});

    /**
     * Select s1 such that Follows(s2, 5) such that Follows(s1, s3)
     * Type: join tuples, both value don't exist
     */
    list<string> result_6 = qe.evaluate(&query_6);
    REQUIRE(generateResultSet(result_6) == ResultSet {"1","2","3","4"});

}

PKB* generateSamplePKBForPatternMatching() {
    /**
     *    x = y;        // test var
     *    x = 1;        //test const
     *    x = y + 1;    //test basic expression
     *    y = (y + x + 2) + 1;  //test 1-nested expression
     *    y = ((y + (3 - z)) * (x + 2)) + 1;    // test >2-nested expression
     *    y = y + x * 1 + z;        // test AST structure
     */
    string a1 = "x = y;";
    string a2 = "x = 1;";
    string a3 = "x = y + 1;";
    string a4 = "y = (y + x + 2) + 1;";
    string a5 = "y = ((y + (3 - z)) * (x + 2)) + 1;";
    string a6 = "y = y + x * 1 + z;";
    string a7 = "x = (y + (3 - z)) + 1;";

    PKB *testPKB = PKB::getInstance();
    testPKB->addAssignNode(Parser::parseAssign(a1));
    testPKB->addAssignNode(Parser::parseAssign(a2));
    testPKB->addAssignNode(Parser::parseAssign(a3));
    testPKB->addAssignNode(Parser::parseAssign(a4));
    testPKB->addAssignNode(Parser::parseAssign(a5));
    testPKB->addAssignNode(Parser::parseAssign(a6));
    testPKB->addAssignNode(Parser::parseAssign(a7));
    return testPKB;
}

TEST_CASE("Pattern clause: return stmt") {
    PKB *testPKB = generateSamplePKBForPatternMatching();
    Query query;
    list<string> resultList;
    unordered_set<string> results;
    unordered_set<string> expected;
    generateSamplePKBForPatternMatching();
    auto qe = QueryEvaluator(testPKB);

    unordered_map<string, DesignEntity> declarationsMap = {{"a1", DesignEntity::ASSIGN}};
    Argument assignSyn = {ArgumentType::SYNONYM, "a1"};

    Argument leftIdent = {ArgumentType::IDENT, "\"x\""};
    Argument wild = {ArgumentType::UNDERSCORE, "_"};
    Argument noResultLeft = {ArgumentType::IDENT, "noResult"};

    Argument rightVar = {ArgumentType::PARTIAL_UNDERSCORE, "_\"y\"_"};
    Argument rightConst = {ArgumentType::PARTIAL_UNDERSCORE, "_\"3\"_"};
    Argument noResultsRight = {ArgumentType::PARTIAL_UNDERSCORE, "_\"asdsadsadasdsa\"_"};

    // create PatternClause using arguments and synonym
    PatternClause wild_wild = {std::vector<Argument>{assignSyn, wild, wild}, SynonymType::ASSIGN};
    PatternClause ident_wild = {std::vector<Argument>{assignSyn, leftIdent, wild}, SynonymType::ASSIGN};
    PatternClause wild_const = {std::vector<Argument>{assignSyn, wild, rightConst}, SynonymType::ASSIGN};
    PatternClause ident_const = {std::vector<Argument>{assignSyn, leftIdent, rightConst}, SynonymType::ASSIGN};
    PatternClause wild_var = {std::vector<Argument>{assignSyn, wild, rightVar}, SynonymType::ASSIGN};
    PatternClause ident_var = {std::vector<Argument>{assignSyn, leftIdent, rightVar}, SynonymType::ASSIGN};

    PatternClause none_wild = {std::vector<Argument>{assignSyn, noResultLeft, wild}, SynonymType::ASSIGN};
    PatternClause wild_none = {std::vector<Argument>{assignSyn, wild, noResultsRight}, SynonymType::ASSIGN};

    query.setDeclarations(declarationsMap);
    query.setSynonym("a1");

    query.setPatternClauses(vector<PatternClause>{wild_wild});  //a1(_,_)
    resultList = qe.evaluate(&query);
    results = std::unordered_set<string> (std::begin(resultList), std::end(resultList));
    expected = std::unordered_set<string> {"1", "2", "3", "4", "5", "6", "7"};
    REQUIRE(results == expected);

    query.setPatternClauses(vector<PatternClause>{ident_wild});  //a1("x",_)
    resultList = qe.evaluate(&query);
    results = std::unordered_set<string> (std::begin(resultList), std::end(resultList));
    expected = std::unordered_set<string> {"1", "2", "3", "7"};
    REQUIRE(results == expected);

    query.setPatternClauses(vector<PatternClause>{wild_const});  //a1(_, 3)
    resultList = qe.evaluate(&query);
    results = std::unordered_set<string> (std::begin(resultList), std::end(resultList));
    expected = std::unordered_set<string> {"5", "7"};
    REQUIRE(results == expected);

    query.setPatternClauses(vector<PatternClause>{ident_const});  //a1("x",3)
    resultList = qe.evaluate(&query);
    results = std::unordered_set<string> (std::begin(resultList), std::end(resultList));
    expected = std::unordered_set<string> {"7"};
    REQUIRE(results == expected);

    query.setPatternClauses(vector<PatternClause>{wild_var});  //a1(_, _"y"_)
    resultList = qe.evaluate(&query);
    results = std::unordered_set<string> (std::begin(resultList), std::end(resultList));
    expected = std::unordered_set<string> {"1", "3", "4", "5", "6", "7"};
    REQUIRE(results == expected);

    query.setPatternClauses(vector<PatternClause>{ident_var});  //a1("x",_"y"_)
    resultList = qe.evaluate(&query);
    results = std::unordered_set<string> (std::begin(resultList), std::end(resultList));
    expected = std::unordered_set<string> {"1", "3", "7"};
    REQUIRE(results == expected);

    query.setPatternClauses(vector<PatternClause>{none_wild});  //a1("noResults",_"asdasdsad"_)
    resultList = qe.evaluate(&query);
    results = std::unordered_set<string> (std::begin(resultList), std::end(resultList));
    expected = std::unordered_set<string> {};
    REQUIRE(results == expected);

    query.setPatternClauses(vector<PatternClause>{wild_none});
    resultList = qe.evaluate(&query);
    results = std::unordered_set<string> (std::begin(resultList), std::end(resultList));
    expected = std::unordered_set<string> {};
    REQUIRE(results == expected);
}


TEST_CASE("Pattern clause: return var + Stmt") {
    PKB *testPKB = generateSamplePKBForPatternMatching();
    Query query;
    list<string> resultList;
    unordered_set<string> results;
    unordered_set<string> expected;
    auto qe = QueryEvaluator(testPKB);

    unordered_map<string, DesignEntity> declarationsMap = {{"a", DesignEntity::ASSIGN}, {"v", DesignEntity::VARIABLE}};
    Argument assignSyn = {ArgumentType::SYNONYM, "a"};

    Argument leftSynonym = {ArgumentType::SYNONYM, "v"};

    Argument wild = {ArgumentType::UNDERSCORE, "_"};
    Argument rightConst = {ArgumentType::PARTIAL_UNDERSCORE, "_\"2\"_"};

    PatternClause synonym_wild = {std::vector<Argument>{assignSyn, leftSynonym, wild}, SynonymType::ASSIGN};
    PatternClause synonym_var = {std::vector<Argument>{assignSyn, leftSynonym, rightConst}, SynonymType::ASSIGN};

    query.setDeclarations(declarationsMap);

    query.setSynonym("a");
    query.setPatternClauses(vector<PatternClause>{synonym_wild});   //a1(v1, _)
    resultList = qe.evaluate(&query);
    results = std::unordered_set<string> (std::begin(resultList), std::end(resultList));
    expected = std::unordered_set<string> {"1", "2", "3", "4", "5", "6", "7"};
    REQUIRE(results == expected);

    query.setSynonym("a");
    query.setPatternClauses(vector<PatternClause>{synonym_var});   //a1(v1, _"2"_)
    resultList = qe.evaluate(&query);
    results = std::unordered_set<string> (std::begin(resultList), std::end(resultList));
    expected = std::unordered_set<string> {"4", "5"};
    REQUIRE(results == expected);

    query.setSynonym("v");
    query.setPatternClauses(vector<PatternClause>{synonym_wild});   //a1(v1, _)
    resultList = qe.evaluate(&query);
    results = std::unordered_set<string> (std::begin(resultList), std::end(resultList));
    expected = std::unordered_set<string> {"x", "y"};
    REQUIRE(results == expected);

    query.setSynonym("v");
    query.setPatternClauses(vector<PatternClause>{synonym_var});   //a1(v1, _"2"_)
    resultList = qe.evaluate(&query);
    results = std::unordered_set<string> (std::begin(resultList), std::end(resultList));
    expected = std::unordered_set<string> {"y"};
    REQUIRE(results == expected);
}

