#include "catch.hpp"
#include "QP_Parser/Tokenizer.h"
#include "pql/query_obj/Argument.h"
#include <vector>
#include <string>
#include <map>
#include <iostream>

using namespace qp;

// Check declarations and select synonym parsing
TEST_CASE ("QP TOKENIZER: SINGLE VARIABLE DECLARATION-SINGLE CHAR") {
    std::string firstQuery = "variable v; \nSelect v";
    Tokenizer tokenizer = Tokenizer();
    QueryToken queryToken = tokenizer.getQueryToken(firstQuery);

    // Check declarations
    std::map<std::string, std::string> expectedDeclarationTokens({{"v", "variable"}});
    std::vector<std::string> expectedDeclarationNames({"v"});
    std::vector<std::string> expectedDesignEntities({"variable"});

    auto declarationTokens = *(queryToken.declarationTokens);
    auto declarations = *(queryToken.declarations);
    auto declarationNames = declarations.first;
    auto designEntities = declarations.second;

    CHECK(declarationTokens == expectedDeclarationTokens);
    CHECK(declarationNames == expectedDeclarationNames);
    CHECK(designEntities == expectedDesignEntities);

    // Check Synonym
    std::string expectedSynonym = "v";
    auto synonym = queryToken.selectClauseToken;

    CHECK(synonym == expectedSynonym);

    // Check Such That Clauses
    std::vector<SuchThatClauseToken>* expectedSuchThatClauseTokens = nullptr;
    auto suchThatClauseTokens = queryToken.suchThatClauseTokens;

    CHECK(suchThatClauseTokens == expectedSuchThatClauseTokens);

    // Check Pattern
    std::vector<PatternToken>* expectedPatternTokens = nullptr;
    auto patternTokens = queryToken.patternTokens;

    CHECK(patternTokens == expectedPatternTokens);
}

TEST_CASE ("QP TOKENIZER: SINGLE VARIABLE DECLARATION-DOUBLE CHAR") {
    std::string firstQuery = "variable va; \nSelect va";
    Tokenizer tokenizer = Tokenizer();
    QueryToken queryToken = tokenizer.getQueryToken(firstQuery);

    // Check declarations
    std::map<std::string, std::string> expectedDeclarationTokens({{"va", "variable"}});
    std::vector<std::string> expectedDeclarationNames({"va"});
    std::vector<std::string> expectedDesignEntities({"variable"});

    auto declarationTokens = *(queryToken.declarationTokens);
    auto declarations = *(queryToken.declarations);
    auto declarationNames = declarations.first;
    auto designEntities = declarations.second;

    CHECK(declarationTokens == expectedDeclarationTokens);
    CHECK(declarationNames == expectedDeclarationNames);
    CHECK(designEntities == expectedDesignEntities);

    // Check Synonym
    std::string expectedSynonym = "va";
    auto synonym = queryToken.selectClauseToken;

    CHECK(synonym == expectedSynonym);
}

TEST_CASE ("QP TOKENIZER: SINGLE VARIABLE DECLARATION-DOUBLE CHAR WITH INT") {
    std::string firstQuery = "variable va1; \nSelect va1";
    Tokenizer tokenizer = Tokenizer();
    QueryToken queryToken = tokenizer.getQueryToken(firstQuery);

    // Check declarations
    std::map<std::string, std::string> expectedDeclarationTokens({{"va1", "variable"}});
    std::vector<std::string> expectedDeclarationNames({"va1"});
    std::vector<std::string> expectedDesignEntities({"variable"});

    auto declarationTokens = *(queryToken.declarationTokens);
    auto declarations = *(queryToken.declarations);
    auto declarationNames = declarations.first;
    auto designEntities = declarations.second;

    CHECK(declarationTokens == expectedDeclarationTokens);
    CHECK(declarationNames == expectedDeclarationNames);
    CHECK(designEntities == expectedDesignEntities);

    // Check Synonym
    std::string expectedSynonym = "va1";
    auto synonym = queryToken.selectClauseToken;

    CHECK(synonym == expectedSynonym);
}

