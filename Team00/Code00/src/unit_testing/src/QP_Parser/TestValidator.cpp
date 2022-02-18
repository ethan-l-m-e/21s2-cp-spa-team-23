#include "catch.hpp"
#include "QP_Parser/Validator.h"

#include <vector>
#include <string>
#include <map>
#include <utility>
#include <iostream>

using namespace qp;

// Check if validator works for declarations
TEST_CASE ("QP SYNTACTIC VALIDATOR: SINGLE CHAR DECLARATION") {
    std::string query = "variable v1; Select v";
    Validator validator = Validator();

    REQUIRE_NOTHROW(validator.validateQueryStructure(query));
}

TEST_CASE ("QP SYNTACTIC VALIDATOR: DOUBLE CHAR DECLARATION") {
    std::string query = "variable va; \n Select va";
    Validator validator = Validator();

    REQUIRE_NOTHROW(validator.validateQueryStructure(query));
}

TEST_CASE ("QP SYNTACTIC VALIDATOR: CHAT+INT DECLARATION") {
    std::string query = "variable v1; \n Select v1";
    Validator validator = Validator();

    REQUIRE_NOTHROW(validator.validateQueryStructure(query));
}

TEST_CASE ("QP SYNTACTIC VALIDATOR: STMT DECLARATION") {
    std::string query = "stmt s; \n Select v1";
    Validator validator = Validator();

    REQUIRE_NOTHROW(validator.validateQueryStructure(query));
}

TEST_CASE ("QP SYNTACTIC VALIDATOR: READ DECLARATION") {
    std::string query = "read s; \n Select v1";
    Validator validator = Validator();

    REQUIRE_NOTHROW(validator.validateQueryStructure(query));
}

TEST_CASE ("QP SYNTACTIC VALIDATOR: PRINT DECLARATION") {
    std::string query = "print s; \n Select v1";
    Validator validator = Validator();

    REQUIRE_NOTHROW(validator.validateQueryStructure(query));
}

TEST_CASE ("QP SYNTACTIC VALIDATOR: CALL DECLARATION") {
    std::string query = "call s; \n Select v1";
    Validator validator = Validator();

    REQUIRE_NOTHROW(validator.validateQueryStructure(query));
}

TEST_CASE ("QP SYNTACTIC VALIDATOR: WHILE DECLARATION") {
    std::string query = "while s; \n Select v1";
    Validator validator = Validator();

    REQUIRE_NOTHROW(validator.validateQueryStructure(query));
}

TEST_CASE ("QP SYNTACTIC VALIDATOR: IF DECLARATION") {
    std::string query = "if s; \n Select v1";
    Validator validator = Validator();

    REQUIRE_NOTHROW(validator.validateQueryStructure(query));
}

TEST_CASE ("QP SYNTACTIC VALIDATOR: ASSIGN DECLARATION") {
    std::string query = "assign s; \n Select v1";
    Validator validator = Validator();

    REQUIRE_NOTHROW(validator.validateQueryStructure(query));
}

TEST_CASE ("QP SYNTACTIC VALIDATOR: CONSTANT DECLARATION") {
    std::string query = "constant s; \n Select v1";
    Validator validator = Validator();

    REQUIRE_NOTHROW(validator.validateQueryStructure(query));
}

TEST_CASE ("QP SYNTACTIC VALIDATOR: PROCEDURE DECLARATION") {
    std::string query = "procedure s; \n Select v1";
    Validator validator = Validator();

    REQUIRE_NOTHROW(validator.validateQueryStructure(query));
}

TEST_CASE ("QP SYNTACTIC VALIDATOR: DOUBLE DECLARATIONS") {
    std::string query = "variable v; stmt s; \n Select v1";
    Validator validator = Validator();

    REQUIRE_NOTHROW(validator.validateQueryStructure(query));
}

TEST_CASE ("QP SYNTACTIC VALIDATOR: TRIPLE DECLARATIONS") {
    std::string query = "variable v; stmt s; procedure p; \n Select v1";
    Validator validator = Validator();

    REQUIRE_NOTHROW(validator.validateQueryStructure(query));
}

