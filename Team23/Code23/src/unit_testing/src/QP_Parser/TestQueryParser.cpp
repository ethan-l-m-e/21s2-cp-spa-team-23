#include "catch.hpp"
#include "QP_Parser/QueryParser.h"
#include "QP_Parser/Tokenizer.h"
#include "QP_Evaluator/Query/Query.h"

#include <string>

using namespace qp;

bool operator==(const Argument& a1, const Argument& a2){
    bool result;
    result = (a1.argumentType == a2.argumentType) && (a1.argumentValue == a2.argumentValue);
    return result;
}

TEST_CASE ("PARSER - DECLARATIONS CHECK") {
    QueryParser parser = QueryParser();

    // variable design entity
    string pql = "variable v; \nSelect v";
    Query query = parser.getQuery(pql);

    Argument expectedArgument = Argument();
    expectedArgument.argumentValue = "v";
    expectedArgument.argumentType = ArgumentType::SYNONYM;

    CHECK(query.getSelectedSynonyms()[0] == expectedArgument);
    CHECK(query.findEntityType("v") == DesignEntity::VARIABLE);

    // constant design entity
    pql = "constant c; \nSelect c";
    query = parser.getQuery(pql);

    expectedArgument = Argument();
    expectedArgument.argumentValue = "c";
    expectedArgument.argumentType = ArgumentType::SYNONYM;

    CHECK(query.getSelectedSynonyms()[0] == expectedArgument);
    CHECK(query.findEntityType("c") == DesignEntity::CONSTANT);

    // procedure design entity
    pql = "procedure p; \nSelect p";
    query = parser.getQuery(pql);

    expectedArgument = Argument();
    expectedArgument.argumentValue = "p";
    expectedArgument.argumentType = ArgumentType::SYNONYM;

    CHECK(query.getSelectedSynonyms()[0] == expectedArgument);
    CHECK(query.findEntityType("p") == DesignEntity::PROCEDURE);

    // stmt design entity
    pql = "stmt s; \nSelect s";
    query = parser.getQuery(pql);

    expectedArgument = Argument();
    expectedArgument.argumentValue = "s";
    expectedArgument.argumentType = ArgumentType::SYNONYM;

    CHECK(query.getSelectedSynonyms()[0] == expectedArgument);
    CHECK(query.findEntityType("s") == DesignEntity::STMT);

    // read design entity
    pql = "read r; \nSelect r";
    query = parser.getQuery(pql);

    expectedArgument = Argument();
    expectedArgument.argumentValue = "r";
    expectedArgument.argumentType = ArgumentType::SYNONYM;

    CHECK(query.getSelectedSynonyms()[0] == expectedArgument);
    CHECK(query.findEntityType("r") == DesignEntity::READ);

    // print design entity
    pql = "print pn; \nSelect pn";
    query = parser.getQuery(pql);

    expectedArgument = Argument();
    expectedArgument.argumentValue = "pn";
    expectedArgument.argumentType = ArgumentType::SYNONYM;

    CHECK(query.getSelectedSynonyms()[0] == expectedArgument);
    CHECK(query.findEntityType("pn") == DesignEntity::PRINT);

    // assign design entity
    pql = "assign a; \nSelect a";
    query = parser.getQuery(pql);

    expectedArgument = Argument();
    expectedArgument.argumentValue = "a";
    expectedArgument.argumentType = ArgumentType::SYNONYM;

    CHECK(query.getSelectedSynonyms()[0] == expectedArgument);
    CHECK(query.findEntityType("a") == DesignEntity::ASSIGN);

    // call design entity
    pql = "call c; \nSelect c";
    query = parser.getQuery(pql);

    expectedArgument = Argument();
    expectedArgument.argumentValue = "c";
    expectedArgument.argumentType = ArgumentType::SYNONYM;

    CHECK(query.getSelectedSynonyms()[0] == expectedArgument);
    CHECK(query.findEntityType("c") == DesignEntity::CALL);

    // while design entity
    pql = "while w; \nSelect w";
    query = parser.getQuery(pql);

    expectedArgument = Argument();
    expectedArgument.argumentValue = "w";
    expectedArgument.argumentType = ArgumentType::SYNONYM;

    CHECK(query.getSelectedSynonyms()[0] == expectedArgument);
    CHECK(query.findEntityType("w") == DesignEntity::WHILE);

    // if design entity
    pql = "if ifs; \nSelect ifs";
    query = parser.getQuery(pql);

    expectedArgument = Argument();
    expectedArgument.argumentValue = "ifs";
    expectedArgument.argumentType = ArgumentType::SYNONYM;

    CHECK(query.getSelectedSynonyms()[0] == expectedArgument);
    CHECK(query.findEntityType("ifs") == DesignEntity::IF);

    // multiple declarations
    pql = "if ifs; assign a; \nSelect ifs";
    query = parser.getQuery(pql);

    expectedArgument = Argument();
    expectedArgument.argumentValue = "ifs";
    expectedArgument.argumentType = ArgumentType::SYNONYM;

    CHECK(query.getSelectedSynonyms()[0] == expectedArgument);
    CHECK(query.findEntityType("ifs") == DesignEntity::IF);
    CHECK(query.findEntityType("a") == DesignEntity::ASSIGN);

    // multiple declarations under same design entity
    pql = "assign a1, a2; \nSelect a1";
    query = parser.getQuery(pql);

    expectedArgument = Argument();
    expectedArgument.argumentValue = "a1";
    expectedArgument.argumentType = ArgumentType::SYNONYM;

    CHECK(query.getSelectedSynonyms()[0] == expectedArgument);
    CHECK(query.findEntityType("a1") == DesignEntity::ASSIGN);
    CHECK(query.findEntityType("a2") == DesignEntity::ASSIGN);
}

TEST_CASE ("PARSER - SYNONYM CHECK") {
    QueryParser parser = QueryParser();

    // synonym named Select
    string pql = "variable Select; \nSelect Select";
    Query query = parser.getQuery(pql);

    Argument expectedArgument = Argument();
    expectedArgument.argumentValue = "Select";
    expectedArgument.argumentType = ArgumentType::SYNONYM;

    CHECK(query.getSelectedSynonyms()[0] == expectedArgument);

    // synonym named pattern
    pql = "variable pattern; \nSelect pattern";
    query = parser.getQuery(pql);

    expectedArgument = Argument();
    expectedArgument.argumentValue = "pattern";
    expectedArgument.argumentType = ArgumentType::SYNONYM;

    CHECK(query.getSelectedSynonyms()[0] == expectedArgument);

    // synonym named pattern with pattern clause
    pql = "assign pattern; \nSelect pattern pattern pattern(_, _)";
    query = parser.getQuery(pql);

    expectedArgument = Argument();
    expectedArgument.argumentValue = "pattern";
    expectedArgument.argumentType = ArgumentType::SYNONYM;

    CHECK(query.getSelectedSynonyms()[0] == expectedArgument);
}

