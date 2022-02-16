//
// Created by Tin Hong Wen on 7/2/22.
//



#include "StringFormatter.h"
#include "Constants/Constants.h"
#include <string>
#include <regex>
#include <iostream>
#include "catch.hpp"

using namespace std;

TEST_CASE("extract String ") {
    vector<string> arr = StringFormatter::tokenizeByRegex("Select v such that Uses(a,b)","[ ]*((Select[ ]*)|(such that[ ]*)|[\\(\\)\\,])[ ]*");
}

TEST_CASE("partition assign") {
    string stmtLst = "x = x + 1;";
    vector<string> arr = StringFormatter::partitionAccordingToCase(stmtLst, ASSIGN);
    CHECK(arr[0] == "x = x + 1;");
    CHECK(arr[1] == "");

    stmtLst = "x = x + 1;read y;";
    arr = StringFormatter::partitionAccordingToCase(stmtLst, ASSIGN);
    CHECK(arr[0] == "x = x + 1;");
    CHECK(arr[1] == "read y;");

    stmtLst = "x = x + 1;\nread y;";
    arr = StringFormatter::partitionAccordingToCase(stmtLst, ASSIGN);
    CHECK(arr[0] == "x = x + 1;");
    CHECK(arr[1] == "read y;");
}


TEST_CASE("partition if-else and while") {
    string whileStatement = "while(x < present) {\n     read = print;\n}";
    vector<string> arr = StringFormatter::partitionAccordingToCase(whileStatement, WHILE);
    CHECK(arr[0] == "while(x < present){\n     read = print;\n}");
    whileStatement = "while(x < present) {\n     read = print;\n} read print;print x;";
    arr = StringFormatter::partitionAccordingToCase(whileStatement, WHILE);
    CHECK(arr[1] == "read print;print x;");
    string ifStmt = "if( x < present ) then   {\n print;\n}else {\nread x;}print y;";
    arr = StringFormatter::partitionAccordingToCase(ifStmt, IF_ELSE);
    CHECK(arr[0] == "if( x < present )then{\n print;\n}else{\nread x;}");
    CHECK(arr[1] == "print y;");

}