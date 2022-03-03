//
// Created by Tin Hong Wen on 10/2/22.
//
#include <regex>

#include "PKB.h"
#include "PatternClauseEvaluator.h"
#include "TNode/Node.h"
#include "StringFormatter.h"
#include "SourceProcessor/Parser.h"
#include "SourceProcessor/Identifier.h"


void addToStmtList(AssignNode* assignNode, vector<ResultItem> *stmtNumberList);
void addToStmtAndVariableList(AssignNode* assignNode, vector<ResultItem> *statementAndVarList);
bool validateExpression(string arg);
bool matchVariableValue(VariableNode* assignNode, Argument arg);
bool matchExpressionValue(Expression firstExpression, Expression secondExpression, Argument arg);
bool searchForMatchInExpr(Expression expressionNode, Expression arg);
bool performExactMatchExpr(Expression expressionNode, Expression arg);


string retrieveLHSVar(AssignNode* assignNode);
string retrieveStmtNo(AssignNode* assignNode);

Result PatternClauseEvaluator::evaluateClause() {
    //first, figure out the synonymType
    // then perform accordingly
    vector<AssignNode*> listOfAssignNodes = PKB::getInstance()->getAllAssignNodes();
    vector<ResultItem> assignVarPairList;
    vector<ResultItem> stmtNumberList;

    //check validity of arg and then convert them into expression
    Argument argLeft = arg1;

    vector<string> argRightList = StringFormatter::tokenizeByRegex(arg2.argumentValue, "[_]?\"|\"[_]?");
    if(argRightList.size() <= 0) throw arg2.argumentValue + "is invalid";
    string trimmedArg = argRightList[0];
    if(!Identifier::checkParenthesesCorrectness(trimmedArg, "()")) throw trimmedArg + "is an invalid expression";
    Argument argRight = arg2;
    Expression exprRight;
    if(!rightIsWildCard())
        exprRight = Parser::parseExpression(trimmedArg);

    /**
     * Chart for pattern clause:
     * LHS/RHS      exact                   _something_              _
     * synonym       filtered assign        filtered assign & var   all assign & var
     * fixed        filtered assign         filtered assign         filtered assign
     * _            filtered assign         filtered assign         all assign
     */
    for (int i = 0; i < listOfAssignNodes.size(); i++) {
        AssignNode * currentNode = listOfAssignNodes[i];
        VariableNode* LHSVariable = currentNode->getLeftNode();
        Expression RHSExpression = currentNode ->getRightNode();
        if (leftIsSynonym() && rightIsWildCard()) {
            addToStmtAndVariableList(currentNode, &assignVarPairList);
        } else if (leftIsSynonym() && (rightIsPartWildCard() || rightIsIdent())) {
            if(matchExpressionValue(RHSExpression, exprRight, argRight)) {
                addToStmtAndVariableList(currentNode, &assignVarPairList);
            }
        } else if (leftIsIdent() && rightIsWildCard()) {
            if(matchVariableValue(LHSVariable, argLeft)) {
                addToStmtList(currentNode, &stmtNumberList);
            }
        } else if (leftIsIdent() && (rightIsPartWildCard() || rightIsIdent())) {
            if(matchVariableValue(LHSVariable, argLeft) && matchExpressionValue(RHSExpression, exprRight, argRight)) {
                addToStmtList(currentNode, &stmtNumberList);
            }
        } else if (leftIsWildCard() && (rightIsPartWildCard() || rightIsIdent())) {

            if(matchExpressionValue(RHSExpression, exprRight, argRight)) {
                addToStmtList(currentNode, &stmtNumberList);
            }
        } else if (leftIsWildCard() && rightIsWildCard()) {
            addToStmtList(currentNode, &stmtNumberList);
        } else {
            throw "arguments in pattern clause mismatch " + arg1.argumentValue + " " + arg2.argumentValue;
        }
    }

    // result construction
    if (leftIsSynonym()) {
        // configure resultType, to have both variable names and assign
        result.resultType = ResultType::TUPLES;
        result.resultBoolean = !assignVarPairList.empty();
        result.resultHeader = tuple<string, string>(syn.argumentValue, arg1.argumentValue);
        result.resultItemList = assignVarPairList;
    } else {
        // configure resultType to have only a list of assign
        result.resultType = ResultType::STRING;
        result.resultBoolean = !stmtNumberList.empty();
        result.resultHeader = syn.argumentValue;
        result.resultItemList = stmtNumberList;
    }

    return result;
}

bool PatternClauseEvaluator::leftIsSynonym() {
    return arg1.argumentType == ArgumentType::SYNONYM;
}
bool PatternClauseEvaluator::leftIsIdent() {
    return arg1.argumentType == ArgumentType::IDENT;
}
bool PatternClauseEvaluator::leftIsWildCard() {
    return arg1.argumentType == ArgumentType::UNDERSCORE;
}
bool PatternClauseEvaluator::rightIsPartWildCard() {
    return arg2.argumentType == ArgumentType::PARTIAL_UNDERSCORE;
}
bool PatternClauseEvaluator::rightIsIdent() {
    return arg2.argumentType == ArgumentType::IDENT;
}
bool PatternClauseEvaluator::rightIsWildCard() {
    return arg2.argumentType == ArgumentType::UNDERSCORE;

}

