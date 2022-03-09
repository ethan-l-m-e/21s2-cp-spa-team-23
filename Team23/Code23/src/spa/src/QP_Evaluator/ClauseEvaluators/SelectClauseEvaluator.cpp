//
// Created by Tianyi Wang on 7/2/22.
//

#include "SelectClauseEvaluator.h"
bool SelectClauseEvaluator::evaluateClause(ResultTable* resultTable) {
    std::unordered_set<std::string> resultSet;
    auto header = resultTable->getHeader();
    vector<int> orders;
    for(Argument synonym : query->getSelectedSynonyms()) {
        if(synonym.argumentType == ArgumentType::BOOLEAN) {
            if(resultTable->isEmpty()) {
                resultTable->setBooleanResult(false);
            } else {
                resultTable->setBooleanResult(true);
            }
            return true;
        }

        if(synonym.argumentType == ArgumentType::ATTR_REF) {
            std::pair<string, AttrName> attrRef = std::get<std::pair<string, AttrName>>(synonym.argumentValue);
            std::string synonymValue = attrRef.first;
            auto it = std::find(header->begin(), header->end(), synonymValue);
            if (it != header->end()) {
                auto index = std::distance(header->begin(), it);
                std::vector<std::string> newColumn;
                if (applyAttrRef(&(*resultTable->getList())[index], attrRef, &newColumn)) {
                    resultTable->appendColumn(attrRef.first + ".altName", newColumn);
                    index = long(resultTable->getTableSize()) - 1;
                }
                orders.emplace_back(index);
            } else {
                auto index = std::distance(header->begin(), it);
                unordered_set<std::string> set = getAllType(query->getSynonymType(synonymValue));
                std::vector<std::string> newColumn;
                std::vector<std::string> resultList;
                resultList = std::vector<std::string>(set.begin(), set.end());
                if (applyAttrRef(&resultList, attrRef, &newColumn)) resultList = newColumn;
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

bool SelectClauseEvaluator::applyAttrRef(std::vector<std::string>* lst,
                                         std::pair<string, AttrName> attrRef,
                                         std::vector<std::string>* newLst) {
    if(query->findEntityType(attrRef.first) == DesignEntity::READ && attrRef.second == AttrName::VAR_NAME) {
        newLst = getMapping(lst, pkb->getVarRead);
        return true;
    } else if (query->findEntityType(attrRef.first) == DesignEntity::PRINT && attrRef.second == AttrName::VAR_NAME) {
        newLst = getMapping(lst, pkb->getVarPrinted);
        return true;
    } else if (query->findEntityType(attrRef.first) == DesignEntity::CALL && attrRef.second == AttrName::PROC_NAME) {
        newLst = getMapping(lst, pkb->getProcByCall);
        return true;
    }
    return false;
}

std::vector<std::string> SelectClauseEvaluator::getMapping(std::vector<std::string>& lst, std::string (*func) (std::string)) {
    std::vector<std::string> mappings;
    for (const std::string& val: lst) {
        std::string mapped = func(val);
        mappings.emplace_back(mapped);
    }
    return mappings;
}