TEST_CASE ("QP SYNTACTIC VALIDATOR: MULTIPLE DECLARATIONS OF SAME DESIGN ENTITY") {
    std::string query = "variable v1, v2, v3; \n Select v1";
    Validator validator = Validator();

    REQUIRE_NOTHROW(validator.validateQueryStructure(query));
}

TEST_CASE ("QP SYNTACTIC VALIDATOR: MULTIPLE DECLARATIONS OF SAME DESIGN ENTITIES") {
    std::string query = "variable v1, v2, v3; procedure p1, p2; \n Select v1";
    Validator validator = Validator();

    REQUIRE_NOTHROW(validator.validateQueryStructure(query));
}

TEST_CASE ("QP SYNTACTIC VALIDATOR: SYNONYM NAME SAME AS DESIGN ENTITY - STMT") {
    std::string query = "stmt stmt; \n Select v1";
    Validator validator = Validator();

    REQUIRE_NOTHROW(validator.validateQueryStructure(query));
}

TEST_CASE ("QP SYNTACTIC VALIDATOR: SYNONYM NAME SAME AS DESIGN ENTITY - READ") {
    std::string query = "read read; \n Select v1";
    Validator validator = Validator();

    REQUIRE_NOTHROW(validator.validateQueryStructure(query));
}

TEST_CASE ("QP SYNTACTIC VALIDATOR: SYNONYM NAME SAME AS DESIGN ENTITY - PRINT") {
    std::string query = "print print; \n Select v1";
    Validator validator = Validator();

    REQUIRE_NOTHROW(validator.validateQueryStructure(query));
}

TEST_CASE ("QP SYNTACTIC VALIDATOR: SYNONYM NAME SAME AS DESIGN ENTITY - CALL") {
    std::string query = "call call; \n Select v1";
    Validator validator = Validator();

    REQUIRE_NOTHROW(validator.validateQueryStructure(query));
}

TEST_CASE ("QP SYNTACTIC VALIDATOR: SYNONYM NAME SAME AS DESIGN ENTITY - WHILE") {
    std::string query = "while while; \n Select v1";
    Validator validator = Validator();

    REQUIRE_NOTHROW(validator.validateQueryStructure(query));
}

TEST_CASE ("QP SYNTACTIC VALIDATOR: SYNONYM NAME SAME AS DESIGN ENTITY - IF") {
    std::string query = "if if; \n Select v1";
    Validator validator = Validator();

    REQUIRE_NOTHROW(validator.validateQueryStructure(query));
}

TEST_CASE ("QP SYNTACTIC VALIDATOR: SYNONYM NAME SAME AS DESIGN ENTITY - ASSIGN") {
    std::string query = "assign assign; \n Select v1";
    Validator validator = Validator();

    REQUIRE_NOTHROW(validator.validateQueryStructure(query));
}

TEST_CASE ("QP SYNTACTIC VALIDATOR: SYNONYM NAME SAME AS DESIGN ENTITY - VARIABLE") {
    std::string query = "variable variable; \n Select v1";
    Validator validator = Validator();

    REQUIRE_NOTHROW(validator.validateQueryStructure(query));
}

TEST_CASE ("QP SYNTACTIC VALIDATOR: SYNONYM NAME SAME AS DESIGN ENTITY - CONSTANT") {
    std::string query = "constant constant; \n Select v1";
    Validator validator = Validator();

    REQUIRE_NOTHROW(validator.validateQueryStructure(query));
}

TEST_CASE ("QP SYNTACTIC VALIDATOR: SYNONYM NAME SAME AS DESIGN ENTITY - PROCEDURE") {
    std::string query = "procedure procedure; \n Select v1";
    Validator validator = Validator();

    REQUIRE_NOTHROW(validator.validateQueryStructure(query));
}

