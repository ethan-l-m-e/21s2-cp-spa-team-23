//
// Created by Tianyi Wang on 7/2/22.
//

#include "ResultClauseEvaluator.h"
bool ResultClauseEvaluator::evaluateClause(ResultTable* resultTable) {
    std::unordered_set<std::string> resultSet;
    auto header = resultTable->getHeader();
    if((query->getSelectedSynonyms())[0].argumentType == ArgumentType::BOOLEAN) {
        resultTable->enableBooleanResult();
        return true;
    }
    vector<int> orders;
    for(Argument synonym : query->getSelectedSynonyms()) {
        if(!resultTable->getBooleanResult()) {
            orders = {};
            break;
        } else {
            std::pair<string, AttrName> attrRef;
            std::string synonymValue;
            if (synonym.argumentType == ArgumentType::ATTR_REF) {
                attrRef = std::get<std::pair<string, AttrName>>(synonym.argumentValue);
                synonymValue = attrRef.first;
            } else {
                synonymValue = std::get<std::string>(synonym.argumentValue);
            }

            auto it = std::find(header->begin(), header->end(), synonymValue);
            if (it != header->end()) {
                auto index = std::distance(header->begin(), it);
                if (!attrRef.first.empty()) {
                    std::vector<std::string> newColumn;
                    if (applyAttrRef(&(*resultTable->getList())[index], attrRef, &newColumn)) {
                        resultTable->appendColumn(attrRef.first + ".altName", newColumn);
                        index = long(resultTable->getTableWidth()) - 1;
                    }
                }
                orders.emplace_back(index);
            } else {
                auto index = std::distance(header->begin(), it);
                unordered_set<std::string> set = getAllType(query->getSynonymType(synonymValue));
                std::vector<std::string> newColumn;
                std::vector<std::string> resultList;
                resultList = std::vector<std::string>(set.begin(), set.end());
                if (!attrRef.first.empty()) {
                    if(applyAttrRef(&resultList, attrRef, &newColumn)) resultList = newColumn;
                }
                Result result = {
                        .resultType = ResultType::STRING,
                        .resultBoolean =true,
                        .resultHeader = synonymValue,
                        .resultItemList = std::vector<ResultItem>(set.begin(), set.end())
                };
                resultTable->mergeResultToTable(result);
                orders.emplace_back(index);
            }
        }
    }
    resultTable->rearrangeSynonyms(orders);
    return true;
}

bool ResultClauseEvaluator::applyAttrRef(std::vector<std::string>* lst,
                                         std::pair<string, AttrName> attrRef,
                                         std::vector<std::string>* newLst) {
    if(query->findEntityType(attrRef.first) == DesignEntity::READ && attrRef.second == AttrName::VAR_NAME) {
        *newLst = getMapping(*lst, (&ResultClauseEvaluator::getVarRead));
        return true;
    } else if (query->findEntityType(attrRef.first) == DesignEntity::PRINT && attrRef.second == AttrName::VAR_NAME) {
        *newLst = getMapping(*lst, (&ResultClauseEvaluator::getVarPrinted));
        return true;
    } else if (query->findEntityType(attrRef.first) == DesignEntity::CALL && attrRef.second == AttrName::PROC_NAME) {
        *newLst = getMapping(*lst, (&ResultClauseEvaluator::getProcByCall));
        return true;
    }
    return false;
}

std::vector<std::string> ResultClauseEvaluator::getMapping(std::vector<std::string>& lst, std::string (ResultClauseEvaluator::*func) (std::string)) {
    std::vector<std::string> mappings;
    for (const std::string& val: lst) {
        std::string mapped = (this->*func)(val);
        mappings.emplace_back(mapped);
    }
    return mappings;
}


string ResultClauseEvaluator::getVarRead(string stmtNumber) {
    return pkb->statement.readStatements.getVariableName(stmtNumber);
}
string ResultClauseEvaluator::getVarPrinted(string stmtNumber) {
    return pkb->statement.printStatements.getVariableName(stmtNumber);
}
string ResultClauseEvaluator::getProcByCall(string stmtNumber) {
    return pkb->statement.callStatements.getProcedureName(stmtNumber);
}