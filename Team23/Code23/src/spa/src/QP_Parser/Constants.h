#pragma once

// Regex for Lexical Tokens
std::string const LETTER = "[A-Za-z]";
std::string const DIGIT = "[0-9]";
std::string const NZDIGIT = "[1-9]";
std::string const IDENT = "[A-Za-z][A-Za-z|0-9]*";
std::string const NAME = "[A-Za-z][A-Za-z|0-9]*";
std::string const INTEGER = "(0|" + NZDIGIT + DIGIT + "*)";
std::string const SPACE_TAB = "( |\t)*";
std::string const SINGLE_SPACE_TAB = "( |\t)+";

std::string const SYNONYM = IDENT;
std::string const STMT_REF = "(" + SYNONYM + "|_|" + INTEGER + ")";
std::string const ENT_REF = "(" + SYNONYM + "|_|" + '"' + IDENT + '"' + ")";

std::string const ATTR_NAME = "(procName|varName|value|stmt#)";
std::string const ATTR_REF = SYNONYM + SPACE_TAB + "\\." + SPACE_TAB + ATTR_NAME;
std::string const ELEM = "(" + SYNONYM + "|" + ATTR_REF + ")";
std::string const REF = "(\"" + IDENT + "\"|" + INTEGER + "|" + ATTR_REF + ")";

// Grammar Rules
std::string const DESIGN_ENTITY = "(stmt|read|print|call|while|if|assign|variable|constant|procedure)";
std::string const DECLARATION = SPACE_TAB + DESIGN_ENTITY + SINGLE_SPACE_TAB + SYNONYM + "(," + SPACE_TAB + SYNONYM
        + SPACE_TAB + ")*" + SPACE_TAB + ";";

std::string const TUPLE = "(" + SPACE_TAB + ELEM + "|" + SPACE_TAB + "<"+ SPACE_TAB + ELEM + SPACE_TAB + "("
        + SPACE_TAB + "," + SPACE_TAB + ELEM + SPACE_TAB + ")*>)";
std::string const RESULT_CL = "(" + TUPLE + "|BOOLEAN)";

// Relationships
std::string const FOLLOWS = "Follows" + SPACE_TAB + "\\(" + SPACE_TAB + STMT_REF + SPACE_TAB + "," + SPACE_TAB
        + STMT_REF + SPACE_TAB + "\\)" + SPACE_TAB;
std::string const FOLLOWS_T = "Follows\\*" + SPACE_TAB + "\\(" + SPACE_TAB + STMT_REF + SPACE_TAB + "," + SPACE_TAB
        + STMT_REF + SPACE_TAB + "\\)" + SPACE_TAB;

std::string const PARENT = "Parent" + SPACE_TAB + "\\(" + SPACE_TAB + STMT_REF + SPACE_TAB + "," + SPACE_TAB
        + STMT_REF + SPACE_TAB + "\\)" + SPACE_TAB;
std::string const PARENT_T = "Parent\\*" + SPACE_TAB + "\\(" + SPACE_TAB + STMT_REF + SPACE_TAB + "," + SPACE_TAB
        + STMT_REF + SPACE_TAB + "\\)" + SPACE_TAB;

std::string const USES_S = "Uses" + SPACE_TAB + "\\(" + SPACE_TAB + STMT_REF + SPACE_TAB + "," + SPACE_TAB + ENT_REF
        + SPACE_TAB + "\\)" + SPACE_TAB;
std::string const USES_P = "Uses" + SPACE_TAB + "\\(" + SPACE_TAB + ENT_REF + SPACE_TAB + "," + SPACE_TAB + ENT_REF
        + SPACE_TAB + "\\)" + SPACE_TAB;

std::string const MODIFIES_S = "Modifies" + SPACE_TAB + "\\(" + SPACE_TAB + STMT_REF + SPACE_TAB + "," + SPACE_TAB
        + ENT_REF + SPACE_TAB + "\\)" + SPACE_TAB;
std::string const MODIFIES_P = "Modifies" + SPACE_TAB + "\\(" + SPACE_TAB + ENT_REF + SPACE_TAB + "," + SPACE_TAB
        + ENT_REF + SPACE_TAB + "\\)" + SPACE_TAB;

std::string const CALLS = "Calls" + SPACE_TAB + "\\(" + SPACE_TAB + ENT_REF + SPACE_TAB + "," + SPACE_TAB + ENT_REF
        + SPACE_TAB + "\\)" + SPACE_TAB;
std::string const CALLS_T = "Calls\\*" + SPACE_TAB + "\\(" + SPACE_TAB + ENT_REF + SPACE_TAB + "," + SPACE_TAB
        + ENT_REF + SPACE_TAB + "\\)" + SPACE_TAB;

std::string const NEXT = "Next" + SPACE_TAB + "\\(" + SPACE_TAB + STMT_REF + SPACE_TAB + "," + SPACE_TAB + STMT_REF
        + SPACE_TAB + "\\)" + SPACE_TAB;
std::string const NEXT_T = "Next\\*" + SPACE_TAB + "\\(" + SPACE_TAB + STMT_REF + SPACE_TAB + "," + SPACE_TAB + STMT_REF
                           + SPACE_TAB + "\\)" + SPACE_TAB;

std::string const AFFECTS = "Affects" + SPACE_TAB + "\\(" + SPACE_TAB + STMT_REF + SPACE_TAB + "," + SPACE_TAB
        + STMT_REF + SPACE_TAB + "\\)" + SPACE_TAB;
