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

// Check Valid queries for Pattern
TEST_CASE ("QP SYNTACTIC VALIDATOR: SIMPLE PATTERN") {
    std::string query = "assign a; Select a pattern a(_, _)";
    Validator validator = Validator();

    REQUIRE_NOTHROW(validator.validateQueryStructure(query));
}

TEST_CASE ("QP SYNTACTIC VALIDATOR: PATTERN WITH DOUBLE CHAR SYN-ASSIGN") {
    std::string query = "assign a; Select a pattern ab(_, _)";
    Validator validator = Validator();

    REQUIRE_NOTHROW(validator.validateQueryStructure(query));
}

TEST_CASE ("QP SYNTACTIC VALIDATOR: PATTERN WITH CHAR+INT SYN-ASSIGN") {
    std::string query = "assign a; Select a pattern a1(_, _)";
    Validator validator = Validator();

    REQUIRE_NOTHROW(validator.validateQueryStructure(query));
}

TEST_CASE ("QP SYNTACTIC VALIDATOR: PATTERN WITH SYNONYM FOR FIRST ARGUMENT") {
    std::string query = "assign a; stmt s; Select a pattern a1(s, _)";
    Validator validator = Validator();

    REQUIRE_NOTHROW(validator.validateQueryStructure(query));
}

TEST_CASE ("QP SYNTACTIC VALIDATOR: PATTERN WITH IDENT FOR FIRST ARGUMENT") {
    std::string query = "assign a; stmt s; Select a pattern a1(\"x\", _)";
    Validator validator = Validator();

    REQUIRE_NOTHROW(validator.validateQueryStructure(query));
}

TEST_CASE ("QP SYNTACTIC VALIDATOR: PATTERN WITH PARTIAL WILDCARD FOR SECOND ARGUMENT") {
    std::string query = "assign a; stmt s; Select a pattern a1(_, _\"x\"_)";
    Validator validator = Validator();

    REQUIRE_NOTHROW(validator.validateQueryStructure(query));
}

TEST_CASE ("QP SYNTACTIC VALIDATOR: PATTERN WITH IDENT FOR SECOND ARGUMENT") {
    std::string query = "assign a; stmt s; Select a pattern a1(_, \"x\")";
    Validator validator = Validator();

    REQUIRE_NOTHROW(validator.validateQueryStructure(query));
}

TEST_CASE ("QP SYNTACTIC VALIDATOR: PATTERN WITH PATTERN FOR SYN-ASSIGN") {
    std::string query = "assign a; stmt s; Select pattern pattern pattern(_, \"x\")";
    Validator validator = Validator();

    REQUIRE_NOTHROW(validator.validateQueryStructure(query));
}

TEST_CASE ("QP SYNTACTIC VALIDATOR: PATTERN WITH SELECT FOR SYN-ASSIGN") {
    std::string query = "assign a; stmt s; Select Select pattern Select(_, \"x\")";
    Validator validator = Validator();

    REQUIRE_NOTHROW(validator.validateQueryStructure(query));
}

// Invalid queries for pattern
TEST_CASE ("QP SYNTACTIC VALIDATOR: PATTERN WITH INTEGER FOR FIRST ARGUMENT") {
    std::string query = "assign a; stmt s; Select Select pattern Select(3, _)";
    Validator validator = Validator();

    REQUIRE_THROWS(validator.validateQueryStructure(query));
}

TEST_CASE ("QP SYNTACTIC VALIDATOR: PATTERN WITH INTEGER FOR SECOND ARGUMENT") {
    std::string query = "assign a; stmt s; Select a pattern a(_, 3)";
    Validator validator = Validator();

    REQUIRE_THROWS(validator.validateQueryStructure(query));
}

TEST_CASE ("QP SYNTACTIC VALIDATOR: PATTERN WITH PARTIAL WILDCARD FOR FIRST ARGUMENT") {
    std::string query = "assign a; stmt s; Select a pattern a(_\"x\"_, _)";
    Validator validator = Validator();

    REQUIRE_THROWS(validator.validateQueryStructure(query));
}

