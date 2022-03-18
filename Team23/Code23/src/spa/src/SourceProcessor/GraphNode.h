//
// Created by Lucas Tai on 18/3/22.
//

#ifndef SPA_GRAPHNODE_H
#define SPA_GRAPHNODE_H
#include <string>
#include <vector>
#include <unordered_set>
#include "TNode/Node.h"

using namespace std;

class GraphNode {
    string name;
    vector<ProcName> toOtherNodes;
public:
    GraphNode(string name, vector<ProcName> toOtherNodes);
    vector<ProcName> getDirectedNodes();
    string getName();
    void changeName(string name);
};

#endif //SPA_GRAPHNODE_H