TEST_CASE ("QP SYNTACTIC VALIDATOR: SYNONYM NAME SAME AS DESIGN ENTITY - STMT READ") {
    std::string query = "stmt read; \n Select v1";
    Validator validator = Validator();

    REQUIRE_NOTHROW(validator.validateQueryStructure(query));
}

TEST_CASE ("QP SYNTACTIC VALIDATOR: SYNONYM NAME IS SELECT") {
    std::string query = "stmt Select; \n Select v1";
    Validator validator = Validator();

    REQUIRE_NOTHROW(validator.validateQueryStructure(query));
}

TEST_CASE ("QP SYNTACTIC VALIDATOR: SYNONYM NAME IS PATTERN") {
    std::string query = "stmt pattern; \n Select v1";
    Validator validator = Validator();

    REQUIRE_NOTHROW(validator.validateQueryStructure(query));
}

// Invalid declarations
TEST_CASE ("QP SYNTACTIC VALIDATOR: INT DECLARATION") {
    std::string query = "variable 1; \n Select v1";
    Validator validator = Validator();

    REQUIRE_THROWS(validator.validateQueryStructure(query));
}

TEST_CASE ("QP SYNTACTIC VALIDATOR: INT-CHAR DECLARATION") {
    std::string query = "variable 1v; \n Select v1";
    Validator validator = Validator();

    REQUIRE_THROWS(validator.validateQueryStructure(query));
}

TEST_CASE ("QP SYNTACTIC VALIDATOR: INCORRECT DESIGN ENTITY") {
    std::string query = "unknown v; \n Select v1";
    Validator validator = Validator();

    REQUIRE_THROWS(validator.validateQueryStructure(query));
}

TEST_CASE ("QP SYNTACTIC VALIDATOR: MISSPELLED DESIGN ENTITY") {
    std::string query = "varible v; \n Select v1";
    Validator validator = Validator();

    REQUIRE_THROWS(validator.validateQueryStructure(query));
}

TEST_CASE ("QP SYNTACTIC VALIDATOR: SHORTENED VERSION OF DESIGN ENTITY") {
    std::string query = "var v; \n Select v1";
    Validator validator = Validator();

    REQUIRE_THROWS(validator.validateQueryStructure(query));
}

TEST_CASE ("QP SYNTACTIC VALIDATOR: WRONG CAPS DESIGN ENTITY") {
    std::string query = "Variable v; \n Select v1";
    Validator validator = Validator();

    REQUIRE_THROWS(validator.validateQueryStructure(query));
}

TEST_CASE ("QP SYNTACTIC VALIDATOR: INCORRECT SEMICOLON USAGE") {
    std::string query = "variable v1; v2; \n Select v1";
    Validator validator = Validator();

    REQUIRE_THROWS(validator.validateQueryStructure(query));
}

TEST_CASE ("QP SYNTACTIC VALIDATOR: INCORRECT COMMA USAGE") {
    std::string query = "variable v1, stmt s; \n Select v1";
    Validator validator = Validator();

    REQUIRE_THROWS(validator.validateQueryStructure(query));
}

TEST_CASE ("QP SYNTACTIC VALIDATOR: INCORRECT COMMA USAGE - 2") {
    std::string query = "variable v1; stmt, s; \n Select v1";
    Validator validator = Validator();

    REQUIRE_THROWS(validator.validateQueryStructure(query));
}

// Valid Syntactic Queries for Select Clause
TEST_CASE ("QP SYNTACTIC VALIDATOR: SELECT CLAUSE") {
    std::string query = "variable v; \n Select v";
    Validator validator = Validator();

    REQUIRE_NOTHROW(validator.validateQueryStructure(query));
}

TEST_CASE ("QP SYNTACTIC VALIDATOR: SELECT CLAUSE WITH SYNONYM HAVING AN INT") {
    std::string query = "variable v; \n Select v2";
    Validator validator = Validator();

    REQUIRE_NOTHROW(validator.validateQueryStructure(query));
}

