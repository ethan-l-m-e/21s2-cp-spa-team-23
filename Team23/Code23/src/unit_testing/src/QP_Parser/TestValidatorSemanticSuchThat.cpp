#include "catch.hpp"
#include "QP_Parser/Validator.h"

#include <utility>

using namespace qp;

void setUp(QueryToken& queryToken) {
    auto declarationTokens = new std::map<std::string, std::string>({
                                                                            {"s",   "stmt"},
                                                                            {"r",   "read"},
                                                                            {"pn",  "print"},
                                                                            {"a",   "assign"},
                                                                            {"c",   "call"},
                                                                            {"w",   "while"},
                                                                            {"ifs", "if"},
                                                                            {"v",   "variable"},
                                                                            {"con", "constant"},
                                                                            {"p",   "procedure"}});
    auto declarationNames = std::vector<std::string>({"s", "r", "pn", "a", "c", "w", "ifs", "v", "con", "p"});
    auto designEntities = std::vector<std::string>({"stmt", "read", "assign", "call", "while", "if", "variable",
                                                    "constant", "procedure"});
    auto declarations = new std::pair(declarationNames, designEntities);

    queryToken.declarations = declarations;
    queryToken.declarationTokens = declarationTokens;
    queryToken.selectClauseTokens = new std::vector<std::string>({"s"});
    queryToken.patternTokens = new std::vector<PatternToken>();
    queryToken.withClauses = new std::vector<std::pair<std::string, std::string>>();
}

// Check validity for such that clause tokens
TEST_CASE ("QP SEMANTIC VALIDATOR: FOLLOWS CLAUSE CHECK ARGUMENTS") {
    Validator validator = Validator();
    QueryToken queryToken = QueryToken();
    setUp(queryToken);

    // Integer as first argument
    SuchThatClauseToken suchThatClauseToken = SuchThatClauseToken();
    std::vector<std::string>* arguments = new std::vector<std::string>({"3", "2"});
    suchThatClauseToken.relRef = "Follows";
    suchThatClauseToken.arguments = arguments;
    std::vector<SuchThatClauseToken>* suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;

    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // Wildcard as first argument
    arguments = new std::vector<std::string>({"_", "2"});
    suchThatClauseToken.relRef = "Follows";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;

    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // stmt synonym as first argument
    arguments = new std::vector<std::string>({"s", "2"});
    suchThatClauseToken.relRef = "Follows";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;

    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // read synonym as first argument
    arguments = new std::vector<std::string>({"r", "2"});
    suchThatClauseToken.relRef = "Follows";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;

    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // print synonym as first argument
    arguments = new std::vector<std::string>({"pn", "2"});
    suchThatClauseToken.relRef = "Follows";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;

    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // assign synonym as first argument
    arguments = new std::vector<std::string>({"a", "2"});
    suchThatClauseToken.relRef = "Follows";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;

    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // call synonym as first argument
    arguments = new std::vector<std::string>({"c", "2"});
    suchThatClauseToken.relRef = "Follows";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;

    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // while synonym as first argument
    arguments = new std::vector<std::string>({"w", "2"});
    suchThatClauseToken.relRef = "Follows";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;

    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // ifs synonym as first argument
    arguments = new std::vector<std::string>({"ifs", "2"});
    suchThatClauseToken.relRef = "Follows";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;

    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // variable synonym as first argument
    arguments = new std::vector<std::string>({"v", "2"});
    suchThatClauseToken.relRef = "Follows";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;

    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    // constant synonym as first argument
    arguments = new std::vector<std::string>({"con", "2"});
    suchThatClauseToken.relRef = "Follows";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;

    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    // procedure synonym as first argument
    arguments = new std::vector<std::string>({"p", "2"});
    suchThatClauseToken.relRef = "Follows";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;

    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    // Ident as first argument
    arguments = new std::vector<std::string>({"\"x\"", "2"});
    suchThatClauseToken.relRef = "Follows";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;

    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    // Integer as second argument
    arguments = new std::vector<std::string>({"3", "2"});
    suchThatClauseToken.relRef = "Follows";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;

    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // Wildcard as second argument
    arguments = new std::vector<std::string>({"3", "_"});
    suchThatClauseToken.relRef = "Follows";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;

    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // stmt synonym as second argument
    arguments = new std::vector<std::string>({"3", "s"});
    suchThatClauseToken.relRef = "Follows";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;

    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // read synonym as second argument
    arguments = new std::vector<std::string>({"3", "r"});
    suchThatClauseToken.relRef = "Follows";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;

    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // print synonym as second argument
    arguments = new std::vector<std::string>({"3", "pn"});
    suchThatClauseToken.relRef = "Follows";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;

    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // assign synonym as second argument
    arguments = new std::vector<std::string>({"3", "a"});
    suchThatClauseToken.relRef = "Follows";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;

    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // call synonym as second argument
    arguments = new std::vector<std::string>({"3", "c"});
    suchThatClauseToken.relRef = "Follows";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;

    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // while synonym as second argument
    arguments = new std::vector<std::string>({"3", "w"});
    suchThatClauseToken.relRef = "Follows";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;

    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // while synonym as second argument
    arguments = new std::vector<std::string>({"3", "ifs"});
    suchThatClauseToken.relRef = "Follows";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;

    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // variable synonym as second argument
    arguments = new std::vector<std::string>({"3", "v"});
    suchThatClauseToken.relRef = "Follows";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;

    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    // constant synonym as second argument
    arguments = new std::vector<std::string>({"3", "con"});
    suchThatClauseToken.relRef = "Follows";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;

    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    // procedure synonym as second argument
    arguments = new std::vector<std::string>({"3", "p"});
    suchThatClauseToken.relRef = "Follows";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;

    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    // ident as second argument
    arguments = new std::vector<std::string>({"3", "\"x\""});
    suchThatClauseToken.relRef = "Follows";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;

    REQUIRE_THROWS(validator.checkForSemantics(queryToken));
}

