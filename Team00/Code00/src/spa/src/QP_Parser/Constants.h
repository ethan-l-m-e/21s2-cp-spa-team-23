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
std::string const DECLARATION = DESIGN_ENTITY + "[ ]+" + SYNONYM + "(,[ ]*" + SYNONYM + "[ ]*)*;";


// Relationships
std::string const REF = "(" + SYNONYM + "|_|" + INTEGER + "|\"" + IDENT + "\"" + ")";
std::string const REL_REF = "(Follows|Follows*|Parent|Parent*|Uses|Modifies)";
std::string const RELATIONSHIP = REL_REF + "\\([ ]*" + REF + "[ ]*,[ ]*" + REF + "[ ]*\\)";
std::string const RELATIONSHIP_MATCH = "(.)*" + RELATIONSHIP + "(.)*";

// TODO: Edit Later
std::string const FOLLOWS = "Follows\\([ ]*" + STMT_REF + "[ ]*,[ ]*" + STMT_REF + "[ ]*\\)";
std::string const FOLLOWS_T = "Follows\\*\\([ ]*" + STMT_REF + "[ ]*,[ ]*" + STMT_REF + "[ ]*\\)";

std::string const PARENT = "Parent\\([ ]*" + STMT_REF + "[ ]*,[ ]*" + STMT_REF + "[ ]*\\)";
std::string const PARENT_T = "Parent\\*\\([ ]*" + STMT_REF + "[ ]*,[ ]*" + STMT_REF + "[ ]*\\)";

std::string const USES_S = "Uses\\([ ]*" + STMT_REF + "[ ]*,[ ]*" + ENT_REF + "[ ]*\\)";
std::string const USES_P = "Uses\\([ ]*" + ENT_REF + "[ ]*,[ ]*" + ENT_REF + "[ ]*\\)";

std::string const MODIFIES_S = "Modifies\\([ ]*" + STMT_REF + "[ ]*,[ ]*" + ENT_REF + "[ ]*\\)";
std::string const MODIFIES_P = "Modifies\\([ ]*" + ENT_REF + "[ ]*,[ ]*" + ENT_REF + "[ ]*\\)";

std::string const SUCH_THAT_CL = "such[ ]+that[ ]+(" + FOLLOWS + "|" + FOLLOWS_T + "|" + PARENT + "|" + PARENT_T
                                 + "|" + USES_S + "|" + USES_P + "|" + MODIFIES_S + "|" + MODIFIES_P + ")";

// pattern regex
std::string const EXPRESSION_SPEC = "(_|_\"(.)*\"_|\"(.)*\")";
std::string const PATTERN_CL = "pattern[ ]+" + SYNONYM + "[ ]*\\([ ]*" + ENT_REF + "[ ]*,[ ]*"
        + EXPRESSION_SPEC + "\\)";
std::string const PATTERN_MATCH = "(.)*" + PATTERN_CL + "(.)*";


std::string const SELECT_CL = "[ |\n]*Select[ ]+" + SYNONYM + "([ ]+" + SUCH_THAT_CL + "|[ ]+" + PATTERN_CL + ")*";
std::string const DECLARATION_REGEX = "([ |\n]*" + DECLARATION+ ")+";
std::string const PQL_FORMAT = DECLARATION_REGEX + "[ |\n]+" + SELECT_CL;