TEST_CASE ("QP SYNTACTIC VALIDATOR: SELECT CLAUSE WITH MULTI CHAR SYNONYM") {
    std::string query = "variable v; \n Select var";
    Validator validator = Validator();

    REQUIRE_NOTHROW(validator.validateQueryStructure(query));
}

TEST_CASE ("QP SYNTACTIC VALIDATOR: SELECT CLAUSE WITH SELECT AS SYNONYM") {
    std::string query = "variable v; \n Select Select";
    Validator validator = Validator();

    REQUIRE_NOTHROW(validator.validateQueryStructure(query));
}

// Invalid queries for select clause
TEST_CASE ("QP SYNTACTIC VALIDATOR: SELECT CLAUSE WITH INT AS SYNONYM") {
    std::string query = "variable v; \n Select 123";
    Validator validator = Validator();

    REQUIRE_THROWS(validator.validateQueryStructure(query));
}

TEST_CASE ("QP SYNTACTIC VALIDATOR: LOWER CASE SELECT CLAUSE") {
    std::string query = "variable v; \n select v1";
    Validator validator = Validator();

    REQUIRE_THROWS(validator.validateQueryStructure(query));
}

TEST_CASE ("QP SYNTACTIC VALIDATOR: MISSPELLED SELECT CLAUSE") {
    std::string query = "variable v; \n Selec v1";
    Validator validator = Validator();

    REQUIRE_THROWS(validator.validateQueryStructure(query));
}

TEST_CASE ("QP SYNTACTIC VALIDATOR: NO SELECT CLAUSE") {
    std::string query = "variable v;";
    Validator validator = Validator();

    REQUIRE_THROWS(validator.validateQueryStructure(query));
}

// Valid Queries for Such That Clauses
TEST_CASE ("QP SYNTACTIC VALIDATOR: FOLLOWS CLAUSE WITH SYNONYM FIRST ARGUMENT") {
    std::string query = "stmt s; Select s such that Follows(s, 3)";
    Validator validator = Validator();

    REQUIRE_NOTHROW(validator.validateQueryStructure(query));
}

TEST_CASE ("QP SYNTACTIC VALIDATOR: FOLLOWS CLAUSE WITH WILDCARD FIRST ARGUMENT") {
    std::string query = "stmt s; Select s such that Follows(_, 3)";
    Validator validator = Validator();

    REQUIRE_NOTHROW(validator.validateQueryStructure(query));
}

TEST_CASE ("QP SYNTACTIC VALIDATOR: FOLLOWS CLAUSE WITH INTEGER FIRST ARGUMENT") {
    std::string query = "stmt s; Select s such that Follows(5, 3)";
    Validator validator = Validator();

    REQUIRE_NOTHROW(validator.validateQueryStructure(query));
}

TEST_CASE ("QP SYNTACTIC VALIDATOR: FOLLOWS CLAUSE WITH SYNONYM SECOND ARGUMENT") {
    std::string query = "stmt s; Select s such that Follows(3, s)";
    Validator validator = Validator();

    REQUIRE_NOTHROW(validator.validateQueryStructure(query));
}

TEST_CASE ("QP SYNTACTIC VALIDATOR: FOLLOWS CLAUSE WITH WILDCARD SECOND ARGUMENT") {
    std::string query = "stmt s; Select s such that Follows(s, _)";
    Validator validator = Validator();

    REQUIRE_NOTHROW(validator.validateQueryStructure(query));
}

TEST_CASE ("QP SYNTACTIC VALIDATOR: FOLLOWS CLAUSE WITH INTEGER SECOND ARGUMENT") {
    std::string query = "stmt s; Select s such that Follows(s, 3)";
    Validator validator = Validator();

    REQUIRE_NOTHROW(validator.validateQueryStructure(query));
}

TEST_CASE ("QP SYNTACTIC VALIDATOR: FOLLOWS* CLAUSE WITH SYNONYM FIRST ARGUMENT") {
    std::string query = "stmt s; Select s such that Follows*(s, 3)";
    Validator validator = Validator();

    REQUIRE_NOTHROW(validator.validateQueryStructure(query));
}