TEST_CASE ("QP SEMANTIC VALIDATOR: FOLLOWS* CLAUSE CHECK ARGUMENTS") {
    Validator validator = Validator();
    QueryToken queryToken = QueryToken();
    setUp(queryToken);

    // Integer as first argument
    SuchThatClauseToken suchThatClauseToken = SuchThatClauseToken();
    std::vector<std::string>* arguments = new std::vector<std::string>({"3", "2"});
    suchThatClauseToken.relRef = "Follows*";
    suchThatClauseToken.arguments = arguments;
    std::vector<SuchThatClauseToken>* suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;

    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // Wildcard as first argument
    arguments = new std::vector<std::string>({"_", "2"});
    suchThatClauseToken.relRef = "Follows*";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;

    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // stmt synonym as first argument
    arguments = new std::vector<std::string>({"s", "2"});
    suchThatClauseToken.relRef = "Follows*";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;

    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // read synonym as first argument
    arguments = new std::vector<std::string>({"r", "2"});
    suchThatClauseToken.relRef = "Follows*";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;

    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // print synonym as first argument
    arguments = new std::vector<std::string>({"pn", "2"});
    suchThatClauseToken.relRef = "Follows*";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;

    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // assign synonym as first argument
    arguments = new std::vector<std::string>({"a", "2"});
    suchThatClauseToken.relRef = "Follows*";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;

    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // call synonym as first argument
    arguments = new std::vector<std::string>({"c", "2"});
    suchThatClauseToken.relRef = "Follows*";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;

    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // while synonym as first argument
    arguments = new std::vector<std::string>({"w", "2"});
    suchThatClauseToken.relRef = "Follows*";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;

    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // while synonym as first argument
    arguments = new std::vector<std::string>({"ifs", "2"});
    suchThatClauseToken.relRef = "Follows*";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;

    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // variable synonym as first argument
    arguments = new std::vector<std::string>({"v", "2"});
    suchThatClauseToken.relRef = "Follows*";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;

    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    // constant synonym as first argument
    arguments = new std::vector<std::string>({"con", "2"});
    suchThatClauseToken.relRef = "Follows*";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;

    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    // procedure synonym as first argument
    arguments = new std::vector<std::string>({"p", "2"});
    suchThatClauseToken.relRef = "Follows*";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;

    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    // ident as first argument
    arguments = new std::vector<std::string>({"\"x\"", "2"});
    suchThatClauseToken.relRef = "Follows*";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;

    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    // Integer as second argument
    arguments = new std::vector<std::string>({"3", "2"});
    suchThatClauseToken.relRef = "Follows*";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;

    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // Wildcard as second argument
    arguments = new std::vector<std::string>({"3", "_"});
    suchThatClauseToken.relRef = "Follows*";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;

    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // stmt synonym as second argument
    arguments = new std::vector<std::string>({"3", "s"});
    suchThatClauseToken.relRef = "Follows*";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;

    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // read synonym as second argument
    arguments = new std::vector<std::string>({"3", "r"});
    suchThatClauseToken.relRef = "Follows*";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;

    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // print synonym as second argument
    arguments = new std::vector<std::string>({"3", "pn"});
    suchThatClauseToken.relRef = "Follows*";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;

    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // assign synonym as second argument
    arguments = new std::vector<std::string>({"3", "a"});
    suchThatClauseToken.relRef = "Follows*";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;

    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // call synonym as second argument
    arguments = new std::vector<std::string>({"3", "c"});
    suchThatClauseToken.relRef = "Follows*";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;

    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // while synonym as second argument
    arguments = new std::vector<std::string>({"3", "w"});
    suchThatClauseToken.relRef = "Follows*";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;

    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // while synonym as second argument
    arguments = new std::vector<std::string>({"3", "ifs"});
    suchThatClauseToken.relRef = "Follows*";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;

    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // variable synonym as second argument
    arguments = new std::vector<std::string>({"3", "v"});
    suchThatClauseToken.relRef = "Follows*";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;

    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    // constant synonym as second argument
    arguments = new std::vector<std::string>({"3", "con"});
    suchThatClauseToken.relRef = "Follows*";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;

    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    // procedure synonym as second argument
    arguments = new std::vector<std::string>({"3", "p"});
    suchThatClauseToken.relRef = "Follows*";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;

    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    // ident as second argument
    arguments = new std::vector<std::string>({"3", "\"x\""});
    suchThatClauseToken.relRef = "Follows*";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;

    REQUIRE_THROWS(validator.checkForSemantics(queryToken));
}

TEST_CASE ("QP SEMANTIC VALIDATOR: PARENT CLAUSE CHECK ARGUMENTS") {
    Validator validator = Validator();
    QueryToken queryToken = QueryToken();
    setUp(queryToken);

    // Integer as first argument
    SuchThatClauseToken suchThatClauseToken = SuchThatClauseToken();
    std::vector<std::string>* arguments = new std::vector<std::string>({"3", "2"});
    suchThatClauseToken.relRef = "Parent";
    suchThatClauseToken.arguments = arguments;
    std::vector<SuchThatClauseToken>* suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;

    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // Wildcard as first argument
    arguments = new std::vector<std::string>({"_", "2"});
    suchThatClauseToken.relRef = "Parent";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;

    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // stmt synonym as first argument
    arguments = new std::vector<std::string>({"s", "2"});
    suchThatClauseToken.relRef = "Parent";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;

    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // read synonym as first argument
    arguments = new std::vector<std::string>({"r", "2"});
    suchThatClauseToken.relRef = "Parent";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;

    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // print synonym as first argument
    arguments = new std::vector<std::string>({"pn", "2"});
    suchThatClauseToken.relRef = "Parent";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;

    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // assign synonym as first argument
    arguments = new std::vector<std::string>({"a", "2"});
    suchThatClauseToken.relRef = "Parent";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;

    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // call synonym as first argument
    arguments = new std::vector<std::string>({"c", "2"});
    suchThatClauseToken.relRef = "Parent";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;

    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // while synonym as first argument
    arguments = new std::vector<std::string>({"w", "2"});
    suchThatClauseToken.relRef = "Parent";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;

    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // while synonym as first argument
    arguments = new std::vector<std::string>({"ifs", "2"});
    suchThatClauseToken.relRef = "Parent";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;

    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // variable synonym as first argument
    arguments = new std::vector<std::string>({"v", "2"});
    suchThatClauseToken.relRef = "Parent";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;

    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    // constant synonym as first argument
    arguments = new std::vector<std::string>({"con", "2"});
    suchThatClauseToken.relRef = "Parent";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;

    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    // procedure synonym as first argument
    arguments = new std::vector<std::string>({"p", "2"});
    suchThatClauseToken.relRef = "Parent";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;

    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    // ident as first argument
    arguments = new std::vector<std::string>({"\"x\"", "2"});
    suchThatClauseToken.relRef = "Parent";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;

    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    // Integer as second argument
    arguments = new std::vector<std::string>({"3", "2"});
    suchThatClauseToken.relRef = "Parent";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;

    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // Wildcard as second argument
    arguments = new std::vector<std::string>({"3", "_"});
    suchThatClauseToken.relRef = "Parent";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;

    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // stmt synonym as second argument
    arguments = new std::vector<std::string>({"3", "s"});
    suchThatClauseToken.relRef = "Parent";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;

    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // read synonym as second argument
    arguments = new std::vector<std::string>({"3", "r"});
    suchThatClauseToken.relRef = "Parent";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;

    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // print synonym as second argument
    arguments = new std::vector<std::string>({"3", "pn"});
    suchThatClauseToken.relRef = "Parent";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;

    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // assign synonym as second argument
    arguments = new std::vector<std::string>({"3", "a"});
    suchThatClauseToken.relRef = "Parent";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;

    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // call synonym as second argument
    arguments = new std::vector<std::string>({"3", "c"});
    suchThatClauseToken.relRef = "Parent";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;

    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // while synonym as second argument
    arguments = new std::vector<std::string>({"3", "w"});
    suchThatClauseToken.relRef = "Parent";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;

    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // while synonym as second argument
    arguments = new std::vector<std::string>({"3", "ifs"});
    suchThatClauseToken.relRef = "Parent";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;

    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // variable synonym as second argument
    arguments = new std::vector<std::string>({"3", "v"});
    suchThatClauseToken.relRef = "Parent";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;

    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    // constant synonym as second argument
    arguments = new std::vector<std::string>({"3", "con"});
    suchThatClauseToken.relRef = "Parent";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;

    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    // procedure synonym as second argument
    arguments = new std::vector<std::string>({"3", "p"});
    suchThatClauseToken.relRef = "Parent";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;

    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    // ident as second argument
    arguments = new std::vector<std::string>({"3", "\"x\""});
    suchThatClauseToken.relRef = "Parent";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;

    REQUIRE_THROWS(validator.checkForSemantics(queryToken));
}