TEST_CASE ("PARSER - SUCH THAT CLAUSE FOLLOWS CHECK WITH ARGUMENTS: SYNONYM, WILDCARD") {
    QueryParser parser = QueryParser();

    std::string pql = "stmt s; \nSelect s such that Follows(s,_)";
    Query query = parser.getQuery(pql);
    SuchThatClause suchThatClause = query.getSuchThatClauses()[0];
    std::vector<Argument> argList = suchThatClause.argList;

    CHECK(suchThatClause.relRef == RelRef::FOLLOWS);

    Argument expectedFirstArgument = Argument();
    expectedFirstArgument.argumentValue = "s";
    expectedFirstArgument.argumentType = ArgumentType::SYNONYM;
    Argument expectedSecondArgument = Argument();
    expectedSecondArgument.argumentValue = "_";
    expectedSecondArgument.argumentType = ArgumentType::UNDERSCORE;

    CHECK(argList[0] == expectedFirstArgument);
    CHECK(argList[1] == expectedSecondArgument);
}

TEST_CASE ("PARSER - SUCH THAT CLAUSE FOLLOWS CHECK WITH ARGUMENTS: SYNONYM, INTEGER") {
    QueryParser parser = QueryParser();

    std::string pql = "stmt s; \nSelect s such that Follows(s,3)";
    Query query = parser.getQuery(pql);
    SuchThatClause suchThatClause = query.getSuchThatClauses()[0];
    std::vector<Argument> argList = suchThatClause.argList;

    CHECK(suchThatClause.relRef == RelRef::FOLLOWS);

    Argument expectedFirstArgument = Argument();
    expectedFirstArgument.argumentValue = "s";
    expectedFirstArgument.argumentType = ArgumentType::SYNONYM;
    Argument expectedSecondArgument = Argument();
    expectedSecondArgument.argumentValue = "3";
    expectedSecondArgument.argumentType = ArgumentType::STMT_NO;

    CHECK(argList[0] == expectedFirstArgument);
    CHECK(argList[1] == expectedSecondArgument);
}

TEST_CASE ("PARSER - SUCH THAT CLAUSE FOLLOWS CHECK WITH ARGUMENTS: SYNONYM, SYNONYM") {
    QueryParser parser = QueryParser();

    std::string pql = "stmt s1, s2; \nSelect s1 such that Follows(s1, s2)";
    Query query = parser.getQuery(pql);
    SuchThatClause suchThatClause = query.getSuchThatClauses()[0];
    std::vector<Argument> argList = suchThatClause.argList;

    CHECK(suchThatClause.relRef == RelRef::FOLLOWS);

    Argument expectedFirstArgument = Argument();
    expectedFirstArgument.argumentValue = "s1";
    expectedFirstArgument.argumentType = ArgumentType::SYNONYM;
    Argument expectedSecondArgument = Argument();
    expectedSecondArgument.argumentValue = "s2";
    expectedSecondArgument.argumentType = ArgumentType::SYNONYM;

    CHECK(argList[0] == expectedFirstArgument);
    CHECK(argList[1] == expectedSecondArgument);
}

TEST_CASE ("PARSER - SUCH THAT CLAUSE FOLLOWS CHECK WITH ARGUMENTS: INTEGER, SYNONYM") {
    QueryParser parser = QueryParser();

    std::string pql = "stmt s1, s2; \nSelect s1 such that Follows(3, s2)";
    Query query = parser.getQuery(pql);
    SuchThatClause suchThatClause = query.getSuchThatClauses()[0];
    std::vector<Argument> argList = suchThatClause.argList;

    CHECK(suchThatClause.relRef == RelRef::FOLLOWS);

    Argument expectedFirstArgument = Argument();
    expectedFirstArgument.argumentValue = "3";
    expectedFirstArgument.argumentType = ArgumentType::STMT_NO;
    Argument expectedSecondArgument = Argument();
    expectedSecondArgument.argumentValue = "s2";
    expectedSecondArgument.argumentType = ArgumentType::SYNONYM;

    CHECK(argList[0] == expectedFirstArgument);
    CHECK(argList[1] == expectedSecondArgument);
}

TEST_CASE ("PARSER - SUCH THAT CLAUSE FOLLOWS CHECK WITH ARGUMENTS: WILDCARD, SYNONYM") {
    QueryParser parser = QueryParser();

    std::string pql = "stmt s1, s2; \nSelect s1 such that Follows(_, s2)";
    Query query = parser.getQuery(pql);
    SuchThatClause suchThatClause = query.getSuchThatClauses()[0];
    std::vector<Argument> argList = suchThatClause.argList;

    CHECK(suchThatClause.relRef == RelRef::FOLLOWS);

    Argument expectedFirstArgument = Argument();
    expectedFirstArgument.argumentValue = "_";
    expectedFirstArgument.argumentType = ArgumentType::UNDERSCORE;
    Argument expectedSecondArgument = Argument();
    expectedSecondArgument.argumentValue = "s2";
    expectedSecondArgument.argumentType = ArgumentType::SYNONYM;

    CHECK(argList[0] == expectedFirstArgument);
    CHECK(argList[1] == expectedSecondArgument);
}

TEST_CASE ("PARSER - SUCH THAT CLAUSE FOLLOWS* CHECK WITH ARGUMENTS: SYNONYM, WILDCARD") {
    QueryParser parser = QueryParser();

    std::string pql = "stmt s; \nSelect s such that Follows*(s,_)";
    Query query = parser.getQuery(pql);
    SuchThatClause suchThatClause = query.getSuchThatClauses()[0];
    std::vector<Argument> argList = suchThatClause.argList;

    CHECK(suchThatClause.relRef == RelRef::FOLLOWS_T);

    Argument expectedFirstArgument = Argument();
    expectedFirstArgument.argumentValue = "s";
    expectedFirstArgument.argumentType = ArgumentType::SYNONYM;
    Argument expectedSecondArgument = Argument();
    expectedSecondArgument.argumentValue = "_";
    expectedSecondArgument.argumentType = ArgumentType::UNDERSCORE;

    CHECK(argList[0] == expectedFirstArgument);
    CHECK(argList[1] == expectedSecondArgument);
}

