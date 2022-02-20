#include "catch.hpp"
#include "QP_Parser/QueryParser.h"
#include "QP_Parser/Tokenizer.h"
#include "pql/query_obj/Query.h"

#include <string>

using namespace qp;

TEST_CASE ("PARSER - DECLARATIONS CHECK") {
    QueryParser parser = QueryParser();

    // variable design entity
    string pql = "variable v; \nSelect v";
    Query query = parser.getQuery(pql);

    CHECK(query.getSelectedSynonym() == "v");
    CHECK(query.findEntityType("v") == DesignEntity::VARIABLE);

    // constant design entity
    pql = "constant c; \nSelect c";
    query = parser.getQuery(pql);

    CHECK(query.getSelectedSynonym() == "c");
    CHECK(query.findEntityType("c") == DesignEntity::CONSTANT);

    // procedure design entity
    pql = "procedure p; \nSelect p";
    query = parser.getQuery(pql);

    CHECK(query.getSelectedSynonym() == "p");
    CHECK(query.findEntityType("p") == DesignEntity::PROCEDURE);

    // stmt design entity
    pql = "stmt s; \nSelect s";
    query = parser.getQuery(pql);

    CHECK(query.getSelectedSynonym() == "s");
    CHECK(query.findEntityType("s") == DesignEntity::STMT);

    // read design entity
    pql = "read r; \nSelect r";
    query = parser.getQuery(pql);

    CHECK(query.getSelectedSynonym() == "r");
    CHECK(query.findEntityType("r") == DesignEntity::READ);

    // print design entity
    pql = "print pn; \nSelect pn";
    query = parser.getQuery(pql);

    CHECK(query.getSelectedSynonym() == "pn");
    CHECK(query.findEntityType("pn") == DesignEntity::PRINT);

    // assign design entity
    pql = "assign a; \nSelect a";
    query = parser.getQuery(pql);

    CHECK(query.getSelectedSynonym() == "a");
    CHECK(query.findEntityType("a") == DesignEntity::ASSIGN);

    // call design entity
    pql = "call c; \nSelect c";
    query = parser.getQuery(pql);

    CHECK(query.getSelectedSynonym() == "c");
    CHECK(query.findEntityType("c") == DesignEntity::CALL);

    // while design entity
    pql = "while w; \nSelect w";
    query = parser.getQuery(pql);

    CHECK(query.getSelectedSynonym() == "w");
    CHECK(query.findEntityType("w") == DesignEntity::WHILE);

    // if design entity
    pql = "if ifs; \nSelect ifs";
    query = parser.getQuery(pql);

    CHECK(query.getSelectedSynonym() == "ifs");
    CHECK(query.findEntityType("ifs") == DesignEntity::IF);

    // multiple declarations
    pql = "if ifs; assign a; \nSelect ifs";
    query = parser.getQuery(pql);

    CHECK(query.getSelectedSynonym() == "ifs");
    CHECK(query.findEntityType("ifs") == DesignEntity::IF);
    CHECK(query.findEntityType("a") == DesignEntity::ASSIGN);

    // multiple declarations under same design entity
    pql = "assign a1, a2; \nSelect a1";
    query = parser.getQuery(pql);

    CHECK(query.getSelectedSynonym() == "a1");
    CHECK(query.findEntityType("a1") == DesignEntity::ASSIGN);
    CHECK(query.findEntityType("a2") == DesignEntity::ASSIGN);
}

TEST_CASE ("PARSER - SYNONYM CHECK") {
    QueryParser parser = QueryParser();

    // synonym named Select
    string pql = "variable Select; \nSelect Select";
    Query query = parser.getQuery(pql);

    CHECK(query.getSelectedSynonym() == "Select");

    // synonym named pattern
    pql = "variable pattern; \nSelect pattern";
    query = parser.getQuery(pql);

    CHECK(query.getSelectedSynonym() == "pattern");

    // synonym named pattern with pattern clause
    pql = "assign pattern; \nSelect pattern pattern pattern(_, _)";
    query = parser.getQuery(pql);

    CHECK(query.getSelectedSynonym() == "pattern");
}

TEST_CASE ("PARSER - SUCH THAT CLAUSE FOLLOWS CHECK WITH ARGUMENTS: SYNONYM, WILDCARD") {
        QueryParser parser = QueryParser();

        std::string pql = "stmt s; \nSelect s such that Follows(s,_)";
        Query query = parser.getQuery(pql);
        SuchThatClause suchThatClause = query.getSuchThatClauses()[0];
        std::vector<Argument> argList = suchThatClause.argList;

        CHECK(suchThatClause.relRef == RelRef::FOLLOWS);
        CHECK(argList[0].argumentType == ArgumentType::SYNONYM);
        CHECK(argList[0].argumentValue == "s");

        CHECK(argList[1].argumentType == ArgumentType::UNDERSCORE);
        CHECK(argList[1].argumentValue == "_");
}

