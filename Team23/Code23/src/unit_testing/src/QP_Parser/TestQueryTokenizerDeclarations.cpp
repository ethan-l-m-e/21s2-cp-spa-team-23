#include "catch.hpp"
#include "QP_Parser/Tokenizer.h"

#include <vector>
#include <string>
#include <map>

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
    auto synonym = *queryToken.selectClauseTokens;

    CHECK(synonym[0] == expectedSynonym);

    // Check Such That Clauses
    auto suchThatClauseTokens = queryToken.suchThatClauseTokens;

    CHECK(suchThatClauseTokens->empty());

    // Check Pattern
    auto patternTokens = queryToken.patternTokens;

    CHECK(patternTokens->empty());
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
    auto synonym = *queryToken.selectClauseTokens;

    CHECK(synonym[0] == expectedSynonym);
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
    auto synonym = *queryToken.selectClauseTokens;

    CHECK(synonym[0] == expectedSynonym);
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
    auto synonym = *queryToken.selectClauseTokens;

    CHECK(synonym[0] == expectedSynonym);
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
    std::vector<std::string> synonyms = *queryToken.selectClauseTokens;

    CHECK(declarationTokens == expectedDeclarationTokens);
    CHECK(declarationNames == expectedDeclarationNames);
    CHECK(designEntities == expectedDesignEntities);
    CHECK(synonyms[0] == "Select");
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

TEST_CASE ("QP TOKENIZER: DECLARATION NAMED PATTERN") {
    std::string firstQuery = "procedure pattern; Select pattern";
    Tokenizer tokenizer = Tokenizer();
    QueryToken queryToken = tokenizer.getQueryToken(firstQuery);

    // Check declarations
    std::map<std::string, std::string> expectedDeclarationTokens({{"pattern", "procedure"}});
    std::vector<std::string> expectedDeclarationNames({"pattern"});
    std::vector<std::string> expectedDesignEntities({"procedure"});

    auto declarationTokens = *(queryToken.declarationTokens);
    auto declarations = *(queryToken.declarations);
    auto declarationNames = declarations.first;
    auto designEntities = declarations.second;
    auto synonyms = *queryToken.selectClauseTokens;

    CHECK(declarationTokens == expectedDeclarationTokens);
    CHECK(declarationNames == expectedDeclarationNames);
    CHECK(designEntities == expectedDesignEntities);
    CHECK(synonyms[0] == "pattern");
}

TEST_CASE ("QP TOKENIZER: DECLARATION NAMED WITH") {
    std::string firstQuery = "while with; Select with";
    Tokenizer tokenizer = Tokenizer();
    QueryToken queryToken = tokenizer.getQueryToken(firstQuery);

    // Check declarations
    std::map<std::string, std::string> expectedDeclarationTokens({{"with", "while"}});
    std::vector<std::string> expectedDeclarationNames({"with"});
    std::vector<std::string> expectedDesignEntities({"while"});

    auto declarationTokens = *(queryToken.declarationTokens);
    auto declarations = *(queryToken.declarations);
    auto declarationNames = declarations.first;
    auto designEntities = declarations.second;
    auto synonyms = *queryToken.selectClauseTokens;

    CHECK(declarationTokens == expectedDeclarationTokens);
    CHECK(declarationNames == expectedDeclarationNames);
    CHECK(designEntities == expectedDesignEntities);
    CHECK(synonyms[0] == "with");
}

TEST_CASE ("QP TOKENIZER: DECLARATION NAMED AND") {
    std::string firstQuery = "while and; Select and";
    Tokenizer tokenizer = Tokenizer();
    QueryToken queryToken = tokenizer.getQueryToken(firstQuery);

    // Check declarations
    std::map<std::string, std::string> expectedDeclarationTokens({{"and", "while"}});
    std::vector<std::string> expectedDeclarationNames({"and"});
    std::vector<std::string> expectedDesignEntities({"while"});

    auto declarationTokens = *(queryToken.declarationTokens);
    auto declarations = *(queryToken.declarations);
    auto declarationNames = declarations.first;
    auto designEntities = declarations.second;
    auto synonyms = *queryToken.selectClauseTokens;

    CHECK(declarationTokens == expectedDeclarationTokens);
    CHECK(declarationNames == expectedDeclarationNames);
    CHECK(designEntities == expectedDesignEntities);
    CHECK(synonyms[0] == "and");
}