std::string const AFFECTS_T = "Affects\\*" + SPACE_TAB + "\\(" + SPACE_TAB + STMT_REF + SPACE_TAB + "," + SPACE_TAB
                              + STMT_REF + SPACE_TAB + "\\)" + SPACE_TAB;

std::string const REL_REF = "(" + FOLLOWS + "|" + FOLLOWS_T + "|" + PARENT + "|" + PARENT_T + "|" + USES_S + "|"
        + USES_P + "|" + MODIFIES_S + "|" + MODIFIES_P + "|" + CALLS + "|" + CALLS_T + "|" + NEXT + "|" + NEXT_T
        + "|" + AFFECTS + "|" + AFFECTS_T + ")";

std::string const REL_COND = REL_REF + "(" + SINGLE_SPACE_TAB + "and" + SINGLE_SPACE_TAB + REL_REF + ")*";

std::string const SUCH_THAT_CL = "such" + SINGLE_SPACE_TAB + "that" + SINGLE_SPACE_TAB + REL_COND;

// pattern regex
std::string const EXPRESSION_SPEC = "(_|_\"(.)+\"_|\"(.)+\")";
std::string const ASSIGN = SYNONYM + SPACE_TAB + "\\(" + SPACE_TAB + ENT_REF + SPACE_TAB + "," + SPACE_TAB
        + EXPRESSION_SPEC + SPACE_TAB + "\\)";
std::string const WHILE = SYNONYM + SPACE_TAB + "\\(" + SPACE_TAB + ENT_REF + SPACE_TAB + "," + SPACE_TAB + "_"
        + SPACE_TAB + "\\)";
std::string const IF = SYNONYM + SPACE_TAB + "\\(" + SPACE_TAB + ENT_REF + SPACE_TAB + "," + SPACE_TAB + "_"
        + SPACE_TAB + "," + SPACE_TAB + "_" + SPACE_TAB + "\\)";
std::string const PATTERN = "(" + ASSIGN + "|" + WHILE + "|" + IF + ")";
std::string const PATTERN_COND = PATTERN + SPACE_TAB + "(and" + SINGLE_SPACE_TAB + PATTERN + SPACE_TAB + ")*";
std::string const PATTERN_CL = "pattern" + SINGLE_SPACE_TAB + PATTERN_COND + SPACE_TAB;

// with regex
std::string const ATTR_COMPARE = REF + SPACE_TAB + "=" + SPACE_TAB + REF;
std::string const ATTR_COND = ATTR_COMPARE + "(" + SINGLE_SPACE_TAB + "and" + SINGLE_SPACE_TAB + ATTR_COMPARE
        + SPACE_TAB + ")*";
std::string const WITH_CL = SPACE_TAB + "with" + SINGLE_SPACE_TAB + ATTR_COND;


std::string const SELECT_CL = "( |\n|\t)*Select( |\n|\t)+" + RESULT_CL + "(" + SINGLE_SPACE_TAB + SUCH_THAT_CL
        + "|" + SINGLE_SPACE_TAB + PATTERN_CL + "|" + SINGLE_SPACE_TAB + WITH_CL + SPACE_TAB + ")*";
std::string const DECLARATION_REGEX = "(( |\n|\t)*" + DECLARATION+ ")+";
std::string const PQL_FORMAT = DECLARATION_REGEX + "( |\n|\t)*" + SELECT_CL + "( |\t|\n)*";

// regex needed for semantic validation
std::string const STMT_RS = "(Follows|Follows\\*|Parent|Parent\\*|Next|Next\\*)";
std::string const VARIABLE_RS = "(Modifies|Uses)";
std::string const CALLS_RS = "(Calls|Calls\\*)";
std::string const PATTERN_SYNONYMS = "(if|while|assign)";
std::string const SYN_ARG = "(\"" + IDENT + "\"|_)";
std::string const INT_WILDCARD = "(_|" + INTEGER + ")";
std::string const IDENT_INT_CHECK = "(\"" + IDENT + "\"|" + INTEGER + ")";
std::string const STMT_DESIGN_ENTITIES = "(read|print|call|while|if|assign|stmt)";

// regex strings for tokenizer
std::string const DECLARATIONS_LINE = "( |\n|\t)*;( |\n|\t)*(Select.*)";
std::string const SPLIT_DESIGN_ENTITIES = SPACE_TAB + ";" + SPACE_TAB;
std::string const SPACE_OR_COMMA = "(" + SINGLE_SPACE_TAB + "|,)";

std::string const SPLIT_SELECT_SYNONYM = "Select" + SINGLE_SPACE_TAB;
std::string const SELECT_SPACE_ANGLE_BRACKETS = "([ |\t]+|<|>)";

std::string const SPLIT_SUCH_THAT_CLAUSE = "[ ]*[\\(\\),][ ]*";

std::string const FIND_PATTERN = "pattern[ |\t]*" + PATTERN;
std::string const PATTERN_ARGUMENTS = ",";

std::string const SPLIT_WITH_CL = "[ |\\t]*(with|and)[ |\\t]*";
std::string const SPLIT_EQUALS = "\"[ |\\\\t]*=[ |\\\\t]*\"";

int const PATTERN_LENGTH = 7;
int const SELECT_LENGTH = 6;