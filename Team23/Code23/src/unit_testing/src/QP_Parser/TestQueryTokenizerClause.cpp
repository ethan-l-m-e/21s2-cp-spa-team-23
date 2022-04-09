#include "catch.hpp"
#include "QP_Parser/Tokenizer.h"

#include <vector>
#include <string>
#include <map>

using namespace qp;

// Check tokenizing for Such That Clauses
TEST_CASE ("QP TOKENIZER: VALID SUCH THAT CLAUSE QUERIES") {
    Tokenizer tokenizer = Tokenizer();

    // FOLLOWS SUCH THAT CLAUSE
    std::string firstQuery = "stmt s; \n Select s such that Follows(3, 2)";
    firstQuery = Tokenizer::lexicalTokens(firstQuery);
    QueryToken queryToken = tokenizer.getQueryToken(firstQuery);

    // Check declarations
    std::map<std::string, std::string> expectedDeclarationTokens({{"s", "stmt"}});
    std::vector<std::string> expectedDeclarationNames({"s"});
    std::vector<std::string> expectedDesignEntities({"stmt"});

    auto declarationTokens = *(queryToken.declarationTokens);
    auto declarations = *(queryToken.declarations);
    auto declarationNames = declarations.first;
    auto designEntities = declarations.second;

    CHECK(declarationTokens == expectedDeclarationTokens);
    CHECK(declarationNames == expectedDeclarationNames);
    CHECK(designEntities == expectedDesignEntities);

    // Check SuchThatClause Token
    auto suchThatClauseTokens = *(queryToken.suchThatClauseTokens);
    auto suchThatClauseToken = suchThatClauseTokens[0];
    std::vector<std::string> expectedArguments = std::vector<std::string>({"3", "2"});

    CHECK(suchThatClauseToken.relRef == "Follows");
    CHECK(*(suchThatClauseToken.arguments) == expectedArguments);

    // FOLLOWS* SUCH THAT CLAUSE
    firstQuery = "stmt Select; \n Select s such that Follows*(3, 2)";
    firstQuery = Tokenizer::lexicalTokens(firstQuery);
    queryToken = tokenizer.getQueryToken(firstQuery);

    // Check SuchThatClause Token
    auto selectClauseTokens = *(queryToken.selectClauseTokens);
    suchThatClauseTokens = *(queryToken.suchThatClauseTokens);
    suchThatClauseToken = suchThatClauseTokens[0];
    expectedArguments = std::vector<std::string>({"3", "2"});

    CHECK(suchThatClauseToken.relRef == "Follows*");
    CHECK(*(suchThatClauseToken.arguments) == expectedArguments);
    CHECK(selectClauseTokens[0] == "s");

    // PARENT SUCH THAT CLAUSE
    firstQuery = "stmt Select; \n Select s such that Parent(3, 2)";
    firstQuery = Tokenizer::lexicalTokens(firstQuery);
    queryToken = tokenizer.getQueryToken(firstQuery);

    // Check SuchThatClause Token
    suchThatClauseTokens = *(queryToken.suchThatClauseTokens);
    suchThatClauseToken = suchThatClauseTokens[0];
    expectedArguments = std::vector<std::string>({"3", "2"});

    CHECK(suchThatClauseToken.relRef == "Parent");
    CHECK(*(suchThatClauseToken.arguments) == expectedArguments);

    // PARENT* SUCH THAT CLAUSE
    firstQuery = "stmt Select; \n Select s such that Parent*(3, 2)";
    firstQuery = Tokenizer::lexicalTokens(firstQuery);
    queryToken = tokenizer.getQueryToken(firstQuery);

    // Check SuchThatClause Token
    suchThatClauseTokens = *(queryToken.suchThatClauseTokens);
    suchThatClauseToken = suchThatClauseTokens[0];
    expectedArguments = std::vector<std::string>({"3", "2"});

    CHECK(suchThatClauseToken.relRef == "Parent*");
    CHECK(*(suchThatClauseToken.arguments) == expectedArguments);

    // USES SUCH THAT CLAUSE
    firstQuery = "variable v; \n Select v such that Uses(v, \"eg\")";
    firstQuery = Tokenizer::lexicalTokens(firstQuery);
    queryToken = tokenizer.getQueryToken(firstQuery);

    // Check SuchThatClause Token
    suchThatClauseTokens = *(queryToken.suchThatClauseTokens);
    suchThatClauseToken = suchThatClauseTokens[0];
    expectedArguments = std::vector<std::string>({"v", "\"eg\""});

    CHECK(suchThatClauseToken.relRef == "Uses");
    CHECK(*(suchThatClauseToken.arguments) == expectedArguments);

    // NEXT SUCH THAT CLAUSE
    firstQuery = "stmt s; \n Select v such that Next(_, s)";
    firstQuery = Tokenizer::lexicalTokens(firstQuery);
    queryToken = tokenizer.getQueryToken(firstQuery);

    // Check SuchThatClause Token
    suchThatClauseTokens = *(queryToken.suchThatClauseTokens);
    suchThatClauseToken = suchThatClauseTokens[0];
    expectedArguments = std::vector<std::string>({"_", "s"});

    CHECK(suchThatClauseToken.relRef == "Next");
    CHECK(*(suchThatClauseToken.arguments) == expectedArguments);

    // NEXT* SUCH THAT CLAUSE
    firstQuery = "stmt s; \n Select v such that Next*(_, s)";
    queryToken = tokenizer.getQueryToken(firstQuery);

    // Check SuchThatClause Token
    suchThatClauseTokens = *(queryToken.suchThatClauseTokens);
    suchThatClauseToken = suchThatClauseTokens[0];
    expectedArguments = std::vector<std::string>({"_", "s"});

    CHECK(suchThatClauseToken.relRef == "Next*");
    CHECK(*(suchThatClauseToken.arguments) == expectedArguments);

    // CALLS SUCH THAT CLAUSE
    firstQuery = "procedure p; \n Select v such that Calls(_, p)";
    firstQuery = Tokenizer::lexicalTokens(firstQuery);
    queryToken = tokenizer.getQueryToken(firstQuery);

    // Check SuchThatClause Token
    suchThatClauseTokens = *(queryToken.suchThatClauseTokens);
    suchThatClauseToken = suchThatClauseTokens[0];
    expectedArguments = std::vector<std::string>({"_", "p"});

    CHECK(suchThatClauseToken.relRef == "Calls");
    CHECK(*(suchThatClauseToken.arguments) == expectedArguments);

    // CALLS* SUCH THAT CLAUSE
    firstQuery = "procedure p; \n Select v such that Calls*(_, p)";
    firstQuery = Tokenizer::lexicalTokens(firstQuery);
    queryToken = tokenizer.getQueryToken(firstQuery);

    // Check SuchThatClause Token
    suchThatClauseTokens = *(queryToken.suchThatClauseTokens);
    suchThatClauseToken = suchThatClauseTokens[0];
    expectedArguments = std::vector<std::string>({"_", "p"});

    CHECK(suchThatClauseToken.relRef == "Calls*");
    CHECK(*(suchThatClauseToken.arguments) == expectedArguments);

    // AFFECTS SUCH THAT CLAUSE
    firstQuery = "assign a; \n Select v such that Affects(_, a)";
    firstQuery = Tokenizer::lexicalTokens(firstQuery);
    queryToken = tokenizer.getQueryToken(firstQuery);

    // Check SuchThatClause Token
    suchThatClauseTokens = *(queryToken.suchThatClauseTokens);
    suchThatClauseToken = suchThatClauseTokens[0];
    expectedArguments = std::vector<std::string>({"_", "a"});

    CHECK(suchThatClauseToken.relRef == "Affects");
    CHECK(*(suchThatClauseToken.arguments) == expectedArguments);

    // AFFECTS* SUCH THAT CLAUSE
    firstQuery = "assign a; \n Select v such that Affects*(_, a)";
    firstQuery = Tokenizer::lexicalTokens(firstQuery);
    queryToken = tokenizer.getQueryToken(firstQuery);

    // Check SuchThatClause Token
    suchThatClauseTokens = *(queryToken.suchThatClauseTokens);
    suchThatClauseToken = suchThatClauseTokens[0];
    expectedArguments = std::vector<std::string>({"_", "a"});

    CHECK(suchThatClauseToken.relRef == "Affects*");
    CHECK(*(suchThatClauseToken.arguments) == expectedArguments);

    // MODIFIES SUCH THAT CLAUSE
    firstQuery = "variable v; \n Select v such that Modifies(v, \"eg\")";
    firstQuery = Tokenizer::lexicalTokens(firstQuery);
    queryToken = tokenizer.getQueryToken(firstQuery);

    // Check SuchThatClause Token
    suchThatClauseTokens = *(queryToken.suchThatClauseTokens);
    suchThatClauseToken = suchThatClauseTokens[0];
    expectedArguments = std::vector<std::string>({"v", "\"eg\""});

    CHECK(suchThatClauseToken.relRef == "Modifies");
    CHECK(*(suchThatClauseToken.arguments) == expectedArguments);

    // MODIFIES SUCH THAT CLAUSE WITH 2 IDENTS AS ARGUMENTS
    firstQuery = "variable v; \n Select v such that Modifies(\"entref\", \"eg\")";
    firstQuery = Tokenizer::lexicalTokens(firstQuery);
    queryToken = tokenizer.getQueryToken(firstQuery);

    // Check SuchThatClause Token
    suchThatClauseTokens = *(queryToken.suchThatClauseTokens);
    suchThatClauseToken = suchThatClauseTokens[0];
    expectedArguments = std::vector<std::string>({"\"entref\"", "\"eg\""});

    CHECK(suchThatClauseToken.relRef == "Modifies");
    CHECK(*(suchThatClauseToken.arguments) == expectedArguments);

    // MODIFIES SUCH THAT CLAUSE WITH SYNONYM AND WILDCARD AS ARGUMENTS
    firstQuery = "variable v1, v2; \n Select v1 such that Modifies(v1, _)";
    firstQuery = Tokenizer::lexicalTokens(firstQuery);
    queryToken = tokenizer.getQueryToken(firstQuery);

    // Check SuchThatClause Token
    suchThatClauseTokens = *(queryToken.suchThatClauseTokens);
    suchThatClauseToken = suchThatClauseTokens[0];
    expectedArguments = std::vector<std::string>({"v1", "_"});

    CHECK(suchThatClauseToken.relRef == "Modifies");
    CHECK(*(suchThatClauseToken.arguments) == expectedArguments);

    // MODIFIES SUCH THAT CLAUSE WITH SYNONYM NAME PROCNAME
    firstQuery = "variable procName; \n Select v1 such that Modifies(procName, _)";
    firstQuery = Tokenizer::lexicalTokens(firstQuery);
    queryToken = tokenizer.getQueryToken(firstQuery);

    // Check SuchThatClause Token
    suchThatClauseTokens = *(queryToken.suchThatClauseTokens);
    suchThatClauseToken = suchThatClauseTokens[0];
    expectedArguments = std::vector<std::string>({"procName", "_"});

    CHECK(suchThatClauseToken.relRef == "Modifies");
    CHECK(*(suchThatClauseToken.arguments) == expectedArguments);

    // MODIFIES SUCH THAT CLAUSE WITH SYNONYM NAME VARNAME
    firstQuery = "variable varName; \n Select v1 such that Modifies(varName, _)";
    firstQuery = Tokenizer::lexicalTokens(firstQuery);
    queryToken = tokenizer.getQueryToken(firstQuery);

    // Check SuchThatClause Token
    suchThatClauseTokens = *(queryToken.suchThatClauseTokens);
    suchThatClauseToken = suchThatClauseTokens[0];
    expectedArguments = std::vector<std::string>({"varName", "_"});

    CHECK(suchThatClauseToken.relRef == "Modifies");
    CHECK(*(suchThatClauseToken.arguments) == expectedArguments);
}