TEST_CASE ("QP TOKENIZER: DECLARATION NAMED FOLLOWS") {
    std::string firstQuery = "while Follows; Select Follows";
    Tokenizer tokenizer = Tokenizer();
    QueryToken queryToken = tokenizer.getQueryToken(firstQuery);

    // Check declarations
    std::map<std::string, std::string> expectedDeclarationTokens({{"Follows", "while"}});
    std::vector<std::string> expectedDeclarationNames({"Follows"});
    std::vector<std::string> expectedDesignEntities({"while"});

    auto declarationTokens = *(queryToken.declarationTokens);
    auto declarations = *(queryToken.declarations);
    auto declarationNames = declarations.first;
    auto designEntities = declarations.second;
    auto synonyms = *queryToken.selectClauseTokens;

    CHECK(declarationTokens == expectedDeclarationTokens);
    CHECK(declarationNames == expectedDeclarationNames);
    CHECK(designEntities == expectedDesignEntities);
    CHECK(synonyms[0] == "Follows");
}

// Check random usages of spaces and tabs for declarations
TEST_CASE ("QP TOKENIZER: DECLARATION WITH SPACES AND TABS BEFORE DECLARATION NAME") {
    std::string firstQuery = "assign\t\t\t\t   a; Select a";
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
}

TEST_CASE ("QP TOKENIZER: DECLARATION WITH SPACES AND TABS AFTER DECLARATION NAME") {
    std::string firstQuery = "assign a\t\t  \t\t  ; Select a";
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
}

TEST_CASE ("QP TOKENIZER: DECLARATION WITH SPACES AND TABS BEFORE NEXT DECLARATION NAME") {
    std::string firstQuery = "assign a,\t\t   \t\t  a2; Select a";
    Tokenizer tokenizer = Tokenizer();
    QueryToken queryToken = tokenizer.getQueryToken(firstQuery);

    // Check declarations
    std::map<std::string, std::string> expectedDeclarationTokens({{"a", "assign"},
                                                                  {"a2", "assign"}});
    std::vector<std::string> expectedDeclarationNames({"a", "a2"});
    std::vector<std::string> expectedDesignEntities({"assign"});

    auto declarationTokens = *(queryToken.declarationTokens);
    auto declarations = *(queryToken.declarations);
    auto declarationNames = declarations.first;
    auto designEntities = declarations.second;

    CHECK(declarationTokens == expectedDeclarationTokens);
    CHECK(declarationNames == expectedDeclarationNames);
    CHECK(designEntities == expectedDesignEntities);
}

TEST_CASE ("QP TOKENIZER: DECLARATION WITH SPACES AND TABS BEFORE NEXT DESIGN ENTITY") {
    std::string firstQuery = "assign a;\t\t    \t  \tprocedure p1; Select a";
    Tokenizer tokenizer = Tokenizer();
    QueryToken queryToken = tokenizer.getQueryToken(firstQuery);

    // Check declarations
    std::map<std::string, std::string> expectedDeclarationTokens({{"a", "assign"},
                                                                  {"p1", "procedure"}});
    std::vector<std::string> expectedDeclarationNames({"a", "p1"});
    std::vector<std::string> expectedDesignEntities({"assign", "procedure"});

    auto declarationTokens = *(queryToken.declarationTokens);
    auto declarations = *(queryToken.declarations);
    auto declarationNames = declarations.first;
    auto designEntities = declarations.second;

    CHECK(declarationTokens == expectedDeclarationTokens);
    CHECK(declarationNames == expectedDeclarationNames);
    CHECK(designEntities == expectedDesignEntities);
}

