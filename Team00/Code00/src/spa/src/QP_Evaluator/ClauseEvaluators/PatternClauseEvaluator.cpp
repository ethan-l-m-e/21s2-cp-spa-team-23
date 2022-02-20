//
// Created by Tin Hong Wen on 10/2/22.
//
#include "PKB.h"
#include "PatternClauseEvaluator.h"
#include "TNode.h"
#include "StringFormatter.h"

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
    int first = arg.argumentValue.find("\"");
    string rightArg = arg.argumentValue.substr(first + 1, arg.argumentValue.size() - 4);
    //string rightArg = StringFormatter::tokenizeByRegex(arg.argumentValue, "_\"|\"_")[0];
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