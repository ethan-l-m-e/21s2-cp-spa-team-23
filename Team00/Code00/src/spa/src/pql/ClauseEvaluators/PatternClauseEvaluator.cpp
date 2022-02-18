//
// Created by Tin Hong Wen on 10/2/22.
//
#include "PKB.h"
#include "PatternClauseEvaluator.h"
#include "TNode.h"
#include "StringFormatter.h"
#include "Parser.h"

#include <iostream>




void addToStmtList(AssignNode* assignNode, vector<ResultItem> *stmtNumberList);
void addToStmtAndVariableList(AssignNode* assignNode, vector<ResultItem> *statementAndVarList);
bool matchLHSValue(AssignNode* assignNode, Argument arg);
bool matchRHSValue(AssignNode* assignNode, Argument arg);
bool searchForPotentialMatchInExpression(Expression expressionNode, string rightArg);

string retrieveLHSVar(AssignNode* assignNode);
string retrieveStmtNo(AssignNode* assignNode);

Result PatternClauseEvaluator::evaluateClause() {
    vector<AssignNode*> listOfAssignNodes = PKB::getInstance()->getAllAssignNodes();
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
            addToStmtAndVariableList(currentNode, &assignVarPairList);
        } else if (leftIsSynonym() && rightIsPartWildCard()) {
            if(matchRHSValue(currentNode, argRight)) {
                addToStmtAndVariableList(currentNode, &assignVarPairList);
            }
        } else if (leftIsIdent() && rightIsWildCard()) {
            if(matchLHSValue(currentNode, argLeft)) {
                addToStmtList(currentNode, &stmtNumberList);
            }
        } else if (leftIsIdent() && rightIsPartWildCard()) {
            if(matchLHSValue(currentNode, argLeft) && matchRHSValue(currentNode, argRight)) {
                addToStmtList(currentNode, &stmtNumberList);
            }
        } else if (leftIsWildCard() && rightIsPartWildCard()) {
            if(matchRHSValue(currentNode, argRight)) {
                addToStmtList(currentNode, &stmtNumberList);
            }
        } else if (leftIsWildCard() && rightIsWildCard()) {
            addToStmtList(currentNode, &stmtNumberList);
        } else {
            throw "arguments in pattern clause mismatch " + argLeft.argumentValue + " " + argRight.argumentValue;
        }
    }

    // result construction
    if (leftIsSynonym()) {
        // configure resultType, to have both variable names and assign
        result.resultType = ResultType::TUPLES;
        result.resultBoolean = !assignVarPairList.empty();
        result.resultHeader = tuple<string, string>(assignSynonym.argumentValue, argLeft.argumentValue);
        result.resultItemList = assignVarPairList;
    } else {
        // configure resultType to have only a list of assign
        result.resultType = ResultType::STRING;
        result.resultBoolean = !stmtNumberList.empty();
        result.resultHeader = assignSynonym.argumentValue;
        result.resultItemList = stmtNumberList;
    }

    return result;
}