TEST_CASE ("QP TOKENIZER: MODIFIES SUCH THAT CLAUSE WITH SYNONYM NAME VALUE") {
    std::string firstQuery = "variable value; \n Select v1 such that Modifies(value, _)";
    firstQuery = Tokenizer::lexicalTokens(firstQuery);
    Tokenizer tokenizer = Tokenizer();
    QueryToken queryToken = tokenizer.getQueryToken(firstQuery);

    // Check SuchThatClause Token
    auto suchThatClauseTokens = *(queryToken.suchThatClauseTokens);
    auto suchThatClauseToken = suchThatClauseTokens[0];
    std::vector<std::string> expectedArguments = std::vector<std::string>({"value", "_"});

    CHECK(suchThatClauseToken.relRef == "Modifies");
    CHECK(*(suchThatClauseToken.arguments) == expectedArguments);
}

TEST_CASE ("QP TOKENIZER: MODIFIES SUCH THAT CLAUSE WITH SYNONYM NAME: SELECT") {
    std::string firstQuery = "variable Select; \n Select Select such that Modifies(Select, _)";
    firstQuery = Tokenizer::lexicalTokens(firstQuery);
    Tokenizer tokenizer = Tokenizer();
    QueryToken queryToken = tokenizer.getQueryToken(firstQuery);

    // Check SuchThatClause Token
    auto suchThatClauseTokens = *(queryToken.suchThatClauseTokens);
    auto suchThatClauseToken = suchThatClauseTokens[0];
    std::vector<std::string> expectedArguments = std::vector<std::string>({"Select", "_"});

    CHECK(suchThatClauseToken.relRef == "Modifies");
    CHECK(*(suchThatClauseToken.arguments) == expectedArguments);
}

TEST_CASE ("QP TOKENIZER: MODIFIES SUCH THAT CLAUSE WITH SYNONYM NAME: PATTERN") {
    std::string firstQuery = "variable pattern; \n Select pattern such that Modifies(pattern, _)";
    firstQuery = Tokenizer::lexicalTokens(firstQuery);
    Tokenizer tokenizer = Tokenizer();
    QueryToken queryToken = tokenizer.getQueryToken(firstQuery);

    // Check SuchThatClause Token
    auto suchThatClauseTokens = *(queryToken.suchThatClauseTokens);
    auto suchThatClauseToken = suchThatClauseTokens[0];
    std::vector<std::string> expectedArguments = std::vector<std::string>({"pattern", "_"});

    CHECK(suchThatClauseToken.relRef == "Modifies");
    CHECK(*(suchThatClauseToken.arguments) == expectedArguments);
}

TEST_CASE ("QP TOKENIZER: MODIFIES SUCH THAT CLAUSE WITH SYNONYM NAME: WITH") {
    std::string firstQuery = "variable with; \n Select pattern such that Modifies(with, _)";
    firstQuery = Tokenizer::lexicalTokens(firstQuery);
    Tokenizer tokenizer = Tokenizer();
    QueryToken queryToken = tokenizer.getQueryToken(firstQuery);

    // Check SuchThatClause Token
    auto suchThatClauseTokens = *(queryToken.suchThatClauseTokens);
    auto suchThatClauseToken = suchThatClauseTokens[0];
    std::vector<std::string> expectedArguments = std::vector<std::string>({"with", "_"});

    CHECK(suchThatClauseToken.relRef == "Modifies");
    CHECK(*(suchThatClauseToken.arguments) == expectedArguments);
}

TEST_CASE ("QP TOKENIZER: MODIFIES SUCH THAT CLAUSE WITH SYNONYM NAME: AND") {
    std::string firstQuery = "variable and; \n Select pattern such that Modifies(and, _)";
    firstQuery = Tokenizer::lexicalTokens(firstQuery);
    Tokenizer tokenizer = Tokenizer();
    QueryToken queryToken = tokenizer.getQueryToken(firstQuery);

    // Check SuchThatClause Token
    auto suchThatClauseTokens = *(queryToken.suchThatClauseTokens);
    auto suchThatClauseToken = suchThatClauseTokens[0];
    std::vector<std::string> expectedArguments = std::vector<std::string>({"and", "_"});

    CHECK(suchThatClauseToken.relRef == "Modifies");
    CHECK(*(suchThatClauseToken.arguments) == expectedArguments);
}

TEST_CASE ("QP TOKENIZER: MODIFIES SUCH THAT CLAUSE WITH SYNONYM NAME: MODIFIES") {
    std::string firstQuery = "variable Modifies; \n Select pattern such that Modifies(Modifies, _)";
    firstQuery = Tokenizer::lexicalTokens(firstQuery);
    Tokenizer tokenizer = Tokenizer();
    QueryToken queryToken = tokenizer.getQueryToken(firstQuery);

    // Check SuchThatClause Token
    auto suchThatClauseTokens = *(queryToken.suchThatClauseTokens);
    auto suchThatClauseToken = suchThatClauseTokens[0];
    std::vector<std::string> expectedArguments = std::vector<std::string>({"Modifies", "_"});

    CHECK(suchThatClauseToken.relRef == "Modifies");
    CHECK(*(suchThatClauseToken.arguments) == expectedArguments);
}

TEST_CASE ("QP TOKENIZER: MULTIPLE SUCH THAT CLAUSES: MODIFIES AND NEXT AND FOLLOWS") {
    std::string firstQuery = "variable value; stmt s; \n Select v1 such that Modifies(value, _) and Next(s, _) and Follows(s, _)";
    firstQuery = Tokenizer::lexicalTokens(firstQuery);
    Tokenizer tokenizer = Tokenizer();
    QueryToken queryToken = tokenizer.getQueryToken(firstQuery);
    auto suchThatClauseTokens = *(queryToken.suchThatClauseTokens);

    // Check first SuchThatClause Token
    auto suchThatClauseToken = suchThatClauseTokens[0];
    std::vector<std::string> expectedArguments = std::vector<std::string>({"value", "_"});

    CHECK(suchThatClauseToken.relRef == "Modifies");
    CHECK(*(suchThatClauseToken.arguments) == expectedArguments);

    // Check second SuchThatClause Token
    suchThatClauseToken = suchThatClauseTokens[1];
    expectedArguments = std::vector<std::string>({"s", "_"});

    CHECK(suchThatClauseToken.relRef == "Next");
    CHECK(*(suchThatClauseToken.arguments) == expectedArguments);

    // Check third SuchThatClause Token
    suchThatClauseToken = suchThatClauseTokens[2];
    expectedArguments = std::vector<std::string>({"s", "_"});

    CHECK(suchThatClauseToken.relRef == "Follows");
    CHECK(*(suchThatClauseToken.arguments) == expectedArguments);
}

TEST_CASE ("QP TOKENIZER: MULTIPLE SUCH THAT CLAUSES WITHOUT AND: MODIFIES AND NEXT AND FOLLOWS") {
    std::string firstQuery = "variable value; stmt s; \n Select v1 such that Modifies(value, _) such that Next(s, _) such that Follows(s, _)";
    firstQuery = Tokenizer::lexicalTokens(firstQuery);
    Tokenizer tokenizer = Tokenizer();
    QueryToken queryToken = tokenizer.getQueryToken(firstQuery);
    auto suchThatClauseTokens = *(queryToken.suchThatClauseTokens);

    // Check first SuchThatClause Token
    auto suchThatClauseToken = suchThatClauseTokens[0];
    std::vector<std::string> expectedArguments = std::vector<std::string>({"value", "_"});

    CHECK(suchThatClauseToken.relRef == "Modifies");
    CHECK(*(suchThatClauseToken.arguments) == expectedArguments);

    // Check second SuchThatClause Token
    suchThatClauseToken = suchThatClauseTokens[1];
    expectedArguments = std::vector<std::string>({"s", "_"});

    CHECK(suchThatClauseToken.relRef == "Next");
    CHECK(*(suchThatClauseToken.arguments) == expectedArguments);

    // Check third SuchThatClause Token
    suchThatClauseToken = suchThatClauseTokens[2];
    expectedArguments = std::vector<std::string>({"s", "_"});

    CHECK(suchThatClauseToken.relRef == "Follows");
    CHECK(*(suchThatClauseToken.arguments) == expectedArguments);
}

