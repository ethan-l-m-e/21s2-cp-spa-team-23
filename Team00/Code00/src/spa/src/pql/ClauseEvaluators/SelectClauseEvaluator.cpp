//
// Created by Tianyi Wang on 7/2/22.
//

#include "SelectClauseEvaluator.h"
Result SelectClauseEvaluator::evaluateClause() {
    std::vector<ResultItem> resultItemList;
    // search
    auto lst = synonymRelations->getHeader();
    auto it = std::find(lst->begin(), lst->end(), query->getSelectedSynonym());
    if (it != lst->end()) {
        auto index =  it - lst->begin();
        for(vector<std::string> nTuple : *synonymRelations->getList()) {
            resultItemList.emplace_back(nTuple[index]);
        }
    } else {
        DesignEntity entityType = query->getSelectedSynonymType();
        unordered_set<std::string> resultSet = getAllType(entityType);
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

