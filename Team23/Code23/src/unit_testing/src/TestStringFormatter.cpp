//
// Created by Tin Hong Wen on 7/2/22.
//



#include "StringFormatter.h"
#include "Constants/Constants.h"
#include <string>
#include <regex>
#include <iostream>
#include "catch.hpp"

using namespace std;

TEST_CASE("extract String ") {
    vector<string> arr = StringFormatter::tokenizeByRegex("Select v such that Uses(a,b)","[ ]*((Select[ ]*)|(such that[ ]*)|[\\(\\)\\,])[ ]*");
}

TEST_CASE("tokenize by regex") {
    string arg = "_\"This is an item\"_";
    vector<string> v = StringFormatter::tokenizeByRegex(arg, "_\"|\"_");
    CHECK(v[0] == "This is an item");
}