TEST_CASE ("QP SYNTACTIC VALIDATOR: PATTERN WITH SYNONYM FOR SECOND ARGUMENT") {
    std::string query = "assign a; stmt s; Select a pattern a(_, s)";
    Validator validator = Validator();

    REQUIRE_THROWS(validator.validateQueryStructure(query));
}

TEST_CASE ("QP SYNTACTIC VALIDATOR: PATTERN WITH INTEGER AS SYN-ASSIGN") {
    std::string query = "assign a; stmt s; Select a pattern 3(_, s)";
    Validator validator = Validator();

    REQUIRE_THROWS(validator.validateQueryStructure(query));
}

// Check valid queries for multi-clauses
TEST_CASE ("QP SYNTACTIC VALIDATOR: MULTI CLAUSES") {
    std::string query = "assign a; stmt s; Select a pattern a(_, _) such that Follows(3, 2)";
    Validator validator = Validator();

    REQUIRE_NOTHROW(validator.validateQueryStructure(query));
}

TEST_CASE ("QP SYNTACTIC VALIDATOR: MULTI CLAUSES SUCH THAT CLAUSE FIRST THEN PATTERN") {
    std::string query = "assign a; stmt s; Select a such that Follows(3, 2) pattern a(_, _) ";
    Validator validator = Validator();

    REQUIRE_NOTHROW(validator.validateQueryStructure(query));
}

TEST_CASE ("QP SYNTACTIC VALIDATOR: SUCH THAT PATTERN INSTEAD OF RELATIONSHIP") {
    std::string query = "assign a; stmt s; Select a such that pattern a(_, _) ";
    Validator validator = Validator();

    REQUIRE_THROWS(validator.validateQueryStructure(query));
}

TEST_CASE ("QP SYNTACTIC VALIDATOR: NO SUCH THAT WITH RELATIONSHIP") {
    std::string query = "assign a; stmt s; Select a Follows(3, 2)";
    Validator validator = Validator();

    REQUIRE_THROWS(validator.validateQueryStructure(query));
}

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
    queryToken.selectClauseToken = "v";

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
    queryToken.selectClauseToken = "v";

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
    queryToken.selectClauseToken = "v1";

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
    queryToken.selectClauseToken = "v";

    Validator validator = Validator();
    REQUIRE_THROWS(validator.checkForSemantics(queryToken));
}

// Check validity for such that clause tokens
TEST_CASE ("QP SEMANTIC VALIDATOR: FOLLOWS CLAUSE CHECK FIRST ARGUMENT") {
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
    queryToken.selectClauseToken = "s";

    // Integer as first argument
    SuchThatClauseToken suchThatClauseToken = SuchThatClauseToken();
    std::pair<std::string, std::string> arguments = std::make_pair("3", "2");
    suchThatClauseToken.relRef = "Follows";
    suchThatClauseToken.arguments = &arguments;
    std::vector<SuchThatClauseToken> suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;

    Validator validator = Validator();
    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // Wildcard as first argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::make_pair("_", "2");
    suchThatClauseToken.relRef = "Follows";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;

    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // stmt synonym as first argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::make_pair("s", "2");
    suchThatClauseToken.relRef = "Follows";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;

    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // read synonym as first argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::make_pair("r", "2");
    suchThatClauseToken.relRef = "Follows";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;

    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // print synonym as first argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::make_pair("pn", "2");
    suchThatClauseToken.relRef = "Follows";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;

    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // assign synonym as first argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::make_pair("a", "2");
    suchThatClauseToken.relRef = "Follows";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;

    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // call synonym as first argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::make_pair("c", "2");
    suchThatClauseToken.relRef = "Follows";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;

    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // while synonym as first argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::make_pair("w", "2");
    suchThatClauseToken.relRef = "Follows";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;

    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // while synonym as first argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::make_pair("ifs", "2");
    suchThatClauseToken.relRef = "Follows";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;

    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // variable synonym as first argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::make_pair("v", "2");
    suchThatClauseToken.relRef = "Follows";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;

    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    // constant synonym as first argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::make_pair("con", "2");
    suchThatClauseToken.relRef = "Follows";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;

    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    // procedure synonym as first argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::make_pair("p", "2");
    suchThatClauseToken.relRef = "Follows";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;

    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    // Ident as first argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::make_pair("\"x\"", "2");
    suchThatClauseToken.relRef = "Follows";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;

    REQUIRE_THROWS(validator.checkForSemantics(queryToken));
}

