//
// Created by Tin Hong Wen on 11/3/22.
//

#include "QP_database/AffectsOperator.h"
#include "QP_database/NextTOperator.h"
#include "QP_Evaluator/TestUtilities.h"
#include "QP_Parser/QueryParser.h"
#include "catch.hpp"

using namespace std;

PKB* testPKB;

AffectsOperator* affectsOp = AffectsOperator::getInstance();
NextTOperator* nextOp = NextTOperator::getInstance();

// test adjacent
// test straight
TEST_CASE("Affects: isRelation") {
    string sourceCode;
    // test linear and if
    sourceCode = "procedure exampleStraightAndIf {"
                        //#1
                        "x = y;"
                        "z = x;"
                        "x = 4;"
                        "y = dasdasd;"
                        "y = dasdasdas;"
                        //#6
                        "d = z + 1;"
                        "if(x < present) then {"
                        "z = adas;"
                        "read d;"
                        "s = d + 1; } else {"
                        //#11
                        "z = adas;"
                        "y = fff;"
                        "s =  d + 1;}"
                        "print f;"
                        "x = z;}";
    constructPKBWithParser(sourceCode);
    CHECK(!affectsOp->computeRelation("1", "1000")); //no results
    CHECK(!affectsOp->computeRelation("9", "14")); // not assign

    CHECK(affectsOp->computeRelation("1", "2")); // adjacent
    CHECK(!affectsOp->computeRelation("2", "1")); // reverse
    CHECK(!affectsOp->computeRelation("1", "3")); // 2 steps obs
    CHECK(affectsOp->computeRelation("2", "6"));  // far
    CHECK(!affectsOp->computeRelation("6", "10")); // linear -> branchLeft obs
    CHECK(affectsOp->computeRelation("6", "13")); // linear ->  branchRight
    CHECK(affectsOp->computeRelation("8", "15")); // branch -> outLinear
    CHECK(affectsOp->computeRelation("11", "15"));

    //test while (with linear)
    sourceCode = "procedure exampleWhile {"
                        //#1
                        "b = bb;"
                        "while(x < y) {"
                        "z = x + 1;"
                        "print f;"
                        "x = z;"
                        //#6
                        "a = a + b;}"
                        "x = a;"
                        "}";
    testPKB = constructPKBWithParser(sourceCode);
    CHECK(affectsOp->computeRelation("5", "3")); // after
    CHECK(affectsOp->computeRelation("3", "5")); // before
    CHECK(affectsOp->computeRelation("6", "6")); // self loop
    CHECK(!affectsOp->computeRelation("5", "2")); // after -> init loop
    CHECK(affectsOp->computeRelation("6", "7"));  // loop -> linear
    CHECK(affectsOp->computeRelation("1", "6")); //  linear -> branch - > linear

    //test call statements
    sourceCode = "procedure proc1 {"
                 //#1
                 "x = d + 1;"
                 "call proc2;"
                 "y = x + 3;"
                 "if(x < present) then {"
                 "call proc2;"
                 //#6
                 "ada = y;} else {"
                 "while(x < s) {"
                 "y = y + 1;"
                 "call proc2;}}}"
                 "procedure proc2 {"
                 "x = d - 1;"
                 //#11
                 "y = s + s;"
                 "}";
    constructPKBWithParser(sourceCode);
    CHECK(!affectsOp->computeRelation("1", "10")); // diff procedures
    CHECK(!affectsOp->computeRelation("3", "6")); // linear -> branch obs
    CHECK(affectsOp->computeRelation("3", "8")); // linear -> branch (steer)
    CHECK(!affectsOp->computeRelation("8", "8")); // self loop obs

}


