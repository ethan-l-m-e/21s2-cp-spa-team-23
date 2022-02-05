//
// Created by Tianyi Wang on 5/2/22.
//

#include "FollowsClauseEvaluator.h"

Result FollowsClauseEvaluator::evaluateClause(){
    Argument argLeft = argList[0];
    Argument argRight = argList[1];
    if (argLeft.argumentType == ArgumentType::SYNONYM) {
        DesignEntity entityLeft = findEntityType(argLeft.argumentValue);
        vector<int> l = pkb->getAllType(entityLeft);
        if (argRight.argumentType == ArgumentType::SYNONYM) {
            DesignEntity entityRight = findEntityType(argRight.argumentValue);

        } else if (argRight.argumentType == ArgumentType::STMT_NO) {

        } else (argRight.argumentType == ArgumentType::UNDERSCORE) {

        }
    } else if (argLeft.argumentType == ArgumentType::STMT_NO) {

    } else if (argLeft.argumentType == ArgumentType::UNDERSCORE) {

    }
};