TEST_CASE ("QP SEMANTIC VALIDATOR: FOLLOWS CLAUSE CHECK SECOND ARGUMENT") {
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
    queryToken.selectClauseToken = "s";

    // Integer as second argument
    SuchThatClauseToken suchThatClauseToken = SuchThatClauseToken();
    std::pair<std::string, std::string> arguments = std::make_pair("3", "2");
    suchThatClauseToken.relRef = "Follows";
    suchThatClauseToken.arguments = &arguments;
    std::vector<SuchThatClauseToken> suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;

    Validator validator = Validator();
    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // Wildcard as second argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::make_pair("3", "_");
    suchThatClauseToken.relRef = "Follows";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;

    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // stmt synonym as second argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::make_pair("3", "s");
    suchThatClauseToken.relRef = "Follows";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;

    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // read synonym as second argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::make_pair("3", "r");
    suchThatClauseToken.relRef = "Follows";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;

    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // print synonym as second argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::make_pair("3", "pn");
    suchThatClauseToken.relRef = "Follows";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;

    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // assign synonym as second argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::make_pair("3", "a");
    suchThatClauseToken.relRef = "Follows";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;

    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // call synonym as second argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::make_pair("3", "c");
    suchThatClauseToken.relRef = "Follows";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;

    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // while synonym as second argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::make_pair("3", "w");
    suchThatClauseToken.relRef = "Follows";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;

    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // while synonym as second argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::make_pair("3", "ifs");
    suchThatClauseToken.relRef = "Follows";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;

    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // variable synonym as second argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::make_pair("3", "v");
    suchThatClauseToken.relRef = "Follows";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;

    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    // constant synonym as second argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::make_pair("3", "con");
    suchThatClauseToken.relRef = "Follows";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;

    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    // procedure synonym as second argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::make_pair("3", "p");
    suchThatClauseToken.relRef = "Follows";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;

    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    // ident as second argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::make_pair("3", "\"x\"");
    suchThatClauseToken.relRef = "Follows";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;

    REQUIRE_THROWS(validator.checkForSemantics(queryToken));
}

TEST_CASE ("QP SEMANTIC VALIDATOR: FOLLOWS* CLAUSE CHECK FIRST ARGUMENT") {
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
    queryToken.selectClauseToken = "s";

    // Integer as first argument
    SuchThatClauseToken suchThatClauseToken = SuchThatClauseToken();
    std::pair<std::string, std::string> arguments = std::make_pair("3", "2");
    suchThatClauseToken.relRef = "Follows*";
    suchThatClauseToken.arguments = &arguments;
    std::vector<SuchThatClauseToken> suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;

    Validator validator = Validator();
    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // Wildcard as first argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::make_pair("_", "2");
    suchThatClauseToken.relRef = "Follows*";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;

    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // stmt synonym as first argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::make_pair("s", "2");
    suchThatClauseToken.relRef = "Follows*";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;

    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // read synonym as first argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::make_pair("r", "2");
    suchThatClauseToken.relRef = "Follows*";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;

    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // print synonym as first argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::make_pair("pn", "2");
    suchThatClauseToken.relRef = "Follows*";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;

    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // assign synonym as first argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::make_pair("a", "2");
    suchThatClauseToken.relRef = "Follows*";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;

    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // call synonym as first argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::make_pair("c", "2");
    suchThatClauseToken.relRef = "Follows*";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;

    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // while synonym as first argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::make_pair("w", "2");
    suchThatClauseToken.relRef = "Follows*";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;

    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // while synonym as first argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::make_pair("ifs", "2");
    suchThatClauseToken.relRef = "Follows*";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;

    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // variable synonym as first argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::make_pair("v", "2");
    suchThatClauseToken.relRef = "Follows*";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;

    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    // constant synonym as first argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::make_pair("con", "2");
    suchThatClauseToken.relRef = "Follows*";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;

    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    // procedure synonym as first argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::make_pair("p", "2");
    suchThatClauseToken.relRef = "Follows*";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;

    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    // ident as first argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::make_pair("\"x\"", "2");
    suchThatClauseToken.relRef = "Follows*";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;

    REQUIRE_THROWS(validator.checkForSemantics(queryToken));
}

