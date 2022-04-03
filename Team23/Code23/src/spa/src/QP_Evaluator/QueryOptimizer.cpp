//
// Created by Tianyi Wang on 30/3/22.
//

#include "QueryOptimizer.h"

std::vector<GroupedClause>* QueryOptimizer::groupClauses(){
    std::map<string, int> synonymIndices;
    vector<Clause*> allClauses;

    // add all clauses into a single vector
    for(auto &patternClause : *query->getPatternClauses()) {
        allClauses.emplace_back(&patternClause);
    }
    for(auto &suchThatClause : *query->getSuchThatClauses()) {
        allClauses.emplace_back(&suchThatClause);
    }
    for(auto &withClause : *query->getWithClauses()) {
        allClauses.emplace_back(&withClause);
    }

    // disjoint set algorithm is used to identify which group a synonym belongs to
    DisjointSet ds(int(query->getDeclarations()->size()));

    // synonym indices maps each synonym to an integer (1 to n+1), which is used in disjoint set algorithm.
    for(auto iter = query->getDeclarations()->begin(); iter != query->getDeclarations()->end(); ++iter){
        auto index = std::distance(query->getDeclarations()->begin(), iter);
        synonymIndices[iter->first] = int(index + 1);
    }

    std::map<Clause*, int> groupIdentifier; // stores the mapping from each clause to one of its synonyms (0 for clauses without synonyms)

    /*
     * for each clause, get all its synonyms. For cases with more than 1 synonym, join them under the same group.
     * set one of its synonym's index as the group identifier for the clause, which will be used to retrieve the group no. at the end.
     */
    auto numOfClauses = allClauses.size();
    for(int i = 0; i < numOfClauses; i ++) {
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

    // GroupedClause stores a pointer to the clause and the group number for the clause, append it to the output vector
    for(int i = 0; i < numOfClauses; i ++) {
        Clause* clause = allClauses[i];
        int synonym = groupIdentifier.at(clause);
        int group = ds.find(synonym);
        GroupedClause newClause = {clause, group};
        rearrangedClauses.emplace_back(newClause);
    }

    // sort the vector such that  1.clauses with no synonyms at the front  2. clause with common synonyms are next to each other.
    std::sort(rearrangedClauses.begin(), rearrangedClauses.end());

    // for testing
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
    return &rearrangedClauses;
}