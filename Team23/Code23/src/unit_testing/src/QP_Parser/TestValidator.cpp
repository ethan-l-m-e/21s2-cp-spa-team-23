#include "catch.hpp"
#include "QP_Parser/Validator.h"

#include <vector>
#include <map>
#include <utility>

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

TEST_CASE ("QP SYNTACTIC VALIDATOR: RANDOM SPACES AND TABS") {
    Validator validator = Validator();

    // multiple spaces between design entity and declaration
    std::string query = "assign        a; stmt s; Select a such that Follows(3, 2)";
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // tab between design entity and declaration
    query = "assign\ta; stmt s; Select a such that Follows(3, 2)";
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // tab and spaces between design entity and declaration
    query = "assign\t   a; stmt s; Select a such that Follows(3, 2)";
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // no space between 2 declarations
    query = "assign a,a2; stmt s; Select a such that Follows(3, 2)";
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // spaces between 2 declarations of same design entity
    query = "assign a,     a2; stmt s; Select a such that Follows(3, 2)";
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // spaces between declarations of different design entities
    query = "assign a;     stmt s; Select a such that Follows(3, 2)";
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // tab between declarations of different design entities
    query = "assign a;\tstmt s; Select a such that Follows(3, 2)";
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // tab and spaces between declarations of different design entities
    query = "assign a;\t     stmt s; Select a such that Follows(3, 2)";
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // no space between 2 design entities declarations
    query = "assign a;stmt s; Select a such that Follows(3, 2)";
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // spaces between declarations and Select clause
    query = "assign a; stmt s;         Select a such that Follows(3, 2)";
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // tab between declarations and Select clause
    query = "assign a; stmt s;\tSelect a such that Follows(3, 2)";
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // tab and spaces between declarations and Select clause
    query = "assign a; stmt s;\t      Select a such that Follows(3, 2)";
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // no tab and spaces between declarations and Select clause
    query = "assign a; stmt s;Select a such that Follows(3, 2)";
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // spaces between Select clause and synonym
    query = "assign a; stmt s; Select     a such that Follows(3, 2)";
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // tab between Select clause and synonym
    query = "assign a; stmt s; Select\ta such that Follows(3, 2)";
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // tab and spaces between Select clause and synonym
    query = "assign a; stmt s; Select\t     a such that Follows(3, 2)";
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // spaces between synonym and such
    query = "assign a; stmt s; Select a      such that Follows(3, 2)";
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // tab between synonym and such
    query = "assign a; stmt s; Select a\tsuch that Follows(3, 2)";
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // tab and spaces between synonym and such
    query = "assign a; stmt s; Select a\t       such that Follows(3, 2)";
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // spaces between such that
    query = "assign a; stmt s; Select a such      that Follows(3, 2)";
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // tab between such that
    query = "assign a; stmt s; Select a such\tthat Follows(3, 2)";
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // spaces and tab between such that
    query = "assign a; stmt s; Select a such\t      that Follows(3, 2)";
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // spaces between such that and Relationship
    query = "assign a; stmt s; Select a such that      Follows(3, 2)";
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // tab between such that and Relationship
    query = "assign a; stmt s; Select a such that\tFollows(3, 2)";
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // tab and spaces between such that and Relationship
    query = "assign a; stmt s; Select a such that\t    Follows(3, 2)";
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // spaces between RelRef and (
    query = "assign a; stmt s; Select a such that Follows    (3, 2)";
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // tab between RelRef and (
    query = "assign a; stmt s; Select a such that Follows\t(3, 2)";
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // tab and spaces between RelRef and (
    query = "assign a; stmt s; Select a such that Follows\t    (3, 2)";
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // spaces between such that clause ( and first argument
    query = "assign a; stmt s; Select a such that Follows(     3, 2)";
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // tab between such that clause ( and first argument
    query = "assign a; stmt s; Select a such that Follows(\t3, 2)";
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // tab and spaces between such that clause ( and first argument
    query = "assign a; stmt s; Select a such that Follows(\t    3, 2)";
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // spaces between such that clause first argument and comma
    query = "assign a; stmt s; Select a such that Follows(3    , 2)";
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // tab between such that clause first argument and comma
    query = "assign a; stmt s; Select a such that Follows(3\t, 2)";
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // tab and spaces between such that clause first argument and comma
    query = "assign a; stmt s; Select a such that Follows(3\t    , 2)";
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // no tab and spaces between such that clause comma and second argument
    query = "assign a; stmt s; Select a such that Follows(3,2)";
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // spaces between such that clause comma and second argument
    query = "assign a; stmt s; Select a such that Follows(3,    2)";
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // tab between such that clause comma and second argument
    query = "assign a; stmt s; Select a such that Follows(3,\t2)";
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // spaces and tab and spaces between such that clause comma and second argument
    query = "assign a; stmt s; Select a such that Follows(3,\t      2)";
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // spaces between such that clause second argument and closing bracket
    query = "assign a; stmt s; Select a such that Follows(3, 2    )";
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // tab between such that clause second argument and closing bracket
    query = "assign a; stmt s; Select a such that Follows(3, 2\t)";
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // tab and spaces between such that clause second argument and closing bracket
    query = "assign a; stmt s; Select a such that Follows(3, 2\t     )";
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // no space between such that clause and pattern
    query = "assign a; stmt s; Select a such that Follows(3, 2)pattern a (_, _)";
    REQUIRE_THROWS(validator.validateQueryStructure(query));

    // spaces between such that clause and pattern
    query = "assign a; stmt s; Select a such that Follows(3, 2)      pattern a (_, _)";
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // tab between such that clause and pattern
    query = "assign a; stmt s; Select a such that Follows(3, 2)\tpattern a (_, _)";
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // tab and spaces between such that clause and pattern
    query = "assign a; stmt s; Select a such that Follows(3, 2)\t       pattern a (_, _)";
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // spaces between pattern and syn-assign
    query = "assign a; stmt s; Select a such that Follows(3, 2) pattern      a (_, _)";
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // tab between pattern and syn-assign
    query = "assign a; stmt s; Select a such that Follows(3, 2) pattern\ta (_, _)";
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // tab and spaces between pattern and syn-assign
    query = "assign a; stmt s; Select a such that Follows(3, 2) pattern\t    a (_, _)";
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // multiple tabs and spaces between pattern and syn-assign
    query = "assign a; stmt s; Select a such that Follows(3, 2) pattern\t\t\t    a (_, _)";
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // spaces between syn-assign and opening bracket
    query = "assign a; stmt s; Select a such that Follows(3, 2) pattern a     (_, _)";
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // tab between syn-assign and opening bracket
    query = "assign a; stmt s; Select a such that Follows(3, 2) pattern a\t(_, _)";
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // tab and spaces between syn-assign and opening bracket
    query = "assign a; stmt s; Select a such that Follows(3, 2) pattern a\t     (_, _)";
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // no tab and spaces between syn-assign and opening bracket
    query = "assign a; stmt s; Select a such that Follows(3, 2) pattern a(_, _)";
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // spaces between opening bracket and first argument
    query = "assign a; stmt s; Select a such that Follows(3, 2) pattern a (       _, _)";
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // tab between opening bracket and first argument
    query = "assign a; stmt s; Select a such that Follows(3, 2) pattern a (\t_, _)";
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // tab and spaces between opening bracket and first argument
    query = "assign a; stmt s; Select a such that Follows(3, 2) pattern a (\t        _, _)";
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // spaces between first argument and comma
    query = "assign a; stmt s; Select a such that Follows(3, 2) pattern a (_     , _)";
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // tab between first argument and comma
    query = "assign a; stmt s; Select a such that Follows(3, 2) pattern a (_\t, _)";
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // tab and spaces between first argument and comma
    query = "assign a; stmt s; Select a such that Follows(3, 2) pattern a (_\t        , _)";
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // spaces between comma and second argument
    query = "assign a; stmt s; Select a such that Follows(3, 2) pattern a (_,     _)";
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // tab between comma and second argument
    query = "assign a; stmt s; Select a such that Follows(3, 2) pattern a (_,\t_)";
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // tab and spaces between comma and second argument
    query = "assign a; stmt s; Select a such that Follows(3, 2) pattern a (_,\t       _)";
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // no tab and spaces between comma and second argument
    query = "assign a; stmt s; Select a such that Follows(3, 2) pattern a (_,_)";
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // spaces between second argument and closing bracket
    query = "assign a; stmt s; Select a such that Follows(3, 2) pattern a (_,_    )";
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // tab between second argument and closing bracket
    query = "assign a; stmt s; Select a such that Follows(3, 2) pattern a (_,_\t)";
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // tab and spaces between second argument and closing bracket
    query = "assign a; stmt s; Select a such that Follows(3, 2) pattern a (_,_\t      )";
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // tab and spaces at the end
    query = "assign a; stmt s; Select a such that Follows(3, 2) pattern a (_, _)      \t\t\t";
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // tab and spaces at the end
    query = "assign a; stmt s; Select a      \t\t\t";
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // tab and spaces at the end
    query = "assign a; stmt s; Select a such that Follows(3, 2)     \t\t\t";
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // tab and spaces at the end
    query = "assign a; stmt s; Select a pattern a (_, _)     \t\t\t";
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // missed spacing
    query = "assigna; stmt s; Select a such that Follows(3, 2) pattern a (_, _)";
    REQUIRE_THROWS(validator.validateQueryStructure(query));

    // missed spacing
    query = "assign a; stmts; Select a such that Follows(3, 2) pattern a (_, _)";
    REQUIRE_THROWS(validator.validateQueryStructure(query));

    // missed spacing
    query = "assign a; stmt s; Selecta such that Follows(3, 2) pattern a (_, _)";
    REQUIRE_THROWS(validator.validateQueryStructure(query));

    // missed spacing
    query = "assign a; stmt s; Select asuch that Follows(3, 2) pattern a (_, _)";
    REQUIRE_THROWS(validator.validateQueryStructure(query));

    // missed spacing
    query = "assign a; stmt s; Select a suchthat Follows(3, 2) pattern a (_, _)";
    REQUIRE_THROWS(validator.validateQueryStructure(query));

    // missed spacing
    query = "assign a; stmt s; Select a such thatFollows(3, 2) pattern a (_, _)";
    REQUIRE_THROWS(validator.validateQueryStructure(query));

    // missed spacing
    query = "assign a; stmt s; Select a such that Follows(3, 2)pattern a (_, _)";
    REQUIRE_THROWS(validator.validateQueryStructure(query));

    // missed spacing
    query = "assign a; stmt s; Select a such that Follows(3, 2) patterna (_, _)";
    REQUIRE_THROWS(validator.validateQueryStructure(query));
}

