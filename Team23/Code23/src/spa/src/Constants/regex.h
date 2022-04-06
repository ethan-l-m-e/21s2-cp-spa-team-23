#pragma once
using namespace std;

// regex
const string LETTER = "[A-Za-z]";
string const DIGIT = "[0-9]";
string const NAME = "[A-Za-z][A-Za-z|0-9]*";
string const INTEGER = "[0-9]+";

string const NAME_W_SPACE = NAME + "( |\n|\t)*";
string const VAR_NAME = NAME_W_SPACE;
string const PROC_NAME = NAME_W_SPACE;
string const CONST_VALUE = INTEGER;

string const BASE_CASE_REGEX = VAR_NAME + "|" + PROC_NAME + "|" + CONST_VALUE;

string const COND_EXPR_IDENTIFIER = "( |\n|\t)*([!]?( |\n|\t)*[\\(]?(.|\n)*[(&&)(||)<>(>=)(<=)(==)(!=)](.|\n)*[\\)]?)";
string const EXPR_TERM_IDENTIFIER = "([^=;\\[\\]\\{\\}]*)[+-/*%]{1}([^=;\\[\\]\\{\\}]*)";
string const TERM_REGEX;
string const TERM_IDENTIFIER;


string const READ_REGEX = "^( |\n|\t)*(read)( |\n|\t)+(" + VAR_NAME +")( |\n|\t)*(;)(.*)";
string const PRINT_REGEX = "^( |\n|\t)*(print)( |\n|\t)+(" + VAR_NAME + ")( |\n|\t)*(;)(.*)";
string const CALL_REGEX = "^( |\n|\t)*(call)( |\n|\t)+(" + PROC_NAME + ")( |\n|\t)*(;)(.*)";

string const WHILE_IDENTIFIER = "^( |\n|\t)*(while)( |\n|\t)*(\\()" + COND_EXPR_IDENTIFIER + "( |\n|\t)*(\\))( |\n|\t)*(\\{)(.*)";
string const IF_IDENTIFIER  = "^( |\n|\t)*(if)( |\n|\t)*(\\()" + COND_EXPR_IDENTIFIER + "(\\))( |\n|\t)*(then)( |\n|\t)*(\\{)(.*)";


string const PROCEDURE_IDENTIFIER = "^( |\n|\t)*(procedure)( |\n|\t)+(" + PROC_NAME + ")( |\n|\t)*(\\{)(.*)" ;
string const ASSIGN_IDENTIFIER = "^( |\n|\t)*" + VAR_NAME + "( |\n|\t)*(=)( |\n|\t)*(" + EXPR_TERM_IDENTIFIER + "|"
        + "[\\(]*(" + BASE_CASE_REGEX + ")[\\)]*"
        + ")( |\n|\t)*(;)(.*)";

string const STMT_IDENTIFIER = "(" + PROCEDURE_IDENTIFIER + "|" + ASSIGN_IDENTIFIER + "|" + READ_REGEX + "|"
        + PRINT_REGEX + "|" + CALL_REGEX + "|" + WHILE_IDENTIFIER + "|" + IF_IDENTIFIER + "|^" + EXPR_TERM_IDENTIFIER
        + "|^" + COND_EXPR_IDENTIFIER + "|^" + VAR_NAME + "|^" + CONST_VALUE+ ")";