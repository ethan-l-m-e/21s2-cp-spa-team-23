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
                                    IsReachableForwardV2);
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
            visited[branch->getLeftNode()->getStatementNumber()] = true;
            visited[lastNodeInLeftInt] = true;
            if(srcVal < destVal && destVal <= lastNodeInLeftInt) {
                cout << "destVal " << destVal << "falls between " << srcVal << " and " << lastNodeInLeftInt << "\n";
                return true;
            }
            unordered_set<NodeCFG *> adjNodes = graphMethods->collateAllAdjacentNodes(branch->getRightNode());
            for (NodeCFG *adjNode: adjNodes) {
                int adjStmtNo = adjNode->getStatementNumber();
                if (!visited[adjStmtNo] && IsReachableForward(adjNode, destNode, visited, path))
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

bool NextTOperator::hasLoopAsParent(int srcVal, int destVal) {

    if(pkb->statement.whileStatements.isStatementNumber(destVal)) {
        if(pkb->relationship.parentT.isRelationship(to_string(destVal), to_string(srcVal))) {
            //cout << "detected loop between "<< srcVal << " and " << destVal << "\n";
            return true;
        }
    }
    stmtSetStr srcParents = pkb->relationship.parentT.getLHS(to_string(srcVal));
    stmtSetStr destParents = pkb->relationship.parentT.getLHS(to_string(destVal));
    vector<string> parentsSet1;
    vector<string> parentsSet2;
    parentsSet1.insert(parentsSet1.end(), srcParents.begin(), srcParents.end());
    parentsSet2.insert(parentsSet2.end(), destParents.begin(), destParents.end());
    std::sort(parentsSet1.begin(), parentsSet1.end());
    std::sort(parentsSet2.begin(), parentsSet2.end());

    std::vector<string>::iterator i, end;
    vector<string> commonParents(std::max(parentsSet1.size(), parentsSet2.size()));
    end = std::set_intersection(parentsSet1.begin(), parentsSet1.end(),
                           parentsSet2.begin(), parentsSet2.end(), commonParents.begin());
    for(i = commonParents.begin(); i != end; ++i) {
        if(pkb->statement.whileStatements.isStatementNumber(*i)) {
            //cout << "both"<< srcVal << " and " << destVal << " have loop " << *i << "as parents\n";
            return true;
        }
    }
    //cout << srcVal << " and " << destVal << "has no parent loop\n";
    return false;
}

int NextTOperator::findLargestValue(stmtSetStr stmtSet) {
    int largest = 0;
    for (string x: stmtSet) {
        if (largest < stoi(x))
            largest = stoi(x);
    }
    return largest;
}

bool NextTOperator::IsReachableForwardV2(NodeCFG* srcNode,
                                       NodeCFG* destNode,
                                       unordered_map<int, bool> &visited,
                                       vector<int> &path) {
    int srcVal = srcNode->getStatementNumber();
    int destVal = destNode->getStatementNumber();
    visited[srcVal] = true;
    path.push_back(srcVal);

    if (srcVal == destVal) {    //match
        return true;
    } else if (srcVal > destVal) {      // instant terminate if src > destVal
        return hasLoopAsParent(srcVal, destVal) ? true : false;
    }

    auto linear = pkb->relationship.followsT.getRHS(to_string(srcVal));
    int largestValInLinear = findLargestValue(linear);

    if (srcVal < destVal && destVal <= largestValInLinear) {
        //cout << "linear check: destVal " << destVal << " falls between " << srcVal << " and " << largestValInLinear << "\n";
        return true;
    }

    if (largestValInLinear == 0) {
        if(pkb->relationship.parentT.isRelationship(to_string(srcVal), to_string(destVal))) return true;
        if (auto loop = dynamic_cast<LoopCFG *>(srcNode)) {
            visited[loop->getNodeInLoop()->getStatementNumber()] = true;
        }
        if(auto branch = dynamic_cast<BranchCFG*>(srcNode)) {
            auto lastNodeInLeft = pkb->relationship.next.
                    getCFGNode(to_string(branch->getRightNode()->getStatementNumber()-1));
            int lastNodeInLeftInt = lastNodeInLeft->getStatementNumber();
            visited[branch->getLeftNode()->getStatementNumber()] = true;
            visited[branch->getRightNode()->getStatementNumber()] = true;
            visited[lastNodeInLeftInt] = true;
            unordered_set<NodeCFG *> adjNodes = graphMethods->collateAllAdjacentNodes(lastNodeInLeft);
            for (NodeCFG *adjNode: adjNodes) {
                int adjStmtNo = adjNode->getStatementNumber();
                if (!visited[adjStmtNo] && IsReachableForward(adjNode, destNode, visited, path))
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
        //cout << "you skipped from " << srcVal << " to " << lastNode->getStatementNumber() << "!\n";
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