TEST_CASE ("PARSER - SUCH THAT CLAUSE FOLLOWS CHECK WITH ARGUMENTS: SYNONYM, INTEGER") {
    QueryParser parser = QueryParser();

    std::string pql = "stmt s; \nSelect s such that Follows(s,3)";
    Query query = parser.getQuery(pql);
    SuchThatClause suchThatClause = query.getSuchThatClauses()[0];
    std::vector<Argument> argList = suchThatClause.argList;

    CHECK(suchThatClause.relRef == RelRef::FOLLOWS);
    CHECK(argList[0].argumentType == ArgumentType::SYNONYM);
    CHECK(argList[0].argumentValue == "s");

    CHECK(argList[1].argumentType == ArgumentType::STMT_NO);
    CHECK(argList[1].argumentValue == "3");
}

TEST_CASE ("PARSER - SUCH THAT CLAUSE FOLLOWS CHECK WITH ARGUMENTS: SYNONYM, SYNONYM") {
    QueryParser parser = QueryParser();

    std::string pql = "stmt s1, s2; \nSelect s1 such that Follows(s1, s2)";
    Query query = parser.getQuery(pql);
    SuchThatClause suchThatClause = query.getSuchThatClauses()[0];
    std::vector<Argument> argList = suchThatClause.argList;

    CHECK(suchThatClause.relRef == RelRef::FOLLOWS);
    CHECK(argList[0].argumentType == ArgumentType::SYNONYM);
    CHECK(argList[0].argumentValue == "s1");

    CHECK(argList[1].argumentType == ArgumentType::SYNONYM);
    CHECK(argList[1].argumentValue == "s2");
}

TEST_CASE ("PARSER - SUCH THAT CLAUSE FOLLOWS CHECK WITH ARGUMENTS: INTEGER, SYNONYM") {
    QueryParser parser = QueryParser();

    std::string pql = "stmt s1, s2; \nSelect s1 such that Follows(3, s2)";
    Query query = parser.getQuery(pql);
    SuchThatClause suchThatClause = query.getSuchThatClauses()[0];
    std::vector<Argument> argList = suchThatClause.argList;

    CHECK(suchThatClause.relRef == RelRef::FOLLOWS);
    CHECK(argList[0].argumentType == ArgumentType::STMT_NO);
    CHECK(argList[0].argumentValue == "3");

    CHECK(argList[1].argumentType == ArgumentType::SYNONYM);
    CHECK(argList[1].argumentValue == "s2");
}

TEST_CASE ("PARSER - SUCH THAT CLAUSE FOLLOWS CHECK WITH ARGUMENTS: WILDCARD, SYNONYM") {
    QueryParser parser = QueryParser();

    std::string pql = "stmt s1, s2; \nSelect s1 such that Follows(_, s2)";
    Query query = parser.getQuery(pql);
    SuchThatClause suchThatClause = query.getSuchThatClauses()[0];
    std::vector<Argument> argList = suchThatClause.argList;

    CHECK(suchThatClause.relRef == RelRef::FOLLOWS);
    CHECK(argList[0].argumentType == ArgumentType::UNDERSCORE);
    CHECK(argList[0].argumentValue == "_");

    CHECK(argList[1].argumentType == ArgumentType::SYNONYM);
    CHECK(argList[1].argumentValue == "s2");
}

TEST_CASE ("PARSER - SUCH THAT CLAUSE FOLLOWS* CHECK WITH ARGUMENTS: SYNONYM, WILDCARD") {
    QueryParser parser = QueryParser();

    std::string pql = "stmt s; \nSelect s such that Follows*(s,_)";
    Query query = parser.getQuery(pql);
    SuchThatClause suchThatClause = query.getSuchThatClauses()[0];
    std::vector<Argument> argList = suchThatClause.argList;

    CHECK(suchThatClause.relRef == RelRef::FOLLOWS_T);
    CHECK(argList[0].argumentType == ArgumentType::SYNONYM);
    CHECK(argList[0].argumentValue == "s");

    CHECK(argList[1].argumentType == ArgumentType::UNDERSCORE);
    CHECK(argList[1].argumentValue == "_");
}

TEST_CASE ("PARSER - SUCH THAT CLAUSE FOLLOWS* CHECK WITH ARGUMENTS: SYNONYM, INTEGER") {
    QueryParser parser = QueryParser();

    std::string pql = "stmt s; \nSelect s such that Follows*(s,3)";
    Query query = parser.getQuery(pql);
    SuchThatClause suchThatClause = query.getSuchThatClauses()[0];
    std::vector<Argument> argList = suchThatClause.argList;

    CHECK(suchThatClause.relRef == RelRef::FOLLOWS_T);
    CHECK(argList[0].argumentType == ArgumentType::SYNONYM);
    CHECK(argList[0].argumentValue == "s");

    CHECK(argList[1].argumentType == ArgumentType::STMT_NO);
    CHECK(argList[1].argumentValue == "3");
}

