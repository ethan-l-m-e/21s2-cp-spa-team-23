#pragma once

// Regex for Lexical Tokens
std::string const LETTER = "[A-Za-z]";
std::string const DIGIT = "[0-9]";
std::string const NZDIGIT = "[1-9]";
std::string const IDENT = "[A-Za-z][A-Za-z|0-9]*";
std::string const NAME = "[A-Za-z][A-Za-z|0-9]*";
std::string const INTEGER = "(0|" + NZDIGIT + DIGIT + "*)";

std::string const SYNONYM = IDENT;
std::string const STMT_REF = "(" + SYNONYM + "|_|" + INTEGER + ")";
std::string const ENT_REF = "(" + SYNONYM + "|_|" + '"' + IDENT + '"' + ")";

std::string const ATTR_NAME = "(procName|varName|value|stmt#)";
std::string const ATTR_REF = SYNONYM + "\\." + ATTR_NAME;
std::string const ELEM = "(" + SYNONYM + "|" + ATTR_REF + ")";
std::string const REF = "(\"" + IDENT + "\"|" + INTEGER + "|" + ATTR_REF + ")";

// Grammar Rules
std::string const DESIGN_ENTITY = "(stmt|read|print|call|while|if|assign|variable|constant|procedure)";
std::string const DECLARATION = "( |\t)*" + DESIGN_ENTITY + "( |\t)+" + SYNONYM + "(,( |\t)*" + SYNONYM + "( |\t)*)*( |\t)*;";

std::string const TUPLE = "(( |\t)*" + ELEM + "|" + "( |\t)*<( |\t)*" + ELEM + "( |\t)*(( |\t)*,( |\t)*" + ELEM + "( |\t)*)*>)";
std::string const RESULT_CL = "(" + TUPLE + "|BOOLEAN)";

// Relationships
//std::string const REF = "(" + SYNONYM + "|_|" + INTEGER + "|\"" + IDENT + "\"" + ")";
//std::string const RELATIONSHIP = REL_REF + "\\([( |\t)]*" + REF + "[( |\t)]*,[( |\t)]*" + REF + "[( |\t)]*\\)";


std::string const FOLLOWS = "Follows( |\t)*\\(( |\t)*" + STMT_REF + "( |\t)*,( |\t)*" + STMT_REF + "( |\t)*\\)[( |\t)]*";
std::string const FOLLOWS_T = "Follows\\*[( |\t)]*\\([( |\t)]*" + STMT_REF + "[( |\t)]*,[( |\t)]*" + STMT_REF + "[( |\t)]*\\)[( |\t)]*";

std::string const PARENT = "Parent[( |\t)]*\\([( |\t)]*" + STMT_REF + "[( |\t)]*,[( |\t)]*" + STMT_REF + "[( |\t)]*\\)[( |\t)]*";
std::string const PARENT_T = "Parent\\*[( |\t)]*\\([( |\t)]*" + STMT_REF + "[( |\t)]*,[( |\t)]*" + STMT_REF + "[( |\t)]*\\)[( |\t)]*";

std::string const USES_S = "Uses[( |\t)]*\\([( |\t)]*" + STMT_REF + "[( |\t)]*,[( |\t)]*" + ENT_REF + "[( |\t)]*\\)[( |\t)]*";
std::string const USES_P = "Uses[( |\t)]*\\([( |\t)]*" + ENT_REF + "[( |\t)]*,[( |\t)]*" + ENT_REF + "[( |\t)]*\\)[( |\t)]*";

std::string const MODIFIES_S = "Modifies[( |\t)]*\\([( |\t)]*" + STMT_REF + "[( |\t)]*,[( |\t)]*" + ENT_REF + "[( |\t)]*\\)[( |\t)]*";
std::string const MODIFIES_P = "Modifies[( |\t)]*\\([( |\t)]*" + ENT_REF + "[( |\t)]*,[( |\t)]*" + ENT_REF + "[( |\t)]*\\)[( |\t)]*";

std::string const CALLS = "Calls[( |\t)]*\\([( |\t)]*" + ENT_REF + "[( |\t)]*,[( |\t)]*" + ENT_REF + "[( |\t)]*\\)[( |\t)]*";
std::string const CALLS_T = "Calls\\*[( |\t)]*\\([( |\t)]*" + ENT_REF + "[( |\t)]*,[( |\t)]*" + ENT_REF + "[( |\t)]*\\)[( |\t)]*";

std::string const NEXT = "Next[( |\t)]*\\([( |\t)]*" + STMT_REF + "[( |\t)]*,[( |\t)]*" + STMT_REF + "[( |\t)]*\\)[( |\t)]*";
std::string const NEXT_T = "Next\\*[( |\t)]*\\([( |\t)]*" + STMT_REF + "[( |\t)]*,[( |\t)]*" + STMT_REF + "[( |\t)]*\\)[( |\t)]*";