bool validateExpression(string arg) {

    return true;
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
// auto value arg as well.
// If same expression variant,
//      compare operator, like var & const
//          if operator same, initiate another exact match with && instead of ||
bool searchForMatchInExpr(Expression expressionNode, Expression arg) {
    /*
     if (auto binaryNode = std::get_if<BinaryOperatorNode*>(&expressionNode)) {
        BinaryOperatorNode* operatorNode = *binaryNode;
        bool leftResult = searchForMatchInExpr(operatorNode->getLeftExpr(), arg);
        bool rightResult = searchForMatchInExpr(operatorNode->getRightExpr(), arg);
        return leftResult || rightResult;
    } else if (auto value = std::get_if<VariableNode*>(&expressionNode)) {
        VariableNode* varNode = *value;
        if (varNode->getVariableName() == arg)     return true;
         else                                           return false;
    } else if(auto value = std::get_if<ConstValueNode*>(&expressionNode)) {
        ConstValueNode* constNode = *value;
        if (constNode->getConstValue() == arg)     return true;
        else                                            return false;
    } else {
        throw "cannot understand expression";
    };
     */
    /**
     * perform exact matching, if it fails, go down the different paths to see if correct or not
     */
    bool hasMatch = performExactMatchExpr(expressionNode, arg);
    if(hasMatch) {
        return true;
    } else if(auto value = std::get_if<BinaryOperatorNode*>(&expressionNode)) {
        BinaryOperatorNode* operatorNode = *value;
        bool leftResult = searchForMatchInExpr(operatorNode->getLeftExpr(), arg);
        bool rightResult = searchForMatchInExpr(operatorNode->getRightExpr(), arg);
        return leftResult || rightResult;
    } else {
        return false;
    }
}

bool performExactMatchExpr(Expression expressionNode, Expression arg) {
    if(auto binary = std::get_if<BinaryOperatorNode*>(&expressionNode)) {
        if(auto argBinary = std::get_if<BinaryOperatorNode*>(&arg)) {
            BinaryOperatorNode* opNode1 = *binary;
            BinaryOperatorNode* opNode2 = *argBinary;
            if(opNode1->getBinaryOperator() == opNode2->getBinaryOperator()) {
                bool leftResult = performExactMatchExpr(opNode1->getLeftExpr(), opNode2->getLeftExpr());
                bool rightResult = performExactMatchExpr(opNode1->getRightExpr(), opNode2->getRightExpr());
                return leftResult && rightResult;
            } else return false;
        } else return false;
    } else if (auto variable = std::get_if<VariableNode*>(&expressionNode)) {
        if(auto argVariable = std::get_if<VariableNode*>(&arg)) {
            VariableNode* varNode1 = *variable;
            VariableNode* varNode2 = *argVariable;
            if (varNode1->getVariableName() == varNode2->getVariableName()) return true;
            else return false;
        } else return false;
    } else if(auto constant = std::get_if<ConstValueNode*>(&expressionNode)) {
        if(auto argConstant = std::get_if<ConstValueNode*>(&arg)) {
            ConstValueNode* varNode1 = *constant;
            ConstValueNode* varNode2 = *argConstant;
            if (varNode1->getConstValue() == varNode2->getConstValue()) return true;
            else return false;
        } else return false;
    } else {
        cout << "cannot understand expression in performExactMatchExpr\n";
        return false;
    }
}

bool matchVariableValue(VariableNode *varNode, Argument arg) {
    string trimmed = StringFormatter::tokenizeByRegex(arg.argumentValue, "[ ]*\"[ ]*")[0];
    if (varNode->getVariableName() == trimmed)
        return true;
    else
        return false;

}

bool matchExpressionValue(Expression firstExpression, Expression secondExpression, Argument arg) {
    // convert arg to variable (or secondExpression in the future)

    /*
    int first = arg.argumentValue.find("\"");
    string rightArg = arg.argumentValue.substr(first + 1, arg.argumentValue.size() - 4);
    //string rightArg = StringFormatter::tokenizeByRegex(arg.argumentValue, "_\"|\"_")[0];
    Expression rightAsExpr = Parser::parseExpression(rightArg); //no usage yet for iteration 1
    Expression RHSExpression = assignNode ->getRightNode();
    return searchForMatchInExpr(RHSExpression, rightAsExpr);
*/
    /**
     * check if the argument is exact or part wildcard
     * if exact, go straight to direct matching
     * if wildcard, go to searching -> matching
     */
     if(arg.argumentType == ArgumentType::IDENT){
         return performExactMatchExpr(firstExpression, secondExpression);

     } else if (arg.argumentType == ArgumentType::PARTIAL_UNDERSCORE) {
         // perform searching
         bool result =  searchForMatchInExpr(firstExpression, secondExpression);
         return result;
     }
}


string retrieveLHSVar(AssignNode *assignNode) {
    return assignNode->getLeftNode()->getVariableName();
}

string retrieveStmtNo(AssignNode *assignNode) {
    return to_string(assignNode->getStmtNumber());
}