TEST_CASE ("PARSER - SUCH THAT CLAUSE FOLLOWS* CHECK WITH ARGUMENTS: SYNONYM, INTEGER") {
    QueryParser parser = QueryParser();

    std::string pql = "stmt s; \nSelect s such that Follows*(s,3)";
    Query query = parser.getQuery(pql);
    SuchThatClause suchThatClause = query.getSuchThatClauses()[0];
    std::vector<Argument> argList = suchThatClause.argList;

    CHECK(suchThatClause.relRef == RelRef::FOLLOWS_T);

    Argument expectedFirstArgument = Argument();
    expectedFirstArgument.argumentValue = "s";
    expectedFirstArgument.argumentType = ArgumentType::SYNONYM;
    Argument expectedSecondArgument = Argument();
    expectedSecondArgument.argumentValue = "3";
    expectedSecondArgument.argumentType = ArgumentType::STMT_NO;

    CHECK(argList[0] == expectedFirstArgument);
    CHECK(argList[1] == expectedSecondArgument);
}

TEST_CASE ("PARSER - SUCH THAT CLAUSE FOLLOWS* CHECK WITH ARGUMENTS: SYNONYM, SYNONYM") {
    QueryParser parser = QueryParser();

    std::string pql = "stmt s1, s2; \nSelect s1 such that Follows*(s1, s2)";
    Query query = parser.getQuery(pql);
    SuchThatClause suchThatClause = query.getSuchThatClauses()[0];
    std::vector<Argument> argList = suchThatClause.argList;

    CHECK(suchThatClause.relRef == RelRef::FOLLOWS_T);

    Argument expectedFirstArgument = Argument();
    expectedFirstArgument.argumentValue = "s1";
    expectedFirstArgument.argumentType = ArgumentType::SYNONYM;
    Argument expectedSecondArgument = Argument();
    expectedSecondArgument.argumentValue = "s2";
    expectedSecondArgument.argumentType = ArgumentType::SYNONYM;

    CHECK(argList[0] == expectedFirstArgument);
    CHECK(argList[1] == expectedSecondArgument);
}

TEST_CASE ("PARSER - SUCH THAT CLAUSE FOLLOWS* CHECK WITH ARGUMENTS: INTEGER, SYNONYM") {
    QueryParser parser = QueryParser();

    std::string pql = "stmt s1, s2; \nSelect s1 such that Follows*(3, s2)";
    Query query = parser.getQuery(pql);
    SuchThatClause suchThatClause = query.getSuchThatClauses()[0];
    std::vector<Argument> argList = suchThatClause.argList;

    CHECK(suchThatClause.relRef == RelRef::FOLLOWS_T);

    Argument expectedFirstArgument = Argument();
    expectedFirstArgument.argumentValue = "3";
    expectedFirstArgument.argumentType = ArgumentType::STMT_NO;
    Argument expectedSecondArgument = Argument();
    expectedSecondArgument.argumentValue = "s2";
    expectedSecondArgument.argumentType = ArgumentType::SYNONYM;

    CHECK(argList[0] == expectedFirstArgument);
    CHECK(argList[1] == expectedSecondArgument);
}

TEST_CASE ("PARSER - SUCH THAT CLAUSE FOLLOWS* CHECK WITH ARGUMENTS: WILDCARD, SYNONYM") {
    QueryParser parser = QueryParser();

    std::string pql = "stmt s1, s2; \nSelect s1 such that Follows*(_, s2)";
    Query query = parser.getQuery(pql);
    SuchThatClause suchThatClause = query.getSuchThatClauses()[0];
    std::vector<Argument> argList = suchThatClause.argList;

    CHECK(suchThatClause.relRef == RelRef::FOLLOWS_T);

    Argument expectedFirstArgument = Argument();
    expectedFirstArgument.argumentValue = "_";
    expectedFirstArgument.argumentType = ArgumentType::UNDERSCORE;
    Argument expectedSecondArgument = Argument();
    expectedSecondArgument.argumentValue = "s2";
    expectedSecondArgument.argumentType = ArgumentType::SYNONYM;

    CHECK(argList[0] == expectedFirstArgument);
    CHECK(argList[1] == expectedSecondArgument);
}

TEST_CASE ("PARSER - SUCH THAT CLAUSE PARENT CHECK WITH ARGUMENTS: SYNONYM, WILDCARD") {
    QueryParser parser = QueryParser();

    std::string pql = "stmt s; \nSelect s such that Parent(s,_)";
    Query query = parser.getQuery(pql);
    SuchThatClause suchThatClause = query.getSuchThatClauses()[0];
    std::vector<Argument> argList = suchThatClause.argList;

    CHECK(suchThatClause.relRef == RelRef::PARENT);

    Argument expectedFirstArgument = Argument();
    expectedFirstArgument.argumentValue = "s";
    expectedFirstArgument.argumentType = ArgumentType::SYNONYM;
    Argument expectedSecondArgument = Argument();
    expectedSecondArgument.argumentValue = "_";
    expectedSecondArgument.argumentType = ArgumentType::UNDERSCORE;

    CHECK(argList[0] == expectedFirstArgument);
    CHECK(argList[1] == expectedSecondArgument);
}

TEST_CASE ("PARSER - SUCH THAT CLAUSE PARENT CHECK WITH ARGUMENTS: SYNONYM, INTEGER") {
    QueryParser parser = QueryParser();

    std::string pql = "stmt s; \nSelect s such that Parent(s,3)";
    Query query = parser.getQuery(pql);
    SuchThatClause suchThatClause = query.getSuchThatClauses()[0];
    std::vector<Argument> argList = suchThatClause.argList;

    CHECK(suchThatClause.relRef == RelRef::PARENT);

    Argument expectedFirstArgument = Argument();
    expectedFirstArgument.argumentValue = "s";
    expectedFirstArgument.argumentType = ArgumentType::SYNONYM;
    Argument expectedSecondArgument = Argument();
    expectedSecondArgument.argumentValue = "3";
    expectedSecondArgument.argumentType = ArgumentType::STMT_NO;

    CHECK(argList[0] == expectedFirstArgument);
    CHECK(argList[1] == expectedSecondArgument);
}