TEST_CASE ("PARSER - SUCH THAT CLAUSE FOLLOWS* CHECK WITH ARGUMENTS: SYNONYM, SYNONYM") {
    QueryParser parser = QueryParser();

    std::string pql = "stmt s1, s2; \nSelect s1 such that Follows*(s1, s2)";
    Query query = parser.getQuery(pql);
    SuchThatClause suchThatClause = query.getSuchThatClauses()[0];
    std::vector<Argument> argList = suchThatClause.argList;

    CHECK(suchThatClause.relRef == RelRef::FOLLOWS_T);
    CHECK(argList[0].argumentType == ArgumentType::SYNONYM);
    CHECK(argList[0].argumentValue == "s1");

    CHECK(argList[1].argumentType == ArgumentType::SYNONYM);
    CHECK(argList[1].argumentValue == "s2");
}

TEST_CASE ("PARSER - SUCH THAT CLAUSE FOLLOWS* CHECK WITH ARGUMENTS: INTEGER, SYNONYM") {
    QueryParser parser = QueryParser();

    std::string pql = "stmt s1, s2; \nSelect s1 such that Follows*(3, s2)";
    Query query = parser.getQuery(pql);
    SuchThatClause suchThatClause = query.getSuchThatClauses()[0];
    std::vector<Argument> argList = suchThatClause.argList;

    CHECK(suchThatClause.relRef == RelRef::FOLLOWS_T);
    CHECK(argList[0].argumentType == ArgumentType::STMT_NO);
    CHECK(argList[0].argumentValue == "3");

    CHECK(argList[1].argumentType == ArgumentType::SYNONYM);
    CHECK(argList[1].argumentValue == "s2");
}

TEST_CASE ("PARSER - SUCH THAT CLAUSE FOLLOWS* CHECK WITH ARGUMENTS: WILDCARD, SYNONYM") {
    QueryParser parser = QueryParser();

    std::string pql = "stmt s1, s2; \nSelect s1 such that Follows*(_, s2)";
    Query query = parser.getQuery(pql);
    SuchThatClause suchThatClause = query.getSuchThatClauses()[0];
    std::vector<Argument> argList = suchThatClause.argList;

    CHECK(suchThatClause.relRef == RelRef::FOLLOWS_T);
    CHECK(argList[0].argumentType == ArgumentType::UNDERSCORE);
    CHECK(argList[0].argumentValue == "_");

    CHECK(argList[1].argumentType == ArgumentType::SYNONYM);
    CHECK(argList[1].argumentValue == "s2");
}

TEST_CASE ("PARSER - SUCH THAT CLAUSE PARENT CHECK WITH ARGUMENTS: SYNONYM, WILDCARD") {
    QueryParser parser = QueryParser();

    std::string pql = "stmt s; \nSelect s such that Parent(s,_)";
    Query query = parser.getQuery(pql);
    SuchThatClause suchThatClause = query.getSuchThatClauses()[0];
    std::vector<Argument> argList = suchThatClause.argList;

    CHECK(suchThatClause.relRef == RelRef::PARENT);
    CHECK(argList[0].argumentType == ArgumentType::SYNONYM);
    CHECK(argList[0].argumentValue == "s");

    CHECK(argList[1].argumentType == ArgumentType::UNDERSCORE);
    CHECK(argList[1].argumentValue == "_");
}

TEST_CASE ("PARSER - SUCH THAT CLAUSE PARENT CHECK WITH ARGUMENTS: SYNONYM, INTEGER") {
    QueryParser parser = QueryParser();

    std::string pql = "stmt s; \nSelect s such that Parent(s,3)";
    Query query = parser.getQuery(pql);
    SuchThatClause suchThatClause = query.getSuchThatClauses()[0];
    std::vector<Argument> argList = suchThatClause.argList;

    CHECK(suchThatClause.relRef == RelRef::PARENT);
    CHECK(argList[0].argumentType == ArgumentType::SYNONYM);
    CHECK(argList[0].argumentValue == "s");

    CHECK(argList[1].argumentType == ArgumentType::STMT_NO);
    CHECK(argList[1].argumentValue == "3");
}

TEST_CASE ("PARSER - SUCH THAT CLAUSE PARENT CHECK WITH ARGUMENTS: SYNONYM, SYNONYM") {
    QueryParser parser = QueryParser();

    std::string pql = "stmt s1, s2; \nSelect s1 such that Parent(s1, s2)";
    Query query = parser.getQuery(pql);
    SuchThatClause suchThatClause = query.getSuchThatClauses()[0];
    std::vector<Argument> argList = suchThatClause.argList;

    CHECK(suchThatClause.relRef == RelRef::PARENT);
    CHECK(argList[0].argumentType == ArgumentType::SYNONYM);
    CHECK(argList[0].argumentValue == "s1");

    CHECK(argList[1].argumentType == ArgumentType::SYNONYM);
    CHECK(argList[1].argumentValue == "s2");
}

