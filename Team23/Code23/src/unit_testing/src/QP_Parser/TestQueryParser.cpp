#include "catch.hpp"
#include "QP_Parser/QueryParser.h"
#include "QP_Parser/Tokenizer.h"
#include "QP_Evaluator/Query/Query.h"

#include <string>
#include <regex>

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
    vector<Argument> resultArgs = query.getResultClause()->argList;

    CHECK(resultArgs[0] == expectedArgument);
    CHECK(query.findEntityType("v") == DesignEntity::VARIABLE);

    // constant design entity
    pql = "constant c; \nSelect c";
    query = parser.getQuery(pql);

    expectedArgument = Argument();
    expectedArgument.argumentValue = "c";
    expectedArgument.argumentType = ArgumentType::SYNONYM;
    resultArgs = query.getResultClause()->argList;

    CHECK(resultArgs[0] == expectedArgument);
    CHECK(query.findEntityType("c") == DesignEntity::CONSTANT);

    // procedure design entity
    pql = "procedure p; \nSelect p";
    query = parser.getQuery(pql);

    expectedArgument = Argument();
    expectedArgument.argumentValue = "p";
    expectedArgument.argumentType = ArgumentType::SYNONYM;
    resultArgs = query.getResultClause()->argList;

    CHECK(resultArgs[0] == expectedArgument);
    CHECK(query.findEntityType("p") == DesignEntity::PROCEDURE);

    // stmt design entity
    pql = "stmt s; \nSelect s";
    query = parser.getQuery(pql);

    expectedArgument = Argument();
    expectedArgument.argumentValue = "s";
    expectedArgument.argumentType = ArgumentType::SYNONYM;
    resultArgs = query.getResultClause()->argList;

    CHECK(resultArgs[0] == expectedArgument);
    CHECK(query.findEntityType("s") == DesignEntity::STMT);

    // read design entity
    pql = "read r; \nSelect r";
    query = parser.getQuery(pql);

    expectedArgument = Argument();
    expectedArgument.argumentValue = "r";
    expectedArgument.argumentType = ArgumentType::SYNONYM;
    resultArgs = query.getResultClause()->argList;

    CHECK(resultArgs[0] == expectedArgument);
    CHECK(query.findEntityType("r") == DesignEntity::READ);

    // print design entity
    pql = "print pn; \nSelect pn";
    query = parser.getQuery(pql);

    expectedArgument = Argument();
    expectedArgument.argumentValue = "pn";
    expectedArgument.argumentType = ArgumentType::SYNONYM;
    resultArgs = query.getResultClause()->argList;

    CHECK(resultArgs[0] == expectedArgument);
    CHECK(query.findEntityType("pn") == DesignEntity::PRINT);

    // assign design entity
    pql = "assign a; \nSelect a";
    query = parser.getQuery(pql);

    expectedArgument = Argument();
    expectedArgument.argumentValue = "a";
    expectedArgument.argumentType = ArgumentType::SYNONYM;
    resultArgs = query.getResultClause()->argList;

    CHECK(resultArgs[0] == expectedArgument);
    CHECK(query.findEntityType("a") == DesignEntity::ASSIGN);

    // call design entity
    pql = "call c; \nSelect c";
    query = parser.getQuery(pql);

    expectedArgument = Argument();
    expectedArgument.argumentValue = "c";
    expectedArgument.argumentType = ArgumentType::SYNONYM;
    resultArgs = query.getResultClause()->argList;

    CHECK(resultArgs[0] == expectedArgument);
    CHECK(query.findEntityType("c") == DesignEntity::CALL);

    // while design entity
    pql = "while w; \nSelect w";
    query = parser.getQuery(pql);

    expectedArgument = Argument();
    expectedArgument.argumentValue = "w";
    expectedArgument.argumentType = ArgumentType::SYNONYM;
    resultArgs = query.getResultClause()->argList;

    CHECK(resultArgs[0] == expectedArgument);
    CHECK(query.findEntityType("w") == DesignEntity::WHILE);

    // if design entity
    pql = "if ifs; \nSelect ifs";
    query = parser.getQuery(pql);

    expectedArgument = Argument();
    expectedArgument.argumentValue = "ifs";
    expectedArgument.argumentType = ArgumentType::SYNONYM;
    resultArgs = query.getResultClause()->argList;

    CHECK(resultArgs[0] == expectedArgument);
    CHECK(query.findEntityType("ifs") == DesignEntity::IF);

    // multiple declarations
    pql = "if ifs; assign a; \nSelect ifs";
    query = parser.getQuery(pql);

    expectedArgument = Argument();
    expectedArgument.argumentValue = "ifs";
    expectedArgument.argumentType = ArgumentType::SYNONYM;
    resultArgs = query.getResultClause()->argList;

    CHECK(resultArgs[0] == expectedArgument);
    CHECK(query.findEntityType("ifs") == DesignEntity::IF);
    CHECK(query.findEntityType("a") == DesignEntity::ASSIGN);

    // multiple declarations under same design entity
    pql = "assign a1, a2; \nSelect a1";
    query = parser.getQuery(pql);

    expectedArgument = Argument();
    expectedArgument.argumentValue = "a1";
    expectedArgument.argumentType = ArgumentType::SYNONYM;
    resultArgs = query.getResultClause()->argList;

    CHECK(resultArgs[0] == expectedArgument);
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
    vector<Argument> resultArgs = query.getResultClause()->argList;

    CHECK(resultArgs[0] == expectedArgument);

    // synonym named pattern
    pql = "variable pattern; \nSelect pattern";
    query = parser.getQuery(pql);

    expectedArgument = Argument();
    expectedArgument.argumentValue = "pattern";
    expectedArgument.argumentType = ArgumentType::SYNONYM;
    resultArgs = query.getResultClause()->argList;

    CHECK(resultArgs[0] == expectedArgument);

    // synonym named pattern with pattern clause
    pql = "assign pattern; \nSelect pattern pattern pattern(_, _)";
    query = parser.getQuery(pql);

    expectedArgument = Argument();
    expectedArgument.argumentValue = "pattern";
    expectedArgument.argumentType = ArgumentType::SYNONYM;
    resultArgs = query.getResultClause()->argList;

    CHECK(resultArgs[0] == expectedArgument);

    // synonym named with
    pql = "assign with; \nSelect with pattern with(_, _)";
    query = parser.getQuery(pql);

    expectedArgument = Argument();
    expectedArgument.argumentValue = "with";
    expectedArgument.argumentType = ArgumentType::SYNONYM;
    resultArgs = query.getResultClause()->argList;

    CHECK(resultArgs[0] == expectedArgument);

    // synonym named and
    pql = "assign a, and; \nSelect and pattern a(_, _) and and(_, _)";
    query = parser.getQuery(pql);

    expectedArgument = Argument();
    expectedArgument.argumentValue = "and";
    expectedArgument.argumentType = ArgumentType::SYNONYM;
    resultArgs = query.getResultClause()->argList;

    CHECK(resultArgs[0] == expectedArgument);
    CHECK(query.getPatternClauses()->size() == 2);

    // tuple: one element
    pql = "assign a; \nSelect <a>";
    query = parser.getQuery(pql);

    expectedArgument = Argument();
    expectedArgument.argumentValue = "a";
    expectedArgument.argumentType = ArgumentType::SYNONYM;
    resultArgs = query.getResultClause()->argList;

    CHECK(resultArgs[0] == expectedArgument);

    // tuple: multiple elements
    pql = "assign a1, a2; procedure p; \nSelect <a1, a2, p.procName>";
    query = parser.getQuery(pql);

    Argument firstArgument = Argument();
    firstArgument.argumentValue = "a1";
    firstArgument.argumentType = ArgumentType::SYNONYM;

    Argument secondArgument = Argument();
    secondArgument.argumentValue = "a2";
    secondArgument.argumentType = ArgumentType::SYNONYM;

    Argument thirdArgument = Argument();
    thirdArgument.argumentValue = std::pair<std::string, AttrName>("p", AttrName::PROC_NAME);
    thirdArgument.argumentType = ArgumentType::ATTR_REF;

    std::vector<Argument> synonymList = std::vector<Argument>({firstArgument, secondArgument, thirdArgument});
    auto synonyms = query.getResultClause()->argList;

    CHECK(synonyms[0] == synonymList[0]);
    CHECK(synonyms[1] == synonymList[1]);
    CHECK(synonyms[2] == synonymList[2]);

    // synonym is an attr ref
    pql = "stmt s; \nSelect s.stmt#";
    query = parser.getQuery(pql);

    expectedArgument = Argument();
    expectedArgument.argumentValue = std::pair<std::string, AttrName>("s", AttrName::STMT_NO);
    expectedArgument.argumentType = ArgumentType::ATTR_REF;
    synonyms = query.getResultClause()->argList;

    CHECK(synonyms[0] == expectedArgument);

    // synonym is boolean
    pql = "stmt s; \nSelect BOOLEAN";
    query = parser.getQuery(pql);

    expectedArgument = Argument();
    expectedArgument.argumentValue = "";
    expectedArgument.argumentType = ArgumentType::BOOLEAN;
    synonyms = query.getResultClause()->argList;

    CHECK(synonyms[0] == expectedArgument);
}