TEST_CASE ("QP SYNTACTIC VALIDATOR: FOLLOWS* CLAUSE WITH WILDCARD FIRST ARGUMENT") {
    std::string query = "stmt s; Select s such that Follows*(_, 3)";
    Validator validator = Validator();

    REQUIRE_NOTHROW(validator.validateQueryStructure(query));
}

TEST_CASE ("QP SYNTACTIC VALIDATOR: FOLLOWS* CLAUSE WITH INTEGER FIRST ARGUMENT") {
    std::string query = "stmt s; Select s such that Follows*(5, 3)";
    Validator validator = Validator();

    REQUIRE_NOTHROW(validator.validateQueryStructure(query));
}

TEST_CASE ("QP SYNTACTIC VALIDATOR: FOLLOWS* CLAUSE WITH SYNONYM SECOND ARGUMENT") {
    std::string query = "stmt s; Select s such that Follows*(3, s)";
    Validator validator = Validator();

    REQUIRE_NOTHROW(validator.validateQueryStructure(query));
}

TEST_CASE ("QP SYNTACTIC VALIDATOR: FOLLOWS* CLAUSE WITH WILDCARD SECOND ARGUMENT") {
    std::string query = "stmt s; Select s such that Follows*(s, _)";
    Validator validator = Validator();

    REQUIRE_NOTHROW(validator.validateQueryStructure(query));
}

TEST_CASE ("QP SYNTACTIC VALIDATOR: FOLLOWS* CLAUSE WITH INTEGER SECOND ARGUMENT") {
    std::string query = "stmt s; Select s such that Follows*(s, 3)";
    Validator validator = Validator();

    REQUIRE_NOTHROW(validator.validateQueryStructure(query));
}

TEST_CASE ("QP SYNTACTIC VALIDATOR: PARENT CLAUSE WITH SYNONYM FIRST ARGUMENT") {
    std::string query = "stmt s; Select s such that Parent(s, 3)";
    Validator validator = Validator();

    REQUIRE_NOTHROW(validator.validateQueryStructure(query));
}

TEST_CASE ("QP SYNTACTIC VALIDATOR: PARENT CLAUSE WITH WILDCARD FIRST ARGUMENT") {
    std::string query = "stmt s; Select s such that Parent(_, 3)";
    Validator validator = Validator();

    REQUIRE_NOTHROW(validator.validateQueryStructure(query));
}

TEST_CASE ("QP SYNTACTIC VALIDATOR: PARENT CLAUSE WITH INTEGER FIRST ARGUMENT") {
    std::string query = "stmt s; Select s such that Parent(5, 3)";
    Validator validator = Validator();

    REQUIRE_NOTHROW(validator.validateQueryStructure(query));
}

TEST_CASE ("QP SYNTACTIC VALIDATOR: PARENT CLAUSE WITH SYNONYM SECOND ARGUMENT") {
    std::string query = "stmt s; Select s such that Parent(3, s)";
    Validator validator = Validator();

    REQUIRE_NOTHROW(validator.validateQueryStructure(query));
}

TEST_CASE ("QP SYNTACTIC VALIDATOR: PARENT CLAUSE WITH WILDCARD SECOND ARGUMENT") {
    std::string query = "stmt s; Select s such that Parent(s, _)";
    Validator validator = Validator();

    REQUIRE_NOTHROW(validator.validateQueryStructure(query));
}

TEST_CASE ("QP SYNTACTIC VALIDATOR: PARENT CLAUSE WITH INTEGER SECOND ARGUMENT") {
    std::string query = "stmt s; Select s such that Parent(s, 3)";
    Validator validator = Validator();

    REQUIRE_NOTHROW(validator.validateQueryStructure(query));
}

TEST_CASE ("QP SYNTACTIC VALIDATOR: PARENT* CLAUSE WITH SYNONYM FIRST ARGUMENT") {
    std::string query = "stmt s; Select s such that Parent*(s, 3)";
    Validator validator = Validator();

    REQUIRE_NOTHROW(validator.validateQueryStructure(query));
}

