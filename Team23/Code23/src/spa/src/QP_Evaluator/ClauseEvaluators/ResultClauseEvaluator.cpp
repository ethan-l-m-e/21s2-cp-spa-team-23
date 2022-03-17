//
// Created by Tianyi Wang on 7/2/22.
//

#include "ResultClauseEvaluator.h"
bool ResultClauseEvaluator::evaluateClause(ResultTable* resultTable) {
    std::unordered_set<std::string> resultSet;

    if ((query->getSelectedSynonyms())[0].argumentType == ArgumentType::BOOLEAN) {
        resultTable->enableBooleanResult();
        return true;
    }

    vector<int> projections;
    if (resultTable->getBooleanResult()) evaluateSelectedSynonyms(&projections, resultTable);
    resultTable->rearrangeSynonyms(projections);
    return true;

}

void ResultClauseEvaluator::evaluateSelectedSynonyms(vector<int>* projections, ResultTable* resultTable) {
    auto header = resultTable->getHeader();
    for (Argument synonym: query->getSelectedSynonyms()) {
        std::pair<string, AttrName> attrRef;
        std::string synonymValue;
        if (synonym.argumentType == ArgumentType::ATTR_REF) {
            attrRef = std::get<std::pair<string, AttrName>>(synonym.argumentValue);
            synonymValue = attrRef.first;
        } else {
            synonymValue = std::get<std::string>(synonym.argumentValue);
        }
        auto it = std::find(header->begin(), header->end(), synonymValue);
        auto index = std::distance(header->begin(), it);
        if (it == header->end()) appendNewSynonym(synonymValue, resultTable);
        if (!attrRef.first.empty()) {
            std::string(ResultClauseEvaluator::*func) (std::string) = nullptr;
            std::string name;
            if (applyAttrRef(attrRef, &func, &name)) {
                auto it1 = std::find(header->begin(), header->end(), name);
                long newIndex = std::distance(header->begin(), it1);
                if (it1 == header->end()) {
                    std::vector<std::string> newColumn = getMapping((*resultTable->getList())[index], func);
                    resultTable->appendColumn(name, newColumn);
                }
                index = newIndex;
            }
        }
        projections->emplace_back(index);
    }
}

void ResultClauseEvaluator::appendNewSynonym(string synonymValue, ResultTable* resultTable){
    unordered_set<std::string> set = getAllType(query->getSynonymType(synonymValue));
    Result result = {
            .resultType = ResultType::STRING,
            .resultBoolean =true,
            .resultHeader = synonymValue,
            .resultItemList = std::vector<ResultItem>(set.begin(), set.end())
    };
    resultTable->mergeResultToTable(result);
}

bool ResultClauseEvaluator::applyAttrRef(std::pair<string, AttrName>& attrRef, std::string (ResultClauseEvaluator::**func)(std::string), std::string *name) {
    if(query->findEntityType(attrRef.first) == DesignEntity::READ && attrRef.second == AttrName::VAR_NAME) {
        *name = attrRef.first + ".varName";
        *func = &ResultClauseEvaluator::getVarRead;
    } else if (query->findEntityType(attrRef.first) == DesignEntity::PRINT && attrRef.second == AttrName::VAR_NAME) {
        *name = attrRef.first + ".varName";
        *func = &ResultClauseEvaluator::getVarPrinted;
    } else if (query->findEntityType(attrRef.first) == DesignEntity::CALL && attrRef.second == AttrName::PROC_NAME) {
        *name = attrRef.first + ".procName";
        *func = &ResultClauseEvaluator::getProcByCall;
    } else {
        return false;
    }
    return true;
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