#include "catch.hpp"
#include "QP_Parser/Validator.h"

#include <vector>
#include <string>
#include <map>
#include <utility>
#include <iostream>

using namespace qp;

TEST_CASE ("VALIDATION") {
    std::string firstQuery = "variable v1; \n assign a; Select v";
    Validator validator = Validator();

    REQUIRE_NOTHROW(validator.validateQueryStructure(firstQuery));
}

TEST_CASE ("VALIDATION2") {
    std::string firstQuery = "variable v; assign a;\nSelect a pattern a (    v , \"x\"      )";
    Validator validator = Validator();

    REQUIRE_NOTHROW(validator.validateQueryStructure(firstQuery));
}

TEST_CASE ("VALIDATION3") {
    std::string firstQuery = "variable v; assign a;\nSelect a pattern (    v , \"x\"      )";
    Validator validator = Validator();

    REQUIRE_THROWS(validator.validateQueryStructure(firstQuery));
}

TEST_CASE ("VALIDATION SEMANTIC1") {
    auto declarationTokens = new std::map<std::string, std::string> ({{"v", "variable"}});
    auto declarationNames = std::vector<std::string>({"v"});
    auto designEntities = std::vector<std::string>({"variable"});
    auto declarations = std::make_pair(declarationNames, designEntities);

    QueryToken queryToken = QueryToken();
    queryToken.declarations = &declarations;
    queryToken.declarationTokens = declarationTokens;
    queryToken.selectClauseToken = "v";

    Validator validator = Validator();
    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));
}

TEST_CASE ("VALIDATION SEMANTIC2") {
    auto declarationTokens = new std::map<std::string, std::string> ({{"v", "variable"}});
    auto declarationNames = std::vector<std::string>({"v"});
    auto designEntities = std::vector<std::string>({"variable"});
    auto declarations = std::make_pair(declarationNames, designEntities);
    SuchThatClauseToken suchThatClauseToken = SuchThatClauseToken("Follows*",
                                                                  new std::pair<std::string, std::string>("1", "2"));
    auto suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});

    QueryToken queryToken = QueryToken();
    queryToken.declarations = &declarations;
    queryToken.declarationTokens = declarationTokens;
    queryToken.selectClauseToken = "v";
    queryToken.suchThatClauseTokens = suchThatClauseTokens;

    Validator validator = Validator();
    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));
}
