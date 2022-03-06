#include "TNode/Node.h"
#include "catch.hpp"
#include "iostream"
#include "SourceProcessor/Parser.h"
#include "PKB.h"
#include "SourceProcessor/RelationshipExtractor.h"
#include "SourceProcessor/SourceProcessor.h"
using namespace std;

TEST_CASE("Integration testing - Extra spaces on both ends") {
//    auto programNode = dynamic_cast<ProgramNode*>(Parser::Parse(sourceCode));

    SourceProcessor::run("integration_non_standardised_spacing.txt");

    CHECK(PKB::getInstance()->isAssignStatement("3"));
    CHECK(PKB::getInstance()->isAssignStatement("6"));
    CHECK(PKB::getInstance()->isReadStatement("12"));
    CHECK(PKB::getInstance()->isPrintStatement("13"));
    CHECK(PKB::getInstance()->isConstant("12"));

    CHECK(PKB::getInstance()->isFollows("2", "3"));
    CHECK(PKB::getInstance()->isFollows("3", "4"));
    CHECK(PKB::getInstance()->isFollows("1", "3")==false);
    CHECK(PKB::getInstance()->isFollowsT("1", "3"));
    CHECK(PKB::getInstance()->isFollows("3", "2")==false);

    CHECK(PKB::getInstance()->isParent("5", "6"));
    CHECK(PKB::getInstance()->isParentT("5", "8"));

    CHECK(PKB::getInstance()->isUses("3","a"));

    CHECK(PKB::getInstance()->isModifies("3", "a") == false);
    CHECK(PKB::getInstance()->isModifies("3", "assignThree"));


}

TEST_CASE("Integration testing - no spaces") {

//    auto programNode = dynamic_cast<ProgramNode *>(Parser::Parse(sourceCode));
//    RelationshipExtractor::extractRelationships(programNode);
    SourceProcessor::run("integration_non_standardised_spacing.txt");

    CHECK(PKB::getInstance()->isAssignStatement("4"));
    CHECK(PKB::getInstance()->isWhileStatement("5"));
    CHECK(PKB::getInstance()->isIfStatement("7"));

    CHECK(PKB::getInstance()->isFollows("4", "5"));
    CHECK(PKB::getInstance()->isFollowsT("1", "5"));
    CHECK(PKB::getInstance()->isFollows("4", "5"));

    CHECK(PKB::getInstance()->isParent("5", "7"));
    CHECK(PKB::getInstance()->isParentT("5", "8"));

    CHECK(PKB::getInstance()->isUses("4","a"));

    CHECK(PKB::getInstance()->isModifies("4", "a") == false);
    CHECK(PKB::getInstance()->isModifies("4", "assignFour"));

}
TEST_CASE("Integration testing - spaces within inequalities") {

//    auto programNode = dynamic_cast<ProgramNode *>(Parser::Parse(sourceCode));
//    RelationshipExtractor::extractRelationships(programNode);
    SourceProcessor::run("integration_non_standardised_spacing.txt");
    CHECK(PKB::getInstance()->isWhileStatement("10"));
    unordered_set<string> toCheck;
    CHECK(PKB::getInstance()->getVariablesUsed("10").count("A")==1);
    CHECK(PKB::getInstance()->getVariablesUsed("10").count("B")==1);

}
TEST_CASE("Integration testing - extra line spaces") {

//    auto programNode = dynamic_cast<ProgramNode *>(Parser::Parse(sourceCode));
//    RelationshipExtractor::extractRelationships(programNode);
    SourceProcessor::run("integration_non_standardised_spacing.txt");
    CHECK(PKB::getInstance()->isAssignStatement("14"));
    CHECK(PKB::getInstance()->isAssignStatement("15"));

    CHECK(PKB::getInstance()->isFollows("13", "14"));
    CHECK(PKB::getInstance()->isFollows("14", "15"));
    CHECK(PKB::getInstance()->isFollowsT("13", "15"));

    CHECK(PKB::getInstance()->isParent("16", "17"));

    CHECK(PKB::getInstance()->isUses("15","a"));

    CHECK(PKB::getInstance()->isModifies("15", "genericAssign2"));
}