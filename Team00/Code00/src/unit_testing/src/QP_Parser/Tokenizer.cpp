#include "catch.hpp"
#include "QP_Parser/Tokenizer.h"
#include <vector>
#include <string>
#include <iostream>

using namespace qp;

TEST_CASE ("DECLARATIONS") {
    std::string firstQuery = "variable v; assign a;\nSelect v";
    Tokenizer tokenizer = Tokenizer();
    QueryToken queryToken = QueryToken();
    tokenizer.getDeclarationTokens(firstQuery, queryToken);
    std::cout << queryToken.declarationTokens[0][0];
    CHECK(queryToken.declarationTokens[0][0] == "variable v");
    std::cout << "\n";
    std::cout << queryToken.declarationTokens[0][1];
    CHECK(queryToken.declarationTokens[0][1] == "assign a");
}

TEST_CASE ("SELECT CLAUSE") {
    std::string first = "variable v; assign a;\nSelect v";
    std::string second = "variable v; assign a;\nSelect a such that Uses(a,v)";
    Tokenizer tokenizer = Tokenizer();
    QueryToken queryToken = QueryToken();
    tokenizer.getSelectClauseTokens(first, queryToken);
    CHECK(queryToken.selectClauseToken == "v");
    tokenizer.getSelectClauseTokens(second, queryToken);
    CHECK(queryToken.selectClauseToken == "a");

}

TEST_CASE("SUCH THAT CLAUSE") {
    std::string second = "variable v; assign a;\nSelect a such that Uses(a,v) pattern a(_,_)";
    Tokenizer tokenizer = Tokenizer();
    QueryToken queryToken = QueryToken();
    tokenizer.getSuchThatClause(second, queryToken);
}

TEST_CASE("PATTERN CLAUSE") {
    std::string second = "variable v; assign a;\nSelect a such that pattern a(v,\"x\")";
    Tokenizer tokenizer = Tokenizer();
    QueryToken queryToken = QueryToken();
    tokenizer.getPatternClause(second, queryToken);
}
