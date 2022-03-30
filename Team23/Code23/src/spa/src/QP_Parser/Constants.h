#pragma once

// Regex for Lexical Tokens
std::string const LETTER = "[A-Za-z]";
std::string const DIGIT = "[0-9]";
std::string const NZDIGIT = "[1-9]";
std::string const IDENT = "[A-Za-z][A-Za-z|0-9]*";
std::string const NAME = "[A-Za-z][A-Za-z|0-9]*";
std::string const INTEGER = "(0|" + NZDIGIT + DIGIT + "*)";
std::string const SPACE = "( )*";
std::string const SINGLE_SPACE = "( )";

std::string const SYNONYM = IDENT;
std::string const STMT_REF = "(" + SYNONYM + "|_|" + INTEGER + ")";
std::string const ENT_REF = "(" + SYNONYM + "|_|" + '"' + IDENT + '"' + ")";

std::string const ATTR_NAME = "(procName|varName|value|stmt#)";
std::string const ATTR_REF = SYNONYM + SPACE + "\\." + SPACE + ATTR_NAME;
std::string const ELEM = "(" + ATTR_REF + "|" + SYNONYM + ")";
std::string const REF = "(\"" + IDENT + "\"|" + INTEGER + "|" + ATTR_REF + ")";

std::string const REL = "(Follows\\*|Parent\\*|Calls\\*|Next\\*|Affects\\*)";
std::string const LEXICAL_TOKENS = "^(" + REL + "|\\(|\\)|<|>|,|=|;|\\.|" + ATTR_NAME + "|" + SYNONYM + "|" + NAME
        + "|" + INTEGER + "|" + STMT_REF + "|" + ENT_REF + ")";

// Grammar Rules
std::string const DESIGN_ENTITY = "(stmt|read|print|call|while|if|assign|variable|constant|procedure)";
std::string const DECLARATION = SPACE + DESIGN_ENTITY + SINGLE_SPACE + SYNONYM + SPACE + "(," + SPACE
                                + SYNONYM + SPACE + ")*" + SPACE + ";";

std::string const TUPLE = "(" + SPACE + ELEM + "|" + SPACE + "<" + SPACE + ELEM + SPACE + "("
                          + SPACE + "," + SPACE + ELEM + SPACE + ")*>)";
std::string const RESULT_CL = "(" + TUPLE + "|BOOLEAN)";

// Relationships
std::string const FOLLOWS = "Follows" + SPACE + "\\(" + SPACE + STMT_REF + SPACE + "," + SPACE
                            + STMT_REF + SPACE + "\\)";
std::string const FOLLOWS_T = "Follows\\*" + SPACE + "\\(" + SPACE + STMT_REF + SPACE + "," + SPACE
                              + STMT_REF + SPACE + "\\)";

std::string const PARENT = "Parent" + SPACE + "\\(" + SPACE + STMT_REF + SPACE + "," + SPACE
                           + STMT_REF + SPACE + "\\)";
std::string const PARENT_T = "Parent\\*" + SPACE + "\\(" + SPACE + STMT_REF + SPACE + "," + SPACE
                             + STMT_REF + SPACE + "\\)";

std::string const USES_S = "Uses" + SPACE + "\\(" + SPACE + STMT_REF + SPACE + "," + SPACE + ENT_REF
                           + SPACE + "\\)";
std::string const USES_P = "Uses" + SPACE + "\\(" + SPACE + ENT_REF + SPACE + "," + SPACE + ENT_REF
                           + SPACE + "\\)";

std::string const MODIFIES_S = "Modifies" + SPACE + "\\(" + SPACE + STMT_REF + SPACE + "," + SPACE
                               + ENT_REF + SPACE + "\\)";
std::string const MODIFIES_P = "Modifies" + SPACE + "\\(" + SPACE + ENT_REF + SPACE + "," + SPACE
                               + ENT_REF + SPACE + "\\)";

std::string const CALLS = "Calls" + SPACE + "\\(" + SPACE + ENT_REF + SPACE + "," + SPACE + ENT_REF
                          + SPACE + "\\)";
std::string const CALLS_T = "Calls\\*" + SPACE + "\\(" + SPACE + ENT_REF + SPACE + "," + SPACE
                            + ENT_REF + SPACE + "\\)";

std::string const NEXT = "Next" + SPACE + "\\(" + SPACE + STMT_REF + SPACE + "," + SPACE + STMT_REF
                         + SPACE + "\\)";
std::string const NEXT_T = "Next\\*" + SPACE + "\\(" + SPACE + STMT_REF + SPACE + "," + SPACE + STMT_REF
                           + SPACE + "\\)";