TEST_CASE ("QP SYNTACTIC VALIDATOR: PARENT* CLAUSE WITH WILDCARD FIRST ARGUMENT") {
    std::string query = "stmt s; Select s such that Parent*(_, 3)";
    Validator validator = Validator();

    REQUIRE_NOTHROW(validator.validateQueryStructure(query));
}

TEST_CASE ("QP SYNTACTIC VALIDATOR: PARENT* CLAUSE WITH INTEGER FIRST ARGUMENT") {
    std::string query = "stmt s; Select s such that Parent*(5, 3)";
    Validator validator = Validator();

    REQUIRE_NOTHROW(validator.validateQueryStructure(query));
}

TEST_CASE ("QP SYNTACTIC VALIDATOR: PARENT* CLAUSE WITH SYNONYM SECOND ARGUMENT") {
    std::string query = "stmt s; Select s such that Parent*(3, s)";
    Validator validator = Validator();

    REQUIRE_NOTHROW(validator.validateQueryStructure(query));
}

TEST_CASE ("QP SYNTACTIC VALIDATOR: PARENT* CLAUSE WITH WILDCARD SECOND ARGUMENT") {
    std::string query = "stmt s; Select s such that Parent*(s, _)";
    Validator validator = Validator();

    REQUIRE_NOTHROW(validator.validateQueryStructure(query));
}

TEST_CASE ("QP SYNTACTIC VALIDATOR: PARENT* CLAUSE WITH INTEGER SECOND ARGUMENT") {
    std::string query = "stmt s; Select s such that Parent*(s, 3)";
    Validator validator = Validator();

    REQUIRE_NOTHROW(validator.validateQueryStructure(query));
}

TEST_CASE ("QP SYNTACTIC VALIDATOR: USES CLAUSE WITH SYNONYM FIRST ARGUMENT") {
    std::string query = "stmt s; variable v; Select s such that Uses(s, v)";
    Validator validator = Validator();

    REQUIRE_NOTHROW(validator.validateQueryStructure(query));
}

TEST_CASE ("QP SYNTACTIC VALIDATOR: USES CLAUSE WITH WILDCARD FIRST ARGUMENT") {
    std::string query = "stmt s; variable v; Select s such that Uses(_, v)";
    Validator validator = Validator();

    REQUIRE_NOTHROW(validator.validateQueryStructure(query));
}

TEST_CASE ("QP SYNTACTIC VALIDATOR: USES CLAUSE WITH INTEGER FIRST ARGUMENT") {
    std::string query = "stmt s; variable v; Select s such that Uses(5, v)";
    Validator validator = Validator();

    REQUIRE_NOTHROW(validator.validateQueryStructure(query));
}

TEST_CASE ("QP SYNTACTIC VALIDATOR: USES CLAUSE WITH IDENT FIRST ARGUMENT") {
    std::string query = "stmt s; variable v; Select s such that Uses(\"x\", v)";
    Validator validator = Validator();

    REQUIRE_NOTHROW(validator.validateQueryStructure(query));
}

TEST_CASE ("QP SYNTACTIC VALIDATOR: USES CLAUSE WITH SYNONYM SECOND ARGUMENT") {
    std::string query = "stmt s; variable v; Select s such that Uses(s, v)";
    Validator validator = Validator();

    REQUIRE_NOTHROW(validator.validateQueryStructure(query));
}

TEST_CASE ("QP SYNTACTIC VALIDATOR: USES CLAUSE WITH WILDCARD SECOND ARGUMENT") {
    std::string query = "stmt s; variable v; Select s such that Uses(v, _)";
    Validator validator = Validator();

    REQUIRE_NOTHROW(validator.validateQueryStructure(query));
}

TEST_CASE ("QP SYNTACTIC VALIDATOR: USES CLAUSE WITH IDENT SECOND ARGUMENT") {
    std::string query = "stmt s; variable v; Select s such that Uses(v, \"x\")";
    Validator validator = Validator();

    REQUIRE_NOTHROW(validator.validateQueryStructure(query));
}