std::string const AFFECTS = "Affects[( |\t)]*\\([( |\t)]*" + STMT_REF + "[( |\t)]*,[( |\t)]*" + STMT_REF + "[( |\t)]*\\)[( |\t)]*";
std::string const AFFECTS_T = "Affects\\*[( |\t)]*\\([( |\t)]*" + STMT_REF + "[( |\t)]*,[( |\t)]*" + STMT_REF + "[( |\t)]*\\)[( |\t)]*";

std::string const REL_REF = "(" + FOLLOWS + "|" + FOLLOWS_T + "|" + PARENT + "|" + PARENT_T + "|" + USES_S + "|"
        + USES_P + "|" + MODIFIES_S + "|" + MODIFIES_P + "|" + CALLS + "|" + CALLS_T + "|" + NEXT + "|" + NEXT_T
        + "|" + AFFECTS + "|" + AFFECTS_T + ")";

std::string const REL_COND = REL_REF + "([( |\t)]+and[( |\t)]+" + REL_REF + ")*";

std::string const SUCH_THAT_CL = "such[( |\t)]+that[( |\t)]+" + REL_COND;

// pattern regex
std::string const EXPRESSION_SPEC = "(_|_\"(.)+\"_|\"(.)+\")";
std::string const ASSIGN = SYNONYM + "[( |\t)]*\\([( |\t)]*" + ENT_REF + "[( |\t)]*,[( |\t)]*" + EXPRESSION_SPEC
        + "[( |\t)]*\\)";
std::string const WHILE = SYNONYM + "[( |\t)]*\\([( |\t)]*" + ENT_REF + "[( |\t)]*,[( |\t)]*_[( |\t)]*\\)";
std::string const IF = SYNONYM + "[( |\t)]*\\([( |\t)]*" + ENT_REF + "[( |\t)]*,[( |\t)]*_[( |\t)]*,[( |\t)]*_[( |\t)]*\\)";
std::string const PATTERN = "(" + ASSIGN + "|" + WHILE + "|" + IF + ")";
std::string const PATTERN_COND = PATTERN + "[( |\t)]*(and[( |\t)]+" + PATTERN + "[( |\t)]*)*";
std::string const PATTERN_CL = "pattern[( |\t)]+" + PATTERN_COND + "[( |\t)]*";

// with regex
std::string const ATTR_COMPARE = REF + "[( |\t)]*=[( |\t)]*" + REF;
std::string const ATTR_COND = ATTR_COMPARE + "([( |\t)]+and[( |\t)]+" + ATTR_COMPARE + "[( |\t)]*)*";
std::string const WITH_CL = "( |\t)*with[( |\t)]+" + ATTR_COND;


std::string const SELECT_CL = "[( |\n|\t)]*Select[( |\n|\t)]+" + RESULT_CL + "([( |\t)]+" + SUCH_THAT_CL + "|[( |\t)]+"
        + PATTERN_CL + "|[( |\t)]+" + WITH_CL + "[( |\t)]*)*";
std::string const DECLARATION_REGEX = "([( |\n|\t)]*" + DECLARATION+ ")+";
std::string const PQL_FORMAT = DECLARATION_REGEX + "[( |\n|\t)]*" + SELECT_CL + "[( |\t|\n)]*";

// regex needed for semantic validation
std::string const STMT_RS = "(Follows|Follows\\*|Parent|Parent\\*|Next|Next\\*)";
std::string const VARIABLE_RS = "(Modifies|Uses)";
std::string const SYN_ARG = "(\"" + IDENT + "\"|_)";
std::string const IDENT_INT_CHECK = "(\"" + IDENT + "\"|[0-9]+)";
std::string const STMT_DESIGN_ENTITIES = "(read|print|call|while|if|assign|stmt)";

// regex strings for tokenizer
std::string const DECLARATIONS_LINE = "[ |\n|\t]*;[ |\n|\t]*(Select.*)";
std::string const SPLIT_DESIGN_ENTITIES = "[ |\t]*;[ |\t]*";
std::string const SPLIT_DECLARATIONS = "[ |\t]*,[ |\t]*";

std::string const SELECT_LINE = "(.*);[ |\n]*(Select[ ]+|[ ]+|(.*;))";
std::string const SUCH_THAT_CLAUSE = "(.)*such [ ]*that[ ]+";
std::string const SPLIT_SUCH_THAT_CLAUSE = "[ ]*[\\(\\),][ ]*";

std::string const PATTERN_LINE = "(.*)[ ]+pattern[ ]+";
std::string const REGEX_FOR_PATTERN_SYNONYM = "(.*)[ ]+pattern[ ]+" + SYNONYM + "[ ]*\\(";
std::string const PATTERN_ARGUMENTS = "(,|pattern)";
std::string const PATTERN_ARGUMENTS_MATCH = "[( |\t)]*\\([( |\t)]*" + ENT_REF + "[( |\t)]*,[( |\t)]*"
                                  + EXPRESSION_SPEC + "[( |\t)]*\\)";