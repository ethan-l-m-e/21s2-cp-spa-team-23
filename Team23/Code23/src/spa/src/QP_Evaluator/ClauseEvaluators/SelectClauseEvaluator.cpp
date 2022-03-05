//
// Created by Tianyi Wang on 7/2/22.
//

#include "SelectClauseEvaluator.h"
bool SelectClauseEvaluator::evaluateClause(ResultTable* resultTable) {
    std::unordered_set<std::string> resultSet;
    auto header = resultTable->getHeader();
    auto* newTable = new ResultTable();
    for(string synonym : query->getSelectedSynonyms()) {
        vector<ResultItem> resultItemList;
        auto it = std::find(header->begin(),header->end(), synonym);
        if (it != header->end()) {
            auto index =  it - header->begin();
            for (auto& entry : *resultTable->getList()) resultItemList.emplace_back(entry[index]);
        } else {
            unordered_set<std::string> set = getAllType(query->getSynonymType(synonym));
            resultItemList = std::vector<ResultItem>(set.begin(), set.end());
        }
        Result result = {.resultType = ResultType::STRING,
                .resultBoolean =true,
                .resultHeader = synonym,
                .resultItemList = resultItemList
        };
        newTable->mergeResultToSynonymsRelations(result);
    }
    *resultTable = *newTable;
    return true;
}