TEST_CASE ("QP SEMANTIC VALIDATOR: FOLLOWS* CLAUSE CHECK SECOND ARGUMENT") {
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
    queryToken.selectClauseToken = "s";

    // Integer as second argument
    SuchThatClauseToken suchThatClauseToken = SuchThatClauseToken();
    std::pair<std::string, std::string> arguments = std::make_pair("3", "2");
    suchThatClauseToken.relRef = "Follows*";
    suchThatClauseToken.arguments = &arguments;
    std::vector<SuchThatClauseToken> suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;

    Validator validator = Validator();
    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // Wildcard as second argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::make_pair("3", "_");
    suchThatClauseToken.relRef = "Follows*";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;

    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // stmt synonym as second argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::make_pair("3", "s");
    suchThatClauseToken.relRef = "Follows*";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;

    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // read synonym as second argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::make_pair("3", "r");
    suchThatClauseToken.relRef = "Follows*";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;

    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // print synonym as second argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::make_pair("3", "pn");
    suchThatClauseToken.relRef = "Follows*";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;

    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // assign synonym as second argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::make_pair("3", "a");
    suchThatClauseToken.relRef = "Follows*";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;

    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // call synonym as second argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::make_pair("3", "c");
    suchThatClauseToken.relRef = "Follows*";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;

    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // while synonym as second argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::make_pair("3", "w");
    suchThatClauseToken.relRef = "Follows*";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;

    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // while synonym as second argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::make_pair("3", "ifs");
    suchThatClauseToken.relRef = "Follows*";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;

    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // variable synonym as second argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::make_pair("3", "v");
    suchThatClauseToken.relRef = "Follows*";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;

    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    // constant synonym as second argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::make_pair("3", "con");
    suchThatClauseToken.relRef = "Follows*";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;

    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    // procedure synonym as second argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::make_pair("3", "p");
    suchThatClauseToken.relRef = "Follows*";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;

    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    // ident as second argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::make_pair("3", "\"x\"");
    suchThatClauseToken.relRef = "Follows*";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;

    REQUIRE_THROWS(validator.checkForSemantics(queryToken));
}

TEST_CASE ("QP SEMANTIC VALIDATOR: PARENT CLAUSE CHECK FIRST ARGUMENT") {
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
    queryToken.selectClauseToken = "s";

    // Integer as first argument
    SuchThatClauseToken suchThatClauseToken = SuchThatClauseToken();
    std::pair<std::string, std::string> arguments = std::make_pair("3", "2");
    suchThatClauseToken.relRef = "Parent";
    suchThatClauseToken.arguments = &arguments;
    std::vector<SuchThatClauseToken> suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;

    Validator validator = Validator();
    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // Wildcard as first argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::make_pair("_", "2");
    suchThatClauseToken.relRef = "Parent";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;

    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // stmt synonym as first argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::make_pair("s", "2");
    suchThatClauseToken.relRef = "Parent";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;

    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // read synonym as first argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::make_pair("r", "2");
    suchThatClauseToken.relRef = "Parent";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;

    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // print synonym as first argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::make_pair("pn", "2");
    suchThatClauseToken.relRef = "Parent";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;

    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // assign synonym as first argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::make_pair("a", "2");
    suchThatClauseToken.relRef = "Parent";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;

    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // call synonym as first argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::make_pair("c", "2");
    suchThatClauseToken.relRef = "Parent";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;

    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // while synonym as first argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::make_pair("w", "2");
    suchThatClauseToken.relRef = "Parent";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;

    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // while synonym as first argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::make_pair("ifs", "2");
    suchThatClauseToken.relRef = "Parent";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;

    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // variable synonym as first argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::make_pair("v", "2");
    suchThatClauseToken.relRef = "Parent";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;

    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    // constant synonym as first argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::make_pair("con", "2");
    suchThatClauseToken.relRef = "Parent";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;

    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    // procedure synonym as first argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::make_pair("p", "2");
    suchThatClauseToken.relRef = "Parent";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;

    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    // ident as first argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::make_pair("\"x\"", "2");
    suchThatClauseToken.relRef = "Parent";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;

    REQUIRE_THROWS(validator.checkForSemantics(queryToken));
}

