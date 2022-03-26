#pragma once
using namespace std;

// switch statements
int const BASE_CASE = 0;
int const PROCEDURE = 1;
int const ASSIGN = 2;
int const ERROR = 3;
int const WHILE = 4;
int const IF_ELSE = 5;
int const READ = 6;
int const OPERATOR = 7;
int const PRINT = 8;
int const CALL = 9;
int const COND_EXPR = 10;
int const EXPR_TERM = 11;
int const VARIABLE_NAME = 12;
int const PROCEDURE_NAME = VARIABLE_NAME;
int const CONSTANT_VALUE = 14;
int const STMT_LIST = ASSIGN;

// length of stmts
int const CALL_SIZE = 4;
int const READ_SIZE = 4;
int const PRINT_SIZE = 5;
int const WHILE_SIZE = 5;

string const EMPTY = "";