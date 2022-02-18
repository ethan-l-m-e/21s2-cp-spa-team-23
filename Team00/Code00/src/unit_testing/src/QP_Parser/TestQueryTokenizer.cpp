#include "catch.hpp"
#include "QP_Parser/Tokenizer.h"
#include "pql/query_obj/Argument.h"
#include <vector>
#include <string>
#include <map>
#include <iostream>

using namespace qp;

// Check tokenizing for declarations and select synonym
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

TEST_CASE ("QP TOKENIZER: DOUBLE DECLARATIONS") {
    std::string firstQuery = "stmt s; variable v; \nSelect s";
    Tokenizer tokenizer = Tokenizer();
    QueryToken queryToken = tokenizer.getQueryToken(firstQuery);

    // Check declarations
    std::map<std::string, std::string> expectedDeclarationTokens({{"s", "stmt"},
                                                                  {"v", "variable"}});
    std::vector<std::string> expectedDeclarationNames({"s", "v"});
    std::vector<std::string> expectedDesignEntities({"stmt", "variable"});

    auto declarationTokens = *(queryToken.declarationTokens);
    auto declarations = *(queryToken.declarations);
    auto declarationNames = declarations.first;
    auto designEntities = declarations.second;

    CHECK(declarationTokens == expectedDeclarationTokens);
    CHECK(declarationNames == expectedDeclarationNames);
    CHECK(designEntities == expectedDesignEntities);
}

TEST_CASE ("QP TOKENIZER: TRIPLE DECLARATIONS") {
    std::string firstQuery = "stmt s; variable v; procedure p; \nSelect s";
    Tokenizer tokenizer = Tokenizer();
    QueryToken queryToken = tokenizer.getQueryToken(firstQuery);

    // Check declarations
    std::map<std::string, std::string> expectedDeclarationTokens({{"s", "stmt"},
                                                                  {"v", "variable"},
                                                                  {"p", "procedure"}});
    std::vector<std::string> expectedDeclarationNames({"s", "v", "p"});
    std::vector<std::string> expectedDesignEntities({"stmt", "variable", "procedure"});

    auto declarationTokens = *(queryToken.declarationTokens);
    auto declarations = *(queryToken.declarations);
    auto declarationNames = declarations.first;
    auto designEntities = declarations.second;

    CHECK(declarationTokens == expectedDeclarationTokens);
    CHECK(declarationNames == expectedDeclarationNames);
    CHECK(designEntities == expectedDesignEntities);
}

TEST_CASE ("QP TOKENIZER: MULTIPLE DECLARATIONS FOR SAME DESIGN ENTITY") {
    std::string firstQuery = "stmt s1, s2; \nSelect s";
    Tokenizer tokenizer = Tokenizer();
    QueryToken queryToken = tokenizer.getQueryToken(firstQuery);

    // Check declarations
    std::map<std::string, std::string> expectedDeclarationTokens({{"s1", "stmt"},
                                                                  {"s2", "stmt"}});
    std::vector<std::string> expectedDeclarationNames({"s1", "s2"});
    std::vector<std::string> expectedDesignEntities({"stmt"});

    auto declarationTokens = *(queryToken.declarationTokens);
    auto declarations = *(queryToken.declarations);
    auto declarationNames = declarations.first;
    auto designEntities = declarations.second;

    CHECK(declarationTokens == expectedDeclarationTokens);
    CHECK(declarationNames == expectedDeclarationNames);
    CHECK(designEntities == expectedDesignEntities);
}

TEST_CASE ("QP TOKENIZER: MULTIPLE DECLARATIONS FOR SAME DESIGN ENTITY DOUBLE DECLARATIONS") {
    std::string firstQuery = "stmt s1, s2; variable v1, v2; \nSelect s1";
    Tokenizer tokenizer = Tokenizer();
    QueryToken queryToken = tokenizer.getQueryToken(firstQuery);

    // Check declarations
    std::map<std::string, std::string> expectedDeclarationTokens({{"s1", "stmt"},
                                                                  {"s2", "stmt"},
                                                                  {"v1", "variable"},
                                                                  {"v2", "variable"}});
    std::vector<std::string> expectedDeclarationNames({"s1", "s2", "v1", "v2"});
    std::vector<std::string> expectedDesignEntities({"stmt", "variable"});

    auto declarationTokens = *(queryToken.declarationTokens);
    auto declarations = *(queryToken.declarations);
    auto declarationNames = declarations.first;
    auto designEntities = declarations.second;

    CHECK(declarationTokens == expectedDeclarationTokens);
    CHECK(declarationNames == expectedDeclarationNames);
    CHECK(designEntities == expectedDesignEntities);
}

