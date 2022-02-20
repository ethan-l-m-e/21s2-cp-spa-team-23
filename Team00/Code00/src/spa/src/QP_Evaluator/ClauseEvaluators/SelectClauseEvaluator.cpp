//
// Created by Tianyi Wang on 7/2/22.
//

#include "SelectClauseEvaluator.h"
Result SelectClauseEvaluator::evaluateClause() {
    std::vector<ResultItem> resultItemList;
    auto header = synonymRelations->getHeader();
    auto it = std::find(header->begin(), header->end(), query->getSelectedSynonym());
    if (it != header->end()) {
        auto index =  it - header->begin();
        for (auto& entry : *synonymRelations->getList()) resultItemList.emplace_back(entry[index]);
    } else {
        std::unordered_set<std::string> resultSet = getAllType(query->getSelectedSynonymType());
        resultItemList = std::vector<ResultItem>(resultSet.begin(), resultSet.end());
    }
     result = {
            .resultType = ResultType::STRING,
            .resultBoolean =true,
            .resultHeader = query->getSelectedSynonym(),
            .resultItemList = resultItemList
    };
    return result;
}
