//
// Created by Tianyi Wang on 14/2/22.
//

#include "pql/QueryEvaluator.h"
#include "catch.hpp"
using namespace std;

PKB* testPKB = PKB::getInstance();
void generateSamplePKB() {
    /**
     * 01 read x;
     * 02 read y;
     * 03 print yeast;
     * 04 print xylophone;
     * 05 while (x = 1) { ## print z;
     * 06 x = 5 ## print x;
     * }
     */
    testPKB->addVariable("x");
    testPKB->addVariable("y");
    testPKB->addVariable("z");
    testPKB->addVariable("xylophone");
    testPKB->addVariable("yeast");
    //testPKB->addVariable("zealous");

    testPKB->addReadStatement(1);
    testPKB->addReadStatement(2);
    testPKB->addPrintStatement(3);
    testPKB->addPrintStatement(4);
    testPKB->addPrintStatement(5);
    testPKB->addPrintStatement(6);

    testPKB->setFollows(1,2);
    testPKB->setFollows(2,3);
    testPKB->setFollows(3,4);
    testPKB->setFollows(4,5);

    testPKB->setParent(5,6);
}

TEST_CASE("Select query with no clauses") {
    generateSamplePKB();
    Query query;
    unordered_map<string, DesignEntity> declarationsMap = {{"v", DesignEntity::VARIABLE}};
    query.setDeclarations(declarationsMap);
    query.setSynonym("v");
    auto qe = QueryEvaluator(testPKB);
    list<string> result = qe.evaluate(&query);
    list<string> expected = {"x", "y", "xylophone", "yeast", "z"};
    REQUIRE(std::unordered_set<string> (std::begin(result), std::end(result))
            == std::unordered_set<string> (std::begin(expected), std::end(expected)));
}

