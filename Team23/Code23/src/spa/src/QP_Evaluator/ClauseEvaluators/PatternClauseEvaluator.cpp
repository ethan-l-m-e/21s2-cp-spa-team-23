//
// Created by Tin Hong Wen on 10/2/22.
//
#include <regex>
#include<iostream>

#include "PKB/PKB.h"
#include "PatternClauseEvaluator.h"
#include "TNode/Node.h"
#include "StringFormatter.h"
#include "SourceProcessor/Parser.h"
#include "SourceProcessor/Identifier.h"

bool isSynonym(Argument arg);
bool isIdent(Argument arg);
bool isWildCard(Argument arg);
bool isPartWildCard(Argument arg);

bool matchVariableValue(VariableNode* assignNode, Expression arg);
vector<string> collectControlVarInCondExpr(CondExprNode* condExpr);

void addToStmtList(Node* node, ResultItems *resultSet);
void addToStmtAndVariableList(Node *node, ResultItems *resultSet);
Expression validateAndParseEntRef(string arg);
Expression validateAndParseExpression(string arg);
bool matchExpressionValue(Expression firstExpression, Expression secondExpression, Argument arg);
bool searchForMatchInExpr(Expression expressionNode, Expression arg);
bool performExactMatchExpr(Expression expressionNode, Expression arg);

/**
     * Chart for pattern clause:
     * LHS/RHS      exact                   _something_              _
     * synonym       filtered assign        filtered assign & var   all assign & var
     * fixed        filtered assign         filtered assign         filtered assign
     * _            filtered assign         filtered assign         all assign
     */


bool PatternClauseEvaluator::evaluateClause(ResultTable *resultTable) {
    if(patternSynonymType == SynonymType::ASSIGN) {
        return evaluateAssign(resultTable);
    } else {
        cout << "pattern not ready for if and while synonyms\n";
        return true;
    }

}

bool PatternClauseEvaluator::evaluateWhile(ResultTable* resultTable) {
    return true;
}

bool PatternClauseEvaluator::evaluateIf(ResultTable* resultTable) {
    return true;
}

// function not ready yet
/*
bool PatternClauseEvaluator::evaluateWithFunc_Pointers(ResultTable* resultTable,
                                                       void(*validateAndParse)(Argument, Argument, Argument,
                                                               Expression, Expression),
                                                               ResultItems (*collectResults)(Argument, Argument, Expression, Expression)){
    Argument argLeft = arg1;
    Argument argRight = arg2;
    Argument argLast = arg3;
    Expression varLeft;
    Expression exprRight;
    //validation and parsing algorithm
    validateAndParse(arg1, arg2, arg3, varLeft, exprRight);
    ResultItems results = collectResults(arg1, arg2, varLeft, exprRight);
    constructResults(results, isSynonym(argLeft));
    return false;
}
*/

bool PatternClauseEvaluator::evaluateAssign(ResultTable* resultTable) {
    //validation and LHS/RHS parsing
    Argument argLeft = arg1;
    Argument argRight = arg2;
    Expression varLeft;
    Expression exprRight;
    if(isIdent(argLeft)) {
        varLeft  = validateAndParseEntRef(std::get<std::string>(argLeft.argumentValue));
    }
    if(!isWildCard(argRight)) {
        exprRight = validateAndParseExpression(std::get<std::string>(argRight.argumentValue));
    }
    // setup parsing and results
    unordered_set<AssignNode*> listOfAssignNodes = PKB::getInstance()->statement.assignStatements.getAllStatementNodes();
    ResultItems resultList;

    unordered_set<AssignNode*>::iterator i;
    // process results
    for ( i = listOfAssignNodes.begin(); i != listOfAssignNodes.end(); ++i) {
        AssignNode * currentNode = *i;
        VariableNode* LHSVariable = currentNode->getLeftNode();
        Expression RHSExpression = currentNode ->getRightNode();
        if (isSynonym(argLeft) && isWildCard(argRight)) {
            addToStmtAndVariableList(currentNode, &resultList);
        }
        else if (isIdent(argLeft) && isWildCard(argRight)) {
            if(matchExpressionValue(LHSVariable, varLeft, argLeft)) {
                addToStmtList(currentNode, &resultList);
            }
        }
        else if (isWildCard(argLeft) && isWildCard(argRight)) {
            addToStmtList(currentNode, &resultList);
        }
        else if (isSynonym(argLeft) && (isPartWildCard(argRight) || isIdent(argRight))) {
            if(matchExpressionValue(RHSExpression, exprRight, argRight)) {
                addToStmtAndVariableList(currentNode, &resultList);
            }
        }
        else if (isIdent(argLeft) && (isPartWildCard(argRight) || isIdent(argRight))) {
            if(matchExpressionValue(LHSVariable, varLeft, argLeft) &&
               matchExpressionValue(RHSExpression, exprRight, argRight)) {
                addToStmtList(currentNode, &resultList);
            }
        }
        else if (isWildCard(argLeft) && (isPartWildCard(argRight) || isIdent(argRight))) {
            if(matchExpressionValue(RHSExpression, exprRight, argRight)) {
                addToStmtList(currentNode, &resultList);
            }
        }
        else {
            throw "arguments in pattern clause mismatch " + std::get<std::string>(arg1.argumentValue) + " " + std::get<std::string>(arg2.argumentValue);
        }
    }

    // result construction
    constructResults(resultList, isSynonym(argLeft));
    if(!result.resultBoolean) {
        resultTable->clearTable();
        resultTable->setBooleanResult(false);
        return false;
    }
    mergeResult(resultTable);
    return true;
}

