//
// Created by Tianyi Wang on 30/3/22.
//

#include "QueryOptimizer.h"

void QueryOptimizer::groupClauses(){
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

    if(allClauses.size() > 3) {
        groupClausesWithCommonSynonyms(allClauses);
    } else {
        groupClausesBasic(allClauses);
    }

    assignWeights(&rearrangedClauses);
    // sort the vector such that  1.clauses with no synonyms at the front  2. clause with common synonyms are next to each other.
    std::sort(rearrangedClauses.begin(), rearrangedClauses.end());
    setGroups();
}

void QueryOptimizer::groupClausesWithCommonSynonyms(vector<Clause*> allClauses){
    setSynonymIndices();

    // disjoint set algorithm is used to identify which group a synonym belongs to
    DisjointSet ds(int(query->getDeclarations()->size()));

    std::unordered_map<Clause*, int> groupIdentifier; // stores the mapping from each clause to one of its synonyms (0 for clauses without synonyms)

    /*
     * for each clause, get all its synonyms. For cases with more than 1 synonym, join them under the same group.
     * set one of its synonym's index as the group identifier for the clause, which will be used to retrieve the group no. at the end.
     */
    auto numOfClauses = allClauses.size();
    for(int i = 0; i < numOfClauses; i ++) {
        std::vector<int> synonyms;
        for(const Argument& a : allClauses[i]->argList) {
            if(a.argumentType == ArgumentType::SYNONYM) {
                string synonym = std::get<string>(a.argumentValue);
                synonyms.emplace_back(synonymIndices[synonym]);
            } else if (a.argumentType == ArgumentType::ATTR_REF) {
                string synonym = std::get<pair<string, AttrName>>(a.argumentValue).first;
                synonyms.emplace_back(synonymIndices[synonym]);
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
}

void QueryOptimizer::groupClausesBasic(vector<Clause*> allClauses){

    auto numOfClauses = allClauses.size();

    // GroupedClause stores a pointer to the clause and the group number for the clause, append it to the output vector
    for(int i = 0; i < numOfClauses; i ++) {
        Clause* clause = allClauses[i];
        GroupedClause newClause = {clause, 0};
        rearrangedClauses.emplace_back(newClause);
    }

    // sort the vector such that  1.clauses with no synonyms at the front  2. clause with common synonyms are next to each other.
    std::sort(rearrangedClauses.begin(), rearrangedClauses.end());

    setGroups();
}

std::vector<GroupedClause> QueryOptimizer::getClauses() {
    return rearrangedClauses;
};

void QueryOptimizer::assignWeights(std::vector<GroupedClause>* groupedClauses) {
    std::vector<GroupedClause>& clauses = *groupedClauses;
    for (size_t i = 0; i < clauses.size(); i++) {
        setWeightByClause(&clauses[i]);
    }
}

void QueryOptimizer::setWeightByClause(GroupedClause* clause) {
    std::pair<int, int> numSynonymConst = getNumSynonymConst(&clause->clause->argList);
    if (numSynonymConst.second == 2) {
        clause->weight = 0;
    } else if (numSynonymConst.first == 1 && numSynonymConst.second == 1) {
        clause->weight = 0.1;
    } else if (dynamic_cast<WithClause*>(clause->clause)) {
        clause->weight = 0.8;
    } else if (dynamic_cast<PatternClause*>(clause->clause)) {
        clause->weight = 0.9;
    } else {
        SuchThatClause suchThatClause = *dynamic_cast<SuchThatClause*>(clause->clause);
        clause->weight = 0.2;
        if (suchThatClause.relRef == RelRef::NEXT_T) {
            clause->weight = 0.6;
        } else if (suchThatClause.relRef == RelRef::AFFECTS || suchThatClause.relRef == RelRef::AFFECTS_T) {
            clause->weight = 1;
        }
    }
}

std::pair<int, int> QueryOptimizer::getNumSynonymConst(std::vector<Argument>* argList) {
    int constants = 0;
    int synonyms = 0;
    for (Argument argument : *argList) {
        if (argument.argumentType == ArgumentType::SYNONYM) {
            synonyms += 1;
        } else if (argument.argumentType == ArgumentType::STMT_NO || argument.argumentType == ArgumentType::BOOLEAN
                   || argument.argumentType == ArgumentType::IDENT) {
            constants += 1;
        }
    }

    return std::pair(synonyms, constants);
}

void QueryOptimizer::setSynonymIndices() {
    // synonym indices maps each synonym to an integer (1 to n+1), which is used in disjoint set algorithm.
    for(auto iter = query->getDeclarations()->begin(); iter != query->getDeclarations()->end(); ++iter){
        auto index = std::distance(query->getDeclarations()->begin(), iter);
        synonymIndices[iter->first] = int(index + 1);
    }
}

void QueryOptimizer::setGroups() {
    for (auto groupedClause : rearrangedClauses) {
        groups.insert(groupedClause.group);
    }
};

unordered_set<int>* QueryOptimizer::getGroups() {
    return &groups;
}