TEST_CASE ("QP SEMANTIC VALIDATOR: PARENT* CLAUSE CHECK ARGUMENTS") {
    Validator validator = Validator();
    QueryToken queryToken = QueryToken();
    setUp(queryToken);

    // Integer as first argument
    SuchThatClauseToken suchThatClauseToken = SuchThatClauseToken();
    std::vector<std::string>* arguments = new std::vector<std::string>({"3", "2"});
    suchThatClauseToken.relRef = "Parent*";
    suchThatClauseToken.arguments = arguments;
    std::vector<SuchThatClauseToken>* suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;

    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // Wildcard as first argument
    arguments = new std::vector<std::string>({"_", "2"});
    suchThatClauseToken.relRef = "Parent*";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;

    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // stmt synonym as first argument
    arguments = new std::vector<std::string>({"s", "2"});
    suchThatClauseToken.relRef = "Parent*";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;

    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // read synonym as first argument
    arguments = new std::vector<std::string>({"r", "2"});
    suchThatClauseToken.relRef = "Parent*";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;

    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // print synonym as first argument
    arguments = new std::vector<std::string>({"pn", "2"});
    suchThatClauseToken.relRef = "Parent*";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;

    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // assign synonym as first argument
    arguments = new std::vector<std::string>({"a", "2"});
    suchThatClauseToken.relRef = "Parent*";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;

    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // call synonym as first argument
    arguments = new std::vector<std::string>({"c", "2"});
    suchThatClauseToken.relRef = "Parent*";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;

    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // while synonym as first argument
    arguments = new std::vector<std::string>({"w", "2"});
    suchThatClauseToken.relRef = "Parent*";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;

    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // while synonym as first argument
    arguments = new std::vector<std::string>({"ifs", "2"});
    suchThatClauseToken.relRef = "Parent*";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;

    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // variable synonym as first argument
    arguments = new std::vector<std::string>({"v", "2"});
    suchThatClauseToken.relRef = "Parent*";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;

    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    // constant synonym as first argument
    arguments = new std::vector<std::string>({"con", "2"});
    suchThatClauseToken.relRef = "Parent*";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;

    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    // procedure synonym as first argument
    arguments = new std::vector<std::string>({"p", "2"});
    suchThatClauseToken.relRef = "Parent*";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;

    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    // ident as first argument
    arguments = new std::vector<std::string>({"\"x\"", "2"});
    suchThatClauseToken.relRef = "Parent*";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;

    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    // Integer as second argument
    arguments = new std::vector<std::string>({"3", "2"});
    suchThatClauseToken.relRef = "Parent*";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;

    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // Wildcard as second argument
    arguments = new std::vector<std::string>({"3", "_"});
    suchThatClauseToken.relRef = "Parent*";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;

    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // stmt synonym as second argument
    arguments = new std::vector<std::string>({"3", "s"});
    suchThatClauseToken.relRef = "Parent*";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;

    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // read synonym as second argument
    arguments = new std::vector<std::string>({"3", "r"});
    suchThatClauseToken.relRef = "Parent*";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;

    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // print synonym as second argument
    arguments = new std::vector<std::string>({"3", "pn"});
    suchThatClauseToken.relRef = "Parent*";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;

    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // assign synonym as second argument
    arguments = new std::vector<std::string>({"3", "a"});
    suchThatClauseToken.relRef = "Parent*";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;

    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // call synonym as second argument
    arguments = new std::vector<std::string>({"3", "c"});
    suchThatClauseToken.relRef = "Parent*";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;

    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // while synonym as second argument
    arguments = new std::vector<std::string>({"3", "w"});
    suchThatClauseToken.relRef = "Parent*";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;

    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // while synonym as second argument
    arguments = new std::vector<std::string>({"3", "ifs"});
    suchThatClauseToken.relRef = "Parent*";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;

    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // variable synonym as second argument
    arguments = new std::vector<std::string>({"3", "v"});
    suchThatClauseToken.relRef = "Parent*";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;

    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    // constant synonym as second argument
    arguments = new std::vector<std::string>({"3", "con"});
    suchThatClauseToken.relRef = "Parent*";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;

    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    // procedure synonym as second argument
    arguments = new std::vector<std::string>({"3", "p"});
    suchThatClauseToken.relRef = "Parent*";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;

    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    // ident as second argument
    arguments = new std::vector<std::string>({"3", "\"x\""});
    suchThatClauseToken.relRef = "Parent*";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;

    REQUIRE_THROWS(validator.checkForSemantics(queryToken));
}