TEST_CASE ("QP SYNTACTIC VALIDATOR: MODIFIES CLAUSE WITH SYNONYM FIRST ARGUMENT") {
    std::string query = "stmt s; variable v; Select s such that Modifies(s, v)";
    Validator validator = Validator();

    REQUIRE_NOTHROW(validator.validateQueryStructure(query));
}

TEST_CASE ("QP SYNTACTIC VALIDATOR: MODIFIES CLAUSE WITH WILDCARD FIRST ARGUMENT") {
    std::string query = "stmt s; variable v; Select s such that Modifies(_, v)";
    Validator validator = Validator();

    REQUIRE_NOTHROW(validator.validateQueryStructure(query));
}

TEST_CASE ("QP SYNTACTIC VALIDATOR: MODIFIES CLAUSE WITH INTEGER FIRST ARGUMENT") {
    std::string query = "stmt s; variable v; Select s such that Modifies(5, v)";
    Validator validator = Validator();

    REQUIRE_NOTHROW(validator.validateQueryStructure(query));
}

TEST_CASE ("QP SYNTACTIC VALIDATOR: MODIFIES CLAUSE WITH IDENT FIRST ARGUMENT") {
    std::string query = "stmt s; variable v; Select s such that Modifies(\"x\", v)";
    Validator validator = Validator();

    REQUIRE_NOTHROW(validator.validateQueryStructure(query));
}

TEST_CASE ("QP SYNTACTIC VALIDATOR: MODIFIES CLAUSE WITH SYNONYM SECOND ARGUMENT") {
    std::string query = "stmt s; variable v; Select s such that Modifies(s, v)";
    Validator validator = Validator();

    REQUIRE_NOTHROW(validator.validateQueryStructure(query));
}

TEST_CASE ("QP SYNTACTIC VALIDATOR: MODIFIES CLAUSE WITH WILDCARD SECOND ARGUMENT") {
    std::string query = "stmt s; variable v; Select s such that Modifies(v, _)";
    Validator validator = Validator();

    REQUIRE_NOTHROW(validator.validateQueryStructure(query));
}

TEST_CASE ("QP SYNTACTIC VALIDATOR: MODIFIES CLAUSE WITH IDENT SECOND ARGUMENT") {
    std::string query = "stmt s; variable v; Select s such that Modifies(v, \"x\")";
    Validator validator = Validator();

    REQUIRE_NOTHROW(validator.validateQueryStructure(query));
}

// Invalid Queries for Such That Clauses
TEST_CASE ("QP SYNTACTIC VALIDATOR: NO SPACE FOR SUCH THAT") {
    std::string query = "stmt s; variable v; Select s suchthat Modifies(v, _)";
    Validator validator = Validator();

    REQUIRE_THROWS(validator.validateQueryStructure(query));
}

TEST_CASE ("QP SYNTACTIC VALIDATOR: MISSPELLED SUCH THAT") {
    std::string query = "stmt s; variable v; Select s such tht Modifies(v, _)";
    Validator validator = Validator();

    REQUIRE_THROWS(validator.validateQueryStructure(query));
}

TEST_CASE ("QP SYNTACTIC VALIDATOR: MISSPELLED MODIFIES CLAUSE") {
    std::string query = "stmt s; variable v; Select s such tht Modifie(v, _)";
    Validator validator = Validator();

    REQUIRE_THROWS(validator.validateQueryStructure(query));
}

TEST_CASE ("QP SYNTACTIC VALIDATOR: INCORRECT CAPS FOR MODIFIES CLAUSE") {
    std::string query = "stmt s; variable v; Select s such tht modifies(v, _)";
    Validator validator = Validator();

    REQUIRE_THROWS(validator.validateQueryStructure(query));
}

