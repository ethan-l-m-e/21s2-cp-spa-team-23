//
// Created by Tianyi Wang on 2/2/22.
//

#include "SuchThatClauseEvaluator.h"
Result SuchThatClauseEvaluator::evaluateClause(PKB* pkb,
unordered_map<string, DesignEntity> declarations){
    switch (relRef) {
        case RelRef::FOLLOWS:
            evaluateFollows(pkb, declarations);
            break;
        case RelRef::FOLLOWS_T:
            break;
        case RelRef::PARENT:
            break;
        case RelRef::PARENT_T:
            break;
        case RelRef::USES_S:
            break;
        case RelRef::USES_P:
            break;
        case RelRef::MODIFIES_S:
            break;
        case RelRef::MODIFIES_P:
            break;
    }
};

Result SuchThatClauseEvaluator::evaluateFollows(PKB* pkb,
                                                unordered_map<string, DesignEntity> declarations){
    Argument argLeft = argList[0];
    Argument argRight = argList[1];
    if (argLeft.argumentType == ArgumentType::SYNONYM) {
        DesignEntity entityLeft = findEntityType(argLeft.argumentValue);
        vector<Integer> l = pkb->getAllType(entityLeft);
        if (argRight.argumentType == ArgumentType::SYNONYM) {
            DesignEntity entityRight = findEntityType(argRight.argumentValue);

        } else if (argRight.argumentType == ArgumentType::STMT_NO) {

        } else (argRight.argumentType == ArgumentType::UNDERSCORE) {

        }
    } else if (argLeft.argumentType == ArgumentType::STMT_NO) {

    } else if (argLeft.argumentType == ArgumentType::UNDERSCORE) {

    }
};
Result SuchThatClauseEvaluator::evaluateFollowsT(){};
Result SuchThatClauseEvaluator::evaluateParent(){};
Result SuchThatClauseEvaluator::evaluateParentT(){};
Result SuchThatClauseEvaluator::evaluateModifiesS(){};
Result SuchThatClauseEvaluator::evaluateModifiesP(){};
Result SuchThatClauseEvaluator::evaluateUsesS(){};
Result SuchThatClauseEvaluator::evaluateUsesP(){};


optional<DesignEntity> findEntityType(std::string synonym) {
    auto got = declarations.find (synonym);
    if ( got == declarations.end() )
        return std::nullopt;
    else
        return got->second;
}