TEST_CASE ("QP SEMANTIC VALIDATOR: USES CLAUSE CHECK ARGUMENTS") {
    Validator validator = Validator();
    QueryToken queryToken = QueryToken();
    setUp(queryToken);

    // IDENT as first argument
    SuchThatClauseToken suchThatClauseToken = SuchThatClauseToken();
    std::vector<std::string>* arguments = new std::vector<std::string>({"\"x\"", "_"});
    suchThatClauseToken.relRef = "Uses";
    suchThatClauseToken.arguments = arguments;
    std::vector<SuchThatClauseToken>* suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;
    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // assign synonym as first argument
    arguments = new std::vector<std::string>({"a", "_"});
    suchThatClauseToken.relRef = "Uses";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;
    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // print synonym as first argument
    arguments = new std::vector<std::string>({"pn", "_"});
    suchThatClauseToken.relRef = "Uses";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;
    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // if synonym as first argument
    arguments = new std::vector<std::string>({"ifs", "_"});
    suchThatClauseToken.relRef = "Uses";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;
    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // while synonym as first argument
    arguments = new std::vector<std::string>({"w", "_"});
    suchThatClauseToken.relRef = "Uses";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;
    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // procedure synonym as first argument
    arguments = new std::vector<std::string>({"p", "_"});
    suchThatClauseToken.relRef = "Uses";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;
    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // call synonym as first argument
    arguments = new std::vector<std::string>({"c", "_"});
    suchThatClauseToken.relRef = "Uses";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;
    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // stmt synonym as first argument
    arguments = new std::vector<std::string>({"s", "_"});
    suchThatClauseToken.relRef = "Uses";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;
    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // read synonym as first argument
    arguments = new std::vector<std::string>({"r", "_"});
    suchThatClauseToken.relRef = "Uses";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;
    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    // variable synonym as first argument
    arguments = new std::vector<std::string>({"v", "_"});
    suchThatClauseToken.relRef = "Uses";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;
    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    // constant synonym as first argument
    arguments = new std::vector<std::string>({"con", "_"});
    suchThatClauseToken.relRef = "Uses";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;
    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    // wildcard as first argument
    arguments = new std::vector<std::string>({"_", "_"});
    suchThatClauseToken.relRef = "Uses";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;
    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    // variable synonym as second argument
    arguments = new std::vector<std::string>({"a", "v"});
    suchThatClauseToken.relRef = "Uses";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;
    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // ident as second argument
    arguments = new std::vector<std::string>({"a", "\"x\""});
    suchThatClauseToken.relRef = "Uses";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;
    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // wildcard as second argument
    arguments = new std::vector<std::string>({"a", "_"});
    suchThatClauseToken.relRef = "Uses";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;
    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // assign synonym as second argument
    arguments = new std::vector<std::string>({"a", "a"});
    suchThatClauseToken.relRef = "Uses";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;
    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    // print synonym as second argument
    arguments = new std::vector<std::string>({"a", "pn"});
    suchThatClauseToken.relRef = "Uses";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;
    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    // if synonym as second argument
    arguments = new std::vector<std::string>({"a", "ifs"});
    suchThatClauseToken.relRef = "Uses";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;
    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    // while synonym as second argument
    arguments = new std::vector<std::string>({"a", "w"});
    suchThatClauseToken.relRef = "Uses";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;
    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    // procedure synonym as second argument
    arguments = new std::vector<std::string>({"a", "p"});
    suchThatClauseToken.relRef = "Uses";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;
    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    // call synonym as second argument
    arguments = new std::vector<std::string>({"a", "c"});
    suchThatClauseToken.relRef = "Uses";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;
    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    // stmt synonym as second argument
    arguments = new std::vector<std::string>({"a", "s"});
    suchThatClauseToken.relRef = "Uses";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;
    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    // read synonym as second argument
    arguments = new std::vector<std::string>({"a", "r"});
    suchThatClauseToken.relRef = "Uses";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;
    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    // constant synonym as second argument
    arguments = new std::vector<std::string>({"a", "con"});
    suchThatClauseToken.relRef = "Uses";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;
    REQUIRE_THROWS(validator.checkForSemantics(queryToken));
}

TEST_CASE ("QP SEMANTIC VALIDATOR: MODIFIES CLAUSE CHECK ARGUMENTS") {
    Validator validator = Validator();
    QueryToken queryToken = QueryToken();
    setUp(queryToken);

    // IDENT as first argument
    SuchThatClauseToken suchThatClauseToken = SuchThatClauseToken();
    std::vector<std::string>* arguments = new std::vector<std::string>({"\"x\"", "_"});
    suchThatClauseToken.relRef = "Modifies";
    suchThatClauseToken.arguments = arguments;
    std::vector<SuchThatClauseToken>* suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;
    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // assign synonym as first argument
    arguments = new std::vector<std::string>({"a", "_"});
    suchThatClauseToken.relRef = "Modifies";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;
    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // read synonym as first argument
    arguments = new std::vector<std::string>({"r", "_"});
    suchThatClauseToken.relRef = "Modifies";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;
    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // if synonym as first argument
    arguments = new std::vector<std::string>({"ifs", "_"});
    suchThatClauseToken.relRef = "Modifies";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;
    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // while synonym as first argument
    arguments = new std::vector<std::string>({"w", "_"});
    suchThatClauseToken.relRef = "Modifies";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;
    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // procedure synonym as first argument
    arguments = new std::vector<std::string>({"p", "_"});
    suchThatClauseToken.relRef = "Modifies";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;
    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // call synonym as first argument
    arguments = new std::vector<std::string>({"c", "_"});
    suchThatClauseToken.relRef = "Modifies";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;
    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // stmt synonym as first argument
    arguments = new std::vector<std::string>({"s", "_"});
    suchThatClauseToken.relRef = "Modifies";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;
    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // print synonym as first argument
    arguments = new std::vector<std::string>({"pn", "_"});
    suchThatClauseToken.relRef = "Modifies";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;
    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    // variable synonym as first argument
    arguments = new std::vector<std::string>({"v", "_"});
    suchThatClauseToken.relRef = "Modifies";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;
    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    // constant synonym as first argument
    arguments = new std::vector<std::string>({"con", "_"});
    suchThatClauseToken.relRef = "Modifies";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;
    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    // wildcard as first argument
    arguments = new std::vector<std::string>({"_", "_"});
    suchThatClauseToken.relRef = "Modifies";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;
    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    // variable synonym as second argument
    arguments = new std::vector<std::string>({"a", "v"});
    suchThatClauseToken.relRef = "Modifies";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;
    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // ident as second argument
    arguments = new std::vector<std::string>({"a", "\"x\""});
    suchThatClauseToken.relRef = "Modifies";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;
    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // wildcard as second argument
    arguments = new std::vector<std::string>({"a", "_"});
    suchThatClauseToken.relRef = "Modifies";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;
    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // assign synonym as second argument
    arguments = new std::vector<std::string>({"a", "a"});
    suchThatClauseToken.relRef = "Modifies";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;
    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    // print synonym as second argument
    arguments = new std::vector<std::string>({"a", "pn"});
    suchThatClauseToken.relRef = "Modifies";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;
    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    // if synonym as second argument
    arguments = new std::vector<std::string>({"a", "ifs"});
    suchThatClauseToken.relRef = "Modifies";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;
    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    // while synonym as second argument
    arguments = new std::vector<std::string>({"a", "w"});
    suchThatClauseToken.relRef = "Modifies";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;
    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    // procedure synonym as second argument
    arguments = new std::vector<std::string>({"a", "p"});
    suchThatClauseToken.relRef = "Modifies";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;
    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    // call synonym as second argument
    arguments = new std::vector<std::string>({"a", "c"});
    suchThatClauseToken.relRef = "Modifies";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;
    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    // stmt synonym as second argument
    arguments = new std::vector<std::string>({"a", "s"});
    suchThatClauseToken.relRef = "Modifies";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;
    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    // read synonym as second argument
    arguments = new std::vector<std::string>({"a", "r"});
    suchThatClauseToken.relRef = "Modifies";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;
    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    // constant synonym as second argument
    arguments = new std::vector<std::string>({"a", "con"});
    suchThatClauseToken.relRef = "Modifies";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;
    REQUIRE_THROWS(validator.checkForSemantics(queryToken));
}

