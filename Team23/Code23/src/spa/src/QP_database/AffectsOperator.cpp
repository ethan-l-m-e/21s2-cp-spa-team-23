//
// Created by Tin Hong Wen on 16/3/22.
//

#include "AffectsOperator.h"
#include "PKB/PKB.h"

using namespace std;

AffectsOperator *AffectsOperator::singleton = nullptr;

AffectsOperator* AffectsOperator::getInstance() {
    if (AffectsOperator::singleton == nullptr) {
        AffectsOperator::singleton = new AffectsOperator();
    }
    return AffectsOperator::singleton;
}

bool AffectsOperator::pathExistBetween(NodeCFG *left, NodeCFG *right, int CFGSize) {
    // check if both from same procedure
    // we can use PKB for this purpose? can be used for some optimisation in CFGOperator

    // left modifies v, right uses the same v
    string leftVal = to_string(left->getStatementNumber());
    string modifiedVar = *PKB::getInstance()->relationship.modifiesS.getSetRHS(leftVal).begin();
    string rightVal = to_string(right->getStatementNumber());
    PKB::getInstance()->relationship.usesS.isRelationship(rightVal, modifiedVar);

    // unmodified control flow path

}

bool AffectsOperator::IsReachableForward(NodeCFG* srcNode, NodeCFG* destNode, string variable,
                                     unordered_map<int, bool> &visited,
                                     vector<int> &path) {
    int srcVal = srcNode->getStatementNumber();
    int destVal = destNode->getStatementNumber();

    if(srcVal == destVal) {
        return true;
    }
    visited[srcVal] = true;
    path.push_back(srcVal);

    unordered_set<NodeCFG*> adjNodes = collateAllAdjacentNodes(srcNode);
    unordered_set<NodeCFG*>::iterator adj;
    for(adj = adjNodes.begin(); adj != adjNodes.end(); ++adj) {
        NodeCFG* adjacentNode =  *adj;

        //if modified, terminates path
        string stmtNo = to_string(adjacentNode->getStatementNumber());
        bool modified = PKB::getInstance()->relationship.modifiesS.isRelationship(stmtNo, variable);

        if (!visited[adjacentNode->getStatementNumber()] && !modified) {
            if (IsReachableForward(adjacentNode, destNode, variable, visited, path))
                return true;
        }
    }

    path.pop_back();
    return false;
}