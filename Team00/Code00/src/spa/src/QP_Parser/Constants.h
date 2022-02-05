#pragma once
using namespace QP;

// Regex for Lexical Tokens
string const LETTER = "[A-Za-z]";
string const DIGIT = "[0-9]";
string const IDENT = "[A-Za-z][A-Za-z|0-9]*";
string const NAME = "[A-Za-z][A-Za-z|0-9]*";
string const INTEGER = DIGIT + "+";

// TODO: Convert to regex
// const std::regex Synonym::synonym_regex = std::regex("[a-zA-Z](\\d|[a-zA-Z])*");
string const SYNONYM = IDENT;
string const STMT_REF = "(" + SYNONYM + "|_|" + INTEGER + ")";
string const ENT_REF = "(" + SYNONYM + "|_|" + '"' + IDENT + '"' + ")";

// Grammar Rules
string const DESIGN_ENTITY = "stmt" | "read" | "print" | "call" | "while" | "if" | "assign" | "variable"
        | "constant" | "procedure";
string const DECLARATION = "[" + DESIGN_ENTITY + " " + SYNONYM + "\\(',' " + SYNONYM + "\\)* ';'" + "]"; // not sure
string const SELECT_CL = DECLARATION + "* Select " + SYNONYM; // incomplete

// Relationships
string const FOLLOWS = "Follows\\(" + STMT_REF + "," + STMT_REF + "\\)";
string const FOLLOWS_T = "Follows\\*\\(" + STMT_REF + "," + STMT_REF + "\\)";

string const PARENT = "Parent\\(" + STMT_REF + "," + STMT_REF + "\\)";
string const PARENT_T = "Parent\\*\\(" + STMT_REF + "," + STMT_REF + "\\)";

string const Uses_S = "Uses\\(" + STMT_REF + "," + ENT_REF + "\\)";
string const Uses_P = "Uses\\(" + ENT_REF + "," + ENT_REF + "\\)";

string const Modifies_S = "Modifies\\(" + STMT_REF + "," + ENT_REF + "\\)";
string const Modifies_P = "Modifies\\(" + ENT_REF + "," + ENT_REF + "\\)";

// TODO: pattern regex
