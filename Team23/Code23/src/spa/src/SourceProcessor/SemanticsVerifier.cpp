//
// Created by Lucas Tai on 18/3/22.
//

#include "SemanticsVerifier.h"
#include "TNode/TNode.h"
#include "GraphNode.h"
#include <unordered_set>
#include <unordered_map>
#include <iostream>

vector<ProcName> getAllProcedureCall(Node* node) {
    if(auto value = dynamic_cast<CallNode*>(node)) {
        ProcName procName = value->getProcName();
        return vector<ProcName>{procName};
    } else if (auto value = dynamic_cast<IfNode*>(node)) {
        vector<Node*> stmtLstNode = value->getStmtLst();
        vector<ProcName> procNameList, e;
        for(Node* s: stmtLstNode) {
            e = getAllProcedureCall(s);
            procNameList.insert(procNameList.end(), e.begin(), e.end());
        }
        return procNameList;
    } else if (auto value = dynamic_cast<WhileNode*>(node)) {
        vector<Node*> stmtLstNode = value->getStmtLst();
        vector<ProcName> procNameList, e;
        for(Node* s: stmtLstNode) {
            e = getAllProcedureCall(s);
            procNameList.insert(procNameList.end(), e.begin(), e.end());
        }
        return procNameList;
    } else if (auto value = dynamic_cast<ProcedureNode*>(node)) {
        vector<Node*> stmtLstNode = value->getStmtLst();
        vector<ProcName> procNameList, e;
        for(Node* s: stmtLstNode) {
            e = getAllProcedureCall(s);
            procNameList.insert(procNameList.end(), e.begin(), e.end());
        }
        return procNameList;
    }  else {
        return {};
    };
}

bool detectCyclicCallsRec(ProcName name,
                          unordered_map<ProcName, GraphNode*> graphNodes,
                          unordered_map<ProcName, bool> visited,
                          unordered_map<ProcName, bool> stack) {
    if (visited[name] == false) {
        visited[name] = true;
        stack[name] = true;
        GraphNode *currentNode = graphNodes[name];
        vector<ProcName> nameList = currentNode->getDirectedNodes();
        vector<ProcName>::iterator i;
        for (i = nameList.begin(); i != nameList.end(); ++i) {
            if (!visited[*i] &&
                detectCyclicCallsRec(*i, graphNodes, stack, visited))
                return true;
            else if (stack[*i] == true) return true;
        }
    }
    stack[name] = false;
    return false;
}
void SemanticsVerifier::detectCyclicCalls(Node* node) {
    auto programNode = dynamic_cast<ProgramNode *>(node);
    vector<ProcedureNode *> v = programNode->getProcLst();

    unordered_map<ProcName, GraphNode *> graphNodes;
    vector < ProcName > allProcName;
    unordered_map<ProcName, bool> visited;
    unordered_map<ProcName, bool> stack;

    for (ProcedureNode *p: v) {
        ProcName name = p->getProcName();
        vector < ProcName > NodesFromP = getAllProcedureCall(p);
        GraphNode *node = new GraphNode(name, NodesFromP);
        graphNodes[name] = node;
        allProcName.push_back(name);
        visited[name], stack[name] = false;
    }
    // perform DFS to check for recursions
    for (int i = 0; i < allProcName.size(); i++) {
        ProcName name = allProcName[i];
        if (!visited[name] && detectCyclicCallsRec(name, graphNodes, visited, stack)) {
            cout << "cyclic call statements detected\n";
            graphNodes.clear();
            throw "cyclic calls detected\n";
        }
    }
    graphNodes.clear();
}

void SemanticsVerifier::detectDuplicateProcedure(Node * node) {
    if(auto value = dynamic_cast<ProgramNode*>(node)) {
        unordered_set<ProcName> procNames;
        ProcedureList procLst = value->getProcLst();
        for(ProcedureNode* p: procLst) {
            if(procNames.find(p->getProcName()) != procNames.end()) {
                throw "Cannot have duplicate Procedure names";
            }
            procNames.insert(p->getProcName());
        }
    }
}