TEST_CASE ("PARSER - SUCH THAT CLAUSE PARENT CHECK WITH ARGUMENTS: INTEGER, SYNONYM") {
    QueryParser parser = QueryParser();

    std::string pql = "stmt s1, s2; \nSelect s1 such that Parent(3, s2)";
    Query query = parser.getQuery(pql);
    SuchThatClause suchThatClause = query.getSuchThatClauses()[0];
    std::vector<Argument> argList = suchThatClause.argList;

    CHECK(suchThatClause.relRef == RelRef::PARENT);
    CHECK(argList[0].argumentType == ArgumentType::STMT_NO);
    CHECK(argList[0].argumentValue == "3");

    CHECK(argList[1].argumentType == ArgumentType::SYNONYM);
    CHECK(argList[1].argumentValue == "s2");
}

TEST_CASE ("PARSER - SUCH THAT CLAUSE PARENT CHECK WITH ARGUMENTS: WILDCARD, SYNONYM") {
    QueryParser parser = QueryParser();

    std::string pql = "stmt s1, s2; \nSelect s1 such that Parent(_, s2)";
    Query query = parser.getQuery(pql);
    SuchThatClause suchThatClause = query.getSuchThatClauses()[0];
    std::vector<Argument> argList = suchThatClause.argList;

    CHECK(suchThatClause.relRef == RelRef::PARENT);
    CHECK(argList[0].argumentType == ArgumentType::UNDERSCORE);
    CHECK(argList[0].argumentValue == "_");

    CHECK(argList[1].argumentType == ArgumentType::SYNONYM);
    CHECK(argList[1].argumentValue == "s2");
}

TEST_CASE ("PARSER - SUCH THAT CLAUSE PARENT* CHECK WITH ARGUMENTS: SYNONYM, WILDCARD") {
    QueryParser parser = QueryParser();

    std::string pql = "stmt s; \nSelect s such that Parent*(s,_)";
    Query query = parser.getQuery(pql);
    SuchThatClause suchThatClause = query.getSuchThatClauses()[0];
    std::vector<Argument> argList = suchThatClause.argList;

    CHECK(suchThatClause.relRef == RelRef::PARENT_T);
    CHECK(argList[0].argumentType == ArgumentType::SYNONYM);
    CHECK(argList[0].argumentValue == "s");

    CHECK(argList[1].argumentType == ArgumentType::UNDERSCORE);
    CHECK(argList[1].argumentValue == "_");
}

TEST_CASE ("PARSER - SUCH THAT CLAUSE PARENT* CHECK WITH ARGUMENTS: SYNONYM, INTEGER") {
    QueryParser parser = QueryParser();

    std::string pql = "stmt s; \nSelect s such that Parent*(s,3)";
    Query query = parser.getQuery(pql);
    SuchThatClause suchThatClause = query.getSuchThatClauses()[0];
    std::vector<Argument> argList = suchThatClause.argList;

    CHECK(suchThatClause.relRef == RelRef::PARENT_T);
    CHECK(argList[0].argumentType == ArgumentType::SYNONYM);
    CHECK(argList[0].argumentValue == "s");

    CHECK(argList[1].argumentType == ArgumentType::STMT_NO);
    CHECK(argList[1].argumentValue == "3");
}

TEST_CASE ("PARSER - SUCH THAT CLAUSE PARENT* CHECK WITH ARGUMENTS: SYNONYM, SYNONYM") {
    QueryParser parser = QueryParser();

    std::string pql = "stmt s1, s2; \nSelect s1 such that Parent*(s1, s2)";
    Query query = parser.getQuery(pql);
    SuchThatClause suchThatClause = query.getSuchThatClauses()[0];
    std::vector<Argument> argList = suchThatClause.argList;

    CHECK(suchThatClause.relRef == RelRef::PARENT_T);
    CHECK(argList[0].argumentType == ArgumentType::SYNONYM);
    CHECK(argList[0].argumentValue == "s1");

    CHECK(argList[1].argumentType == ArgumentType::SYNONYM);
    CHECK(argList[1].argumentValue == "s2");
}

TEST_CASE ("PARSER - SUCH THAT CLAUSE PARENT* CHECK WITH ARGUMENTS: INTEGER, SYNONYM") {
    QueryParser parser = QueryParser();

    std::string pql = "stmt s1, s2; \nSelect s1 such that Parent*(3, s2)";
    Query query = parser.getQuery(pql);
    SuchThatClause suchThatClause = query.getSuchThatClauses()[0];
    std::vector<Argument> argList = suchThatClause.argList;

    CHECK(suchThatClause.relRef == RelRef::PARENT_T);
    CHECK(argList[0].argumentType == ArgumentType::STMT_NO);
    CHECK(argList[0].argumentValue == "3");

    CHECK(argList[1].argumentType == ArgumentType::SYNONYM);
    CHECK(argList[1].argumentValue == "s2");
}

