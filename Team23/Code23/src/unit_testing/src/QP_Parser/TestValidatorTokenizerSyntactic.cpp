#include "catch.hpp"
#include "QP_Parser/Validator.h"

#include <utility>

using namespace qp;

// Check if validator works for declarations
TEST_CASE ("QP SYNTACTIC VALIDATOR: CHECK DECLARATIONS") {
    Validator validator = Validator();

    // Single Char declaration
    std::string query = "variable v1; Select v";
    query = Tokenizer::lexicalTokens(query);
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // Double char declaration
    query = "variable va; Select va";
    query = Tokenizer::lexicalTokens(query);
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // Char + Int declaration
    query = "variable v1; Select v1";
    query = Tokenizer::lexicalTokens(query);
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // All possible declarations
    query = "stmt s; read r; print pn; call c; while w; if ifs; assign a; constant con; procedure p; Select v1";
    query = Tokenizer::lexicalTokens(query);
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // Double declarations
    query = "variable v; stmt s; Select v1";
    query = Tokenizer::lexicalTokens(query);
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // Triple Declarations
    query = "variable v; stmt s; procedure p; Select v1";
    query = Tokenizer::lexicalTokens(query);
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // Multiple declaration sof same design entity
    query = "variable v1, v2, v3; Select v1";
    query = Tokenizer::lexicalTokens(query);
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // Multiple declarations of same design entities
    query = "variable v1, v2, v3; procedure p1, p2; Select v1";
    query = Tokenizer::lexicalTokens(query);
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // Synonym name same as design entities
    query = "stmt stmt; read read; print print; call call; while while; if if; assign assign; variable variable; constant constant; procedure procedure; Select v1";
    query = Tokenizer::lexicalTokens(query);
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // Synonym name same as design entity - stmt read
    query = "stmt read; Select v1";
    query = Tokenizer::lexicalTokens(query);
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // Synonym name is Select
    query = "stmt Select; Select v1";
    query = Tokenizer::lexicalTokens(query);
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // Synonym name is pattern
    query = "stmt pattern; Select v1";
    query = Tokenizer::lexicalTokens(query);
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));
}

TEST_CASE ("QP SYNTACTIC VALIDATOR: INVALID DECLARATIONS") {
    Validator validator = Validator();

    // integer as declaration synonym
    std::string query = "variable 1; \n Select v1";
    query = Tokenizer::lexicalTokens(query);
    REQUIRE_THROWS(validator.validateQueryStructure(query));

    // int-char as declaration name
    query = "variable 1v; \n Select v1";
    query = Tokenizer::lexicalTokens(query);
    REQUIRE_THROWS(validator.validateQueryStructure(query));

    // Invalid design entity
    query = "unknown v; \n Select v1";
    query = Tokenizer::lexicalTokens(query);
    REQUIRE_THROWS(validator.validateQueryStructure(query));

    // Misspelt design entity
    query = "varible v; \n Select v1";
    query = Tokenizer::lexicalTokens(query);
    REQUIRE_THROWS(validator.validateQueryStructure(query));

    // shortened version of design entity
    query = "var v; \n Select v1";
    query = Tokenizer::lexicalTokens(query);
    REQUIRE_THROWS(validator.validateQueryStructure(query));

    // Wrong caps design entity
    query = "Variable v; \n Select v1";
    query = Tokenizer::lexicalTokens(query);
    REQUIRE_THROWS(validator.validateQueryStructure(query));

    // Incorrect semicolon usage
    query = "variable v1; v2; \n Select v1";
    query = Tokenizer::lexicalTokens(query);
    REQUIRE_THROWS(validator.validateQueryStructure(query));

    // Incorrect comma usage
    query = "variable v1, stmt s; \n Select v1";
    query = Tokenizer::lexicalTokens(query);
    REQUIRE_THROWS(validator.validateQueryStructure(query));

    // Incorrect comma usage - 2
    query = "variable v1; stmt, s; \n Select v1";
    query = Tokenizer::lexicalTokens(query);
    REQUIRE_THROWS(validator.validateQueryStructure(query));
}

TEST_CASE ("QP SYNTACTIC VALIDATOR: VALID SELECT CLAUSE TESTS") {
    Validator validator = Validator();

    // Normal Select clause
    std::string query = "variable v; Select v";
    query = Tokenizer::lexicalTokens(query);
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // Select clause with synonym having an int
    query = "variable v; Select v2";
    query = Tokenizer::lexicalTokens(query);
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // Select clause with multi char synonym
    query = "variable v; Select var";
    query = Tokenizer::lexicalTokens(query);
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // Select clause with Select as synonym
    query = "variable v; Select Select";
    query = Tokenizer::lexicalTokens(query);
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // Select clause with 'with' as synonym
    query = "variable with; Select with";
    query = Tokenizer::lexicalTokens(query);
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // Select clause with 'and' as synonym
    query = "variable and; Select and";
    query = Tokenizer::lexicalTokens(query);
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // Select clause with 'Follows' as synonym
    query = "variable Follows; Select Follows";
    query = Tokenizer::lexicalTokens(query);
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // Select clause with 'BOOLEAN' as synonym
    query = "variable Follows; Select BOOLEAN";
    query = Tokenizer::lexicalTokens(query);
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // Select clause with tuple: single element
    query = "variable example; Select <example>";
    query = Tokenizer::lexicalTokens(query);
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // Select clause with tuple: Select as synonym name
    query = "variable Select; Select <Select>";
    query = Tokenizer::lexicalTokens(query);
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // Select clause with tuple: Select and with as synonym names
    query = "variable Select, with; Select <Select, with>";
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // Select clause with tuple: Attribute References
    query = "variable Select, with; Select <p.procName, s.stmt#, v.varName, c.value>";
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // Select clause with AttrRef - procName
    query = "procedure p; Select p.procName";
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // Select clause with AttrRef - varName
    query = "procedure p; Select p.varName";
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // Select clause with AttrRef - value
    query = "procedure p; Select p.value";
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // Select clause with AttrRef - stmt#
    query = "procedure p; Select p.stmt#";
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));
}