bool PatternClauseEvaluator::leftIsSynonym() {
    return argLeft.argumentType == ArgumentType::SYNONYM;
}
bool PatternClauseEvaluator::leftIsIdent() {
    return argLeft.argumentType == ArgumentType::IDENT;
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

void addToStmtList(AssignNode *assignNode, vector<ResultItem> *stmtNumberList) {
    string stmtNo = retrieveStmtNo(assignNode);
    stmtNumberList->push_back(stmtNo);
}

void addToStmtAndVariableList(AssignNode *assignNode, vector<ResultItem> *statementAndVarList) {
    ResultItem assignVarPair = tuple<string, string>(retrieveStmtNo(assignNode), retrieveLHSVar(assignNode));
    statementAndVarList->push_back(assignVarPair);
}


// TODO: convert string argument to an expression one. for future iteration requirements
// ideas:
// auto value rightArg as well.
// If same expression variant,
//      compare operator, like var & const
//          if operator same, initiate another exact match with && instead of ||
bool searchForPotentialMatchInExpression(Expression expressionNode, string rightArg) {
    if (auto value = std::get_if<BinaryOperatorNode*>(&expressionNode)) {
        BinaryOperatorNode* operatorNode = *value;
        bool leftResult = searchForPotentialMatchInExpression(operatorNode->getLeftExpr(), rightArg);
        bool rightResult = searchForPotentialMatchInExpression(operatorNode->getRightExpr(), rightArg);
        return leftResult || rightResult;
    } else if (auto value = std::get_if<VariableNode*>(&expressionNode)) {
        VariableNode* varNode = *value;
        if (varNode->getVariableName() == rightArg)     return true;
         else                                           return false;
    } else if(auto value = std::get_if<ConstValueNode*>(&expressionNode)) {
        ConstValueNode* constNode = *value;
        if (constNode->getConstValue() == rightArg)     return true;
        else                                            return false;
    } else {
        throw "cannot understand expression";
    };
}

bool matchLHSValue(AssignNode *assignNode, Argument arg) {
    string trimmed = StringFormatter::tokenizeByRegex(arg.argumentValue, "[ ]*\"[ ]*")[0];
    if (retrieveLHSVar(assignNode) == trimmed)
        return true;
    else
        return false;

}

bool matchRHSValue(AssignNode *assignNode, Argument arg) {
    // convert arg to variable (or expression in the future)
    string rightArg = StringFormatter::tokenizeByRegex(arg.argumentValue, "(_\")|(\"_)")[0];
    //Expression rightAsExpr = Parser::parseExpression(rightArg); //no usage yet for iteration 1
    Expression RHSExpression = assignNode ->getRightNode();
    return searchForPotentialMatchInExpression(RHSExpression, rightArg);
}


string retrieveLHSVar(AssignNode *assignNode) {
    return assignNode->getLeftNode()->getVariableName();
}

string retrieveStmtNo(AssignNode *assignNode) {
    return to_string(assignNode->getStmtNumber());
}




/*
string PatternClauseEvaluator::retrieveLHSVar(AssignNode* assignNode) {
    return assignNode->getLeftNode()->getVariableName();
}

void PatternClauseEvaluator::addToStmtList(AssignNode* assignNode, vector<ResultItem> stmtNumberList) {
    stmtNumberList.push_back(retrieveStmtNo(assignNode) + "");
}

void PatternClauseEvaluator::addToStmtAndVariableList(AssignNode* assignNode, vector<ResultItem> StatementAndVarList) {
    ResultItem assignVarPair = tuple<string, string>(retrieveLHSVar(assignNode), retrieveStmtNo(assignNode) + "");
    StatementAndVarList.push_back(assignVarPair);
}



bool PatternClauseEvaluator::matchLHSValue(AssignNode* assignNode, Argument arg) {      //  not tested yet
    if (retrieveLHSVar(assignNode) == arg.argumentValue) {
        return true;
    } else {
        return false;
    }
}

int PatternClauseEvaluator::retrieveStmtNo(AssignNode* assignNode) {
    return assignNode->getStmtNumber();
}

bool PatternClauseEvaluator::matchRHSValue(AssignNode* assignNode, Argument arg) {    // for partial wildcards
    // convert arg to variable (or expression in the future)
    string rightArg = StringFormatter::tokenizeByRegex(arg.argumentValue, "(_\")|(\"_)")[0];
    // convert into an AST (future issue, for now stick to single variable/const value)
    // TODO: extract assignNode right side, then call searchForMatchInExpression method
    Expression RHSExpression = assignNode ->getRightNode();
    //searchForMatchInExpression(RHSExpression, rightArg);
    return true;
}

bool PatternClauseEvaluator::searchForMatchInExpression(Expression expressionNode, string rightArg) {
    // TODO: complete pattern matching algorithm. search expressionNode to see if can find RHS argument
    // if is variable/const node
    //      compare value with rightArg. if match return true else false
    // else
    //      return searchRHSExpression(leftside) || searchForMatchInExpression(rightSide)
    if (auto value = std::get_if<BinaryOperatorNode*>(&expressionNode)) {
        BinaryOperatorNode* operatorNode = *value;
        bool leftResult = searchForMatchInExpression(operatorNode->getLeftExpr(), rightArg);
        bool rightResult = searchForPotentialMatchInExpression(operatorNode->getRightExpr(), rightArg);
        return leftResult || rightResult;
    } else if (auto value = std::get_if<VariableNode*>(&expressionNode)) {
        VariableNode* varNode = *value;
        if (varNode->getVariableName() == rightArg) {
            return true;
        } else {
            cout << varNode->getVariableName() << " != " << rightArg;
            return false;
        }
    } else if(auto value = std::get_if<ConstValueNode*>(&expressionNode)) {
        ConstValueNode* constNode = *value;
        if (constNode->getConstValue() == rightArg) {
            return true;
        } else {
            cout << constNode->getConstValue() << " != " << rightArg;
            return false;
        }
    } else {
        throw "cannot understand expression";
    };
}
*/