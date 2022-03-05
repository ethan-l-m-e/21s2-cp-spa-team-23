//
// Created by Tianyi Wang on 7/2/22.
//

#include "SelectClauseEvaluator.h"
bool SelectClauseEvaluator::evaluateClause(ResultTable* resultTable) {
    std::unordered_set<std::string> resultSet;
    auto header = resultTable->getHeader();
    vector<int> orders;
    for(string synonym : query->getSelectedSynonyms()) {
        vector<ResultItem> resultItemList;
        auto it = std::find(header->begin(),header->end(), synonym);
        if (it != header->end()) {
            auto index =  it - header->begin();
            orders.emplace_back(index);
        } else {
            auto index =  it - header->begin();
            unordered_set<std::string> set = getAllType(query->getSynonymType(synonym));
            resultItemList = std::vector<ResultItem>(set.begin(), set.end());
            Result result = {.resultType = ResultType::STRING,
                    .resultBoolean =true,
                    .resultHeader = synonym,
                    .resultItemList = resultItemList
            };
            resultTable->mergeResultToTable(result);
            orders.emplace_back(index);
        }
        resultTable->rearrangeSynonyms(orders);
    }
    return true;
}