TEST_CASE ("QP TOKENIZER: MULTIPLE DECLARATIONS FOR SAME DESIGN ENTITY TRIPLE DECLARATIONS") {
    std::string firstQuery = "stmt s1, s2, s3; variable v1, v2; procedure p1, p2; \nSelect s1";
    Tokenizer tokenizer = Tokenizer();
    QueryToken queryToken = tokenizer.getQueryToken(firstQuery);

    // Check declarations
    std::map<std::string, std::string> expectedDeclarationTokens({{"s1", "stmt"},
                                                                  {"s2", "stmt"},
                                                                  {"s3", "stmt"},
                                                                  {"v1", "variable"},
                                                                  {"v2", "variable"},
                                                                  {"p1", "procedure"},
                                                                  {"p2", "procedure"}});
    std::vector<std::string> expectedDeclarationNames({"s1", "s2", "s3", "v1", "v2", "p1", "p2"});
    std::vector<std::string> expectedDesignEntities({"stmt", "variable", "procedure"});

    auto declarationTokens = *(queryToken.declarationTokens);
    auto declarations = *(queryToken.declarations);
    auto declarationNames = declarations.first;
    auto designEntities = declarations.second;

    CHECK(declarationTokens == expectedDeclarationTokens);
    CHECK(declarationNames == expectedDeclarationNames);
    CHECK(designEntities == expectedDesignEntities);
}

TEST_CASE ("QP TOKENIZER: SAME DESIGN ENTITY DECLARED TWICE") {
    std::string firstQuery = "stmt s1; variable v; stmt s2; \nSelect s";
    Tokenizer tokenizer = Tokenizer();
    QueryToken queryToken = tokenizer.getQueryToken(firstQuery);

    // Check declarations
    std::map<std::string, std::string> expectedDeclarationTokens({{"s1", "stmt"},
                                                                  {"v", "variable"},
                                                                  {"s2", "stmt"}});
    std::vector<std::string> expectedDeclarationNames({"s1", "v", "s2"});
    std::vector<std::string> expectedDesignEntities({"stmt", "variable", "stmt"});

    auto declarationTokens = *(queryToken.declarationTokens);
    auto declarations = *(queryToken.declarations);
    auto declarationNames = declarations.first;
    auto designEntities = declarations.second;

    CHECK(declarationTokens == expectedDeclarationTokens);
    CHECK(declarationNames == expectedDeclarationNames);
    CHECK(designEntities == expectedDesignEntities);
}

TEST_CASE ("QP TOKENIZER: SAME VARIABLE NAME DECLARED TWICE") {
    std::string firstQuery = "stmt s; variable s; \nSelect s";
    Tokenizer tokenizer = Tokenizer();
    QueryToken queryToken = tokenizer.getQueryToken(firstQuery);

    // Check declarations
    std::map<std::string, std::string> expectedDeclarationTokens({{"s", "stmt"},
                                                                  {"s", "variable"}});
    std::vector<std::string> expectedDeclarationNames({"s", "s"});
    std::vector<std::string> expectedDesignEntities({"stmt", "variable"});

    auto declarationTokens = *(queryToken.declarationTokens);
    auto declarations = *(queryToken.declarations);
    auto declarationNames = declarations.first;
    auto designEntities = declarations.second;

    CHECK(declarationTokens == expectedDeclarationTokens);
    CHECK(declarationNames == expectedDeclarationNames);
    CHECK(designEntities == expectedDesignEntities);
}

TEST_CASE ("QP TOKENIZER: DECLARATION NAMED SELECT") {
    std::string firstQuery = "stmt Select; \nSelect s";
    Tokenizer tokenizer = Tokenizer();
    QueryToken queryToken = tokenizer.getQueryToken(firstQuery);

    // Check declarations
    std::map<std::string, std::string> expectedDeclarationTokens({{"Select", "stmt"}});
    std::vector<std::string> expectedDeclarationNames({"Select"});
    std::vector<std::string> expectedDesignEntities({"stmt"});

    auto declarationTokens = *(queryToken.declarationTokens);
    auto declarations = *(queryToken.declarations);
    auto declarationNames = declarations.first;
    auto designEntities = declarations.second;

    CHECK(declarationTokens == expectedDeclarationTokens);
    CHECK(declarationNames == expectedDeclarationNames);
    CHECK(designEntities == expectedDesignEntities);
}

