//
// Created by Tin Hong Wen on 7/2/22.
//



#include "StringFormatter.h"
#include <string>
#include <regex>
#include "catch.hpp"

using namespace std;

TEST_CASE("extract String ") {
    vector<string> arr = StringFormatter::tokenizeByRegex("Select v such that Uses(a,b)",
                                                          "[ ]*((Select[ ]*)|(such that[ ]*)|[\\(\\)\\,])[ ]*");
}