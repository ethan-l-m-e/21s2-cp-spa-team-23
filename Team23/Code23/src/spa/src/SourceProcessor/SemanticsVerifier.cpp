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
    auto callNodeValue = dynamic_cast<CallNode*>(node);
    auto ifNodeValue = dynamic_cast<IfNode*>(node);
    auto whileNodeValue = dynamic_cast<WhileNode*>(node);
    auto procedureNodeValue = dynamic_cast<ProcedureNode*>(node);
    if(callNodeValue) {
        ProcName procName = callNodeValue->getProcName();
        return vector<ProcName>{procName};
    } else if (ifNodeValue || whileNodeValue || procedureNodeValue) {
        vector<Node*> stmtLstNode = node->getStmtLst();
        vector<ProcName> procNameList, e;
        for(Node* s: stmtLstNode) {
            e = getAllProcedureCall(s);
            procNameList.insert(procNameList.end(), e.begin(), e.end());
        }
        return procNameList;
    } else {
        return {};
    };
}

unordered_map<ProcName, GraphNode*> graphNodes;
unordered_map<ProcName, bool> visited;
unordered_map<ProcName, bool> stack;

bool detectCyclicCallsRec(ProcName name) {
    if (visited[name] == false) {
        visited[name] = true;
        stack[name] = true;
        GraphNode *currentNode = graphNodes[name];
        vector<ProcName> nameList = currentNode->getDirectedNodes();
        vector<ProcName>::iterator i;
        for (i = nameList.begin(); i != nameList.end(); ++i) {
            if ((!visited[*i] &&
                detectCyclicCallsRec(*i)) || stack[*i])
                return true;
        }
    }
    stack[name] = false;
    return false;
}

void SemanticsVerifier::checkIfProcIsDeclared(ProcedureList procList, vector<ProcName> procCall) {
    for(ProcName call: procCall) {
        bool existInProcList = false;
        for(ProcedureNode* procedure: procList) {
            ProcName procedureName = procedure->getProcName();
            if(call == procedureName) {
                existInProcList = true;
                break;
            }
        }
        if(!existInProcList) throw "\"" + call + "\" procedure is not declared in program";
    }
}

void SemanticsVerifier::detectCyclicCalls(Node* node) {
    auto programNode = dynamic_cast<ProgramNode *>(node);
    vector<ProcedureNode *> v = programNode->getProcLst();
    vector < ProcName > allProcName;

    for (ProcedureNode *p: v) {
        ProcName name = p->getProcName();
        vector < ProcName > NodesFromP = getAllProcedureCall(p);
        checkIfProcIsDeclared(v, NodesFromP);

        GraphNode *node = new GraphNode(name, NodesFromP);
        graphNodes[name] = node;
        allProcName.push_back(name);
        visited[name], stack[name] = false;
    }
    // perform DFS to check for recursions
    for (int i = 0; i < allProcName.size(); i++) {
        ProcName name = allProcName[i];
        if (!visited[name] && detectCyclicCallsRec(name)) {
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
