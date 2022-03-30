//
// Created by Tianyi Wang on 30/3/22.
//

#ifndef SPA_QUERYOPTIMIZER_H
#define SPA_QUERYOPTIMIZER_H

#include "QP_Evaluator/Query/Query.h"
#include <unordered_set>
#include <map>
#include <iostream>

class DisjointSet {
public:
    DisjointSet(int size) : root(size) {
        for (int i = 0; i < size + 1; i++) {
            root[i] = i;
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
    bool operator <(const GroupedClause & other) const
    {
        return group < other.group; // compare group number
    }
} GroupedClause;

class QueryOptimizer {
private:
    Query *query;
public:
    QueryOptimizer(Query* query): query{query}{}
    std::vector<GroupedClause> groupClauses();
};


#endif //SPA_QUERYOPTIMIZER_H