TEST_CASE ("QP SEMANTIC VALIDATOR: NEXT CLAUSE CHECK ARGUMENTS") {
    Validator validator = Validator();
    QueryToken queryToken = QueryToken();
    setUp(queryToken);

    // Integer as first argument
    SuchThatClauseToken suchThatClauseToken = SuchThatClauseToken();
    std::vector<std::string>* arguments = new std::vector<std::string>({"3", "2"});
    suchThatClauseToken.relRef = "Next";
    suchThatClauseToken.arguments = arguments;
    std::vector<SuchThatClauseToken>* suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;

    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // Wildcard as first argument
    arguments = new std::vector<std::string>({"_", "2"});
    suchThatClauseToken.relRef = "Next";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;

    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // stmt synonym as first argument
    arguments = new std::vector<std::string>({"s", "2"});
    suchThatClauseToken.relRef = "Next";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;

    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // read synonym as first argument
    arguments = new std::vector<std::string>({"r", "2"});
    suchThatClauseToken.relRef = "Next";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;

    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // print synonym as first argument
    arguments = new std::vector<std::string>({"pn", "2"});
    suchThatClauseToken.relRef = "Next";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;

    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // assign synonym as first argument
    arguments = new std::vector<std::string>({"a", "2"});
    suchThatClauseToken.relRef = "Next";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;

    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // call synonym as first argument
    arguments = new std::vector<std::string>({"c", "2"});
    suchThatClauseToken.relRef = "Next";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;

    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // while synonym as first argument
    arguments = new std::vector<std::string>({"w", "2"});
    suchThatClauseToken.relRef = "Next";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;

    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // while synonym as first argument
    arguments = new std::vector<std::string>({"ifs", "2"});
    suchThatClauseToken.relRef = "Next";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;

    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // variable synonym as first argument
    arguments = new std::vector<std::string>({"v", "2"});
    suchThatClauseToken.relRef = "Next";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;

    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    // constant synonym as first argument
    arguments = new std::vector<std::string>({"con", "2"});
    suchThatClauseToken.relRef = "Next";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;

    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    // procedure synonym as first argument
    arguments = new std::vector<std::string>({"p", "2"});
    suchThatClauseToken.relRef = "Next";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;

    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    // ident as first argument
    arguments = new std::vector<std::string>({"\"x\"", "2"});
    suchThatClauseToken.relRef = "Next";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;

    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    // Integer as second argument
    arguments = new std::vector<std::string>({"3", "2"});
    suchThatClauseToken.relRef = "Next";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;

    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // Wildcard as second argument
    arguments = new std::vector<std::string>({"3", "_"});
    suchThatClauseToken.relRef = "Next";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;

    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // stmt synonym as second argument
    arguments = new std::vector<std::string>({"3", "s"});
    suchThatClauseToken.relRef = "Next";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;

    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // read synonym as second argument
    arguments = new std::vector<std::string>({"3", "r"});
    suchThatClauseToken.relRef = "Next";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;

    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // print synonym as second argument
    arguments = new std::vector<std::string>({"3", "pn"});
    suchThatClauseToken.relRef = "Next";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;

    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // assign synonym as second argument
    arguments = new std::vector<std::string>({"3", "a"});
    suchThatClauseToken.relRef = "Next";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;

    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // call synonym as second argument
    arguments = new std::vector<std::string>({"3", "c"});
    suchThatClauseToken.relRef = "Next";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;

    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // while synonym as second argument
    arguments = new std::vector<std::string>({"3", "w"});
    suchThatClauseToken.relRef = "Next";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;

    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // while synonym as second argument
    arguments = new std::vector<std::string>({"3", "ifs"});
    suchThatClauseToken.relRef = "Next";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;

    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // variable synonym as second argument
    arguments = new std::vector<std::string>({"3", "v"});
    suchThatClauseToken.relRef = "Next";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;

    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    // constant synonym as second argument
    arguments = new std::vector<std::string>({"3", "con"});
    suchThatClauseToken.relRef = "Next";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;

    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    // procedure synonym as second argument
    arguments = new std::vector<std::string>({"3", "p"});
    suchThatClauseToken.relRef = "Next";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;

    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    // ident as second argument
    arguments = new std::vector<std::string>({"3", "\"x\""});
    suchThatClauseToken.relRef = "Next";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;

    REQUIRE_THROWS(validator.checkForSemantics(queryToken));
}

