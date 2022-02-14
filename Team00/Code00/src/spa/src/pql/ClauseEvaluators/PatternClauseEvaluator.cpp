//
// Created by Tin Hong Wen on 10/2/22.
//
#include "PKB.h"
#include "PatternClauseEvaluator.h"
#include "TNode.h"
#include "StringFormatter.h"


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

    /**
     * Chart for pattern clause:
     * LHS/RHS      _something_              _
     * synonym      filtered assign & var   all assign & var
     * fixed        filtered assign         filtered assign
     * _            filtered assign         all assign
     */
    for (int i = 0; i < listOfAssignNodes.size(); i++) {
        AssignNode * currentNode = listOfAssignNodes[i];
        if (leftIsSynonym() && rightIsWildCard()) {
            addToStmtAndVariableList(currentNode, assignVarPairList);
        } else if (leftIsSynonym() && rightIsPartWildCard()) {
            if(matchRHSValue(currentNode, argRight))
                addToStmtAndVariableList(currentNode, assignVarPairList);
        } else if (leftIsFixed() && rightIsWildCard()) {
            if(matchLHSValue(currentNode, argLeft))
                addToStmtList(currentNode, stmtNumberList);
        } else if (leftIsFixed() && rightIsPartWildCard()) {
            if(matchLHSValue(currentNode, argLeft) && matchRHSValue(currentNode, argRight))
                addToStmtList(currentNode, stmtNumberList);
        } else if (leftIsWildCard() && rightIsPartWildCard()) {
            if(matchRHSValue(currentNode, argRight))
                addToStmtList(currentNode, stmtNumberList);
        } else if (leftIsWildCard() && rightIsWildCard()) {
            addToStmtList(currentNode, stmtNumberList);
        }
    }

    // result construction
    if (leftIsSynonym()) {
        // configure resultType, to have both variable names and assign
        result.resultType = ResultType::TUPLES;
        result.resultBoolean = !result.resultItemList.empty();
        result.resultHeader = tuple<string, string>(assignSynonym.argumentValue, argLeft.argumentValue);
        result.resultItemList = assignVarPairList;
    } else {
        // configure resultType to have only a list of assign
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

bool matchLHSValue(AssignNode* assignNode, Argument arg) {      //  not tested yet
    if (retrieveLHSVar(assignNode) == arg.argumentValue) {
        return true;
    } else {
        return false;
    }
}

int retrieveStmtNo(AssignNode* assignNode) {
    return assignNode->getStmtNumber();
}

bool matchRHSValue(AssignNode* assignNode, Argument arg) {    // for partial wildcards
    // convert arg to variable (or expression in the future)
    string rightArg = StringFormatter::tokenizeByRegex(arg.argumentValue, "(_\")|(\"_)")[0];
    // convert into an AST (future issue, for now stick to single variable/const value)
    // TODO: extract assignNode right side, then call searchForMatchInExpression method
    // extract right side of Assign node
    // searchForMatchInExpression(right side of AssignNode, rightArg)
    return true;
}

bool searchForMatchInExpression(BinaryOperatorNode* expressionNode, string rightArg) {
    // TODO: complete pattern matching algorithm. search expressionNode to see if can find RHS argument
    // if is variable/const node
    //      compare value with rightArg. if match return true else false
    // else
    //      return searchRHSExpression(leftside) || searchForMatchInExpression(rightSide)
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