TEST_CASE ("QP TOKENIZER: MULTIPLE SUCH THAT CLAUSES WITH AND: MODIFIES AND NEXT AND FOLLOWS") {
    std::string firstQuery = "variable value; stmt s; \n Select v1 such that Modifies(value, _) and Next(s, _) such that Follows(s, _)";
    firstQuery = Tokenizer::lexicalTokens(firstQuery);
    Tokenizer tokenizer = Tokenizer();
    QueryToken queryToken = tokenizer.getQueryToken(firstQuery);
    auto suchThatClauseTokens = *(queryToken.suchThatClauseTokens);

    // Check first SuchThatClause Token
    auto suchThatClauseToken = suchThatClauseTokens[0];
    std::vector<std::string> expectedArguments = std::vector<std::string>({"value", "_"});

    CHECK(suchThatClauseToken.relRef == "Modifies");
    CHECK(*(suchThatClauseToken.arguments) == expectedArguments);

    // Check second SuchThatClause Token
    suchThatClauseToken = suchThatClauseTokens[1];
    expectedArguments = std::vector<std::string>({"s", "_"});

    CHECK(suchThatClauseToken.relRef == "Next");
    CHECK(*(suchThatClauseToken.arguments) == expectedArguments);

    // Check third SuchThatClause Token
    suchThatClauseToken = suchThatClauseTokens[2];
    expectedArguments = std::vector<std::string>({"s", "_"});

    CHECK(suchThatClauseToken.relRef == "Follows");
    CHECK(*(suchThatClauseToken.arguments) == expectedArguments);
}

TEST_CASE ("QP TOKENIZER: MODIFIES SUCH THAT CLAUSE WITH SPACES AND TABS BETWEEN 'SUCH' AND 'THAT'") {
    std::string firstQuery = "variable v; \n Select v1 such \t  \t  that Modifies(v, _)";
    firstQuery = Tokenizer::lexicalTokens(firstQuery);
    Tokenizer tokenizer = Tokenizer();
    QueryToken queryToken = tokenizer.getQueryToken(firstQuery);

    // Check SuchThatClause Token
    auto suchThatClauseTokens = *(queryToken.suchThatClauseTokens);
    auto suchThatClauseToken = suchThatClauseTokens[0];
    std::vector<std::string> expectedArguments = std::vector<std::string>({"v", "_"});

    CHECK(suchThatClauseToken.relRef == "Modifies");
    CHECK(*(suchThatClauseToken.arguments) == expectedArguments);
}

TEST_CASE ("QP TOKENIZER: MODIFIES SUCH THAT CLAUSE WITH SPACES AND TABS BETWEEN 'THAT' AND RELATIONSHIP") {
    std::string firstQuery = "variable v; \n Select v such that\t\t  \t\t  Modifies(v, _)";
    firstQuery = Tokenizer::lexicalTokens(firstQuery);
    Tokenizer tokenizer = Tokenizer();
    QueryToken queryToken = tokenizer.getQueryToken(firstQuery);

    // Check SuchThatClause Token
    auto suchThatClauseTokens = *(queryToken.suchThatClauseTokens);
    auto suchThatClauseToken = suchThatClauseTokens[0];
    std::vector<std::string> expectedArguments = std::vector<std::string>({"v", "_"});

    CHECK(suchThatClauseToken.relRef == "Modifies");
    CHECK(*(suchThatClauseToken.arguments) == expectedArguments);
}

TEST_CASE ("QP TOKENIZER: MODIFIES SUCH THAT CLAUSE WITH SPACE AND TABS BETWEEN RELREF AND '('") {
    std::string firstQuery = "variable v; \n Select v such that Modifies\t  \t  \t(v, _)";
    firstQuery = Tokenizer::lexicalTokens(firstQuery);
    Tokenizer tokenizer = Tokenizer();
    QueryToken queryToken = tokenizer.getQueryToken(firstQuery);

    // Check SuchThatClause Token
    auto suchThatClauseTokens = *(queryToken.suchThatClauseTokens);
    auto suchThatClauseToken = suchThatClauseTokens[0];
    std::vector<std::string> expectedArguments = std::vector<std::string>({"v", "_"});

    CHECK(suchThatClauseToken.relRef == "Modifies");
    CHECK(*(suchThatClauseToken.arguments) == expectedArguments);
}

TEST_CASE ("QP TOKENIZER: MODIFIES SUCH THAT CLAUSE WITH SPACES AND TABS BETWEEN '(' AND FIRST ARGUMENT") {
    std::string firstQuery = "variable v; \n Select v such that Modifies(\t  \t  \tv, _)";
    firstQuery = Tokenizer::lexicalTokens(firstQuery);
    Tokenizer tokenizer = Tokenizer();
    QueryToken queryToken = tokenizer.getQueryToken(firstQuery);

    // Check SuchThatClause Token
    auto suchThatClauseTokens = *(queryToken.suchThatClauseTokens);
    auto suchThatClauseToken = suchThatClauseTokens[0];
    std::vector<std::string> expectedArguments = std::vector<std::string>({"v", "_"});

    CHECK(suchThatClauseToken.relRef == "Modifies");
    CHECK(*(suchThatClauseToken.arguments) == expectedArguments);
}

TEST_CASE ("QP TOKENIZER: MODIFIES SUCH THAT CLAUSE WITH SPACES AND TABS BETWEEN FIRST ARGUMENT AND COMMA") {
    std::string firstQuery = "variable v; \n Select v such that Modifies(v \t \t , _)";
    firstQuery = Tokenizer::lexicalTokens(firstQuery);
    Tokenizer tokenizer = Tokenizer();
    QueryToken queryToken = tokenizer.getQueryToken(firstQuery);

    // Check SuchThatClause Token
    auto suchThatClauseTokens = *(queryToken.suchThatClauseTokens);
    auto suchThatClauseToken = suchThatClauseTokens[0];
    std::vector<std::string> expectedArguments = std::vector<std::string>({"v", "_"});

    CHECK(suchThatClauseToken.relRef == "Modifies");
    CHECK(*(suchThatClauseToken.arguments) == expectedArguments);
}

TEST_CASE ("QP TOKENIZER: MODIFIES SUCH THAT CLAUSE WITH SPACES AND TABS BETWEEN COMMA AND SECOND ARGUMENT") {
    std::string firstQuery = "variable v; \n Select v such that Modifies(v,\t \t  _)";
    firstQuery = Tokenizer::lexicalTokens(firstQuery);
    Tokenizer tokenizer = Tokenizer();
    QueryToken queryToken = tokenizer.getQueryToken(firstQuery);

    // Check SuchThatClause Token
    auto suchThatClauseTokens = *(queryToken.suchThatClauseTokens);
    auto suchThatClauseToken = suchThatClauseTokens[0];
    std::vector<std::string> expectedArguments = std::vector<std::string>({"v", "_"});

    CHECK(suchThatClauseToken.relRef == "Modifies");
    CHECK(*(suchThatClauseToken.arguments) == expectedArguments);
}

TEST_CASE ("QP TOKENIZER: MODIFIES SUCH THAT CLAUSE WITH SPACES AND TABS BETWEEN SECOND ARGUMENT AND ')'") {
    std::string firstQuery = "variable v; \n Select v such that Modifies(v, _\t \t )";
    firstQuery = Tokenizer::lexicalTokens(firstQuery);
    Tokenizer tokenizer = Tokenizer();
    QueryToken queryToken = tokenizer.getQueryToken(firstQuery);

    // Check SuchThatClause Token
    auto suchThatClauseTokens = *(queryToken.suchThatClauseTokens);
    auto suchThatClauseToken = suchThatClauseTokens[0];
    std::vector<std::string> expectedArguments = std::vector<std::string>({"v", "_"});

    CHECK(suchThatClauseToken.relRef == "Modifies");
    CHECK(*(suchThatClauseToken.arguments) == expectedArguments);
}

TEST_CASE ("QP TOKENIZER: MODIFIES SUCH THAT CLAUSE WITH SPACES AND TABS BETWEEN RELATIONSHIP AND AND") {
    std::string firstQuery = "variable v; \n Select v such that Modifies(v, _)  \t \t and Next(3, 2)";
    firstQuery = Tokenizer::lexicalTokens(firstQuery);
    Tokenizer tokenizer = Tokenizer();
    QueryToken queryToken = tokenizer.getQueryToken(firstQuery);

    // Check SuchThatClause Token
    auto suchThatClauseTokens = *(queryToken.suchThatClauseTokens);
    auto suchThatClauseToken = suchThatClauseTokens[0];
    std::vector<std::string> expectedArguments = std::vector<std::string>({"v", "_"});

    CHECK(suchThatClauseToken.relRef == "Modifies");
    CHECK(*(suchThatClauseToken.arguments) == expectedArguments);
}

