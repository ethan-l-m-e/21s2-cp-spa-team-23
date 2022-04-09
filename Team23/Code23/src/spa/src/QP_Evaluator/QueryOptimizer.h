//
// Created by Tianyi Wang on 30/3/22.
//

#ifndef SPA_QUERYOPTIMIZER_H
#define SPA_QUERYOPTIMIZER_H

#include "QP_Evaluator/Query/Query.h"
#include <unordered_set>
#include <unordered_map>
#include <iostream>

using std::unordered_set;
using std::unordered_map;

class DisjointSet {
public:
    explicit DisjointSet(int size) {
        for (int i = 0; i < size + 1; i++) {
            root.emplace_back(i);
        }
    }

    int find(int x) {
        if (x == root[x]) {
            return x;
        }
        return root[x] = find(root[x]);
    }

    void unionSet(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);
        if (rootX != rootY) {
            root[rootY] = rootX;
        }
    }

private:
    vector<int> root;
};

typedef struct GroupedClause {
    Clause* clause;
    int group;
    float weight;
    bool operator <(const GroupedClause & other) const
    {
        return weight < other.weight;
//        return group < other.group; // compare group number
    }
} GroupedClause;

class QueryOptimizer {
private:
    std::vector<GroupedClause> rearrangedClauses; // the output vector, initially empty
    Query *query;
    unordered_set<int> groups;
    unordered_map<string, int> synonymIndices;
    void setSynonymIndices();
    void setGroups();
public:
    QueryOptimizer(Query* query): query{query}{}
    void groupClauses();
    void groupClausesWithCommonSynonyms(vector<Clause*> allClauses);
    void groupClausesBasic(vector<Clause*> allClauses);
    vector<GroupedClause> getClauses();
    unordered_set<int>* getGroups();

    void assignWeights(std::vector<GroupedClause>*);
    void setWeightByClause(GroupedClause*);
    std::pair<int, int> getNumSynonymConst(std::vector<Argument>*);
};


#endif //SPA_QUERYOPTIMIZER_H
