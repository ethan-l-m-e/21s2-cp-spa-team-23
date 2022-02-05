#include "catch.hpp"
#include "QP_Parser/Tokenizer.h"
#include <vector>
#include <string>
#include <iostream>

using namespace qp;

std::vector<std::string> queries;
std::string firstQuery = "variable v;\nSelect v";

TEST_CASE ("DECLARATIONS") {
    queries.push_back(firstQuery);
    Tokenizer tokenizer = Tokenizer();
    QueryToken queryToken = QueryToken();
    tokenizer.getDeclarationTokens(firstQuery, queryToken);
    std::vector<std::string> expected_declarations;
    std::cout << queryToken.declarationTokens[0][0];
    CHECK(queryToken.declarationTokens[0][0] == "variable v");
}