TEST_CASE ("QP SEMANTIC VALIDATOR: PARENT CLAUSE CHECK SECOND ARGUMENT") {
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
    queryToken.selectClauseToken = "s";

    // Integer as second argument
    SuchThatClauseToken suchThatClauseToken = SuchThatClauseToken(suchThatClauseToken);
    std::pair<std::string, std::string> arguments = std::make_pair("3", "2");
    suchThatClauseToken.relRef = "Parent";
    suchThatClauseToken.arguments = &arguments;
    std::vector<SuchThatClauseToken> suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;

    Validator validator = Validator();
    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // Wildcard as second argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::make_pair("3", "_");
    suchThatClauseToken.relRef = "Parent";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;

    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // stmt synonym as second argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::make_pair("3", "s");
    suchThatClauseToken.relRef = "Parent";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;

    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // read synonym as second argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::make_pair("3", "r");
    suchThatClauseToken.relRef = "Parent";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;

    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // print synonym as second argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::make_pair("3", "pn");
    suchThatClauseToken.relRef = "Parent";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;

    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // assign synonym as second argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::make_pair("3", "a");
    suchThatClauseToken.relRef = "Parent";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;

    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // call synonym as second argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::make_pair("3", "c");
    suchThatClauseToken.relRef = "Parent";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;

    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // while synonym as second argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::make_pair("3", "w");
    suchThatClauseToken.relRef = "Parent";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;

    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // while synonym as second argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::make_pair("3", "ifs");
    suchThatClauseToken.relRef = "Parent";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;

    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // variable synonym as second argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::make_pair("3", "v");
    suchThatClauseToken.relRef = "Parent";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;

    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    // constant synonym as second argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::make_pair("3", "con");
    suchThatClauseToken.relRef = "Parent";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;

    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    // procedure synonym as second argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::make_pair("3", "p");
    suchThatClauseToken.relRef = "Parent";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;

    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    // ident as second argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::make_pair("3", "\"x\"");
    suchThatClauseToken.relRef = "Parent";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;

    REQUIRE_THROWS(validator.checkForSemantics(queryToken));
}

TEST_CASE ("QP SEMANTIC VALIDATOR: PARENT* CLAUSE CHECK FIRST ARGUMENT") {
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
    queryToken.selectClauseToken = "s";

    // Integer as first argument
    SuchThatClauseToken suchThatClauseToken = SuchThatClauseToken();
    std::pair<std::string, std::string> arguments = std::make_pair("3", "2");
    suchThatClauseToken.relRef = "Parent*";
    suchThatClauseToken.arguments = &arguments;
    std::vector<SuchThatClauseToken> suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;

    Validator validator = Validator();
    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // Wildcard as first argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::make_pair("_", "2");
    suchThatClauseToken.relRef = "Parent*";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;

    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // stmt synonym as first argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::make_pair("s", "2");
    suchThatClauseToken.relRef = "Parent*";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;

    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // read synonym as first argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::make_pair("r", "2");
    suchThatClauseToken.relRef = "Parent*";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;

    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // print synonym as first argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::make_pair("pn", "2");
    suchThatClauseToken.relRef = "Parent*";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;

    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // assign synonym as first argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::make_pair("a", "2");
    suchThatClauseToken.relRef = "Parent*";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;

    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // call synonym as first argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::make_pair("c", "2");
    suchThatClauseToken.relRef = "Parent*";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;

    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // while synonym as first argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::make_pair("w", "2");
    suchThatClauseToken.relRef = "Parent*";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;

    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // while synonym as first argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::make_pair("ifs", "2");
    suchThatClauseToken.relRef = "Parent*";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;

    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // variable synonym as first argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::make_pair("v", "2");
    suchThatClauseToken.relRef = "Parent*";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;

    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    // constant synonym as first argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::make_pair("con", "2");
    suchThatClauseToken.relRef = "Parent*";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;

    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    // procedure synonym as first argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::make_pair("p", "2");
    suchThatClauseToken.relRef = "Parent*";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;

    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    // ident as first argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::make_pair("\"x\"", "2");
    suchThatClauseToken.relRef = "Parent*";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;

    REQUIRE_THROWS(validator.checkForSemantics(queryToken));
}