TEST_CASE ("PARSER - SUCH THAT CLAUSE PARENT CHECK WITH ARGUMENTS: SYNONYM, SYNONYM") {
    QueryParser parser = QueryParser();

    std::string pql = "stmt s1, s2; \nSelect s1 such that Parent(s1, s2)";
    Query query = parser.getQuery(pql);
    SuchThatClause suchThatClause = query.getSuchThatClauses()[0];
    std::vector<Argument> argList = suchThatClause.argList;

    CHECK(suchThatClause.relRef == RelRef::PARENT);

    Argument expectedFirstArgument = Argument();
    expectedFirstArgument.argumentValue = "s1";
    expectedFirstArgument.argumentType = ArgumentType::SYNONYM;
    Argument expectedSecondArgument = Argument();
    expectedSecondArgument.argumentValue = "s2";
    expectedSecondArgument.argumentType = ArgumentType::SYNONYM;

    CHECK(argList[0] == expectedFirstArgument);
    CHECK(argList[1] == expectedSecondArgument);
}

TEST_CASE ("PARSER - SUCH THAT CLAUSE PARENT CHECK WITH ARGUMENTS: INTEGER, SYNONYM") {
    QueryParser parser = QueryParser();

    std::string pql = "stmt s1, s2; \nSelect s1 such that Parent(3, s2)";
    Query query = parser.getQuery(pql);
    SuchThatClause suchThatClause = query.getSuchThatClauses()[0];
    std::vector<Argument> argList = suchThatClause.argList;

    CHECK(suchThatClause.relRef == RelRef::PARENT);

    Argument expectedFirstArgument = Argument();
    expectedFirstArgument.argumentValue = "3";
    expectedFirstArgument.argumentType = ArgumentType::STMT_NO;
    Argument expectedSecondArgument = Argument();
    expectedSecondArgument.argumentValue = "s2";
    expectedSecondArgument.argumentType = ArgumentType::SYNONYM;

    CHECK(argList[0] == expectedFirstArgument);
    CHECK(argList[1] == expectedSecondArgument);
}

TEST_CASE ("PARSER - SUCH THAT CLAUSE PARENT CHECK WITH ARGUMENTS: WILDCARD, SYNONYM") {
    QueryParser parser = QueryParser();

    std::string pql = "stmt s1, s2; \nSelect s1 such that Parent(_, s2)";
    Query query = parser.getQuery(pql);
    SuchThatClause suchThatClause = query.getSuchThatClauses()[0];
    std::vector<Argument> argList = suchThatClause.argList;

    CHECK(suchThatClause.relRef == RelRef::PARENT);

    Argument expectedFirstArgument = Argument();
    expectedFirstArgument.argumentValue = "_";
    expectedFirstArgument.argumentType = ArgumentType::UNDERSCORE;
    Argument expectedSecondArgument = Argument();
    expectedSecondArgument.argumentValue = "s2";
    expectedSecondArgument.argumentType = ArgumentType::SYNONYM;

    CHECK(argList[0] == expectedFirstArgument);
    CHECK(argList[1] == expectedSecondArgument);
}

TEST_CASE ("PARSER - SUCH THAT CLAUSE PARENT* CHECK WITH ARGUMENTS: SYNONYM, WILDCARD") {
    QueryParser parser = QueryParser();

    std::string pql = "stmt s; \nSelect s such that Parent*(s,_)";
    Query query = parser.getQuery(pql);
    SuchThatClause suchThatClause = query.getSuchThatClauses()[0];
    std::vector<Argument> argList = suchThatClause.argList;

    CHECK(suchThatClause.relRef == RelRef::PARENT_T);

    Argument expectedFirstArgument = Argument();
    expectedFirstArgument.argumentValue = "s";
    expectedFirstArgument.argumentType = ArgumentType::SYNONYM;
    Argument expectedSecondArgument = Argument();
    expectedSecondArgument.argumentValue = "_";
    expectedSecondArgument.argumentType = ArgumentType::UNDERSCORE;

    CHECK(argList[0] == expectedFirstArgument);
    CHECK(argList[1] == expectedSecondArgument);
}

TEST_CASE ("PARSER - SUCH THAT CLAUSE PARENT* CHECK WITH ARGUMENTS: SYNONYM, INTEGER") {
    QueryParser parser = QueryParser();

    std::string pql = "stmt s; \nSelect s such that Parent*(s,3)";
    Query query = parser.getQuery(pql);
    SuchThatClause suchThatClause = query.getSuchThatClauses()[0];
    std::vector<Argument> argList = suchThatClause.argList;

    CHECK(suchThatClause.relRef == RelRef::PARENT_T);

    Argument expectedFirstArgument = Argument();
    expectedFirstArgument.argumentValue = "s";
    expectedFirstArgument.argumentType = ArgumentType::SYNONYM;
    Argument expectedSecondArgument = Argument();
    expectedSecondArgument.argumentValue = "3";
    expectedSecondArgument.argumentType = ArgumentType::STMT_NO;

    CHECK(argList[0] == expectedFirstArgument);
    CHECK(argList[1] == expectedSecondArgument);
}

TEST_CASE ("PARSER - SUCH THAT CLAUSE PARENT* CHECK WITH ARGUMENTS: SYNONYM, SYNONYM") {
    QueryParser parser = QueryParser();

    std::string pql = "stmt s1, s2; \nSelect s1 such that Parent*(s1, s2)";
    Query query = parser.getQuery(pql);
    SuchThatClause suchThatClause = query.getSuchThatClauses()[0];
    std::vector<Argument> argList = suchThatClause.argList;

    CHECK(suchThatClause.relRef == RelRef::PARENT_T);

    Argument expectedFirstArgument = Argument();
    expectedFirstArgument.argumentValue = "s1";
    expectedFirstArgument.argumentType = ArgumentType::SYNONYM;
    Argument expectedSecondArgument = Argument();
    expectedSecondArgument.argumentValue = "s2";
    expectedSecondArgument.argumentType = ArgumentType::SYNONYM;

    CHECK(argList[0] == expectedFirstArgument);
    CHECK(argList[1] == expectedSecondArgument);
}

TEST_CASE ("PARSER - SUCH THAT CLAUSE PARENT* CHECK WITH ARGUMENTS: INTEGER, SYNONYM") {
    QueryParser parser = QueryParser();

    std::string pql = "stmt s1, s2; \nSelect s1 such that Parent*(3, s2)";
    Query query = parser.getQuery(pql);
    SuchThatClause suchThatClause = query.getSuchThatClauses()[0];
    std::vector<Argument> argList = suchThatClause.argList;

    CHECK(suchThatClause.relRef == RelRef::PARENT_T);

    Argument expectedFirstArgument = Argument();
    expectedFirstArgument.argumentValue = "3";
    expectedFirstArgument.argumentType = ArgumentType::STMT_NO;
    Argument expectedSecondArgument = Argument();
    expectedSecondArgument.argumentValue = "s2";
    expectedSecondArgument.argumentType = ArgumentType::SYNONYM;

    CHECK(argList[0] == expectedFirstArgument);
    CHECK(argList[1] == expectedSecondArgument);
}