TEST_CASE ("PARSER - SUCH THAT CLAUSE PARENT* CHECK WITH ARGUMENTS: WILDCARD, SYNONYM") {
    QueryParser parser = QueryParser();

    std::string pql = "stmt s1, s2; \nSelect s1 such that Parent*(_, s2)";
    Query query = parser.getQuery(pql);
    SuchThatClause suchThatClause = query.getSuchThatClauses()[0];
    std::vector<Argument> argList = suchThatClause.argList;

    CHECK(suchThatClause.relRef == RelRef::PARENT_T);
    CHECK(argList[0].argumentType == ArgumentType::UNDERSCORE);
    CHECK(argList[0].argumentValue == "_");

    CHECK(argList[1].argumentType == ArgumentType::SYNONYM);
    CHECK(argList[1].argumentValue == "s2");
}

TEST_CASE ("PARSER - SUCH THAT CLAUSE USES CHECK WITH ARGUMENTS: IDENT, WILDCARD") {
    QueryParser parser = QueryParser();

    std::string pql = "variable v; assign a; \nSelect v such that Uses(\"x\", _)";
    Query query = parser.getQuery(pql);
    SuchThatClause suchThatClause = query.getSuchThatClauses()[0];
    std::vector<Argument> argList = suchThatClause.argList;

    CHECK(suchThatClause.relRef == RelRef::USES_P);
    CHECK(argList[0].argumentType == ArgumentType::IDENT);
    CHECK(argList[0].argumentValue == "x");

    CHECK(argList[1].argumentType == ArgumentType::UNDERSCORE);
    CHECK(argList[1].argumentValue == "_");
}

TEST_CASE ("PARSER - SUCH THAT CLAUSE USES CHECK WITH ARGUMENTS: STMT SYNONYM, WILDCARD") {
    QueryParser parser = QueryParser();

    std::string pql = "variable v; assign a; stmt s; \nSelect v such that Uses(a, _)";
    Query query = parser.getQuery(pql);
    SuchThatClause suchThatClause = query.getSuchThatClauses()[0];
    std::vector<Argument> argList = suchThatClause.argList;

    CHECK(suchThatClause.relRef == RelRef::USES_S);
    CHECK(argList[0].argumentType == ArgumentType::SYNONYM);
    CHECK(argList[0].argumentValue == "a");

    CHECK(argList[1].argumentType == ArgumentType::UNDERSCORE);
    CHECK(argList[1].argumentValue == "_");
}

TEST_CASE ("PARSER - SUCH THAT CLAUSE USES CHECK WITH ARGUMENTS: STMT SYNONYM - PRINT, WILDCARD") {
    QueryParser parser = QueryParser();

    std::string pql = "variable v; assign a; stmt s; print pn; \nSelect v such that Uses(pn, _)";
    Query query = parser.getQuery(pql);
    SuchThatClause suchThatClause = query.getSuchThatClauses()[0];
    std::vector<Argument> argList = suchThatClause.argList;

    CHECK(suchThatClause.relRef == RelRef::USES_S);
    CHECK(argList[0].argumentType == ArgumentType::SYNONYM);
    CHECK(argList[0].argumentValue == "pn");

    CHECK(argList[1].argumentType == ArgumentType::UNDERSCORE);
    CHECK(argList[1].argumentValue == "_");
}

TEST_CASE ("PARSER - SUCH THAT CLAUSE USES CHECK WITH ARGUMENTS: STMT SYNONYM - IF, WILDCARD") {
    QueryParser parser = QueryParser();

    std::string pql = "variable v; assign a; stmt s; print pn; if ifs; \nSelect v such that Uses(ifs, _)";
    Query query = parser.getQuery(pql);
    SuchThatClause suchThatClause = query.getSuchThatClauses()[0];
    std::vector<Argument> argList = suchThatClause.argList;

    CHECK(suchThatClause.relRef == RelRef::USES_S);
    CHECK(argList[0].argumentType == ArgumentType::SYNONYM);
    CHECK(argList[0].argumentValue == "ifs");

    CHECK(argList[1].argumentType == ArgumentType::UNDERSCORE);
    CHECK(argList[1].argumentValue == "_");
}

TEST_CASE ("PARSER - SUCH THAT CLAUSE USES CHECK WITH ARGUMENTS: STMT SYNONYM - WHILE, WILDCARD") {
    QueryParser parser = QueryParser();

    std::string pql = "variable v; assign a; stmt s; print pn; if ifs; while w; \nSelect v such that Uses(w, _)";
    Query query = parser.getQuery(pql);
    SuchThatClause suchThatClause = query.getSuchThatClauses()[0];
    std::vector<Argument> argList = suchThatClause.argList;

    CHECK(suchThatClause.relRef == RelRef::USES_S);
    CHECK(argList[0].argumentType == ArgumentType::SYNONYM);
    CHECK(argList[0].argumentValue == "w");

    CHECK(argList[1].argumentType == ArgumentType::UNDERSCORE);
    CHECK(argList[1].argumentValue == "_");
}

