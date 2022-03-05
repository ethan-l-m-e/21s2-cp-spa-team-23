#include "TNode/Node.h"
#include "catch.hpp"
#include "iostream"
#include "SourceProcessor/Parser.h"
#include "PKB.h"
#include "SourceProcessor/RelationshipExtractor.h"
using namespace std;

string sourceCode = "procedure NestedWithOtherConditions {\n"
                        "    entryPoint = 1;\n"
                        "    while (A < a) {\n"
                        "        mainWhileLoop = a;\n"
                        "        while (A > a) {\n"
                        "            while (A <= a) {\n"
                        "                while (A >= a) {\n"
                        "                    nestWithOnlyWhileLoops = 1;\n"
                        "                }\n"
                        "            }\n"
                        "        }\n"
                        "        if (A != a) then {\n"
                        "            while (A == 1) {\n"
                        "                while ((A == 1) || (B == 1)) {\n"
                        "                    nestedWhileInWhileInIf = 1;\n"
                        "                }\n"
                        "            }\n"
                        "        } else {\n"
                        "            while ((A == 1) && (B == 1)) {\n"
                        "                if ((A != 1) && ((B <= 1) && (C == 1))) then {\n"
                        "                    while (A == 1) {\n"
                        "                        if (((A != 1) && (1 < 2)) || ((longVariableName > 123456789) && (0 <= var123))) then {\n"
                        "                            nestedAlternateIfAndWhile = 1;\n"
                        "                        } else {\n"
                        "                            X = a%b;\n"
                        "                        }\n"
                        "                    }\n"
                        "                } else {\n"
                        "                    print doNothing;\n"
                        "                }\n"
                        "            }\n"
                        "        }\n"
                        "        endOfMainWhileLoop = 1;\n"
                        "    }\n"
                        "    genericAssignStatement = 1;\n"
                        "    read genericRead;\n"
                        "    print genericPrint;\n"
                        "}";

void require(bool b) {
    REQUIRE(b);
}

TEST_CASE("statement type check from parser to pkb") {
    auto programNode = dynamic_cast<ProgramNode*>(Parser::Parse(sourceCode));

    CHECK(programNode->getProcLst()[0]->getProcName() == "NestedWithOtherConditions");
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

    //these 3 dont work because the test cases here all run at different timings, creating multiple overlaps in the pkb (not sure how to fix yet)
//    CHECK(PKB::getInstance()->getAllAssignStatements().size()==8);
//    CHECK(PKB::getInstance()->getAllWhileStatements().size()==8);
//    CHECK(PKB::getInstance()->getAllIfStatements().size()==3);

}

TEST_CASE("follows relationship type check from parser to pkb") {
    auto programNode = dynamic_cast<ProgramNode *>(Parser::Parse(sourceCode));
    RelationshipExtractor::extractRelationships(programNode);

    CHECK(PKB::getInstance()->isFollows("1", "2"));
    CHECK(PKB::getInstance()->isFollows("2", "3") == false);
    CHECK(PKB::getInstance()->isFollows("2", "20"));
    CHECK(PKB::getInstance()->isFollows("1", "20") == false);
    CHECK(PKB::getInstance()->isFollowsT("1", "2"));
    CHECK(PKB::getInstance()->isFollowsT("1", "20"));
    CHECK(PKB::getInstance()->isFollows("3", "4"));

}
TEST_CASE("parent relationship type check from parser to pkb") {

    auto programNode = dynamic_cast<ProgramNode *>(Parser::Parse(sourceCode));
    RelationshipExtractor::extractRelationships(programNode);

    CHECK(PKB::getInstance()->isParent("3", "4") == false);
    CHECK(PKB::getInstance()->isParent("2", "3"));
    CHECK(PKB::getInstance()->isParent("2", "4"));
    CHECK(PKB::getInstance()->isParent("2", "5") == false);
    CHECK(PKB::getInstance()->isParentT("2", "5"));
    CHECK(PKB::getInstance()->isParentT("2", "7"));

}
TEST_CASE("modifies relationship type check from parser to pkb") {

    auto programNode = dynamic_cast<ProgramNode *>(Parser::Parse(sourceCode));
    RelationshipExtractor::extractRelationships(programNode);

    CHECK(PKB::getInstance()->isModifies("1", "entryPoint"));
    CHECK(PKB::getInstance()->isModifies("2", "A") == false);
    CHECK(PKB::getInstance()->isModifies("2", "a") == false);
    CHECK(PKB::getInstance()->isModifies("3", "mainWhileLoop"));
    CHECK(PKB::getInstance()->isModifies("3", "a") == false);
    CHECK(PKB::getInstance()->isModifies("2", "mainWhileLoop"));
    CHECK(PKB::getInstance()->isModifies("21", "genericRead"));
    CHECK(PKB::getInstance()->isModifies("22", "genericPrint") == false);

}
TEST_CASE("uses relationship type check from parser to pkb") {

    auto programNode = dynamic_cast<ProgramNode *>(Parser::Parse(sourceCode));
    RelationshipExtractor::extractRelationships(programNode);

    CHECK(PKB::getInstance()->isUses("1","entryPoint") == false);
    CHECK(PKB::getInstance()->isUses("2","A"));
    CHECK(PKB::getInstance()->isUses("2","a"));
    CHECK(PKB::getInstance()->isUses("3","a"));
    CHECK(PKB::getInstance()->isUses("3","mainWhileLoop")==false);
    CHECK(PKB::getInstance()->isUses("2","a"));
    CHECK(PKB::getInstance()->isUses("21","genericRead")==false);
    CHECK(PKB::getInstance()->isUses("22","genericPrint"));

}