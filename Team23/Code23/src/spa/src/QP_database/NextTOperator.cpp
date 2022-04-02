//
// Created by Tin Hong Wen on 22/3/22.
//

#include "NextTOperator.h"


bool NextTOperator::computeRelation(string left, string right) {
    if(stmtIsNotInSource(vector<string>{left, right})) return false;
    NodeCFG* leftNode = retrieveNode(left);
    NodeCFG* rightNode = retrieveNode(right);
    int size = getSize();
    if(isOptimised()) {
        return graphMethods->DFSBoolean(leftNode,
                                        rightNode,
                                        size,
                                        IsReachableForwardV2);
    } else {
        return graphMethods->DFSBoolean(leftNode,
                                        rightNode,
                                        size,
                                        graphMethods->IsReachableForward);
    }
}

unordered_set<string> NextTOperator::computeRHS(string left) {
    if(stmtIsNotInSource(vector<string>{left})) return {};
    stmtSetStr  resultSet;
    stmtSetStr allStmtNo = pkb->statement.statements.getAllStatementNumbers();
    for(stmtStr right: allStmtNo){
        if(computeRelation(left, right)) {
            resultSet.insert(right);
        }
    }
    return resultSet;
}


unordered_set<string> NextTOperator::computeLHS(string right) {
    if(stmtIsNotInSource(vector<string>{right})) return {};
    stmtSetStr  resultSet;
    stmtSetStr allStmtNo = pkb->statement.statements.getAllStatementNumbers();
    for(stmtStr left: allStmtNo){
        if(computeRelation(left, right)) {
            resultSet.insert(left);
        }
    }
    return resultSet;
}

bool NextTOperator::hasLoopAsParent(int srcVal, int destVal) {

    if(pkb->statement.whileStatements.isStatementNumber(std::to_string(destVal))) {
        if(pkb->relationship.parentT.isRelationship(to_string(destVal), to_string(srcVal))) {
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
            return true;
        }
    }
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

/**
 * an optimised version of DFS search. rules it used:
 * 1) if dest is located in FollowsT or between gaps in followsT, returns true
 * 2) if src is a while or a branch, perform ParentsT.getRHS. any dest value that matches returns true
 * 3) if srcVal exceeds destVal, perform ParentT.getLHS for both and perform set intersection.
 * If any while loop is present return true, else false. Can can be expensive (due to sorting) and inconclusive,
 * so it is performed when src > dest (as src > dest is likely false unless a while loop is present)
 */
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
        // performs #3 using set intersection. only performed at most once in every computeRelation algo
        return hasLoopAsParent(srcVal, destVal) ? true : false;
    }

    // performs #1
    auto linear = pkb->relationship.followsT.getRHS(to_string(srcVal));
    int largestValInLinear = findLargestValue(linear);
    if (srcVal < destVal && destVal <= largestValInLinear) {
        return true;
    }


    if (largestValInLinear == 0) {
        //#erforms #2
        if(pkb->relationship.parentT.isRelationship(to_string(srcVal), to_string(destVal))) {
            return true;
        }

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

            // skips over both branches, and then perform recursion on the merge branch (if any)
            unordered_set<NodeCFG *> adjNodes = graphMethods->collateAllAdjacentNodes(lastNodeInLeft);
            for (NodeCFG *adjNode: adjNodes) {
                int adjStmtNo = adjNode->getStatementNumber();
                if (!visited[adjStmtNo] && IsReachableForwardV2(adjNode, destNode, visited, path))
                    return true;
            }
        }
        // gets nextNode to potentially step out of nesting
        unordered_set<NodeCFG *> adjNodes = graphMethods->collateAllAdjacentNodes(srcNode);
        for (NodeCFG *adjNode: adjNodes) {
            int adjStmtNo = adjNode->getStatementNumber();
            if (!visited[adjStmtNo] && IsReachableForwardV2(adjNode, destNode, visited, path))
                return true;
        }
    } else {
        // gets nextNode to potentially step out of nesting
        NodeCFG *lastNode = pkb->relationship.next.getCFGNode(to_string(largestValInLinear));
        unordered_set<NodeCFG *> adjNodes = graphMethods->collateAllAdjacentNodes(lastNode);

        for (NodeCFG *adjNode: adjNodes) {
            int adjStmtNo = adjNode->getStatementNumber();
            if (!visited[adjStmtNo] && IsReachableForwardV2(adjNode, destNode, visited, path))
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