//
// Created by Tianyi Wang on 14/2/22.
//

#include "pql/QueryEvaluator.h"
#include "catch.hpp"
#include "Parser.h"

using namespace std;

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


TEST_CASE("Select query with no clauses") {
    PKB *testPKB = generateSamplePKB();
    unordered_map<string, DesignEntity> declarationsMap = {{"v", DesignEntity::VARIABLE},
                                                           {"a", DesignEntity::ASSIGN},
                                                           {"pn", DesignEntity::PRINT},
                                                           {"s", DesignEntity::STMT}
                                                           };
    Query query1;
    query1.setDeclarations(declarationsMap);
    query1.setSynonym("v");

    Query query2;
    query2.setDeclarations(declarationsMap);
    query2.setSynonym("s");

    Query query3;
    query3.setDeclarations(declarationsMap);
    query3.setSynonym("pn");

    Query query4;
    query4.setDeclarations(declarationsMap);
    query4.setSynonym("a");

    auto qe = QueryEvaluator(testPKB);

    /**
     * Select v
     * Type: select all variables
     */
    list<string> result1 = qe.evaluate(&query1);

    /**
     * Select s
     * Type: select all statements
     */
    list<string> result2 = qe.evaluate(&query2);

    /**
     * Select pn
     * Type: select all print
     */
    list<string> result3 = qe.evaluate(&query3);

    /**
     * Select a
     * Type: select all assign
     */
    list<string> result4 = qe.evaluate(&query4);

    REQUIRE(std::unordered_set<string> (std::begin(result1), std::end(result1))
            == std::unordered_set<string> {"x", "y", "xylophone", "yeast", "z", "zealous"});
    REQUIRE(std::unordered_set<string> (std::begin(result2), std::end(result2))
            == std::unordered_set<string> {"1", "2", "3", "4", "5", "6"});
    REQUIRE(std::unordered_set<string> (std::begin(result3), std::end(result3))
            == std::unordered_set<string> {"4"});
    REQUIRE(std::unordered_set<string> (std::begin(result4), std::end(result4))
            == std::unordered_set<string> {"2", "3", "6"});
}