TEST_CASE ("QP SEMANTIC VALIDATOR: PARENT* CLAUSE CHECK SECOND ARGUMENT") {
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
    queryToken.selectClauseToken = "s";

    // Integer as second argument
    SuchThatClauseToken suchThatClauseToken = SuchThatClauseToken();
    std::pair<std::string, std::string> arguments = std::make_pair("3", "2");
    suchThatClauseToken.relRef = "Parent*";
    suchThatClauseToken.arguments = &arguments;
    std::vector<SuchThatClauseToken> suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;

    Validator validator = Validator();
    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // Wildcard as second argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::make_pair("3", "_");
    suchThatClauseToken.relRef = "Parent*";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;

    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // stmt synonym as second argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::make_pair("3", "s");
    suchThatClauseToken.relRef = "Parent*";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;

    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // read synonym as second argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::make_pair("3", "r");
    suchThatClauseToken.relRef = "Parent*";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;

    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // print synonym as second argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::make_pair("3", "pn");
    suchThatClauseToken.relRef = "Parent*";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;

    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // assign synonym as second argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::make_pair("3", "a");
    suchThatClauseToken.relRef = "Parent*";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;

    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // call synonym as second argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::make_pair("3", "c");
    suchThatClauseToken.relRef = "Parent*";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;

    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // while synonym as second argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::make_pair("3", "w");
    suchThatClauseToken.relRef = "Parent*";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;

    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // while synonym as second argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::make_pair("3", "ifs");
    suchThatClauseToken.relRef = "Parent*";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;

    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // variable synonym as second argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::make_pair("3", "v");
    suchThatClauseToken.relRef = "Parent*";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;

    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    // constant synonym as second argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::make_pair("3", "con");
    suchThatClauseToken.relRef = "Parent*";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;

    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    // procedure synonym as second argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::make_pair("3", "p");
    suchThatClauseToken.relRef = "Parent*";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;

    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    // ident as second argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::make_pair("3", "\"x\"");
    suchThatClauseToken.relRef = "Parent*";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;

    REQUIRE_THROWS(validator.checkForSemantics(queryToken));
}

TEST_CASE ("QP SEMANTIC VALIDATOR: USES CLAUSE CHECK FIRST ARGUMENT") {
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
    queryToken.selectClauseToken = "s";

    // IDENT as first argument
    SuchThatClauseToken suchThatClauseToken = SuchThatClauseToken();
    std::pair<std::string, std::string> arguments = std::make_pair("\"x\"", "_");
    suchThatClauseToken.relRef = "Uses";
    suchThatClauseToken.arguments = &arguments;
    std::vector<SuchThatClauseToken> suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;
    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // assign synonym as first argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::make_pair("a", "_");
    suchThatClauseToken.relRef = "Uses";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;
    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // print synonym as first argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::make_pair("pn", "_");
    suchThatClauseToken.relRef = "Uses";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;
    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // if synonym as first argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::make_pair("ifs", "_");
    suchThatClauseToken.relRef = "Uses";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;
    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // while synonym as first argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::make_pair("w", "_");
    suchThatClauseToken.relRef = "Uses";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;
    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // procedure synonym as first argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::make_pair("p", "_");
    suchThatClauseToken.relRef = "Uses";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;
    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // call synonym as first argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::make_pair("c", "_");
    suchThatClauseToken.relRef = "Uses";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;
    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // stmt synonym as first argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::make_pair("s", "_");
    suchThatClauseToken.relRef = "Uses";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;
    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    // read synonym as first argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::make_pair("r", "_");
    suchThatClauseToken.relRef = "Uses";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;
    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    // variable synonym as first argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::make_pair("v", "_");
    suchThatClauseToken.relRef = "Uses";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;
    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    // constant synonym as first argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::make_pair("con", "_");
    suchThatClauseToken.relRef = "Uses";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;
    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    // wildcard as first argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::make_pair("_", "_");
    suchThatClauseToken.relRef = "Uses";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;
    REQUIRE_THROWS(validator.checkForSemantics(queryToken));
}