TEST_CASE ("QP TOKENIZER: ASSIGN PATTERN") {
    std::string firstQuery = "assign a; \nSelect a pattern a(_, _)";
    firstQuery = Tokenizer::lexicalTokens(firstQuery);
    Tokenizer tokenizer = Tokenizer();
    QueryToken queryToken = tokenizer.getQueryToken(firstQuery);

    // Check declarations
    std::map<std::string, std::string> expectedDeclarationTokens({{"a", "assign"}});
    std::vector<std::string> expectedDeclarationNames({"a"});
    std::vector<std::string> expectedDesignEntities({"assign"});

    auto declarationTokens = *(queryToken.declarationTokens);
    auto declarations = *(queryToken.declarations);
    auto declarationNames = declarations.first;
    auto designEntities = declarations.second;

    CHECK(declarationTokens == expectedDeclarationTokens);
    CHECK(declarationNames == expectedDeclarationNames);
    CHECK(designEntities == expectedDesignEntities);

    // Check Synonym
    std::string expectedSynonym = "a";
    auto synonym = *queryToken.selectClauseTokens;

    CHECK(synonym[0] == expectedSynonym);

    // Check Such That Clauses
    auto suchThatClauseTokens = queryToken.suchThatClauseTokens;

    CHECK(suchThatClauseTokens->empty());

    // Check Pattern
    std::vector<std::string> expectedArguments = std::vector<std::string>({"_", "_"});
    auto patternTokens = *(queryToken.patternTokens);
    auto patternToken = patternTokens[0];

    CHECK(patternToken.synonym == "a");
    CHECK(*(patternToken.arguments) == expectedArguments);
}

TEST_CASE ("QP TOKENIZER: PATTERN WITH SYNONYM ARGUMENT") {
    std::string firstQuery = "assign a; variable v; \nSelect a pattern a(v, _)";
    firstQuery = Tokenizer::lexicalTokens(firstQuery);
    Tokenizer tokenizer = Tokenizer();
    QueryToken queryToken = tokenizer.getQueryToken(firstQuery);

    // Check Pattern
    std::vector<std::string> expectedArguments = std::vector<std::string>({"v", "_"});
    auto patternTokens = *(queryToken.patternTokens);
    auto patternToken = patternTokens[0];

    CHECK(patternToken.synonym == "a");
    CHECK(*(patternToken.arguments) == expectedArguments);
}

TEST_CASE ("QP TOKENIZER: PATTERN WITH IDENT ARGUMENT") {
    std::string firstQuery = "assign a; variable v; \nSelect a pattern a(\"x\", _)";
    firstQuery = Tokenizer::lexicalTokens(firstQuery);
    Tokenizer tokenizer = Tokenizer();
    QueryToken queryToken = tokenizer.getQueryToken(firstQuery);

    // Check Pattern
    std::vector<std::string> expectedArguments = std::vector<std::string>({"\"x\"", "_"});
    auto patternTokens = *(queryToken.patternTokens);
    auto patternToken = patternTokens[0];

    CHECK(patternToken.synonym == "a");
    CHECK(*(patternToken.arguments) == expectedArguments);
}

TEST_CASE ("QP TOKENIZER: IF PATTERN WITH 3 WILDCARD ARGUMENTS") {
    std::string firstQuery = "if ifs; variable v; \nSelect a pattern ifs(_, _, _)";
    firstQuery = Tokenizer::lexicalTokens(firstQuery);
    Tokenizer tokenizer = Tokenizer();
    QueryToken queryToken = tokenizer.getQueryToken(firstQuery);

    // Check Pattern
    std::vector<std::string> expectedArguments = std::vector<std::string>({"_", "_", "_"});
    auto patternTokens = *(queryToken.patternTokens);
    auto patternToken = patternTokens[0];

    CHECK(patternToken.synonym == "ifs");
    CHECK(*(patternToken.arguments) == expectedArguments);
}

TEST_CASE ("QP TOKENIZER: PATTERN WITH DOUBLE CHAR SYN-ASSIGN") {
    std::string firstQuery = "assign as; variable v; \nSelect as pattern as (\"x\", _)";
    firstQuery = Tokenizer::lexicalTokens(firstQuery);
    Tokenizer tokenizer = Tokenizer();
    QueryToken queryToken = tokenizer.getQueryToken(firstQuery);

    // Check Pattern
    std::vector<std::string> expectedArguments = std::vector<std::string>({"\"x\"", "_"});
    auto patternTokens = *(queryToken.patternTokens);
    auto patternToken = patternTokens[0];

    CHECK(patternToken.synonym == "as");
    CHECK(*(patternToken.arguments) == expectedArguments);
}

TEST_CASE ("QP TOKENIZER: PATTERN WITH DOUBLE CHAR AND INT SYN-ASSIGN") {
    std::string firstQuery = "assign as1; variable v; \nSelect as1 pattern as1 (\"x\", _)";
    firstQuery = Tokenizer::lexicalTokens(firstQuery);
    Tokenizer tokenizer = Tokenizer();
    QueryToken queryToken = tokenizer.getQueryToken(firstQuery);

    // Check Pattern
    std::vector<std::string> expectedArguments = std::vector<std::string>({"\"x\"", "_"});
    auto patternTokens = *(queryToken.patternTokens);
    auto patternToken = patternTokens[0];

    CHECK(patternToken.synonym == "as1");
    CHECK(*(patternToken.arguments) == expectedArguments);
}

TEST_CASE ("QP TOKENIZER: PATTERN WITH SELECT AS SYN-ASSIGN") {
    std::string firstQuery = "assign Select; variable v; \nSelect Select pattern Select (\"x\", _)";
    firstQuery = Tokenizer::lexicalTokens(firstQuery);
    Tokenizer tokenizer = Tokenizer();
    QueryToken queryToken = tokenizer.getQueryToken(firstQuery);

    // Check Pattern
    std::vector<std::string> expectedArguments = std::vector<std::string>({"\"x\"", "_"});
    auto patternTokens = *(queryToken.patternTokens);
    auto patternToken = patternTokens[0];

    CHECK(patternToken.synonym == "Select");
    CHECK(*(patternToken.arguments) == expectedArguments);
}

TEST_CASE ("QP TOKENIZER: PATTERN WITH PATTERN AS SYNONYM") {
    std::string firstQuery = "assign pattern; variable v; \nSelect pattern pattern pattern (\"x\", _)";
    firstQuery = Tokenizer::lexicalTokens(firstQuery);
    Tokenizer tokenizer = Tokenizer();
    QueryToken queryToken = tokenizer.getQueryToken(firstQuery);

    // Check Pattern
    std::vector<std::string> expectedArguments = std::vector<std::string>({"\"x\"", "_"});
    auto patternTokens = *(queryToken.patternTokens);
    auto patternToken = patternTokens[0];

    CHECK(patternToken.synonym == "pattern");
    CHECK(*(patternToken.arguments) == expectedArguments);
}

TEST_CASE ("QP TOKENIZER: PATTERN WITH PATTERN AS SYN-ASSIGN") {
    std::string firstQuery = "assign pattern, a; \nSelect a pattern pattern (\"x\", _)";
    firstQuery = Tokenizer::lexicalTokens(firstQuery);
    Tokenizer tokenizer = Tokenizer();
    QueryToken queryToken = tokenizer.getQueryToken(firstQuery);

    // Check Pattern
    std::vector<std::string> expectedArguments = std::vector<std::string>({"\"x\"", "_"});
    auto patternTokens = *(queryToken.patternTokens);
    auto patternToken = patternTokens[0];

    CHECK(patternToken.synonym == "pattern");
    CHECK(*(patternToken.arguments) == expectedArguments);
}

TEST_CASE ("QP TOKENIZER: PATTERN WITH PROCNAME AS SYN-ASSIGN") {
    std::string firstQuery = "assign procName, a; \nSelect a pattern procName (\"x\", _)";
    firstQuery = Tokenizer::lexicalTokens(firstQuery);
    Tokenizer tokenizer = Tokenizer();
    QueryToken queryToken = tokenizer.getQueryToken(firstQuery);

    // Check Pattern
    std::vector<std::string> expectedArguments = std::vector<std::string>({"\"x\"", "_"});
    auto patternTokens = *(queryToken.patternTokens);
    auto patternToken = patternTokens[0];

    CHECK(patternToken.synonym == "procName");
    CHECK(*(patternToken.arguments) == expectedArguments);
}

TEST_CASE ("QP TOKENIZER: PATTERN WITH VARNAME AS SYN-ASSIGN") {
    std::string firstQuery = "assign varName, a; \nSelect a pattern varName (\"x\", _)";
    firstQuery = Tokenizer::lexicalTokens(firstQuery);
    Tokenizer tokenizer = Tokenizer();
    QueryToken queryToken = tokenizer.getQueryToken(firstQuery);

    // Check Pattern
    std::vector<std::string> expectedArguments = std::vector<std::string>({"\"x\"", "_"});
    auto patternTokens = *(queryToken.patternTokens);
    auto patternToken = patternTokens[0];

    CHECK(patternToken.synonym == "varName");
    CHECK(*(patternToken.arguments) == expectedArguments);
}

TEST_CASE ("QP TOKENIZER: PATTERN WITH VALUE AS SYN-ASSIGN") {
    std::string firstQuery = "assign value, a; \nSelect a pattern value (\"x\", _)";
    firstQuery = Tokenizer::lexicalTokens(firstQuery);
    Tokenizer tokenizer = Tokenizer();
    QueryToken queryToken = tokenizer.getQueryToken(firstQuery);

    // Check Pattern
    std::vector<std::string> expectedArguments = std::vector<std::string>({"\"x\"", "_"});
    auto patternTokens = *(queryToken.patternTokens);
    auto patternToken = patternTokens[0];

    CHECK(patternToken.synonym == "value");
    CHECK(*(patternToken.arguments) == expectedArguments);
}

TEST_CASE ("QP TOKENIZER: PATTERN WITH 'WITH' AS SYN-ASSIGN") {
    std::string firstQuery = "assign with, a; \nSelect a pattern with (\"x\", _)";
    firstQuery = Tokenizer::lexicalTokens(firstQuery);
    Tokenizer tokenizer = Tokenizer();
    QueryToken queryToken = tokenizer.getQueryToken(firstQuery);

    // Check Pattern
    std::vector<std::string> expectedArguments = std::vector<std::string>({"\"x\"", "_"});
    auto patternTokens = *(queryToken.patternTokens);
    auto patternToken = patternTokens[0];

    CHECK(patternToken.synonym == "with");
    CHECK(*(patternToken.arguments) == expectedArguments);
}

