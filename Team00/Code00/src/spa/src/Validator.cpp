//
// Created by Tin Hong Wen on 3/2/22.
//
#include <string>
#include<iostream>
#include <vector>

#include "Validator.h"
using namespace std;


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
bool Validator::checkParenthesesCorrectness(string code, string brackets) {
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