TEST_CASE ("PARSER - SUCH THAT CLAUSE PARENT* CHECK WITH ARGUMENTS: WILDCARD, SYNONYM") {
    QueryParser parser = QueryParser();

    std::string pql = "stmt s1, s2; \nSelect s1 such that Parent*(_, s2)";
    Query query = parser.getQuery(pql);
    SuchThatClause suchThatClause = query.getSuchThatClauses()[0];
    std::vector<Argument> argList = suchThatClause.argList;

    CHECK(suchThatClause.relRef == RelRef::PARENT_T);

    Argument expectedFirstArgument = Argument();
    expectedFirstArgument.argumentValue = "_";
    expectedFirstArgument.argumentType = ArgumentType::UNDERSCORE;
    Argument expectedSecondArgument = Argument();
    expectedSecondArgument.argumentValue = "s2";
    expectedSecondArgument.argumentType = ArgumentType::SYNONYM;

    CHECK(argList[0] == expectedFirstArgument);
    CHECK(argList[1] == expectedSecondArgument);
}

TEST_CASE ("PARSER - SUCH THAT CLAUSE USES CHECK WITH ARGUMENTS: IDENT, WILDCARD") {
    QueryParser parser = QueryParser();

    std::string pql = "variable v; assign a; \nSelect v such that Uses(\"x\", _)";
    Query query = parser.getQuery(pql);
    SuchThatClause suchThatClause = query.getSuchThatClauses()[0];
    std::vector<Argument> argList = suchThatClause.argList;

    CHECK(suchThatClause.relRef == RelRef::USES_P);

    Argument expectedFirstArgument = Argument();
    expectedFirstArgument.argumentValue = "x";
    expectedFirstArgument.argumentType = ArgumentType::IDENT;
    Argument expectedSecondArgument = Argument();
    expectedSecondArgument.argumentValue = "_";
    expectedSecondArgument.argumentType = ArgumentType::UNDERSCORE;

    CHECK(argList[0] == expectedFirstArgument);
    CHECK(argList[1] == expectedSecondArgument);
}

TEST_CASE ("PARSER - SUCH THAT CLAUSE USES CHECK WITH ARGUMENTS: STMT SYNONYM, WILDCARD") {
    QueryParser parser = QueryParser();

    std::string pql = "variable v; assign a; stmt s; \nSelect v such that Uses(a, _)";
    Query query = parser.getQuery(pql);
    SuchThatClause suchThatClause = query.getSuchThatClauses()[0];
    std::vector<Argument> argList = suchThatClause.argList;

    CHECK(suchThatClause.relRef == RelRef::USES_S);

    Argument expectedFirstArgument = Argument();
    expectedFirstArgument.argumentValue = "a";
    expectedFirstArgument.argumentType = ArgumentType::SYNONYM;
    Argument expectedSecondArgument = Argument();
    expectedSecondArgument.argumentValue = "_";
    expectedSecondArgument.argumentType = ArgumentType::UNDERSCORE;

    CHECK(argList[0] == expectedFirstArgument);
    CHECK(argList[1] == expectedSecondArgument);
}

TEST_CASE ("PARSER - SUCH THAT CLAUSE USES CHECK WITH ARGUMENTS: STMT SYNONYM - PRINT, WILDCARD") {
    QueryParser parser = QueryParser();

    std::string pql = "variable v; assign a; stmt s; print pn; \nSelect v such that Uses(pn, _)";
    Query query = parser.getQuery(pql);
    SuchThatClause suchThatClause = query.getSuchThatClauses()[0];
    std::vector<Argument> argList = suchThatClause.argList;

    CHECK(suchThatClause.relRef == RelRef::USES_S);

    Argument expectedFirstArgument = Argument();
    expectedFirstArgument.argumentValue = "pn";
    expectedFirstArgument.argumentType = ArgumentType::SYNONYM;
    Argument expectedSecondArgument = Argument();
    expectedSecondArgument.argumentValue = "_";
    expectedSecondArgument.argumentType = ArgumentType::UNDERSCORE;

    CHECK(argList[0] == expectedFirstArgument);
    CHECK(argList[1] == expectedSecondArgument);
}

TEST_CASE ("PARSER - SUCH THAT CLAUSE USES CHECK WITH ARGUMENTS: STMT SYNONYM - IF, WILDCARD") {
    QueryParser parser = QueryParser();

    std::string pql = "variable v; assign a; stmt s; print pn; if ifs; \nSelect v such that Uses(ifs, _)";
    Query query = parser.getQuery(pql);
    SuchThatClause suchThatClause = query.getSuchThatClauses()[0];
    std::vector<Argument> argList = suchThatClause.argList;

    CHECK(suchThatClause.relRef == RelRef::USES_S);

    Argument expectedFirstArgument = Argument();
    expectedFirstArgument.argumentValue = "ifs";
    expectedFirstArgument.argumentType = ArgumentType::SYNONYM;
    Argument expectedSecondArgument = Argument();
    expectedSecondArgument.argumentValue = "_";
    expectedSecondArgument.argumentType = ArgumentType::UNDERSCORE;

    CHECK(argList[0] == expectedFirstArgument);
    CHECK(argList[1] == expectedSecondArgument);
}

TEST_CASE ("PARSER - SUCH THAT CLAUSE USES CHECK WITH ARGUMENTS: STMT SYNONYM - WHILE, WILDCARD") {
    QueryParser parser = QueryParser();

    std::string pql = "variable v; assign a; stmt s; print pn; if ifs; while w; \nSelect v such that Uses(w, _)";
    Query query = parser.getQuery(pql);
    SuchThatClause suchThatClause = query.getSuchThatClauses()[0];
    std::vector<Argument> argList = suchThatClause.argList;

    CHECK(suchThatClause.relRef == RelRef::USES_S);

    Argument expectedFirstArgument = Argument();
    expectedFirstArgument.argumentValue = "w";
    expectedFirstArgument.argumentType = ArgumentType::SYNONYM;
    Argument expectedSecondArgument = Argument();
    expectedSecondArgument.argumentValue = "_";
    expectedSecondArgument.argumentType = ArgumentType::UNDERSCORE;

    CHECK(argList[0] == expectedFirstArgument);
    CHECK(argList[1] == expectedSecondArgument);
}