TEST_CASE ("QP TOKENIZER: PATTERN WITH 'AND' AS SYN-ASSIGN") {
    std::string firstQuery = "assign and, a; \nSelect a pattern and (\"x\", _)";
    firstQuery = Tokenizer::lexicalTokens(firstQuery);
    Tokenizer tokenizer = Tokenizer();
    QueryToken queryToken = tokenizer.getQueryToken(firstQuery);

    // Check Pattern
    std::vector<std::string> expectedArguments = std::vector<std::string>({"\"x\"", "_"});
    auto patternTokens = *(queryToken.patternTokens);
    auto patternToken = patternTokens[0];

    CHECK(patternToken.synonym == "and");
    CHECK(*(patternToken.arguments) == expectedArguments);
}

TEST_CASE ("QP TOKENIZER: PATTERN WITH 'FOLLOWS' AS SYN-ASSIGN") {
    std::string firstQuery = "assign Follows, a; \nSelect a pattern Follows (a, _)";
    firstQuery = Tokenizer::lexicalTokens(firstQuery);
    Tokenizer tokenizer = Tokenizer();
    QueryToken queryToken = tokenizer.getQueryToken(firstQuery);

    // Check Pattern
    std::vector<std::string> expectedArguments = std::vector<std::string>({"a", "_"});
    auto patternTokens = *(queryToken.patternTokens);
    auto suchThatClauseTokens = *(queryToken.suchThatClauseTokens);
    auto patternToken = patternTokens[0];

    CHECK(patternToken.synonym == "Follows");
    CHECK(*(patternToken.arguments) == expectedArguments);

    CHECK(suchThatClauseTokens.size() == 0);
}

// Check multiple pattern optimizeQueryClauses
TEST_CASE ("QP TOKENIZER: MULTIPLE PATTERN CLAUSES WITH AND") {
    std::string firstQuery = "assign a1, a2, a3; \nSelect a1 pattern a1 (\"x\", _) and a2(_, _) and a3(_, _, _)";
    firstQuery = Tokenizer::lexicalTokens(firstQuery);
    Tokenizer tokenizer = Tokenizer();
    QueryToken queryToken = tokenizer.getQueryToken(firstQuery);

    // Check first Pattern
    std::vector<std::string> expectedArguments = std::vector<std::string>({"\"x\"", "_"});
    auto patternTokens = *(queryToken.patternTokens);
    auto patternToken = patternTokens[0];

    CHECK(patternToken.synonym == "a1");
    CHECK(*(patternToken.arguments) == expectedArguments);

    // Check second Pattern
    expectedArguments = std::vector<std::string>({"_", "_"});
    patternTokens = *(queryToken.patternTokens);
    patternToken = patternTokens[1];

    CHECK(patternToken.synonym == "a2");
    CHECK(*(patternToken.arguments) == expectedArguments);

    // Check third Pattern
    expectedArguments = std::vector<std::string>({"_", "_", "_"});
    patternTokens = *(queryToken.patternTokens);
    patternToken = patternTokens[2];

    CHECK(patternToken.synonym == "a3");
    CHECK(*(patternToken.arguments) == expectedArguments);
}

TEST_CASE ("QP TOKENIZER: MULTIPLE PATTERN CLAUSES") {
    std::string firstQuery = "assign a1, a2, a3; \nSelect a1 pattern a1 (\"x\", _) pattern a2(_, _) pattern a3(_, _, _)";
    firstQuery = Tokenizer::lexicalTokens(firstQuery);
    Tokenizer tokenizer = Tokenizer();
    QueryToken queryToken = tokenizer.getQueryToken(firstQuery);

    // Check first Pattern
    std::vector<std::string> expectedArguments = std::vector<std::string>({"\"x\"", "_"});
    auto patternTokens = *(queryToken.patternTokens);
    auto patternToken = patternTokens[0];

    CHECK(patternToken.synonym == "a1");
    CHECK(*(patternToken.arguments) == expectedArguments);

    // Check second Pattern
    expectedArguments = std::vector<std::string>({"_", "_"});
    patternTokens = *(queryToken.patternTokens);
    patternToken = patternTokens[1];

    CHECK(patternToken.synonym == "a2");
    CHECK(*(patternToken.arguments) == expectedArguments);

    // Check third Pattern
    expectedArguments = std::vector<std::string>({"_", "_", "_"});
    patternTokens = *(queryToken.patternTokens);
    patternToken = patternTokens[2];

    CHECK(patternToken.synonym == "a3");
    CHECK(*(patternToken.arguments) == expectedArguments);
}

TEST_CASE ("QP TOKENIZER: MULTIPLE PATTERN CLAUSES AND PATTERN") {
    std::string firstQuery = "assign a1, a2, a3; \nSelect a1 pattern a1 (\"x\", _) and a2(_, _) pattern a3(_, _, _)";
    firstQuery = Tokenizer::lexicalTokens(firstQuery);
    Tokenizer tokenizer = Tokenizer();
    QueryToken queryToken = tokenizer.getQueryToken(firstQuery);

    // Check first Pattern
    std::vector<std::string> expectedArguments = std::vector<std::string>({"\"x\"", "_"});
    auto patternTokens = *(queryToken.patternTokens);
    auto patternToken = patternTokens[0];

    CHECK(patternToken.synonym == "a1");
    CHECK(*(patternToken.arguments) == expectedArguments);

    // Check second Pattern
    expectedArguments = std::vector<std::string>({"_", "_"});
    patternTokens = *(queryToken.patternTokens);
    patternToken = patternTokens[1];

    CHECK(patternToken.synonym == "a2");
    CHECK(*(patternToken.arguments) == expectedArguments);

    // Check third Pattern
    expectedArguments = std::vector<std::string>({"_", "_", "_"});
    patternTokens = *(queryToken.patternTokens);
    patternToken = patternTokens[2];

    CHECK(patternToken.synonym == "a3");
    CHECK(*(patternToken.arguments) == expectedArguments);
}

TEST_CASE ("QP TOKENIZER: MULTIPLE PATTERN CLAUSES AND PATTERN WITH AND AS SYNONYM") {
    std::string firstQuery = "assign a1, and, a3; \nSelect a1 pattern a1 (\"x\", _) and and(_, _) pattern a3(_, _, _)";
    firstQuery = Tokenizer::lexicalTokens(firstQuery);
    Tokenizer tokenizer = Tokenizer();
    QueryToken queryToken = tokenizer.getQueryToken(firstQuery);

    // Check first Pattern
    std::vector<std::string> expectedArguments = std::vector<std::string>({"\"x\"", "_"});
    auto patternTokens = *(queryToken.patternTokens);
    auto patternToken = patternTokens[0];

    CHECK(patternToken.synonym == "a1");
    CHECK(*(patternToken.arguments) == expectedArguments);

    // Check second Pattern
    expectedArguments = std::vector<std::string>({"_", "_"});
    patternTokens = *(queryToken.patternTokens);
    patternToken = patternTokens[1];

    CHECK(patternToken.synonym == "and");
    CHECK(*(patternToken.arguments) == expectedArguments);

    // Check third Pattern
    expectedArguments = std::vector<std::string>({"_", "_", "_"});
    patternTokens = *(queryToken.patternTokens);
    patternToken = patternTokens[2];

    CHECK(patternToken.synonym == "a3");
    CHECK(*(patternToken.arguments) == expectedArguments);
}

TEST_CASE ("QP TOKENIZER: PATTERN WITH SPACES AND TABS IN BETWEEN PATTERN AND SYNONYM") {
    std::string firstQuery = "assign a; \nSelect a pattern \t   \t  \ta (\"x\", _)";
    firstQuery = Tokenizer::lexicalTokens(firstQuery);
    Tokenizer tokenizer = Tokenizer();
    QueryToken queryToken = tokenizer.getQueryToken(firstQuery);

    // Check Pattern
    std::vector<std::string> expectedArguments = std::vector<std::string>({"\"x\"", "_"});
    auto patternTokens = *(queryToken.patternTokens);
    auto patternToken = patternTokens[0];

    CHECK(patternToken.synonym == "a");
    CHECK(*(patternToken.arguments) == expectedArguments);
}

TEST_CASE ("QP TOKENIZER: PATTERN WITH SPACES AND TABS IN BETWEEN SYNONYM AND '('") {
    std::string firstQuery = "assign a; \nSelect a pattern a\t   \t  \t(\"x\", _)";
    firstQuery = Tokenizer::lexicalTokens(firstQuery);
    Tokenizer tokenizer = Tokenizer();
    QueryToken queryToken = tokenizer.getQueryToken(firstQuery);

    // Check Pattern
    std::vector<std::string> expectedArguments = std::vector<std::string>({"\"x\"", "_"});
    auto patternTokens = *(queryToken.patternTokens);
    auto patternToken = patternTokens[0];

    CHECK(patternToken.synonym == "a");
    CHECK(*(patternToken.arguments) == expectedArguments);
}

TEST_CASE ("QP TOKENIZER: PATTERN WITH SPACES AND TABS IN BETWEEN '(' AND FIRST ARGUMENT") {
    std::string firstQuery = "assign a; \nSelect a pattern a(\t   \t  \t\"x\", _)";
    firstQuery = Tokenizer::lexicalTokens(firstQuery);
    Tokenizer tokenizer = Tokenizer();
    QueryToken queryToken = tokenizer.getQueryToken(firstQuery);

    // Check Pattern
    std::vector<std::string> expectedArguments = std::vector<std::string>({"\"x\"", "_"});
    auto patternTokens = *(queryToken.patternTokens);
    auto patternToken = patternTokens[0];

    CHECK(patternToken.synonym == "a");
    CHECK(*(patternToken.arguments) == expectedArguments);
}

