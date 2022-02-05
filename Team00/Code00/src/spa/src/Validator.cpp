//
// Created by Tin Hong Wen on 3/2/22.
//
#include <string>
#include<iostream>
#include <vector>

#include "Validator.h"
using namespace std;

bool Validator::checkParenthesesCorrectness(string code, string brackets) {
    int count = 0;
    bool startedCount = false;
    char bracketLeft = brackets[0];
    char bracketRight = brackets[1];
    for (int i = 0; i < code.size(); i++) {
        if (startedCount == true && count == 0) {
            cout << "bracket syntax correct\n";
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
        cout << "bracket syntax correct\n";
        return true;
    }
}

