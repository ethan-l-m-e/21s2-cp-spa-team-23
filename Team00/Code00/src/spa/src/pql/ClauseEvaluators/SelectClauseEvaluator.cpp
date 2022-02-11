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
        //unordered_set<std::string> dummySet {"1","2","3"};
        resultItemList = std::vector<ResultItem>(resultSet.begin(), resultSet.end());
    }

    return {ResultType::LIST, resultItemList.empty(), query->getSelectedSynonym(), resultItemList};
}

