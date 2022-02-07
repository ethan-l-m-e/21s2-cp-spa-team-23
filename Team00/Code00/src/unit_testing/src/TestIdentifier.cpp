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


TEST_CASE("READ") {
    switchCase = Identifier::identifyFirstObject(read1 + "\n");        //standard read
    CHECK(switchCase == READ);
    switchCase = Identifier::identifyFirstObject(read2);        //read with non-standard spacing
    CHECK(switchCase == READ);
    switchCase = Identifier::identifyFirstObject(read3_wrong);  //incorrect varname
    CHECK(switchCase == ERROR);
    switchCase = Identifier::identifyFirstObject("read" + varName + ";");  //wrong syntax
    CHECK(switchCase == ERROR);
}

TEST_CASE("PRINT") {
    switchCase = Identifier::identifyFirstObject(print1 + "\n");   //standard print
    CHECK(switchCase == PRINT);
    switchCase = Identifier::identifyFirstObject(print2);   //non-standard spacing
    CHECK(switchCase == PRINT);
    switchCase = Identifier::identifyFirstObject(print3_wrong); //incorrect varname
    CHECK(switchCase == ERROR);
    switchCase = Identifier::identifyFirstObject("print " + varName);  //missing ;
    CHECK(switchCase == ERROR);
}

TEST_CASE("ASSIGN") {
    switchCase = Identifier::identifyFirstObject(assign1 + "\n"); // standard assign
    CHECK(switchCase == ASSIGN);
    switchCase = Identifier::identifyFirstObject(assign2);  //non-standard spacing
    CHECK(switchCase == ASSIGN);
    switchCase = Identifier::identifyFirstObject("x = ;");  // missing RHS expr
    CHECK(switchCase == ERROR);
    switchCase = Identifier::identifyFirstObject("x = 1 + 1");  //missing ;
    CHECK(switchCase == ERROR);
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
    switchCase = Identifier::identifyFirstObject("x + 1");  //standard
    CHECK(switchCase == EXPR_TERM);
    switchCase = Identifier::identifyFirstObject("((x + 1) + 2) * (2 + 2)");  //brackets
    CHECK(switchCase == EXPR_TERM);
    switchCase = Identifier::identifyFirstObject("((x + 1) + 2");   //incorrect brackets
    CHECK(switchCase == ERROR);
    switchCase = Identifier::identifyFirstObject(")(x + 1) + 2");   //incorrect brackets
    CHECK(switchCase == ERROR);
    switchCase = Identifier::identifyFirstObject("x + 1;"); // ;
    CHECK(switchCase == ERROR);
}

TEST_CASE("PROCEDURE") {
    string procedureLine = "procedure Example {\n " + assign1 +"\n}";   //standard with new line
    switchCase = Identifier::identifyFirstObject(procedureLine);
    CHECK(switchCase == PROCEDURE);
    procedureLine = "procedure Example { " + assign1 +"}";              //no new line
    switchCase = Identifier::identifyFirstObject(procedureLine);
    CHECK(switchCase == PROCEDURE);
    procedureLine = "procedure   Example{\n" + assign1 +"}\n";     //non-standard spacing
    switchCase = Identifier::identifyFirstObject(procedureLine);
    CHECK(switchCase == PROCEDURE);
    procedureLine = "procedure Example {\n{" + assign1 +"\n}";          //incorrect bracket count
    switchCase = Identifier::identifyFirstObject(procedureLine);
    CHECK(switchCase == ERROR);
}

TEST_CASE("STMTLST") {
    string stmtlst = read1 + "\n" + assign1 + "\n" + print1;
    switchCase = Identifier::identifyFirstObject(stmtlst);
    CHECK(switchCase == READ);
    stmtlst = assign1 + "\n" + print1;
    CHECK(switchCase == ASSIGN);
}

TEST_CASE("COND_EXPR") {
    string cond1 = "x < present";
    switchCase = Identifier::identifyFirstObject(cond1);
    CHECK(switchCase == COND_EXPR);
    cond1 = "!( x < present)";
    switchCase = Identifier::identifyFirstObject(cond1);
    CHECK(switchCase == COND_EXPR);
    cond1 = "(x > 1) && (y < 2)";
    switchCase = Identifier::identifyFirstObject(cond1);
    CHECK(switchCase == COND_EXPR);
    cond1 = "(x > 1) || (y < 2)";
    switchCase = Identifier::identifyFirstObject(cond1);
    CHECK(switchCase == COND_EXPR);
    cond1 = "!((x > 1)";
    switchCase = Identifier::identifyFirstObject(cond1);
    CHECK(switchCase == ERROR);
}

TEST_CASE("WHILE") {

}

TEST_CASE("IF") {

}



