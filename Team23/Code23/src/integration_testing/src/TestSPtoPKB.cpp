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
    CHECK(PKB::getInstance()->isCallStatement("23"));

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

    CHECK(PKB::getInstance()->isModifiesS("1", "entryPoint"));
    CHECK(PKB::getInstance()->isModifiesS("2", "A") == false);
    CHECK(PKB::getInstance()->isModifiesS("2", "a") == false);
    CHECK(PKB::getInstance()->isModifiesS("3", "mainWhileLoop"));
    CHECK(PKB::getInstance()->isModifiesS("3", "a") == false);
    CHECK(PKB::getInstance()->isModifiesS("2", "mainWhileLoop"));
    CHECK(PKB::getInstance()->isModifiesS("21", "genericRead"));
    CHECK(PKB::getInstance()->isModifiesS("22", "genericPrint") == false);
    CHECK(PKB::getInstance()->isModifiesP("NestedWithOtherConditions", "mainWhileLoop"));
    CHECK(PKB::getInstance()->isModifiesP("genericProcedure", "insideGenericProcedure"));

}
TEST_CASE("Integration testing - uses relationship type check from parser to pkb") {

//    auto programNode = dynamic_cast<ProgramNode *>(Parser::Parse(sourceCode));
//    RelationshipExtractor::extractRelationships(programNode);
    SourceProcessor::run("integration_source.txt");

    CHECK(PKB::getInstance()->isUsesS("1","entryPoint") == false);
    CHECK(PKB::getInstance()->isUsesS("2","A"));
    CHECK(PKB::getInstance()->isUsesS("2","a"));
    CHECK(PKB::getInstance()->isUsesS("3","a"));
    CHECK(PKB::getInstance()->isUsesS("3","mainWhileLoop")==false);
    CHECK(PKB::getInstance()->isUsesS("2","a"));
    CHECK(PKB::getInstance()->isUsesS("21","genericRead")==false);
    CHECK(PKB::getInstance()->isUsesS("22","genericPrint"));

    CHECK(PKB::getInstance()->isUsesS("10","A"));
    CHECK(PKB::getInstance()->isUsesS("10","B"));
    CHECK(PKB::getInstance()->isUsesS("12","A"));
    CHECK(PKB::getInstance()->isUsesS("12","B"));
    CHECK(PKB::getInstance()->isUsesS("13","A"));
    CHECK(PKB::getInstance()->isUsesS("13","B"));
    CHECK(PKB::getInstance()->isUsesS("13","C"));

    CHECK(PKB::getInstance()->isUsesP("NestedWithOtherConditions","A"));
    CHECK(PKB::getInstance()->isUsesP("genericProcedure","a"));


}

TEST_CASE("Integration testing - additional procedure") {
    SourceProcessor::run("integration_source.txt");

    CHECK(PKB::getInstance()->isAssignStatement("24"));
    unordered_set<string> allProcedures = PKB::getInstance()->getAllProcedures();
    CHECK(allProcedures.count("genericProcedure") == 1);
    CHECK(allProcedures.count("NestedWithOtherConditions") == 1);

}