TEST_CASE("Such that clause: 1 synonym") {
    PKB *testPKB = generateSamplePKB();
    unordered_map<string, DesignEntity> declarationsMap = {{"s", DesignEntity::STMT}};
    Argument a0 = {ArgumentType::UNDERSCORE, "_"};
    Argument as = {ArgumentType::SYNONYM, "s"};
    Argument a3 = {ArgumentType::STMT_NO, "3"};
    Argument a5 = {ArgumentType::STMT_NO, "5"};
    Argument a6 = {ArgumentType::STMT_NO, "6"};

    SuchThatClause clause1 = {std::vector<Argument>{a3, as},RelRef::FOLLOWS};
    SuchThatClause clause2 = {std::vector<Argument>{as, a3},RelRef::FOLLOWS};
    SuchThatClause clause3 = {std::vector<Argument>{a0, as},RelRef::FOLLOWS};
    SuchThatClause clause4 = {std::vector<Argument>{as, a0},RelRef::FOLLOWS};
    SuchThatClause clause5 = {std::vector<Argument>{as, a6},RelRef::PARENT};
    SuchThatClause clause6 = {std::vector<Argument>{a5, as},RelRef::PARENT};
    SuchThatClause clause7 = {std::vector<Argument>{as, a0},RelRef::PARENT};
    SuchThatClause clause8 = {std::vector<Argument>{a0, as},RelRef::PARENT};

    Query query1;
    query1.setDeclarations(declarationsMap);
    query1.setSynonym("s");
    query1.setSuchThatClauses(vector<SuchThatClause>{clause1});

    Query query2;
    query2.setDeclarations(declarationsMap);
    query2.setSynonym("s");
    query2.setSuchThatClauses(vector<SuchThatClause>{clause2});

    Query query3;
    query3.setDeclarations(declarationsMap);
    query3.setSynonym("s");
    query3.setSuchThatClauses(vector<SuchThatClause>{clause3});

    Query query4;
    query4.setDeclarations(declarationsMap);
    query4.setSynonym("s");
    query4.setSuchThatClauses(vector<SuchThatClause>{clause4});

    Query query5;
    query5.setDeclarations(declarationsMap);
    query5.setSynonym("s");
    query5.setSuchThatClauses(vector<SuchThatClause>{clause5});

    Query query6;
    query6.setDeclarations(declarationsMap);
    query6.setSynonym("s");
    query6.setSuchThatClauses(vector<SuchThatClause>{clause6});

    Query query7;
    query7.setDeclarations(declarationsMap);
    query7.setSynonym("s");
    query7.setSuchThatClauses(vector<SuchThatClause>{clause7});

    Query query8;
    query8.setDeclarations(declarationsMap);
    query8.setSynonym("s");
    query8.setSuchThatClauses(vector<SuchThatClause>{clause8});

    auto qe = QueryEvaluator(testPKB);
    /**
     * Select s such that Follows(3, s)
     * Type: follows, select second arg
     */
    list<string> result1 = qe.evaluate(&query1);
    /**
     * Select s such that Follows(s, 3)
     * Type: follows, select first arg
     */
    list<string> result2 = qe.evaluate(&query2);
    /**
     * Select s such that Follows(_, s)
     * Type: follows, select second arg, wildcard
     */
    list<string> result3 = qe.evaluate(&query3);
    /**
     * Select s such that Follows(s, _)
     * Type: follows, select first arg, wildcard
     */
    list<string> result4 = qe.evaluate(&query4);
    /**
     * Select s such that Parent(s, 6)
     * Type: parent, select first arg
     */
    list<string> result5 = qe.evaluate(&query5);
    /**
     * Select s such that Parent(5, s)
     * Type: parent, select second arg
     */
    list<string> result6 = qe.evaluate(&query6);
    /**
     * Select s such that Parent(s, _)
     * Type: parent, select first arg, wildcard
     */
    list<string> result7 = qe.evaluate(&query7);
    /**
     * Select s such that Parent(_, s)
     * Type: parent, select second arg, wildcard
     */
    list<string> result8 = qe.evaluate(&query8);

    REQUIRE(std::unordered_set<string> (std::begin(result1), std::end(result1))
            == std::unordered_set<string> {"4"});
    REQUIRE(std::unordered_set<string> (std::begin(result2), std::end(result2))
            == std::unordered_set<string> {"2"});
    REQUIRE(std::unordered_set<string> (std::begin(result3), std::end(result3))
            == std::unordered_set<string> {"2", "3", "4", "5"});
    REQUIRE(std::unordered_set<string> (std::begin(result4), std::end(result4))
            == std::unordered_set<string> {"1", "2", "3", "4"});
    REQUIRE(std::unordered_set<string> (std::begin(result5), std::end(result5))
            == std::unordered_set<string> {"5"});
    REQUIRE(std::unordered_set<string> (std::begin(result6), std::end(result6))
            == std::unordered_set<string> {"6"});
    REQUIRE(std::unordered_set<string> (std::begin(result7), std::end(result7))
            == std::unordered_set<string> {"5"});
    REQUIRE(std::unordered_set<string> (std::begin(result8), std::end(result8))
            == std::unordered_set<string> {"6"});
}

