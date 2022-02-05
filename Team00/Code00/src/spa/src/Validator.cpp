//
// Created by Tin Hong Wen on 3/2/22.
//
#include <string>
#include<iostream>
#include <vector>

#include "Validator.h"
using namespace std;

void splitString(string s, vector<string> &v){
    string temp = "";
    for(int i=0;i<s.length();++i){

        if(s[i]==' ' || s[i] == '\n'){
            v.push_back(temp);
            temp = "";
        }
        else{
            temp.push_back(s[i]);
        }
    }
    v.push_back(temp);
}

bool Validator::checkParenthesesCorrectness(string code, string brackets) {
    int count = 0;
    bool startedCount = false;
    char bracketLeft = brackets[0];
    char bracketRight = brackets[1];
    vector<string> stringArr;
    splitString(code, stringArr);
    for (int i = 0; i < stringArr.size(); i++) {
        if (startedCount == true && count == 0) {
            cout << "bracket syntax correct\n";
            return true;
        } else if (stringArr[i].find(bracketLeft) != string::npos) {
            startedCount = true;
            count++;
        } else if (stringArr[i].find(bracketRight) != string::npos) {
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
    } else if (count == 0) {
        return true;
    }
}