TEST_CASE ("QP SYNTACTIC VALIDATOR: INCORRECT IDENT FIRST ARGUMENT FOR FOLLOWS") {
    std::string query = "stmt s; variable v; Select s such tht Follows(\"x\", 3)";
    Validator validator = Validator();

    REQUIRE_THROWS(validator.validateQueryStructure(query));
}

TEST_CASE ("QP SYNTACTIC VALIDATOR: INCORRECT IDENT SECOND ARGUMENT FOR FOLLOWS") {
    std::string query = "stmt s; variable v; Select s such tht Follows(2, \"x\")";
    Validator validator = Validator();

    REQUIRE_THROWS(validator.validateQueryStructure(query));
}

TEST_CASE ("QP SYNTACTIC VALIDATOR: INCORRECT IDENT FIRST ARGUMENT FOR FOLLOWS*") {
    std::string query = "stmt s; variable v; Select s such tht Follows*(\"x\", 3)";
    Validator validator = Validator();

    REQUIRE_THROWS(validator.validateQueryStructure(query));
}

TEST_CASE ("QP SYNTACTIC VALIDATOR: INCORRECT IDENT SECOND ARGUMENT FOR FOLLOWS*") {
    std::string query = "stmt s; variable v; Select s such tht Follows*(2, \"x\")";
    Validator validator = Validator();

    REQUIRE_THROWS(validator.validateQueryStructure(query));
}

TEST_CASE ("QP SYNTACTIC VALIDATOR: INCORRECT IDENT FIRST ARGUMENT FOR PARENT") {
    std::string query = "stmt s; variable v; Select s such tht Parent(\"x\", 3)";
    Validator validator = Validator();

    REQUIRE_THROWS(validator.validateQueryStructure(query));
}

TEST_CASE ("QP SYNTACTIC VALIDATOR: INCORRECT IDENT SECOND ARGUMENT FOR PARENT") {
    std::string query = "stmt s; variable v; Select s such tht Parent(2, \"x\")";
    Validator validator = Validator();

    REQUIRE_THROWS(validator.validateQueryStructure(query));
}

TEST_CASE ("QP SYNTACTIC VALIDATOR: INCORRECT IDENT FIRST ARGUMENT FOR PARENT*") {
    std::string query = "stmt s; variable v; Select s such tht Parent*(\"x\", 3)";
    Validator validator = Validator();

    REQUIRE_THROWS(validator.validateQueryStructure(query));
}

TEST_CASE ("QP SYNTACTIC VALIDATOR: INCORRECT IDENT SECOND ARGUMENT FOR PARENT*") {
    std::string query = "stmt s; variable v; Select s such tht Parent*(2, \"x\")";
    Validator validator = Validator();

    REQUIRE_THROWS(validator.validateQueryStructure(query));
}

TEST_CASE ("QP SYNTACTIC VALIDATOR: INCORRECT INTEGER FIRST ARGUMENT FOR USES") {
    std::string query = "stmt s; variable v; Select v such tht Uses(3, v)";
    Validator validator = Validator();

    REQUIRE_THROWS(validator.validateQueryStructure(query));
}

TEST_CASE ("QP SYNTACTIC VALIDATOR: INCORRECT INTEGER SECOND ARGUMENT FOR USES") {
    std::string query = "stmt s; variable v; Select v such tht Uses(v, 3)";
    Validator validator = Validator();

    REQUIRE_THROWS(validator.validateQueryStructure(query));
}

TEST_CASE ("QP SYNTACTIC VALIDATOR: INCORRECT INTEGER FIRST ARGUMENT FOR MODIFIES") {
    std::string query = "stmt s; variable v; Select v such tht Modifies(3, v)";
    Validator validator = Validator();

    REQUIRE_THROWS(validator.validateQueryStructure(query));
}

TEST_CASE ("QP SYNTACTIC VALIDATOR: INCORRECT INTEGER SECOND ARGUMENT FOR MODIFIES") {
    std::string query = "stmt s; variable v; Select v such tht Modifies(v, 3)";
    Validator validator = Validator();

    REQUIRE_THROWS(validator.validateQueryStructure(query));
}

// TODO: Edit below

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