TEST_CASE ("PARSER - SUCH THAT CLAUSE USES CHECK WITH ARGUMENTS: STMT SYNONYM - CALL, WILDCARD") {
    QueryParser parser = QueryParser();

    std::string pql = "variable v; call c; stmt s; print pn; if ifs; while w; \nSelect v such that Uses(c, _)";
    Query query = parser.getQuery(pql);
    SuchThatClause suchThatClause = query.getSuchThatClauses()[0];
    std::vector<Argument> argList = suchThatClause.argList;

    CHECK(suchThatClause.relRef == RelRef::USES_S);

    Argument expectedFirstArgument = Argument();
    expectedFirstArgument.argumentValue = "c";
    expectedFirstArgument.argumentType = ArgumentType::SYNONYM;
    Argument expectedSecondArgument = Argument();
    expectedSecondArgument.argumentValue = "_";
    expectedSecondArgument.argumentType = ArgumentType::UNDERSCORE;

    CHECK(argList[0] == expectedFirstArgument);
    CHECK(argList[1] == expectedSecondArgument);
}

TEST_CASE ("PARSER - SUCH THAT CLAUSE USES CHECK WITH ARGUMENTS: STMT SYNONYM, SYNONYM") {
    QueryParser parser = QueryParser();

    std::string pql = "variable v; assign a; stmt s; \nSelect v such that Uses(a, v)";
    Query query = parser.getQuery(pql);
    SuchThatClause suchThatClause = query.getSuchThatClauses()[0];
    std::vector<Argument> argList = suchThatClause.argList;

    CHECK(suchThatClause.relRef == RelRef::USES_S);

    Argument expectedFirstArgument = Argument();
    expectedFirstArgument.argumentValue = "a";
    expectedFirstArgument.argumentType = ArgumentType::SYNONYM;
    Argument expectedSecondArgument = Argument();
    expectedSecondArgument.argumentValue = "v";
    expectedSecondArgument.argumentType = ArgumentType::SYNONYM;

    CHECK(argList[0] == expectedFirstArgument);
    CHECK(argList[1] == expectedSecondArgument);
}

TEST_CASE ("PARSER - SUCH THAT CLAUSE USES CHECK WITH ARGUMENTS: STMT SYNONYM, IDENT") {
    QueryParser parser = QueryParser();

    std::string pql = "variable v; assign a; stmt s; \nSelect v such that Uses(a, \"x\")";
    Query query = parser.getQuery(pql);
    SuchThatClause suchThatClause = query.getSuchThatClauses()[0];
    std::vector<Argument> argList = suchThatClause.argList;

    CHECK(suchThatClause.relRef == RelRef::USES_S);

    Argument expectedFirstArgument = Argument();
    expectedFirstArgument.argumentValue = "a";
    expectedFirstArgument.argumentType = ArgumentType::SYNONYM;
    Argument expectedSecondArgument = Argument();
    expectedSecondArgument.argumentValue = "x";
    expectedSecondArgument.argumentType = ArgumentType::IDENT;

    CHECK(argList[0] == expectedFirstArgument);
    CHECK(argList[1] == expectedSecondArgument);
}

TEST_CASE ("PARSER - SUCH THAT CLAUSE MODIFIES CHECK WITH ARGUMENTS: IDENT, WILDCARD") {
    QueryParser parser = QueryParser();

    std::string pql = "variable v; assign a; \nSelect v such that Modifies(\"x\", _)";
    Query query = parser.getQuery(pql);
    SuchThatClause suchThatClause = query.getSuchThatClauses()[0];
    std::vector<Argument> argList = suchThatClause.argList;

    CHECK(suchThatClause.relRef == RelRef::MODIFIES_P);

    Argument expectedFirstArgument = Argument();
    expectedFirstArgument.argumentValue = "x";
    expectedFirstArgument.argumentType = ArgumentType::IDENT;
    Argument expectedSecondArgument = Argument();
    expectedSecondArgument.argumentValue = "_";
    expectedSecondArgument.argumentType = ArgumentType::UNDERSCORE;

    CHECK(argList[0] == expectedFirstArgument);
    CHECK(argList[1] == expectedSecondArgument);
}

TEST_CASE ("PARSER - SUCH THAT CLAUSE MODIFIES CHECK WITH ARGUMENTS: STMT SYNONYM, WILDCARD") {
    QueryParser parser = QueryParser();

    std::string pql = "variable v; assign a; stmt s; \nSelect v such that Modifies(a, _)";
    Query query = parser.getQuery(pql);
    SuchThatClause suchThatClause = query.getSuchThatClauses()[0];
    std::vector<Argument> argList = suchThatClause.argList;

    CHECK(suchThatClause.relRef == RelRef::MODIFIES_S);

    Argument expectedFirstArgument = Argument();
    expectedFirstArgument.argumentValue = "a";
    expectedFirstArgument.argumentType = ArgumentType::SYNONYM;
    Argument expectedSecondArgument = Argument();
    expectedSecondArgument.argumentValue = "_";
    expectedSecondArgument.argumentType = ArgumentType::UNDERSCORE;

    CHECK(argList[0] == expectedFirstArgument);
    CHECK(argList[1] == expectedSecondArgument);
}

TEST_CASE ("PARSER - SUCH THAT CLAUSE MODIFIES CHECK WITH ARGUMENTS: STMT SYNONYM - READ, WILDCARD") {
    QueryParser parser = QueryParser();

    std::string pql = "variable v; assign a; stmt s; read r; \nSelect v such that Modifies(r, _)";
    Query query = parser.getQuery(pql);
    SuchThatClause suchThatClause = query.getSuchThatClauses()[0];
    std::vector<Argument> argList = suchThatClause.argList;

    CHECK(suchThatClause.relRef == RelRef::MODIFIES_S);

    Argument expectedFirstArgument = Argument();
    expectedFirstArgument.argumentValue = "r";
    expectedFirstArgument.argumentType = ArgumentType::SYNONYM;
    Argument expectedSecondArgument = Argument();
    expectedSecondArgument.argumentValue = "_";
    expectedSecondArgument.argumentType = ArgumentType::UNDERSCORE;

    CHECK(argList[0] == expectedFirstArgument);
    CHECK(argList[1] == expectedSecondArgument);
}
TEST_CASE ("PARSER - SUCH THAT CLAUSE MODIFIES CHECK WITH ARGUMENTS: STMT SYNONYM - IF, WILDCARD") {
    QueryParser parser = QueryParser();

    std::string pql = "variable v; assign a; stmt s; print pn; if ifs; \nSelect v such that Modifies(ifs, _)";
    Query query = parser.getQuery(pql);
    SuchThatClause suchThatClause = query.getSuchThatClauses()[0];
    std::vector<Argument> argList = suchThatClause.argList;

    CHECK(suchThatClause.relRef == RelRef::MODIFIES_S);

    Argument expectedFirstArgument = Argument();
    expectedFirstArgument.argumentValue = "ifs";
    expectedFirstArgument.argumentType = ArgumentType::SYNONYM;
    Argument expectedSecondArgument = Argument();
    expectedSecondArgument.argumentValue = "_";
    expectedSecondArgument.argumentType = ArgumentType::UNDERSCORE;

    CHECK(argList[0] == expectedFirstArgument);
    CHECK(argList[1] == expectedSecondArgument);
}