TEST_CASE ("QP TOKENIZER: PATTERN WITH SPACES AND TABS IN BETWEEN FIRST ARGUMENT AND ','") {
    std::string firstQuery = "assign a; \nSelect a pattern a(\"x\"\t   \t  \t, _)";
    firstQuery = Tokenizer::lexicalTokens(firstQuery);
    Tokenizer tokenizer = Tokenizer();
    QueryToken queryToken = tokenizer.getQueryToken(firstQuery);

    // Check Pattern
    std::vector<std::string> expectedArguments = std::vector<std::string>({"\"x\"", "_"});
    auto patternTokens = *(queryToken.patternTokens);
    auto patternToken = patternTokens[0];

    CHECK(patternToken.synonym == "a");
    CHECK(*(patternToken.arguments) == expectedArguments);
}

TEST_CASE ("QP TOKENIZER: PATTERN WITH SPACES AND TABS IN BETWEEN ',' AND SECOND ARGUMENT") {
    std::string firstQuery = "assign a; \nSelect a pattern a(\"x\",\t   \t  \t _)";
    firstQuery = Tokenizer::lexicalTokens(firstQuery);
    Tokenizer tokenizer = Tokenizer();
    QueryToken queryToken = tokenizer.getQueryToken(firstQuery);

    // Check Pattern
    std::vector<std::string> expectedArguments = std::vector<std::string>({"\"x\"", "_"});
    auto patternTokens = *(queryToken.patternTokens);
    auto patternToken = patternTokens[0];

    CHECK(patternToken.synonym == "a");
    CHECK(*(patternToken.arguments) == expectedArguments);
}

TEST_CASE ("QP TOKENIZER: PATTERN WITH SPACES AND TABS IN BETWEEN SECOND ARGUMENT AND ')'") {
    std::string firstQuery = "assign a; \nSelect a pattern a(\"x\", _\t   \t  \t)";
    firstQuery = Tokenizer::lexicalTokens(firstQuery);
    Tokenizer tokenizer = Tokenizer();
    QueryToken queryToken = tokenizer.getQueryToken(firstQuery);

    // Check Pattern
    std::vector<std::string> expectedArguments = std::vector<std::string>({"\"x\"", "_"});
    auto patternTokens = *(queryToken.patternTokens);
    auto patternToken = patternTokens[0];

    CHECK(patternToken.synonym == "a");
    CHECK(*(patternToken.arguments) == expectedArguments);
}

TEST_CASE ("QP TOKENIZER: PATTERN WITH SPACES AND TABS IN BETWEEN ')' AND AND") {
    std::string firstQuery = "assign a; \nSelect a pattern a(\"x\", _)\t   \t  \tand a(_, _)";
    firstQuery = Tokenizer::lexicalTokens(firstQuery);
    Tokenizer tokenizer = Tokenizer();
    QueryToken queryToken = tokenizer.getQueryToken(firstQuery);

    // Check first Pattern
    std::vector<std::string> expectedArguments = std::vector<std::string>({"\"x\"", "_"});
    auto patternTokens = *(queryToken.patternTokens);
    auto patternToken = patternTokens[0];

    CHECK(patternToken.synonym == "a");
    CHECK(*(patternToken.arguments) == expectedArguments);

    // Check second Pattern
    expectedArguments = std::vector<std::string>({"_", "_"});
    patternTokens = *(queryToken.patternTokens);
    patternToken = patternTokens[1];

    CHECK(patternToken.synonym == "a");
    CHECK(*(patternToken.arguments) == expectedArguments);
}

TEST_CASE ("QP TOKENIZER: PATTERN WITH SPACES AND TABS IN BETWEEN AND AND SYNONYM") {
    std::string firstQuery = "assign a; \nSelect a pattern a(\"x\", _) and\t   \t  \ta(_, _)";
    firstQuery = Tokenizer::lexicalTokens(firstQuery);
    Tokenizer tokenizer = Tokenizer();
    QueryToken queryToken = tokenizer.getQueryToken(firstQuery);

    // Check first Pattern
    std::vector<std::string> expectedArguments = std::vector<std::string>({"\"x\"", "_"});
    auto patternTokens = *(queryToken.patternTokens);
    auto patternToken = patternTokens[0];

    CHECK(patternToken.synonym == "a");
    CHECK(*(patternToken.arguments) == expectedArguments);

    // Check second Pattern
    expectedArguments = std::vector<std::string>({"_", "_"});
    patternTokens = *(queryToken.patternTokens);
    patternToken = patternTokens[1];

    CHECK(patternToken.synonym == "a");
    CHECK(*(patternToken.arguments) == expectedArguments);
}

// Check With Clauses
TEST_CASE ("QP TOKENIZER: WITH CLAUSES") {
    Tokenizer tokenizer = Tokenizer();

    // PROCNAME AND PROCNAME
    std::string firstQuery = "procedure p1, p2; \nSelect p1 with p1.procName = p2.procName";
    firstQuery = Tokenizer::lexicalTokens(firstQuery);
    QueryToken queryToken = tokenizer.getQueryToken(firstQuery);

    // Check With Clause
    std::pair<std::string, std::string> expectedArguments = std::pair<std::string, std::string>("p1.procName", "p2.procName");
    auto withClauses = *(queryToken.withClauses);

    CHECK(withClauses[0] == expectedArguments);

    // PROCNAME AND VARNAME
    firstQuery = "procedure p1, p2; \nSelect p1 with p1.procName = p2.varName";
    queryToken = tokenizer.getQueryToken(firstQuery);

    // Check With Clause
    expectedArguments = std::pair<std::string, std::string>("p1.procName", "p2.varName");
    withClauses = *(queryToken.withClauses);

    CHECK(withClauses[0] == expectedArguments);

    // PROCNAME AND VALUE
    firstQuery = "procedure p1, p2; \nSelect p1 with p1.procName = p2.value";
    tokenizer = Tokenizer();
    queryToken = tokenizer.getQueryToken(firstQuery);

    // Check With Clause
    expectedArguments = std::pair<std::string, std::string>("p1.procName", "p2.value");
    withClauses = *(queryToken.withClauses);

    CHECK(withClauses[0] == expectedArguments);

    // PROCNAME AND STMT#
    firstQuery = "procedure p1, p2; \nSelect p1 with p1.procName = p2.stmt#";
    queryToken = tokenizer.getQueryToken(firstQuery);

    // Check With Clause
    expectedArguments = std::pair<std::string, std::string>("p1.procName", "p2.stmt#");
    withClauses = *(queryToken.withClauses);

    CHECK(withClauses[0] == expectedArguments);

    // PROCNAME AND INT
    firstQuery = "procedure p1, p2; \nSelect p1 with p1.procName = 3";
    queryToken = tokenizer.getQueryToken(firstQuery);

    // Check With Clause
    expectedArguments = std::pair<std::string, std::string>("p1.procName", "3");
    withClauses = *(queryToken.withClauses);

    CHECK(withClauses[0] == expectedArguments);

    // PROCNAME AND IDENT
    firstQuery = "procedure p1, p2; \nSelect p1 with p1.procName = \"x\"";
    queryToken = tokenizer.getQueryToken(firstQuery);

    // Check With Clause
    expectedArguments = std::pair<std::string, std::string>("p1.procName", "\"x\"");
    withClauses = *(queryToken.withClauses);

    CHECK(withClauses[0] == expectedArguments);

    // SYNONYM NAME PROCNAME
    firstQuery = "procedure procName; \nSelect procName with procName.procName = \"x\"";
    queryToken = tokenizer.getQueryToken(firstQuery);

    // Check With Clause
    expectedArguments = std::pair<std::string, std::string>("procName.procName", "\"x\"");
    withClauses = *(queryToken.withClauses);

    CHECK(withClauses[0] == expectedArguments);
}

TEST_CASE ("QP TOKENIZER: WITH CLAUSE - SYNONYM NAME VARNAME") {
    std::string firstQuery = "procedure varName; \nSelect procName with procName.varName = \"x\"";
    firstQuery = Tokenizer::lexicalTokens(firstQuery);
    Tokenizer tokenizer = Tokenizer();
    QueryToken queryToken = tokenizer.getQueryToken(firstQuery);

    // Check With Clause
    std::pair<std::string, std::string> expectedArguments = std::pair<std::string, std::string>("procName.varName", "\"x\"");
    auto withClauses = *(queryToken.withClauses);

    CHECK(withClauses[0] == expectedArguments);
}

TEST_CASE ("QP TOKENIZER: WITH CLAUSE - SYNONYM NAME VALUE") {
    std::string firstQuery = "procedure value; \nSelect procName with procName.value = \"x\"";
    firstQuery = Tokenizer::lexicalTokens(firstQuery);
    Tokenizer tokenizer = Tokenizer();
    QueryToken queryToken = tokenizer.getQueryToken(firstQuery);

    // Check With Clause
    std::pair<std::string, std::string> expectedArguments = std::pair<std::string, std::string>("procName.value", "\"x\"");
    auto withClauses = *(queryToken.withClauses);

    CHECK(withClauses[0] == expectedArguments);
}

TEST_CASE ("QP TOKENIZER: WITH CLAUSE - SYNONYM NAME SELECT") {
    std::string firstQuery = "procedure Select, p; \nSelect p with Select.value = \"x\"";
    firstQuery = Tokenizer::lexicalTokens(firstQuery);
    Tokenizer tokenizer = Tokenizer();
    QueryToken queryToken = tokenizer.getQueryToken(firstQuery);

    // Check With Clause
    std::pair<std::string, std::string> expectedArguments = std::pair<std::string, std::string>("Select.value", "\"x\"");
    auto withClauses = *(queryToken.withClauses);

    CHECK(withClauses[0] == expectedArguments);
}