std::string const AFFECTS = "Affects" + SPACE + "\\(" + SPACE + STMT_REF + SPACE + "," + SPACE
                            + STMT_REF + SPACE + "\\)";
std::string const AFFECTS_T = "Affects\\*" + SPACE + "\\(" + SPACE + STMT_REF + SPACE + "," + SPACE
                              + STMT_REF + SPACE + "\\)";

std::string const REL_REF = "(" + FOLLOWS + "|" + FOLLOWS_T + "|" + PARENT + "|" + PARENT_T + "|" + USES_S + "|"
        + USES_P + "|" + MODIFIES_S + "|" + MODIFIES_P + "|" + CALLS + "|" + CALLS_T + "|" + NEXT + "|" + NEXT_T
        + "|" + AFFECTS + "|" + AFFECTS_T + ")";

std::string const REL_COND = REL_REF + "(" + SINGLE_SPACE + "and" + SINGLE_SPACE + REL_REF + ")*";

std::string const SUCH_THAT_CL = "such" + SINGLE_SPACE + "that" + SINGLE_SPACE + REL_COND;

// pattern regex
std::string const EXPRESSION_SPEC = "(_|_" + SPACE + "\"(.)+\"" + SPACE + "_|\"(.)+\")";
std::string const ASSIGN = SYNONYM + SPACE + "\\(" + SPACE + ENT_REF + SPACE + "," + SPACE
                           + EXPRESSION_SPEC + SPACE + "\\)";
std::string const WHILE = SYNONYM + SPACE + "\\(" + SPACE + ENT_REF + SPACE + "," + SPACE + "_"
                          + SPACE + "\\)";
std::string const IF = SYNONYM + SPACE + "\\(" + SPACE + ENT_REF + SPACE + "," + SPACE + "_"
                       + SPACE + "," + SPACE + "_" + SPACE + "\\)";
std::string const PATTERN = "(" + ASSIGN + "|" + WHILE + "|" + IF + ")";
std::string const PATTERN_COND = PATTERN + "(" + SINGLE_SPACE + "and" + SINGLE_SPACE + PATTERN + ")*";
std::string const PATTERN_CL = "pattern" + SINGLE_SPACE + PATTERN_COND;

// with regex
std::string const ATTR_COMPARE = REF + SPACE + "=" + SPACE + REF;
std::string const ATTR_COND = ATTR_COMPARE + "(" + SINGLE_SPACE + "and" + SINGLE_SPACE + ATTR_COMPARE
                              + ")*";
std::string const WITH_CL = SPACE + "with" + SINGLE_SPACE + ATTR_COND;


std::string const SELECT_CL = SPACE + "Select" + SINGLE_SPACE + RESULT_CL + "(" + SINGLE_SPACE + SUCH_THAT_CL
                              + "|" + SINGLE_SPACE + PATTERN_CL + "|" + SINGLE_SPACE + WITH_CL + ")*" + SPACE;
std::string const DECLARATION_REGEX = "(" + SPACE + DECLARATION + ")+";
std::string const PQL_FORMAT = DECLARATION_REGEX + SELECT_CL + SPACE;

// regex needed for semantic validation
std::string const STMT_RS = "(Follows|Follows\\*|Parent|Parent\\*|Next|Next\\*)";
std::string const VARIABLE_RS = "(Modifies|Uses)";
std::string const CALLS_RS = "(Calls|Calls\\*)";
std::string const PATTERN_SYNONYMS = "(if|while|assign)";
std::string const INT_WILDCARD = "(_|" + INTEGER + ")";
std::string const IDENT_INT_CHECK = "(\"" + IDENT + "\"|" + INTEGER + ")";
std::string const STMT_DESIGN_ENTITIES = "(read|print|call|while|if|assign|stmt)";

// regex strings for tokenizer
std::string const DECLARATIONS_LINE = "( )*;( )*(Select.*)";
std::string const SPLIT_DESIGN_ENTITIES = SPACE + ";" + SPACE;
std::string const SPACE_OR_COMMA = "(" + SINGLE_SPACE + "|,)";

std::string const SPLIT_SELECT_SYNONYM = "Select" + SINGLE_SPACE;
std::string const SELECT_SPACE_ANGLE_BRACKETS = "([ ]+|<|>)";

std::string const SPLIT_SUCH_THAT_CLAUSE = "[ ]*[\\(\\),][ ]*";
std::string const PATTERN_ARGUMENTS = ",";

std::string const EQUALS = "=";
std::string const WHITESPACE_START = "^\\s+";
std::string const WHITESPACE = "\\s+";
std::string const CLAUSES = "(^" + SUCH_THAT_CL + "|^" + PATTERN_CL + "|^" + WITH_CL + ")";

int const SELECT_LENGTH = 6;