TEST_CASE ("QP SEMANTIC VALIDATOR: USES CLAUSE CHECK SECOND ARGUMENT") {
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
    queryToken.selectClauseToken = "s";

    // variable synonym as second argument
    SuchThatClauseToken suchThatClauseToken = SuchThatClauseToken();
    std::pair<std::string, std::string> arguments = std::make_pair("a", "v");
    suchThatClauseToken.relRef = "Uses";
    suchThatClauseToken.arguments = &arguments;
    std::vector<SuchThatClauseToken> suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;
    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // ident as second argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::make_pair("a", "\"x\"");
    suchThatClauseToken.relRef = "Uses";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;
    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // wildcard as second argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::make_pair("a", "_");
    suchThatClauseToken.relRef = "Uses";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;
    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // assign synonym as second argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::make_pair("a", "a");
    suchThatClauseToken.relRef = "Uses";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;
    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    // print synonym as second argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::make_pair("a", "pn");
    suchThatClauseToken.relRef = "Uses";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;
    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    // if synonym as second argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::make_pair("a", "ifs");
    suchThatClauseToken.relRef = "Uses";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;
    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    // while synonym as second argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::make_pair("a", "w");
    suchThatClauseToken.relRef = "Uses";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;
    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    // procedure synonym as second argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::make_pair("a", "p");
    suchThatClauseToken.relRef = "Uses";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;
    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    // call synonym as second argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::make_pair("a", "c");
    suchThatClauseToken.relRef = "Uses";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;
    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    // stmt synonym as second argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::make_pair("a", "s");
    suchThatClauseToken.relRef = "Uses";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;
    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    // read synonym as second argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::make_pair("a", "r");
    suchThatClauseToken.relRef = "Uses";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;
    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    // constant synonym as second argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::make_pair("a", "con");
    suchThatClauseToken.relRef = "Uses";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;
    REQUIRE_THROWS(validator.checkForSemantics(queryToken));
}

TEST_CASE ("QP SEMANTIC VALIDATOR: MODIFIES CLAUSE CHECK FIRST ARGUMENT") {
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
    queryToken.selectClauseToken = "s";

    // IDENT as first argument
    SuchThatClauseToken suchThatClauseToken = SuchThatClauseToken();
    std::pair<std::string, std::string> arguments = std::make_pair("\"x\"", "_");
    suchThatClauseToken.relRef = "Modifies";
    suchThatClauseToken.arguments = &arguments;
    std::vector<SuchThatClauseToken> suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;
    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // assign synonym as first argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::make_pair("a", "_");
    suchThatClauseToken.relRef = "Modifies";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;
    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // read synonym as first argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::make_pair("r", "_");
    suchThatClauseToken.relRef = "Modifies";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;
    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // if synonym as first argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::make_pair("ifs", "_");
    suchThatClauseToken.relRef = "Modifies";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;
    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // while synonym as first argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::make_pair("w", "_");
    suchThatClauseToken.relRef = "Modifies";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;
    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // procedure synonym as first argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::make_pair("p", "_");
    suchThatClauseToken.relRef = "Modifies";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;
    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // call synonym as first argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::make_pair("c", "_");
    suchThatClauseToken.relRef = "Modifies";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;
    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // stmt synonym as first argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::make_pair("s", "_");
    suchThatClauseToken.relRef = "Modifies";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;
    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    // print synonym as first argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::make_pair("pn", "_");
    suchThatClauseToken.relRef = "Modifies";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;
    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    // variable synonym as first argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::make_pair("v", "_");
    suchThatClauseToken.relRef = "Modifies";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;
    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    // constant synonym as first argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::make_pair("con", "_");
    suchThatClauseToken.relRef = "Modifies";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;
    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    // wildcard as first argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::make_pair("_", "_");
    suchThatClauseToken.relRef = "Modifies";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;
    REQUIRE_THROWS(validator.checkForSemantics(queryToken));
}

