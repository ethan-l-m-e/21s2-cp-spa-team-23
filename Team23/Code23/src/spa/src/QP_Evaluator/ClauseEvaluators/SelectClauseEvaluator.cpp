//
// Created by Tianyi Wang on 7/2/22.
//

#include "SelectClauseEvaluator.h"
Result SelectClauseEvaluator::evaluateClause() {
    std::unordered_set<std::string> resultSet;
    auto header = resultTable->getHeader();
    ResultTable* newTable = new ResultTable();
    for(string synonym : query->getSelectedSynonyms()) {
        vector<ResultItem> resultItemList;
        auto it = std::find(header->begin(), header->end(), query->getSelectedSynonyms());
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
    return {.resultType = ResultType::STRING,
            .resultBoolean =true,
            .resultHeader = newTable->getHeader()->front(),
            .resultItemList = {}}
}
