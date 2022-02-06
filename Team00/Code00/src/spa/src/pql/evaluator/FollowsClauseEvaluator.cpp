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
    if (hasNoSynonyms()) {
        //resultBoolean = pkb->isFollows(argLeft.argumentValue, argRight.argumentValue);
        resultType = ResultType::BOOLEAN;
    }
    else if (hasTwoSynonyms()) {
        DesignEntity entityLeft = query->findEntityType(argLeft.argumentValue);
        DesignEntity entityRight = query->findEntityType(argRight.argumentValue);
        //resultItem = pkb->getAllFollows();
        resultBoolean = resultItem.empty();
        resultType = ResultType::TUPLES;
        resultHeader = tuple<string, string> { argLeft.argumentValue, argRight.argumentValue};
    }
    else if (leftIsSynonym()) {
        DesignEntity entityLeft = query->findEntityType(argLeft.argumentValue);
        //resultItem = pkb->getStmtFollowedBy(argRight.argumentValue);
        resultBoolean = resultItem.empty();
        resultType = ResultType::LIST;
        resultHeader = argLeft.argumentValue;
    }
    else //if (rightIsSynonym())
    {
        DesignEntity entityRight = query->findEntityType(argRight.argumentValue);
        //resultItem = pkb->getStmtFollows(argLeft.argumentValue);
        resultBoolean = resultItem.empty();
        resultType = ResultType::LIST;
        resultHeader = argRight.argumentValue;
    }

    return buildResult(resultType, resultBoolean, resultHeader, resultItem);
};