TEST_CASE ("QP SEMANTIC VALIDATOR: MODIFIES CLAUSE CHECK SECOND ARGUMENT") {
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
    queryToken.selectClauseToken = "s";

    // variable synonym as second argument
    SuchThatClauseToken suchThatClauseToken = SuchThatClauseToken();
    std::pair<std::string, std::string> arguments = std::make_pair("a", "v");
    suchThatClauseToken.relRef = "Modifies";
    suchThatClauseToken.arguments = &arguments;
    std::vector<SuchThatClauseToken> suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;
    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // ident as second argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::make_pair("a", "\"x\"");
    suchThatClauseToken.relRef = "Modifies";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;
    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // wildcard as second argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::make_pair("a", "_");
    suchThatClauseToken.relRef = "Modifies";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;
    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // assign synonym as second argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::make_pair("a", "a");
    suchThatClauseToken.relRef = "Modifies";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;
    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    // print synonym as second argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::make_pair("a", "pn");
    suchThatClauseToken.relRef = "Modifies";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;
    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    // if synonym as second argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::make_pair("a", "ifs");
    suchThatClauseToken.relRef = "Modifies";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;
    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    // while synonym as second argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::make_pair("a", "w");
    suchThatClauseToken.relRef = "Modifies";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;
    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    // procedure synonym as second argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::make_pair("a", "p");
    suchThatClauseToken.relRef = "Modifies";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;
    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    // call synonym as second argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::make_pair("a", "c");
    suchThatClauseToken.relRef = "Modifies";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;
    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    // stmt synonym as second argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::make_pair("a", "s");
    suchThatClauseToken.relRef = "Modifies";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;
    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    // read synonym as second argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::make_pair("a", "r");
    suchThatClauseToken.relRef = "Modifies";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;
    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    // constant synonym as second argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::make_pair("a", "con");
    suchThatClauseToken.relRef = "Modifies";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;
    REQUIRE_THROWS(validator.checkForSemantics(queryToken));
}

TEST_CASE ("QP SEMANTIC VALIDATOR: PATTERN CHECK SYNONYM") {
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
    queryToken.selectClauseToken = "s";

    // valid synonym
    PatternToken patternToken = PatternToken();
    std::pair<std::string, std::string> arguments = std::make_pair("_", "_");
    patternToken.synonym = "a";
    patternToken.arguments = &arguments;
    std::vector<PatternToken> patternTokens = std::vector<PatternToken>({patternToken});
    queryToken.patternTokens = &patternTokens;
    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // invalid synonym that does not exit in declarations
    patternToken = PatternToken();
    arguments = std::make_pair("_", "_");
    patternToken.synonym = "unknown";
    patternToken.arguments = &arguments;
    patternTokens = std::vector<PatternToken>({patternToken});
    queryToken.patternTokens = &patternTokens;
    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    // synonym that is not an assign statement
    patternToken = PatternToken();
    arguments = std::make_pair("_", "_");
    patternToken.synonym = "c";
    patternToken.arguments = &arguments;
    patternTokens = std::vector<PatternToken>({patternToken});
    queryToken.patternTokens = &patternTokens;
    REQUIRE_THROWS(validator.checkForSemantics(queryToken));
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
    queryToken.selectClauseToken = "s";

    SuchThatClauseToken suchThatClauseToken = SuchThatClauseToken();
    std::pair<std::string, std::string> arguments = std::make_pair("a", "v");
    suchThatClauseToken.relRef = "Modifies";
    suchThatClauseToken.arguments = &arguments;
    std::vector<SuchThatClauseToken> suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;

    PatternToken patternToken = PatternToken();
    std::pair<std::string, std::string> patternArguments = std::make_pair("_", "_");
    patternToken.synonym = "a";
    patternToken.arguments = &patternArguments;
    std::vector<PatternToken> patternTokens = std::vector<PatternToken>({patternToken});
    queryToken.patternTokens = &patternTokens;
    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));
}