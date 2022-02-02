//
// Created by Tianyi Wang on 2/2/22.
//

#include "SuchThatClause.h"
Class
Result SuchThatClause::evaluateClause(){
    switch (relRef) {
        case RelRef::FOLLOWS:
            evaluateFollows();
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

Result SuchThatClause::evaluateFollows(){
    Argument argLeft = argList[0];
    Argument argRight = argList[1];
    if (argLeft.argumentType == ArgumentType::SYNONYM) {
        argLeft.argumentValue
        if (argRight.argumentType == ArgumentType::SYNONYM) {
            for ( : declarations) {

            }
        } else if (argRight.argumentType == ArgumentType::STMT_NO) {

        } else (argRight.argumentType == ArgumentType::UNDERSCORE) {

        }
    } else if (argLeft.argumentType == ArgumentType::STMT_NO) {

    } else if (argLeft.argumentType == ArgumentType::UNDERSCORE) {

    }
};
Result SuchThatClause::evaluateFollowsT(){};
Result SuchThatClause::evaluateParent(){};
Result SuchThatClause::evaluateParentT(){};
Result SuchThatClause::evaluateModifiesS(){};
Result SuchThatClause::evaluateModifiesP(){};
Result SuchThatClause::evaluateUsesS(){};
Result SuchThatClause::evaluateUsesP(){};

auto Utility::(const std::string &name)
{
    HandleMap::iterator it = pHandles.find(name);

    if (it != pHandles.end())
        return it->first;
    return -1;
}