TEST_CASE ("QP SEMANTIC VALIDATOR: NEXT* CLAUSE CHECK ARGUMENTS") {
    Validator validator = Validator();
    QueryToken queryToken = QueryToken();
    setUp(queryToken);

    // Integer as first argument
    SuchThatClauseToken suchThatClauseToken = SuchThatClauseToken();
    std::vector<std::string>* arguments = new std::vector<std::string>({"3", "2"});
    suchThatClauseToken.relRef = "Next*";
    suchThatClauseToken.arguments = arguments;
    std::vector<SuchThatClauseToken>* suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;

    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // Wildcard as first argument
    arguments = new std::vector<std::string>({"_", "2"});
    suchThatClauseToken.relRef = "Next*";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;

    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // stmt synonym as first argument
    arguments = new std::vector<std::string>({"s", "2"});
    suchThatClauseToken.relRef = "Next*";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;

    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // read synonym as first argument
    arguments = new std::vector<std::string>({"r", "2"});
    suchThatClauseToken.relRef = "Next*";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;

    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // print synonym as first argument
    arguments = new std::vector<std::string>({"pn", "2"});
    suchThatClauseToken.relRef = "Next*";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;

    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // assign synonym as first argument
    arguments = new std::vector<std::string>({"a", "2"});
    suchThatClauseToken.relRef = "Next*";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;

    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // call synonym as first argument
    arguments = new std::vector<std::string>({"c", "2"});
    suchThatClauseToken.relRef = "Next*";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;

    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // while synonym as first argument
    arguments = new std::vector<std::string>({"w", "2"});
    suchThatClauseToken.relRef = "Next*";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;

    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // while synonym as first argument
    arguments = new std::vector<std::string>({"ifs", "2"});
    suchThatClauseToken.relRef = "Next*";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;

    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // variable synonym as first argument
    arguments = new std::vector<std::string>({"v", "2"});
    suchThatClauseToken.relRef = "Next*";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;

    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    // constant synonym as first argument
    arguments = new std::vector<std::string>({"con", "2"});
    suchThatClauseToken.relRef = "Next*";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;

    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    // procedure synonym as first argument
    arguments = new std::vector<std::string>({"p", "2"});
    suchThatClauseToken.relRef = "Next*";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;

    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    // ident as first argument
    arguments = new std::vector<std::string>({"\"x\"", "2"});
    suchThatClauseToken.relRef = "Next*";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;

    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    // Integer as second argument
    arguments = new std::vector<std::string>({"3", "2"});
    suchThatClauseToken.relRef = "Next*";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;

    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // Wildcard as second argument
    arguments = new std::vector<std::string>({"3", "_"});
    suchThatClauseToken.relRef = "Next*";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;

    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // stmt synonym as second argument
    arguments = new std::vector<std::string>({"3", "s"});
    suchThatClauseToken.relRef = "Next*";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;

    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // read synonym as second argument
    arguments = new std::vector<std::string>({"3", "r"});
    suchThatClauseToken.relRef = "Next*";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;

    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // print synonym as second argument
    arguments = new std::vector<std::string>({"3", "pn"});
    suchThatClauseToken.relRef = "Next*";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;

    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // assign synonym as second argument
    arguments = new std::vector<std::string>({"3", "a"});
    suchThatClauseToken.relRef = "Next*";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;

    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // call synonym as second argument
    arguments = new std::vector<std::string>({"3", "c"});
    suchThatClauseToken.relRef = "Next*";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;

    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // while synonym as second argument
    arguments = new std::vector<std::string>({"3", "w"});
    suchThatClauseToken.relRef = "Next*";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;

    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // while synonym as second argument
    arguments = new std::vector<std::string>({"3", "ifs"});
    suchThatClauseToken.relRef = "Next*";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;

    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // variable synonym as second argument
    arguments = new std::vector<std::string>({"3", "v"});
    suchThatClauseToken.relRef = "Next*";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;

    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    // constant synonym as second argument
    arguments = new std::vector<std::string>({"3", "con"});
    suchThatClauseToken.relRef = "Next*";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;

    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    // procedure synonym as second argument
    arguments = new std::vector<std::string>({"3", "p"});
    suchThatClauseToken.relRef = "Next*";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;

    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    // ident as second argument
    arguments = new std::vector<std::string>({"3", "\"x\""});
    suchThatClauseToken.relRef = "Next*";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;

    REQUIRE_THROWS(validator.checkForSemantics(queryToken));
}

TEST_CASE ("QP SEMANTIC VALIDATOR: CALLS CLAUSE CHECK ARGUMENTS") {
    Validator validator = Validator();
    QueryToken queryToken = QueryToken();
    setUp(queryToken);

    // IDENT as first argument
    SuchThatClauseToken suchThatClauseToken = SuchThatClauseToken();
    std::vector<std::string>* arguments = new std::vector<std::string>({"\"x\"", "_"});
    suchThatClauseToken.relRef = "Calls";
    suchThatClauseToken.arguments = arguments;
    std::vector<SuchThatClauseToken>* suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;
    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // assign synonym as first argument
    arguments = new std::vector<std::string>({"a", "_"});
    suchThatClauseToken.relRef = "Calls";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;
    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    // read synonym as first argument
    arguments = new std::vector<std::string>({"r", "_"});
    suchThatClauseToken.relRef = "Calls";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;
    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    // if synonym as first argument
    arguments = new std::vector<std::string>({"ifs", "_"});
    suchThatClauseToken.relRef = "Calls";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;
    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    // while synonym as first argument
    arguments = new std::vector<std::string>({"w", "_"});
    suchThatClauseToken.relRef = "Calls";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;
    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    // procedure synonym as first argument
    arguments = new std::vector<std::string>({"p", "_"});
    suchThatClauseToken.relRef = "Calls";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;
    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // call synonym as first argument
    arguments = new std::vector<std::string>({"c", "_"});
    suchThatClauseToken.relRef = "Calls";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;
    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    // stmt synonym as first argument
    arguments = new std::vector<std::string>({"s", "_"});
    suchThatClauseToken.relRef = "Calls";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;
    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    // print synonym as first argument
    arguments = new std::vector<std::string>({"pn", "_"});
    suchThatClauseToken.relRef = "Calls";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;
    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    // variable synonym as first argument
    arguments = new std::vector<std::string>({"v", "_"});
    suchThatClauseToken.relRef = "Calls";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;
    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    // constant synonym as first argument
    arguments = new std::vector<std::string>({"con", "_"});
    suchThatClauseToken.relRef = "Calls";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;
    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    // wildcard as first argument
    arguments = new std::vector<std::string>({"_", "_"});
    suchThatClauseToken.relRef = "Calls";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;
    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // variable synonym as second argument
    arguments = new std::vector<std::string>({"p", "v"});
    suchThatClauseToken.relRef = "Calls";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;
    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    // ident as second argument
    arguments = new std::vector<std::string>({"p", "\"x\""});
    suchThatClauseToken.relRef = "Calls";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;
    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // wildcard as second argument
    arguments = new std::vector<std::string>({"p", "_"});
    suchThatClauseToken.relRef = "Calls";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;
    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // assign synonym as second argument
    arguments = new std::vector<std::string>({"p", "a"});
    suchThatClauseToken.relRef = "Calls";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;
    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    // print synonym as second argument
    arguments = new std::vector<std::string>({"p", "pn"});
    suchThatClauseToken.relRef = "Calls";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;
    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    // if synonym as second argument
    arguments = new std::vector<std::string>({"p", "ifs"});
    suchThatClauseToken.relRef = "Calls";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;
    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    // while synonym as second argument
    arguments = new std::vector<std::string>({"p", "w"});
    suchThatClauseToken.relRef = "Calls";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;
    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    // procedure synonym as second argument
    arguments = new std::vector<std::string>({"_", "p"});
    suchThatClauseToken.relRef = "Calls";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;
    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // call synonym as second argument
    arguments = new std::vector<std::string>({"p", "c"});
    suchThatClauseToken.relRef = "Calls";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;
    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    // stmt synonym as second argument
    arguments = new std::vector<std::string>({"p", "s"});
    suchThatClauseToken.relRef = "Calls";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;
    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    // read synonym as second argument
    arguments = new std::vector<std::string>({"p", "r"});
    suchThatClauseToken.relRef = "Calls";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;
    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    // constant synonym as second argument
    arguments = new std::vector<std::string>({"p", "con"});
    suchThatClauseToken.relRef = "Calls";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;
    REQUIRE_THROWS(validator.checkForSemantics(queryToken));
}