TEST_CASE ("PARSER - SUCH THAT CLAUSE MODIFIES CHECK WITH ARGUMENTS: STMT SYNONYM - WHILE, WILDCARD") {
    QueryParser parser = QueryParser();

    std::string pql = "variable v; assign a; stmt s; print pn; procedure p, q; if ifs; while w; \nSelect v such that Modifies(w, _)";
    Query query = parser.getQuery(pql);
    SuchThatClause suchThatClause = query.getSuchThatClauses()[0];
    std::vector<Argument> argList = suchThatClause.argList;

    CHECK(suchThatClause.relRef == RelRef::MODIFIES_S);

    Argument expectedFirstArgument = Argument();
    expectedFirstArgument.argumentValue = "w";
    expectedFirstArgument.argumentType = ArgumentType::SYNONYM;
    Argument expectedSecondArgument = Argument();
    expectedSecondArgument.argumentValue = "_";
    expectedSecondArgument.argumentType = ArgumentType::UNDERSCORE;

    CHECK(argList[0] == expectedFirstArgument);
    CHECK(argList[1] == expectedSecondArgument);
}

TEST_CASE ("PARSER - SUCH THAT CLAUSE MODIFIES CHECK WITH ARGUMENTS: STMT SYNONYM - CALL, WILDCARD") {
    QueryParser parser = QueryParser();

    std::string pql = "variable v; call c; stmt s; print pn; if ifs; while w; \nSelect v such that Modifies(c, _)";
    Query query = parser.getQuery(pql);
    SuchThatClause suchThatClause = query.getSuchThatClauses()[0];
    std::vector<Argument> argList = suchThatClause.argList;

    CHECK(suchThatClause.relRef == RelRef::MODIFIES_S);

    Argument expectedFirstArgument = Argument();
    expectedFirstArgument.argumentValue = "c";
    expectedFirstArgument.argumentType = ArgumentType::SYNONYM;
    Argument expectedSecondArgument = Argument();
    expectedSecondArgument.argumentValue = "_";
    expectedSecondArgument.argumentType = ArgumentType::UNDERSCORE;

    CHECK(argList[0] == expectedFirstArgument);
    CHECK(argList[1] == expectedSecondArgument);
}

TEST_CASE ("PARSER - SUCH THAT CLAUSE MODIFIES CHECK WITH ARGUMENTS: STMT SYNONYM, SYNONYM") {
    QueryParser parser = QueryParser();

    std::string pql = "variable v; assign a; stmt s; \nSelect v such that Modifies(a, v)";
    Query query = parser.getQuery(pql);
    SuchThatClause suchThatClause = query.getSuchThatClauses()[0];
    std::vector<Argument> argList = suchThatClause.argList;

    CHECK(suchThatClause.relRef == RelRef::MODIFIES_S);

    Argument expectedFirstArgument = Argument();
    expectedFirstArgument.argumentValue = "a";
    expectedFirstArgument.argumentType = ArgumentType::SYNONYM;
    Argument expectedSecondArgument = Argument();
    expectedSecondArgument.argumentValue = "v";
    expectedSecondArgument.argumentType = ArgumentType::SYNONYM;

    CHECK(argList[0] == expectedFirstArgument);
    CHECK(argList[1] == expectedSecondArgument);
}

TEST_CASE ("PARSER - SUCH THAT CLAUSE MODIFIES CHECK WITH ARGUMENTS: STMT SYNONYM, IDENT") {
    QueryParser parser = QueryParser();

    std::string pql = "variable v; assign a; stmt s; \nSelect v such that Modifies(a, \"x\")";
    Query query = parser.getQuery(pql);
    SuchThatClause suchThatClause = query.getSuchThatClauses()[0];
    std::vector<Argument> argList = suchThatClause.argList;

    CHECK(suchThatClause.relRef == RelRef::MODIFIES_S);

    Argument expectedFirstArgument = Argument();
    expectedFirstArgument.argumentValue = "a";
    expectedFirstArgument.argumentType = ArgumentType::SYNONYM;
    Argument expectedSecondArgument = Argument();
    expectedSecondArgument.argumentValue = "x";
    expectedSecondArgument.argumentType = ArgumentType::IDENT;

    CHECK(argList[0] == expectedFirstArgument);
    CHECK(argList[1] == expectedSecondArgument);
}

TEST_CASE ("PARSER - PATTERN CLAUSE CHECK WITH ARGUMENTS: IDENT, WILDCARD") {
    QueryParser parser = QueryParser();

    std::string pql = "variable v; assign a; stmt s; \nSelect v pattern a (\"x\", _)";
    Query query = parser.getQuery(pql);
    PatternClause patternClause = query.getPatternClauses()[0];
    std::vector<Argument> argList = patternClause.argList;

    Argument expectedFirstArgument = Argument();
    expectedFirstArgument.argumentValue = "a";
    expectedFirstArgument.argumentType = ArgumentType::SYNONYM;
    Argument expectedSecondArgument = Argument();
    expectedSecondArgument.argumentValue = "x";
    expectedSecondArgument.argumentType = ArgumentType::IDENT;
    Argument expectedThirdArgument = Argument();
    expectedThirdArgument.argumentValue = "_";
    expectedThirdArgument.argumentType = ArgumentType::UNDERSCORE;

    CHECK(argList[0] == expectedFirstArgument);
    CHECK(argList[1] == expectedSecondArgument);
    CHECK(argList[2] == expectedThirdArgument);
}