TEST_CASE("Affects: computeLHS & RHS") {
    //linear: adj, 2 step, far
    //branch:simple, nested
    //loop: simple, nested
    string sourceCode = "procedure proc1 {"
                        //#1
                        "x = y;"
                        "y = x;"
                        "print y;"
                        "x = y;"
                        "print y;"
                        //#6
                        "print y;"
                        "print y;"
                        "y = x;"
                        "read y;"
                        "x = y;"
                        "}";
    constructPKBWithParser(sourceCode);

    CHECK(unordered_set<string>{} == affectsOp->computeLHS("1000"));
    CHECK(unordered_set<string>{} == affectsOp->computeLHS("3"));
    CHECK(unordered_set<string>{"1"} == affectsOp->computeLHS("2"));
    CHECK(unordered_set<string>{"2"} == affectsOp->computeLHS("4"));
    CHECK(unordered_set<string>{"4"} == affectsOp->computeLHS("8"));
    CHECK(unordered_set<string>{} == affectsOp->computeLHS("10"));

    CHECK(unordered_set<string>{} == affectsOp->computeRHS("1000"));
    CHECK(unordered_set<string>{} == affectsOp->computeRHS("3"));
    CHECK(unordered_set<string>{"2"} == affectsOp->computeRHS("1"));
    CHECK(unordered_set<string>{"4"} == affectsOp->computeRHS("2"));
    CHECK(unordered_set<string>{"8"} == affectsOp->computeRHS("4"));
    CHECK(unordered_set<string>{} == affectsOp->computeRHS("8"));

    sourceCode = "procedure branchSet {"
                    //#1
                    "x = y;"
                    "if(x < y) then {"
                        "x = y;"
                    "} else {"
                        "if(x < y) then {"
                            "read x;"
                            "y = x;"
                        "} else {"
                            "if(x < y) then {"
                                "y = x;"
                            "} else {"
                                "y = x;"
                            "}"
                        "}"
                    "}"
                 "}";
    constructPKBWithParser(sourceCode);
    //CHECK(unordered_set<string>{} == affectsOp->computeRHS("3"));
    //CHECK(unordered_set<string>{"8", "9"} == affectsOp->computeRHS("1"));

}

TEST_CASE("Affects: combined and nested") {
    // both branch and loop
}



void constructPKBForNextT() {
    string sourceCode = "procedure proc1 {"
                        //#1
                        "if(x < 1) then {"
                        "print x;"
                        "print y;"
                        "print z;"
                        "read ddd;} else {"
                        //#6
                        "while (s < a){"
                        "while (a < b) {"
                        "read s; }}}"
                        "x = x + 1;"
                        "while (s < a) {"
                        //#11
                        "x = x + 1;"
                        "if(s < a) then {"
                        "x = x + 1; } else {"
                        "x = x + 1;}"
                        "}"
                        "}"
                        "procedure proc2 {"
                        "x = x + 1;"
                        //#16
                        "x = x + 1;"
                        "x = x + 1;"
                        "}";

    constructPKBWithParser(sourceCode);
}

TEST_CASE("nextOp* - isRelation") {
    constructPKBForNextT();

    /*
    CHECK(!nextOp->computeRelation("4", "100"));
    CHECK(!nextOp->computeRelation("4", "16"));
    // direct
    CHECK(nextOp->computeRelation("1", "2"));
    CHECK(nextOp->computeRelation("2", "3"));
    CHECK(nextOp->computeRelation("1", "5"));

    //loop
    CHECK(!nextOp->computeRelation("3", "8"));

    CHECK(nextOp->computeRelation("8", "7"));
    CHECK(nextOp->computeRelation("8", "6"));

    //branch
    CHECK(!nextOp->computeRelation("4", "8"));
    CHECK(nextOp->computeRelation("4", "13"));
    */
    CHECK(nextOp->computeRelation("1", "14"));

}

TEST_CASE("nextOp* - computeRHS"){
    constructPKBForNextT();

    CHECK(unordered_set<string>{} == nextOp->computeRHS("17"));
    CHECK(unordered_set<string>{"17"} == nextOp->computeRHS("16"));
    CHECK(unordered_set<string>{"16", "17"} == nextOp->computeRHS("15"));
    CHECK(unordered_set<string>{"2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14"} ==
                  nextOp->computeRHS("1"));
    CHECK(unordered_set<string>{"3", "4", "5", "9", "10", "11", "12", "13", "14"} == nextOp->computeRHS("2"));
    CHECK(unordered_set<string>{"6", "7", "8", "9", "10", "11", "12", "13", "14"} == nextOp->computeRHS("8"));
    CHECK(unordered_set<string>{"6", "7", "8", "9", "10", "11", "12", "13", "14"} == nextOp->computeRHS("7"));

    // not working
    //CHECK(unordered_set<string>{"10", "11", "12", "13", "14"} == nextOp->computeRHS("14"));
}

TEST_CASE("nextOp* - computeLHS") {
    constructPKBForNextT();

    CHECK(unordered_set<string>{} == nextOp->computeLHS("15"));
    CHECK(unordered_set<string>{"15"} == nextOp->computeLHS("16"));
    CHECK(unordered_set<string>{"15", "16"} == nextOp->computeLHS("17"));
    // not working
    //CHECK(unordered_set<string>{"1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14"} ==
    //      nextOp->computeLHS("14"));
    CHECK(unordered_set<string>{"1", "2", "3", "4", "5", "6", "7", "8"} == nextOp->computeLHS("9"));
    CHECK(unordered_set<string>{"1", "6", "7", "8"} == nextOp->computeLHS("8"));
}