TEST_CASE ("QP SYNTACTIC VALIDATOR: INVALID SELECT CLAUSE QUERIES") {
    Validator validator = Validator();

    // Select clause with int as synonym
    std::string query = "variable v; \n Select 123";
    REQUIRE_THROWS(validator.validateQueryStructure(query));

    // Lower case select clause
    query = "variable v; \n select v1";
    REQUIRE_THROWS(validator.validateQueryStructure(query));

    // Misspelled select clause
    query = "variable v; \n Selec v1";
    REQUIRE_THROWS(validator.validateQueryStructure(query));

    // No select clause
    query = "variable v;";
    REQUIRE_THROWS(validator.validateQueryStructure(query));

    // Tuple: Invalid bracket
    query = "variable v; Select <example)";
    REQUIRE_THROWS(validator.validateQueryStructure(query));

    // Tuple: Invalid brackets
    query = "variable v; Select (example)";
    REQUIRE_THROWS(validator.validateQueryStructure(query));

    // Tuple: Invalid semicolon
    query = "procedure p1, p2; Select <p1; p2>";
    REQUIRE_THROWS(validator.validateQueryStructure(query));

    // Tuple: Invalid semicolon after synonym
    query = "procedure p1, p2; Select p1;";
    REQUIRE_THROWS(validator.validateQueryStructure(query));

    // Missing Select synonym
    query = "procedure p1, p2; Select such that Follows(s1, s2)";
    REQUIRE_THROWS(validator.validateQueryStructure(query));

    // Invalid synonym
    query = "procedure p1, p2; Select stmt#";
    REQUIRE_THROWS(validator.validateQueryStructure(query));
}

TEST_CASE ("QP SYNTACTIC VALIDATOR: VALID FOLLOWS CLAUSE QUERIES") {
    Validator validator = Validator();

    // Synonym First argument
    std::string query = "stmt s; Select s such that Follows(s, 3)";
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // Wildcard first argument
    query = "stmt s; Select s such that Follows(_, 3)";
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // Integer first argument
    query = "stmt s; Select s such that Follows(5, 3)";
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // Synonym second argument
    query = "stmt s; Select s such that Follows(3, s)";
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // Wildcard second argument
    query = "stmt s; Select s such that Follows(s, _)";
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // Integer Second argument
    query = "stmt s; Select s such that Follows(s, 3)";
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));
}

TEST_CASE ("QP SYNTACTIC VALIDATOR: VALID FOLLOWS* CLAUSE QUERIES") {
    Validator validator = Validator();

    // Synonym First argument
    std::string query = "stmt s; Select s such that Follows*(s, 3)";
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // Wildcard first argument
    query = "stmt s; Select s such that Follows*(_, 3)";
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // Integer first argument
    query = "stmt s; Select s such that Follows*(5, 3)";
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // Synonym second argument
    query = "stmt s; Select s such that Follows*(3, s)";
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // Wildcard second argument
    query = "stmt s; Select s such that Follows*(s, _)";
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // Integer Second argument
    query = "stmt s; Select s such that Follows*(s, 3)";
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));
}

TEST_CASE ("QP SYNTACTIC VALIDATOR: VALID PARENT CLAUSE QUERIES") {
    Validator validator = Validator();

    // Synonym First argument
    std::string query = "stmt s; Select s such that Parent(s, 3)";
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // Wildcard first argument
    query = "stmt s; Select s such that Parent(_, 3)";
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // Integer first argument
    query = "stmt s; Select s such that Parent(5, 3)";
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // Synonym second argument
    query = "stmt s; Select s such that Parent(3, s)";
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // Wildcard second argument
    query = "stmt s; Select s such that Parent(s, _)";
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // Integer Second argument
    query = "stmt s; Select s such that Parent(s, 3)";
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));
}

TEST_CASE ("QP SYNTACTIC VALIDATOR: VALID PARENT* CLAUSE QUERIES") {
    Validator validator = Validator();

    // Synonym First argument
    std::string query = "stmt s; Select s such that Parent*(s, 3)";
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // Wildcard first argument
    query = "stmt s; Select s such that Parent*(_, 3)";
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // Integer first argument
    query = "stmt s; Select s such that Parent*(5, 3)";
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // Synonym second argument
    query = "stmt s; Select s such that Parent*(3, s)";
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // Wildcard second argument
    query = "stmt s; Select s such that Parent*(s, _)";
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // Integer Second argument
    query = "stmt s; Select s such that Parent*(s, 3)";
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));
}

TEST_CASE ("QP SYNTACTIC VALIDATOR: USES CLAUSE VALID QUERIES") {
    Validator validator = Validator();

    // Synonym first argument
    std::string query = "stmt s; variable v; Select s such that Uses(s, v)";
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // Wildcard second argument
    query = "stmt s; variable v; Select s such that Uses(_, v)";
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // Integer first argument
    query = "stmt s; variable v; Select s such that Uses(5, v)";
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // Ident first argument
    query = "stmt s; variable v; Select s such that Uses(\"x\", v)";
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // Synonym second argument
    query = "stmt s; variable v; Select s such that Uses(s, v)";
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // Wildcard second argument
    query = "stmt s; variable v; Select s such that Uses(v, _)";
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // Ident second argument
    query = "stmt s; variable v; Select s such that Uses(v, \"x\")";
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));
}

TEST_CASE ("QP SYNTACTIC VALIDATOR: MODIFIES CLAUSE VALID QUERIES") {
    Validator validator = Validator();

    // Synonym first argument
    std::string query = "stmt s; variable v; Select s such that Modifies(s, v)";
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // Wildcard second argument
    query = "stmt s; variable v; Select s such that Modifies(_, v)";
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // Integer first argument
    query = "stmt s; variable v; Select s such that Modifies(5, v)";
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // Ident first argument
    query = "stmt s; variable v; Select s such that Modifies(\"x\", v)";
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // Synonym second argument
    query = "stmt s; variable v; Select s such that Modifies(s, v)";
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // Wildcard second argument
    query = "stmt s; variable v; Select s such that Modifies(v, _)";
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // Ident second argument
    query = "stmt s; variable v; Select s such that Modifies(v, \"x\")";
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));
}

TEST_CASE ("QP SYNTACTIC VALIDATOR: VALID NEXT CLAUSE QUERIES") {
    Validator validator = Validator();

    // Synonym First argument
    std::string query = "stmt s; Select s such that Next(s, 3)";
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // Wildcard first argument
    query = "stmt s; Select s such that Next(_, 3)";
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // Integer first argument
    query = "stmt s; Select s such that Next(5, 3)";
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // Synonym second argument
    query = "stmt s; Select s such that Next(3, s)";
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // Wildcard second argument
    query = "stmt s; Select s such that Next(s, _)";
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // Integer Second argument
    query = "stmt s; Select s such that Next(s, 3)";
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));
}

