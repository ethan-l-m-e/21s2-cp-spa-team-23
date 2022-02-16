#pragma once
using namespace std;

// regex
const string LETTER = "[A-Za-z]";
string const DIGIT = "[0-9]";
string const NAME = "[A-Za-z][A-Za-z|0-9]*";
string const INTEGER = "[0-9]+";

string const NAME_W_SPACE = NAME + "[ ]*";
string const VAR_NAME = NAME_W_SPACE;
string const PROC_NAME = NAME_W_SPACE;
string const CONST_VALUE = INTEGER;

string const BASE_CASE_REGEX = VAR_NAME + "|" + PROC_NAME + "|" + CONST_VALUE;

string const COND_EXPR_REGEX;
string const COND_EXPR_IDENTIFIER = "([!]?[\\(]?(.*)[(&&)(||)<>(>=)(<=)(==)(!=)](.*)[\\)]?)";
string const EXPR_REGEX;
string const EXPR_TERM_IDENTIFIER = "([^=;\\[\\]\\{\\}]*)[+-/*]{1}([^=;\\[\\]\\{\\}]*)";
string const TERM_REGEX;
string const TERM_IDENTIFIER;
string const REL_FACTOR_REGEX;
string const FACTOR_REGEX;


//string const READ_REGEX = "(read )([A-Za-z][A-Za-z|0-9]*)(;)";
//string const PRINT_REGEX = "(print )(" + VAR_NAME + ")(;)";
string const READ_REGEX = "[ ]*(read )[ ]*(" + VAR_NAME +")[ ]*(;)[\\}]*";
string const PRINT_REGEX = "[ ]*(print )[ ]*(" + VAR_NAME + ")[ ]*(;)[\\}]*";


string const WHILE_IDENTIFIER = "(while)[ ]*(\\()" + COND_EXPR_IDENTIFIER + "(\\))[ ]*(\\{)(.*)";
string const IF_IDENTIFIER  = "(if)[ ]*(\\()" + COND_EXPR_IDENTIFIER + "(\\))[ ]* (then)[ ]*(\\{)(.*)";


string const PROCEDURE_IDENTIFIER = "(procedure )[ ]*(" + PROC_NAME + ")[ ]*(\\{)(.*)" ;
string const ASSIGN_IDENTIFIER = VAR_NAME + "[ ]*(=)[ ]*(" + EXPR_TERM_IDENTIFIER + "|" +  BASE_CASE_REGEX + ")(;)";

//char STMT_REGEX[200];    int s = sprintf(STMT_REGEX, "%s|%s|%s|%s|%s", READ_REGEX, PRINT_REGEX, ASSIGN_IDENTIFIER.c_str(), WHILE_REGEX, IF_ELSE_REGEX);   //not done
