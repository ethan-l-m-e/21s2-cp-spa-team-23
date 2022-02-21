//
// Created by Tianyi Wang on 7/2/22.
//

#include "SelectClauseEvaluator.h"
Result SelectClauseEvaluator::evaluateClause() {
    std::unordered_set<std::string> resultSet;
    auto header = synonymRelations->getHeader();
    auto it = std::find(header->begin(), header->end(), query->getSelectedSynonym());
    if (it != header->end()) {
        auto index =  it - header->begin();
        for (auto& entry : *synonymRelations->getList()) resultSet.emplace(entry[index]);
    } else {
        resultSet = getAllType(query->getSelectedSynonymType());
    }

    std::vector<ResultItem> resultItemList = std::vector<ResultItem>(resultSet.begin(), resultSet.end());

     result = {
            .resultType = ResultType::STRING,
            .resultBoolean =true,
            .resultHeader = query->getSelectedSynonym(),
            .resultItemList = resultItemList
    };
    return result;
}
