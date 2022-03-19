#include "catch.hpp"
#include "QP_Parser/Validator.h"

#include <utility>

using namespace qp;

// Check for Semantic Errors for Declarations
TEST_CASE ("QP SEMANTIC VALIDATOR: NON-REPEATED DECLARATION NAMES AND DESIGN ENTITIES") {
    auto declarationTokens = new std::map<std::string, std::string> ({
                                                                             {"v", "variable"},
                                                                             {"a", "assign"}});
    auto declarationNames = std::vector<std::string>({"v", "a"});
    auto designEntities = std::vector<std::string>({"variable", "assign"});
    auto declarations = std::make_pair(declarationNames, designEntities);

    QueryToken queryToken = QueryToken();
    queryToken.declarations = &declarations;
    queryToken.declarationTokens = declarationTokens;
    queryToken.selectClauseTokens = new std::vector<std::string>({"v"});
    queryToken.patternTokens = new std::vector<PatternToken>();
    queryToken.suchThatClauseTokens = new std::vector<SuchThatClauseToken>();
    queryToken.withClauses = new std::vector<std::pair<std::string, std::string>>();

    Validator validator = Validator();
    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));
}

TEST_CASE ("QP SEMANTIC VALIDATOR: REPEATED DECLARATION NAMES") {
    auto declarationTokens = new std::map<std::string, std::string> ({
                                                                             {"v", "variable"},
                                                                             {"v", "assign"}});
    auto declarationNames = std::vector<std::string>({"v", "v"});
    auto designEntities = std::vector<std::string>({"variable", "assign"});
    auto declarations = std::make_pair(declarationNames, designEntities);

    QueryToken queryToken = QueryToken();
    queryToken.declarations = &declarations;
    queryToken.declarationTokens = declarationTokens;
    queryToken.selectClauseTokens = new std::vector<std::string>({"v"});

    Validator validator = Validator();
    REQUIRE_THROWS(validator.checkForSemantics(queryToken));
}

TEST_CASE ("QP SEMANTIC VALIDATOR: REPEATED DESIGN ENTITIES") {
    auto declarationTokens = new std::map<std::string, std::string> ({
                                                                             {"v1", "variable"},
                                                                             {"a", "assign"},
                                                                             {"v2", "variable"}});
    auto declarationNames = std::vector<std::string>({"v1", "a", "v2"});
    auto designEntities = std::vector<std::string>({"variable", "assign", "variable"});
    auto declarations = std::make_pair(declarationNames, designEntities);

    QueryToken queryToken = QueryToken();
    queryToken.declarations = &declarations;
    queryToken.declarationTokens = declarationTokens;
    queryToken.selectClauseTokens = new std::vector<std::string>({"v1"});

    Validator validator = Validator();
    REQUIRE_THROWS(validator.checkForSemantics(queryToken));
}

TEST_CASE ("QP SEMANTIC VALIDATOR: SYNONYM NOT IN DECLARATIONS") {
    auto declarationTokens = new std::map<std::string, std::string> ({
                                                                             {"v1", "variable"},
                                                                             {"a", "assign"}});
    auto declarationNames = std::vector<std::string>({"v1", "a", "v2"});
    auto designEntities = std::vector<std::string>({"variable", "assign"});
    auto declarations = std::make_pair(declarationNames, designEntities);

    QueryToken queryToken = QueryToken();
    queryToken.declarations = &declarations;
    queryToken.declarationTokens = declarationTokens;
    queryToken.selectClauseTokens = new std::vector<std::string>({"v"});

    Validator validator = Validator();
    REQUIRE_THROWS(validator.checkForSemantics(queryToken));
}