TEST_CASE ("QP TOKENIZER: SINGLE STMT DECLARATION") {
    std::string firstQuery = "stmt s; \nSelect s";
    Tokenizer tokenizer = Tokenizer();
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

    // Check Synonym
    std::string expectedSynonym = "s";
    auto synonym = queryToken.selectClauseToken;

    CHECK(synonym == expectedSynonym);
}

TEST_CASE ("QP TOKENIZER: SINGLE READ DECLARATION") {
    std::string firstQuery = "read s; \nSelect s";
    Tokenizer tokenizer = Tokenizer();
    QueryToken queryToken = tokenizer.getQueryToken(firstQuery);

    // Check declarations
    std::map<std::string, std::string> expectedDeclarationTokens({{"s", "read"}});
    std::vector<std::string> expectedDeclarationNames({"s"});
    std::vector<std::string> expectedDesignEntities({"read"});

    auto declarationTokens = *(queryToken.declarationTokens);
    auto declarations = *(queryToken.declarations);
    auto declarationNames = declarations.first;
    auto designEntities = declarations.second;

    CHECK(declarationTokens == expectedDeclarationTokens);
    CHECK(declarationNames == expectedDeclarationNames);
    CHECK(designEntities == expectedDesignEntities);
}

TEST_CASE ("QP TOKENIZER: SINGLE PRINT DECLARATION") {
    std::string firstQuery = "print s; \nSelect s";
    Tokenizer tokenizer = Tokenizer();
    QueryToken queryToken = tokenizer.getQueryToken(firstQuery);

    // Check declarations
    std::map<std::string, std::string> expectedDeclarationTokens({{"s", "print"}});
    std::vector<std::string> expectedDeclarationNames({"s"});
    std::vector<std::string> expectedDesignEntities({"print"});

    auto declarationTokens = *(queryToken.declarationTokens);
    auto declarations = *(queryToken.declarations);
    auto declarationNames = declarations.first;
    auto designEntities = declarations.second;

    CHECK(declarationTokens == expectedDeclarationTokens);
    CHECK(declarationNames == expectedDeclarationNames);
    CHECK(designEntities == expectedDesignEntities);
}

TEST_CASE ("QP TOKENIZER: SINGLE CALL DECLARATION") {
    std::string firstQuery = "call s; \nSelect s";
    Tokenizer tokenizer = Tokenizer();
    QueryToken queryToken = tokenizer.getQueryToken(firstQuery);

    // Check declarations
    std::map<std::string, std::string> expectedDeclarationTokens({{"s", "call"}});
    std::vector<std::string> expectedDeclarationNames({"s"});
    std::vector<std::string> expectedDesignEntities({"call"});

    auto declarationTokens = *(queryToken.declarationTokens);
    auto declarations = *(queryToken.declarations);
    auto declarationNames = declarations.first;
    auto designEntities = declarations.second;

    CHECK(declarationTokens == expectedDeclarationTokens);
    CHECK(declarationNames == expectedDeclarationNames);
    CHECK(designEntities == expectedDesignEntities);
}

TEST_CASE ("QP TOKENIZER: SINGLE WHILE DECLARATION") {
    std::string firstQuery = "while s; \nSelect s";
    Tokenizer tokenizer = Tokenizer();
    QueryToken queryToken = tokenizer.getQueryToken(firstQuery);

    // Check declarations
    std::map<std::string, std::string> expectedDeclarationTokens({{"s", "while"}});
    std::vector<std::string> expectedDeclarationNames({"s"});
    std::vector<std::string> expectedDesignEntities({"while"});

    auto declarationTokens = *(queryToken.declarationTokens);
    auto declarations = *(queryToken.declarations);
    auto declarationNames = declarations.first;
    auto designEntities = declarations.second;

    CHECK(declarationTokens == expectedDeclarationTokens);
    CHECK(declarationNames == expectedDeclarationNames);
    CHECK(designEntities == expectedDesignEntities);
}