TEST_CASE ("QP TOKENIZER: DECLARATION NAMED SELECT AND SELECT SYNONYM IS ALSO SELECT") {
    std::string firstQuery = "stmt Select; \nSelect Select";
    Tokenizer tokenizer = Tokenizer();
    QueryToken queryToken = tokenizer.getQueryToken(firstQuery);

    // Check declarations
    std::map<std::string, std::string> expectedDeclarationTokens({{"Select", "stmt"}});
    std::vector<std::string> expectedDeclarationNames({"Select"});
    std::vector<std::string> expectedDesignEntities({"stmt"});

    auto declarationTokens = *(queryToken.declarationTokens);
    auto declarations = *(queryToken.declarations);
    auto declarationNames = declarations.first;
    auto designEntities = declarations.second;
    std::string synonym = queryToken.selectClauseToken;

    CHECK(declarationTokens == expectedDeclarationTokens);
    CHECK(declarationNames == expectedDeclarationNames);
    CHECK(designEntities == expectedDesignEntities);
    CHECK(synonym == "Select");
}

TEST_CASE ("QP TOKENIZER: DECLARATION NAMED SELECT WITH NO NEWLINE") {
    std::string firstQuery = "stmt Select; Select s";
    Tokenizer tokenizer = Tokenizer();
    QueryToken queryToken = tokenizer.getQueryToken(firstQuery);

    // Check declarations
    std::map<std::string, std::string> expectedDeclarationTokens({{"Select", "stmt"}});
    std::vector<std::string> expectedDeclarationNames({"Select"});
    std::vector<std::string> expectedDesignEntities({"stmt"});

    auto declarationTokens = *(queryToken.declarationTokens);
    auto declarations = *(queryToken.declarations);
    auto declarationNames = declarations.first;
    auto designEntities = declarations.second;

    CHECK(declarationTokens == expectedDeclarationTokens);
    CHECK(declarationNames == expectedDeclarationNames);
    CHECK(designEntities == expectedDesignEntities);
}

// TODO: Check spacings and newlines for Declarations

// Check tokenizing for Such That Clauses
TEST_CASE ("QP TOKENIZER: FOLLOWS SUCH THAT CLAUSE") {
    std::string firstQuery = "stmt s; \n Select s such that Follows(3, 2)";
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

    // Check SuchThatClause Token
    auto suchThatClauseTokens = *(queryToken.suchThatClauseTokens);
    auto suchThatClauseToken = suchThatClauseTokens[0];
    std::pair<std::string, std::string> expectedArguments = std::make_pair("3", "2");

    CHECK(suchThatClauseToken.relRef == "Follows");
    CHECK(*(suchThatClauseToken.arguments) == expectedArguments);
}

TEST_CASE ("QP TOKENIZER: FOLLOWS* SUCH THAT CLAUSE") {
    std::string firstQuery = "stmt Select; \n Select s such that Follows*(3, 2)";
    Tokenizer tokenizer = Tokenizer();
    QueryToken queryToken = tokenizer.getQueryToken(firstQuery);

    // Check SuchThatClause Token
    auto suchThatClauseTokens = *(queryToken.suchThatClauseTokens);
    auto suchThatClauseToken = suchThatClauseTokens[0];
    std::pair<std::string, std::string> expectedArguments = std::make_pair("3", "2");

    CHECK(suchThatClauseToken.relRef == "Follows*");
    CHECK(*(suchThatClauseToken.arguments) == expectedArguments);
    CHECK(queryToken.selectClauseToken == "s");
}

TEST_CASE ("QP TOKENIZER: PARENT SUCH THAT CLAUSE") {
    std::string firstQuery = "stmt Select; \n Select s such that Parent(3, 2)";
    Tokenizer tokenizer = Tokenizer();
    QueryToken queryToken = tokenizer.getQueryToken(firstQuery);

    // Check SuchThatClause Token
    auto suchThatClauseTokens = *(queryToken.suchThatClauseTokens);
    auto suchThatClauseToken = suchThatClauseTokens[0];
    std::pair<std::string, std::string> expectedArguments = std::make_pair("3", "2");

    CHECK(suchThatClauseToken.relRef == "Parent");
    CHECK(*(suchThatClauseToken.arguments) == expectedArguments);
}