TEST_CASE("Follows/Parent/Follows* clause: 1 synonym with stmt type") {
    PKB *testPKB = generateSamplePKB();
    unordered_map<string, DesignEntity> declarationsMap = {{"s", DesignEntity::STMT},
                                                           {"a", DesignEntity::ASSIGN},
                                                           {"pn", DesignEntity::PRINT},
                                                           {"r", DesignEntity::READ},};
    Argument a0 = {ArgumentType::UNDERSCORE, "_"};
    Argument a1 = {ArgumentType::STMT_NO, "1"};
    Argument a2 = {ArgumentType::STMT_NO, "2"};
    Argument a3 = {ArgumentType::STMT_NO, "3"};
    Argument a5 = {ArgumentType::STMT_NO, "5"};
    Argument as = {ArgumentType::SYNONYM, "s"};
    Argument aa = {ArgumentType::SYNONYM, "a"};
    Argument apn = {ArgumentType::SYNONYM, "pn"};
    Argument ar = {ArgumentType::SYNONYM, "r"};

    SuchThatClause clause_0_a = {std::vector<Argument>{a0, aa}, RelRef::FOLLOWS};
    SuchThatClause clause_1_a = {std::vector<Argument>{a1, aa},RelRef::FOLLOWS_T};
    SuchThatClause clause_a_2 = {std::vector<Argument>{aa, a2},RelRef::FOLLOWS};
    SuchThatClause clause_pn_0 = {std::vector<Argument>{apn, a0},RelRef::FOLLOWS};
    SuchThatClause clause_2_pn = {std::vector<Argument>{a2, apn},RelRef::FOLLOWS};
    SuchThatClause clause_r_2 = {std::vector<Argument>{ar, a2},RelRef::FOLLOWS};
    SuchThatClause clause_5_r = {std::vector<Argument>{a5, ar},RelRef::FOLLOWS};
    SuchThatClause clause_5_a = {std::vector<Argument>{a5, aa},RelRef::PARENT};

    Query query1;
    query1.setDeclarations(declarationsMap);
    query1.setSynonym("a");
    query1.setSuchThatClauses(vector<SuchThatClause>{clause_0_a});

    Query query2;
    query2.setDeclarations(declarationsMap);
    query2.setSynonym("a");
    query2.setSuchThatClauses(vector<SuchThatClause>{clause_1_a});

    Query query3;
    query3.setDeclarations(declarationsMap);
    query3.setSynonym("a");
    query3.setSuchThatClauses(vector<SuchThatClause>{clause_a_2});

    Query query4;
    query4.setDeclarations(declarationsMap);
    query4.setSynonym("pn");
    query4.setSuchThatClauses(vector<SuchThatClause>{clause_pn_0});

    Query query5;
    query5.setDeclarations(declarationsMap);
    query5.setSynonym("pn");
    query5.setSuchThatClauses(vector<SuchThatClause>{clause_2_pn});

    Query query6;
    query6.setDeclarations(declarationsMap);
    query6.setSynonym("r");
    query6.setSuchThatClauses(vector<SuchThatClause>{clause_r_2});

    Query query7;
    query7.setDeclarations(declarationsMap);
    query7.setSynonym("r");
    query7.setSuchThatClauses(vector<SuchThatClause>{clause_5_r});

    Query query8;
    query8.setDeclarations(declarationsMap);
    query8.setSynonym("a");
    query8.setSuchThatClauses(vector<SuchThatClause>{clause_5_a});

    auto qe = QueryEvaluator(testPKB);
    /**
     * Select a such that Follows(_, a)
     * Type: follows, select second arg, wildcard, assign
     */
    list<string> result1 = qe.evaluate(&query1);

    /**
     * Select a such that Follows*(1, a)
     * Type: follows*, select second arg, assign
     */
    list<string> result2 = qe.evaluate(&query2);

    /**
     * Select a such that Follows(a, 2)
     * Type: follows, select first arg, assign
     */
    list<string> result3 = qe.evaluate(&query3);

    /**
     * Select pn such that Follows(pn, _)
     * Type: follows, select first arg, wildcard, print
     */
    list<string> result4 = qe.evaluate(&query4);

    /**
     * Select pn such that Follows(2, pn)
     * Type: follows, select second arg, print
     */
    list<string> result5 = qe.evaluate(&query5);

    /**
     * Select r such that Follows(r, 2)
     * Type: follows, select first arg, read
     */
    list<string> result6 = qe.evaluate(&query6);

    /**
     * Select r such that Follows(5, r)
     * Type: follows, select second arg, read
     */
    list<string> result7 = qe.evaluate(&query7);

    /**
     * Select a such that Parent(5, a)
     * Type: parent, select second arg, assign
     */
    list<string> result8 = qe.evaluate(&query8);

    REQUIRE(std::unordered_set<string> (std::begin(result1), std::end(result1))
            == std::unordered_set<string> {"2","3"});
    REQUIRE(std::unordered_set<string> (std::begin(result2), std::end(result2))
            == std::unordered_set<string> {"2", "3"});
    REQUIRE(std::unordered_set<string> (std::begin(result3), std::end(result3)).empty());
    REQUIRE(std::unordered_set<string> (std::begin(result4), std::end(result4))
            == std::unordered_set<string> {"4"});
    REQUIRE(std::unordered_set<string> (std::begin(result5), std::end(result5)).empty());
    REQUIRE(std::unordered_set<string> (std::begin(result6), std::end(result6))
            == std::unordered_set<string> {"1"});
    REQUIRE(std::unordered_set<string> (std::begin(result7), std::end(result7)).empty());
    REQUIRE(std::unordered_set<string> (std::begin(result8), std::end(result8))
            == std::unordered_set<string> {"6"});
}