TEST_CASE ("PARSER - SUCH THAT CLAUSE USES CHECK WITH ARGUMENTS: STMT SYNONYM - CALL, WILDCARD") {
    QueryParser parser = QueryParser();

    std::string pql = "variable v; call c; stmt s; print pn; if ifs; while w; \nSelect v such that Uses(c, _)";
    Query query = parser.getQuery(pql);
    SuchThatClause suchThatClause = query.getSuchThatClauses()[0];
    std::vector<Argument> argList = suchThatClause.argList;

    CHECK(suchThatClause.relRef == RelRef::USES_S);
    CHECK(argList[0].argumentType == ArgumentType::SYNONYM);
    CHECK(argList[0].argumentValue == "c");

    CHECK(argList[1].argumentType == ArgumentType::UNDERSCORE);
    CHECK(argList[1].argumentValue == "_");
}

TEST_CASE ("PARSER - SUCH THAT CLAUSE USES CHECK WITH ARGUMENTS: STMT SYNONYM, SYNONYM") {
    QueryParser parser = QueryParser();

    std::string pql = "variable v; assign a; stmt s; \nSelect v such that Uses(a, v)";
    Query query = parser.getQuery(pql);
    SuchThatClause suchThatClause = query.getSuchThatClauses()[0];
    std::vector<Argument> argList = suchThatClause.argList;

    CHECK(suchThatClause.relRef == RelRef::USES_S);
    CHECK(argList[0].argumentType == ArgumentType::SYNONYM);
    CHECK(argList[0].argumentValue == "a");

    CHECK(argList[1].argumentType == ArgumentType::SYNONYM);
    CHECK(argList[1].argumentValue == "v");
}

TEST_CASE ("PARSER - SUCH THAT CLAUSE USES CHECK WITH ARGUMENTS: STMT SYNONYM, IDENT") {
    QueryParser parser = QueryParser();

    std::string pql = "variable v; assign a; stmt s; \nSelect v such that Uses(a, \"x\")";
    Query query = parser.getQuery(pql);
    SuchThatClause suchThatClause = query.getSuchThatClauses()[0];
    std::vector<Argument> argList = suchThatClause.argList;

    CHECK(suchThatClause.relRef == RelRef::USES_S);
    CHECK(argList[0].argumentType == ArgumentType::SYNONYM);
    CHECK(argList[0].argumentValue == "a");

    CHECK(argList[1].argumentType == ArgumentType::IDENT);
    CHECK(argList[1].argumentValue == "x");
}

TEST_CASE ("PARSER - SUCH THAT CLAUSE MODIFIES CHECK WITH ARGUMENTS: IDENT, WILDCARD") {
    QueryParser parser = QueryParser();

    std::string pql = "variable v; assign a; \nSelect v such that Modifies(\"x\", _)";
    Query query = parser.getQuery(pql);
    SuchThatClause suchThatClause = query.getSuchThatClauses()[0];
    std::vector<Argument> argList = suchThatClause.argList;

    CHECK(suchThatClause.relRef == RelRef::MODIFIES_P);
    CHECK(argList[0].argumentType == ArgumentType::IDENT);
    CHECK(argList[0].argumentValue == "x");

    CHECK(argList[1].argumentType == ArgumentType::UNDERSCORE);
    CHECK(argList[1].argumentValue == "_");
}

TEST_CASE ("PARSER - SUCH THAT CLAUSE MODIFIES CHECK WITH ARGUMENTS: STMT SYNONYM, WILDCARD") {
    QueryParser parser = QueryParser();

    std::string pql = "variable v; assign a; stmt s; \nSelect v such that Modifies(a, _)";
    Query query = parser.getQuery(pql);
    SuchThatClause suchThatClause = query.getSuchThatClauses()[0];
    std::vector<Argument> argList = suchThatClause.argList;

    CHECK(suchThatClause.relRef == RelRef::MODIFIES_S);
    CHECK(argList[0].argumentType == ArgumentType::SYNONYM);
    CHECK(argList[0].argumentValue == "a");

    CHECK(argList[1].argumentType == ArgumentType::UNDERSCORE);
    CHECK(argList[1].argumentValue == "_");
}

TEST_CASE ("PARSER - SUCH THAT CLAUSE MODIFIES CHECK WITH ARGUMENTS: STMT SYNONYM - READ, WILDCARD") {
    QueryParser parser = QueryParser();

    std::string pql = "variable v; assign a; stmt s; read r; \nSelect v such that Modifies(r, _)";
    Query query = parser.getQuery(pql);
    SuchThatClause suchThatClause = query.getSuchThatClauses()[0];
    std::vector<Argument> argList = suchThatClause.argList;

    CHECK(suchThatClause.relRef == RelRef::MODIFIES_S);
    CHECK(argList[0].argumentType == ArgumentType::SYNONYM);
    CHECK(argList[0].argumentValue == "r");

    CHECK(argList[1].argumentType == ArgumentType::UNDERSCORE);
    CHECK(argList[1].argumentValue == "_");
}