TEST_CASE ("QP TOKENIZER: DECLARATION WITH NO SPACES AND TABS BEFORE NEXT DESIGN ENTITY") {
    std::string firstQuery = "assign a;procedure p1; Select a";
    Tokenizer tokenizer = Tokenizer();
    QueryToken queryToken = tokenizer.getQueryToken(firstQuery);

    // Check declarations
    std::map<std::string, std::string> expectedDeclarationTokens({{"a", "assign"},
                                                                  {"p1", "procedure"}});
    std::vector<std::string> expectedDeclarationNames({"a", "p1"});
    std::vector<std::string> expectedDesignEntities({"assign", "procedure"});

    auto declarationTokens = *(queryToken.declarationTokens);
    auto declarations = *(queryToken.declarations);
    auto declarationNames = declarations.first;
    auto designEntities = declarations.second;

    CHECK(declarationTokens == expectedDeclarationTokens);
    CHECK(declarationNames == expectedDeclarationNames);
    CHECK(designEntities == expectedDesignEntities);
}

// Check Select clause token
TEST_CASE ("QP TOKENIZER: SELECT CLAUSE WITH BOOLEAN AS SYNONYM") {
    std::string firstQuery = "assign a, a2; Select BOOLEAN";
    Tokenizer tokenizer = Tokenizer();
    QueryToken queryToken = tokenizer.getQueryToken(firstQuery);

    auto synonyms = *queryToken.selectClauseTokens;

    CHECK(synonyms[0] == "BOOLEAN");
}

TEST_CASE ("QP TOKENIZER: SELECT CLAUSE WITH ATTR REF: CONSTANT.VALUE") {
    std::string firstQuery = "constant c; Select c.value";
    Tokenizer tokenizer = Tokenizer();
    QueryToken queryToken = tokenizer.getQueryToken(firstQuery);

    auto synonyms = *queryToken.selectClauseTokens;

    CHECK(synonyms[0] == "c.value");
}

TEST_CASE ("QP TOKENIZER: SELECT CLAUSE WITH ATTR REF: STATEMENT.STMT#") {
    std::string firstQuery = "stmt s; Select s.stmt#";
    Tokenizer tokenizer = Tokenizer();
    QueryToken queryToken = tokenizer.getQueryToken(firstQuery);

    auto synonyms = *queryToken.selectClauseTokens;

    CHECK(synonyms[0] == "s.stmt#");
}

TEST_CASE ("QP TOKENIZER: SELECT CLAUSE WITH ATTR REF: PROCEDURE.PROCNAME") {
    std::string firstQuery = "procedure p; Select p.procName";
    Tokenizer tokenizer = Tokenizer();
    QueryToken queryToken = tokenizer.getQueryToken(firstQuery);

    auto synonyms = *queryToken.selectClauseTokens;

    CHECK(synonyms[0] == "p.procName");
}

// Check tuples as select clause
TEST_CASE ("QP TOKENIZER: SELECT CLAUSE WITH TUPLE: SINGLE ELEMENT SYNONYM") {
    std::string firstQuery = "procedure p; Select <p>";
    Tokenizer tokenizer = Tokenizer();
    QueryToken queryToken = tokenizer.getQueryToken(firstQuery);

    auto synonyms = *queryToken.selectClauseTokens;

    CHECK(synonyms[0] == "p");
}

TEST_CASE ("QP TOKENIZER: SELECT CLAUSE WITH TUPLE: SINGLE ELEMENT ATTR REF") {
    std::string firstQuery = "procedure p; Select <p.procName>";
    Tokenizer tokenizer = Tokenizer();
    QueryToken queryToken = tokenizer.getQueryToken(firstQuery);

    auto synonyms = *queryToken.selectClauseTokens;

    CHECK(synonyms[0] == "p.procName");
}