TEST_CASE ("QP TOKENIZER: PARENT* SUCH THAT CLAUSE") {
    std::string firstQuery = "stmt Select; \n Select s such that Parent*(3, 2)";
    Tokenizer tokenizer = Tokenizer();
    QueryToken queryToken = tokenizer.getQueryToken(firstQuery);

    // Check SuchThatClause Token
    auto suchThatClauseTokens = *(queryToken.suchThatClauseTokens);
    auto suchThatClauseToken = suchThatClauseTokens[0];
    std::pair<std::string, std::string> expectedArguments = std::make_pair("3", "2");

    CHECK(suchThatClauseToken.relRef == "Parent*");
    CHECK(*(suchThatClauseToken.arguments) == expectedArguments);
}

TEST_CASE ("QP TOKENIZER: USES SUCH THAT CLAUSE") {
    std::string firstQuery = "variable v; \n Select v such that Uses(v, \"eg\")";
    Tokenizer tokenizer = Tokenizer();
    QueryToken queryToken = tokenizer.getQueryToken(firstQuery);

    // Check SuchThatClause Token
    auto suchThatClauseTokens = *(queryToken.suchThatClauseTokens);
    auto suchThatClauseToken = suchThatClauseTokens[0];
    std::pair<std::string, std::string> expectedArguments = std::make_pair("v", "\"eg\"");

    CHECK(suchThatClauseToken.relRef == "Uses");
    CHECK(*(suchThatClauseToken.arguments) == expectedArguments);
}

TEST_CASE ("QP TOKENIZER: MODIFIES SUCH THAT CLAUSE") {
    std::string firstQuery = "variable v; \n Select v such that Modifies(v, \"eg\")";
    Tokenizer tokenizer = Tokenizer();
    QueryToken queryToken = tokenizer.getQueryToken(firstQuery);

    // Check SuchThatClause Token
    auto suchThatClauseTokens = *(queryToken.suchThatClauseTokens);
    auto suchThatClauseToken = suchThatClauseTokens[0];
    std::pair<std::string, std::string> expectedArguments = std::make_pair("v", "\"eg\"");

    CHECK(suchThatClauseToken.relRef == "Modifies");
    CHECK(*(suchThatClauseToken.arguments) == expectedArguments);
}

TEST_CASE ("QP TOKENIZER: MODIFIES SUCH THAT CLAUSE WITH 2 IDENTS AS ARGUMENTS") {
    std::string firstQuery = "variable v; \n Select v such that Modifies(\"entref\", \"eg\")";
    Tokenizer tokenizer = Tokenizer();
    QueryToken queryToken = tokenizer.getQueryToken(firstQuery);

    // Check SuchThatClause Token
    auto suchThatClauseTokens = *(queryToken.suchThatClauseTokens);
    auto suchThatClauseToken = suchThatClauseTokens[0];
    std::pair<std::string, std::string> expectedArguments = std::make_pair("\"entref\"", "\"eg\"");

    CHECK(suchThatClauseToken.relRef == "Modifies");
    CHECK(*(suchThatClauseToken.arguments) == expectedArguments);
}

TEST_CASE ("QP TOKENIZER: MODIFIES SUCH THAT CLAUSE WITH SYNONYM AND WILDCARD AS ARGUMENTS") {
    std::string firstQuery = "variable v1, v2; \n Select v1 such that Modifies(v1, _)";
    Tokenizer tokenizer = Tokenizer();
    QueryToken queryToken = tokenizer.getQueryToken(firstQuery);

    // Check SuchThatClause Token
    auto suchThatClauseTokens = *(queryToken.suchThatClauseTokens);
    auto suchThatClauseToken = suchThatClauseTokens[0];
    std::pair<std::string, std::string> expectedArguments = std::make_pair("v1", "_");

    CHECK(suchThatClauseToken.relRef == "Modifies");
    CHECK(*(suchThatClauseToken.arguments) == expectedArguments);
}

TEST_CASE ("QP TOKENIZER: PATTERN") {
    std::string firstQuery = "assign a; \nSelect a pattern a(_, _)";
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
    auto synonym = queryToken.selectClauseToken;

    CHECK(synonym == expectedSynonym);

    // Check Such That Clauses
    std::vector<SuchThatClauseToken>* expectedSuchThatClauseTokens = nullptr;
    auto suchThatClauseTokens = queryToken.suchThatClauseTokens;

    CHECK(suchThatClauseTokens == expectedSuchThatClauseTokens);

    // Check Pattern
    std::pair<std::string, std::string> expectedArguments = std:: make_pair("_", "_");
    auto patternTokens = *(queryToken.patternTokens);
    auto patternToken = patternTokens[0];

    CHECK(patternToken.synonym == "a");
    CHECK(*(patternToken.arguments) == expectedArguments);
}