TEST_CASE ("QP SYNTACTIC VALIDATOR: VALID NEXT* CLAUSE QUERIES") {
    Validator validator = Validator();

    // Synonym First argument
    std::string query = "stmt s; Select s such that Next*(s, 3)";
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // Wildcard first argument
    query = "stmt s; Select s such that Next*(_, 3)";
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // Integer first argument
    query = "stmt s; Select s such that Next*(5, 3)";
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // Synonym second argument
    query = "stmt s; Select s such that Next*(3, s)";
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // Wildcard second argument
    query = "stmt s; Select s such that Next*(s, _)";
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // Integer Second argument
    query = "stmt s; Select s such that Next*(s, 3)";
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));
}

TEST_CASE("QP SYNTACTIC VALIDATOR: VALID CALLS QUERIES") {
    Validator validator = Validator();

    // Synonym first argument
    std::string query = "stmt s; variable v; Select s such that Calls(s, v)";
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // Wildcard first argument
    query = "stmt s; variable v; Select s such that Calls(_, v)";
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // Ident first argument
    query = "stmt s; variable v; Select s such that Calls(\"x\", v)";
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // Synonym second argument
    query = "stmt s; variable v; Select s such that Calls(s, v)";
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // Wildcard second argument
    query = "stmt s; variable v; Select s such that Calls(v, _)";
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // Ident second argument
    query = "stmt s; variable v; Select s such that Calls(v, \"x\")";
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));
}

TEST_CASE("QP SYNTACTIC VALIDATOR: VALID CALLS* QUERIES") {
    Validator validator = Validator();

    // Synonym first argument
    std::string query = "stmt s; variable v; Select s such that Calls*(s, v)";
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // Wildcard first argument
    query = "stmt s; variable v; Select s such that Calls*(_, v)";
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // Ident first argument
    query = "stmt s; variable v; Select s such that Calls*(\"x\", v)";
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // Synonym second argument
    query = "stmt s; variable v; Select s such that Calls*(s, v)";
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // Wildcard second argument
    query = "stmt s; variable v; Select s such that Calls*(v, _)";
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // Ident second argument
    query = "stmt s; variable v; Select s such that Calls*(v, \"x\")";
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));
}

TEST_CASE("QP SYNTACTIC VALIDATOR: VALID FFECTS QUERIES") {
    Validator validator = Validator();

    // Synonym first argument
    std::string query = "stmt s; variable v; Select s such that Affects(s, v)";
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // Wildcard first argument
    query = "stmt s; variable v; Select s such that Affects(_, v)";
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // Integer first argument
    query = "stmt s; variable v; Select s such that Affects(3, v)";
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // Synonym second argument
    query = "stmt s; variable v; Select s such that Affects(s, v)";
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // Wildcard second argument
    query = "stmt s; variable v; Select s such that Affects(v, _)";
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // Integer second argument
    query = "stmt s; variable v; Select s such that Affects(v, 3)";
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));
}

TEST_CASE("QP SYNTACTIC VALIDATOR: VALID AFFECTS* QUERIES") {
    Validator validator = Validator();

    // Synonym first argument
    std::string query = "stmt s; variable v; Select s such that Affects*(s, v)";
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // Wildcard first argument
    query = "stmt s; variable v; Select s such that Affects*(_, v)";
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // Integer first argument
    query = "stmt s; variable v; Select s such that Affects*(3, v)";
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // Synonym second argument
    query = "stmt s; variable v; Select s such that Affects*(s, v)";
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // Wildcard second argument
    query = "stmt s; variable v; Select s such that Affects*(v, _)";
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // Integer second argument
    query = "stmt s; variable v; Select s such that Affects*(v, 3)";
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));
}

TEST_CASE ("QP SYNTACTIC VALIDATOR: MULTIPLE SUCH THAT CLAUSES") {
    Validator validator = Validator();

    // Such that relationship and relationship and relationship
    std::string query = "stmt s; variable v; Select s such that Modifies(v, _) and Follows(3, 2) and Next*(s, 4)";
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // Multiple such that clauses
    query = "stmt s; variable v; Select s such that Modifies(v, _) such that Follows(3, 2) and Next*(s, 4) such that Affects(_, _)";
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // Check attr names as arguments
    query = "stmt s; variable v; Select s such that Modifies(procName, varName) such that Follows(3, 2) and Affects*(value, 4)";
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));
}

