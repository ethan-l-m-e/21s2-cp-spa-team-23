#include "TNode/Node.h"
#include "catch.hpp"
#include "iostream"
#include "SourceProcessor/Parser.h"
#include "PKB/PKB.h"
#include "SourceProcessor/RelationshipExtractor.h"
#include "SourceProcessor/SourceProcessor.h"
using namespace std;

void require(bool b) {
    REQUIRE(b);
}

TEST_CASE("Integration testing - statement type check from parser to pkb") {
    std::string filename = "../../../src/integration_testing/src/integration_source.txt";
    SourceProcessor::run(filename);

    CHECK(PKB::getInstance()->statement.assignStatements.isStatementNumber("1"));
    CHECK(PKB::getInstance()->statement.whileStatements.isStatementNumber("2"));
    CHECK(PKB::getInstance()->statement.assignStatements.isStatementNumber("3"));
    CHECK(PKB::getInstance()->statement.whileStatements.isStatementNumber("4"));
    CHECK(PKB::getInstance()->statement.whileStatements.isStatementNumber("5"));
    CHECK(PKB::getInstance()->statement.whileStatements.isStatementNumber("6"));
    CHECK(PKB::getInstance()->statement.assignStatements.isStatementNumber("7"));
    CHECK(PKB::getInstance()->statement.ifStatements.isStatementNumber("8"));
    CHECK(PKB::getInstance()->statement.whileStatements.isStatementNumber("9"));
    CHECK(PKB::getInstance()->statement.whileStatements.isStatementNumber("10"));
    CHECK(PKB::getInstance()->statement.assignStatements.isStatementNumber("11"));
    CHECK(PKB::getInstance()->statement.whileStatements.isStatementNumber("12"));
    CHECK(PKB::getInstance()->statement.ifStatements.isStatementNumber("13"));
    CHECK(PKB::getInstance()->statement.whileStatements.isStatementNumber("14"));
    CHECK(PKB::getInstance()->statement.ifStatements.isStatementNumber("15"));
    CHECK(PKB::getInstance()->statement.assignStatements.isStatementNumber("16"));
    CHECK(PKB::getInstance()->statement.assignStatements.isStatementNumber("17"));
    CHECK(PKB::getInstance()->statement.printStatements.isStatementNumber("18"));
    CHECK(PKB::getInstance()->statement.assignStatements.isStatementNumber("19"));
    CHECK(PKB::getInstance()->statement.callStatements.isStatementNumber("23"));

    //these 3 dont work because the test cases here all run at different timings, creating multiple overlaps in the pkb (not sure how to fix yet)
//    CHECK(PKB::getInstance()->getAllAssignStatements().size()==8);
//    CHECK(PKB::getInstance()->getAllWhileStatements().size()==8);
//    CHECK(PKB::getInstance()->getAllIfStatements().size()==3);

}

TEST_CASE("Integration testing - follows relationship type check from parser to pkb") {

//    auto programNode = dynamic_cast<ProgramNode *>(Parser::Parse(sourceCode));
//    RelationshipExtractor::extractRelationships(programNode);
    SourceProcessor::run("../../../src/integration_testing/src/integration_source.txt");

    CHECK(PKB::getInstance()->relationship.follows.isRelationship("1", "2"));
    CHECK(PKB::getInstance()->relationship.follows.isRelationship("2", "3") == false);
    CHECK(PKB::getInstance()->relationship.follows.isRelationship("2", "20"));
    CHECK(PKB::getInstance()->relationship.follows.isRelationship("1", "20") == false);
    CHECK(PKB::getInstance()->relationship.followsT.isRelationship("1", "2"));
    CHECK(PKB::getInstance()->relationship.followsT.isRelationship("1", "20"));
    CHECK(PKB::getInstance()->relationship.follows.isRelationship("3", "4"));

}
TEST_CASE("Integration testing - parent relationship type check from parser to pkb") {

//    auto programNode = dynamic_cast<ProgramNode *>(Parser::Parse(sourceCode));
//    RelationshipExtractor::extractRelationships(programNode);
    SourceProcessor::run("../../../src/integration_testing/src/integration_source.txt");

    CHECK(PKB::getInstance()->relationship.parent.isRelationship("3", "4") == false);
    CHECK(PKB::getInstance()->relationship.parent.isRelationship("2", "3"));
    CHECK(PKB::getInstance()->relationship.parent.isRelationship("2", "4"));
    CHECK(PKB::getInstance()->relationship.parent.isRelationship("2", "5") == false);
    CHECK(PKB::getInstance()->relationship.parentT.isRelationship("2", "5"));
    CHECK(PKB::getInstance()->relationship.parentT.isRelationship("2", "7"));

}
TEST_CASE("Integration testing - modifies relationship type check from parser to pkb") {

//    auto programNode = dynamic_cast<ProgramNode *>(Parser::Parse(sourceCode));
//    RelationshipExtractor::extractRelationships(programNode);
    SourceProcessor::run("../../../src/integration_testing/src/integration_source.txt");

    CHECK(PKB::getInstance()->relationship.modifiesS.isRelationship("1", "entryPoint"));
    CHECK(PKB::getInstance()->relationship.modifiesS.isRelationship("2", "A") == false);
    CHECK(PKB::getInstance()->relationship.modifiesS.isRelationship("2", "a") == false);
    CHECK(PKB::getInstance()->relationship.modifiesS.isRelationship("3", "mainWhileLoop"));
    CHECK(PKB::getInstance()->relationship.modifiesS.isRelationship("3", "a") == false);
    CHECK(PKB::getInstance()->relationship.modifiesS.isRelationship("2", "mainWhileLoop"));
    CHECK(PKB::getInstance()->relationship.modifiesS.isRelationship("21", "genericRead"));
    CHECK(PKB::getInstance()->relationship.modifiesS.isRelationship("22", "genericPrint") == false);
    CHECK(PKB::getInstance()->relationship.modifiesP.isRelationship("NestedWithOtherConditions", "mainWhileLoop"));
    CHECK(PKB::getInstance()->relationship.modifiesP.isRelationship("genericProcedure", "insideGenericProcedure"));

}
TEST_CASE("Integration testing - uses relationship type check from parser to pkb") {

//    auto programNode = dynamic_cast<ProgramNode *>(Parser::Parse(sourceCode));
//    RelationshipExtractor::extractRelationships(programNode);
    SourceProcessor::run("../../../src/integration_testing/src/integration_source.txt");

    CHECK(PKB::getInstance()->relationship.usesS.isRelationship("1","entryPoint") == false);
    CHECK(PKB::getInstance()->relationship.usesS.isRelationship("2","A"));
    CHECK(PKB::getInstance()->relationship.usesS.isRelationship("2","a"));
    CHECK(PKB::getInstance()->relationship.usesS.isRelationship("3","a"));
    CHECK(PKB::getInstance()->relationship.usesS.isRelationship("3","mainWhileLoop")==false);
    CHECK(PKB::getInstance()->relationship.usesS.isRelationship("2","a"));
    CHECK(PKB::getInstance()->relationship.usesS.isRelationship("21","genericRead")==false);
    CHECK(PKB::getInstance()->relationship.usesS.isRelationship("22","genericPrint"));

    CHECK(PKB::getInstance()->relationship.usesS.isRelationship("10","A"));
    CHECK(PKB::getInstance()->relationship.usesS.isRelationship("10","B"));
    CHECK(PKB::getInstance()->relationship.usesS.isRelationship("12","A"));
    CHECK(PKB::getInstance()->relationship.usesS.isRelationship("12","B"));
    CHECK(PKB::getInstance()->relationship.usesS.isRelationship("13","A"));
    CHECK(PKB::getInstance()->relationship.usesS.isRelationship("13","B"));
    CHECK(PKB::getInstance()->relationship.usesS.isRelationship("13","C"));

    CHECK(PKB::getInstance()->relationship.usesP.isRelationship("NestedWithOtherConditions","A"));
    CHECK(PKB::getInstance()->relationship.usesP.isRelationship("genericProcedure","a"));


}