TEST_CASE("Follows/Parent/Follows* clause: 2 synonyms") {
    PKB *testPKB = generateSamplePKB();
    unordered_map<string, DesignEntity> declarationsMap = {{"s1", DesignEntity::STMT},
                                                           {"s2", DesignEntity::STMT}};
    Argument as1 = {ArgumentType::SYNONYM, "s1"};
    Argument as2 = {ArgumentType::SYNONYM, "s2"};

    SuchThatClause clause1 = {std::vector<Argument>{as1, as2},RelRef::FOLLOWS};
    SuchThatClause clause2 = {std::vector<Argument>{as1, as2},RelRef::PARENT};
    SuchThatClause clause3 = {std::vector<Argument>{as1, as2},RelRef::FOLLOWS_T};

    Query query1;
    query1.setDeclarations(declarationsMap);
    query1.setSynonym("s1");
    query1.setSuchThatClauses(vector<SuchThatClause>{clause1});

    Query query2;
    query2.setDeclarations(declarationsMap);
    query2.setSynonym("s2");
    query2.setSuchThatClauses(vector<SuchThatClause>{clause1});

    Query query3;
    query3.setDeclarations(declarationsMap);
    query3.setSynonym("s1");
    query3.setSuchThatClauses(vector<SuchThatClause>{clause2});

    Query query4;
    query4.setDeclarations(declarationsMap);
    query4.setSynonym("s2");
    query4.setSuchThatClauses(vector<SuchThatClause>{clause2});

    Query query5;
    query5.setDeclarations(declarationsMap);
    query5.setSynonym("s2");
    query5.setSuchThatClauses(vector<SuchThatClause>{clause3});


    auto qe = QueryEvaluator(testPKB);

    /**
     * Select s1 such that Follows(s1, s2)
     * Type: follows, select first arg
     */
    list<string> result1 = qe.evaluate(&query1);
    /**
     * Select s2 such that Follows(s1, s2)
     * Type: follows, select second arg
     */
    list<string> result2 = qe.evaluate(&query2);
    /**
     * Select s1 such that Parent(s1, s2)
     * Type: parent, select first arg
     */
    list<string> result3 = qe.evaluate(&query3);
    /**
     * Select s2 such that Parent(s1, s2)
     * Type: parent, select second arg
     */
    list<string> result4 = qe.evaluate(&query4);
    /**
     * Select s2 such that Follows*(s1, s2)
     * Type: follows*, select second arg
     */
    list<string> result5 = qe.evaluate(&query5);


    REQUIRE(std::unordered_set<string> (std::begin(result1), std::end(result1))
            == std::unordered_set<string> {"1", "2", "3", "4"});
    REQUIRE(std::unordered_set<string> (std::begin(result2), std::end(result2))
            == std::unordered_set<string> {"2", "3", "4", "5"});
    REQUIRE(std::unordered_set<string> (std::begin(result3), std::end(result3))
            == std::unordered_set<string> {"5"});
    REQUIRE(std::unordered_set<string> (std::begin(result4), std::end(result4))
            == std::unordered_set<string> {"6"});
    REQUIRE(std::unordered_set<string> (std::begin(result5), std::end(result5))
            == std::unordered_set<string> {"2", "3", "4", "5"});
}

