//
// Created by Tin Hong Wen on 10/2/22.
//
#include "PKB.h"
#include "PatternClauseEvaluator.h"
#include "TNode.h"


void addToStmtList(AssignNode* assignNode, vector<ResultItem> stmtNumberList);
void addToStmtAndVariableList(AssignNode* assignNode, vector<ResultItem> statementAndVarList);
string retrieveLHSVar(AssignNode* assignNode);
bool matchLHSValue(AssignNode* assignNode, Argument arg);
int retrieveStmtNo(AssignNode* assignNode);
bool matchRHSValue(AssignNode* assignNode, Argument arg);


Result PatternClauseEvaluator::evaluateClause() {
    vector<AssignNode*> listOfAssignNodes;
    //PKB::getInstance() -> getAllAssignPointers();

    vector<ResultItem> assignVarPairList;
    vector<ResultItem> stmtNumberList;

    for (int i = 0; i < listOfAssignNodes.size(); i++) {
        AssignNode * currentNode = listOfAssignNodes[i];
        if (leftIsSynonym() && rightIsPartWildCard()) {
            if(matchRHSValue(currentNode, argRight)) {
                addToStmtAndVariableList(currentNode, assignVarPairList);
            }
        } else if (leftIsSynonym() && rightIsWildCard()) {
            addToStmtAndVariableList(currentNode, assignVarPairList);
        } else if (leftIsFixed() && rightIsWildCard()) {
            if(matchLHSValue(currentNode, argLeft)) {
                addToStmtList(currentNode, stmtNumberList);
            }
        } else if (leftIsFixed() && rightIsPartWildCard()) {
            if(matchLHSValue(currentNode, argLeft) && matchRHSValue(currentNode, argRight)) {
                addToStmtList(currentNode, stmtNumberList);
            }
        } else if (leftIsWildCard() && rightIsPartWildCard()) {
            if(matchRHSValue(currentNode, argRight)) {
                addToStmtList(currentNode, stmtNumberList);
            }
        } else if (leftIsWildCard() && rightIsWildCard()) {
            addToStmtList(currentNode, stmtNumberList);
        }
    }


    // result construction
    if (leftIsSynonym()) {
        // configure resultType, to have both variable names and statement numbers
        result.resultType = ResultType::TUPLES;
        result.resultBoolean = !result.resultItemList.empty();
        result.resultHeader = tuple<string, string>(assignSynonym.argumentValue, argLeft.argumentValue);
        result.resultItemList = assignVarPairList;
    } else {
        // configure resultType to have only a list of statement number
        result.resultType = ResultType::LIST;
        result.resultBoolean = !result.resultItemList.empty();
        result.resultHeader = assignSynonym.argumentValue;
        result.resultItemList = stmtNumberList;
    }

}

void addToStmtList(AssignNode* assignNode, vector<ResultItem> stmtNumberList) {
    stmtNumberList.push_back(retrieveStmtNo(assignNode) + "");
}

void addToStmtAndVariableList(AssignNode* assignNode, vector<ResultItem> StatementAndVarList) {
    ResultItem assignVarPair = tuple<string, string>(retrieveLHSVar(assignNode), retrieveStmtNo(assignNode) + "");
    StatementAndVarList.push_back(assignVarPair);
}

string retrieveLHSVar(AssignNode* assignNode) {
    return assignNode->getLeftNode()->getVariableName();
}

bool matchLHSValue(AssignNode* assignNode, Argument arg) {
    if (retrieveLHSVar(assignNode) == arg.argumentValue) {
        return true;
    } else {
        return false;
    }
}

int retrieveStmtNo(AssignNode* assignNode) {
    return assignNode->getStmtNumber();
}

bool matchRHSValue(AssignNode* assignNode, Argument arg) {    // Arg: Expression node, Objective node
    // perform Search algorithm
    return true;
}


bool PatternClauseEvaluator::leftIsSynonym() {
    return argLeft.argumentType == ArgumentType::SYNONYM;
}
bool PatternClauseEvaluator::leftIsFixed() {
    return argLeft.argumentType != ArgumentType::UNDERSCORE && argLeft.argumentType != ArgumentType::SYNONYM;
}
bool PatternClauseEvaluator::leftIsWildCard() {
    return argLeft.argumentType == ArgumentType::UNDERSCORE;
}
bool PatternClauseEvaluator::rightIsPartWildCard() {
    return argRight.argumentType == ArgumentType::PARTIAL_UNDERSCORE;
}
bool PatternClauseEvaluator::rightIsWildCard() {
    return argRight.argumentType == ArgumentType::UNDERSCORE;

}
