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
    std::string firstQuery = "variable v; assign a;\nSelect v";
    Tokenizer tokenizer = Tokenizer();
    QueryToken queryToken = QueryToken();
    tokenizer.getSelectClauseTokens(firstQuery, queryToken);
    std::cout << queryToken.selectClauseToken;
    CHECK(queryToken.selectClauseToken == "v");
}