TEST_CASE ("PARSER - SUCH THAT CLAUSE MODIFIES CHECK WITH ARGUMENTS: STMT SYNONYM - IF, WILDCARD") {
    QueryParser parser = QueryParser();

    std::string pql = "variable v; assign a; stmt s; print pn; if ifs; \nSelect v such that Modifies(ifs, _)";
    Query query = parser.getQuery(pql);
    SuchThatClause suchThatClause = query.getSuchThatClauses()[0];
    std::vector<Argument> argList = suchThatClause.argList;

    CHECK(suchThatClause.relRef == RelRef::MODIFIES_S);
    CHECK(argList[0].argumentType == ArgumentType::SYNONYM);
    CHECK(argList[0].argumentValue == "ifs");

    CHECK(argList[1].argumentType == ArgumentType::UNDERSCORE);
    CHECK(argList[1].argumentValue == "_");
}

TEST_CASE ("PARSER - SUCH THAT CLAUSE MODIFIES CHECK WITH ARGUMENTS: STMT SYNONYM - WHILE, WILDCARD") {
    QueryParser parser = QueryParser();

    std::string pql = "variable v; assign a; stmt s; print pn; if ifs; while w; \nSelect v such that Modifies(w, _)";
    Query query = parser.getQuery(pql);
    SuchThatClause suchThatClause = query.getSuchThatClauses()[0];
    std::vector<Argument> argList = suchThatClause.argList;

    CHECK(suchThatClause.relRef == RelRef::MODIFIES_S);
    CHECK(argList[0].argumentType == ArgumentType::SYNONYM);
    CHECK(argList[0].argumentValue == "w");

    CHECK(argList[1].argumentType == ArgumentType::UNDERSCORE);
    CHECK(argList[1].argumentValue == "_");
}

TEST_CASE ("PARSER - SUCH THAT CLAUSE MODIFIES CHECK WITH ARGUMENTS: STMT SYNONYM - CALL, WILDCARD") {
    QueryParser parser = QueryParser();

    std::string pql = "variable v; call c; stmt s; print pn; if ifs; while w; \nSelect v such that Modifies(c, _)";
    Query query = parser.getQuery(pql);
    SuchThatClause suchThatClause = query.getSuchThatClauses()[0];
    std::vector<Argument> argList = suchThatClause.argList;

    CHECK(suchThatClause.relRef == RelRef::MODIFIES_S);
    CHECK(argList[0].argumentType == ArgumentType::SYNONYM);
    CHECK(argList[0].argumentValue == "c");

    CHECK(argList[1].argumentType == ArgumentType::UNDERSCORE);
    CHECK(argList[1].argumentValue == "_");
}

TEST_CASE ("PARSER - SUCH THAT CLAUSE MODIFIES CHECK WITH ARGUMENTS: STMT SYNONYM, SYNONYM") {
    QueryParser parser = QueryParser();

    std::string pql = "variable v; assign a; stmt s; \nSelect v such that Modifies(a, v)";
    Query query = parser.getQuery(pql);
    SuchThatClause suchThatClause = query.getSuchThatClauses()[0];
    std::vector<Argument> argList = suchThatClause.argList;

    CHECK(suchThatClause.relRef == RelRef::MODIFIES_S);
    CHECK(argList[0].argumentType == ArgumentType::SYNONYM);
    CHECK(argList[0].argumentValue == "a");

    CHECK(argList[1].argumentType == ArgumentType::SYNONYM);
    CHECK(argList[1].argumentValue == "v");
}

TEST_CASE ("PARSER - SUCH THAT CLAUSE MODIFIES CHECK WITH ARGUMENTS: STMT SYNONYM, IDENT") {
    QueryParser parser = QueryParser();

    std::string pql = "variable v; assign a; stmt s; \nSelect v such that Modifies(a, \"x\")";
    Query query = parser.getQuery(pql);
    SuchThatClause suchThatClause = query.getSuchThatClauses()[0];
    std::vector<Argument> argList = suchThatClause.argList;

    CHECK(suchThatClause.relRef == RelRef::MODIFIES_S);
    CHECK(argList[0].argumentType == ArgumentType::SYNONYM);
    CHECK(argList[0].argumentValue == "a");

    CHECK(argList[1].argumentType == ArgumentType::IDENT);
    CHECK(argList[1].argumentValue == "x");
}

TEST_CASE ("PARSER - PATTERN CLAUSE CHECK WITH ARGUMENTS: IDENT, WILDCARD") {
    QueryParser parser = QueryParser();

    std::string pql = "variable v; assign a; stmt s; \nSelect v pattern a (\"x\", _)";
    Query query = parser.getQuery(pql);
    PatternClause patternClause = query.getPatternClauses()[0];
    std::vector<Argument> argList = patternClause.argList;

    CHECK(argList[0].argumentType == ArgumentType::SYNONYM);
    CHECK(argList[0].argumentValue == "a");

    CHECK(argList[1].argumentType == ArgumentType::IDENT);
    CHECK(argList[1].argumentValue == "x");

    CHECK(argList[2].argumentType == ArgumentType::UNDERSCORE);
    CHECK(argList[2].argumentValue == "_");
}