TEST_CASE("Such that clause: 1 synonym") {
    generateSamplePKB();

    unordered_map<string, DesignEntity> declarationsMap = {{"s", DesignEntity::STMT}};
    Argument a0 = {.argumentType = ArgumentType::UNDERSCORE, .argumentValue = "_"};
    Argument a = {.argumentType = ArgumentType::SYNONYM, .argumentValue = "s"};
    Argument a3 = {.argumentType = ArgumentType::STMT_NO, .argumentValue = "3"};
    Argument a5 = {.argumentType = ArgumentType::STMT_NO, .argumentValue = "5"};
    Argument a6 = {.argumentType = ArgumentType::STMT_NO, .argumentValue = "6"};

    SuchThatClause clause1 = {.relRef = RelRef::FOLLOWS};
    clause1.argList = {a3, a};

    SuchThatClause clause2 = {.relRef = RelRef::FOLLOWS};
    clause2.argList = {a, a3};

    SuchThatClause clause3 = {.relRef = RelRef::FOLLOWS};
    clause3.argList = {a0, a};

    SuchThatClause clause4 = {.relRef = RelRef::FOLLOWS};
    clause4.argList = {a, a0};

    SuchThatClause clause5 = {.relRef = RelRef::PARENT};
    clause5.argList = {a, a6};

    SuchThatClause clause6 = {.relRef = RelRef::PARENT};
    clause6.argList = {a5, a};

    SuchThatClause clause7 = {.relRef = RelRef::PARENT};
    clause7.argList = {a, a0};

    SuchThatClause clause8 = {.relRef = RelRef::PARENT};
    clause8.argList = {a0, a};

    Query query1;
    query1.setDeclarations(declarationsMap);
    query1.setSynonym("s");
    query1.addSuchThatClause(clause1);

    Query query2;
    query2.setDeclarations(declarationsMap);
    query2.setSynonym("s");
    query2.addSuchThatClause(clause2);

    Query query3;
    query3.setDeclarations(declarationsMap);
    query3.setSynonym("s");
    query3.addSuchThatClause(clause3);

    Query query4;
    query4.setDeclarations(declarationsMap);
    query4.setSynonym("s");
    query4.addSuchThatClause(clause4);

    Query query5;
    query5.setDeclarations(declarationsMap);
    query5.setSynonym("s");
    query5.addSuchThatClause(clause5);

    Query query6;
    query6.setDeclarations(declarationsMap);
    query6.setSynonym("s");
    query6.addSuchThatClause(clause6);

    Query query7;
    query7.setDeclarations(declarationsMap);
    query7.setSynonym("s");
    query7.addSuchThatClause(clause7);

    Query query8;
    query8.setDeclarations(declarationsMap);
    query8.setSynonym("s");
    query8.addSuchThatClause(clause8);

    auto qe = QueryEvaluator(testPKB);
    list<string> result1 = qe.evaluate(&query1);
    list<string> result2 = qe.evaluate(&query2);
    list<string> result3 = qe.evaluate(&query3);
    list<string> result4 = qe.evaluate(&query4);
    list<string> result5 = qe.evaluate(&query5);
    list<string> result6 = qe.evaluate(&query6);
    list<string> result7 = qe.evaluate(&query7);
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
    generateSamplePKB();

    unordered_map<string, DesignEntity> declarationsMap = {{"s1", DesignEntity::STMT}, {"s2", DesignEntity::STMT}};
    Argument a1 = {.argumentType = ArgumentType::SYNONYM, .argumentValue = "s1"};
    Argument a2 = {.argumentType = ArgumentType::SYNONYM, .argumentValue = "s2"};
    SuchThatClause clause1 = {.relRef = RelRef::FOLLOWS};
    clause1.argList = {a1, a2};

    SuchThatClause clause2 = {.relRef = RelRef::PARENT};
    clause2.argList = {a1, a2};

    Query query1;
    query1.setDeclarations(declarationsMap);
    query1.setSynonym("s1");
    query1.addSuchThatClause(clause1);

    Query query2;
    query2.setDeclarations(declarationsMap);
    query2.setSynonym("s2");
    query2.addSuchThatClause(clause1);

    Query query3;
    query3.setDeclarations(declarationsMap);
    query3.setSynonym("s1");
    query3.addSuchThatClause(clause2);

    Query query4;
    query4.setDeclarations(declarationsMap);
    query4.setSynonym("s2");
    query4.addSuchThatClause(clause2);


    auto qe = QueryEvaluator(testPKB);
    list<string> result1 = qe.evaluate(&query1);
    list<string> result2 = qe.evaluate(&query2);
    list<string> result3 = qe.evaluate(&query3);
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
TEST_CASE("Query8") {
    generateSamplePKB();
    Query query;
    unordered_map<string, DesignEntity> declarationsMap = {
            {"s1", DesignEntity::STMT},
            {"s2", DesignEntity::STMT},
            {"s3", DesignEntity::STMT},
    };
    query.setDeclarations(declarationsMap);
    query.setSynonym("s2");

    Argument a1 = {.argumentType = ArgumentType::SYNONYM, .argumentValue = "s1"};
    Argument a2 = {.argumentType = ArgumentType::SYNONYM, .argumentValue = "s2"};
    SuchThatClause clause1 = {.relRef = RelRef::FOLLOWS};
    clause1.argList = {a1, a2};
    query.addSuchThatClause(clause1);

    Argument a3 = {.argumentType = ArgumentType::SYNONYM, .argumentValue = "s2"};
    Argument a4 = {.argumentType = ArgumentType::SYNONYM, .argumentValue = "s3"};
    SuchThatClause clause2 = {.relRef = RelRef::FOLLOWS};
    clause2.argList = {a3, a4};
    query.addSuchThatClause(clause2);

    auto qe = QueryEvaluator(testPKB);
    list<string> result = qe.evaluate(&query);
    list<string> expected = {"2,3,4"};
    REQUIRE(std::unordered_set<string> (std::begin(result), std::end(result))
            == std::unordered_set<string> (std::begin(expected), std::end(expected)));
}
*/
