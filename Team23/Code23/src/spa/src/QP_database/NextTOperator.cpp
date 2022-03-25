//
// Created by Tin Hong Wen on 22/3/22.
//

#include "NextTOperator.h"

static bool optimisation_activated = false;
static bool cache_activated = false;

bool NextTOperator::computeRelation(string left, string right) {
    if(stmtIsNotInSource(vector<string>{left, right})) return false;
    NodeCFG* leftNode = retrieveNode(left);
    NodeCFG* rightNode = retrieveNode(right);
    int size = getSize();
    return graphMethods->DFSBoolean(leftNode,
                                    rightNode,
                                    size,
                                    IsReachableForward);
}

unordered_set<string> NextTOperator::computeRHS(string left) {
    if(stmtIsNotInSource(vector<string>{left})) return {};
    NodeCFG* leftNode = retrieveNode(left);
    int size = getSize();
    stmtSetNum resultSet;
    resultSet = graphMethods->DFSResultSet(leftNode,
                                               size,
                                               graphMethods->collateAllAdjacentNodes,
                                               graphMethods->searchNodesAlongPathAfter);

    return convertIntToString(resultSet);
}


unordered_set<string> NextTOperator::computeLHS(string right) {
    if(stmtIsNotInSource(vector<string>{right})) return {};
    NodeCFG* rightNode = retrieveNode(right);
    int size = getSize();
    stmtSetNum resultSet = graphMethods->DFSResultSet(rightNode,
                                                      size,
                                                      graphMethods->collateAllPreviousNodes,
                                                      graphMethods->searchNodesAlongPathBefore);
    return convertIntToString(resultSet);
}



unordered_set<int> NextTOperator::searchNodesAlongPathAfter(NodeCFG* leftNode,
                                                            unordered_map<int, bool> &visited,
                                                            unordered_set<int> resultSet) {
    /*
    int currVal = leftNode->getStatementNumber();
    visited[currVal] = true;
    resultSet.insert(currVal);

    auto linearStmt = pkb->relationship.followsT.getRHS(to_string(currVal));
    if(linearStmt.size() == 0) {
        if(LoopCFG* loopNode = const dynamic_cast<LoopCFG*>(&leftNode)) {
            int nodeInLoopNum = loopNode->getNodeInLoop()->getStatementNumber();
            if(!visited[nodeInLoopNum]) {
                visited[nodeInLoopNum] = true;
                auto allNodesInLoop = loopNode->generateNodesInLoopList();
                resultSet.insert(allNodesInLoop.begin(), allNodesInLoop.end());
            }

            unordered_set<NodeCFG*> adjNodes = graphMethods->collateAllAdjacentNodes(leftNode);
            for(NodeCFG* adjNode: adjNodes) {
                if(!visited[adjNode->getStatementNumber()]) {
                    unordered_set<int> resultSetInAdjacentNode = searchNodesAlongPathAfter(adjNode, visited, resultSet);
                    resultSet.insert(resultSetInAdjacentNode.begin(), resultSetInAdjacentNode.end());
                }
            }
        }else if(auto branchNode = dynamic_cast<BranchCFG*>(leftNode)) {
            int lastNodeLeftBranch = branchNode->getRightNode()->getStatementNumber() - 1;

        }

    } else {
        // find last node in the linear set
        // add all integers between current and last node
        // searchNodeAlongPathAfter(last,)
    }
     */
    return resultSet;
}

bool NextTOperator::IsReachableForward(NodeCFG* srcNode,
                                      NodeCFG* destNode,
                                      unordered_map<int, bool> &visited,
                                      vector<int> &path) {
    int srcVal = srcNode->getStatementNumber();
    int destVal = destNode->getStatementNumber();

    if (srcVal == destVal) {
        return true;
    }
    visited[srcVal] = true;
    path.push_back(srcVal);

    auto linear = pkb->relationship.followsT.getRHS(to_string(srcVal));
    int largestValInLinear = 0;
    for (string x: linear) {
        if (largestValInLinear < stoi(x))
            largestValInLinear = stoi(x);
    }

    if (srcVal < destVal && destVal <= largestValInLinear) {
        cout << "destVal " << destVal << "falls between " << srcVal << " and " << largestValInLinear << "\n";
        return true;
    }

    if (largestValInLinear == 0) {
        if (auto loop = dynamic_cast<LoopCFG *>(srcNode)) {
            auto wholeLoopInOrder = loop->generateNodesInLoopList();
            visited[loop->getNodeInLoop()->getStatementNumber()] = true;
            int largestValInLoop = *wholeLoopInOrder.end()--;
            if (destVal <= largestValInLoop) {
                cout << "destVal " << destVal << "falls between " << srcVal << " and " << largestValInLoop << "\n";
                return true;
            }
        }
        if(auto branch = dynamic_cast<BranchCFG*>(srcNode)) {
            auto lastNodeInLeft = pkb->relationship.next.
                    getCFGNode(to_string(branch->getRightNode()->getStatementNumber()-1));
            int lastNodeInLeftInt = lastNodeInLeft->getStatementNumber();
            visited[lastNodeInLeftInt] = true;
            if(srcVal < destVal && destVal <= lastNodeInLeftInt) {
                cout << "destVal " << destVal << "falls between " << srcVal << " and " << lastNodeInLeftInt << "\n";
                return true;
            }
        }
        unordered_set<NodeCFG *> adjNodes = graphMethods->collateAllAdjacentNodes(srcNode);
        for (NodeCFG *adjNode: adjNodes) {
            int adjStmtNo = adjNode->getStatementNumber();
            if (!visited[adjStmtNo] && IsReachableForward(adjNode, destNode, visited, path))
                return true;
        }
    } else {
        NodeCFG *lastNode = pkb->relationship.next.getCFGNode(to_string(largestValInLinear));
        cout << "you skipped from " << srcVal << " to " << lastNode->getStatementNumber() << "!\n";
        unordered_set<NodeCFG *> adjNodes = graphMethods->collateAllAdjacentNodes(lastNode);
        for (NodeCFG *adjNode: adjNodes) {
            int adjStmtNo = adjNode->getStatementNumber();
            if (!visited[adjStmtNo] && IsReachableForward(adjNode, destNode, visited, path))
                return true;
        }

    }
    path.pop_back();
    return false;
}



NextTOperator *NextTOperator::singleton = nullptr;
NextTOperator::NextTOperator(): CacheOperator(){}
NextTOperator* NextTOperator::getInstance() {
    if (NextTOperator::singleton == nullptr) {
        NextTOperator::singleton = new NextTOperator();
    }
    return NextTOperator::singleton;
}