TEST_CASE ("QP SYNTACTIC VALIDATOR: INVALID SUCH THAT CLAUSE QUERIES") {
    Validator validator = Validator();

    // No space for such that
    std::string query = "stmt s; variable v; Select s suchthat Modifies(v, _)";
    REQUIRE_THROWS(validator.validateQueryStructure(query));

    // misspelled such that
    query = "stmt s; variable v; Select s such tht Modifies(v, _)";
    REQUIRE_THROWS(validator.validateQueryStructure(query));

    // misspelled modifies clause
    query = "stmt s; variable v; Select s such tht Modifie(v, _)";
    REQUIRE_THROWS(validator.validateQueryStructure(query));

    // Incorrect caps for modifies clause
    query = "stmt s; variable v; Select s such tht modifies(v, _)";
    REQUIRE_THROWS(validator.validateQueryStructure(query));

    // Incorrect ident first argument for Follows
    query = "stmt s; variable v; Select s such tht Follows(\"x\", 3)";
    REQUIRE_THROWS(validator.validateQueryStructure(query));

    // Incorrect ident second argument for Follows
    query = "stmt s; variable v; Select s such tht Follows(2, \"x\")";
    REQUIRE_THROWS(validator.validateQueryStructure(query));

    // Incorrect ident first argument for Follows*
    query = "stmt s; variable v; Select s such tht Follows*(\"x\", 3)";
    REQUIRE_THROWS(validator.validateQueryStructure(query));

    // Incorrect ident second argument for Follows*
    query = "stmt s; variable v; Select s such tht Follows*(2, \"x\")";
    REQUIRE_THROWS(validator.validateQueryStructure(query));

    // Incorrect ident first argument for Parent
    query = "stmt s; variable v; Select s such tht Parent(\"x\", 3)";
    REQUIRE_THROWS(validator.validateQueryStructure(query));

    // Incorrect ident second argument for Parent
    query = "stmt s; variable v; Select s such tht Parent(2, \"x\")";
    REQUIRE_THROWS(validator.validateQueryStructure(query));

    // Incorrect ident first argument for Parent*
    query = "stmt s; variable v; Select s such tht Parent*(\"x\", 3)";
    REQUIRE_THROWS(validator.validateQueryStructure(query));

    // Incorrect ident second argument for Parent*
    query = "stmt s; variable v; Select s such tht Parent*(2, \"x\")";
    REQUIRE_THROWS(validator.validateQueryStructure(query));

    // Incorrect integer first argument for Uses
    query = "stmt s; variable v; Select v such tht Uses(3, v)";
    REQUIRE_THROWS(validator.validateQueryStructure(query));

    // Incorrect integer second argument for Uses
    query = "stmt s; variable v; Select v such tht Uses(v, 3)";
    REQUIRE_THROWS(validator.validateQueryStructure(query));

    // Incorrect integer first argument for Modifies
    query = "stmt s; variable v; Select v such tht Modifies(3, v)";
    REQUIRE_THROWS(validator.validateQueryStructure(query));

    // Incorrect second argument for Modifies
    query = "stmt s; variable v; Select v such tht Modifies(v, 3)";
    REQUIRE_THROWS(validator.validateQueryStructure(query));

    // Incorrect ident first argument for Next
    query = "stmt s; variable v; Select s such tht Next(\"x\", 3)";
    REQUIRE_THROWS(validator.validateQueryStructure(query));

    // Incorrect ident second argument for Next
    query = "stmt s; variable v; Select s such tht Next(2, \"x\")";
    REQUIRE_THROWS(validator.validateQueryStructure(query));

    // Incorrect ident first argument for Next*
    query = "stmt s; variable v; Select s such tht Next*(\"x\", 3)";
    REQUIRE_THROWS(validator.validateQueryStructure(query));

    // Incorrect ident second argument for Next*
    query = "stmt s; variable v; Select s such tht Next*(2, \"x\")";
    REQUIRE_THROWS(validator.validateQueryStructure(query));

    // Incorrect integer first argument for Affects
    query = "stmt s; variable v; Select v such tht Affects(3, v)";
    REQUIRE_THROWS(validator.validateQueryStructure(query));

    // Incorrect second argument for Affects
    query = "stmt s; variable v; Select v such tht Affects(v, 3)";
    REQUIRE_THROWS(validator.validateQueryStructure(query));

    // Incorrect integer first argument for Affects*
    query = "stmt s; variable v; Select v such tht Affects*(3, v)";
    REQUIRE_THROWS(validator.validateQueryStructure(query));

    // Incorrect second argument for Affects*
    query = "stmt s; variable v; Select v such tht Affects*(v, 3)";
    REQUIRE_THROWS(validator.validateQueryStructure(query));

    // Incorrect integer first argument for Calls
    query = "stmt s; variable v; Select v such tht Calls(3, v)";
    REQUIRE_THROWS(validator.validateQueryStructure(query));

    // Incorrect second argument for Calls
    query = "stmt s; variable v; Select v such tht Calls(v, 3)";
    REQUIRE_THROWS(validator.validateQueryStructure(query));

    // Incorrect integer first argument for Calls*
    query = "stmt s; variable v; Select v such tht Calls*(3, v)";
    REQUIRE_THROWS(validator.validateQueryStructure(query));

    // Incorrect second argument for Affects*
    query = "stmt s; variable v; Select v such tht Affects*(v, 3)";
    REQUIRE_THROWS(validator.validateQueryStructure(query));

    // pattern followed by such that
    query = "stmt s; variable v; Select v such tht pattern a1(v1, _)";
    REQUIRE_THROWS(validator.validateQueryStructure(query));

    // pattern followed by such that
    query = "stmt s; variable v; Select v such tht pattern(v1, _)";
    REQUIRE_THROWS(validator.validateQueryStructure(query));

    // pattern followed by such that
    query = "stmt s; variable v; Select v such tht Uses(v1, _) and pattern a1(_, _)";
    REQUIRE_THROWS(validator.validateQueryStructure(query));

    // pattern followed by such that
    query = "stmt s; variable v; Select v such tht Uses(v1, _) and a1(_, _)";
    REQUIRE_THROWS(validator.validateQueryStructure(query));

    // with clause followed by such that
    query = "stmt s; variable v; Select v such tht Uses(v1, _) and p.procName=p2.procName";
    REQUIRE_THROWS(validator.validateQueryStructure(query));
}

TEST_CASE ("QP SYNTACTIC VALIDATOR: VALID PATTERN CLAUSE QUERIES") {
    Validator validator = Validator();

    // Simple pattern clause
    std::string query = "assign a; Select a pattern a(_, _)";
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // Pattern with double char syn-assign
    query = "assign a; Select a pattern ab(_, _)";
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // Pattern with char+int syn-assign
    query = "assign a; Select a pattern a1(_, _)";
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // Pattern with synonym for first argument
    query = "assign a; stmt s; Select a pattern a1(s, _)";
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // Pattern with ident for first argument
    query = "assign a; stmt s; Select a pattern a1(\"x\", _)";
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // Pattern with partial wildcard for second argument
    query = "assign a; stmt s; Select a pattern a1(_, _\"x\"_)";
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // Pattern with ident for second argument
    query = "assign a; stmt s; Select a pattern a1(_, \"x\")";
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // Pattern with pattern for syn-assign
    query = "assign a; stmt s; Select pattern pattern pattern(_, \"x\")";
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // Pattern with Select for syn-assign
    query = "assign a; stmt s; Select Select pattern Select(_, \"x\")";
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // Pattern with 3 wildcard arguments
    query = "assign a; stmt s; Select Select pattern a(_, _, _)";
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // Pattern and pattern and pattern
    query = "assign a; stmt s; Select Select pattern a(_, _, _) and a1 (_, _) and a2(v, _)";
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // Pattern and pattern pattern
    query = "assign a; stmt s; Select Select pattern a(_, _, _) and a1 (_, _) pattern a2(v, _)";
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // Pattern and pattern synonym named Follows
    query = "assign a; stmt s; Select Select pattern a(_, _, _) and Follows (_, _)";
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // Pattern arguments attr names
    query = "assign a; stmt s; Select Select pattern a(varName, _, _) and a1 (procName, _) pattern a2(value, _)";
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));
}

