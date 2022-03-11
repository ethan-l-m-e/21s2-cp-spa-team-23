//
// Created by Tianyi Wang on 9/2/22.
//

#include "SuchThatClauseEvaluator.h"
#include "QP_Parser/Exception.h"

/**
 * Evaluate the such that clause.
 * @return  an result object for the evaluation of the clause
 */
bool SuchThatClauseEvaluator::evaluateClause(ResultTable* resultTable) {
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
    if(!result.resultBoolean) return false;
    mergeResult(resultTable);
    return true;
}

/**
 * Get clause synonym type of the such that clause.
 * @return  a clause synonym type to indicate the number and position of synonym in the clause
 */
ClauseSynonymType SuchThatClauseEvaluator::getClauseSynonymType() const {
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

/**
 * Evaluate a clause with no synonym in its arguments.
 */
void SuchThatClauseEvaluator::evaluateNoSynonym() {

    unordered_set<std::string> leftSet = generateValueSet(argLeft, std::get<0>(getWildcardType()));
    unordered_set<std::string> rightSet = generateValueSet(argRight, std::get<1>(getWildcardType()));

    result = {
            .resultType = ResultType::BOOLEAN,
            .resultBoolean = validateRelation(leftSet, rightSet)};
}

/**
 * Evaluate a clause with two synonym in its arguments.
 */
void SuchThatClauseEvaluator::evaluateTwoSynonyms() {
    DesignEntity entityLeft = query->findEntityType(std::get<std::string>(argLeft.argumentValue));
    DesignEntity entityRight = query->findEntityType(std::get<std::string>(argRight.argumentValue));
    unordered_set<std::string> leftSet = getAllType(entityLeft);
    unordered_set<std::string> rightSet = getAllType(entityRight);
    vector<ResultItem> resultItemList = generateTuples(leftSet, rightSet);
    result = {
            .resultType = ResultType::TUPLES,
            .resultBoolean = !resultItemList.empty(),
            .resultHeader = tuple<string, string> { std::get<std::string>(argLeft.argumentValue), std::get<std::string>(argRight.argumentValue)},
            .resultItemList = resultItemList
    };
}

/**
 * Evaluate a clause with a synonym in its left argument.
 */
void SuchThatClauseEvaluator::evaluateLeftSynonym() {
    DesignEntity entityLeft = query->findEntityType(std::get<std::string>(argLeft.argumentValue));
    unordered_set<std::string> rightSet = generateValueSet(argRight, std::get<1>(getWildcardType()));
    unordered_set<std::string> resultSet = generateLeftSet(rightSet);
    filterByType(resultSet, entityLeft);
    bool isEmpty = resultSet.empty();
    result = {.resultType = ResultType::STRING,
            .resultBoolean = !isEmpty,
            .resultHeader = std::get<std::string>(argLeft.argumentValue),
            .resultItemList = convertSetToVector(resultSet)};
}

/**
 * Evaluate a clause with a synonym in its right argument.
 */
void SuchThatClauseEvaluator::evaluateRightSynonym() {
    DesignEntity entityRight = query->findEntityType(std::get<std::string>(argRight.argumentValue));
    unordered_set<std::string> leftSet = generateValueSet(argLeft, std::get<0>(getWildcardType()));
    unordered_set<std::string> resultSet = generateRightSet(leftSet);
    filterByType(resultSet, entityRight);
    bool isEmpty = resultSet.empty();
    result = {.resultType = ResultType::STRING,
              .resultBoolean = !isEmpty,
              .resultHeader = std::get<std::string>(argRight.argumentValue),
              .resultItemList = convertSetToVector(resultSet)};
}

/**
 * Generate a vector of the result item tuples for a 2-synonym clause.
 * @param leftSet  the set of possible values for the left synonym
 * @param rightSet  the set of possible values for the right synonym
 * @return  a vector of ResultItem of the type tuples
 */
std::vector<ResultItem> SuchThatClauseEvaluator::generateTuples(unordered_set<std::string>& leftSet, unordered_set<std::string>& rightSet) {
    std::vector<ResultItem> tuples = std::vector<ResultItem>{};
    for (const auto & left : leftSet) {
        unordered_set<std::string> resultSet = getRightSynonymValue(left);
        for (const auto & result : resultSet) {
            if (rightSet.find(result) != rightSet.end()) {
                tuples.emplace_back(std::tuple<string, string>(left, result));
            }
        }
    }
    return tuples;
}

/**
 * Find whether any of the combination of the left and set values satisfies the relation.
 * @param leftSet  the set of possible values for the left argument
 * @param rightSet  the set of possible values for the right argument
 * @return  a boolean value indicating whether there is at least one pair that satisfies the relation
 */
bool SuchThatClauseEvaluator::validateRelation(unordered_set<std::string>& leftSet, unordered_set<std::string>& rightSet) {
    for (const auto & left : leftSet) {
        std::unordered_set<std:: string> resultSet = getRightSynonymValue(left);
        for (const auto & result : resultSet) {
            if (rightSet.find(result) != rightSet.end()) return true;
        }
    }
    return false;
}

/**
 * Generate the set of possible values for the left synonym given the possible values for the right set.
 * @param rightSet  the set of possible values for the right argument
 * @return  a set of possible values for the left argument
 */
unordered_set<std::string> SuchThatClauseEvaluator::generateLeftSet (unordered_set<std::string>& rightSet) {
    unordered_set<std::string> leftSet;
    for (const std::string& str : rightSet) {
        unordered_set<std::string> resultSet = getLeftSynonymValue(str);
        leftSet.insert(resultSet.begin(), resultSet.end());
    }

    return leftSet;
}

/**
 * Generate the set of possible values for the right synonym given the possible values for the left set.
 * @param leftSet  the set of possible values for the left argument
 * @return  a set of possible values for the right argument
 */
unordered_set<std::string> SuchThatClauseEvaluator::generateRightSet (unordered_set<std::string>& leftSet) {
    unordered_set<std::string> rightSet;
    for (const std::string& str : leftSet) {
        unordered_set<std::string> resultSet = getRightSynonymValue(str);
        rightSet.insert(resultSet.begin(), resultSet.end());
    }
    return rightSet;
}

/**
 * Filter a set of values by the entity type.
 * @param set  a set of values for an argument
 * @param entityType  an DesignEntity value
 */
void SuchThatClauseEvaluator::filterByType (unordered_set<std::string>& set, DesignEntity entityType) {
    for (auto it = set.begin(); it != set.end(); ) {
        if(!isEntityType(*it, entityType)) {
            set.erase(it++);
        }
        else {
            ++it;
        }
    }
}

/**
 * Check if a string identifier belongs to an entity type.
 * @param ident  reference to an string identifier
 * @param entityType  an DesignEntity value
 * @return  a boolean value indicating whether the identifier belongs to an entity type.
 */
bool SuchThatClauseEvaluator::isEntityType (const std::string& ident, DesignEntity entityType) {
    switch (entityType) {
        case DesignEntity::STMT:
            return pkb->isStatement(ident);
        case DesignEntity::VARIABLE:
            return pkb->isVariable(ident);
        case DesignEntity::CONSTANT:
            return pkb->isConstant(ident);
        case DesignEntity::ASSIGN:
            return pkb->isAssignStatement(ident);
        case DesignEntity::PRINT:
            return pkb->isPrintStatement(ident);
        case DesignEntity::READ:
            return pkb->isReadStatement(ident);
        case DesignEntity::WHILE:
            return pkb->isWhileStatement(ident);
        case DesignEntity::IF:
            return pkb->isIfStatement(ident);
        case DesignEntity::PROCEDURE:
            return pkb->isProcedure(ident);
        case DesignEntity::CALL:
            return pkb->isCallStatement(ident);
        default:
            throw qp::QPEvaluatorException("Invalid design entity found.");
    }
}

/**
 * Generate a set of values for an argument given the type of value for the argument.
 * For wildcard argument, generate all values for that design entity.
 * For other arguments, simply return the string value for the argument in a set.
 * @param argument  reference to an argument object
 * @param wildCardType  the DesignEntity used for the argument if the argument is a wildcard.
 * @return  return the set of values for the argument
 */
unordered_set<string> SuchThatClauseEvaluator::generateValueSet(Argument& argument, DesignEntity wildCardType) {
    if(argument.argumentType == ArgumentType::UNDERSCORE) {
        return getAllType(wildCardType);
    } else {
        assert(argument.argumentType != ArgumentType::SYNONYM);
        return {std::get<std::string>(argument.argumentValue)};
    }
}

/**
 * Utility function for converting an unordered set to a vector.
 * @param set  the set to be converted
 * @return  a vector object containing the items of the original set
 */
std::vector<ResultItem> SuchThatClauseEvaluator::convertSetToVector (unordered_set<std::string> set) {
    std::vector<ResultItem> vector {};
    vector.reserve(set.size());
    for (auto it = set.begin(); it != set.end(); ) {
        vector.emplace_back(std::move(set.extract(it++).value()));
    }
    return vector;
}





