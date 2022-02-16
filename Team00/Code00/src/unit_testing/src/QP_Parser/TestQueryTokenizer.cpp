#include "catch.hpp"
#include "QP_Parser/Tokenizer.h"
#include "pql/query_obj/Argument.h"
#include <vector>
#include <string>
#include <iostream>

using namespace qp;

TEST_CASE ("DECLARATIONS") {
    std::string firstQuery = "variable v1, v2; assign a;\nSelect v";
    Tokenizer tokenizer = Tokenizer();
    QueryToken queryToken = QueryToken();
//    tokenizer.getDeclarationTokens(firstQuery, queryToken);
//    std::cout << queryToken.declarationTokens[0][0];
//    CHECK(queryToken.declarationTokens[0][0] == "variable v1, v2");
//    std::cout << "\n";
//    std::cout << queryToken.declarationTokens[0][1];
//    CHECK(queryToken.declarationTokens[0][1] == "assign a");
}

TEST_CASE("PATTERN CLAUSE") {
    std::string second = "variable v; assign a;\nSelect a such that pattern a (    v , \"x\"      )";
    Tokenizer tokenizer = Tokenizer();
    QueryToken queryToken = QueryToken();
    QueryToken token = tokenizer.getQueryToken(second);
}