TEST_CASE ("QP SYNTACTIC VALIDATOR: INCORRECT NEW LINES") {
    Validator validator = Validator();

    // newline in the middle of a design entity
    std::string query = "assign a; st\nmt s; Select a such that Follows(3, 2)";
    REQUIRE_THROWS(validator.validateQueryStructure(query));

    // newline in the middle of Select
    query = "assign a; stmt s; Sel\nect a such that Follows(3, 2)";
    REQUIRE_THROWS(validator.validateQueryStructure(query));

    // newline in the middle of a relationship
    query = "assign a; stmt s; Select a such that Foll\nows(3, 2)";
    REQUIRE_THROWS(validator.validateQueryStructure(query));

    // newline in the middle of pattern
    query = "assign a; stmt s; Select a such that Follows(3, 2) pat\ntern a(2, 3)";
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
    queryToken.selectClauseTokens = new std::vector<std::string>({"v"});

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
    queryToken.selectClauseTokens = new std::vector<std::string>({"s"});

    // Integer as first argument
    SuchThatClauseToken suchThatClauseToken = SuchThatClauseToken();
    std::vector<std::string> arguments = std::vector<std::string>({"3", "2"});
    suchThatClauseToken.relRef = "Follows";
    suchThatClauseToken.arguments = &arguments;
    std::vector<SuchThatClauseToken> suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;

    Validator validator = Validator();
    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // Wildcard as first argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::vector<std::string>({"_", "2"});
    suchThatClauseToken.relRef = "Follows";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;

    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // stmt synonym as first argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::vector<std::string>({"s", "2"});
    suchThatClauseToken.relRef = "Follows";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;

    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // read synonym as first argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::vector<std::string>({"r", "2"});
    suchThatClauseToken.relRef = "Follows";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;

    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // print synonym as first argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::vector<std::string>({"pn", "2"});
    suchThatClauseToken.relRef = "Follows";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;

    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // assign synonym as first argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::vector<std::string>({"a", "2"});
    suchThatClauseToken.relRef = "Follows";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;

    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // call synonym as first argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::vector<std::string>({"c", "2"});
    suchThatClauseToken.relRef = "Follows";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;

    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // while synonym as first argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::vector<std::string>({"w", "2"});
    suchThatClauseToken.relRef = "Follows";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;

    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // while synonym as first argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::vector<std::string>({"ifs", "2"});
    suchThatClauseToken.relRef = "Follows";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;

    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // variable synonym as first argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::vector<std::string>({"v", "2"});
    suchThatClauseToken.relRef = "Follows";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;

    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    // constant synonym as first argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::vector<std::string>({"con", "2"});
    suchThatClauseToken.relRef = "Follows";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;

    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    // procedure synonym as first argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::vector<std::string>({"p", "2"});
    suchThatClauseToken.relRef = "Follows";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;

    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    // Ident as first argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::vector<std::string>({"\"x\"", "2"});
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
    queryToken.selectClauseTokens = new std::vector<std::string>({"s"});

    // Integer as second argument
    SuchThatClauseToken suchThatClauseToken = SuchThatClauseToken();
    std::vector<std::string> arguments = std::vector<std::string>({"3", "2"});
    suchThatClauseToken.relRef = "Follows";
    suchThatClauseToken.arguments = &arguments;
    std::vector<SuchThatClauseToken> suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;

    Validator validator = Validator();
    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // Wildcard as second argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::vector<std::string>({"3", "_"});
    suchThatClauseToken.relRef = "Follows";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;

    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // stmt synonym as second argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::vector<std::string>({"3", "s"});
    suchThatClauseToken.relRef = "Follows";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;

    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // read synonym as second argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::vector<std::string>({"3", "r"});
    suchThatClauseToken.relRef = "Follows";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;

    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // print synonym as second argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::vector<std::string>({"3", "pn"});
    suchThatClauseToken.relRef = "Follows";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;

    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // assign synonym as second argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::vector<std::string>({"3", "a"});
    suchThatClauseToken.relRef = "Follows";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;

    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // call synonym as second argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::vector<std::string>({"3", "c"});
    suchThatClauseToken.relRef = "Follows";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;

    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // while synonym as second argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::vector<std::string>({"3", "w"});
    suchThatClauseToken.relRef = "Follows";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;

    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // while synonym as second argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::vector<std::string>({"3", "ifs"});
    suchThatClauseToken.relRef = "Follows";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;

    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // variable synonym as second argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::vector<std::string>({"3", "v"});
    suchThatClauseToken.relRef = "Follows";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;

    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    // constant synonym as second argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::vector<std::string>({"3", "con"});
    suchThatClauseToken.relRef = "Follows";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;

    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    // procedure synonym as second argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::vector<std::string>({"3", "p"});
    suchThatClauseToken.relRef = "Follows";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;

    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    // ident as second argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::vector<std::string>({"3", "\"x\""});
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
    queryToken.selectClauseTokens = new std::vector<std::string>({"s"});

    // Integer as first argument
    SuchThatClauseToken suchThatClauseToken = SuchThatClauseToken();
    std::vector<std::string> arguments = std::vector<std::string>({"3", "2"});
    suchThatClauseToken.relRef = "Follows*";
    suchThatClauseToken.arguments = &arguments;
    std::vector<SuchThatClauseToken> suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;

    Validator validator = Validator();
    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // Wildcard as first argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::vector<std::string>({"_", "2"});
    suchThatClauseToken.relRef = "Follows*";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;

    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // stmt synonym as first argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::vector<std::string>({"s", "2"});
    suchThatClauseToken.relRef = "Follows*";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;

    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // read synonym as first argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::vector<std::string>({"r", "2"});
    suchThatClauseToken.relRef = "Follows*";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;

    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // print synonym as first argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::vector<std::string>({"pn", "2"});
    suchThatClauseToken.relRef = "Follows*";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;

    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // assign synonym as first argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::vector<std::string>({"a", "2"});
    suchThatClauseToken.relRef = "Follows*";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;

    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // call synonym as first argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::vector<std::string>({"c", "2"});
    suchThatClauseToken.relRef = "Follows*";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;

    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // while synonym as first argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::vector<std::string>({"w", "2"});
    suchThatClauseToken.relRef = "Follows*";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;

    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // while synonym as first argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::vector<std::string>({"ifs", "2"});
    suchThatClauseToken.relRef = "Follows*";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;

    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // variable synonym as first argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::vector<std::string>({"v", "2"});
    suchThatClauseToken.relRef = "Follows*";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;

    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    // constant synonym as first argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::vector<std::string>({"con", "2"});
    suchThatClauseToken.relRef = "Follows*";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;

    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    // procedure synonym as first argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::vector<std::string>({"p", "2"});
    suchThatClauseToken.relRef = "Follows*";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;

    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    // ident as first argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::vector<std::string>({"\"x\"", "2"});
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
    queryToken.selectClauseTokens = new std::vector<std::string>({"s"});

    // Integer as second argument
    SuchThatClauseToken suchThatClauseToken = SuchThatClauseToken();
    std::vector<std::string> arguments = std::vector<std::string>({"3", "2"});
    suchThatClauseToken.relRef = "Follows*";
    suchThatClauseToken.arguments = &arguments;
    std::vector<SuchThatClauseToken> suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;

    Validator validator = Validator();
    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // Wildcard as second argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::vector<std::string>({"3", "_"});
    suchThatClauseToken.relRef = "Follows*";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;

    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // stmt synonym as second argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::vector<std::string>({"3", "s"});
    suchThatClauseToken.relRef = "Follows*";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;

    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // read synonym as second argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::vector<std::string>({"3", "r"});
    suchThatClauseToken.relRef = "Follows*";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;

    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // print synonym as second argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::vector<std::string>({"3", "pn"});
    suchThatClauseToken.relRef = "Follows*";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;

    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // assign synonym as second argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::vector<std::string>({"3", "a"});
    suchThatClauseToken.relRef = "Follows*";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;

    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // call synonym as second argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::vector<std::string>({"3", "c"});
    suchThatClauseToken.relRef = "Follows*";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;

    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // while synonym as second argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::vector<std::string>({"3", "w"});
    suchThatClauseToken.relRef = "Follows*";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;

    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // while synonym as second argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::vector<std::string>({"3", "ifs"});
    suchThatClauseToken.relRef = "Follows*";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;

    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // variable synonym as second argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::vector<std::string>({"3", "v"});
    suchThatClauseToken.relRef = "Follows*";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;

    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    // constant synonym as second argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::vector<std::string>({"3", "con"});
    suchThatClauseToken.relRef = "Follows*";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;

    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    // procedure synonym as second argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::vector<std::string>({"3", "p"});
    suchThatClauseToken.relRef = "Follows*";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;

    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    // ident as second argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::vector<std::string>({"3", "\"x\""});
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
    queryToken.selectClauseTokens = new std::vector<std::string>({"s"});

    // Integer as first argument
    SuchThatClauseToken suchThatClauseToken = SuchThatClauseToken();
    std::vector<std::string> arguments = std::vector<std::string>({"3", "2"});
    suchThatClauseToken.relRef = "Parent";
    suchThatClauseToken.arguments = &arguments;
    std::vector<SuchThatClauseToken> suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;

    Validator validator = Validator();
    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // Wildcard as first argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::vector<std::string>({"_", "2"});
    suchThatClauseToken.relRef = "Parent";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;

    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // stmt synonym as first argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::vector<std::string>({"s", "2"});
    suchThatClauseToken.relRef = "Parent";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;

    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // read synonym as first argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::vector<std::string>({"r", "2"});
    suchThatClauseToken.relRef = "Parent";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;

    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // print synonym as first argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::vector<std::string>({"pn", "2"});
    suchThatClauseToken.relRef = "Parent";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;

    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // assign synonym as first argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::vector<std::string>({"a", "2"});
    suchThatClauseToken.relRef = "Parent";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;

    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // call synonym as first argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::vector<std::string>({"c", "2"});
    suchThatClauseToken.relRef = "Parent";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;

    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // while synonym as first argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::vector<std::string>({"w", "2"});
    suchThatClauseToken.relRef = "Parent";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;

    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // while synonym as first argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::vector<std::string>({"ifs", "2"});
    suchThatClauseToken.relRef = "Parent";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;

    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // variable synonym as first argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::vector<std::string>({"v", "2"});
    suchThatClauseToken.relRef = "Parent";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;

    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    // constant synonym as first argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::vector<std::string>({"con", "2"});
    suchThatClauseToken.relRef = "Parent";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;

    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    // procedure synonym as first argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::vector<std::string>({"p", "2"});
    suchThatClauseToken.relRef = "Parent";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;

    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    // ident as first argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::vector<std::string>({"\"x\"", "2"});
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
    queryToken.selectClauseTokens = new std::vector<std::string>({"s"});

    // Integer as second argument
    SuchThatClauseToken suchThatClauseToken = SuchThatClauseToken();
    std::vector<std::string> arguments = std::vector<std::string>({"3", "2"});
    suchThatClauseToken.relRef = "Parent";
    suchThatClauseToken.arguments = &arguments;
    std::vector<SuchThatClauseToken> suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;

    Validator validator = Validator();
    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // Wildcard as second argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::vector<std::string>({"3", "_"});
    suchThatClauseToken.relRef = "Parent";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;

    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // stmt synonym as second argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::vector<std::string>({"3", "s"});
    suchThatClauseToken.relRef = "Parent";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;

    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // read synonym as second argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::vector<std::string>({"3", "r"});
    suchThatClauseToken.relRef = "Parent";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;

    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // print synonym as second argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::vector<std::string>({"3", "pn"});
    suchThatClauseToken.relRef = "Parent";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;

    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // assign synonym as second argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::vector<std::string>({"3", "a"});
    suchThatClauseToken.relRef = "Parent";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;

    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // call synonym as second argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::vector<std::string>({"3", "c"});
    suchThatClauseToken.relRef = "Parent";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;

    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // while synonym as second argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::vector<std::string>({"3", "w"});
    suchThatClauseToken.relRef = "Parent";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;

    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // while synonym as second argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::vector<std::string>({"3", "ifs"});
    suchThatClauseToken.relRef = "Parent";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;

    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // variable synonym as second argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::vector<std::string>({"3", "v"});
    suchThatClauseToken.relRef = "Parent";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;

    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    // constant synonym as second argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::vector<std::string>({"3", "con"});
    suchThatClauseToken.relRef = "Parent";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;

    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    // procedure synonym as second argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::vector<std::string>({"3", "p"});
    suchThatClauseToken.relRef = "Parent";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;

    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    // ident as second argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::vector<std::string>({"3", "\"x\""});
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
    queryToken.selectClauseTokens = new std::vector<std::string>({"s"});

    // Integer as first argument
    SuchThatClauseToken suchThatClauseToken = SuchThatClauseToken();
    std::vector<std::string> arguments = std::vector<std::string>({"3", "2"});
    suchThatClauseToken.relRef = "Parent*";
    suchThatClauseToken.arguments = &arguments;
    std::vector<SuchThatClauseToken> suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;

    Validator validator = Validator();
    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // Wildcard as first argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::vector<std::string>({"_", "2"});
    suchThatClauseToken.relRef = "Parent*";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;

    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // stmt synonym as first argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::vector<std::string>({"s", "2"});
    suchThatClauseToken.relRef = "Parent*";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;

    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // read synonym as first argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::vector<std::string>({"r", "2"});
    suchThatClauseToken.relRef = "Parent*";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;

    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // print synonym as first argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::vector<std::string>({"pn", "2"});
    suchThatClauseToken.relRef = "Parent*";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;

    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // assign synonym as first argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::vector<std::string>({"a", "2"});
    suchThatClauseToken.relRef = "Parent*";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;

    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // call synonym as first argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::vector<std::string>({"c", "2"});
    suchThatClauseToken.relRef = "Parent*";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;

    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // while synonym as first argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::vector<std::string>({"w", "2"});
    suchThatClauseToken.relRef = "Parent*";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;

    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // while synonym as first argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::vector<std::string>({"ifs", "2"});
    suchThatClauseToken.relRef = "Parent*";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;

    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // variable synonym as first argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::vector<std::string>({"v", "2"});
    suchThatClauseToken.relRef = "Parent*";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;

    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    // constant synonym as first argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::vector<std::string>({"con", "2"});
    suchThatClauseToken.relRef = "Parent*";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;

    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    // procedure synonym as first argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::vector<std::string>({"p", "2"});
    suchThatClauseToken.relRef = "Parent*";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;

    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    // ident as first argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::vector<std::string>({"\"x\"", "2"});
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
    queryToken.selectClauseTokens = new std::vector<std::string>({"s"});

    // Integer as second argument
    SuchThatClauseToken suchThatClauseToken = SuchThatClauseToken();
    std::vector<std::string> arguments = std::vector<std::string>({"3", "2"});
    suchThatClauseToken.relRef = "Parent*";
    suchThatClauseToken.arguments = &arguments;
    std::vector<SuchThatClauseToken> suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;

    Validator validator = Validator();
    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // Wildcard as second argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::vector<std::string>({"3", "_"});
    suchThatClauseToken.relRef = "Parent*";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;

    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // stmt synonym as second argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::vector<std::string>({"3", "s"});
    suchThatClauseToken.relRef = "Parent*";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;

    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // read synonym as second argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::vector<std::string>({"3", "r"});
    suchThatClauseToken.relRef = "Parent*";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;

    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // print synonym as second argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::vector<std::string>({"3", "pn"});
    suchThatClauseToken.relRef = "Parent*";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;

    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // assign synonym as second argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::vector<std::string>({"3", "a"});
    suchThatClauseToken.relRef = "Parent*";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;

    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // call synonym as second argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::vector<std::string>({"3", "c"});
    suchThatClauseToken.relRef = "Parent*";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;

    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // while synonym as second argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::vector<std::string>({"3", "w"});
    suchThatClauseToken.relRef = "Parent*";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;

    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // while synonym as second argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::vector<std::string>({"3", "ifs"});
    suchThatClauseToken.relRef = "Parent*";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;

    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // variable synonym as second argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::vector<std::string>({"3", "v"});
    suchThatClauseToken.relRef = "Parent*";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;

    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    // constant synonym as second argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::vector<std::string>({"3", "con"});
    suchThatClauseToken.relRef = "Parent*";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;

    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    // procedure synonym as second argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::vector<std::string>({"3", "p"});
    suchThatClauseToken.relRef = "Parent*";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;

    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    // ident as second argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::vector<std::string>({"3", "\"x\""});
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
    queryToken.selectClauseTokens = new std::vector<std::string>({"s"});

    // IDENT as first argument
    SuchThatClauseToken suchThatClauseToken = SuchThatClauseToken();
    std::vector<std::string> arguments = std::vector<std::string>({"\"x\"", "_"});
    suchThatClauseToken.relRef = "Uses";
    suchThatClauseToken.arguments = &arguments;
    std::vector<SuchThatClauseToken> suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;
    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // assign synonym as first argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::vector<std::string>({"a", "_"});
    suchThatClauseToken.relRef = "Uses";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;
    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // print synonym as first argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::vector<std::string>({"pn", "_"});
    suchThatClauseToken.relRef = "Uses";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;
    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // if synonym as first argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::vector<std::string>({"ifs", "_"});
    suchThatClauseToken.relRef = "Uses";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;
    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // while synonym as first argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::vector<std::string>({"w", "_"});
    suchThatClauseToken.relRef = "Uses";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;
    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // procedure synonym as first argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::vector<std::string>({"p", "_"});
    suchThatClauseToken.relRef = "Uses";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;
    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // call synonym as first argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::vector<std::string>({"c", "_"});
    suchThatClauseToken.relRef = "Uses";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;
    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // stmt synonym as first argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::vector<std::string>({"s", "_"});
    suchThatClauseToken.relRef = "Uses";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;
    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // read synonym as first argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::vector<std::string>({"r", "_"});
    suchThatClauseToken.relRef = "Uses";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;
    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    // variable synonym as first argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::vector<std::string>({"v", "_"});
    suchThatClauseToken.relRef = "Uses";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;
    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    // constant synonym as first argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::vector<std::string>({"con", "_"});
    suchThatClauseToken.relRef = "Uses";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;
    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    // wildcard as first argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::vector<std::string>({"_", "_"});
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
    queryToken.selectClauseTokens = new std::vector<std::string>({"s"});

    // variable synonym as second argument
    SuchThatClauseToken suchThatClauseToken = SuchThatClauseToken();
    std::vector<std::string> arguments = std::vector<std::string>({"a", "v"});
    suchThatClauseToken.relRef = "Uses";
    suchThatClauseToken.arguments = &arguments;
    std::vector<SuchThatClauseToken> suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;
    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // ident as second argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::vector<std::string>({"a", "\"x\""});
    suchThatClauseToken.relRef = "Uses";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;
    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // wildcard as second argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::vector<std::string>({"a", "_"});
    suchThatClauseToken.relRef = "Uses";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;
    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // assign synonym as second argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::vector<std::string>({"a", "a"});
    suchThatClauseToken.relRef = "Uses";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;
    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    // print synonym as second argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::vector<std::string>({"a", "pn"});
    suchThatClauseToken.relRef = "Uses";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;
    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    // if synonym as second argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::vector<std::string>({"a", "ifs"});
    suchThatClauseToken.relRef = "Uses";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;
    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    // while synonym as second argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::vector<std::string>({"a", "w"});
    suchThatClauseToken.relRef = "Uses";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;
    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    // procedure synonym as second argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::vector<std::string>({"a", "p"});
    suchThatClauseToken.relRef = "Uses";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;
    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    // call synonym as second argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::vector<std::string>({"a", "c"});
    suchThatClauseToken.relRef = "Uses";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;
    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    // stmt synonym as second argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::vector<std::string>({"a", "s"});
    suchThatClauseToken.relRef = "Uses";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;
    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    // read synonym as second argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::vector<std::string>({"a", "r"});
    suchThatClauseToken.relRef = "Uses";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;
    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    // constant synonym as second argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::vector<std::string>({"a", "con"});
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
    queryToken.selectClauseTokens = new std::vector<std::string>({"s"});

    // IDENT as first argument
    SuchThatClauseToken suchThatClauseToken = SuchThatClauseToken();
    std::vector<std::string> arguments = std::vector<std::string>({"\"x\"", "_"});
    suchThatClauseToken.relRef = "Modifies";
    suchThatClauseToken.arguments = &arguments;
    std::vector<SuchThatClauseToken> suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;
    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // assign synonym as first argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::vector<std::string>({"a", "_"});
    suchThatClauseToken.relRef = "Modifies";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;
    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // read synonym as first argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::vector<std::string>({"r", "_"});
    suchThatClauseToken.relRef = "Modifies";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;
    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // if synonym as first argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::vector<std::string>({"ifs", "_"});
    suchThatClauseToken.relRef = "Modifies";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;
    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // while synonym as first argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::vector<std::string>({"w", "_"});
    suchThatClauseToken.relRef = "Modifies";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;
    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // procedure synonym as first argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::vector<std::string>({"p", "_"});
    suchThatClauseToken.relRef = "Modifies";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;
    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // call synonym as first argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::vector<std::string>({"c", "_"});
    suchThatClauseToken.relRef = "Modifies";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;
    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // stmt synonym as first argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::vector<std::string>({"s", "_"});
    suchThatClauseToken.relRef = "Modifies";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;
    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // print synonym as first argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::vector<std::string>({"pn", "_"});
    suchThatClauseToken.relRef = "Modifies";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;
    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    // variable synonym as first argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::vector<std::string>({"v", "_"});
    suchThatClauseToken.relRef = "Modifies";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;
    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    // constant synonym as first argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::vector<std::string>({"con", "_"});
    suchThatClauseToken.relRef = "Modifies";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;
    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    // wildcard as first argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::vector<std::string>({"_", "_"});
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
    queryToken.selectClauseTokens = new std::vector<std::string>({"s"});

    // variable synonym as second argument
    SuchThatClauseToken suchThatClauseToken = SuchThatClauseToken();
    std::vector<std::string> arguments = std::vector<std::string>({"a", "v"});
    suchThatClauseToken.relRef = "Modifies";
    suchThatClauseToken.arguments = &arguments;
    std::vector<SuchThatClauseToken> suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;
    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // ident as second argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::vector<std::string>({"a", "\"x\""});
    suchThatClauseToken.relRef = "Modifies";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;
    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // wildcard as second argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::vector<std::string>({"a", "_"});
    suchThatClauseToken.relRef = "Modifies";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;
    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // assign synonym as second argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::vector<std::string>({"a", "a"});
    suchThatClauseToken.relRef = "Modifies";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;
    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    // print synonym as second argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::vector<std::string>({"a", "pn"});
    suchThatClauseToken.relRef = "Modifies";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;
    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    // if synonym as second argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::vector<std::string>({"a", "ifs"});
    suchThatClauseToken.relRef = "Modifies";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;
    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    // while synonym as second argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::vector<std::string>({"a", "w"});
    suchThatClauseToken.relRef = "Modifies";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;
    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    // procedure synonym as second argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::vector<std::string>({"a", "p"});
    suchThatClauseToken.relRef = "Modifies";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;
    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    // call synonym as second argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::vector<std::string>({"a", "c"});
    suchThatClauseToken.relRef = "Modifies";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;
    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    // stmt synonym as second argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::vector<std::string>({"a", "s"});
    suchThatClauseToken.relRef = "Modifies";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;
    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    // read synonym as second argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::vector<std::string>({"a", "r"});
    suchThatClauseToken.relRef = "Modifies";
    suchThatClauseToken.arguments = &arguments;
    suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;
    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    // constant synonym as second argument
    suchThatClauseToken = SuchThatClauseToken();
    arguments = std::vector<std::string>({"a", "con"});
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
    queryToken.selectClauseTokens = new std::vector<std::string>({"s"});

    // valid synonym
    PatternToken patternToken = PatternToken();
    std::vector<std::string> arguments = std::vector<std::string>({"_", "_"});
    patternToken.synonym = "a";
    patternToken.arguments = &arguments;
    std::vector<PatternToken> patternTokens = std::vector<PatternToken>({patternToken});
    queryToken.patternTokens = &patternTokens;
    REQUIRE_NOTHROW(validator.checkForSemantics(queryToken));

    // invalid synonym that does not exit in declarations
    patternToken = PatternToken();
    arguments = std::vector<std::string>({"_", "_"});
    patternToken.synonym = "unknown";
    patternToken.arguments = &arguments;
    patternTokens = std::vector<PatternToken>({patternToken});
    queryToken.patternTokens = &patternTokens;
    REQUIRE_THROWS(validator.checkForSemantics(queryToken));

    // synonym that is not an assign statement
    patternToken = PatternToken();
    arguments = std::vector<std::string>({"_", "_"});
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
    queryToken.selectClauseTokens = new std::vector<std::string>({"s"});

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

    // variable synonym as second argument
    SuchThatClauseToken suchThatClauseToken = SuchThatClauseToken();
    std::vector<std::string> arguments = std::vector<std::string>({"s1", "s"});
    suchThatClauseToken.relRef = "Follows";
    suchThatClauseToken.arguments = &arguments;
    std::vector<SuchThatClauseToken> suchThatClauseTokens = std::vector<SuchThatClauseToken>({suchThatClauseToken});
    queryToken.suchThatClauseTokens = &suchThatClauseTokens;
    REQUIRE_THROWS(validator.checkForSemantics(queryToken));
}