TEST_CASE ("QP SYNTACTIC VALIDATOR: VALID PATTERN QUERIES") {
    Validator validator = Validator();

    // Pattern with integer as first argument
    std::string query = "assign a; stmt s; Select Select pattern Select(3, _)";
    REQUIRE_THROWS(validator.validateQueryStructure(query));

    // Pattern with integer as second argument
    query = "assign a; stmt s; Select a pattern a(_, 3)";
    REQUIRE_THROWS(validator.validateQueryStructure(query));

    // Pattern with integer as third argument
    query = "assign a; stmt s; Select a pattern a(_, _, 3)";
    REQUIRE_THROWS(validator.validateQueryStructure(query));

    // Pattern with ident as third argument
    query = "assign a; stmt s; Select a pattern a(_, _, \"x\")";
    REQUIRE_THROWS(validator.validateQueryStructure(query));

    // Pattern with partial wildcard as first argument
    query = "assign a; stmt s; Select a pattern a(_\"x\"_, _)";
    REQUIRE_THROWS(validator.validateQueryStructure(query));

    // Pattern with partial wildcard as third argument
    query = "assign a; stmt s; Select a pattern a(_, _, _\"x\"_)";
    REQUIRE_THROWS(validator.validateQueryStructure(query));

    // Pattern with synonym for second argument
    query = "assign a; stmt s; Select a pattern a(_, s)";
    REQUIRE_THROWS(validator.validateQueryStructure(query));

    // Pattern with synonym for third argument
    query = "assign a; stmt s; Select a pattern a(_, _, s)";
    REQUIRE_THROWS(validator.validateQueryStructure(query));

    // Pattern with integer as syn-assign
    query = "assign a; stmt s; Select a pattern 3(_, s)";
    REQUIRE_THROWS(validator.validateQueryStructure(query));

    // Pattern and invalid pattern
    query = "assign a; stmt s; Select a pattern a(_, _) and pattern a(_, _)";
    REQUIRE_THROWS(validator.validateQueryStructure(query));

    // 4 arguments for pattern
    query = "assign a; stmt s; Select a pattern a(_, _, _, _)";
    REQUIRE_THROWS(validator.validateQueryStructure(query));

    // Pattern and with clause
    query = "assign a; stmt s; Select a pattern a(_, _, _) and p.procName=\"x\"";
    REQUIRE_THROWS(validator.validateQueryStructure(query));
}

TEST_CASE ("QP SYNTACTIC VALIDATOR: VALID WITH CLAUSE QUERIES") {
    Validator validator = Validator();

    // With clause with procName attribute
    std::string query = "assign a; procedure p1, p2; Select a with p1.procName=p2.procName";
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // With clause with varName attribute
    query = "assign a; procedure p1, p2; Select a with p1.varName=p2.varName";
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // With clause with value attribute
    query = "assign a; procedure p1, p2; Select a with p1.value=p2.value";
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // With clause with stmt# attribute
    query = "assign a; procedure p1, p2; Select a with p1.stmt#=p2.stmt#";
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // With clause with ident as first argument
    query = "assign a; procedure p1, p2; Select a with \"x\"=p2.procName";
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // With clause with integer as first argument
    query = "assign a; procedure p1, p2; Select a with 3=p2.stmt#";
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // With clause with ident as second argument
    query = "assign a; procedure p1, p2; Select a with p1.procName=\"x\"";
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // With clause with integer as second argument
    query = "assign a; procedure p1, p2; Select a with p2.stmt#=3";
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // With clause and with clause and with clause
    query = "assign a; procedure p1, p2; Select a with p2.stmt#=3 and p1.procName=\"x\" and p1.value=4";
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // Multiple with clauses
    query = "assign a; procedure p1, p2; Select a with p2.stmt#=3 with p1.procName=\"x\" with p1.value=4";
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // Multiple with clauses with 'and'
    query = "assign a; procedure p1, p2; Select a with p2.stmt#=3 with p1.procName=\"x\" and p1.value=4";
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // With clause with synonym called 'with'
    query = "assign a; procedure p1, p2; Select a with with.stmt#=3";
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // With clause with synonym called 'procName'
    query = "assign a; procedure p1, p2; Select a with procName.stmt#=3";
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));
}

TEST_CASE ("QP SYNTACTIC VALIDATOR: INVALID WITH CLAUSE QUERIES") {
    Validator validator = Validator();

    // With clause with synonym as first argument
    std::string query = "assign a; procedure p1, p2; Select a with p1=p2.procName";
    query = Tokenizer::lexicalTokens(query);
    REQUIRE_THROWS(validator.validateQueryStructure(query));

    // With clause with synonym as second argument
    query = "assign a; procedure p1, p2; Select a with p1.procName=p2";
    query = Tokenizer::lexicalTokens(query);
    REQUIRE_THROWS(validator.validateQueryStructure(query));

    // With clause with invalid synonym
    query = "assign a; procedure p1, p2; Select a with 1.procName=p2.procName";
    REQUIRE_THROWS(Tokenizer::lexicalTokens(query));

    // With clause and pattern
    query = "assign a; procedure p1, p2; Select a with p1.procName=p2.procName and a (_, _)";
    query = Tokenizer::lexicalTokens(query);
    REQUIRE_THROWS(validator.validateQueryStructure(query));

    // With clause and Follows
    query = "assign a; procedure p1, p2; Select a with 1.procName=p2.procName and Follows (_, _)";
    REQUIRE_THROWS(Tokenizer::lexicalTokens(query));

    // With clause and pattern
    query = "assign a; procedure p1, p2; Select a with 1.procName=p2.procName and pattern a (_, _)";
    REQUIRE_THROWS(Tokenizer::lexicalTokens(query));
}