TEST_CASE ("QP TOKENIZER: PATTERN WITH SYNONYM ARGUMENT") {
    std::string firstQuery = "assign a; variable v; \nSelect a pattern a(v, _)";
    Tokenizer tokenizer = Tokenizer();
    QueryToken queryToken = tokenizer.getQueryToken(firstQuery);

    // Check Pattern
    std::pair<std::string, std::string> expectedArguments = std:: make_pair("v", "_");
    auto patternTokens = *(queryToken.patternTokens);
    auto patternToken = patternTokens[0];

    CHECK(patternToken.synonym == "a");
    CHECK(*(patternToken.arguments) == expectedArguments);
}

TEST_CASE ("QP TOKENIZER: PATTERN WITH IDENT ARGUMENT") {
    std::string firstQuery = "assign a; variable v; \nSelect a pattern a(\"x\", _)";
    Tokenizer tokenizer = Tokenizer();
    QueryToken queryToken = tokenizer.getQueryToken(firstQuery);

    // Check Pattern
    std::pair<std::string, std::string> expectedArguments = std:: make_pair("\"x\"", "_");
    auto patternTokens = *(queryToken.patternTokens);
    auto patternToken = patternTokens[0];

    CHECK(patternToken.synonym == "a");
    CHECK(*(patternToken.arguments) == expectedArguments);
}

TEST_CASE ("QP TOKENIZER: PATTERN WITH DOUBLE CHAR SYN-ASSIGN") {
    std::string firstQuery = "assign as; variable v; \nSelect as pattern as (\"x\", _)";
    Tokenizer tokenizer = Tokenizer();
    QueryToken queryToken = tokenizer.getQueryToken(firstQuery);

    // Check Pattern
    std::pair<std::string, std::string> expectedArguments = std:: make_pair("\"x\"", "_");
    auto patternTokens = *(queryToken.patternTokens);
    auto patternToken = patternTokens[0];

    CHECK(patternToken.synonym == "as");
    CHECK(*(patternToken.arguments) == expectedArguments);
}

TEST_CASE ("QP TOKENIZER: PATTERN WITH DOUBLE CHAR AND INT SYN-ASSIGN") {
    std::string firstQuery = "assign as1; variable v; \nSelect as1 pattern as1 (\"x\", _)";
    Tokenizer tokenizer = Tokenizer();
    QueryToken queryToken = tokenizer.getQueryToken(firstQuery);

    // Check Pattern
    std::pair<std::string, std::string> expectedArguments = std:: make_pair("\"x\"", "_");
    auto patternTokens = *(queryToken.patternTokens);
    auto patternToken = patternTokens[0];

    CHECK(patternToken.synonym == "as1");
    CHECK(*(patternToken.arguments) == expectedArguments);
}

TEST_CASE ("QP TOKENIZER: PATTERN WITH SELECT AS SYN-ASSIGN") {
    std::string firstQuery = "assign Select; variable v; \nSelect Select pattern Select (\"x\", _)";
    Tokenizer tokenizer = Tokenizer();
    QueryToken queryToken = tokenizer.getQueryToken(firstQuery);

    // Check Pattern
    std::pair<std::string, std::string> expectedArguments = std:: make_pair("\"x\"", "_");
    auto patternTokens = *(queryToken.patternTokens);
    auto patternToken = patternTokens[0];

    CHECK(patternToken.synonym == "Select");
    CHECK(*(patternToken.arguments) == expectedArguments);
}

TEST_CASE ("QP TOKENIZER: PATTERN WITH PATTERN AS SYN-ASSIGN") {
    std::string firstQuery = "assign pattern; variable v; \nSelect pattern pattern pattern (\"x\", _)";
    Tokenizer tokenizer = Tokenizer();
    QueryToken queryToken = tokenizer.getQueryToken(firstQuery);

    // Check Pattern
    std::pair<std::string, std::string> expectedArguments = std:: make_pair("\"x\"", "_");
    auto patternTokens = *(queryToken.patternTokens);
    auto patternToken = patternTokens[0];

    CHECK(patternToken.synonym == "pattern");
    CHECK(*(patternToken.arguments) == expectedArguments);
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