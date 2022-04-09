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

/**
 * Disjoint set algorithm for finding the grouping of clauses based on common synonyms
 */
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

/**
 * Grouped clause is a struct used for grouping and sorting of a clause
 */
typedef struct GroupedClause {
    Clause* clause;
    int group;
    float weight;
    bool operator <(const GroupedClause & other) const
    {
        return weight < other.weight;
    }
} GroupedClause;

class QueryOptimizer {
public:
    explicit QueryOptimizer(Query *query) : query{query} {}

    void optimizeQueryClauses();

    vector<GroupedClause> *getClauses();

    unordered_set<int> *getGroups();

private:

    std::vector<GroupedClause> rearrangedClauses; // the output vector, initially empty
    Query *query;
    unordered_set<int> groups;
    unordered_map<string, int> synonymIndices;

    void assignWeights(std::vector<GroupedClause> *);

    void groupClausesWithCommonSynonyms(vector<Clause *> allClauses);

    void groupClausesSingle(vector<Clause *> allClauses);

    void setSynonymIndices();

    void setGroups();

    void setWeightByClause(GroupedClause *);

    std::pair<int, int> getNumSynonymConst(std::vector<Argument> *);

};


#endif //SPA_QUERYOPTIMIZER_H
