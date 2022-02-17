//
// Created by Tin Hong Wen on 11/2/22.
//

#include "catch.hpp"
#include "pql/ClauseEvaluators/PatternClauseEvaluator.h"
#include "TNode.h"
#include "Parser.h"
#include <vector>

using namespace std;

TEST_CASE("PATTERN METHODS MATCHING TEST") {
    // build vector of assigns without PKB
    AssignNode* assignNode1 = Parser::parseAssign("x = x + 1");
    AssignNode* assignNode2 = Parser::parseAssign("y = (x + 1) + y");
    AssignNode* assignNode3 = Parser::parseAssign("z = y");

    vector<AssignNode*> v;
    v.push_back(assignNode1);
    v.push_back(assignNode2);
    v.push_back(assignNode3);

    /**
     * For testing the most critical part of the code that involves matching
     * Only open if want to individually test the helper methods, since the methods are abstracted
     * away as private methods within patternClause
     * */

    /*
    Argument leftArgIdent = {.argumentType = ArgumentType::IDENT, .argumentValue = "x"};
    CHECK(PatternClauseEvaluator::matchLHSValue(assignNode1, leftArgIdent));
    CHECK(!PatternClauseEvaluator::matchLHSValue(assignNode2, leftArgIdent));

    Argument rightArgPartial = {.argumentType = ArgumentType::PARTIAL_UNDERSCORE, .argumentValue = "_\"x\"_"};
    CHECK(PatternClauseEvaluator::matchRHSValue(assignNode1, rightArgPartial));
    CHECK(PatternClauseEvaluator::matchRHSValue(assignNode2, rightArgPartial));
    CHECK(!PatternClauseEvaluator::matchRHSValue(assignNode3, rightArgPartial));
    */

    //PatternClauseEvaluator::
}

TEST_CASE("EVALUATION TEST") {

}