TEST_CASE("Follows/Parent/Follows* clause: 2 synonyms with type") {
    PKB *testPKB = generateSamplePKB();
    unordered_map<string, DesignEntity> declarationsMap = {{"s", DesignEntity::STMT},
                                                           {"a", DesignEntity::ASSIGN},
                                                           {"pn", DesignEntity::PRINT},
                                                           {"r", DesignEntity::READ},
                                                           {"w", DesignEntity::WHILE},};
    Argument as = {ArgumentType::SYNONYM, "s"};
    Argument aa = {ArgumentType::SYNONYM, "a"};
    Argument apn = {ArgumentType::SYNONYM, "pn"};
    Argument ar = {ArgumentType::SYNONYM, "r"};
    Argument aw = {ArgumentType::SYNONYM, "w"};

    SuchThatClause clause_s_pn = {std::vector<Argument>{as, apn},RelRef::FOLLOWS};
    SuchThatClause clause_r_a = {std::vector<Argument>{ar, aa},RelRef::FOLLOWS};
    SuchThatClause clause_w_a = {std::vector<Argument>{aw, aa},RelRef::PARENT};

    Query query1;
    query1.setDeclarations(declarationsMap);
    query1.setSynonym("s");
    query1.setSuchThatClauses(vector<SuchThatClause>{clause_s_pn});

    Query query2;
    query2.setDeclarations(declarationsMap);
    query2.setSynonym("pn");
    query2.setSuchThatClauses(vector<SuchThatClause>{clause_s_pn});

    Query query3;
    query3.setDeclarations(declarationsMap);
    query3.setSynonym("r");
    query3.setSuchThatClauses(vector<SuchThatClause>{clause_r_a});

    Query query4;
    query4.setDeclarations(declarationsMap);
    query4.setSynonym("w");
    query4.setSuchThatClauses(vector<SuchThatClause>{clause_w_a});


    auto qe = QueryEvaluator(testPKB);

    /**
     * Select s such that Follows(s, p)
     * Type: follows, select first arg
     */
    list<string> result1 = qe.evaluate(&query1);
    /**
     * Select p such that Follows(s, p)
     * Type: follows, select second arg
     */
    list<string> result2 = qe.evaluate(&query2);
    /**
     * Select r such that Follows(r, a)
     * Type: parent, select first arg
     */
    list<string> result3 = qe.evaluate(&query3);
    /**
     * Select w such that Parent(w, a)
     * Type: parent, select first arg
     */
    list<string> result4 = qe.evaluate(&query4);

    REQUIRE(std::unordered_set<string> (std::begin(result1), std::end(result1))
            == std::unordered_set<string> {"3"});
    REQUIRE(std::unordered_set<string> (std::begin(result2), std::end(result2))
            == std::unordered_set<string> {"4"});
    REQUIRE(std::unordered_set<string> (std::begin(result3), std::end(result3))
            == std::unordered_set<string> {"1"});
    REQUIRE(std::unordered_set<string> (std::begin(result4), std::end(result4))
            == std::unordered_set<string> {"5"});
}