TEST_CASE ("QP TOKENIZER: WITH CLAUSE - SYNONYM NAME PATTERN") {
    std::string firstQuery = "procedure pattern, p; \nSelect p with pattern.value = \"x\"";
    firstQuery = Tokenizer::lexicalTokens(firstQuery);
    Tokenizer tokenizer = Tokenizer();
    QueryToken queryToken = tokenizer.getQueryToken(firstQuery);

    // Check With Clause
    std::pair<std::string, std::string> expectedArguments = std::pair<std::string, std::string>("pattern.value", "\"x\"");
    auto withClauses = *(queryToken.withClauses);

    CHECK(withClauses[0] == expectedArguments);
}

TEST_CASE ("QP TOKENIZER: WITH CLAUSE - SYNONYM NAME WITH") {
    std::string firstQuery = "procedure with, p; \nSelect p with with.value = \"x\"";
    firstQuery = Tokenizer::lexicalTokens(firstQuery);
    Tokenizer tokenizer = Tokenizer();
    QueryToken queryToken = tokenizer.getQueryToken(firstQuery);

    // Check With Clause
    std::pair<std::string, std::string> expectedArguments = std::pair<std::string, std::string>("with.value", "\"x\"");
    auto withClauses = *(queryToken.withClauses);

    CHECK(withClauses[0] == expectedArguments);
}

TEST_CASE ("QP TOKENIZER: WITH CLAUSE - SYNONYM NAME AND") {
    std::string firstQuery = "procedure and, p; \nSelect p with and.value = \"x\"";
    firstQuery = Tokenizer::lexicalTokens(firstQuery);
    Tokenizer tokenizer = Tokenizer();
    QueryToken queryToken = tokenizer.getQueryToken(firstQuery);

    // Check With Clause
    std::pair<std::string, std::string> expectedArguments = std::pair<std::string, std::string>("and.value", "\"x\"");
    auto withClauses = *(queryToken.withClauses);

    CHECK(withClauses[0] == expectedArguments);
}

TEST_CASE ("QP TOKENIZER: WITH CLAUSE - SYNONYM NAME FOLLOWS") {
    std::string firstQuery = "procedure Follows, p; \nSelect p with Follows.value = \"x\"";
    firstQuery = Tokenizer::lexicalTokens(firstQuery);
    Tokenizer tokenizer = Tokenizer();
    QueryToken queryToken = tokenizer.getQueryToken(firstQuery);

    // Check With Clause
    std::pair<std::string, std::string> expectedArguments = std::pair<std::string, std::string>("Follows.value", "\"x\"");
    auto withClauses = *(queryToken.withClauses);

    CHECK(withClauses[0] == expectedArguments);
}

TEST_CASE ("QP TOKENIZER: WITH CLAUSE: SPACES AND TABS AFTER WITH") {
    std::string firstQuery = "procedure p; \nSelect p with \t  \t  p.value = \"x\"";
    firstQuery = Tokenizer::lexicalTokens(firstQuery);
    Tokenizer tokenizer = Tokenizer();
    QueryToken queryToken = tokenizer.getQueryToken(firstQuery);

    // Check With Clause
    std::pair<std::string, std::string> expectedArguments = std::pair<std::string, std::string>("p.value", "\"x\"");
    auto withClauses = *(queryToken.withClauses);

    CHECK(withClauses[0] == expectedArguments);
}

TEST_CASE ("QP TOKENIZER: WITH CLAUSE: SPACES AND TABS AFTER synonym") {
    std::string firstQuery = "procedure p; \nSelect p with p\t  \t  .value = \"x\"";
    firstQuery = Tokenizer::lexicalTokens(firstQuery);
    Tokenizer tokenizer = Tokenizer();
    QueryToken queryToken = tokenizer.getQueryToken(firstQuery);

    // Check With Clause
    std::pair<std::string, std::string> expectedArguments = std::pair<std::string, std::string>("p.value", "\"x\"");
    auto withClauses = *(queryToken.withClauses);

    CHECK(withClauses[0] == expectedArguments);
}

TEST_CASE ("QP TOKENIZER: WITH CLAUSE: SPACES AND TABS AFTER '.'") {
    std::string firstQuery = "procedure p; \nSelect p with p.\t  \t  value = \"x\"";
    firstQuery = Tokenizer::lexicalTokens(firstQuery);
    Tokenizer tokenizer = Tokenizer();
    QueryToken queryToken = tokenizer.getQueryToken(firstQuery);

    // Check With Clause
    std::pair<std::string, std::string> expectedArguments = std::pair<std::string, std::string>("p.value", "\"x\"");
    auto withClauses = *(queryToken.withClauses);

    CHECK(withClauses[0] == expectedArguments);
}

TEST_CASE ("QP TOKENIZER: WITH CLAUSE: SPACES AND TABS BEFORE '='") {
    std::string firstQuery = "procedure p; \nSelect p with p.value\t  \t   = \"x\"";
    firstQuery = Tokenizer::lexicalTokens(firstQuery);
    Tokenizer tokenizer = Tokenizer();
    QueryToken queryToken = tokenizer.getQueryToken(firstQuery);

    // Check With Clause
    std::pair<std::string, std::string> expectedArguments = std::pair<std::string, std::string>("p.value", "\"x\"");
    auto withClauses = *(queryToken.withClauses);

    CHECK(withClauses[0] == expectedArguments);
}

TEST_CASE ("QP TOKENIZER: WITH CLAUSE: SPACES AND TABS AFTER '='") {
    std::string firstQuery = "procedure p; \nSelect p with p.value = \t  \t   \"x\"";
    firstQuery = Tokenizer::lexicalTokens(firstQuery);
    Tokenizer tokenizer = Tokenizer();
    QueryToken queryToken = tokenizer.getQueryToken(firstQuery);

    // Check With Clause
    std::pair<std::string, std::string> expectedArguments = std::pair<std::string, std::string>("p.value", "\"x\"");
    auto withClauses = *(queryToken.withClauses);

    CHECK(withClauses[0] == expectedArguments);
}

TEST_CASE ("QP TOKENIZER: WITH CLAUSE: NO SPACES AND TABS BEFORE AND AFTER '='") {
    std::string firstQuery = "procedure p; \nSelect p with p.value=\"x\"";
    firstQuery = Tokenizer::lexicalTokens(firstQuery);
    Tokenizer tokenizer = Tokenizer();
    QueryToken queryToken = tokenizer.getQueryToken(firstQuery);

    // Check With Clause
    std::pair<std::string, std::string> expectedArguments = std::pair<std::string, std::string>("p.value", "\"x\"");
    auto withClauses = *(queryToken.withClauses);

    CHECK(withClauses[0] == expectedArguments);
}

TEST_CASE ("QP TOKENIZER: MULTIPLE WITH CLAUSES AND") {
    std::string firstQuery = "procedure p1, p2; \nSelect p1 with p1.procName = \"x\" and p2.procName = p1.procName and p2.stmt# = 3";
    firstQuery = Tokenizer::lexicalTokens(firstQuery);
    Tokenizer tokenizer = Tokenizer();
    QueryToken queryToken = tokenizer.getQueryToken(firstQuery);

    // Check first With Clause
    std::pair<std::string, std::string> expectedArguments = std::pair<std::string, std::string>("p1.procName", "\"x\"");
    auto withClauses = *(queryToken.withClauses);
    CHECK(withClauses[0] == expectedArguments);

    // Check second With Clause
    expectedArguments = std::pair<std::string, std::string>("p2.procName", "p1.procName");
    CHECK(withClauses[1] == expectedArguments);

    // Check third With Clause
    expectedArguments = std::pair<std::string, std::string>("p2.stmt#", "3");
    CHECK(withClauses[2] == expectedArguments);
}

TEST_CASE ("QP TOKENIZER: MULTIPLE WITH CLAUSES WITHOUT AND") {
    std::string firstQuery = "procedure p1, p2; \nSelect p1 with p1.procName = \"x\" with p2.procName = p1.procName with p2.stmt# = 3";
    firstQuery = Tokenizer::lexicalTokens(firstQuery);
    Tokenizer tokenizer = Tokenizer();
    QueryToken queryToken = tokenizer.getQueryToken(firstQuery);

    // Check first With Clause
    std::pair<std::string, std::string> expectedArguments = std::pair<std::string, std::string>("p1.procName", "\"x\"");
    auto withClauses = *(queryToken.withClauses);
    CHECK(withClauses[0] == expectedArguments);

    // Check second With Clause
    expectedArguments = std::pair<std::string, std::string>("p2.procName", "p1.procName");
    CHECK(withClauses[1] == expectedArguments);

    // Check third With Clause
    expectedArguments = std::pair<std::string, std::string>("p2.stmt#", "3");
    CHECK(withClauses[2] == expectedArguments);
}

TEST_CASE ("QP TOKENIZER: MULTIPLE WITH CLAUSES AND AND") {
    std::string firstQuery = "procedure p1, p2; \nSelect p1 with p1.procName = \"x\" and p2.procName = p1.procName with p2.stmt# = 3";
    firstQuery = Tokenizer::lexicalTokens(firstQuery);
    Tokenizer tokenizer = Tokenizer();
    QueryToken queryToken = tokenizer.getQueryToken(firstQuery);

    // Check first With Clause
    std::pair<std::string, std::string> expectedArguments = std::pair<std::string, std::string>("p1.procName", "\"x\"");
    auto withClauses = *(queryToken.withClauses);
    CHECK(withClauses[0] == expectedArguments);

    // Check second With Clause
    expectedArguments = std::pair<std::string, std::string>("p2.procName", "p1.procName");
    CHECK(withClauses[1] == expectedArguments);

    // Check third With Clause
    expectedArguments = std::pair<std::string, std::string>("p2.stmt#", "3");
    CHECK(withClauses[2] == expectedArguments);
}

