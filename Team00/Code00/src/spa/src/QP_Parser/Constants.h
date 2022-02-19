#pragma once

// Regex for Lexical Tokens
std::string const LETTER = "[A-Za-z]";
std::string const DIGIT = "[0-9]";
std::string const IDENT = "[A-Za-z][A-Za-z|0-9]*";
std::string const NAME = "[A-Za-z][A-Za-z|0-9]*";
std::string const INTEGER = DIGIT + "+";

std::string const SYNONYM = IDENT;
std::string const STMT_REF = "(" + SYNONYM + "|_|" + INTEGER + ")";
std::string const ENT_REF = "(" + SYNONYM + "|_|" + '"' + IDENT + '"' + ")";

// Grammar Rules
std::string const DESIGN_ENTITY = "(stmt|read|print|call|while|if|assign|variable|constant|procedure)";
std::string const DECLARATION = DESIGN_ENTITY + "[( |\t)]+" + SYNONYM + "(,[( |\t)]*" + SYNONYM + "[( |\t)]*)*;";


// Relationships
std::string const REF = "(" + SYNONYM + "|_|" + INTEGER + "|\"" + IDENT + "\"" + ")";
std::string const REL_REF = "(Follows|Follows\\*|Parent|Parent\\*|Uses|Modifies)";
std::string const RELATIONSHIP = REL_REF + "\\([( |\t)]*" + REF + "[( |\t)]*,[( |\t)]*" + REF + "[( |\t)]*\\)";
std::string const RELATIONSHIP_MATCH = "(.)*" + RELATIONSHIP + "(.)*";

// TODO: Edit Later
std::string const FOLLOWS = "Follows\\([( |\t)]*" + STMT_REF + "[( |\t)]*,[( |\t)]*" + STMT_REF + "[( |\t)]*\\)";
std::string const FOLLOWS_T = "Follows\\*\\([( |\t)]*" + STMT_REF + "[( |\t)]*,[( |\t)]*" + STMT_REF + "[( |\t)]*\\)";

std::string const PARENT = "Parent\\([( |\t)]*" + STMT_REF + "[( |\t)]*,[( |\t)]*" + STMT_REF + "[( |\t)]*\\)";
std::string const PARENT_T = "Parent\\*\\([( |\t)]*" + STMT_REF + "[( |\t)]*,[( |\t)]*" + STMT_REF + "[( |\t)]*\\)";

std::string const USES_S = "Uses\\([( |\t)]*" + STMT_REF + "[( |\t)]*,[( |\t)]*" + ENT_REF + "[( |\t)]*\\)";
std::string const USES_P = "Uses\\([( |\t)]*" + ENT_REF + "[( |\t)]*,[( |\t)]*" + ENT_REF + "[( |\t)]*\\)";

std::string const MODIFIES_S = "Modifies\\([( |\t)]*" + STMT_REF + "[( |\t)]*,[( |\t)]*" + ENT_REF + "[( |\t)]*\\)";
std::string const MODIFIES_P = "Modifies\\([( |\t)]*" + ENT_REF + "[( |\t)]*,[( |\t)]*" + ENT_REF + "[( |\t)]*\\)";

std::string const SUCH_THAT_CL = "such[( |\t)]+that[( |\t)]+(" + FOLLOWS + "|" + FOLLOWS_T + "|" + PARENT + "|" + PARENT_T
                                 + "|" + USES_S + "|" + USES_P + "|" + MODIFIES_S + "|" + MODIFIES_P + ")";

// pattern regex
std::string const EXPRESSION_SPEC = "(_|_\"(.)*\"_|\"(.)*\")";
std::string const PATTERN_CL = "pattern[( |\t)]+" + SYNONYM + "[( |\t)]*\\([( |\t)]*" + ENT_REF + "[( |\t)]*,[( |\t)]*"
        + EXPRESSION_SPEC + "[( |\t)]*\\)";
std::string const PATTERN_MATCH = "(.)*" + PATTERN_CL + "(.)*";


std::string const SELECT_CL = "[( |\n|\t)]*Select[ ]+" + SYNONYM + "([( |\t)]+" + SUCH_THAT_CL + "|[( |\t)]+"
        + PATTERN_CL + "[( |\t)]*)*";
std::string const DECLARATION_REGEX = "([( |\n|\t)]*" + DECLARATION+ ")+";
std::string const PQL_FORMAT = DECLARATION_REGEX + "[( |\n|\t)]+" + SELECT_CL;

// regex needed for semantic validation
std::string const STMT_RS = "(Follows|Follows\\*|Parent|Parent\\*)";
std::string const IDENT_CHECK = "\"" + IDENT + "\"";