//
// Created by Tianyi Wang on 26/3/22.
//

#include "WithClauseEvaluator.h"

bool WithClauseEvaluator::evaluateClause(ResultTable* resultTable) {
    
    if(argLeft.argumentType == ArgumentType::ATTR_REF && argRight.argumentType == ArgumentType::ATTR_REF) {
        unordered_map<string, string> leftResult = getAttributeMapping(std::get<pair<string, AttrName>>(argLeft.argumentValue));
        unordered_map<string, string> rightResult = getAttributeMapping(std::get<pair<string, AttrName>>(argRight.argumentValue));
        unordered_set<pair<string, string>> resultItems = compareAttributes(leftResult, rightResult);
        string synonym1 = std::get<pair<string, AttrName>>(argLeft.argumentValue).first;
        string synonym2 = std::get<pair<string, AttrName>>(argRight.argumentValue).first;
        result = makeResult(make_pair(synonym1, synonym2), resultItems);
    } else if(argLeft.argumentType == ArgumentType::ATTR_REF) {
        unordered_map<string, string> leftResult = getAttributeMapping(std::get<pair<string, AttrName>>(argLeft.argumentValue));
        unordered_set<string> resultItems = compareAttributes(leftResult, std::get<string>(argRight.argumentValue));
        string synonym = std::get<pair<string, AttrName>>(argLeft.argumentValue).first;
        result = makeResult(synonym, resultItems);
    } else if(argRight.argumentType == ArgumentType::ATTR_REF) {
        unordered_map<string, string> rightResult = getAttributeMapping(std::get<pair<string, AttrName>>(argRight.argumentValue));
        unordered_set<string> resultItems = compareAttributes(rightResult, std::get<string>(argLeft.argumentValue));
        string synonym = std::get<pair<string, AttrName>>(argRight.argumentValue).first;
        result = makeResult(synonym, resultItems);
    } else {
        bool isEqual = std::get<string>(argLeft.argumentValue) == std::get<string>(argRight.argumentValue);
        result = makeResult(isEqual);
    }

    bool resultValidity = processResult(resultTable);
    return resultValidity;
}

/**
 * Compare two set of key value pairs to find the pairs with common values.
 * @param  leftMap an unordered map representing the < synonym, attribute synonym reference> for the left argument
 * @param  rightMap an unordered map representing the < synonym, attribute synonym reference> for the right argument
 * @return  filtered set of pairs of synonyms (keys)
 */
unordered_set<pair<string, string>> WithClauseEvaluator::compareAttributes(unordered_map<string, string> leftMap, unordered_map<string, string> rightMap) {
    unordered_set<pair<string, string>> resultItems;
    for (const auto& elementLeft : leftMap) {
        for (const auto& elementRight : rightMap) {
            if(elementLeft.second == elementRight.second) {
                resultItems.insert(make_pair(elementLeft.first, elementRight.first));
            }
        }
    }
    return resultItems;
}

/**
 * Compare a set of key value pairs with a single string value
 * @param map  an unordered map representing the < synonym, attribute synonym reference> for the argument with unknowns
 * @param ident  a string ident value
 * @return  filtered set of synonyms (keys)
 */
unordered_set<string> WithClauseEvaluator::compareAttributes(unordered_map<string, string> map, string ident) {
    unordered_set<string> resultItems;
    for(const auto& element : map) {
        if (element.second == ident) {
            resultItems.insert(element.first);
        }
    }
    return resultItems;
}

/**
 * Get the mapping of synonym to the attribute reference of the synonym
 * @param argumentValue  an
 * @return
 */
unordered_map<string, string> WithClauseEvaluator::getAttributeMapping(pair<string, AttrName> argumentValue) {
    unordered_set<string> valueSet = getAllType(declarations->at(argumentValue.first));
    string(ClauseEvaluator::*func) (string&);
    string name;
    if (applyAttrRef(argumentValue, &func, &name)) {
        return generateMap(valueSet, func);
    } else {
        return generateMap(valueSet);
    }
}