TEST_CASE ("QP TOKENIZER: SINGLE IF DECLARATION") {
    std::string firstQuery = "if s; \nSelect s";
    Tokenizer tokenizer = Tokenizer();
    QueryToken queryToken = tokenizer.getQueryToken(firstQuery);

    // Check declarations
    std::map<std::string, std::string> expectedDeclarationTokens({{"s", "if"}});
    std::vector<std::string> expectedDeclarationNames({"s"});
    std::vector<std::string> expectedDesignEntities({"if"});

    auto declarationTokens = *(queryToken.declarationTokens);
    auto declarations = *(queryToken.declarations);
    auto declarationNames = declarations.first;
    auto designEntities = declarations.second;

    CHECK(declarationTokens == expectedDeclarationTokens);
    CHECK(declarationNames == expectedDeclarationNames);
    CHECK(designEntities == expectedDesignEntities);
}

TEST_CASE ("QP TOKENIZER: SINGLE ASSIGN DECLARATION") {
    std::string firstQuery = "assign s; \nSelect s";
    Tokenizer tokenizer = Tokenizer();
    QueryToken queryToken = tokenizer.getQueryToken(firstQuery);

    // Check declarations
    std::map<std::string, std::string> expectedDeclarationTokens({{"s", "assign"}});
    std::vector<std::string> expectedDeclarationNames({"s"});
    std::vector<std::string> expectedDesignEntities({"assign"});

    auto declarationTokens = *(queryToken.declarationTokens);
    auto declarations = *(queryToken.declarations);
    auto declarationNames = declarations.first;
    auto designEntities = declarations.second;

    CHECK(declarationTokens == expectedDeclarationTokens);
    CHECK(declarationNames == expectedDeclarationNames);
    CHECK(designEntities == expectedDesignEntities);
}

TEST_CASE ("QP TOKENIZER: SINGLE CONSTANT DECLARATION") {
    std::string firstQuery = "constant s; \nSelect s";
    Tokenizer tokenizer = Tokenizer();
    QueryToken queryToken = tokenizer.getQueryToken(firstQuery);

    // Check declarations
    std::map<std::string, std::string> expectedDeclarationTokens({{"s", "constant"}});
    std::vector<std::string> expectedDeclarationNames({"s"});
    std::vector<std::string> expectedDesignEntities({"constant"});

    auto declarationTokens = *(queryToken.declarationTokens);
    auto declarations = *(queryToken.declarations);
    auto declarationNames = declarations.first;
    auto designEntities = declarations.second;

    CHECK(declarationTokens == expectedDeclarationTokens);
    CHECK(declarationNames == expectedDeclarationNames);
    CHECK(designEntities == expectedDesignEntities);
}

TEST_CASE ("QP TOKENIZER: SINGLE PROCEDURE DECLARATION") {
    std::string firstQuery = "procedure s; \nSelect s";
    Tokenizer tokenizer = Tokenizer();
    QueryToken queryToken = tokenizer.getQueryToken(firstQuery);

    // Check declarations
    std::map<std::string, std::string> expectedDeclarationTokens({{"s", "procedure"}});
    std::vector<std::string> expectedDeclarationNames({"s"});
    std::vector<std::string> expectedDesignEntities({"procedure"});

    auto declarationTokens = *(queryToken.declarationTokens);
    auto declarations = *(queryToken.declarations);
    auto declarationNames = declarations.first;
    auto designEntities = declarations.second;

    CHECK(declarationTokens == expectedDeclarationTokens);
    CHECK(declarationNames == expectedDeclarationNames);
    CHECK(designEntities == expectedDesignEntities);
}

// TODO: Edit

TEST_CASE ("DECLARATIONS") {
    std::string firstQuery = "variable v1, v2; assign a;\nSelect v";
    Tokenizer tokenizer = Tokenizer();
    QueryToken queryToken = tokenizer.getQueryToken(firstQuery);
}

TEST_CASE("PATTERN CLAUSE") {
    std::string second = "variable v; assign a;\nSelect a pattern a (    v , \"x\"      )";
    Tokenizer tokenizer = Tokenizer();
    QueryToken queryToken = tokenizer.getQueryToken(second);
}

TEST_CASE("SUCH THAT CLAUSE") {
    std::string second = "variable v; stmt s;\nSelect s such that Follows(10, s)";
    Tokenizer tokenizer = Tokenizer();
    QueryToken queryToken = tokenizer.getQueryToken(second);
}