TEST_CASE ("QP TOKENIZER: SELECT CLAUSE WITH TUPLE: DOUBLE ELEMENTS") {
    std::string firstQuery = "procedure p; stmt s; Select <s, p.procName>";
    Tokenizer tokenizer = Tokenizer();
    QueryToken queryToken = tokenizer.getQueryToken(firstQuery);
    std::vector<std::string> expectedSelectClauseTokens = std::vector<std::string>({"s", "p.procName"});

    auto synonyms = *queryToken.selectClauseTokens;

    CHECK(synonyms == expectedSelectClauseTokens);
}

TEST_CASE ("QP TOKENIZER: SELECT CLAUSE WITH TUPLE: FOUR ELEMENTS") {
    std::string firstQuery = "procedure p; stmt s1, s2, s3; Select <s, p.procName, s2, s3>";
    Tokenizer tokenizer = Tokenizer();
    QueryToken queryToken = tokenizer.getQueryToken(firstQuery);
    std::vector<std::string> expectedSelectClauseTokens = std::vector<std::string>({"s", "p.procName", "s2", "s3"});

    auto synonyms = *queryToken.selectClauseTokens;

    CHECK(synonyms == expectedSelectClauseTokens);
}

TEST_CASE ("QP TOKENIZER: SELECT CLAUSE WITH TUPLE: SELECT, PATTERN, WITH, AND, FOLLOWS IN TUPLE") {
    std::string firstQuery = "procedure Select, pattern, with, and, Follows; Select <Select, pattern, with, and, Follows>";
    Tokenizer tokenizer = Tokenizer();
    QueryToken queryToken = tokenizer.getQueryToken(firstQuery);
    std::vector<std::string> expectedSelectClauseTokens = std::vector<std::string>({"Select", "pattern", "with", "and", "Follows"});

    auto synonyms = *queryToken.selectClauseTokens;

    CHECK(synonyms == expectedSelectClauseTokens);
}

TEST_CASE ("QP TOKENIZER: SELECT CLAUSE SYNONYM WITH PROCNAME") {
    std::string firstQuery = "procedure procName; Select procName";
    Tokenizer tokenizer = Tokenizer();
    QueryToken queryToken = tokenizer.getQueryToken(firstQuery);
    std::vector<std::string> expectedSelectClauseTokens = std::vector<std::string>({"procName"});

    auto synonyms = *queryToken.selectClauseTokens;

    CHECK(synonyms == expectedSelectClauseTokens);
}

TEST_CASE ("QP TOKENIZER: SELECT CLAUSE WITH TUPLE: PROCNAME, VARNAME, VALUE") {
    std::string firstQuery = "procedure procName, varName, value; Select <procName, varName, value>";
    Tokenizer tokenizer = Tokenizer();
    QueryToken queryToken = tokenizer.getQueryToken(firstQuery);
    std::vector<std::string> expectedSelectClauseTokens = std::vector<std::string>({"procName", "varName", "value"});

    auto synonyms = *queryToken.selectClauseTokens;

    CHECK(synonyms == expectedSelectClauseTokens);
}

// Check random usage of spaces and tabs for select clause
TEST_CASE ("QP TOKENIZER: SPACES AND TABS BEFORE SELECT CLAUSE") {
    std::string firstQuery = "assign a, a2;  \t\t   \t\tSelect a";
    Tokenizer tokenizer = Tokenizer();
    QueryToken queryToken = tokenizer.getQueryToken(firstQuery);

    auto synonyms = *queryToken.selectClauseTokens;

    CHECK(synonyms[0] == "a");
}

TEST_CASE ("QP TOKENIZER: SPACES AND TABS BEFORE SELECT CLAUSE SYNONYM") {
    std::string firstQuery = "assign a, a2; Select  \t\t  \t\ta";
    Tokenizer tokenizer = Tokenizer();
    QueryToken queryToken = tokenizer.getQueryToken(firstQuery);

    auto synonyms = *queryToken.selectClauseTokens;

    CHECK(synonyms[0] == "a");
}