TEST_CASE ("QP SEMANTIC VALIDATOR: CHECK VALIDITY OF ATTRIBUTE REFERENCES IN SELECT CLAUSE") {
    auto declarationTokens = new std::map<std::string, std::string> ({
                                                                             {"s", "stmt"},
                                                                             {"r", "read"},
                                                                             {"pn", "print"},
                                                                             {"a", "assign"},
                                                                             {"c", "call"},
                                                                             {"w", "while"},
                                                                             {"ifs", "if"},
                                                                             {"v", "variable"},
                                                                             {"con", "constant"},
                                                                             {"p", "procedure"}});
    auto declarationNames = std::vector<std::string>({"s", "r", "pn", "a", "c", "w", "ifs", "v", "con", "p"});
    auto designEntities = std::vector<std::string>({"stmt", "read", "assign", "call", "while", "if", "variable",
                                                    "constant", "procedure"});
    auto declarations = std::make_pair(declarationNames, designEntities);

    QueryToken queryToken = QueryToken();
    queryToken.declarations = &declarations;
    queryToken.declarationTokens = declarationTokens;
    queryToken.selectClauseTokens = new std::vector<std::string>({"p.procName", "c.procName", "v.varName",
                                                                  "r.varName", "pn.varName", "con.value",
                                                                  "s.stmt#", "r.stmt#", "pn.stmt#", "c.stmt#",
                                                                  "w.stmt#", "ifs.stmt#", "a.stmt#"});
    queryToken.patternTokens = new std::vector<PatternToken>();
    queryToken.withClauses = new std::vector<std::pair<std::string, std::string>>();
    queryToken.suchThatClauseTokens = new std::vector<SuchThatClauseToken>();

    Validator validator = Validator();
    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // Invalid attribute references - procName
    queryToken.selectClauseTokens = new std::vector<std::string>({"s.procName"});
    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    queryToken.selectClauseTokens = new std::vector<std::string>({"r.procName"});
    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    queryToken.selectClauseTokens = new std::vector<std::string>({"pn.procName"});
    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    queryToken.selectClauseTokens = new std::vector<std::string>({"a.procName"});
    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    queryToken.selectClauseTokens = new std::vector<std::string>({"w.procName"});
    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    queryToken.selectClauseTokens = new std::vector<std::string>({"ifs.procName"});
    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    queryToken.selectClauseTokens = new std::vector<std::string>({"v.procName"});
    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    queryToken.selectClauseTokens = new std::vector<std::string>({"con.procName"});
    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    // Invalid attribute references - varName
    queryToken.selectClauseTokens = new std::vector<std::string>({"s.varName"});
    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    queryToken.selectClauseTokens = new std::vector<std::string>({"a.varName"});
    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    queryToken.selectClauseTokens = new std::vector<std::string>({"c.varName"});
    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    queryToken.selectClauseTokens = new std::vector<std::string>({"w.varName"});
    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    queryToken.selectClauseTokens = new std::vector<std::string>({"ifs.varName"});
    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    queryToken.selectClauseTokens = new std::vector<std::string>({"con.varName"});
    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    queryToken.selectClauseTokens = new std::vector<std::string>({"p.varName"});
    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    // Invalid attribute references - value
    queryToken.selectClauseTokens = new std::vector<std::string>({"s.value"});
    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    queryToken.selectClauseTokens = new std::vector<std::string>({"r.value"});
    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    queryToken.selectClauseTokens = new std::vector<std::string>({"pn.value"});
    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    queryToken.selectClauseTokens = new std::vector<std::string>({"a.value"});
    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    queryToken.selectClauseTokens = new std::vector<std::string>({"c.value"});
    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    queryToken.selectClauseTokens = new std::vector<std::string>({"w.value"});
    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    queryToken.selectClauseTokens = new std::vector<std::string>({"ifs.value"});
    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    queryToken.selectClauseTokens = new std::vector<std::string>({"v.value"});
    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    queryToken.selectClauseTokens = new std::vector<std::string>({"p.value"});
    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    // Invalid attribute references - stmt#
    queryToken.selectClauseTokens = new std::vector<std::string>({"v.stmt#"});
    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    queryToken.selectClauseTokens = new std::vector<std::string>({"con.stmt#"});
    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    queryToken.selectClauseTokens = new std::vector<std::string>({"p.stmt#"});
    REQUIRE_THROWS(validator.checkForSemantics(queryToken));
}