TEST_CASE ("PARSER - PATTERN CLAUSE CHECK WITH ARGUMENTS: WILDCARD, WILDCARD") {
    QueryParser parser = QueryParser();

    std::string pql = "variable v; assign a; stmt s; \nSelect v pattern a (_, _)";
    Query query = parser.getQuery(pql);
    PatternClause patternClause = query.getPatternClauses()[0];
    std::vector<Argument> argList = patternClause.argList;

    CHECK(argList[0].argumentType == ArgumentType::SYNONYM);
    CHECK(argList[0].argumentValue == "a");

    CHECK(argList[1].argumentType == ArgumentType::UNDERSCORE);
    CHECK(argList[1].argumentValue == "_");

    CHECK(argList[2].argumentType == ArgumentType::UNDERSCORE);
    CHECK(argList[2].argumentValue == "_");
}

TEST_CASE ("PARSER - PATTERN CLAUSE CHECK WITH ARGUMENTS: VARIABLE, WILDCARD") {
    QueryParser parser = QueryParser();

    std::string pql = "variable v; assign a; stmt s; \nSelect v pattern a (v, _)";
    Query query = parser.getQuery(pql);
    PatternClause patternClause = query.getPatternClauses()[0];
    std::vector<Argument> argList = patternClause.argList;

    CHECK(argList[0].argumentType == ArgumentType::SYNONYM);
    CHECK(argList[0].argumentValue == "a");

    CHECK(argList[1].argumentType == ArgumentType::SYNONYM);
    CHECK(argList[1].argumentValue == "v");

    CHECK(argList[2].argumentType == ArgumentType::UNDERSCORE);
    CHECK(argList[2].argumentValue == "_");
}

TEST_CASE ("PARSER - PATTERN CLAUSE CHECK WITH ARGUMENTS: VARIABLE, IDENT") {
    QueryParser parser = QueryParser();

    std::string pql = "variable v; assign a; stmt s; \nSelect v pattern a (v, \"x\")";
    Query query = parser.getQuery(pql);
    PatternClause patternClause = query.getPatternClauses()[0];
    std::vector<Argument> argList = patternClause.argList;

    CHECK(argList[0].argumentType == ArgumentType::SYNONYM);
    CHECK(argList[0].argumentValue == "a");

    CHECK(argList[1].argumentType == ArgumentType::SYNONYM);
    CHECK(argList[1].argumentValue == "v");

    CHECK(argList[2].argumentType == ArgumentType::IDENT);
    CHECK(argList[2].argumentValue == "x");
}

TEST_CASE ("PARSER - PATTERN CLAUSE CHECK WITH ARGUMENTS: VARIABLE, PARTIAL WILDCARD") {
    QueryParser parser = QueryParser();

    std::string pql = "variable v; assign a; stmt s; \nSelect v pattern a (v, _\"x\"_)";
    Query query = parser.getQuery(pql);
    PatternClause patternClause = query.getPatternClauses()[0];
    std::vector<Argument> argList = patternClause.argList;

    CHECK(argList[0].argumentType == ArgumentType::SYNONYM);
    CHECK(argList[0].argumentValue == "a");

    CHECK(argList[1].argumentType == ArgumentType::SYNONYM);
    CHECK(argList[1].argumentValue == "v");

    CHECK(argList[2].argumentType == ArgumentType::PARTIAL_UNDERSCORE);
    CHECK(argList[2].argumentValue == "_\"x\"_");
}

TEST_CASE ("PARSER - MULTICLAUSE CHECK") {
    QueryParser parser = QueryParser();

    std::string pql = "stmt s; assign a; \nSelect s such that Parent*(s,3) pattern a (_, _)";
    Query query = parser.getQuery(pql);
    SuchThatClause suchThatClause = query.getSuchThatClauses()[0];
    std::vector<Argument> argList = suchThatClause.argList;

    PatternClause patternClause = query.getPatternClauses()[0];
    std::vector<Argument> patternArgList = patternClause.argList;

    CHECK(suchThatClause.relRef == RelRef::PARENT_T);
    CHECK(argList[0].argumentType == ArgumentType::SYNONYM);
    CHECK(argList[0].argumentValue == "s");

    CHECK(argList[1].argumentType == ArgumentType::STMT_NO);
    CHECK(argList[1].argumentValue == "3");

    CHECK(patternArgList[0].argumentType == ArgumentType::SYNONYM);
    CHECK(patternArgList[0].argumentValue == "a");

    CHECK(patternArgList[1].argumentType == ArgumentType::UNDERSCORE);
    CHECK(patternArgList[1].argumentValue == "_");

    CHECK(patternArgList[2].argumentType == ArgumentType::UNDERSCORE);
    CHECK(patternArgList[2].argumentValue == "_");
}


