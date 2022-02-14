//
// Created by Tianyi Wang on 9/2/22.
//

#include "SuchThatClauseEvaluator.h"

Result SuchThatClauseEvaluator::evaluateClause(){
    switch(getClauseSynonymType()){
        case ClauseSynonymType::SYNONYM_NONE:
            evaluateNoSynonym();
            break;
        case ClauseSynonymType::SYNONYM_LEFT:
            evaluateLeftSynonym();
            break;
        case ClauseSynonymType::SYNONYM_RIGHT:
            evaluateRightSynonym();
            break;
        case ClauseSynonymType::SYNONYM_BOTH:
            evaluateTwoSynonyms();
            break;
        default:
            break;
    }
    return result;
}

ClauseSynonymType SuchThatClauseEvaluator::getClauseSynonymType() {
    if (argLeft.argumentType == ArgumentType::SYNONYM){
        if (argRight.argumentType == ArgumentType::SYNONYM) {
            return ClauseSynonymType::SYNONYM_BOTH;
        } else {
            return ClauseSynonymType::SYNONYM_LEFT;
        }
    } else if (argRight.argumentType == ArgumentType::SYNONYM){
        return ClauseSynonymType::SYNONYM_RIGHT;
    } else {
        return ClauseSynonymType::SYNONYM_NONE;
    }
}

void SuchThatClauseEvaluator::evaluateNoSynonym() {

    result = {
            .resultType = ResultType::BOOLEAN,
            .resultBoolean = isRelation(argLeft.argumentValue, argRight.argumentValue)};
}
void SuchThatClauseEvaluator::evaluateTwoSynonyms() {
    DesignEntity entityLeft = query->findEntityType(argLeft.argumentValue);
    DesignEntity entityRight = query->findEntityType(argRight.argumentValue);
    unordered_set<std::string> leftSet = getAllType(entityLeft);
    unordered_set<std::string> rightSet = getAllType(entityRight);
    result.resultType = ResultType::TUPLES;
    result.resultBoolean = !result.resultItemList.empty();
    result.resultHeader = tuple<string, string> { argLeft.argumentValue, argRight.argumentValue};
    result.resultItemList = generateTuples(leftSet, rightSet);
}
void SuchThatClauseEvaluator::evaluateLeftSynonym() {
    DesignEntity entityLeft = query->findEntityType(argLeft.argumentValue);
    unordered_set<std::string> rightSet;
    if(argRight.argumentType == ArgumentType::UNDERSCORE) {
        rightSet = getAllType(std::get<1>(getWildcardType()));
    } else {
        rightSet = {argRight.argumentValue};
    }
    unordered_set<std::string> resultSet = generateLeftSet(rightSet);
    filterByType(resultSet, entityLeft);
    bool isEmpty = resultSet.empty();
    result = {.resultType = ResultType::STRING,
            .resultBoolean = !isEmpty,
            .resultHeader = argLeft.argumentValue,
            .resultItemList = convertSetToVector(resultSet)};
}

void SuchThatClauseEvaluator::evaluateRightSynonym() {
    DesignEntity entityRight = query->findEntityType(argRight.argumentValue);
    unordered_set<std::string> leftSet;
    if(argLeft.argumentType == ArgumentType::UNDERSCORE) {
        leftSet = getAllType(std::get<0>(getWildcardType()));
    } else {
        leftSet = {argLeft.argumentValue};
    }

    unordered_set<std::string> resultSet = generateRightSet(leftSet);
    filterByType(resultSet, entityRight);
    bool isEmpty = resultSet.empty();
    result = {.resultType = ResultType::STRING,
              .resultBoolean = !isEmpty,
              .resultHeader = argRight.argumentValue,
              .resultItemList = convertSetToVector(resultSet)};
}

std::vector<ResultItem> SuchThatClauseEvaluator::generateTuples(unordered_set<std::string>& leftSet, unordered_set<std::string>& rightSet) {
    std::vector<ResultItem> tuples = std::vector<ResultItem>{};
    for (const auto & left : leftSet) {
        unordered_set<std::string> follows = getRightSynonymValue(left);
        for (const auto & follow : follows) {
            if (rightSet.find(follow) != rightSet.end()) {
                tuples.emplace_back(std::tuple<string, string>(left, follow));
            }
        }
    }
    return tuples;
};

std::vector<ResultItem> SuchThatClauseEvaluator::convertSetToVector (unordered_set<std::string> set) {
    std::vector<ResultItem> vector {};
    vector.reserve(set.size());
    for (auto it = set.begin(); it != set.end(); ) {
        vector.emplace_back(std::move(set.extract(it++).value()));
    }
    return vector;
};

unordered_set<std::string> SuchThatClauseEvaluator::generateLeftSet (unordered_set<std::string>& rightSet) {

    /*
    unordered_set<std::string> intersect;
    for( const std::string& str1 : set1 ) {
        for( const std::string& str2 : set2 ) {
            if (str1 == str2) {
                intersect.emplace(str1);
            }
        }
    };
    std::cout << '\n' ;
    cout << intersect.size();
    return intersect;
     */
    unordered_set<std::string> leftSet;
    for (const std::string& str : rightSet) {
        unordered_set<std::string> resultSet = getLeftSynonymValue(str);
        leftSet.insert(resultSet.begin(), resultSet.end());
    }

    return leftSet;
};

unordered_set<std::string> SuchThatClauseEvaluator::generateRightSet (unordered_set<std::string>& leftSet) {
    unordered_set<std::string> rightSet;
    for (const std::string& str : leftSet) {
        unordered_set<std::string> resultSet = getRightSynonymValue(str);
        rightSet.insert(resultSet.begin(), resultSet.end());
    }
    return rightSet;
}

void SuchThatClauseEvaluator::filterByType (unordered_set<std::string>& set, DesignEntity entityType) {
    for (const std::string& str : set) {
        if(!isEntityType(str, entityType)) {
            set.erase(str);
        }
    }
}


bool SuchThatClauseEvaluator::isEntityType (std::string ident, DesignEntity entityType) {
    switch (entityType) {
        /*
        case DesignEntity::STMT:
            return pkb->isStatement(ident);
        case DesignEntity::VARIABLE:
            return pkb->isVariable(ident);
        case DesignEntity::ASSIGN:
            return pkb->isAssign(ident);
        case DesignEntity::PRINT:
            return pkb->isPrint(ident);
        case DesignEntity::READ:
            return pkb->isRead(ident);
        case DesignEntity::WHILE:
            return pkb->isWhile(ident);
        case DesignEntity::IF:
            return pkb->isIf(ident);
            */
        default:
            return true;
    }
}





