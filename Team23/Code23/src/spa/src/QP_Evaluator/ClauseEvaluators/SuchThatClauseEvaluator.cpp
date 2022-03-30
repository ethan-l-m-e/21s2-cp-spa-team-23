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

    bool resultValidity = processResult(resultTable);
    return resultValidity;
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

    unordered_set<string> leftSet = generateValueSet(argLeft, std::get<0>(getWildcardType()));
    unordered_set<string> rightSet = generateValueSet(argRight, std::get<1>(getWildcardType()));
    result = makeResult(validateRelation(leftSet, rightSet));
}

/**
 * Evaluate a clause with two synonym in its arguments.
 */
void SuchThatClauseEvaluator::evaluateTwoSynonyms() {
    string leftSynonym = std::get<string>(argLeft.argumentValue);
    string rightSynonym = std::get<string>(argRight.argumentValue);
    DesignEntity entityLeft = declarations->at(leftSynonym);
    DesignEntity entityRight = declarations->at(rightSynonym);
    unordered_set<string> leftSet = getAllType(entityLeft);
    unordered_set<string> rightSet = getAllType(entityRight);
    unordered_set<pair<string,string>> resultPairs = generateTuples(leftSet, rightSet, leftSynonym == rightSynonym);
    result = makeResult(make_pair( std::get<string>(argLeft.argumentValue), std::get<string>(argRight.argumentValue)), resultPairs);
}

/**
 * Evaluate a clause with a synonym in its left argument.
 */
void SuchThatClauseEvaluator::evaluateLeftSynonym() {
    DesignEntity entityLeft = declarations->at(std::get<string>(argLeft.argumentValue));
    unordered_set<string> rightSet = generateValueSet(argRight, std::get<1>(getWildcardType()));
    unordered_set<string> results = generateLeftSet(rightSet);
    filterByType(results, entityLeft);
    result = makeResult(std::get<string>(argLeft.argumentValue), results);
}

/**
 * Evaluate a clause with a synonym in its right argument.
 */
void SuchThatClauseEvaluator::evaluateRightSynonym() {
    DesignEntity entityRight = declarations->at(std::get<string>(argRight.argumentValue));
    unordered_set<string> leftSet = generateValueSet(argLeft, std::get<0>(getWildcardType()));
    unordered_set<string> results = generateRightSet(leftSet);
    filterByType(results, entityRight);
    result = makeResult(std::get<string>(argRight.argumentValue), results);
}

/**
 * Generate a vector of the result item tuples for a 2-synonym clause.
 * @param leftSet  the set of possible values for the left synonym
 * @param rightSet  the set of possible values for the right synonym
 * @param isSameSynonym  boolean indicating whether the two synonyms are the same
 * @return  a vector of ResultItem of the type tuples
 */
unordered_set<std::pair<string, string>> SuchThatClauseEvaluator::generateTuples(unordered_set<string>& leftSet, unordered_set<string>& rightSet, bool isSameSynonym) {
    unordered_set<std::pair<string, string>> tuples;
    for (const auto & left : leftSet) {
        for (const auto &right: rightSet) {
            if (isSameSynonym && right != left) continue;
            if (isRelation(left, right)) {
                tuples.insert(std::pair<string, string>(left, right));
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
bool SuchThatClauseEvaluator::validateRelation(unordered_set<string>& leftSet, unordered_set<string>& rightSet) {
    for (const auto & left : leftSet) {
        for (const auto & right : rightSet) {
            if (isRelation(left, right)) return true;
        }
    }
    return false;
}

/**
 * Generate the set of possible values for the left synonym given the possible values for the right set.
 * @param rightSet  the set of possible values for the right argument
 * @return  a set of possible values for the left argument
 */
unordered_set<string> SuchThatClauseEvaluator::generateLeftSet (unordered_set<string>& rightSet) {
    unordered_set<string> leftSet;
    for (const string& str : rightSet) {
        unordered_set<string> resultSet = getLeftSynonymValue(str);
        leftSet.insert(resultSet.begin(), resultSet.end());
    }

    return leftSet;
}

/**
 * Generate the set of possible values for the right synonym given the possible values for the left set.
 * @param leftSet  the set of possible values for the left argument
 * @return  a set of possible values for the right argument
 */
unordered_set<string> SuchThatClauseEvaluator::generateRightSet (unordered_set<string>& leftSet) {
    unordered_set<string> rightSet;
    for (const string& str : leftSet) {
        unordered_set<string> resultSet = getRightSynonymValue(str);
        rightSet.insert(resultSet.begin(), resultSet.end());
    }
    return rightSet;
}

/**
 * Filter a set of values by the entity type.
 * @param set  a set of values for an argument
 * @param entityType  an DesignEntity value
 */
void SuchThatClauseEvaluator::filterByType (unordered_set<string>& set, DesignEntity entityType) {
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
bool SuchThatClauseEvaluator::isEntityType (const string& ident, DesignEntity entityType) {
    switch (entityType) {
        case DesignEntity::STMT:
            return pkb->statement.statements.isStatementNumber(ident);
        case DesignEntity::VARIABLE:
            return pkb->entity.variables.isEntity(ident);
        case DesignEntity::CONSTANT:
            return pkb->entity.constants.isEntity(ident);
        case DesignEntity::ASSIGN:
            return pkb->statement.assignStatements.isStatementNumber(ident);
        case DesignEntity::PRINT:
            return pkb->statement.printStatements.isStatementNumber(ident);
        case DesignEntity::READ:
            return pkb->statement.readStatements.isStatementNumber(ident);
        case DesignEntity::WHILE:
            return pkb->statement.whileStatements.isStatementNumber(ident);
        case DesignEntity::IF:
            return pkb->statement.ifStatements.isStatementNumber(ident);
        case DesignEntity::PROCEDURE:
            return pkb->entity.procedures.isEntity(ident);
        case DesignEntity::CALL:
            return pkb->statement.callStatements.isStatementNumber(ident);
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
        return {std::get<string>(argument.argumentValue)};
    }
}





