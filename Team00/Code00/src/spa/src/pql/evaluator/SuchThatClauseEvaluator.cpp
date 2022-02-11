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
    result.resultType = ResultType::BOOLEAN;
    result.resultBoolean = isRelation(argLeft.argumentValue, argRight.argumentValue);
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
    unordered_set<std::string> intersect = findIntersection(getLeftSynonymValue(argRight.argumentValue), getAllType(entityLeft));
    result.resultType = ResultType::LIST;
    result.resultBoolean = !result.resultItemList.empty();
    result.resultHeader = argLeft.argumentValue;
    result.resultItemList = convertSetToVector(intersect);
}
void SuchThatClauseEvaluator::evaluateRightSynonym() {
    DesignEntity entityRight = query->findEntityType(argRight.argumentValue);
    unordered_set<std::string> intersect = findIntersection(getRightSynonymValue(argLeft.argumentValue), getAllType(entityRight));
    result.resultType = ResultType::LIST;
    result.resultBoolean = !result.resultItemList.empty();
    result.resultHeader = argRight.argumentValue;
    result.resultItemList = convertSetToVector(intersect);
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
};

unordered_set<std::string> SuchThatClauseEvaluator::findIntersection (unordered_set<std::string> set1, unordered_set<std::string> set2) {
    unordered_set<std::string> intersect;
    set_intersection(set1.begin(), set1.end(), set2.begin(), set2.end(),
                     std::inserter(intersect, intersect.begin()));
};