TEST_CASE ("PARSER - PATTERN CLAUSE CHECK WITH ARGUMENTS: WILDCARD, WILDCARD") {
    QueryParser parser = QueryParser();

    std::string pql = "variable v; assign a; stmt s; \nSelect v pattern a (_, _)";
    Query query = parser.getQuery(pql);
    PatternClause patternClause = query.getPatternClauses()[0];
    std::vector<Argument> argList = patternClause.argList;

    Argument expectedFirstArgument = Argument();
    expectedFirstArgument.argumentValue = "a";
    expectedFirstArgument.argumentType = ArgumentType::SYNONYM;
    Argument expectedSecondArgument = Argument();
    expectedSecondArgument.argumentValue = "_";
    expectedSecondArgument.argumentType = ArgumentType::UNDERSCORE;
    Argument expectedThirdArgument = Argument();
    expectedThirdArgument.argumentValue = "_";
    expectedThirdArgument.argumentType = ArgumentType::UNDERSCORE;

    CHECK(argList[0] == expectedFirstArgument);
    CHECK(argList[1] == expectedSecondArgument);
    CHECK(argList[2] == expectedThirdArgument);
}

TEST_CASE ("PARSER - PATTERN CLAUSE CHECK WITH ARGUMENTS: VARIABLE, WILDCARD") {
    QueryParser parser = QueryParser();

    std::string pql = "variable v; assign a; stmt s; \nSelect v pattern a (v, _)";
    Query query = parser.getQuery(pql);
    PatternClause patternClause = query.getPatternClauses()[0];
    std::vector<Argument> argList = patternClause.argList;

    Argument expectedFirstArgument = Argument();
    expectedFirstArgument.argumentValue = "a";
    expectedFirstArgument.argumentType = ArgumentType::SYNONYM;
    Argument expectedSecondArgument = Argument();
    expectedSecondArgument.argumentValue = "v";
    expectedSecondArgument.argumentType = ArgumentType::SYNONYM;
    Argument expectedThirdArgument = Argument();
    expectedThirdArgument.argumentValue = "_";
    expectedThirdArgument.argumentType = ArgumentType::UNDERSCORE;

    CHECK(argList[0] == expectedFirstArgument);
    CHECK(argList[1] == expectedSecondArgument);
    CHECK(argList[2] == expectedThirdArgument);
}

TEST_CASE ("PARSER - PATTERN CLAUSE CHECK WITH ARGUMENTS: VARIABLE, IDENT") {
    QueryParser parser = QueryParser();

    std::string pql = "variable v; assign a; stmt s; \nSelect v pattern a (v, \"x\")";
    Query query = parser.getQuery(pql);
    PatternClause patternClause = query.getPatternClauses()[0];
    std::vector<Argument> argList = patternClause.argList;

    Argument expectedFirstArgument = Argument();
    expectedFirstArgument.argumentValue = "a";
    expectedFirstArgument.argumentType = ArgumentType::SYNONYM;
    Argument expectedSecondArgument = Argument();
    expectedSecondArgument.argumentValue = "v";
    expectedSecondArgument.argumentType = ArgumentType::SYNONYM;
    Argument expectedThirdArgument = Argument();
    expectedThirdArgument.argumentValue = "x";
    expectedThirdArgument.argumentType = ArgumentType::IDENT;

    CHECK(argList[0] == expectedFirstArgument);
    CHECK(argList[1] == expectedSecondArgument);
    CHECK(argList[2] == expectedThirdArgument);
}

TEST_CASE ("PARSER - PATTERN CLAUSE CHECK WITH ARGUMENTS: VARIABLE, PARTIAL WILDCARD") {
    QueryParser parser = QueryParser();

    std::string pql = "variable v; assign a; stmt s; \nSelect v pattern a (v, _\"x\"_)";
    Query query = parser.getQuery(pql);
    PatternClause patternClause = query.getPatternClauses()[0];
    std::vector<Argument> argList = patternClause.argList;

    Argument expectedFirstArgument = Argument();
    expectedFirstArgument.argumentValue = "a";
    expectedFirstArgument.argumentType = ArgumentType::SYNONYM;
    Argument expectedSecondArgument = Argument();
    expectedSecondArgument.argumentValue = "v";
    expectedSecondArgument.argumentType = ArgumentType::SYNONYM;
    Argument expectedThirdArgument = Argument();
    expectedThirdArgument.argumentValue = "_\"x\"_";
    expectedThirdArgument.argumentType = ArgumentType::PARTIAL_UNDERSCORE;

    CHECK(argList[0] == expectedFirstArgument);
    CHECK(argList[1] == expectedSecondArgument);
    CHECK(argList[2] == expectedThirdArgument);
}

TEST_CASE ("PARSER - MULTICLAUSE CHECK") {
    QueryParser parser = QueryParser();

    std::string pql = "stmt s; assign a; \nSelect s such that Parent*(s,3) pattern a (_, _, _)";
    Query query = parser.getQuery(pql);
    SuchThatClause suchThatClause = query.getSuchThatClauses()[0];
    std::vector<Argument> argList = suchThatClause.argList;

    PatternClause patternClause = query.getPatternClauses()[0];
    std::vector<Argument> patternArgList = patternClause.argList;

    CHECK(suchThatClause.relRef == RelRef::PARENT_T);

    Argument expectedFirstArgument = Argument();
    expectedFirstArgument.argumentValue = "s";
    expectedFirstArgument.argumentType = ArgumentType::SYNONYM;
    Argument expectedSecondArgument = Argument();
    expectedSecondArgument.argumentValue = "3";
    expectedSecondArgument.argumentType = ArgumentType::STMT_NO;

    CHECK(argList[0] == expectedFirstArgument);
    CHECK(argList[1] == expectedSecondArgument);

    Argument expectedPatternFirstArgument = Argument();
    expectedPatternFirstArgument.argumentValue = "a";
    expectedPatternFirstArgument.argumentType = ArgumentType::SYNONYM;
    Argument expectedPatternSecondArgument = Argument();
    expectedPatternSecondArgument.argumentValue = "_";
    expectedPatternSecondArgument.argumentType = ArgumentType::UNDERSCORE;
    Argument expectedPatternThirdArgument = Argument();
    expectedPatternThirdArgument.argumentValue = "_";
    expectedPatternThirdArgument.argumentType = ArgumentType::UNDERSCORE;

    CHECK(patternArgList[0] == expectedPatternFirstArgument);
    CHECK(patternArgList[1] == expectedPatternSecondArgument);
    CHECK(patternArgList[2] == expectedPatternThirdArgument);
}


