//
// Created by Tianyi Wang on 14/2/22.
//

#include "pql/QueryEvaluator.h"
#include "catch.hpp"
using namespace std;

PKB* generateSamplePKB() {
    PKB *testPKB = PKB::getInstance();
/**
 * Procedure p {
 * 01 read x;
 * 02 y = yeast;
 * 03 zealous = 3;
 * 04 print xylophone;
 * 05 while (z = 1) {
 * 06    x = 5;
 *    };
 * }
 */
    testPKB->addVariable("x");
    testPKB->addVariable("y");
    testPKB->addVariable("z");
    testPKB->addVariable("xylophone");
    testPKB->addVariable("yeast");
    testPKB->addVariable("zealous");

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
    return testPKB;
}

PKB *testPKB = generateSamplePKB();

TEST_CASE("Select query with no clauses") {
    Query query;
    unordered_map<string, DesignEntity> declarationsMap = {{"v", DesignEntity::VARIABLE}};
    query.setDeclarations(declarationsMap);
    query.setSynonym("v");

    auto qe = QueryEvaluator(testPKB);

    /**
     * Select v
     * Type: select all variables
     */
    list<string> result = qe.evaluate(&query);
    list<string> expected = {"x", "y", "xylophone", "yeast", "z"};
    REQUIRE(std::unordered_set<string> (std::begin(result), std::end(result))
            == std::unordered_set<string> (std::begin(expected), std::end(expected)));
}

TEST_CASE("Such that clause: 1 synonym") {
    unordered_map<string, DesignEntity> declarationsMap = {{"s", DesignEntity::STMT}};
    Argument a0 = {.argumentType = ArgumentType::UNDERSCORE, .argumentValue = "_"};
    Argument as = {.argumentType = ArgumentType::SYNONYM, .argumentValue = "s"};
    Argument a3 = {.argumentType = ArgumentType::STMT_NO, .argumentValue = "3"};
    Argument a5 = {.argumentType = ArgumentType::STMT_NO, .argumentValue = "5"};
    Argument a6 = {.argumentType = ArgumentType::STMT_NO, .argumentValue = "6"};

    SuchThatClause clause1 = {.relRef = RelRef::FOLLOWS};
    clause1.argList = {a3, as};

    SuchThatClause clause2 = {.relRef = RelRef::FOLLOWS};
    clause2.argList = {as, a3};

    SuchThatClause clause3 = {.relRef = RelRef::FOLLOWS};
    clause3.argList = {a0, as};

    SuchThatClause clause4 = {.relRef = RelRef::FOLLOWS};
    clause4.argList = {as, a0};

    SuchThatClause clause5 = {.relRef = RelRef::PARENT};
    clause5.argList = {as, a6};

    SuchThatClause clause6 = {.relRef = RelRef::PARENT};
    clause6.argList = {a5, as};

    SuchThatClause clause7 = {.relRef = RelRef::PARENT};
    clause7.argList = {as, a0};

    SuchThatClause clause8 = {.relRef = RelRef::PARENT};
    clause8.argList = {a0, as};

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

TEST_CASE("Such that clause: 2 synonyms") {
    unordered_map<string, DesignEntity> declarationsMap = {{"s1", DesignEntity::STMT},
                                                           {"s2", DesignEntity::STMT}};
    Argument a1 = {.argumentType = ArgumentType::SYNONYM, .argumentValue = "s1"};
    Argument a2 = {.argumentType = ArgumentType::SYNONYM, .argumentValue = "s2"};
    SuchThatClause clause1 = {.relRef = RelRef::FOLLOWS};
    clause1.argList = {a1, a2};

    SuchThatClause clause2 = {.relRef = RelRef::PARENT};
    clause2.argList = {a1, a2};

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

    REQUIRE(std::unordered_set<string> (std::begin(result1), std::end(result1))
            == std::unordered_set<string> {"1", "2", "3", "4"});
    REQUIRE(std::unordered_set<string> (std::begin(result2), std::end(result2))
            == std::unordered_set<string> {"2", "3", "4", "5"});
    REQUIRE(std::unordered_set<string> (std::begin(result3), std::end(result3))
            == std::unordered_set<string> {"5"});
    REQUIRE(std::unordered_set<string> (std::begin(result4), std::end(result4))
            == std::unordered_set<string> {"6"});
}


/*
TEST_CASE("Pattern clause: ") {
    unordered_map<string, DesignEntity> declarationsMap = {{"a", DesignEntity::ASSIGN}, {"v", DesignEntity::VARIABLE}};
    Argument a1 = {.argumentType = ArgumentType::UNDERSCORE, .argumentValue = "_"};
    Argument a2 = {.argumentType = ArgumentType::UNDERSCORE, .argumentValue = "_"};
    PatternClause clause1 = {.synonymType = SynonymType::ASSIGN};
    clause1.argList = {a1, a2};

    Query query1;
    query1.setDeclarations(declarationsMap);
    query1.setSynonym("a");
    query1.setPatternClauses(vector<PatternClause>{clause1});


    auto qe = QueryEvaluator(testPKB);
    list<string> result1 = qe.evaluate(&query1);

    REQUIRE(std::unordered_set<string> (std::begin(result1), std::end(result1))
            == std::unordered_set<string> {"2", "3"});
}
*/

TEST_CASE("Merge synonyms") {
    unordered_map<string, DesignEntity> declarationsMap = {
            {"s1", DesignEntity::STMT},
            {"s2", DesignEntity::STMT},
            {"s3", DesignEntity::STMT},
    };

    Argument as1 = {.argumentType = ArgumentType::SYNONYM, .argumentValue = "s1"};
    Argument as2 = {.argumentType = ArgumentType::SYNONYM, .argumentValue = "s2"};
    Argument as3 = {.argumentType = ArgumentType::SYNONYM, .argumentValue = "s3"};
    Argument a0 = {.argumentType = ArgumentType::UNDERSCORE, .argumentValue = "_"};
    Argument a4 = {.argumentType = ArgumentType::STMT_NO, .argumentValue = "4"};
    Argument a5 = {.argumentType = ArgumentType::STMT_NO, .argumentValue = "5"};

    SuchThatClause clause_s1_s2 = {.relRef = RelRef::FOLLOWS};
    clause_s1_s2.argList = {as1, as2};

    SuchThatClause clause_s2_s3 = {.relRef = RelRef::FOLLOWS};
    clause_s2_s3.argList = {as2, as3};

    SuchThatClause clause_s2_5 = {.relRef = RelRef::FOLLOWS};
    clause_s2_5.argList = {as2, a5};

    SuchThatClause clause_s1_s3 = {.relRef = RelRef::FOLLOWS};
    clause_s1_s3.argList = {as1, as3};

    SuchThatClause clause_s1_0 = {.relRef = RelRef::FOLLOWS};
    clause_s1_0.argList = {as1, a0};

    SuchThatClause clause_s2_0 = {.relRef = RelRef::FOLLOWS};
    clause_s2_0.argList = {as2, a0};

    SuchThatClause clause_4_5 = {.relRef = RelRef::FOLLOWS};
    clause_4_5.argList = {a4, a5};

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