TEST_CASE ("QP SEMANTIC VALIDATOR: PATTERN CHECK") {
    Validator validator = Validator();
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
    auto declarations = std::make_pair(declarationNames, designEntities);

    QueryToken queryToken = QueryToken();
    queryToken.declarations = &declarations;
    queryToken.declarationTokens = declarationTokens;
    queryToken.selectClauseTokens = new std::vector<std::string>({"s"});
    queryToken.suchThatClauseTokens = new std::vector<SuchThatClauseToken>();
    queryToken.withClauses = new std::vector<std::pair<std::string, std::string>>();

    // valid synonym - assign
    PatternToken patternToken = PatternToken();
    std::vector<std::string> arguments = std::vector<std::string>({"_", "_"});
    patternToken.synonym = "a";
    patternToken.arguments = &arguments;
    std::vector<PatternToken> patternTokens = std::vector<PatternToken>({patternToken});
    queryToken.patternTokens = &patternTokens;
    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // valid synonym - while
    arguments = std::vector<std::string>({"_", "_"});
    patternToken.synonym = "w";
    patternToken.arguments = &arguments;
    patternTokens = std::vector<PatternToken>({patternToken});
    queryToken.patternTokens = &patternTokens;
    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // valid synonym - ifs
    arguments = std::vector<std::string>({"_", "_", "_"});
    patternToken.synonym = "ifs";
    patternToken.arguments = &arguments;
    patternTokens = std::vector<PatternToken>({patternToken});
    queryToken.patternTokens = &patternTokens;
    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // invalid synonym - statement
    arguments = std::vector<std::string>({"_", "_"});
    patternToken.synonym = "s";
    patternToken.arguments = &arguments;
    patternTokens = std::vector<PatternToken>({patternToken});
    queryToken.patternTokens = &patternTokens;
    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    // invalid synonym - read
    arguments = std::vector<std::string>({"_", "_"});
    patternToken.synonym = "r";
    patternToken.arguments = &arguments;
    patternTokens = std::vector<PatternToken>({patternToken});
    queryToken.patternTokens = &patternTokens;
    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    // invalid synonym - print
    arguments = std::vector<std::string>({"_", "_"});
    patternToken.synonym = "pn";
    patternToken.arguments = &arguments;
    patternTokens = std::vector<PatternToken>({patternToken});
    queryToken.patternTokens = &patternTokens;
    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    // invalid synonym - variable
    arguments = std::vector<std::string>({"_", "_"});
    patternToken.synonym = "v";
    patternToken.arguments = &arguments;
    patternTokens = std::vector<PatternToken>({patternToken});
    queryToken.patternTokens = &patternTokens;
    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    // invalid synonym - constant
    arguments = std::vector<std::string>({"_", "_"});
    patternToken.synonym = "con";
    patternToken.arguments = &arguments;
    patternTokens = std::vector<PatternToken>({patternToken});
    queryToken.patternTokens = &patternTokens;
    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    // invalid synonym - procedure
    arguments = std::vector<std::string>({"_", "_"});
    patternToken.synonym = "p";
    patternToken.arguments = &arguments;
    patternTokens = std::vector<PatternToken>({patternToken});
    queryToken.patternTokens = &patternTokens;
    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    // invalid synonym that does not exit in declarations
    arguments = std::vector<std::string>({"_", "_"});
    patternToken.synonym = "unknown";
    patternToken.arguments = &arguments;
    patternTokens = std::vector<PatternToken>({patternToken});
    queryToken.patternTokens = &patternTokens;
    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    // invalid synonym for ifs pattern - stmt
    arguments = std::vector<std::string>({"_", "_", "_"});
    patternToken.synonym = "s";
    patternToken.arguments = &arguments;
    patternTokens = std::vector<PatternToken>({patternToken});
    queryToken.patternTokens = &patternTokens;
    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    // invalid synonym for ifs pattern - read
    arguments = std::vector<std::string>({"_", "_", "_"});
    patternToken.synonym = "r";
    patternToken.arguments = &arguments;
    patternTokens = std::vector<PatternToken>({patternToken});
    queryToken.patternTokens = &patternTokens;
    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    // invalid synonym for ifs pattern - print
    arguments = std::vector<std::string>({"_", "_", "_"});
    patternToken.synonym = "pn";
    patternToken.arguments = &arguments;
    patternTokens = std::vector<PatternToken>({patternToken});
    queryToken.patternTokens = &patternTokens;
    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    // invalid synonym for ifs pattern - assign
    arguments = std::vector<std::string>({"_", "_", "_"});
    patternToken.synonym = "a";
    patternToken.arguments = &arguments;
    patternTokens = std::vector<PatternToken>({patternToken});
    queryToken.patternTokens = &patternTokens;
    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    // invalid synonym for ifs pattern - call
    arguments = std::vector<std::string>({"_", "_", "_"});
    patternToken.synonym = "c";
    patternToken.arguments = &arguments;
    patternTokens = std::vector<PatternToken>({patternToken});
    queryToken.patternTokens = &patternTokens;
    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    // invalid synonym for ifs pattern - while
    arguments = std::vector<std::string>({"_", "_", "_"});
    patternToken.synonym = "w";
    patternToken.arguments = &arguments;
    patternTokens = std::vector<PatternToken>({patternToken});
    queryToken.patternTokens = &patternTokens;
    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    // invalid synonym for ifs pattern - variable
    arguments = std::vector<std::string>({"_", "_", "_"});
    patternToken.synonym = "v";
    patternToken.arguments = &arguments;
    patternTokens = std::vector<PatternToken>({patternToken});
    queryToken.patternTokens = &patternTokens;
    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    // invalid synonym for ifs pattern - constant
    arguments = std::vector<std::string>({"_", "_", "_"});
    patternToken.synonym = "con";
    patternToken.arguments = &arguments;
    patternTokens = std::vector<PatternToken>({patternToken});
    queryToken.patternTokens = &patternTokens;
    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    // invalid synonym for ifs pattern - procedure
    arguments = std::vector<std::string>({"_", "_", "_"});
    patternToken.synonym = "p";
    patternToken.arguments = &arguments;
    patternTokens = std::vector<PatternToken>({patternToken});
    queryToken.patternTokens = &patternTokens;
    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    // assign pattern: valid first argument: variable
    arguments = std::vector<std::string>({"v", "_"});
    patternToken.synonym = "a";
    patternToken.arguments = &arguments;
    patternTokens = std::vector<PatternToken>({patternToken});
    queryToken.patternTokens = &patternTokens;
    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // assign pattern: valid first argument: ident
    arguments = std::vector<std::string>({"\"x\"", "_"});
    patternToken.synonym = "a";
    patternToken.arguments = &arguments;
    patternTokens = std::vector<PatternToken>({patternToken});
    queryToken.patternTokens = &patternTokens;
    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // assign pattern: valid first argument: wildcard
    arguments = std::vector<std::string>({"_", "_"});
    patternToken.synonym = "a";
    patternToken.arguments = &arguments;
    patternTokens = std::vector<PatternToken>({patternToken});
    queryToken.patternTokens = &patternTokens;
    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // assign pattern: valid second argument: ident
    arguments = std::vector<std::string>({"_", "\"x\""});
    patternToken.synonym = "a";
    patternToken.arguments = &arguments;
    patternTokens = std::vector<PatternToken>({patternToken});
    queryToken.patternTokens = &patternTokens;
    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // assign pattern: valid second argument: partial wildcard
    arguments = std::vector<std::string>({"_", "_\"x\"_"});
    patternToken.synonym = "a";
    patternToken.arguments = &arguments;
    patternTokens = std::vector<PatternToken>({patternToken});
    queryToken.patternTokens = &patternTokens;
    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // while pattern: valid first argument: variable
    arguments = std::vector<std::string>({"v", "_"});
    patternToken.synonym = "w";
    patternToken.arguments = &arguments;
    patternTokens = std::vector<PatternToken>({patternToken});
    queryToken.patternTokens = &patternTokens;
    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // while pattern: valid first argument: ident
    arguments = std::vector<std::string>({"\"x\"", "_"});
    patternToken.synonym = "w";
    patternToken.arguments = &arguments;
    patternTokens = std::vector<PatternToken>({patternToken});
    queryToken.patternTokens = &patternTokens;
    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // while pattern: valid second argument: wildcard
    arguments = std::vector<std::string>({"_", "_"});
    patternToken.synonym = "w";
    patternToken.arguments = &arguments;
    patternTokens = std::vector<PatternToken>({patternToken});
    queryToken.patternTokens = &patternTokens;
    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // if pattern: valid first argument: variable
    arguments = std::vector<std::string>({"v", "_", "_"});
    patternToken.synonym = "ifs";
    patternToken.arguments = &arguments;
    patternTokens = std::vector<PatternToken>({patternToken});
    queryToken.patternTokens = &patternTokens;
    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // if pattern: valid first argument: ident
    arguments = std::vector<std::string>({"\"x\"", "_", "_"});
    patternToken.synonym = "ifs";
    patternToken.arguments = &arguments;
    patternTokens = std::vector<PatternToken>({patternToken});
    queryToken.patternTokens = &patternTokens;
    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // assign pattern: invalid synonym for first argument
    arguments = std::vector<std::string>({"r", "_"});
    patternToken.synonym = "a";
    patternToken.arguments = &arguments;
    patternTokens = std::vector<PatternToken>({patternToken});
    queryToken.patternTokens = &patternTokens;
    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    // while pattern: invalid second argument: ident
    arguments = std::vector<std::string>({"_", "\"x\""});
    patternToken.synonym = "w";
    patternToken.arguments = &arguments;
    patternTokens = std::vector<PatternToken>({patternToken});
    queryToken.patternTokens = &patternTokens;
    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    // while pattern: invalid second argument: partial wildcard
    arguments = std::vector<std::string>({"_", "_\"x\"_"});
    patternToken.synonym = "w";
    patternToken.arguments = &arguments;
    patternTokens = std::vector<PatternToken>({patternToken});
    queryToken.patternTokens = &patternTokens;
    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    // if pattern: invalid second argument: ident
    arguments = std::vector<std::string>({"_", "\"x\"", "_"});
    patternToken.synonym = "ifs";
    patternToken.arguments = &arguments;
    patternTokens = std::vector<PatternToken>({patternToken});
    queryToken.patternTokens = &patternTokens;
    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    // if pattern: invalid second argument: integer
    arguments = std::vector<std::string>({"_", "3", "_"});
    patternToken.synonym = "ifs";
    patternToken.arguments = &arguments;
    patternTokens = std::vector<PatternToken>({patternToken});
    queryToken.patternTokens = &patternTokens;
    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    // if pattern: invalid second argument: partial wildcard
    arguments = std::vector<std::string>({"_", "_\"x\"_", "_"});
    patternToken.synonym = "ifs";
    patternToken.arguments = &arguments;
    patternTokens = std::vector<PatternToken>({patternToken});
    queryToken.patternTokens = &patternTokens;
    REQUIRE_THROWS(validator.checkForSemantics(queryToken));
}

