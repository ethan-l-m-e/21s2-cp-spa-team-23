#pragma once
#include <regex>
//using namespace qp;

// Regex for Lexical Tokens
std::string const LETTER = "[A-Za-z]";
std::string const DIGIT = "[0-9]";
std::string const IDENT = "[A-Za-z][A-Za-z|0-9]*";
std::string const NAME = "[A-Za-z][A-Za-z|0-9]*";
std::string const INTEGER = DIGIT + "+";

// TODO: Convert to regex
std::string const SYNONYM = IDENT;
std::string const STMT_REF = "(" + SYNONYM + "|_|" + INTEGER + ")";
std::string const ENT_REF = "(" + SYNONYM + "|_|" + '"' + IDENT + '"' + ")";

// Grammar Rules
std::string const DESIGN_ENTITY = "(stmt|read|print|call|while|if|assign|variable|constant|procedure)";
std::string const DECLARATION = "(" + DESIGN_ENTITY + " " + SYNONYM + "(, " + SYNONYM + ")*;" + ")";
std::string const SELECT_CL = DECLARATION + "* Select " + SYNONYM; // incomplete

// Relationships
std::string const FOLLOWS = "Follows\\(" + STMT_REF + "," + STMT_REF + "\\)";
std::string const FOLLOWS_T = "Follows\\*\\(" + STMT_REF + "," + STMT_REF + "\\)";

std::string const PARENT = "Parent\\(" + STMT_REF + "," + STMT_REF + "\\)";
std::string const PARENT_T = "Parent\\*\\(" + STMT_REF + "," + STMT_REF + "\\)";

std::string const Uses_S = "Uses\\(" + STMT_REF + "," + ENT_REF + "\\)";
std::string const Uses_P = "Uses\\(" + ENT_REF + "," + ENT_REF + "\\)";

std::string const Modifies_S = "Modifies\\(" + STMT_REF + "," + ENT_REF + "\\)";
std::string const Modifies_P = "Modifies\\(" + ENT_REF + "," + ENT_REF + "\\)";

// TODO: pattern regex
std::string const FACTOR;
std::string const EXPRESSION_SPEC = "";
std::string const pattern = "pattern a\\(" + ENT_REF + "," + EXPRESSION_SPEC + "\\)";