TEST_CASE ("QP SEMANTIC VALIDATOR: CALLS* CLAUSE CHECK ARGUMENTS") {
    Validator validator = Validator();
    QueryToken queryToken = QueryToken();
    setUp(queryToken);

    // IDENT as first argument
    SuchThatClauseToken suchThatClauseToken = SuchThatClauseToken();
    std::vector<std::string>* arguments = new std::vector<std::string>({"\"x\"", "_"});
    suchThatClauseToken.relRef = "Calls*";
    suchThatClauseToken.arguments = arguments;
    std::vector<SuchThatClauseToken>* suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;
    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // assign synonym as first argument
    arguments = new std::vector<std::string>({"a", "_"});
    suchThatClauseToken.relRef = "Calls*";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;
    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    // read synonym as first argument
    arguments = new std::vector<std::string>({"r", "_"});
    suchThatClauseToken.relRef = "Calls*";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;
    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    // if synonym as first argument
    arguments = new std::vector<std::string>({"ifs", "_"});
    suchThatClauseToken.relRef = "Calls*";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;
    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    // while synonym as first argument
    arguments = new std::vector<std::string>({"w", "_"});
    suchThatClauseToken.relRef = "Calls*";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;
    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    // procedure synonym as first argument
    arguments = new std::vector<std::string>({"p", "_"});
    suchThatClauseToken.relRef = "Calls*";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;
    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // call synonym as first argument
    arguments = new std::vector<std::string>({"c", "_"});
    suchThatClauseToken.relRef = "Calls*";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;
    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    // stmt synonym as first argument
    arguments = new std::vector<std::string>({"s", "_"});
    suchThatClauseToken.relRef = "Calls*";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;
    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    // print synonym as first argument
    arguments = new std::vector<std::string>({"pn", "_"});
    suchThatClauseToken.relRef = "Calls*";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;
    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    // variable synonym as first argument
    arguments = new std::vector<std::string>({"v", "_"});
    suchThatClauseToken.relRef = "Calls*";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;
    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    // constant synonym as first argument
    arguments = new std::vector<std::string>({"con", "_"});
    suchThatClauseToken.relRef = "Calls*";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;
    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    // wildcard as first argument
    arguments = new std::vector<std::string>({"_", "_"});
    suchThatClauseToken.relRef = "Calls*";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;
    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // variable synonym as second argument
    arguments = new std::vector<std::string>({"p", "v"});
    suchThatClauseToken.relRef = "Calls*";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;
    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    // ident as second argument
    arguments = new std::vector<std::string>({"p", "\"x\""});
    suchThatClauseToken.relRef = "Calls*";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;
    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // wildcard as second argument
    arguments = new std::vector<std::string>({"p", "_"});
    suchThatClauseToken.relRef = "Calls*";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;
    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // assign synonym as second argument
    arguments = new std::vector<std::string>({"p", "a"});
    suchThatClauseToken.relRef = "Calls*";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;
    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    // print synonym as second argument
    arguments = new std::vector<std::string>({"p", "pn"});
    suchThatClauseToken.relRef = "Calls*";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;
    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    // if synonym as second argument
    arguments = new std::vector<std::string>({"p", "ifs"});
    suchThatClauseToken.relRef = "Calls*";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;
    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    // while synonym as second argument
    arguments = new std::vector<std::string>({"p", "w"});
    suchThatClauseToken.relRef = "Calls*";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;
    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    // procedure synonym as second argument
    arguments = new std::vector<std::string>({"_", "p"});
    suchThatClauseToken.relRef = "Calls*";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;
    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // call synonym as second argument
    arguments = new std::vector<std::string>({"p", "c"});
    suchThatClauseToken.relRef = "Calls*";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;
    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    // stmt synonym as second argument
    arguments = new std::vector<std::string>({"p", "s"});
    suchThatClauseToken.relRef = "Calls*";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;
    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    // read synonym as second argument
    arguments = new std::vector<std::string>({"p", "r"});
    suchThatClauseToken.relRef = "Calls*";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;
    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    // constant synonym as second argument
    arguments = new std::vector<std::string>({"p", "con"});
    suchThatClauseToken.relRef = "Calls*";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;
    REQUIRE_THROWS(validator.checkForSemantics(queryToken));
}