TEST_CASE ("QP SEMANTIC VALIDATOR: WITH CLAUSES CHECK") {
    Validator validator = Validator();
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
    auto declarations = std::make_pair(declarationNames, designEntities);

    QueryToken queryToken = QueryToken();
    queryToken.declarations = &declarations;
    queryToken.declarationTokens = declarationTokens;
    queryToken.patternTokens = new std::vector<PatternToken>();
    queryToken.selectClauseTokens = new std::vector<std::string>({"s"});
    queryToken.suchThatClauseTokens = new std::vector<SuchThatClauseToken>();
    queryToken.withClauses = new std::vector<std::pair<std::string, std::string>>();

    // valid attr refs
    auto withClauses = std::vector<std::pair<std::string, std::string>>({
        std::pair<std::string, std::string>("p.procName", "c.procName"),
        std::pair<std::string, std::string>("v.varName", "r.varName"),
        std::pair<std::string, std::string>("pn.varName", "\"x\""),
        std::pair<std::string, std::string>("con.value", "3"),
        std::pair<std::string, std::string>("s.stmt#", "r.stmt#"),
        std::pair<std::string, std::string>("pn.stmt#", "c.stmt#"),
        std::pair<std::string, std::string>("w.stmt#", "ifs.stmt#"),
        std::pair<std::string, std::string>("4", "a.stmt#"),
    });

    queryToken.withClauses = &withClauses;
    validator.checkForSemantics(queryToken);
    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));
}