TEST_CASE ("PARSER - SUCH THAT CLAUSE FOLLOWS CHECK WITH ARGUMENTS: SYNONYM, WILDCARD") {
    QueryParser parser = QueryParser();

    std::string pql = "stmt s; \nSelect s such that Follows(s,_)";
    Query query = parser.getQuery(pql);
    SuchThatClause suchThatClause = (*query.getSuchThatClauses())[0];
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
    SuchThatClause suchThatClause = (*query.getSuchThatClauses())[0];
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
    SuchThatClause suchThatClause = (*query.getSuchThatClauses())[0];
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
    SuchThatClause suchThatClause = (*query.getSuchThatClauses())[0];
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
    SuchThatClause suchThatClause = (*query.getSuchThatClauses())[0];
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
    SuchThatClause suchThatClause = (*query.getSuchThatClauses())[0];
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
    SuchThatClause suchThatClause = (*query.getSuchThatClauses())[0];
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
    SuchThatClause suchThatClause = (*query.getSuchThatClauses())[0];
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
    SuchThatClause suchThatClause = (*query.getSuchThatClauses())[0];
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
    SuchThatClause suchThatClause = (*query.getSuchThatClauses())[0];
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
    SuchThatClause suchThatClause = (*query.getSuchThatClauses())[0];
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
    SuchThatClause suchThatClause = (*query.getSuchThatClauses())[0];
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
    SuchThatClause suchThatClause = (*query.getSuchThatClauses())[0];
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
    SuchThatClause suchThatClause = (*query.getSuchThatClauses())[0];
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
    SuchThatClause suchThatClause = (*query.getSuchThatClauses())[0];
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
    SuchThatClause suchThatClause = (*query.getSuchThatClauses())[0];
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
    SuchThatClause suchThatClause = (*query.getSuchThatClauses())[0];
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
    SuchThatClause suchThatClause = (*query.getSuchThatClauses())[0];
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
    SuchThatClause suchThatClause = (*query.getSuchThatClauses())[0];
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
    SuchThatClause suchThatClause = (*query.getSuchThatClauses())[0];
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
    SuchThatClause suchThatClause = (*query.getSuchThatClauses())[0];
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
    SuchThatClause suchThatClause = (*query.getSuchThatClauses())[0];
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
    SuchThatClause suchThatClause = (*query.getSuchThatClauses())[0];
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
    SuchThatClause suchThatClause = (*query.getSuchThatClauses())[0];
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
    SuchThatClause suchThatClause = (*query.getSuchThatClauses())[0];
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
    SuchThatClause suchThatClause = (*query.getSuchThatClauses())[0];
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
    SuchThatClause suchThatClause = (*query.getSuchThatClauses())[0];
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
    SuchThatClause suchThatClause = (*query.getSuchThatClauses())[0];
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
    SuchThatClause suchThatClause = (*query.getSuchThatClauses())[0];
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
    SuchThatClause suchThatClause = (*query.getSuchThatClauses())[0];
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
    SuchThatClause suchThatClause = (*query.getSuchThatClauses())[0];
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
    SuchThatClause suchThatClause = (*query.getSuchThatClauses())[0];
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
    SuchThatClause suchThatClause = (*query.getSuchThatClauses())[0];
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
    SuchThatClause suchThatClause = (*query.getSuchThatClauses())[0];
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
    SuchThatClause suchThatClause = (*query.getSuchThatClauses())[0];
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
    SuchThatClause suchThatClause = (*query.getSuchThatClauses())[0];
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

TEST_CASE ("PARSER - SUCH THAT CLAUSE NEXT CHECK WITH ARGUMENTS: SYNONYM, WILDCARD") {
    QueryParser parser = QueryParser();

    std::string pql = "stmt s; \nSelect s such that Next(s,_)";
    Query query = parser.getQuery(pql);
    SuchThatClause suchThatClause = (*query.getSuchThatClauses())[0];
    std::vector<Argument> argList = suchThatClause.argList;

    CHECK(suchThatClause.relRef == RelRef::NEXT);

    Argument expectedFirstArgument = Argument();
    expectedFirstArgument.argumentValue = "s";
    expectedFirstArgument.argumentType = ArgumentType::SYNONYM;
    Argument expectedSecondArgument = Argument();
    expectedSecondArgument.argumentValue = "_";
    expectedSecondArgument.argumentType = ArgumentType::UNDERSCORE;

    CHECK(argList[0] == expectedFirstArgument);
    CHECK(argList[1] == expectedSecondArgument);
}

TEST_CASE ("PARSER - SUCH THAT CLAUSE NEXT CHECK WITH ARGUMENTS: SYNONYM, INTEGER") {
    QueryParser parser = QueryParser();

    std::string pql = "stmt s; \nSelect s such that Next(s,3)";
    Query query = parser.getQuery(pql);
    SuchThatClause suchThatClause = (*query.getSuchThatClauses())[0];
    std::vector<Argument> argList = suchThatClause.argList;

    CHECK(suchThatClause.relRef == RelRef::NEXT);

    Argument expectedFirstArgument = Argument();
    expectedFirstArgument.argumentValue = "s";
    expectedFirstArgument.argumentType = ArgumentType::SYNONYM;
    Argument expectedSecondArgument = Argument();
    expectedSecondArgument.argumentValue = "3";
    expectedSecondArgument.argumentType = ArgumentType::STMT_NO;

    CHECK(argList[0] == expectedFirstArgument);
    CHECK(argList[1] == expectedSecondArgument);
}

TEST_CASE ("PARSER - SUCH THAT CLAUSE NEXT CHECK WITH ARGUMENTS: SYNONYM, SYNONYM") {
    QueryParser parser = QueryParser();

    std::string pql = "stmt s1, s2; \nSelect s1 such that Next(s1, s2)";
    Query query = parser.getQuery(pql);
    SuchThatClause suchThatClause = (*query.getSuchThatClauses())[0];
    std::vector<Argument> argList = suchThatClause.argList;

    CHECK(suchThatClause.relRef == RelRef::NEXT);

    Argument expectedFirstArgument = Argument();
    expectedFirstArgument.argumentValue = "s1";
    expectedFirstArgument.argumentType = ArgumentType::SYNONYM;
    Argument expectedSecondArgument = Argument();
    expectedSecondArgument.argumentValue = "s2";
    expectedSecondArgument.argumentType = ArgumentType::SYNONYM;

    CHECK(argList[0] == expectedFirstArgument);
    CHECK(argList[1] == expectedSecondArgument);
}

TEST_CASE ("PARSER - SUCH THAT CLAUSE NEXT CHECK WITH ARGUMENTS: INTEGER, SYNONYM") {
    QueryParser parser = QueryParser();

    std::string pql = "stmt s1, s2; \nSelect s1 such that Next(3, s2)";
    Query query = parser.getQuery(pql);
    SuchThatClause suchThatClause = (*query.getSuchThatClauses())[0];
    std::vector<Argument> argList = suchThatClause.argList;

    CHECK(suchThatClause.relRef == RelRef::NEXT);

    Argument expectedFirstArgument = Argument();
    expectedFirstArgument.argumentValue = "3";
    expectedFirstArgument.argumentType = ArgumentType::STMT_NO;
    Argument expectedSecondArgument = Argument();
    expectedSecondArgument.argumentValue = "s2";
    expectedSecondArgument.argumentType = ArgumentType::SYNONYM;

    CHECK(argList[0] == expectedFirstArgument);
    CHECK(argList[1] == expectedSecondArgument);
}

TEST_CASE ("PARSER - SUCH THAT CLAUSE NEXT CHECK WITH ARGUMENTS: WILDCARD, SYNONYM") {
    QueryParser parser = QueryParser();

    std::string pql = "stmt s1, s2; \nSelect s1 such that Next(_, s2)";
    Query query = parser.getQuery(pql);
    SuchThatClause suchThatClause = (*query.getSuchThatClauses())[0];
    std::vector<Argument> argList = suchThatClause.argList;

    CHECK(suchThatClause.relRef == RelRef::NEXT);

    Argument expectedFirstArgument = Argument();
    expectedFirstArgument.argumentValue = "_";
    expectedFirstArgument.argumentType = ArgumentType::UNDERSCORE;
    Argument expectedSecondArgument = Argument();
    expectedSecondArgument.argumentValue = "s2";
    expectedSecondArgument.argumentType = ArgumentType::SYNONYM;

    CHECK(argList[0] == expectedFirstArgument);
    CHECK(argList[1] == expectedSecondArgument);
}

TEST_CASE ("PARSER - SUCH THAT CLAUSE NEXT* CHECK WITH ARGUMENTS: SYNONYM, WILDCARD") {
    QueryParser parser = QueryParser();

    std::string pql = "stmt s; \nSelect s such that Next*(s,_)";
    Query query = parser.getQuery(pql);
    SuchThatClause suchThatClause = (*query.getSuchThatClauses())[0];
    std::vector<Argument> argList = suchThatClause.argList;

    CHECK(suchThatClause.relRef == RelRef::NEXT_T);

    Argument expectedFirstArgument = Argument();
    expectedFirstArgument.argumentValue = "s";
    expectedFirstArgument.argumentType = ArgumentType::SYNONYM;
    Argument expectedSecondArgument = Argument();
    expectedSecondArgument.argumentValue = "_";
    expectedSecondArgument.argumentType = ArgumentType::UNDERSCORE;

    CHECK(argList[0] == expectedFirstArgument);
    CHECK(argList[1] == expectedSecondArgument);
}

TEST_CASE ("PARSER - SUCH THAT CLAUSE NEXT* CHECK WITH ARGUMENTS: SYNONYM, INTEGER") {
    QueryParser parser = QueryParser();

    std::string pql = "stmt s; \nSelect s such that Next*(s,3)";
    Query query = parser.getQuery(pql);
    SuchThatClause suchThatClause = (*query.getSuchThatClauses())[0];
    std::vector<Argument> argList = suchThatClause.argList;

    CHECK(suchThatClause.relRef == RelRef::NEXT_T);

    Argument expectedFirstArgument = Argument();
    expectedFirstArgument.argumentValue = "s";
    expectedFirstArgument.argumentType = ArgumentType::SYNONYM;
    Argument expectedSecondArgument = Argument();
    expectedSecondArgument.argumentValue = "3";
    expectedSecondArgument.argumentType = ArgumentType::STMT_NO;

    CHECK(argList[0] == expectedFirstArgument);
    CHECK(argList[1] == expectedSecondArgument);
}

TEST_CASE ("PARSER - SUCH THAT CLAUSE NEXT* CHECK WITH ARGUMENTS: SYNONYM, SYNONYM") {
    QueryParser parser = QueryParser();

    std::string pql = "stmt s1, s2; \nSelect s1 such that Next*(s1, s2)";
    Query query = parser.getQuery(pql);
    SuchThatClause suchThatClause = (*query.getSuchThatClauses())[0];
    std::vector<Argument> argList = suchThatClause.argList;

    CHECK(suchThatClause.relRef == RelRef::NEXT_T);

    Argument expectedFirstArgument = Argument();
    expectedFirstArgument.argumentValue = "s1";
    expectedFirstArgument.argumentType = ArgumentType::SYNONYM;
    Argument expectedSecondArgument = Argument();
    expectedSecondArgument.argumentValue = "s2";
    expectedSecondArgument.argumentType = ArgumentType::SYNONYM;

    CHECK(argList[0] == expectedFirstArgument);
    CHECK(argList[1] == expectedSecondArgument);
}

TEST_CASE ("PARSER - SUCH THAT CLAUSE NEXT* CHECK WITH ARGUMENTS: INTEGER, SYNONYM") {
    QueryParser parser = QueryParser();

    std::string pql = "stmt s1, s2; \nSelect s1 such that Next*(3, s2)";
    Query query = parser.getQuery(pql);
    SuchThatClause suchThatClause = (*query.getSuchThatClauses())[0];
    std::vector<Argument> argList = suchThatClause.argList;

    CHECK(suchThatClause.relRef == RelRef::NEXT_T);

    Argument expectedFirstArgument = Argument();
    expectedFirstArgument.argumentValue = "3";
    expectedFirstArgument.argumentType = ArgumentType::STMT_NO;
    Argument expectedSecondArgument = Argument();
    expectedSecondArgument.argumentValue = "s2";
    expectedSecondArgument.argumentType = ArgumentType::SYNONYM;

    CHECK(argList[0] == expectedFirstArgument);
    CHECK(argList[1] == expectedSecondArgument);
}

TEST_CASE ("PARSER - SUCH THAT CLAUSE NEXT* CHECK WITH ARGUMENTS: WILDCARD, SYNONYM") {
    QueryParser parser = QueryParser();

    std::string pql = "stmt s1, s2; \nSelect s1 such that Next*(_, s2)";
    Query query = parser.getQuery(pql);
    SuchThatClause suchThatClause = (*query.getSuchThatClauses())[0];
    std::vector<Argument> argList = suchThatClause.argList;

    CHECK(suchThatClause.relRef == RelRef::NEXT_T);

    Argument expectedFirstArgument = Argument();
    expectedFirstArgument.argumentValue = "_";
    expectedFirstArgument.argumentType = ArgumentType::UNDERSCORE;
    Argument expectedSecondArgument = Argument();
    expectedSecondArgument.argumentValue = "s2";
    expectedSecondArgument.argumentType = ArgumentType::SYNONYM;

    CHECK(argList[0] == expectedFirstArgument);
    CHECK(argList[1] == expectedSecondArgument);
}

TEST_CASE ("PARSER - SUCH THAT CLAUSE AFFECTS CHECK WITH ARGUMENTS: SYNONYM, WILDCARD") {
    QueryParser parser = QueryParser();

    std::string pql = "assign a; \nSelect a such that Affects(a,_)";
    Query query = parser.getQuery(pql);
    SuchThatClause suchThatClause = (*query.getSuchThatClauses())[0];
    std::vector<Argument> argList = suchThatClause.argList;

    CHECK(suchThatClause.relRef == RelRef::AFFECTS);

    Argument expectedFirstArgument = Argument();
    expectedFirstArgument.argumentValue = "a";
    expectedFirstArgument.argumentType = ArgumentType::SYNONYM;
    Argument expectedSecondArgument = Argument();
    expectedSecondArgument.argumentValue = "_";
    expectedSecondArgument.argumentType = ArgumentType::UNDERSCORE;

    CHECK(argList[0] == expectedFirstArgument);
    CHECK(argList[1] == expectedSecondArgument);
}

TEST_CASE ("PARSER - SUCH THAT CLAUSE AFFECTS CHECK WITH ARGUMENTS: SYNONYM, INTEGER") {
    QueryParser parser = QueryParser();

    std::string pql = "assign a; \nSelect a such that Affects(a,3)";
    Query query = parser.getQuery(pql);
    SuchThatClause suchThatClause = (*query.getSuchThatClauses())[0];
    std::vector<Argument> argList = suchThatClause.argList;

    CHECK(suchThatClause.relRef == RelRef::AFFECTS);

    Argument expectedFirstArgument = Argument();
    expectedFirstArgument.argumentValue = "a";
    expectedFirstArgument.argumentType = ArgumentType::SYNONYM;
    Argument expectedSecondArgument = Argument();
    expectedSecondArgument.argumentValue = "3";
    expectedSecondArgument.argumentType = ArgumentType::STMT_NO;

    CHECK(argList[0] == expectedFirstArgument);
    CHECK(argList[1] == expectedSecondArgument);
}

TEST_CASE ("PARSER - SUCH THAT CLAUSE AFFECTS CHECK WITH ARGUMENTS: SYNONYM, SYNONYM") {
    QueryParser parser = QueryParser();

    std::string pql = "assign a1, a2; \nSelect a1 such that Affects(a1, a2)";
    Query query = parser.getQuery(pql);
    SuchThatClause suchThatClause = (*query.getSuchThatClauses())[0];
    std::vector<Argument> argList = suchThatClause.argList;

    CHECK(suchThatClause.relRef == RelRef::AFFECTS);

    Argument expectedFirstArgument = Argument();
    expectedFirstArgument.argumentValue = "a1";
    expectedFirstArgument.argumentType = ArgumentType::SYNONYM;
    Argument expectedSecondArgument = Argument();
    expectedSecondArgument.argumentValue = "a2";
    expectedSecondArgument.argumentType = ArgumentType::SYNONYM;

    CHECK(argList[0] == expectedFirstArgument);
    CHECK(argList[1] == expectedSecondArgument);
}

TEST_CASE ("PARSER - SUCH THAT CLAUSE AFFECTS CHECK WITH ARGUMENTS: INTEGER, SYNONYM") {
    QueryParser parser = QueryParser();

    std::string pql = "assign a1, a2; \nSelect a1 such that Affects(3, a2)";
    Query query = parser.getQuery(pql);
    SuchThatClause suchThatClause = (*query.getSuchThatClauses())[0];
    std::vector<Argument> argList = suchThatClause.argList;

    CHECK(suchThatClause.relRef == RelRef::AFFECTS);

    Argument expectedFirstArgument = Argument();
    expectedFirstArgument.argumentValue = "3";
    expectedFirstArgument.argumentType = ArgumentType::STMT_NO;
    Argument expectedSecondArgument = Argument();
    expectedSecondArgument.argumentValue = "a2";
    expectedSecondArgument.argumentType = ArgumentType::SYNONYM;

    CHECK(argList[0] == expectedFirstArgument);
    CHECK(argList[1] == expectedSecondArgument);
}

TEST_CASE ("PARSER - SUCH THAT CLAUSE AFFECTS CHECK WITH ARGUMENTS: WILDCARD, SYNONYM") {
    QueryParser parser = QueryParser();

    std::string pql = "assign a1, a2; \nSelect a1 such that Affects(_, a2)";
    Query query = parser.getQuery(pql);
    SuchThatClause suchThatClause = (*query.getSuchThatClauses())[0];
    std::vector<Argument> argList = suchThatClause.argList;

    CHECK(suchThatClause.relRef == RelRef::AFFECTS);

    Argument expectedFirstArgument = Argument();
    expectedFirstArgument.argumentValue = "_";
    expectedFirstArgument.argumentType = ArgumentType::UNDERSCORE;
    Argument expectedSecondArgument = Argument();
    expectedSecondArgument.argumentValue = "a2";
    expectedSecondArgument.argumentType = ArgumentType::SYNONYM;

    CHECK(argList[0] == expectedFirstArgument);
    CHECK(argList[1] == expectedSecondArgument);
}

TEST_CASE ("PARSER - SUCH THAT CLAUSE AFFECTS* CHECK WITH ARGUMENTS: SYNONYM, WILDCARD") {
    QueryParser parser = QueryParser();

    std::string pql = "assign a; \nSelect a such that Affects*(a,_)";
    Query query = parser.getQuery(pql);
    SuchThatClause suchThatClause = (*query.getSuchThatClauses())[0];
    std::vector<Argument> argList = suchThatClause.argList;

    CHECK(suchThatClause.relRef == RelRef::AFFECTS_T);

    Argument expectedFirstArgument = Argument();
    expectedFirstArgument.argumentValue = "a";
    expectedFirstArgument.argumentType = ArgumentType::SYNONYM;
    Argument expectedSecondArgument = Argument();
    expectedSecondArgument.argumentValue = "_";
    expectedSecondArgument.argumentType = ArgumentType::UNDERSCORE;

    CHECK(argList[0] == expectedFirstArgument);
    CHECK(argList[1] == expectedSecondArgument);
}

TEST_CASE ("PARSER - SUCH THAT CLAUSE AFFECTS* CHECK WITH ARGUMENTS: SYNONYM, INTEGER") {
    QueryParser parser = QueryParser();

    std::string pql = "assign a; \nSelect a such that Affects*(a,3)";
    Query query = parser.getQuery(pql);
    SuchThatClause suchThatClause = (*query.getSuchThatClauses())[0];
    std::vector<Argument> argList = suchThatClause.argList;

    CHECK(suchThatClause.relRef == RelRef::AFFECTS_T);

    Argument expectedFirstArgument = Argument();
    expectedFirstArgument.argumentValue = "a";
    expectedFirstArgument.argumentType = ArgumentType::SYNONYM;
    Argument expectedSecondArgument = Argument();
    expectedSecondArgument.argumentValue = "3";
    expectedSecondArgument.argumentType = ArgumentType::STMT_NO;

    CHECK(argList[0] == expectedFirstArgument);
    CHECK(argList[1] == expectedSecondArgument);
}

TEST_CASE ("PARSER - SUCH THAT CLAUSE AFFECTS* CHECK WITH ARGUMENTS: SYNONYM, SYNONYM") {
    QueryParser parser = QueryParser();

    std::string pql = "assign a1, a2; \nSelect a1 such that Affects*(a1, a2)";
    Query query = parser.getQuery(pql);
    SuchThatClause suchThatClause = (*query.getSuchThatClauses())[0];
    std::vector<Argument> argList = suchThatClause.argList;

    CHECK(suchThatClause.relRef == RelRef::AFFECTS_T);

    Argument expectedFirstArgument = Argument();
    expectedFirstArgument.argumentValue = "a1";
    expectedFirstArgument.argumentType = ArgumentType::SYNONYM;
    Argument expectedSecondArgument = Argument();
    expectedSecondArgument.argumentValue = "a2";
    expectedSecondArgument.argumentType = ArgumentType::SYNONYM;

    CHECK(argList[0] == expectedFirstArgument);
    CHECK(argList[1] == expectedSecondArgument);
}

TEST_CASE ("PARSER - SUCH THAT CLAUSE AFFECTS* CHECK WITH ARGUMENTS: INTEGER, SYNONYM") {
    QueryParser parser = QueryParser();

    std::string pql = "assign a1, a2; \nSelect a1 such that Affects*(3, a2)";
    Query query = parser.getQuery(pql);
    SuchThatClause suchThatClause = (*query.getSuchThatClauses())[0];
    std::vector<Argument> argList = suchThatClause.argList;

    CHECK(suchThatClause.relRef == RelRef::AFFECTS_T);

    Argument expectedFirstArgument = Argument();
    expectedFirstArgument.argumentValue = "3";
    expectedFirstArgument.argumentType = ArgumentType::STMT_NO;
    Argument expectedSecondArgument = Argument();
    expectedSecondArgument.argumentValue = "a2";
    expectedSecondArgument.argumentType = ArgumentType::SYNONYM;

    CHECK(argList[0] == expectedFirstArgument);
    CHECK(argList[1] == expectedSecondArgument);
}

TEST_CASE ("PARSER - SUCH THAT CLAUSE AFFECTS* CHECK WITH ARGUMENTS: WILDCARD, SYNONYM") {
    QueryParser parser = QueryParser();

    std::string pql = "assign a1, a2; \nSelect a1 such that Affects*(_, a2)";
    Query query = parser.getQuery(pql);
    SuchThatClause suchThatClause = (*query.getSuchThatClauses())[0];
    std::vector<Argument> argList = suchThatClause.argList;

    CHECK(suchThatClause.relRef == RelRef::AFFECTS_T);

    Argument expectedFirstArgument = Argument();
    expectedFirstArgument.argumentValue = "_";
    expectedFirstArgument.argumentType = ArgumentType::UNDERSCORE;
    Argument expectedSecondArgument = Argument();
    expectedSecondArgument.argumentValue = "a2";
    expectedSecondArgument.argumentType = ArgumentType::SYNONYM;

    CHECK(argList[0] == expectedFirstArgument);
    CHECK(argList[1] == expectedSecondArgument);
}

TEST_CASE ("PARSER - SUCH THAT CLAUSE CALLS CHECK WITH ARGUMENTS: IDENT, WILDCARD") {
    QueryParser parser = QueryParser();

    std::string pql = "procedure p; \nSelect p such that Calls(\"x\", _)";
    Query query = parser.getQuery(pql);
    SuchThatClause suchThatClause = (*query.getSuchThatClauses())[0];
    std::vector<Argument> argList = suchThatClause.argList;

    CHECK(suchThatClause.relRef == RelRef::CALLS);

    Argument expectedFirstArgument = Argument();
    expectedFirstArgument.argumentValue = "x";
    expectedFirstArgument.argumentType = ArgumentType::IDENT;
    Argument expectedSecondArgument = Argument();
    expectedSecondArgument.argumentValue = "_";
    expectedSecondArgument.argumentType = ArgumentType::UNDERSCORE;

    CHECK(argList[0] == expectedFirstArgument);
    CHECK(argList[1] == expectedSecondArgument);
}

TEST_CASE ("PARSER - SUCH THAT CLAUSE CALLS CHECK WITH ARGUMENTS: SYNONYM, IDENT") {
    QueryParser parser = QueryParser();

    std::string pql = "procedure p; \nSelect p such that Calls(p, \"x\")";
    Query query = parser.getQuery(pql);
    SuchThatClause suchThatClause = (*query.getSuchThatClauses())[0];
    std::vector<Argument> argList = suchThatClause.argList;

    CHECK(suchThatClause.relRef == RelRef::CALLS);

    Argument expectedFirstArgument = Argument();
    expectedFirstArgument.argumentValue = "p";
    expectedFirstArgument.argumentType = ArgumentType::SYNONYM;
    Argument expectedSecondArgument = Argument();
    expectedSecondArgument.argumentValue = "x";
    expectedSecondArgument.argumentType = ArgumentType::IDENT;

    CHECK(argList[0] == expectedFirstArgument);
    CHECK(argList[1] == expectedSecondArgument);
}

TEST_CASE ("PARSER - SUCH THAT CLAUSE CALLS CHECK WITH ARGUMENTS: WILDCARD, SYNONYM") {
    QueryParser parser = QueryParser();

    std::string pql = "procedure p; \nSelect p such that Calls(_, p)";
    Query query = parser.getQuery(pql);
    SuchThatClause suchThatClause = (*query.getSuchThatClauses())[0];
    std::vector<Argument> argList = suchThatClause.argList;

    CHECK(suchThatClause.relRef == RelRef::CALLS);

    Argument expectedFirstArgument = Argument();
    expectedFirstArgument.argumentValue = "_";
    expectedFirstArgument.argumentType = ArgumentType::UNDERSCORE;
    Argument expectedSecondArgument = Argument();
    expectedSecondArgument.argumentValue = "p";
    expectedSecondArgument.argumentType = ArgumentType::SYNONYM;

    CHECK(argList[0] == expectedFirstArgument);
    CHECK(argList[1] == expectedSecondArgument);
}

TEST_CASE ("PARSER - SUCH THAT CLAUSE CALLS* CHECK WITH ARGUMENTS: IDENT, WILDCARD") {
    QueryParser parser = QueryParser();

    std::string pql = "procedure p; \nSelect p such that Calls*(\"x\", _)";
    Query query = parser.getQuery(pql);
    SuchThatClause suchThatClause = (*query.getSuchThatClauses())[0];
    std::vector<Argument> argList = suchThatClause.argList;

    CHECK(suchThatClause.relRef == RelRef::CALLS_T);

    Argument expectedFirstArgument = Argument();
    expectedFirstArgument.argumentValue = "x";
    expectedFirstArgument.argumentType = ArgumentType::IDENT;
    Argument expectedSecondArgument = Argument();
    expectedSecondArgument.argumentValue = "_";
    expectedSecondArgument.argumentType = ArgumentType::UNDERSCORE;

    CHECK(argList[0] == expectedFirstArgument);
    CHECK(argList[1] == expectedSecondArgument);
}

TEST_CASE ("PARSER - SUCH THAT CLAUSE CALLS* CHECK WITH ARGUMENTS: SYNONYM, IDENT") {
    QueryParser parser = QueryParser();

    std::string pql = "procedure p; \nSelect p such that Calls*(p, \"x\")";
    Query query = parser.getQuery(pql);
    SuchThatClause suchThatClause = (*query.getSuchThatClauses())[0];
    std::vector<Argument> argList = suchThatClause.argList;

    CHECK(suchThatClause.relRef == RelRef::CALLS_T);

    Argument expectedFirstArgument = Argument();
    expectedFirstArgument.argumentValue = "p";
    expectedFirstArgument.argumentType = ArgumentType::SYNONYM;
    Argument expectedSecondArgument = Argument();
    expectedSecondArgument.argumentValue = "x";
    expectedSecondArgument.argumentType = ArgumentType::IDENT;

    CHECK(argList[0] == expectedFirstArgument);
    CHECK(argList[1] == expectedSecondArgument);
}

TEST_CASE ("PARSER - SUCH THAT CLAUSE CALLS* CHECK WITH ARGUMENTS: WILDCARD, SYNONYM") {
    QueryParser parser = QueryParser();

    std::string pql = "procedure p; \nSelect p such that Calls*(_, p)";
    Query query = parser.getQuery(pql);
    SuchThatClause suchThatClause = (*query.getSuchThatClauses())[0];
    std::vector<Argument> argList = suchThatClause.argList;

    CHECK(suchThatClause.relRef == RelRef::CALLS_T);

    Argument expectedFirstArgument = Argument();
    expectedFirstArgument.argumentValue = "_";
    expectedFirstArgument.argumentType = ArgumentType::UNDERSCORE;
    Argument expectedSecondArgument = Argument();
    expectedSecondArgument.argumentValue = "p";
    expectedSecondArgument.argumentType = ArgumentType::SYNONYM;

    CHECK(argList[0] == expectedFirstArgument);
    CHECK(argList[1] == expectedSecondArgument);
}

TEST_CASE ("PARSER - MULTIPLE SUCH THAT CLAUSES: CALLS* AND FOLLOWS") {
    QueryParser parser = QueryParser();

    std::string pql = "procedure p; \nSelect p such that Calls*(_, p) and Follows(2, 3)";
    Query query = parser.getQuery(pql);
    SuchThatClause suchThatClause = (*query.getSuchThatClauses())[0];
    std::vector<Argument> argList = suchThatClause.argList;

    CHECK(suchThatClause.relRef == RelRef::CALLS_T);

    Argument expectedFirstArgument = Argument();
    expectedFirstArgument.argumentValue = "_";
    expectedFirstArgument.argumentType = ArgumentType::UNDERSCORE;
    Argument expectedSecondArgument = Argument();
    expectedSecondArgument.argumentValue = "p";
    expectedSecondArgument.argumentType = ArgumentType::SYNONYM;

    CHECK(argList[0] == expectedFirstArgument);
    CHECK(argList[1] == expectedSecondArgument);

    // Check second such that clause
    suchThatClause = (*query.getSuchThatClauses())[1];
    argList = suchThatClause.argList;

    CHECK(suchThatClause.relRef == RelRef::FOLLOWS);

    expectedFirstArgument = Argument();
    expectedFirstArgument.argumentValue = "2";
    expectedFirstArgument.argumentType = ArgumentType::STMT_NO;
    expectedSecondArgument = Argument();
    expectedSecondArgument.argumentValue = "3";
    expectedSecondArgument.argumentType = ArgumentType::STMT_NO;

    CHECK(argList[0] == expectedFirstArgument);
    CHECK(argList[1] == expectedSecondArgument);
}

TEST_CASE ("PARSER - ASSIGN PATTERN CLAUSE CHECK WITH ARGUMENTS: IDENT, WILDCARD") {
    QueryParser parser = QueryParser();

    std::string pql = "variable v; assign a; stmt s; \nSelect v pattern a (\"x\", _)";
    Query query = parser.getQuery(pql);
    PatternClause patternClause = (*query.getPatternClauses())[0];
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

    CHECK(patternClause.synonymType == SynonymType::ASSIGN);
    CHECK(argList[0] == expectedFirstArgument);
    CHECK(argList[1] == expectedSecondArgument);
    CHECK(argList[2] == expectedThirdArgument);
}

TEST_CASE ("PARSER - ASSIGN PATTERN CLAUSE CHECK WITH ARGUMENTS: WILDCARD, WILDCARD") {
    QueryParser parser = QueryParser();

    std::string pql = "variable v; assign a; stmt s; \nSelect v pattern a (_, _)";
    Query query = parser.getQuery(pql);
    PatternClause patternClause = (*query.getPatternClauses())[0];
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

    CHECK(patternClause.synonymType == SynonymType::ASSIGN);
    CHECK(argList[0] == expectedFirstArgument);
    CHECK(argList[1] == expectedSecondArgument);
    CHECK(argList[2] == expectedThirdArgument);
}

TEST_CASE ("PARSER - ASSIGN PATTERN CLAUSE CHECK WITH ARGUMENTS: VARIABLE, WILDCARD") {
    QueryParser parser = QueryParser();

    std::string pql = "variable v; assign a; stmt s; \nSelect v pattern a (v, _)";
    Query query = parser.getQuery(pql);
    PatternClause patternClause = (*query.getPatternClauses())[0];
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

    CHECK(patternClause.synonymType == SynonymType::ASSIGN);
    CHECK(argList[0] == expectedFirstArgument);
    CHECK(argList[1] == expectedSecondArgument);
    CHECK(argList[2] == expectedThirdArgument);
}

TEST_CASE ("PARSER - ASSIGN PATTERN CLAUSE CHECK WITH ARGUMENTS: VARIABLE, IDENT") {
    QueryParser parser = QueryParser();

    std::string pql = "variable v; assign a; stmt s; \nSelect v pattern a (v, \"x\")";
    Query query = parser.getQuery(pql);
    PatternClause patternClause = (*query.getPatternClauses())[0];
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

    CHECK(patternClause.synonymType == SynonymType::ASSIGN);
    CHECK(argList[0] == expectedFirstArgument);
    CHECK(argList[1] == expectedSecondArgument);
    CHECK(argList[2] == expectedThirdArgument);
}

TEST_CASE ("PARSER - ASSIGN PATTERN CLAUSE CHECK WITH ARGUMENTS: VARIABLE, PARTIAL WILDCARD") {
    QueryParser parser = QueryParser();

    std::string pql = "variable v; assign a; stmt s; \nSelect v pattern a (v, _\"x\"_)";
    Query query = parser.getQuery(pql);
    PatternClause patternClause = (*query.getPatternClauses())[0];
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

    CHECK(patternClause.synonymType == SynonymType::ASSIGN);
    CHECK(argList[0] == expectedFirstArgument);
    CHECK(argList[1] == expectedSecondArgument);
    CHECK(argList[2] == expectedThirdArgument);
}

TEST_CASE ("PARSER - WHILE PATTERN CLAUSE CHECK WITH ARGUMENTS: IDENT, WILDCARD") {
    QueryParser parser = QueryParser();

    std::string pql = "while w; variable v; \nSelect v pattern w (\"x\", _)";
    Query query = parser.getQuery(pql);
    PatternClause patternClause = (*query.getPatternClauses())[0];
    std::vector<Argument> argList = patternClause.argList;

    Argument expectedFirstArgument = Argument();
    expectedFirstArgument.argumentValue = "w";
    expectedFirstArgument.argumentType = ArgumentType::SYNONYM;
    Argument expectedSecondArgument = Argument();
    expectedSecondArgument.argumentValue = "x";
    expectedSecondArgument.argumentType = ArgumentType::IDENT;
    Argument expectedThirdArgument = Argument();
    expectedThirdArgument.argumentValue = "_";
    expectedThirdArgument.argumentType = ArgumentType::UNDERSCORE;

    CHECK(patternClause.synonymType == SynonymType::WHILE);
    CHECK(argList[0] == expectedFirstArgument);
    CHECK(argList[1] == expectedSecondArgument);
    CHECK(argList[2] == expectedThirdArgument);
}

TEST_CASE ("PARSER - WHILE PATTERN CLAUSE CHECK WITH ARGUMENTS: WILDCARD, WILDCARD") {
    QueryParser parser = QueryParser();

    std::string pql = "while w; variable v; \nSelect v pattern w (_, _)";
    Query query = parser.getQuery(pql);
    PatternClause patternClause = (*query.getPatternClauses())[0];
    std::vector<Argument> argList = patternClause.argList;

    Argument expectedFirstArgument = Argument();
    expectedFirstArgument.argumentValue = "w";
    expectedFirstArgument.argumentType = ArgumentType::SYNONYM;
    Argument expectedSecondArgument = Argument();
    expectedSecondArgument.argumentValue = "_";
    expectedSecondArgument.argumentType = ArgumentType::UNDERSCORE;
    Argument expectedThirdArgument = Argument();
    expectedThirdArgument.argumentValue = "_";
    expectedThirdArgument.argumentType = ArgumentType::UNDERSCORE;

    CHECK(patternClause.synonymType == SynonymType::WHILE);
    CHECK(argList[0] == expectedFirstArgument);
    CHECK(argList[1] == expectedSecondArgument);
    CHECK(argList[2] == expectedThirdArgument);
}

TEST_CASE ("PARSER - WHILE PATTERN CLAUSE CHECK WITH ARGUMENTS: VARIABLE, WILDCARD") {
    QueryParser parser = QueryParser();

    std::string pql = "while w; variable v; \nSelect v pattern w (v, _)";
    Query query = parser.getQuery(pql);
    PatternClause patternClause = (*query.getPatternClauses())[0];
    std::vector<Argument> argList = patternClause.argList;

    Argument expectedFirstArgument = Argument();
    expectedFirstArgument.argumentValue = "w";
    expectedFirstArgument.argumentType = ArgumentType::SYNONYM;
    Argument expectedSecondArgument = Argument();
    expectedSecondArgument.argumentValue = "v";
    expectedSecondArgument.argumentType = ArgumentType::SYNONYM;
    Argument expectedThirdArgument = Argument();
    expectedThirdArgument.argumentValue = "_";
    expectedThirdArgument.argumentType = ArgumentType::UNDERSCORE;

    CHECK(patternClause.synonymType == SynonymType::WHILE);
    CHECK(argList[0] == expectedFirstArgument);
    CHECK(argList[1] == expectedSecondArgument);
    CHECK(argList[2] == expectedThirdArgument);
}

TEST_CASE ("PARSER - IF PATTERN CLAUSE CHECK WITH ARGUMENTS: IDENT, WILDCARD, WILDCARD") {
    QueryParser parser = QueryParser();

    std::string pql = "variable v; if ifs; \nSelect v pattern ifs (\"x\", _, _)";
    Query query = parser.getQuery(pql);
    PatternClause patternClause = (*query.getPatternClauses())[0];
    std::vector<Argument> argList = patternClause.argList;

    Argument expectedFirstArgument = Argument();
    expectedFirstArgument.argumentValue = "ifs";
    expectedFirstArgument.argumentType = ArgumentType::SYNONYM;
    Argument expectedSecondArgument = Argument();
    expectedSecondArgument.argumentValue = "x";
    expectedSecondArgument.argumentType = ArgumentType::IDENT;
    Argument expectedThirdArgument = Argument();
    expectedThirdArgument.argumentValue = "_";
    expectedThirdArgument.argumentType = ArgumentType::UNDERSCORE;

    CHECK(patternClause.synonymType == SynonymType::IF);
    CHECK(argList[0] == expectedFirstArgument);
    CHECK(argList[1] == expectedSecondArgument);
    CHECK(argList[2] == expectedThirdArgument);
}

TEST_CASE ("PARSER - IF PATTERN CLAUSE CHECK WITH ARGUMENTS: WILDCARD, WILDCARD") {
    QueryParser parser = QueryParser();

    std::string pql = "variable v;  if ifs; \nSelect v pattern ifs (_, _)";
    Query query = parser.getQuery(pql);
    PatternClause patternClause = (*query.getPatternClauses())[0];
    std::vector<Argument> argList = patternClause.argList;

    Argument expectedFirstArgument = Argument();
    expectedFirstArgument.argumentValue = "ifs";
    expectedFirstArgument.argumentType = ArgumentType::SYNONYM;
    Argument expectedSecondArgument = Argument();
    expectedSecondArgument.argumentValue = "_";
    expectedSecondArgument.argumentType = ArgumentType::UNDERSCORE;
    Argument expectedThirdArgument = Argument();
    expectedThirdArgument.argumentValue = "_";
    expectedThirdArgument.argumentType = ArgumentType::UNDERSCORE;

    CHECK(patternClause.synonymType == SynonymType::IF);
    CHECK(argList[0] == expectedFirstArgument);
    CHECK(argList[1] == expectedSecondArgument);
    CHECK(argList[2] == expectedThirdArgument);
}

TEST_CASE ("PARSER - IF PATTERN CLAUSE CHECK WITH ARGUMENTS: VARIABLE, WILDCARD") {
    QueryParser parser = QueryParser();

    std::string pql = "variable v;  if ifs; \nSelect v pattern ifs (v, _)";
    Query query = parser.getQuery(pql);
    PatternClause patternClause = (*query.getPatternClauses())[0];
    std::vector<Argument> argList = patternClause.argList;

    Argument expectedFirstArgument = Argument();
    expectedFirstArgument.argumentValue = "ifs";
    expectedFirstArgument.argumentType = ArgumentType::SYNONYM;
    Argument expectedSecondArgument = Argument();
    expectedSecondArgument.argumentValue = "v";
    expectedSecondArgument.argumentType = ArgumentType::SYNONYM;
    Argument expectedThirdArgument = Argument();
    expectedThirdArgument.argumentValue = "_";
    expectedThirdArgument.argumentType = ArgumentType::UNDERSCORE;

    CHECK(patternClause.synonymType == SynonymType::IF);
    CHECK(argList[0] == expectedFirstArgument);
    CHECK(argList[1] == expectedSecondArgument);
    CHECK(argList[2] == expectedThirdArgument);
}

TEST_CASE ("PARSER - WITH CLAUSES") {
    QueryParser parser = QueryParser();

    std::string pql = "constant c; procedure p; stmt s; variable v; \nSelect s with s.stmt#=5 and c.value = v.varName with p.procName = \"x\"";
    Query query = parser.getQuery(pql);
    WithClause withClause = (*query.getWithClauses())[0];
    std::vector<Argument> argList = withClause.argList;

    // First with clause
    Argument expectedFirstArgument = Argument();
    expectedFirstArgument.argumentValue = std::pair<std::string, AttrName>("s", AttrName::STMT_NO);
    expectedFirstArgument.argumentType = ArgumentType::ATTR_REF;
    Argument expectedSecondArgument = Argument();
    expectedSecondArgument.argumentValue = "5";
    expectedSecondArgument.argumentType = ArgumentType::STMT_NO;

    CHECK(argList[0] == expectedFirstArgument);
    CHECK(argList[1] == expectedSecondArgument);

    // Second with clause
    argList = (*query.getWithClauses())[1].argList;
    expectedFirstArgument = Argument();
    expectedFirstArgument.argumentValue = std::pair<std::string, AttrName>("c", AttrName::VALUE);
    expectedFirstArgument.argumentType = ArgumentType::ATTR_REF;
    expectedSecondArgument = Argument();
    expectedSecondArgument.argumentValue = std::pair<std::string, AttrName>("v", AttrName::VAR_NAME);
    expectedSecondArgument.argumentType = ArgumentType::ATTR_REF;

    CHECK(argList[0] == expectedFirstArgument);
    CHECK(argList[1] == expectedSecondArgument);

    // Third with clause
    argList = (*query.getWithClauses())[2].argList;
    expectedFirstArgument = Argument();
    expectedFirstArgument.argumentValue = std::pair<std::string, AttrName>("p", AttrName::PROC_NAME);
    expectedFirstArgument.argumentType = ArgumentType::ATTR_REF;
    expectedSecondArgument = Argument();
    expectedSecondArgument.argumentValue = "x";
    expectedSecondArgument.argumentType = ArgumentType::IDENT;

    CHECK(argList[0] == expectedFirstArgument);
    CHECK(argList[1] == expectedSecondArgument);
}

TEST_CASE ("PARSER - MULTICLAUSE CHECK") {
    QueryParser parser = QueryParser();

    std::string pql = "stmt s; assign a; constant c; variable v; \nSelect s such that Parent*(s,3) pattern a (_, _) with c.value=v.varName";
    Query query = parser.getQuery(pql);
    SuchThatClause suchThatClause = (*query.getSuchThatClauses())[0];
    std::vector<Argument> argList = suchThatClause.argList;

    PatternClause patternClause = (*query.getPatternClauses())[0];
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

    argList = (*query.getWithClauses())[0].argList;
    expectedFirstArgument = Argument();
    expectedFirstArgument.argumentValue = std::pair<std::string, AttrName>("c", AttrName::VALUE);
    expectedFirstArgument.argumentType = ArgumentType::ATTR_REF;
    expectedSecondArgument = Argument();
    expectedSecondArgument.argumentValue = std::pair<std::string, AttrName>("v", AttrName::VAR_NAME);
    expectedSecondArgument.argumentType = ArgumentType::ATTR_REF;

    CHECK(argList[0] == expectedFirstArgument);
    CHECK(argList[1] == expectedSecondArgument);
}

TEST_CASE ("PARSER - INCORRECT CHECK") {
    QueryParser parser = QueryParser();

    std::string pql = "constant c; Select c with c.value = 0such that Follows(_, _)and Parent*(_,_)";
    Query query = parser.getQuery(pql);

}