TEST_CASE ("QP SYNTACTIC VALIDATOR: VALID MULTI CLAUSES QUERIES") {
    Validator validator = Validator();

    // Pattern then Follows
    std::string query = "assign a; stmt s; Select a pattern a(_, _) such that Follows(3, 2)";
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // Follows then pattern
    query = "assign a; stmt s; Select a such that Follows(3, 2) pattern a(_, _) ";
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // Pattern and pattern then such that clause and such that clause
    query = "assign a; stmt s; Select a pattern a(_, _) and a2(_, _) such that Follows(3, 2) and Parent*(_, 4)";
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // Such that clause then with clause
    query = "assign a; stmt s; Select a such that Follows(2, 3) with p.procName=p2.procName";
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // Pattern then with clause
    query = "assign a; stmt s; Select a pattern a(_, _) with p.procName=p2.procName";
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // With Clause then Follows
    query = "assign a; stmt s; Select a with p.procName=p2.procName such that Follows(2, 3)";
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // With clause then pattern
    query = "assign a; stmt s; Select a with p.procName=p2.procName pattern a (_, _)";
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // With clause, pattern then such that clause
    query = "assign a; stmt s; Select a with p.procName=p2.procName pattern a (_, _) such that Follows(2, 3)";
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // With clause, pattern then such that clause with ands
    query = "assign a; stmt s; Select a with p.procName=p2.procName and c.value = 3 pattern a (_, _) and a(v, _) such that Follows(2, 3) and Next*(_, _)";
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));
}

TEST_CASE ("QP SYNTACTIC VALIDATOR: INVALID QUERIES MULTICLAUSE") {
    Validator validator = Validator();

    // such that pattern instead of relationship
    std::string query = "assign a; stmt s; Select a such that pattern a(_, _) ";
    REQUIRE_THROWS(validator.validateQueryStructure(query));

    // such that with clause instead of relationship
    query = "assign a; stmt s; Select a such that with p.procName = 3";
    REQUIRE_THROWS(validator.validateQueryStructure(query));

    // no such that with relationship
    query = "assign a; stmt s; Select a Follows(3, 2)";
    REQUIRE_THROWS(validator.validateQueryStructure(query));
}