TEST_CASE ("QP TOKENIZER: MULTI CLAUSE TEST PATTERN FIRST THEN SUCH THAT CLAUSE") {
    std::string firstQuery = "assign a; \nSelect a pattern a(_, _) such that Follows(2, 1)";
    firstQuery = Tokenizer::lexicalTokens(firstQuery);
    Tokenizer tokenizer = Tokenizer();
    QueryToken queryToken = tokenizer.getQueryToken(firstQuery);

    // Check declarations
    std::map<std::string, std::string> expectedDeclarationTokens({{"a", "assign"}});
    std::vector<std::string> expectedDeclarationNames({"a"});
    std::vector<std::string> expectedDesignEntities({"assign"});

    auto declarationTokens = *(queryToken.declarationTokens);
    auto declarations = *(queryToken.declarations);
    auto declarationNames = declarations.first;
    auto designEntities = declarations.second;

    CHECK(declarationTokens == expectedDeclarationTokens);
    CHECK(declarationNames == expectedDeclarationNames);
    CHECK(designEntities == expectedDesignEntities);

    // Check Synonym
    std::string expectedSynonym = "a";
    auto synonyms = *queryToken.selectClauseTokens;

    CHECK(synonyms[0] == expectedSynonym);

    // Check Such That Clauses
    auto suchThatClauseTokens = *(queryToken.suchThatClauseTokens);
    auto suchThatClauseToken = suchThatClauseTokens[0];
    std::vector<std::string> expectedSuchThatArguments = std::vector<std::string>({"2", "1"});

    CHECK(suchThatClauseToken.relRef == "Follows");
    CHECK(*(suchThatClauseToken.arguments) == expectedSuchThatArguments);

    // Check Pattern
    std::vector<std::string> expectedArguments = std::vector<std::string>({"_", "_"});
    auto patternTokens = *(queryToken.patternTokens);
    auto patternToken = patternTokens[0];

    CHECK(patternToken.synonym == "a");
    CHECK(*(patternToken.arguments) == expectedArguments);
}

TEST_CASE ("QP TOKENIZER: MULTI CLAUSE TEST SUCH THAT CLAUSE FIRST THEN PATTERN") {
    std::string firstQuery = "assign a; \nSelect a such that Follows(2, 1) pattern a(_, _)";
    firstQuery = Tokenizer::lexicalTokens(firstQuery);
    Tokenizer tokenizer = Tokenizer();
    QueryToken queryToken = tokenizer.getQueryToken(firstQuery);

    // Check declarations
    std::map<std::string, std::string> expectedDeclarationTokens({{"a", "assign"}});
    std::vector<std::string> expectedDeclarationNames({"a"});
    std::vector<std::string> expectedDesignEntities({"assign"});

    auto declarationTokens = *(queryToken.declarationTokens);
    auto declarations = *(queryToken.declarations);
    auto declarationNames = declarations.first;
    auto designEntities = declarations.second;

    CHECK(declarationTokens == expectedDeclarationTokens);
    CHECK(declarationNames == expectedDeclarationNames);
    CHECK(designEntities == expectedDesignEntities);

    // Check Synonym
    std::string expectedSynonym = "a";
    auto synonyms = *queryToken.selectClauseTokens;

    CHECK(synonyms[0] == expectedSynonym);

    // Check Such That Clauses
    auto suchThatClauseTokens = *(queryToken.suchThatClauseTokens);
    auto suchThatClauseToken = suchThatClauseTokens[0];
    std::vector<std::string> expectedSuchThatArguments = std::vector<std::string>({"2", "1"});

    CHECK(suchThatClauseToken.relRef == "Follows");
    CHECK(*(suchThatClauseToken.arguments) == expectedSuchThatArguments);

    // Check Pattern
    std::vector<std::string> expectedArguments = std::vector<std::string>({"_", "_"});
    auto patternTokens = *(queryToken.patternTokens);
    auto patternToken = patternTokens[0];

    CHECK(patternToken.synonym == "a");
    CHECK(*(patternToken.arguments) == expectedArguments);
}

TEST_CASE ("QP TOKENIZER: MULTI CLAUSE TEST SUCH THAT CLAUSE FIRST THEN PATTERN WITH PATTERN AS SYN-ASSIGN") {
    std::string firstQuery = "assign pattern; \nSelect pattern such that Follows(2, 1) pattern pattern(_, _)";
    firstQuery = Tokenizer::lexicalTokens(firstQuery);
    Tokenizer tokenizer = Tokenizer();
    QueryToken queryToken = tokenizer.getQueryToken(firstQuery);

    // Check declarations
    std::map<std::string, std::string> expectedDeclarationTokens({{"pattern", "assign"}});
    std::vector<std::string> expectedDeclarationNames({"pattern"});
    std::vector<std::string> expectedDesignEntities({"assign"});

    auto declarationTokens = *(queryToken.declarationTokens);
    auto declarations = *(queryToken.declarations);
    auto declarationNames = declarations.first;
    auto designEntities = declarations.second;

    CHECK(declarationTokens == expectedDeclarationTokens);
    CHECK(declarationNames == expectedDeclarationNames);
    CHECK(designEntities == expectedDesignEntities);

    // Check Synonym
    std::string expectedSynonym = "pattern";
    auto synonyms = *queryToken.selectClauseTokens;

    CHECK(synonyms[0] == expectedSynonym);

    // Check Such That Clauses
    auto suchThatClauseTokens = *(queryToken.suchThatClauseTokens);
    auto suchThatClauseToken = suchThatClauseTokens[0];
    std::vector<std::string> expectedSuchThatArguments = std::vector<std::string>({"2", "1"});

    CHECK(suchThatClauseToken.relRef == "Follows");
    CHECK(*(suchThatClauseToken.arguments) == expectedSuchThatArguments);

    // Check Pattern
    std::vector<std::string> expectedArguments = std::vector<std::string>({"_", "_"});
    auto patternTokens = *(queryToken.patternTokens);
    auto patternToken = patternTokens[0];

    CHECK(patternToken.synonym == "pattern");
    CHECK(*(patternToken.arguments) == expectedArguments);
}

TEST_CASE ("QP TOKENIZER: MULTI CLAUSE TEST PATTERN FIRST THEN WITH CLAUSE") {
    std::string firstQuery = "assign a; procedure p1, p2; \nSelect a pattern a(_, _) with p1.procName=p2.procName";
    firstQuery = Tokenizer::lexicalTokens(firstQuery);
    Tokenizer tokenizer = Tokenizer();
    QueryToken queryToken = tokenizer.getQueryToken(firstQuery);

    // Check With Clauses
    auto withClauses = *(queryToken.withClauses);
    std::pair<std::string, std::string> expectedWithClause = std::pair<std::string, std::string>("p1.procName", "p2.procName");

    CHECK(withClauses[0] == expectedWithClause);

    // Check Pattern
    std::vector<std::string> expectedArguments = std::vector<std::string>({"_", "_"});
    auto patternTokens = *(queryToken.patternTokens);
    auto patternToken = patternTokens[0];

    CHECK(patternToken.synonym == "a");
    CHECK(*(patternToken.arguments) == expectedArguments);
}

TEST_CASE ("QP TOKENIZER: MULTI CLAUSE TEST WITH CLAUSE THEN SUCH THAT CLAUSE") {
    std::string firstQuery = "assign a; procedure p1, p2; \nSelect a with p1.procName=p2.procName such that Follows(2, 1)";
    firstQuery = Tokenizer::lexicalTokens(firstQuery);
    Tokenizer tokenizer = Tokenizer();
    QueryToken queryToken = tokenizer.getQueryToken(firstQuery);

    // Check With Clauses
    auto withClauses = *(queryToken.withClauses);
    std::pair<std::string, std::string> expectedWithClause = std::pair<std::string, std::string>("p1.procName", "p2.procName");

    CHECK(withClauses[0] == expectedWithClause);

    // Check Such That Clauses
    auto suchThatClauseTokens = *(queryToken.suchThatClauseTokens);
    auto suchThatClauseToken = suchThatClauseTokens[0];
    std::vector<std::string> expectedSuchThatArguments = std::vector<std::string>({"2", "1"});

    CHECK(suchThatClauseToken.relRef == "Follows");
    CHECK(*(suchThatClauseToken.arguments) == expectedSuchThatArguments);
}

TEST_CASE ("QP TOKENIZER: MULTI CLAUSE TEST PATTERN AND WITH CLAUSE AND SUCH THAT CLAUSE") {
    std::string firstQuery = "assign a; procedure p1, p2; \nSelect a pattern a(_, _) with p1.procName=p2.procName such that Follows(2, 1)";
    firstQuery = Tokenizer::lexicalTokens(firstQuery);
    Tokenizer tokenizer = Tokenizer();
    QueryToken queryToken = tokenizer.getQueryToken(firstQuery);

    // Check With Clauses
    auto withClauses = *(queryToken.withClauses);
    std::pair<std::string, std::string> expectedWithClause = std::pair<std::string, std::string>("p1.procName", "p2.procName");

    CHECK(withClauses[0] == expectedWithClause);

    // Check Pattern
    std::vector<std::string> expectedArguments = std::vector<std::string>({"_", "_"});
    auto patternTokens = *(queryToken.patternTokens);
    auto patternToken = patternTokens[0];

    CHECK(patternToken.synonym == "a");
    CHECK(*(patternToken.arguments) == expectedArguments);

    // Check Such That Clauses
    auto suchThatClauseTokens = *(queryToken.suchThatClauseTokens);
    auto suchThatClauseToken = suchThatClauseTokens[0];
    std::vector<std::string> expectedSuchThatArguments = std::vector<std::string>({"2", "1"});

    CHECK(suchThatClauseToken.relRef == "Follows");
    CHECK(*(suchThatClauseToken.arguments) == expectedSuchThatArguments);
}
