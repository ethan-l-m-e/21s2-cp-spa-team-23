//
// Created by Tin Hong Wen on 6/2/22.
//

#include "SourceProcessor/SourceTokenizer.h"

#include "catch.hpp"

using namespace std;

TEST_CASE("call token - basic") {
    string a = "    call     name       ;  ";
    vector<string> v;
    SourceTokenizer::extractCall(a, v);
    REQUIRE(v[0] == "name");
}

TEST_CASE("assign token - basic") {
    string a = "     x = y + 1;";
    vector<string> v;
    SourceTokenizer::extractAssign(a, v);
    REQUIRE(v[0] == "x");
    REQUIRE(v[1] == "y + 1");
}

TEST_CASE("assign token - weird whitespaces") {
    string a = " x  = y   +  1   ;  ";
    vector<string> v;
    SourceTokenizer::extractAssign(a, v);
    REQUIRE(v[0] == "x");
    REQUIRE(v[1] == "y   +  1");
}

TEST_CASE("procedure token - basic") {
    string p = "procedure test {x = 1}";
    vector<string> v;
    SourceTokenizer::extractProcedure(p, v);
    REQUIRE(v[0] == "test");
    REQUIRE(v[1] == "x = 1");
}

TEST_CASE("if-else token - basic") {
    string p = "if (x==1 )then {y = 1} else {y = 2}";
    vector<string> v;
    SourceTokenizer::extractIfElseThen(p, v);
    REQUIRE(v[0] == "x==1");
    REQUIRE(v[1] == "y = 1");
    REQUIRE(v[2] == "y = 2");
}
TEST_CASE("if-else token - nested") {
    string p = "if (x==1) then {y=1; if(a==1)then{b=2}else{c=2}}else{y = 3; if(l==1)then{m=2}else{n=2}}";
    vector<string> v;
    SourceTokenizer::extractIfElseThen(p, v);
    REQUIRE(v[0] == "x==1");
    REQUIRE(v[1] == "y=1; if(a==1)then{b=2}else{c=2}");
    REQUIRE(v[2] == "y = 3; if(l==1)then{m=2}else{n=2}");
}

TEST_CASE("while token - basic") {
    string p = "while(x==0) {y = 1;}";
    vector<string> v;
    SourceTokenizer::extractWhile(p, v);
    REQUIRE(v[0] == "x==0");
    REQUIRE(v[1] == "y = 1;");
}

TEST_CASE("while token - nested while loop") {
    string p = "while(x==0) {y = 1; while(y==0){z = 2;}}";
    vector<string> v;
    SourceTokenizer::extractWhile(p, v);
    REQUIRE(v[0] == "x==0");
    REQUIRE(v[1] == "y = 1; while(y==0){z = 2;}");
}

TEST_CASE("expression token - basic") {
    string p = " x + y ";
    vector<string> v;
    SourceTokenizer::extractExpression(p, v);
    REQUIRE(v[0] == "x");
    REQUIRE(v[1] == "y");
    REQUIRE(v[2] == "+");
}

TEST_CASE("expression token - only '+'") {
    string p = " x + y +z + a + b + c";
    vector<string> v;
    SourceTokenizer::extractExpression(p, v);
    REQUIRE(v[0] == "x + y +z + a + b");
    REQUIRE(v[1] == "c");
    REQUIRE(v[2] == "+");
}

TEST_CASE("expression token - only '*'") {
    string p = " x * y *z * a * b * c";
    vector<string> v;
    SourceTokenizer::extractExpression(p, v);
    REQUIRE(v[0] == "x * y *z * a * b");
    REQUIRE(v[1] == "c");
    REQUIRE(v[2] == "*");
}

TEST_CASE("expression token - '+' and '-'") {
    string p = " x + y +z - a + b - c";
    vector<string> v;
    SourceTokenizer::extractExpression(p, v);
    REQUIRE(v[0] == "x + y +z - a + b");
    REQUIRE(v[1] == "c");
    REQUIRE(v[2] == "-");
}

TEST_CASE("expression token - '+' and '-' and '*' and '/' ") {
    string p = " x + y * z - a - b / c";
    vector<string> v;
    SourceTokenizer::extractExpression(p, v);
    REQUIRE(v[0] == "x + y * z - a");
    REQUIRE(v[1] == "b / c");
    REQUIRE(v[2] == "-");
}

TEST_CASE("expression token - '+' and '*' and brackets") {
    string p = " (x + y) * z + (a +c)";
    vector<string> v;
    SourceTokenizer::extractExpression(p, v);
    REQUIRE(v[0] == "(x + y) * z");
    REQUIRE(v[1] == "(a +c)");
    REQUIRE(v[2] == "+");
}

TEST_CASE("expression token - brackets on the whole expression") {
    string p = "(x + y + z)";
    vector<string> v;
    SourceTokenizer::extractExpression(p, v);
    REQUIRE(v[0] == "x + y");
    REQUIRE(v[1] == "z");
    REQUIRE(v[2] == "+");
}

TEST_CASE("expression token - nested brackets") {
    string p = "(x + y) + (a + b) + ((m*n) + (p*q))";
    vector<string> v;
    SourceTokenizer::extractExpression(p, v);
    REQUIRE(v[0] == "(x + y) + (a + b)");
    REQUIRE(v[1] == "((m*n) + (p*q))");
    REQUIRE(v[2] == "+");
}

TEST_CASE("fail test") {
    string p = "x+y";
    vector<string> v;
    SourceTokenizer::extractExpression(p, v);
    REQUIRE(v[0] == "x");
    REQUIRE(v[1] == "y");
    REQUIRE(v[2] != "*");
}

TEST_CASE("partition assign") {
    string stmtLst = "x = x + 1;";
    vector<string> arr = SourceTokenizer::partitionAccordingToCase(stmtLst, ASSIGN);
    CHECK(arr[0] == "x = x + 1;");
    CHECK(arr[1] == "");

    stmtLst = "read x;read y;";
    arr = SourceTokenizer::partitionAccordingToCase(stmtLst, READ);
    CHECK(arr[0] == "read x;");
    CHECK(arr[1] == "read y;");

    stmtLst = "x = x + 1;\nread y;";
    arr = SourceTokenizer::partitionAccordingToCase(stmtLst, ASSIGN);
    CHECK(arr[0] == "x = x + 1;");
    CHECK(arr[1] == "read y;");
}


TEST_CASE("partition if-else and while") {
    string whileStatement = "while(x < present) {\n     read = print;\n}";
    vector<string> arr = SourceTokenizer::partitionAccordingToCase(whileStatement, WHILE);
    CHECK(arr[0] == "while(x < present){\n     read = print;\n}");
    whileStatement = "while(x < present) {\n     read = print;\n} read print;print x;";
    arr = SourceTokenizer::partitionAccordingToCase(whileStatement, WHILE);
    CHECK(arr[1] == "read print;print x;");
    string ifStmt = "if( x < present ) then   {\n print;\n}else {\nread x;}print y;";
    arr = SourceTokenizer::partitionAccordingToCase(ifStmt, IF_ELSE);
    CHECK(arr[0] == "if( x < present )then{\n print;\n}else{\nread x;}");
    CHECK(arr[1] == " print y;");

}
