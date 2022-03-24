//
// Created by Tin Hong Wen on 2/2/22.
//
#include <iostream>
#include <regex>
#include <vector>
#include <string>

#include "Identifier.h"
#include "Constants/regex.h"
#include "Constants/Constants.h"
#include "StringFormatter.h"

//bool checkParenthesesClosure(string code, string brackets);
int switchCaseOrError(int, bool);

int Identifier::identifyFirstObject(string sourceCode) {
    std::smatch sm;
//    std::string check = "while ((!(6 == 9)) || (4 == 2 + 2)) {\n                mu11 = mu12 * mu13;\n                m11 = u19 + u18;\n              }\n              if (72 * 1010101010101 >= u15)\n                then{\n                    mu19 = u19 + u18 + u17 / u16;\n                    mu19 = mu19+ 10;\n                    print u19;\n                    read m19;\n                }\n              else {\n                m17 = u17;\n                m18 = u18;\n                m15 = mu16 + mu17 + mu18 + mu19;\n              }\n              print mu11;\n              read m16;\n              read m12;";
//    std::regex_search (check, sm, std::regex(STMT_IDENTIFIER));
//    std::string check2 = sm[0];
    std::regex_search (sourceCode, sm, std::regex(STMT_IDENTIFIER));
    std::string firstLine = sm[0];
//    std::string check = "(((2 > 1) || (u21 < mu21))\n                || (((mu22 > u22) && (mu21 < u23)) && ((mu21) != (18 * (69) - (u24) / 2 + u21 % x2))))\n || (((mu21 > 22) && (3 < 5)) && ((8) != (8 * (8) - (16) / 2 + 16 % 2)))))";
//    std::string check2 = "\n\n    while ((((2 > 1) || (u21 < mu21))\n                || (((mu22 > u22) && (mu21 < u23)) && ((mu21) != (18 * (69) - (u24) / 2 + u21 % x2))))\n               &&  ((((x1 > x2) || (u21 < u24)))))\n  {";
//    bool result = std::regex_match(check, std::regex(COND_EXPR_IDENTIFIER));
    //    string firstLine = StringFormatter::extractFrontStringByRegex(sourceCode, "\n");
    firstLine = StringFormatter::removeTrailingSpace(firstLine);
    if (regex_match(firstLine, std::regex(PROCEDURE_IDENTIFIER))) {
        bool isCorrect = checkParenthesesClosure(sourceCode, "{}");
        return switchCaseOrError(PROCEDURE, isCorrect); //ignores stmtLst
    } else if (regex_match(firstLine, std::regex(ASSIGN_IDENTIFIER))) {
        return ASSIGN; // ignores EXPR_TERM
    } else if (regex_match(firstLine, std::regex(READ_REGEX))) {
        return READ; // done
    } else if (regex_match(firstLine, std::regex(PRINT_REGEX))) {
        return PRINT; // done
    } else if (regex_match(firstLine, std::regex(CALL_REGEX))) {
        return CALL;
    } else if (regex_match(firstLine, std::regex(WHILE_IDENTIFIER))) {
        bool isCorrect = checkParenthesesClosure(sourceCode, "()") && checkParenthesesClosure(sourceCode, "{}");
        return switchCaseOrError(WHILE, isCorrect); //ignores stmtLst
    } else if (regex_match(firstLine, std::regex(IF_IDENTIFIER))) {
        bool isCorrect = checkParenthesesClosure(sourceCode, "()") && checkParenthesesClosure(sourceCode, "{}");
        return switchCaseOrError(IF_ELSE, isCorrect); //ignores stmtLst
    } else if (regex_match(firstLine, std::regex(EXPR_TERM_IDENTIFIER))) {
        bool isCorrect = checkParenthesesClosure(sourceCode, "()");
        return switchCaseOrError(EXPR_TERM, isCorrect); //ignores stmtLst
    } else if (regex_match(firstLine, std::regex(COND_EXPR_IDENTIFIER))) {
        bool isCorrect = checkParenthesesClosure(sourceCode, "()");
        return switchCaseOrError(COND_EXPR, isCorrect);
    } else if (regex_match(firstLine, std::regex(VAR_NAME))) {
        return VARIABLE_NAME; // same as proc name
    }  else if (regex_match(firstLine, std::regex(CONST_VALUE))) {
        return CONSTANT_VALUE;
    } else {
        cout << "parser cannot identify '" + firstLine + "' in the source code\n";
        return ERROR;
    }
}


int switchCaseOrError(int switchCase, bool cond) {
    if (cond)  return switchCase;
    else return ERROR;
}

/**
 * IMPORTANT NOTE this algorithm DOES NOT CHECK:
 *
 * - brackets after closure
 * (e.g. '(x + 1) * (y - 1)'. does not check the latter brackets (y - 1))
 *
 * - other types of brackets other than the one specified
 * (e.g. '( ss {ddd) sss }'. this will be counted as correct by the algo, but it's obviously wrong
 *
 * these 2 problems shall be resolved by the main recursion in Parser.cpp by via gradual trimming/partitioning
 * e.g. 'procedure a {}} procedure b {}'
 * after trimming the correct portion of the code, left with '} procedure b {}'.
 * The stray '}' will throw an error during identification
 */
bool Identifier::checkParenthesesClosure(string code, string brackets) {
    int count = 0;
    bool startedCount = false;
    char bracketLeft = brackets[0];
    char bracketRight = brackets[1];
    for (int i = 0; i < code.size(); i++) {
        if (startedCount == true && count == 0) {
            return true;
        } else if (code[i]== bracketLeft) {
            startedCount = true;
            count++;
        } else if (code[i] == bracketRight) {
            startedCount = true;
            count--;
            if ( count < 0) {
                cout << "excessive " << bracketRight <<"\n";
                return false;
            }
        }
    }

    if (count > 0) {
        cout << "excessive " << bracketLeft << "\n";
        return false;
    } else if (count < 0) {
        cout << "excessive " << bracketRight << "\n";
        return false;
    } else {
        return true;
    }
}
/**
 * more accurate than checkParenthesesCorrectness. However usage is much more limited
 * @param code
 * @param brackets
 * @return
 */
bool Identifier::checkParenthesesCorrectness(string code, string brackets)  {
    int count = 0;
    char bracketLeft = brackets[0];
    char bracketRight = brackets[1];
    for (int i = 0; i < code.size(); i++) {
        if (code[i]== bracketLeft) {
            count++;
        } else if (code[i] == bracketRight) {
            count--;
            if ( count < 0) {
                cout << "excessive " << bracketRight <<"\n";
                return false;
            }
        }
    }

    if(count == 0) return true;
    else return false;
}