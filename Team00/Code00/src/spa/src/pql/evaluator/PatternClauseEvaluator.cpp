//
// Created by Tin Hong Wen on 10/2/22.
//
#include "PKB.h"
#include "PatternClauseEvaluator.h"
#include "TNode.h"

void addToStmtList(AssignNode* assignNode, vector<int> stmtNumberList);
void addToBothList(AssignNode* assignNode, vector<string> varList, vector<int> stmtNumberList);
string retrieveLHSVar(AssignNode* assignNode);
bool matchLHSValue(AssignNode* assignNode, Argument arg);
int retrieveStmtNo(AssignNode* assignNode);
bool matchRHSValue(AssignNode* assignNode, Argument arg);

Result PatternClauseEvaluator::evaluateClause() {
    Argument argLeft = argList[0];
    Argument argRight = argList[1];
    ResultType resultType;
    ResultHeader resultHeader;
    vector<ResultItem> resultItem;

    vector<AssignNode*> listOfAssignNodes;
    //PKB::getInstance() -> getAllAssignPointers();

    vector<string> varList;
    vector<int> stmtNumberList;

    for (int i = 0; i < listOfAssignNodes.size(); i++) {
        // get statement number

        //LHS can be synonym, _ or "concreteValue"
        //RHS can be _, _const or variable_

        // return types table
        //  LHS /   RHS         _const | var_                   _
        //  synonym             filtered LHS var & stmtNumberList       all LHS variable & stmtNumberList
        //  "concrete value"    filtered stmtNumberList                 filtered stmtNumberList
        //      _               filtered stmtNumberList                 all stmtNumberList

        // LHS node
        // RHS node
        // return list of statement numbers that match the pattern clause
        AssignNode * currentNode = listOfAssignNodes[i];
        if (leftIsSynonym() && rightIsPartWildCard()) {
            if(matchRHSValue(currentNode, argRight)) {
                addToBothList(currentNode, varList, stmtNumberList);
            }
        } else if (leftIsSynonym() && rightIsWildCard()) {
            addToStmtList(currentNode, stmtNumberList);

        } else if (leftIsConcrete() && rightIsWildCard()) {
            if(matchLHSValue(currentNode, argLeft)) {
                addToStmtList(currentNode, stmtNumberList);
            }
        } else if (leftIsConcrete() && rightIsPartWildCard()) {
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

    if (leftIsSynonym()) {

    } else {


    }
}

void addToStmtList(AssignNode* assignNode, vector<int> stmtNumberList) {
    stmtNumberList.push_back(retrieveStmtNo(assignNode));
}

void addToBothList(AssignNode* assignNode, vector<string> varList, vector<int> stmtNumberList) {
    varList.push_back(retrieveLHSVar(assignNode));
    stmtNumberList.push_back(retrieveStmtNo(assignNode));

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


bool matchRHSValue(AssignNode* assignNode, string arg) {    // Arg: Expression node, Objective node
    // perform Search algorithm
    return true;
}
