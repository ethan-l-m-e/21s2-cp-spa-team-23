#include "catch.hpp"
#include "QP_Parser/Validator.h"
#include <vector>
#include <string>
#include <iostream>

using namespace qp;

TEST_CASE ("VALIDATION") {
    std::string firstQuery = "variable v1; assign a;\nSelect v";
    Validator validator = Validator();
    validator.validateQueryStructure(firstQuery);
//    tokenizer.getDeclarationTokens(firstQuery, queryToken);
//    std::cout << queryToken.declarationTokens[0][0];
//    CHECK(queryToken.declarationTokens[0][0] == "variable v1, v2");
//    std::cout << "\n";
//    std::cout << queryToken.declarationTokens[0][1];
//    CHECK(queryToken.declarationTokens[0][1] == "assign a");
}