TEST_CASE ("QP SEMANTIC VALIDATOR: AFFECTS CLAUSE CHECK ARGUMENTS") {
    Validator validator = Validator();
    QueryToken queryToken = QueryToken();
    setUp(queryToken);

    // IDENT as first argument
    SuchThatClauseToken suchThatClauseToken = SuchThatClauseToken();
    std::vector<std::string>* arguments = new std::vector<std::string>({"\"x\"", "_"});
    suchThatClauseToken.relRef = "Affects";
    suchThatClauseToken.arguments = arguments;
    std::vector<SuchThatClauseToken>* suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;
    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // assign synonym as first argument
    arguments = new std::vector<std::string>({"a", "_"});
    suchThatClauseToken.relRef = "Affects";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;
    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // read synonym as first argument
    arguments = new std::vector<std::string>({"r", "_"});
    suchThatClauseToken.relRef = "Affects";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;
    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    // if synonym as first argument
    arguments = new std::vector<std::string>({"ifs", "_"});
    suchThatClauseToken.relRef = "Affects";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;
    setUp(queryToken);
    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    // while synonym as first argument
    arguments = new std::vector<std::string>({"w", "_"});
    suchThatClauseToken.relRef = "Affects";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;
    setUp(queryToken);
    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    // procedure synonym as first argument
    arguments = new std::vector<std::string>({"p", "_"});
    suchThatClauseToken.relRef = "Affects";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;
    setUp(queryToken);
    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    // call synonym as first argument
    arguments = new std::vector<std::string>({"c", "_"});
    suchThatClauseToken.relRef = "Affects";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;
    setUp(queryToken);
    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    // stmt synonym as first argument
    arguments = new std::vector<std::string>({"s", "_"});
    suchThatClauseToken.relRef = "Affects";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;
    setUp(queryToken);
    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    // print synonym as first argument
    arguments = new std::vector<std::string>({"pn", "_"});
    suchThatClauseToken.relRef = "Affects";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;
    setUp(queryToken);
    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    // variable synonym as first argument
    arguments = new std::vector<std::string>({"v", "_"});
    suchThatClauseToken.relRef = "Affects";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;
    setUp(queryToken);
    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    // constant synonym as first argument
    arguments = new std::vector<std::string>({"con", "_"});
    suchThatClauseToken.relRef = "Affects";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;
    setUp(queryToken);
    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    // wildcard as first argument
    arguments = new std::vector<std::string>({"_", "_"});
    suchThatClauseToken.relRef = "Affects";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;
    setUp(queryToken);
    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // variable synonym as second argument
    arguments = new std::vector<std::string>({"a", "v"});
    suchThatClauseToken.relRef = "Affects";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;
    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    // ident as second argument
    arguments = new std::vector<std::string>({"p", "\"x\""});
    suchThatClauseToken.relRef = "Affects";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;
    setUp(queryToken);
    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    // wildcard as second argument
    arguments = new std::vector<std::string>({"a", "_"});
    suchThatClauseToken.relRef = "Affects";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;
    setUp(queryToken);
    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // assign synonym as second argument
    arguments = new std::vector<std::string>({"_", "a"});
    suchThatClauseToken.relRef = "Affects";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;
    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // print synonym as second argument
    arguments = new std::vector<std::string>({"a", "pn"});
    suchThatClauseToken.relRef = "Affects";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;
    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    // if synonym as second argument
    arguments = new std::vector<std::string>({"a", "ifs"});
    suchThatClauseToken.relRef = "Affects";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;
    setUp(queryToken);
    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    // while synonym as second argument
    arguments = new std::vector<std::string>({"a", "w"});
    suchThatClauseToken.relRef = "Affects";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;
    setUp(queryToken);
    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    // assign synonym as second argument
    arguments = new std::vector<std::string>({"_", "a"});
    suchThatClauseToken.relRef = "Affects";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;
    setUp(queryToken);
    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // call synonym as second argument
    arguments = new std::vector<std::string>({"_", "c"});
    suchThatClauseToken.relRef = "Affects";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;
    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    // stmt synonym as second argument
    arguments = new std::vector<std::string>({"_", "s"});
    suchThatClauseToken.relRef = "Affects";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;
    setUp(queryToken);
    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    // read synonym as second argument
    arguments = new std::vector<std::string>({"_", "r"});
    suchThatClauseToken.relRef = "Affects";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;
    setUp(queryToken);
    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    // constant synonym as second argument
    arguments = new std::vector<std::string>({"_", "con"});
    suchThatClauseToken.relRef = "Affects";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;
    setUp(queryToken);
    REQUIRE_THROWS(validator.checkForSemantics(queryToken));
}

TEST_CASE ("QP SEMANTIC VALIDATOR: AFFECTS* CLAUSE CHECK ARGUMENTS") {
    Validator validator = Validator();
    QueryToken queryToken = QueryToken();
    setUp(queryToken);

    // IDENT as first argument
    SuchThatClauseToken suchThatClauseToken = SuchThatClauseToken();
    std::vector<std::string>* arguments = new std::vector<std::string>({"\"x\"", "_"});
    suchThatClauseToken.relRef = "Affects*";
    suchThatClauseToken.arguments = arguments;
    std::vector<SuchThatClauseToken>* suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;
    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // assign synonym as first argument
    arguments = new std::vector<std::string>({"a", "_"});
    suchThatClauseToken.relRef = "Affects*";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;
    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // read synonym as first argument
    arguments = new std::vector<std::string>({"r", "_"});
    suchThatClauseToken.relRef = "Affects*";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;
    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    // if synonym as first argument
    arguments = new std::vector<std::string>({"ifs", "_"});
    suchThatClauseToken.relRef = "Affects*";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;
    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    // while synonym as first argument
    arguments = new std::vector<std::string>({"w", "_"});
    suchThatClauseToken.relRef = "Affects*";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;
    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    // procedure synonym as first argument
    arguments = new std::vector<std::string>({"p", "_"});
    suchThatClauseToken.relRef = "Affects*";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;
    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    // call synonym as first argument
    arguments = new std::vector<std::string>({"c", "_"});
    suchThatClauseToken.relRef = "Affects*";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;
    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    // stmt synonym as first argument
    arguments = new std::vector<std::string>({"s", "_"});
    suchThatClauseToken.relRef = "Affects*";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;
    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    // print synonym as first argument
    arguments = new std::vector<std::string>({"pn", "_"});
    suchThatClauseToken.relRef = "Affects*";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;
    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    // variable synonym as first argument
    arguments = new std::vector<std::string>({"v", "_"});
    suchThatClauseToken.relRef = "Affects*";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;
    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    // constant synonym as first argument
    arguments = new std::vector<std::string>({"con", "_"});
    suchThatClauseToken.relRef = "Affects*";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;
    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    // wildcard as first argument
    arguments = new std::vector<std::string>({"_", "_"});
    suchThatClauseToken.relRef = "Affects*";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;
    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // variable synonym as second argument
    arguments = new std::vector<std::string>({"p", "v"});
    suchThatClauseToken.relRef = "Affects*";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;
    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    // ident as second argument
    arguments = new std::vector<std::string>({"_", "\"x\""});
    suchThatClauseToken.relRef = "Affects*";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;
    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // wildcard as second argument
    arguments = new std::vector<std::string>({"_", "_"});
    suchThatClauseToken.relRef = "Affects*";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;
    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // assign synonym as second argument
    arguments = new std::vector<std::string>({"_", "a"});
    suchThatClauseToken.relRef = "Affects*";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;
    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // print synonym as second argument
    arguments = new std::vector<std::string>({"_", "pn"});
    suchThatClauseToken.relRef = "Affects*";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;
    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    // if synonym as second argument
    arguments = new std::vector<std::string>({"_", "ifs"});
    suchThatClauseToken.relRef = "Affects*";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;
    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    // while synonym as second argument
    arguments = new std::vector<std::string>({"_", "w"});
    suchThatClauseToken.relRef = "Affects*";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;
    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    // assign synonym as second argument
    arguments = new std::vector<std::string>({"_", "a"});
    suchThatClauseToken.relRef = "Affects*";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;
    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // call synonym as second argument
    arguments = new std::vector<std::string>({"_", "c"});
    suchThatClauseToken.relRef = "Affects*";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;
    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    // stmt synonym as second argument
    arguments = new std::vector<std::string>({"_", "s"});
    suchThatClauseToken.relRef = "Affects*";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;
    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    // read synonym as second argument
    arguments = new std::vector<std::string>({"_", "r"});
    suchThatClauseToken.relRef = "Affects*";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;
    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    // constant synonym as second argument
    arguments = new std::vector<std::string>({"_", "con"});
    suchThatClauseToken.relRef = "Affects*";
    suchThatClauseToken.arguments = arguments;
    suchThatClauseTokens = new std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = suchThatClauseTokens;
    REQUIRE_THROWS(validator.checkForSemantics(queryToken));
}