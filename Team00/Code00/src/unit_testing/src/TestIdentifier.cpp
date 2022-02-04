//
// Created by Tin Hong Wen on 4/2/22.
//

#include "Identifier.h"
#include "catch.hpp"
#include "Constants/Constants.h"

using namespace std;

int switchCase;

string varName = "x";
string varNameWrong = "123a";
string integer = "222";
string strayBracket = ")";

string assign1 = "x = (x + 1) * 3;";
string assign2 = "     y    = x + s;";

string read1 = "read method;";
string read2 = "   read    " + varName + " ;";
string read3_wrong = "read " + varNameWrong + ";";

string print1 = "print method;";
string print2 = "   print    " + varName + " ;";
string print3_wrong = "print " + varNameWrong + ";";

string expr1 = "x + 2";

TEST_CASE("READ") {
    switchCase = Identifier::identifyFirstObject(read1);
    CHECK(switchCase == READ);
    switchCase = Identifier::identifyFirstObject(read2);
    CHECK(switchCase == READ);
    switchCase = Identifier::identifyFirstObject(read3_wrong);
    CHECK(switchCase == ERROR);
}

TEST_CASE("PRINT") {
    switchCase = Identifier::identifyFirstObject(print1);
    CHECK(switchCase == READ);
    switchCase = Identifier::identifyFirstObject(print2);
    CHECK(switchCase == READ);
    switchCase = Identifier::identifyFirstObject(print3_wrong);
    CHECK(switchCase == ERROR);
}

TEST_CASE("ASSIGN") {
    switchCase = Identifier::identifyFirstObject(assign1);
    CHECK(switchCase == ASSIGN);
    switchCase = Identifier::identifyFirstObject(assign2);
    CHECK(switchCase == ASSIGN);
    switchCase = Identifier::identifyFirstObject(assign1 + "\n");
    CHECK(switchCase == ASSIGN);
}

TEST_CASE("BASE CASE") {
    switchCase = Identifier::identifyFirstObject(varName);
    CHECK(switchCase == BASE_CASE);
    switchCase = Identifier::identifyFirstObject(integer);
    CHECK(switchCase == BASE_CASE);
    switchCase = Identifier::identifyFirstObject(varNameWrong);
    CHECK(switchCase == ERROR);
    switchCase = Identifier::identifyFirstObject(strayBracket);
    CHECK(switchCase == ERROR);
}

TEST_CASE("EXPR_TERM") {

}

TEST_CASE("PROCEDURE") {

}

TEST_CASE("GENERAL") {

}