TEST_CASE ("QP SEMANTIC VALIDATOR: MULTI-CLAUSE CHECK") {
    Validator validator = Validator();
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
    auto declarations = std::make_pair(declarationNames, designEntities);

    QueryToken queryToken = QueryToken();
    queryToken.declarations = &declarations;
    queryToken.declarationTokens = declarationTokens;
    queryToken.selectClauseTokens = new std::vector<std::string>({"s"});
    queryToken.withClauses = new std::vector<std::pair<std::string, std::string>>();

    SuchThatClauseToken suchThatClauseToken = SuchThatClauseToken();
    std::vector<std::string> arguments = std::vector<std::string>({"a", "v"});
    suchThatClauseToken.relRef = "Modifies";
    suchThatClauseToken.arguments = &arguments;
    std::vector<SuchThatClauseToken> suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;

    PatternToken patternToken = PatternToken();
    std::vector<std::string> patternArguments = std::vector<std::string>({"_", "_"});
    patternToken.synonym = "a";
    patternToken.arguments = &patternArguments;
    std::vector<PatternToken> patternTokens = std::vector<PatternToken>({patternToken});
    queryToken.patternTokens = &patternTokens;
    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));
}


TEST_CASE ("QP SEMANTIC VALIDATOR: SAME SYNONYM AS ARGUMENTS") {
    Validator validator = Validator();
    auto declarationTokens = new std::map<std::string, std::string>({{"s", "stmt"}});
    auto declarationNames = std::vector<std::string>({"s"});
    auto designEntities = std::vector<std::string>({"stmt"});
    auto declarations = std::make_pair(declarationNames, designEntities);

    QueryToken queryToken = QueryToken();
    queryToken.declarations = &declarations;
    queryToken.declarationTokens = declarationTokens;
    queryToken.selectClauseTokens = new std::vector<std::string>({"s"});
    queryToken.patternTokens = new std::vector<PatternToken>();
    queryToken.suchThatClauseTokens = new std::vector<SuchThatClauseToken>();
    queryToken.withClauses = new std::vector<std::pair<std::string, std::string>>();

    // variable synonym as second argument
    SuchThatClauseToken suchThatClauseToken = SuchThatClauseToken();
    std::vector<std::string> arguments = std::vector<std::string>({"s", "s"});
    suchThatClauseToken.relRef = "Follows";
    suchThatClauseToken.arguments = &arguments;
    std::vector<SuchThatClauseToken> suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;
    REQUIRE_THROWS(validator.checkForSemantics(queryToken));
}

TEST_CASE ("QP SEMANTIC VALIDATOR: SYNONYM IN ARGUMENT NOT DECLARED") {
    Validator validator = Validator();
    auto declarationTokens = new std::map<std::string, std::string>({{"s", "stmt"}});
    auto declarationNames = std::vector<std::string>({"s"});
    auto designEntities = std::vector<std::string>({"stmt"});
    auto declarations = std::make_pair(declarationNames, designEntities);

    QueryToken queryToken = QueryToken();
    queryToken.declarations = &declarations;
    queryToken.declarationTokens = declarationTokens;
    queryToken.selectClauseTokens = new std::vector<std::string>({"s"});
    queryToken.patternTokens = new std::vector<PatternToken>();
    queryToken.withClauses = new std::vector<std::pair<std::string, std::string>>();

    // variable synonym as second argument
    SuchThatClauseToken suchThatClauseToken = SuchThatClauseToken();
    std::vector<std::string> arguments = std::vector<std::string>({"s1", "s"});
    suchThatClauseToken.relRef = "Follows";
    suchThatClauseToken.arguments = &arguments;
    std::vector<SuchThatClauseToken> suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;
    REQUIRE_THROWS(validator.checkForSemantics(queryToken));
}