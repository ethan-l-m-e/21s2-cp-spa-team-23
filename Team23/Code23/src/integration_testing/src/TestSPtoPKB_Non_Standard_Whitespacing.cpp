#include "TNode/Node.h"
#include "catch.hpp"
#include "iostream"
#include "SourceProcessor/Parser.h"
#include "PKB/PKB.h"
#include "SourceProcessor/RelationshipExtractor.h"
#include "SourceProcessor/SourceProcessor.h"

using namespace std;

TEST_CASE("Integration testing - Extra spaces on both ends") {
//    auto programNode = dynamic_cast<ProgramNode*>(Parser::Parse(sourceCode));

    SourceProcessor::run("integration_non_standardised_spacing.txt");

    CHECK(PKB::getInstance()->statement.assignStatements.isStatementNumber("3"));
    CHECK(PKB::getInstance()->statement.assignStatements.isStatementNumber("6"));
    CHECK(PKB::getInstance()->statement.assignStatements.isStatementNumber("18"));
    CHECK(PKB::getInstance()->statement.readStatements.isStatementNumber("12"));
    CHECK(PKB::getInstance()->statement.printStatements.isStatementNumber("13"));
    CHECK(PKB::getInstance()->entity.constants.isEntity("12"));

    CHECK(PKB::getInstance()->relationship.follows.isRelationship("2", "3"));
    CHECK(PKB::getInstance()->relationship.follows.isRelationship("3", "4"));
    CHECK(PKB::getInstance()->relationship.follows.isRelationship("1", "3")==false);
    CHECK(PKB::getInstance()->relationship.followsT.isRelationship("1", "3"));
    CHECK(PKB::getInstance()->relationship.follows.isRelationship("3", "2")==false);

    CHECK(PKB::getInstance()->relationship.parent.isRelationship("5", "6"));
    CHECK(PKB::getInstance()->relationship.parentT.isRelationship("5", "8"));

    CHECK(PKB::getInstance()->relationship.usesS.isRelationship("3","a"));

    CHECK(PKB::getInstance()->relationship.modifiesS.isRelationship("3", "a") == false);
    CHECK(PKB::getInstance()->relationship.modifiesS.isRelationship("3", "assignThree"));


}

TEST_CASE("Integration testing - no spaces") {

//    auto programNode = dynamic_cast<ProgramNode *>(Parser::Parse(sourceCode));
//    RelationshipExtractor::extractRelationships(programNode);
    SourceProcessor::run("integration_non_standardised_spacing.txt");

    CHECK(PKB::getInstance()->statement.readStatements.isStatementNumber("4"));
    CHECK(PKB::getInstance()->statement.whileStatements.isStatementNumber("5"));
    CHECK(PKB::getInstance()->statement.ifStatements.isStatementNumber("7"));

    CHECK(PKB::getInstance()->relationship.follows.isRelationship("4", "5"));
    CHECK(PKB::getInstance()->relationship.followsT.isRelationship("1", "5"));
    CHECK(PKB::getInstance()->relationship.follows.isRelationship("4", "5"));

    CHECK(PKB::getInstance()->relationship.parent.isRelationship("5", "7"));
    CHECK(PKB::getInstance()->relationship.parentT.isRelationship("5", "8"));

    CHECK(PKB::getInstance()->relationship.usesS.isRelationship("4","a"));

    CHECK(PKB::getInstance()->relationship.modifiesS.isRelationship("4", "a") == false);
    CHECK(PKB::getInstance()->relationship.modifiesS.isRelationship("4", "assignFour"));

}
TEST_CASE("Integration testing - spaces within inequalities") {

//    auto programNode = dynamic_cast<ProgramNode *>(Parser::Parse(sourceCode));
//    RelationshipExtractor::extractRelationships(programNode);
    SourceProcessor::run("integration_non_standardised_spacing.txt");
    CHECK(PKB::getInstance()->statement.whileStatements.isStatementNumber("10"));
    CHECK(PKB::getInstance()->relationship.usesS.isRelationship("10","A"));
    CHECK(PKB::getInstance()->relationship.usesS.isRelationship("10","B"));

}
TEST_CASE("Integration testing - extra line spaces") {

//    auto programNode = dynamic_cast<ProgramNode *>(Parser::Parse(sourceCode));
//    RelationshipExtractor::extractRelationships(programNode);
    SourceProcessor::run("integration_non_standardised_spacing.txt");
    CHECK(PKB::getInstance()->statement.readStatements.isStatementNumber("14"));
    CHECK(PKB::getInstance()->statement.readStatements.isStatementNumber("15"));

    CHECK(PKB::getInstance()->relationship.follows.isRelationship("13", "14"));
    CHECK(PKB::getInstance()->relationship.follows.isRelationship("14", "15"));
    CHECK(PKB::getInstance()->relationship.followsT.isRelationship("13", "15"));

    CHECK(PKB::getInstance()->relationship.parent.isRelationship("16", "17"));

    CHECK(PKB::getInstance()->relationship.usesS.isRelationship("15","a"));

    CHECK(PKB::getInstance()->relationship.modifiesS.isRelationship("15", "genericAssign2"));
}