TEST_CASE("Modifies/Uses clause: 1 synonym with stmt type") {
    PKB *testPKB = generateSamplePKB();
    unordered_map<string, DesignEntity> declarationsMap = {{"s", DesignEntity::STMT},
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

    SuchThatClause clause_2_v = {std::vector<Argument>{a2, av},RelRef::USES_S};
    SuchThatClause clauseU_s_x = {std::vector<Argument>{as, ax},RelRef::USES_S};
    SuchThatClause clause_a_0 = {std::vector<Argument>{aa, a0},RelRef::USES_S};
    SuchThatClause clause_a_z = {std::vector<Argument>{aa, az},RelRef::USES_S};
    SuchThatClause clause_6_v = {std::vector<Argument>{a6, av},RelRef::MODIFIES_S};
    SuchThatClause clause_r_x = {std::vector<Argument>{ar, ax},RelRef::MODIFIES_S};
    SuchThatClause clauseM_s_x = {std::vector<Argument>{as, ax},RelRef::MODIFIES_S};
    SuchThatClause clause_s_0 = {std::vector<Argument>{as, a0},RelRef::MODIFIES_S};


    Query query1;
    query1.setDeclarations(declarationsMap);
    query1.setSynonym("v");
    query1.setSuchThatClauses(vector<SuchThatClause>{clause_2_v});

    Query query2;
    query2.setDeclarations(declarationsMap);
    query2.setSynonym("s");
    query2.setSuchThatClauses(vector<SuchThatClause>{clauseU_s_x});

    Query query3;
    query3.setDeclarations(declarationsMap);
    query3.setSynonym("a");
    query3.setSuchThatClauses(vector<SuchThatClause>{clause_a_0});

    Query query4;
    query4.setDeclarations(declarationsMap);
    query4.setSynonym("a");
    query4.setSuchThatClauses(vector<SuchThatClause>{clause_a_z});

    Query query5;
    query5.setDeclarations(declarationsMap);
    query5.setSynonym("v");
    query5.setSuchThatClauses(vector<SuchThatClause>{clause_6_v});

    Query query6;
    query6.setDeclarations(declarationsMap);
    query6.setSynonym("r");
    query6.setSuchThatClauses(vector<SuchThatClause>{clause_r_x});

    Query query7;
    query7.setDeclarations(declarationsMap);
    query7.setSynonym("s");
    query7.setSuchThatClauses(vector<SuchThatClause>{clauseM_s_x});

    Query query8;
    query8.setDeclarations(declarationsMap);
    query8.setSynonym("s");
    query8.setSuchThatClauses(vector<SuchThatClause>{clause_s_0});

    auto qe = QueryEvaluator(testPKB);
    /**
     * Select v such that Uses(2, v)
     * Type: uses, select second arg
     */
    list<string> result1 = qe.evaluate(&query1);

    /**
     * Select s such that Uses(s, "x")
     * Type: uses, select first arg
     */
    list<string> result2 = qe.evaluate(&query2);

    /**
     * Select a such that Uses(a, _) {"2", "6"}
     * Type: uses, select first arg, wildcard
     */
    list<string> result3 = qe.evaluate(&query3);

    /**
     * Select a such that Uses(a, "z") {}
     * Type: uses, select first arg, assign
     */
    list<string> result4 = qe.evaluate(&query4);

    /**
     * Select v such that Modifies(6, v)
     * Type: modifies, select second arg
     */
    list<string> result5 = qe.evaluate(&query5);

    /**
     * Select r such that Modifies(r, "x")
     * Type: modifies, select first arg, read
     */
    list<string> result6 = qe.evaluate(&query6);

    /**
     * Select s such that Modifies(s, "x")
     * Type: modifies, select second arg, read
     */
    list<string> result7 = qe.evaluate(&query7);

    /**
     * Select s such that Modifies(s, _) {"1", "2", "3", "6"}
     * Type: modifies, select first arg, assign
     */
    list<string> result8 = qe.evaluate(&query8);

    REQUIRE(std::unordered_set<string> (std::begin(result1), std::end(result1))
            == std::unordered_set<string> {"yeast", "zealous", "x"});
    REQUIRE(std::unordered_set<string> (std::begin(result2), std::end(result2))
            == std::unordered_set<string> {"2", "5", "6"});
    REQUIRE(std::unordered_set<string> (std::begin(result3), std::end(result3))
            == std::unordered_set<string> {"2", "6"});
    REQUIRE(std::unordered_set<string> (std::begin(result4), std::end(result4)).empty());
    REQUIRE(std::unordered_set<string> (std::begin(result5), std::end(result5))
            == std::unordered_set<string> {"x"});
    REQUIRE(std::unordered_set<string> (std::begin(result6), std::end(result6))
            == std::unordered_set<string> {"1"});
    REQUIRE(std::unordered_set<string> (std::begin(result7), std::end(result7))
            == std::unordered_set<string> {"1", "5", "6"});
    REQUIRE(std::unordered_set<string> (std::begin(result8), std::end(result8))
            == std::unordered_set<string> {"1", "2", "3", "5", "6"});
}

TEST_CASE("Modifies/Uses clause: 2 synonyms with stmt type") {
    PKB *testPKB = generateSamplePKB();
    unordered_map<string, DesignEntity> declarationsMap = {{"s", DesignEntity::STMT},
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

    SuchThatClause clauseU_s_v = {std::vector<Argument>{as, av},RelRef::USES_S};
    SuchThatClause clause_a_v = {std::vector<Argument>{aa, av},RelRef::USES_S};
    SuchThatClause clause_pn_v = {std::vector<Argument>{apn, av},RelRef::USES_S};
    SuchThatClause clause_r_v = {std::vector<Argument>{ar, av},RelRef::USES_S};
    SuchThatClause clauseM_s_v = {std::vector<Argument>{as, av},RelRef::MODIFIES_S};
    SuchThatClause clause_w_v = {std::vector<Argument>{aw, av},RelRef::MODIFIES_S};

    Query query1;
    query1.setDeclarations(declarationsMap);
    query1.setSynonym("s");
    query1.setSuchThatClauses(vector<SuchThatClause>{clauseU_s_v});

    Query query2;
    query2.setDeclarations(declarationsMap);
    query2.setSynonym("a");
    query2.setSuchThatClauses(vector<SuchThatClause>{clause_a_v});

    Query query3;
    query3.setDeclarations(declarationsMap);
    query3.setSynonym("v");
    query3.setSuchThatClauses(vector<SuchThatClause>{clause_pn_v});

    Query query4;
    query4.setDeclarations(declarationsMap);
    query4.setSynonym("v");
    query4.setSuchThatClauses(vector<SuchThatClause>{clause_r_v});

    Query query5;
    query5.setDeclarations(declarationsMap);
    query5.setSynonym("v");
    query5.setSuchThatClauses(vector<SuchThatClause>{clauseM_s_v});

    Query query6;
    query6.setDeclarations(declarationsMap);
    query6.setSynonym("v");
    query6.setSuchThatClauses(vector<SuchThatClause>{clause_w_v});

    Query query7;
    query7.setDeclarations(declarationsMap);
    query7.setSynonym("s");
    query7.setSuchThatClauses(vector<SuchThatClause>{clauseM_s_v});

    Query query8;
    query8.setDeclarations(declarationsMap);
    query8.setSynonym("c");
    query8.setSuchThatClauses(vector<SuchThatClause>{clauseM_s_v});

    auto qe = QueryEvaluator(testPKB);
    /**
     * Select s such that Uses(s, v)
     * Type: uses, select first arg
     */
    list<string> result1 = qe.evaluate(&query1);

    /**
     * Select a such that Uses(a, v)
     * Type: uses, select first arg
     */
    list<string> result2 = qe.evaluate(&query2);

    /**
     * Select v such that Uses(p, v)
     * Type: uses, select second arg
     */
    list<string> result3 = qe.evaluate(&query3);

    /**
     * Select v such that Uses(r, v)
     * Type: uses, select second arg
     */
    list<string> result4 = qe.evaluate(&query4);

    /**
     * Select v such that Modifies(s, v)
     * Type: modifies, select second arg
     */
    list<string> result5 = qe.evaluate(&query5);

    /**
     * Select v such that Modifies(w, v)
     * Type: modifies, select second arg
     */
    list<string> result6 = qe.evaluate(&query6);

    /**
     * Select s such that Modifies(s, v)
     * Type: modifies, select first arg
     */
    list<string> result7 = qe.evaluate(&query7);

    /**
     * Select c such that Modifies(s, v)
     * Type: modifies, select no arg
     */
    list<string> result8 = qe.evaluate(&query8);

    REQUIRE(std::unordered_set<string> (std::begin(result1), std::end(result1))
            == std::unordered_set<string> {"2", "4", "5", "6"});
    REQUIRE(std::unordered_set<string> (std::begin(result2), std::end(result2))
            == std::unordered_set<string> {"2", "6"});
    REQUIRE(std::unordered_set<string> (std::begin(result3), std::end(result3))
            == std::unordered_set<string> {"xylophone"});
    REQUIRE(std::unordered_set<string> (std::begin(result4), std::end(result4)).empty()); //TODO: HANDLE ERROR
    REQUIRE(std::unordered_set<string> (std::begin(result5), std::end(result5))
            == std::unordered_set<string> {"x", "y", "zealous"});
    REQUIRE(std::unordered_set<string> (std::begin(result6), std::end(result6))
            == std::unordered_set<string> {"x"});
    REQUIRE(std::unordered_set<string> (std::begin(result7), std::end(result7))
            == std::unordered_set<string> {"1", "2", "3", "5", "6"});
    REQUIRE(std::unordered_set<string> (std::begin(result8), std::end(result8))
            == std::unordered_set<string> {"1", "3", "5"});
}

TEST_CASE("Merge synonyms") {
    PKB *testPKB = generateSamplePKB();
    unordered_map<string, DesignEntity> declarationsMap = {
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

    SuchThatClause clause_s1_s2 = {std::vector<Argument>{as1, as2},RelRef::FOLLOWS};
    SuchThatClause clause_s2_s3 = {std::vector<Argument>{as2, as3},RelRef::FOLLOWS};
    SuchThatClause clause_s2_5 = {std::vector<Argument>{as2, a5},RelRef::FOLLOWS};
    SuchThatClause clause_s1_s3 = {std::vector<Argument>{as1, as3},RelRef::FOLLOWS};
    SuchThatClause clause_s1_0 = {std::vector<Argument>{as1, a0},RelRef::FOLLOWS};
    SuchThatClause clause_s2_0 = {std::vector<Argument>{as2, a0},RelRef::FOLLOWS};
    SuchThatClause clause_4_5 = {std::vector<Argument>{a4, a5},RelRef::FOLLOWS};

    Query query_0;
    query_0.setDeclarations(declarationsMap);
    query_0.setSynonym("s1");
    query_0.setSuchThatClauses({clause_s1_s2, clause_4_5});

    Query query_1;
    query_1.setDeclarations(declarationsMap);
    query_1.setSynonym("s1");
    query_1.setSuchThatClauses({clause_s1_s2, clause_s2_5});

    Query query_2;
    query_2.setDeclarations(declarationsMap);
    query_2.setSynonym("s1");
    query_2.setSuchThatClauses({clause_s1_s3, clause_s2_5});

    Query query_3;
    query_3.setDeclarations(declarationsMap);
    query_3.setSynonym("s2");
    query_3.setSuchThatClauses({clause_s1_s2, clause_s2_s3});

    Query query_4;
    query_4.setDeclarations(declarationsMap);
    query_4.setSynonym("s1");
    query_4.setSuchThatClauses({clause_s2_5, clause_s1_s2});

    Query query_5;
    query_5.setDeclarations(declarationsMap);
    query_5.setSynonym("s1");
    query_5.setSuchThatClauses({clause_s1_0, clause_s2_0, clause_s1_s2});

    Query query_6;
    query_6.setDeclarations(declarationsMap);
    query_6.setSynonym("s1");
    query_6.setSuchThatClauses({clause_s2_5, clause_s1_s3});


    auto qe = QueryEvaluator(testPKB);

    /**
     * Select s1 such that Follows(s1, s2) such that Follows(4, 5)
     * Type: boolean clause, no merge needed
     */
    list<string> result_0 = qe.evaluate(&query_0);

    /**
     * elect s1 such that Follows(s1, s2) such that Follows(s2, 5)
     * Type: join string, value exists
     */
    list<string> result_1 = qe.evaluate(&query_1);

    /**
     * Select s1 such that Follows(s1, s3) such that Follows(s2, 5)
     * Type: join string, value doesn't exist
     */
    list<string> result_2 = qe.evaluate(&query_2);

    /**
    * Select s2 such that Follows(s1, s2) such that Follows(s2, s3)
    * Type: join tuples, left value exists
    */
    list<string> result_3 = qe.evaluate(&query_3);

    /**
     * Select s1 such that Follows(s2, 5) such that Follows(s1, s2)
     * Type: join tuples, right value exists
     */
    list<string> result_4 = qe.evaluate(&query_4);

    /**
     * Select s1 such that Follows(s1, _) such that Follows(s2, _) such that Follows(s1, s2)
     * Type: join tuples, both value exist
     */
    list<string> result_5 = qe.evaluate(&query_5);

    /**
     * Select s1 such that Follows(s2, 5) such that Follows(s1, s3)
     * Type: join tuples, both value don't exist
     */
    list<string> result_6 = qe.evaluate(&query_6);

    REQUIRE(std::unordered_set<string> (std::begin(result_0), std::end(result_0))
            == std::unordered_set<string> {"1","2","3","4"});
    REQUIRE(std::unordered_set<string> (std::begin(result_1), std::end(result_1))
            == std::unordered_set<string> {"3"});
    REQUIRE(std::unordered_set<string> (std::begin(result_2), std::end(result_2))
            == std::unordered_set<string> {"1","2","3","4"});
    REQUIRE(std::unordered_set<string> (std::begin(result_3), std::end(result_3))
            == std::unordered_set<string> {"2","3","4"});
    REQUIRE(std::unordered_set<string> (std::begin(result_4), std::end(result_4))
            == std::unordered_set<string> {"3"});
    REQUIRE(std::unordered_set<string> (std::begin(result_5), std::end(result_5))
            == std::unordered_set<string> {"1","2","3"});
    REQUIRE(std::unordered_set<string> (std::begin(result_6), std::end(result_6))
            == std::unordered_set<string> {"1","2","3","4"});
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

