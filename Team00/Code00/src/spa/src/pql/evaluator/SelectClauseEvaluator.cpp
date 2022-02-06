//
// Created by Tianyi Wang on 7/2/22.
//

#include "SelectClauseEvaluator.h"
Result SelectClauseEvaluator::evaluateClause() {
    vector<ResultItem> resultItemList;
    // search
    auto lst = get_if<vector<std::string>>(&resultReference->resultHeader);
    auto it = std::find(lst->begin(), lst->end(), query->getSelectedSynonym());
    if (it != lst->end()) {
        int index =  it - lst->begin();
        for(ResultItem resultItem : resultReference->resultItemList) {
            auto vec =get_if<vector<std::string>>(&resultItem);
            resultItemList.emplace_back(vec[index]);
        }
    } else {
        DesignEntity entityType = query->getSelectedSynonymType();
        unordered_set<std::string> resultSet = getAllType(entityType);
        resultItemList = vector<ResultItem>(resultSet.begin(), resultSet.end());
    }

    return {ResultType::LIST, resultItemList.empty(), query->getSelectedSynonym(), resultItemList};
}