TEST_CASE ("QP SYNTACTIC VALIDATOR: RANDOM SPACES AND TABS") {
    Validator validator = Validator();

    // multiple spaces between design entity and declaration
    std::string query = "assign        a; stmt s; Select a such that Follows(3, 2)";
    query = Tokenizer::lexicalTokens(query);
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // tab between design entity and declaration
    query = "assign\ta; stmt s; Select a such that Follows(3, 2)";
    query = Tokenizer::lexicalTokens(query);
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // tab and spaces between design entity and declaration
    query = "assign\t   a; stmt s; Select a such that Follows(3, 2)";
    query = Tokenizer::lexicalTokens(query);
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // no space between 2 declarations
    query = "assign a,a2; stmt s; Select a such that Follows(3, 2)";
    query = Tokenizer::lexicalTokens(query);
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // spaces between 2 declarations of same design entity
    query = "assign a,     a2; stmt s; Select a such that Follows(3, 2)";
    query = Tokenizer::lexicalTokens(query);
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // spaces between declarations of different design entities
    query = "assign a;     stmt s; Select a such that Follows(3, 2)";
    query = Tokenizer::lexicalTokens(query);
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // tab between declarations of different design entities
    query = "assign a;\tstmt s; Select a such that Follows(3, 2)";
    query = Tokenizer::lexicalTokens(query);
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // tab and spaces between declarations of different design entities
    query = "assign a;\t     stmt s; Select a such that Follows(3, 2)";
    query = Tokenizer::lexicalTokens(query);
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // no space between 2 design entities declarations
    query = "assign a;stmt s; Select a such that Follows(3, 2)";
    query = Tokenizer::lexicalTokens(query);
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // spaces between declarations and Select clause
    query = "assign a; stmt s;         Select a such that Follows(3, 2)";
    query = Tokenizer::lexicalTokens(query);
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // tab between declarations and Select clause
    query = "assign a; stmt s;\tSelect a such that Follows(3, 2)";
    query = Tokenizer::lexicalTokens(query);
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // tab and spaces between declarations and Select clause
    query = "assign a; stmt s;\t      Select a such that Follows(3, 2)";
    query = Tokenizer::lexicalTokens(query);
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // no tab and spaces between declarations and Select clause
    query = "assign a; stmt s;Select a such that Follows(3, 2)";
    query = Tokenizer::lexicalTokens(query);
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // spaces between Select clause and synonym
    query = "assign a; stmt s; Select     a such that Follows(3, 2)";
    query = Tokenizer::lexicalTokens(query);
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // tab between Select clause and synonym
    query = "assign a; stmt s; Select\ta such that Follows(3, 2)";
    query = Tokenizer::lexicalTokens(query);
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // tab and spaces between Select clause and synonym
    query = "assign a; stmt s; Select\t     a such that Follows(3, 2)";
    query = Tokenizer::lexicalTokens(query);
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // spaces between synonym and such
    query = "assign a; stmt s; Select a      such that Follows(3, 2)";
    query = Tokenizer::lexicalTokens(query);
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // tab between synonym and such
    query = "assign a; stmt s; Select a\tsuch that Follows(3, 2)";
    query = Tokenizer::lexicalTokens(query);
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // tab and spaces between synonym and such
    query = "assign a; stmt s; Select a\t       such that Follows(3, 2)";
    query = Tokenizer::lexicalTokens(query);
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // spaces between such that
    query = "assign a; stmt s; Select a such      that Follows(3, 2)";
    query = Tokenizer::lexicalTokens(query);
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // tab between such that
    query = "assign a; stmt s; Select a such\tthat Follows(3, 2)";
    query = Tokenizer::lexicalTokens(query);
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // spaces and tab between such that
    query = "assign a; stmt s; Select a such\t      that Follows(3, 2)";
    query = Tokenizer::lexicalTokens(query);
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // spaces between such that and Relationship
    query = "assign a; stmt s; Select a such that      Follows(3, 2)";
    query = Tokenizer::lexicalTokens(query);
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // tab between such that and Relationship
    query = "assign a; stmt s; Select a such that\tFollows(3, 2)";
    query = Tokenizer::lexicalTokens(query);
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // tab and spaces between such that and Relationship
    query = "assign a; stmt s; Select a such that\t    Follows(3, 2)";
    query = Tokenizer::lexicalTokens(query);
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // spaces between RelRef and (
    query = "assign a; stmt s; Select a such that Follows    (3, 2)";
    query = Tokenizer::lexicalTokens(query);
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // tab between RelRef and (
    query = "assign a; stmt s; Select a such that Follows\t(3, 2)";
    query = Tokenizer::lexicalTokens(query);
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // tab and spaces between RelRef and (
    query = "assign a; stmt s; Select a such that Follows\t    (3, 2)";
    query = Tokenizer::lexicalTokens(query);
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // spaces between such that clause ( and first argument
    query = "assign a; stmt s; Select a such that Follows(     3, 2)";
    query = Tokenizer::lexicalTokens(query);
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // tab between such that clause ( and first argument
    query = "assign a; stmt s; Select a such that Follows(\t3, 2)";
    query = Tokenizer::lexicalTokens(query);
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // tab and spaces between such that clause ( and first argument
    query = "assign a; stmt s; Select a such that Follows(\t    3, 2)";
    query = Tokenizer::lexicalTokens(query);
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // spaces between such that clause first argument and comma
    query = "assign a; stmt s; Select a such that Follows(3    , 2)";
    query = Tokenizer::lexicalTokens(query);
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // tab between such that clause first argument and comma
    query = "assign a; stmt s; Select a such that Follows(3\t, 2)";
    query = Tokenizer::lexicalTokens(query);
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // tab and spaces between such that clause first argument and comma
    query = "assign a; stmt s; Select a such that Follows(3\t    , 2)";
    query = Tokenizer::lexicalTokens(query);
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // no tab and spaces between such that clause comma and second argument
    query = "assign a; stmt s; Select a such that Follows(3,2)";
    query = Tokenizer::lexicalTokens(query);
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // spaces between such that clause comma and second argument
    query = "assign a; stmt s; Select a such that Follows(3,    2)";
    query = Tokenizer::lexicalTokens(query);
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // tab between such that clause comma and second argument
    query = "assign a; stmt s; Select a such that Follows(3,\t2)";
    query = Tokenizer::lexicalTokens(query);
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // spaces and tab and spaces between such that clause comma and second argument
    query = "assign a; stmt s; Select a such that Follows(3,\t      2)";
    query = Tokenizer::lexicalTokens(query);
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // spaces between such that clause second argument and closing bracket
    query = "assign a; stmt s; Select a such that Follows(3, 2    )";
    query = Tokenizer::lexicalTokens(query);
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // tab between such that clause second argument and closing bracket
    query = "assign a; stmt s; Select a such that Follows(3, 2\t)";
    query = Tokenizer::lexicalTokens(query);
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // tab and spaces between such that clause second argument and closing bracket
    query = "assign a; stmt s; Select a such that Follows(3, 2\t     )";
    query = Tokenizer::lexicalTokens(query);
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // no space between such that clause and pattern
    query = "assign a; stmt s; Select a such that Follows(3, 2)pattern a (_, _)";
    query = Tokenizer::lexicalTokens(query);
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // spaces between such that clause and pattern
    query = "assign a; stmt s; Select a such that Follows(3, 2)      pattern a (_, _)";
    query = Tokenizer::lexicalTokens(query);
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // tab between such that clause and pattern
    query = "assign a; stmt s; Select a such that Follows(3, 2)\tpattern a (_, _)";
    query = Tokenizer::lexicalTokens(query);
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // tab and spaces between such that clause and pattern
    query = "assign a; stmt s; Select a such that Follows(3, 2)\t       pattern a (_, _)";
    query = Tokenizer::lexicalTokens(query);
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // spaces between pattern and syn-assign
    query = "assign a; stmt s; Select a such that Follows(3, 2) pattern      a (_, _)";
    query = Tokenizer::lexicalTokens(query);
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // tab between pattern and syn-assign
    query = "assign a; stmt s; Select a such that Follows(3, 2) pattern\ta (_, _)";
    query = Tokenizer::lexicalTokens(query);
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // tab and spaces between pattern and syn-assign
    query = "assign a; stmt s; Select a such that Follows(3, 2) pattern\t    a (_, _)";
    query = Tokenizer::lexicalTokens(query);
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // multiple tabs and spaces between pattern and syn-assign
    query = "assign a; stmt s; Select a such that Follows(3, 2) pattern\t\t\t    a (_, _)";
    query = Tokenizer::lexicalTokens(query);
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // spaces between syn-assign and opening bracket
    query = "assign a; stmt s; Select a such that Follows(3, 2) pattern a     (_, _)";
    query = Tokenizer::lexicalTokens(query);
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // tab between syn-assign and opening bracket
    query = "assign a; stmt s; Select a such that Follows(3, 2) pattern a\t(_, _)";
    query = Tokenizer::lexicalTokens(query);
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // tab and spaces between syn-assign and opening bracket
    query = "assign a; stmt s; Select a such that Follows(3, 2) pattern a\t     (_, _)";
    query = Tokenizer::lexicalTokens(query);
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // no tab and spaces between syn-assign and opening bracket
    query = "assign a; stmt s; Select a such that Follows(3, 2) pattern a(_, _)";
    query = Tokenizer::lexicalTokens(query);
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // spaces between opening bracket and first argument
    query = "assign a; stmt s; Select a such that Follows(3, 2) pattern a (       _, _)";
    query = Tokenizer::lexicalTokens(query);
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // tab between opening bracket and first argument
    query = "assign a; stmt s; Select a such that Follows(3, 2) pattern a (\t_, _)";
    query = Tokenizer::lexicalTokens(query);
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // tab and spaces between opening bracket and first argument
    query = "assign a; stmt s; Select a such that Follows(3, 2) pattern a (\t        _, _)";
    query = Tokenizer::lexicalTokens(query);
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // spaces between first argument and comma
    query = "assign a; stmt s; Select a such that Follows(3, 2) pattern a (_     , _)";
    query = Tokenizer::lexicalTokens(query);
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // tab between first argument and comma
    query = "assign a; stmt s; Select a such that Follows(3, 2) pattern a (_\t, _)";
    query = Tokenizer::lexicalTokens(query);
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // tab and spaces between first argument and comma
    query = "assign a; stmt s; Select a such that Follows(3, 2) pattern a (_\t        , _)";
    query = Tokenizer::lexicalTokens(query);
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // spaces between comma and second argument
    query = "assign a; stmt s; Select a such that Follows(3, 2) pattern a (_,     _)";
    query = Tokenizer::lexicalTokens(query);
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // tab between comma and second argument
    query = "assign a; stmt s; Select a such that Follows(3, 2) pattern a (_,\t_)";
    query = Tokenizer::lexicalTokens(query);
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // tab and spaces between comma and second argument
    query = "assign a; stmt s; Select a such that Follows(3, 2) pattern a (_,\t       _)";
    query = Tokenizer::lexicalTokens(query);
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // no tab and spaces between comma and second argument
    query = "assign a; stmt s; Select a such that Follows(3, 2) pattern a (_,_)";
    query = Tokenizer::lexicalTokens(query);
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // spaces between second argument and closing bracket
    query = "assign a; stmt s; Select a such that Follows(3, 2) pattern a (_,_    )";
    query = Tokenizer::lexicalTokens(query);
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // tab between second argument and closing bracket
    query = "assign a; stmt s; Select a such that Follows(3, 2) pattern a (_,_\t)";
    query = Tokenizer::lexicalTokens(query);
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // tab and spaces between second argument and closing bracket
    query = "assign a; stmt s; Select a such that Follows(3, 2) pattern a (_,_\t      )";
    query = Tokenizer::lexicalTokens(query);
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // tab and spaces at the end
    query = "assign a; stmt s; Select a such that Follows(3, 2) pattern a (_, _)      \t\t\t";
    query = Tokenizer::lexicalTokens(query);
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // tab and spaces at the end
    query = "assign a; stmt s; Select a      \t\t\t";
    query = Tokenizer::lexicalTokens(query);
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // tab and spaces at the end
    query = "assign a; stmt s; Select a such that Follows(3, 2)     \t\t\t";
    query = Tokenizer::lexicalTokens(query);
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // tab and spaces at the end
    query = "assign a; stmt s; Select a pattern a (_, _)     \t\t\t";
    query = Tokenizer::lexicalTokens(query);
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // tabs and spaces between '.' in Select clause attr ref
    query = "assign a; procedure p; Select p  \t  \t . \t \t \tprocName";
    query = Tokenizer::lexicalTokens(query);
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // tabs and spaces between '.' in with clause attr ref
    query = "assign a; procedure p; Select p with p  \t  \t . \t \t \tprocName = \"x\"";
    query = Tokenizer::lexicalTokens(query);
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // tabs and spaces between 'and' in with clauses
    query = "assign a; procedure p; Select p with p.procName = \"x\" \t \t \t \t and c.value=3";
    query = Tokenizer::lexicalTokens(query);
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // tabs and spaces between 'and' in pattern clauses
    query = "assign a; procedure p; Select p pattern a (_, _)\t \t \t \t  and a2(_, _)";
    query = Tokenizer::lexicalTokens(query);
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // tabs and spaces between 'and' in such that clauses
    query = "assign a; procedure p; Select p such that Next(3, 2) \t \t \t \t  and Follows(_, _)";
    query = Tokenizer::lexicalTokens(query);
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // missed spacing
    query = "assigna; stmt s; Select a such that Follows(3, 2) pattern a (_, _)";
    query = Tokenizer::lexicalTokens(query);
    REQUIRE_THROWS(validator.validateQueryStructure(query));

    // missed spacing
    query = "assign a; stmts; Select a such that Follows(3, 2) pattern a (_, _)";
    query = Tokenizer::lexicalTokens(query);
    REQUIRE_THROWS(validator.validateQueryStructure(query));

    // missed spacing
    query = "assign a; stmt s; Selecta such that Follows(3, 2) pattern a (_, _)";
    query = Tokenizer::lexicalTokens(query);
    REQUIRE_THROWS(validator.validateQueryStructure(query));

    // missed spacing
    query = "assign a; stmt s; Select asuch that Follows(3, 2) pattern a (_, _)";
    query = Tokenizer::lexicalTokens(query);
    REQUIRE_THROWS(validator.validateQueryStructure(query));

    // missed spacing
    query = "assign a; stmt s; Select a suchthat Follows(3, 2) pattern a (_, _)";
    query = Tokenizer::lexicalTokens(query);
    REQUIRE_THROWS(validator.validateQueryStructure(query));

    // missed spacing
    query = "assign a; stmt s; Select a such thatFollows(3, 2) pattern a (_, _)";
    query = Tokenizer::lexicalTokens(query);
    REQUIRE_THROWS(validator.validateQueryStructure(query));

    // missed spacing
    query = "assign a; stmt s; Select a such that Follows(3, 2)pattern a (_, _)";
    query = Tokenizer::lexicalTokens(query);
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // missed spacing
    query = "assign a; stmt s; Select a such that Follows(3, 2) patterna (_, _)";
    query = Tokenizer::lexicalTokens(query);
    REQUIRE_THROWS(validator.validateQueryStructure(query));

    // missed spacing
    query = "assign a; procedure p; Select p withp.procName = \"x\"";
    query = Tokenizer::lexicalTokens(query);
    REQUIRE_THROWS(validator.validateQueryStructure(query));

    // missed spacing between 2 such that clauses
    query = "assign a; procedure p; Select p such that Follows(2, 3)and Next(2, 3)";
    query = Tokenizer::lexicalTokens(query);
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // missed spacing between 2 patterns
    query = "assign a; procedure p; Select p pattern a(_,_)and a1(_, _)";
    query = Tokenizer::lexicalTokens(query);
    REQUIRE_NOTHROW(validator.validateQueryStructure(query));

    // incorrect spacing for with clause
    query = "assign a; procedure p; Select p with p.proc Name = \"x\"";
    REQUIRE_THROWS(Tokenizer::lexicalTokens(query));

    // incorrect spacing for with clause
    query = "assign a; procedure p; Select p wi th p.procName = \"x\"";
    query = Tokenizer::lexicalTokens(query);
    REQUIRE_THROWS(validator.validateQueryStructure(query));
}

TEST_CASE ("QP SYNTACTIC VALIDATOR: INCORRECT NEW LINES") {
    Validator validator = Validator();

    // newline in the middle of a design entity
    std::string query = "assign a; st\nmt s; Select a such that Follows(3, 2)";
    query = Tokenizer::lexicalTokens(query);
    REQUIRE_THROWS(validator.validateQueryStructure(query));

    // newline in the middle of Select
    query = "assign a; stmt s; Sel\nect a such that Follows(3, 2)";
    query = Tokenizer::lexicalTokens(query);
    REQUIRE_THROWS(validator.validateQueryStructure(query));

    // newline in the middle of a relationship
    query = "assign a; stmt s; Select a such that Foll\nows(3, 2)";
    query = Tokenizer::lexicalTokens(query);
    REQUIRE_THROWS(validator.validateQueryStructure(query));

    // newline in the middle of pattern
    query = "assign a; stmt s; Select a such that Follows(3, 2) pat\ntern a(2, 3)";
    query = Tokenizer::lexicalTokens(query);
    REQUIRE_THROWS(validator.validateQueryStructure(query));
}