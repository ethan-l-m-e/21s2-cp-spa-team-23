//
// Created by Tianyi Wang on 30/3/22.
//

#include "QueryOptimizer.h"

std::vector<GroupedClause> QueryOptimizer::groupClauses(){
    std::map<string, int> synonymIndices;
    vector<Clause*> allClauses;
    for(auto& patternClause : *query->getPatternClauses()) {
        allClauses.emplace_back(&patternClause);
    }
    for(auto& suchThatClause : *query->getSuchThatClauses()) {
        allClauses.emplace_back(&suchThatClause);
    }
    for(auto& withClause : *query->getWithClauses()) {
        allClauses.emplace_back(&withClause);
    }
    auto n = allClauses.size();
    DisjointSet ds(int(query->getDeclarations()->size()));
    for(auto iter = query->getDeclarations()->begin(); iter != query->getDeclarations()->end(); ++iter){
        auto index = std::distance(query->getDeclarations()->begin(), iter);
        synonymIndices[iter->first] = int(index + 1);
    }
    std::vector<GroupedClause> rearrangedClauses;

    std::map<Clause*, int> groupIdentifier;
    for(int i = 0; i < n; i ++) {
        std::vector<int> synonyms;
        for(const Argument& a : allClauses[i]->argList) {
            if(a.argumentType == ArgumentType::SYNONYM) {
                synonyms.emplace_back(synonymIndices[std::get<string>(a.argumentValue)]);
            } else if (a.argumentType == ArgumentType::ATTR_REF) {
                synonyms.emplace_back(synonymIndices[std::get<pair<string, AttrName>>(a.argumentValue).first]);
            }
        }
        if(synonyms.size() > 1) {
            for (int j = 0; j < synonyms.size() - 1; j++) {
                ds.unionSet(synonyms[j], synonyms[j + 1]);
            }
            groupIdentifier[allClauses[i]] = synonyms[0];
        } else if (synonyms.empty()) {
            groupIdentifier[allClauses[i]] = 0;
        } else {
            groupIdentifier[allClauses[i]] = synonyms[0];
        }
    }

    for(int i = 0; i < n; i ++) {
        int synonym = groupIdentifier.at(allClauses[i]);
        rearrangedClauses.emplace_back(GroupedClause{allClauses[i], ds.find(synonym)});
    }

    std::sort(rearrangedClauses.begin(), rearrangedClauses.end());
    /*
    for(GroupedClause gc : rearrangedClauses) {
        if (dynamic_cast<WithClause*>(gc.clause)) {
            auto *c = dynamic_cast<WithClause*>(gc.clause);
            std::cout<< c->getName() << " group: " << gc.group << std::endl;
        }
        else if (dynamic_cast<SuchThatClause*>(gc.clause)){
            auto *c = dynamic_cast<SuchThatClause *>(gc.clause);
            std::cout<< c->getName() << " group: " << gc.group << std::endl;
        }
        else if (dynamic_cast<PatternClause*>(gc.clause)){
            auto *c = dynamic_cast<PatternClause *>(gc.clause);
            std::cout<< c->getName() << " group: " << gc.group << std::endl;
        }
    }
    */
    return rearrangedClauses;
}