TEST_CASE("Integration testing - additional procedure") {
    SourceProcessor::run("../../../src/integration_testing/src/integration_source.txt");

    CHECK(PKB::getInstance()->statement.assignStatements.isStatementNumber("24"));
    unordered_set<string> allProcedures = PKB::getInstance()->entity.procedures.getAll();
    CHECK(allProcedures.count("genericProcedure") == 1);
    CHECK(allProcedures.count("NestedWithOtherConditions") == 1);

}
TEST_CASE("nested branch"){
    SourceProcessor::run("../../../src/integration_testing/src/integration_source_for_CFG.txt");
    CHECK(PKB::getInstance()->relationship.next.isRelationship("1","2"));
    CHECK(PKB::getInstance()->relationship.next.isRelationship("2","3"));
    CHECK(PKB::getInstance()->relationship.next.isRelationship("3","4")==false);
    CHECK(PKB::getInstance()->relationship.next.isRelationship("4","5"));
    CHECK(PKB::getInstance()->relationship.next.isRelationship("5","6"));
    CHECK(PKB::getInstance()->relationship.next.isRelationship("6","7")==false);
    CHECK(PKB::getInstance()->relationship.next.isRelationship("7","8"));
    CHECK(PKB::getInstance()->relationship.next.isRelationship("8","9")==false);
}

TEST_CASE("while nested if-then"){
    SourceProcessor::run("../../../src/integration_testing/src/integration_source_for_CFG.txt");
    CHECK(PKB::getInstance()->relationship.next.isRelationship("10","11"));
    CHECK(PKB::getInstance()->relationship.next.isRelationship("11","12"));
    CHECK(PKB::getInstance()->relationship.next.isRelationship("12","13"));
    CHECK(PKB::getInstance()->relationship.next.isRelationship("13","14"));
    CHECK(PKB::getInstance()->relationship.next.isRelationship("14","15")==false);
    CHECK(PKB::getInstance()->relationship.next.isRelationship("15","16"));
    CHECK(PKB::getInstance()->relationship.next.isRelationship("17","16"));
    CHECK(PKB::getInstance()->relationship.next.isRelationship("16","15"));
    CHECK(PKB::getInstance()->relationship.next.isRelationship("15","18"));
    CHECK(PKB::getInstance()->relationship.next.isRelationship("16","18")==false);
    CHECK(PKB::getInstance()->relationship.next.isRelationship("18","19"));
    CHECK(PKB::getInstance()->relationship.next.isRelationship("19","20"));
    CHECK(PKB::getInstance()->relationship.next.isRelationship("21","22"));
    CHECK(PKB::getInstance()->relationship.next.isRelationship("22","23")==false);
    CHECK(PKB::getInstance()->relationship.next.isRelationship("22","19"));
    CHECK(PKB::getInstance()->relationship.next.isRelationship("23","19"));



}