TEST_CASE ("QP TOKENIZER: SPACES AND TABS BEFORE SELECT CLAUSE SYNONYM - BOOLEAN") {
    std::string firstQuery = "assign a, a2; Select\t  \t\t  \tBOOLEAN";
    Tokenizer tokenizer = Tokenizer();
    QueryToken queryToken = tokenizer.getQueryToken(firstQuery);

    auto synonyms = *queryToken.selectClauseTokens;

    CHECK(synonyms[0] == "BOOLEAN");
}

TEST_CASE ("QP TOKENIZER: SPACES AND TABS BEFORE '.' in SELECT CLAUSE SYNONYM - ATTRREF") {
    std::string firstQuery = "procedure p; Select p   \t  \t\t\t\t.procName";
    Tokenizer tokenizer = Tokenizer();
    QueryToken queryToken = tokenizer.getQueryToken(firstQuery);

    auto synonyms = *queryToken.selectClauseTokens;

    CHECK(synonyms[0] == "p.procName");
}

TEST_CASE ("QP TOKENIZER: SPACES AND TABS AFTER '.' in SELECT CLAUSE SYNONYM - ATTRREF") {
    std::string firstQuery = "procedure p; Select p.  \t  \t  \t\tprocName";
    Tokenizer tokenizer = Tokenizer();
    QueryToken queryToken = tokenizer.getQueryToken(firstQuery);

    auto synonyms = *queryToken.selectClauseTokens;

    CHECK(synonyms[0] == "p.procName");
}

TEST_CASE ("QP TOKENIZER: SPACES AND TABS AFTER '<' in SELECT CLAUSE TUPLE") {
    std::string firstQuery = "procedure p1, p2; Select <\t  \t \t\t  \tp1>";
    Tokenizer tokenizer = Tokenizer();
    QueryToken queryToken = tokenizer.getQueryToken(firstQuery);

    auto synonyms = *queryToken.selectClauseTokens;

    CHECK(synonyms[0] == "p1");
}

TEST_CASE ("QP TOKENIZER: SPACES AND TABS BEFORE '>' in SELECT CLAUSE TUPLE") {
    std::string firstQuery = "procedure p1, p2; Select <p1\t\t  \t\t  \t>";
    Tokenizer tokenizer = Tokenizer();
    QueryToken queryToken = tokenizer.getQueryToken(firstQuery);

    auto synonyms = *queryToken.selectClauseTokens;

    CHECK(synonyms[0] == "p1");
}

TEST_CASE ("QP TOKENIZER: SPACES AND TABS AFTER ',' in SELECT CLAUSE TUPLE") {
    std::string firstQuery = "procedure p1, p2; Select <p1, \t\t\t\t    \t p2>";
    Tokenizer tokenizer = Tokenizer();
    QueryToken queryToken = tokenizer.getQueryToken(firstQuery);
    std::vector<std::string> expectedSelectClauseTokens = std::vector<std::string>({"p1", "p2"});

    auto synonyms = *queryToken.selectClauseTokens;

    CHECK(synonyms == expectedSelectClauseTokens);
}

TEST_CASE ("QP TOKENIZER: SPACES AND TABS FOR ATTR REF in SELECT CLAUSE TUPLE") {
    std::string firstQuery = "procedure p1, p2; Select <p1, p2 \t\t . procName \t\t>";
    Tokenizer tokenizer = Tokenizer();
    QueryToken queryToken = tokenizer.getQueryToken(firstQuery);
    std::vector<std::string> expectedSelectClauseTokens = std::vector<std::string>({"p1", "p2.procName"});

    auto synonyms = *queryToken.selectClauseTokens;

    CHECK(synonyms == expectedSelectClauseTokens);
}

