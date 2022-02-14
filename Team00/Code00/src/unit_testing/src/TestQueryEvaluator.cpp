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

TEST_CASE("Query0") {
    generateSamplePKB();
    Query query0;
    unordered_map<string, DesignEntity> declarationsMap = {{"v", DesignEntity::VARIABLE}};
    query0.setDeclarations(declarationsMap);
    query0.setSynonym("v");
    auto qe = QueryEvaluator(testPKB);
    list<string> result = qe.evaluate(&query0);
    list<string> expected = {"x", "y", "xylophone", "yeast", "z"};
    REQUIRE(std::unordered_set<string> (std::begin(result), std::end(result))
            == std::unordered_set<string> (std::begin(expected), std::end(expected)));
}

TEST_CASE("Query1") {
    generateSamplePKB();
    Query query1;
    unordered_map<string, DesignEntity> declarationsMap = {{"s", DesignEntity::STMT}};
    query1.setDeclarations(declarationsMap);
    query1.setSynonym("s");
    Argument a1 = {.argumentType = ArgumentType::STMT_NO, .argumentValue = "1"};
    Argument a2 = {.argumentType = ArgumentType::SYNONYM, .argumentValue = "s"};
    SuchThatClause follows = {.relRef = RelRef::FOLLOWS};
    follows.argList = {a1, a2};
    query1.addSuchThatClause(follows);
    auto qe = QueryEvaluator(testPKB);
    list<string> result = qe.evaluate(&query1);
    list<string> expected = {"2"};
    REQUIRE(std::unordered_set<string> (std::begin(result), std::end(result))
            == std::unordered_set<string> (std::begin(expected), std::end(expected)));
}

TEST_CASE("Query2") {
    generateSamplePKB();
    Query query2;
    unordered_map<string, DesignEntity> declarationsMap = {{"s", DesignEntity::STMT}};
    query2.setDeclarations(declarationsMap);
    query2.setSynonym("s");
    Argument a1 = {.argumentType = ArgumentType::UNDERSCORE, .argumentValue = "_"};
    Argument a2 = {.argumentType = ArgumentType::SYNONYM, .argumentValue = "s"};
    SuchThatClause follows = {.relRef = RelRef::FOLLOWS};
    follows.argList = {a1, a2};
    query2.addSuchThatClause(follows);
    auto qe = QueryEvaluator(testPKB);
    list<string> result = qe.evaluate(&query2);
    list<string> expected = {"2", "3", "4", "5"};

    REQUIRE(std::unordered_set<string> (std::begin(result), std::end(result))
            == std::unordered_set<string> (std::begin(expected), std::end(expected)));
}

TEST_CASE("Query3") {
    generateSamplePKB();
    Query query3;
    unordered_map<string, DesignEntity> declarationsMap = {{"s", DesignEntity::STMT}};
    query3.setDeclarations(declarationsMap);
    query3.setSynonym("s");
    Argument a1 = {.argumentType = ArgumentType::SYNONYM, .argumentValue = "s"};
    Argument a2 = {.argumentType = ArgumentType::UNDERSCORE, .argumentValue = "_"};
    SuchThatClause follows = {.relRef = RelRef::FOLLOWS};
    follows.argList = {a1, a2};
    query3.addSuchThatClause(follows);
    auto qe = QueryEvaluator(testPKB);
    list<string> result = qe.evaluate(&query3);
    list<string> expected = {"1", "2", "3", "4"};
    REQUIRE(std::unordered_set<string> (std::begin(result), std::end(result))
            == std::unordered_set<string> (std::begin(expected), std::end(expected)));
}

TEST_CASE("Query4") {
    generateSamplePKB();
    Query query4;
    unordered_map<string, DesignEntity> declarationsMap = {{"s1", DesignEntity::STMT}, {"s2", DesignEntity::STMT}};
    query4.setDeclarations(declarationsMap);
    query4.setSynonym("s1");
    Argument a1 = {.argumentType = ArgumentType::SYNONYM, .argumentValue = "s1"};
    Argument a2 = {.argumentType = ArgumentType::SYNONYM, .argumentValue = "s2"};
    SuchThatClause follows = {.relRef = RelRef::FOLLOWS};
    follows.argList = {a1, a2};
    query4.addSuchThatClause(follows);
    auto qe = QueryEvaluator(testPKB);
    list<string> result = qe.evaluate(&query4);
    list<string> expected = {"1", "2", "3", "4"};
    REQUIRE(std::unordered_set<string> (std::begin(result), std::end(result))
            == std::unordered_set<string> (std::begin(expected), std::end(expected)));
}