void PatternClauseEvaluator::constructResults(ResultItems results, bool hasTuples) {
    if (hasTuples) {
        // configure resultType, to have both variable names and assign
        result.resultType = ResultType::TUPLES;
        result.resultBoolean = !(get<unordered_set<pair<string, string>>>(results)).empty();
        result.resultHeader = pair<string, string>(std::get<std::string>(patternSynonym.argumentValue),
                                                    std::get<std::string>(arg1.argumentValue));
        result.resultSet = results;

    } else {
        // configure resultType to have only a list of assign
        result.resultType = ResultType::STRING;
        result.resultBoolean = !(get<unordered_set<string>>(results)).empty();
        result.resultHeader = std::get<std::string>(patternSynonym.argumentValue);
        result.resultSet = results;

    }
}

Expression validateAndParseEntRef(string arg) {
    vector<string> exprTokenList = StringFormatter::tokenizeByRegex(arg, "[ ]*\"[ ]*");
    if(exprTokenList.size() <= 0) throw arg + "is invalid entSpec";
    string trimmedArg = exprTokenList[0];
    Expression varNode = Parser::parseExpression(trimmedArg);
    if(auto value = get_if<VariableNode*>(&varNode)) {
        return varNode;
    } else {
        throw "validateAndParseEntRef( " + arg + ") is not a variable";
    }
}

Expression validateAndParseExpression(string arg) {
    vector<string> exprTokenList = StringFormatter::tokenizeByRegex(arg, "[_]?\"[ ]*|[ ]*\"[_]?");
    if(exprTokenList.size() <= 0) throw arg + "is invalid expression spec";
    string trimmedArg = exprTokenList[0];
    if(!Identifier::checkParenthesesCorrectness(trimmedArg, "()")) throw trimmedArg + "is an invalid expression";
    return Parser::parseExpression(trimmedArg);
}

void addToStmtList(Node *node, ResultItems *resultSet) {
    std::unordered_set<std::string> stmtNumberList;
    string stmtNo = to_string(node->getStmtNumber());
    stmtNumberList.insert(stmtNo);
    *resultSet = stmtNumberList;
}

void addToStmtAndVariableList(Node *node, ResultItems *resultSet) {
    std::unordered_set<std::pair<std::string, std::string>> statementAndVarList;
    if(auto assignNode = dynamic_cast<AssignNode*>(node)) {
        auto assignVarPair = pair<string, string>(to_string(assignNode->getStmtNumber()), assignNode->getLeftNode()->getVariableName());
        statementAndVarList.insert(assignVarPair);
    } else if (auto whileNode = dynamic_cast<WhileNode*>(node)) {
        string stmtNo = to_string(whileNode->getStmtNumber());
        vector<VarName> controlVariables = collectControlVarInCondExpr(whileNode->getCondExpr());
        for(VarName controlVar: controlVariables) {
            auto stmtVarPair = pair<string, string>(stmtNo, controlVar);
            statementAndVarList.insert(stmtVarPair);
        }
    } else if (auto ifNode = dynamic_cast<IfNode*>(node)) {
        string stmtNo = to_string(ifNode->getStmtNumber());
        vector<VarName> controlVariables = collectControlVarInCondExpr(ifNode->getCondExpr());
        for(VarName controlVar: controlVariables) {
            auto stmtVarPair = pair<string, string>(stmtNo, controlVar);
            statementAndVarList.insert(stmtVarPair);
        }
    }
    *resultSet = statementAndVarList;
}

vector<string> collectControlVarInCondExpr(CondExprNode* condExpr) {
    return condExpr->getListOfVarUsed();
}

bool searchForMatchInExpr(Expression expressionNode, Expression arg) {
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

bool matchControlVarInCondExpr(CondExprNode* condExpr, Expression arg) {
    if(condExpr->getRelExpr() != nullptr) {
        RelExprNode* relExprNode = condExpr->getRelExpr();
        Expression leftNode = relExprNode->getLeftFactor();
        Expression rightNode = relExprNode->getRightFactor();
        return searchForMatchInExpr(leftNode, arg) || searchForMatchInExpr(rightNode, arg);
        // perform search
    } else if (condExpr->getCondOperator() != "") {
        CondExprNode* innerCondExpr = condExpr->getRightNode();
        return matchControlVarInCondExpr(innerCondExpr, arg);
    } else if (condExpr->getLeftNode() != nullptr && condExpr->getRightNode() != nullptr) {
        CondExprNode* leftCondExpr = condExpr->getLeftNode();
        CondExprNode* rightCondExpr = condExpr->getRightNode();
        return matchControlVarInCondExpr(leftCondExpr, arg) ||
               matchControlVarInCondExpr(rightCondExpr, arg);
    } else {
        throw "there is something wrong with your conditional node. cond Node can only have 1) relExpr 2) relExpr && || relExpr or 3) another cond Op";
    }
}

bool matchExpressionValue(Expression firstExpression, Expression secondExpression, Argument arg) {
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

    return false;
}


bool isSynonym(Argument arg) {return arg.argumentType == ArgumentType::SYNONYM;}

bool isIdent(Argument arg) {return arg.argumentType == ArgumentType::IDENT;}

bool isWildCard(Argument arg) {return arg.argumentType == ArgumentType::UNDERSCORE;}

bool isPartWildCard(Argument arg) {return arg.argumentType == ArgumentType::PARTIAL_UNDERSCORE;}

