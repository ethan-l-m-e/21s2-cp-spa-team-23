//
// Created by Tianyi Wang on 5/2/22.
//

#include "FollowsClauseEvaluator.h"

Result FollowsClauseEvaluator::evaluateClause(){
    Argument argLeft = argList[0];
    Argument argRight = argList[1];
    ResultType resultType;
    ResultHeader resultHeader;
    vector<ResultItem> resultItem;
    bool resultBoolean;
    if (hasNoSynonym()) {
        //resultBoolean = pkb->isFollows(argLeft.argumentValue, argRight.argumentValue);
        resultType = ResultType::BOOLEAN;
    }
    else if (hasTwoSynonyms()) {
        DesignEntity entityLeft = query->findEntityType(argLeft.argumentValue);
        DesignEntity entityRight = query->findEntityType(argRight.argumentValue);
        unordered_set<std::string> leftSet = getAllType(entityLeft);
        unordered_set<std::string> rightSet = getAllType(entityRight);
        resultType = ResultType::TUPLES;
        resultItem = generateTuples(leftSet, rightSet);
        resultBoolean = !resultItem.empty();
        resultHeader = tuple<string, string> { argLeft.argumentValue, argRight.argumentValue};
    }
    else if (hasLeftSynonym()) {
        DesignEntity entityLeft = query->findEntityType(argLeft.argumentValue);
        //resultItem = pkb->getStmtFollowedBy(argRight.argumentValue);
        resultBoolean = !resultItem.empty();
        resultType = ResultType::LIST;
        resultHeader = argLeft.argumentValue;
    }
    else if (hasRightSynonym()) {
        DesignEntity entityRight = query->findEntityType(argRight.argumentValue);
        //resultItem = pkb->getStmtFollows(argLeft.argumentValue);
        resultBoolean = !resultItem.empty();
        resultType = ResultType::LIST;
        resultHeader = argRight.argumentValue;
    }

    return buildResult(resultType, resultBoolean, resultHeader, resultItem);
};

std::vector<ResultItem> FollowsClauseEvaluator::generateTuples(unordered_set<std::string>& leftSet, unordered_set<std::string>& rightSet) {
    std::vector<ResultItem> tuples = std::vector<ResultItem>{};
    for (auto left = leftSet.begin(); left != leftSet.end(); ++left) {
        /* ... process *itr ...
        unordered_set<std::string> follows = pkb->getStmtFollows(left);
        for (const auto & follow : follows) {
            if (rightSet.find(follow) != rightSet.end()) {
                tuples.emplace_back(std::tuple<string, string>(*left, follow));
            }
        }
         */
    }
    return tuples;
};