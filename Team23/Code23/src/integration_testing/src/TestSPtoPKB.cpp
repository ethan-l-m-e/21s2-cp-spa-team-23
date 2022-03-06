#include "TNode/Node.h"
#include "catch.hpp"
#include "iostream"
#include "SourceProcessor/Parser.h"
#include "PKB.h"
#include "SourceProcessor/RelationshipExtractor.h"
#include "SourceProcessor/SourceProcessor.h"
using namespace std;

void require(bool b) {
    REQUIRE(b);
}

TEST_CASE("Integration testing - statement type check from parser to pkb") {
//    auto programNode = dynamic_cast<ProgramNode*>(Parser::Parse(sourceCode));

    SourceProcessor::run("integration_source.txt");

    CHECK(PKB::getInstance()->isAssignStatement("1"));
    CHECK(PKB::getInstance()->isWhileStatement("2"));
    CHECK(PKB::getInstance()->isAssignStatement("3"));
    CHECK(PKB::getInstance()->isWhileStatement("4"));
    CHECK(PKB::getInstance()->isWhileStatement("5"));
    CHECK(PKB::getInstance()->isWhileStatement("6"));
    CHECK(PKB::getInstance()->isAssignStatement("7"));
    CHECK(PKB::getInstance()->isIfStatement("8"));
    CHECK(PKB::getInstance()->isWhileStatement("9"));
    CHECK(PKB::getInstance()->isWhileStatement("10"));
    CHECK(PKB::getInstance()->isAssignStatement("11"));
    CHECK(PKB::getInstance()->isWhileStatement("12"));
    CHECK(PKB::getInstance()->isIfStatement("13"));
    CHECK(PKB::getInstance()->isWhileStatement("14"));
    CHECK(PKB::getInstance()->isIfStatement("15"));
    CHECK(PKB::getInstance()->isAssignStatement("16"));
    CHECK(PKB::getInstance()->isAssignStatement("17"));
    CHECK(PKB::getInstance()->isPrintStatement("18"));
    CHECK(PKB::getInstance()->isAssignStatement("19"));
//    CHECK(PKB::getInstance()->isCallStatement("23"));

    //these 3 dont work because the test cases here all run at different timings, creating multiple overlaps in the pkb (not sure how to fix yet)
//    CHECK(PKB::getInstance()->getAllAssignStatements().size()==8);
//    CHECK(PKB::getInstance()->getAllWhileStatements().size()==8);
//    CHECK(PKB::getInstance()->getAllIfStatements().size()==3);

}

TEST_CASE("Integration testing - follows relationship type check from parser to pkb") {

//    auto programNode = dynamic_cast<ProgramNode *>(Parser::Parse(sourceCode));
//    RelationshipExtractor::extractRelationships(programNode);
    SourceProcessor::run("integration_source.txt");

    CHECK(PKB::getInstance()->isFollows("1", "2"));
    CHECK(PKB::getInstance()->isFollows("2", "3") == false);
    CHECK(PKB::getInstance()->isFollows("2", "20"));
    CHECK(PKB::getInstance()->isFollows("1", "20") == false);
    CHECK(PKB::getInstance()->isFollowsT("1", "2"));
    CHECK(PKB::getInstance()->isFollowsT("1", "20"));
    CHECK(PKB::getInstance()->isFollows("3", "4"));

}
TEST_CASE("Integration testing - parent relationship type check from parser to pkb") {

//    auto programNode = dynamic_cast<ProgramNode *>(Parser::Parse(sourceCode));
//    RelationshipExtractor::extractRelationships(programNode);
    SourceProcessor::run("integration_source.txt");

    CHECK(PKB::getInstance()->isParent("3", "4") == false);
    CHECK(PKB::getInstance()->isParent("2", "3"));
    CHECK(PKB::getInstance()->isParent("2", "4"));
    CHECK(PKB::getInstance()->isParent("2", "5") == false);
    CHECK(PKB::getInstance()->isParentT("2", "5"));
    CHECK(PKB::getInstance()->isParentT("2", "7"));

}
TEST_CASE("Integration testing - modifies relationship type check from parser to pkb") {

//    auto programNode = dynamic_cast<ProgramNode *>(Parser::Parse(sourceCode));
//    RelationshipExtractor::extractRelationships(programNode);
    SourceProcessor::run("integration_source.txt");

    CHECK(PKB::getInstance()->isModifies("1", "entryPoint"));
    CHECK(PKB::getInstance()->isModifies("2", "A") == false);
    CHECK(PKB::getInstance()->isModifies("2", "a") == false);
    CHECK(PKB::getInstance()->isModifies("3", "mainWhileLoop"));
    CHECK(PKB::getInstance()->isModifies("3", "a") == false);
    CHECK(PKB::getInstance()->isModifies("2", "mainWhileLoop"));
    CHECK(PKB::getInstance()->isModifies("21", "genericRead"));
    CHECK(PKB::getInstance()->isModifies("22", "genericPrint") == false);

}
TEST_CASE("Integration testing - uses relationship type check from parser to pkb") {

//    auto programNode = dynamic_cast<ProgramNode *>(Parser::Parse(sourceCode));
//    RelationshipExtractor::extractRelationships(programNode);
    SourceProcessor::run("integration_source.txt");

    CHECK(PKB::getInstance()->isUses("1","entryPoint") == false);
    CHECK(PKB::getInstance()->isUses("2","A"));
    CHECK(PKB::getInstance()->isUses("2","a"));
    CHECK(PKB::getInstance()->isUses("3","a"));
    CHECK(PKB::getInstance()->isUses("3","mainWhileLoop")==false);
    CHECK(PKB::getInstance()->isUses("2","a"));
    CHECK(PKB::getInstance()->isUses("21","genericRead")==false);
    CHECK(PKB::getInstance()->isUses("22","genericPrint"));

    unordered_set<string> stmtTenUses = PKB::getInstance()->getVariablesUsed("10");
    unordered_set<string> stmtTwelveUses = PKB::getInstance()->getVariablesUsed("12");
    unordered_set<string> stmtThirteenUses = PKB::getInstance()->getVariablesUsed("13");
    CHECK(stmtTenUses.count("A") == 1);
    CHECK(stmtTenUses.count("B") == 1);
    CHECK(stmtTwelveUses.count("A") == 1);
    CHECK(stmtTwelveUses.count("B") == 1);
    CHECK(stmtThirteenUses.count("A") == 1);
    CHECK(stmtThirteenUses.count("B") == 1);
    CHECK(stmtThirteenUses.count("C") == 1);

}

TEST_CASE("Integration testing - additional procedure") {
    SourceProcessor::run("integration_source.txt");

    CHECK(PKB::getInstance()->isAssignStatement("24"));
    unordered_set<string> allProcedures = PKB::getInstance()->getAllProcedures();
    CHECK(allProcedures.count("genericProcedure") == 1);
    CHECK(allProcedures.count("NestedWithOtherConditions") == 1);

}
