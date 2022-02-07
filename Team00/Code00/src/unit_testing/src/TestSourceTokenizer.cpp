//
// Created by Tin Hong Wen on 6/2/22.
//

#include "SourceTokenizer.h"

#include "catch.hpp"

using namespace std;

TEST_CASE("assign token") {
    string a = "x = y + 1;";
    vector<string> v;
    SourceTokenizer::extractAssign(a, v);
}