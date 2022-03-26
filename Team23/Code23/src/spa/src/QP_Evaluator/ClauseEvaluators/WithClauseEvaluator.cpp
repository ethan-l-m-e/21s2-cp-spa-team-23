//
// Created by Tianyi Wang on 26/3/22.
//

#include "WithClauseEvaluator.h"

bool WithClauseEvaluator::evaluateClause(ResultTable* resultTable) {
    
    if(argLeft.argumentType == ArgumentType::ATTR_REF && argRight.argumentType == ArgumentType::ATTR_REF) {
        string synonym1 = std::get<pair<string, AttrName>>(argLeft.argumentValue).first;
        string synonym2 = std::get<pair<string, AttrName>>(argRight.argumentValue).first;
        unordered_map<string, string> leftResult = getAttributeMapping(std::get<pair<string, AttrName>>(argLeft.argumentValue));
        unordered_map<string, string> rightResult = getAttributeMapping(std::get<pair<string, AttrName>>(argRight.argumentValue));
        unordered_set<pair<string, string>> resultItems = compareAttributes(leftResult, rightResult);
        result = makeResult(make_pair(synonym1, synonym2), resultItems);
    } else if(argLeft.argumentType == ArgumentType::ATTR_REF) {
        string synonym = std::get<pair<string, AttrName>>(argLeft.argumentValue).first;
        unordered_map<string, string> leftResult = getAttributeMapping(std::get<pair<string, AttrName>>(argLeft.argumentValue));
        unordered_set<string> resultItems = compareAttributes(leftResult, std::get<string>(argRight.argumentValue));
        result = makeResult(synonym, resultItems);
    } else if(argRight.argumentType == ArgumentType::ATTR_REF) {
        string synonym = std::get<pair<string, AttrName>>(argRight.argumentValue).first;
        unordered_map<string, string> rightResult = getAttributeMapping(std::get<pair<string, AttrName>>(argRight.argumentValue));
        unordered_set<string> resultItems = compareAttributes(rightResult, std::get<string>(argLeft.argumentValue));
        result = makeResult(synonym, resultItems);
    } else {
        return std::get<string>(argLeft.argumentValue) == std::get<string>(argRight.argumentValue);
    }

    processResult(resultTable);
    return true;
}

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

unordered_set<string> WithClauseEvaluator::compareAttributes(unordered_map<string, string> map, string ident) {
    unordered_set<string> resultItems;
    for(const auto& element : map) {
        if (element.second == ident) {
            resultItems.insert(element.first);
        }
    }
    return resultItems;
}

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