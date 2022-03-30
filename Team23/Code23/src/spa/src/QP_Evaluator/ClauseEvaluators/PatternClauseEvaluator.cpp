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

void addToStmtList(Node* node, unordered_set<string> *stmtNumberList);
void addToStmtAndVariableList(Node *node, unordered_set<pair<string, string>> *statementAndVarList);
Expression validateAndParseEntRef(string arg);
Expression validateAndParseExpression(string arg);
bool matchControlVarInCondExpr(CondExprNode* condExpr, Expression arg);
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
    if (patternSynonymType == SynonymType::ASSIGN) {
        return evaluateAssign(resultTable);
    } else if (patternSynonymType == SynonymType::WHILE) {
        return evaluateWhile(resultTable);
    } else if (patternSynonymType == SynonymType::IF) {
        return evaluateIf(resultTable);
    } else {
        throw "unknown pattern synonyms\n";
    }
}

bool PatternClauseEvaluator::evaluateWhile(ResultTable* resultTable) {
    Argument argLeft = arg1;
    Argument argRight = arg2;
    Expression varLeft;
    Expression exprRight;
    if(isIdent(argLeft)) {
        varLeft  = validateAndParseEntRef(std::get<string>(argLeft.argumentValue));
    }
    if(!isWildCard(argRight)) {
        throw "right side is not a wild card";
    }

    auto listOfWhile = PKB::getInstance()->statement.whileStatements.getAllStatementNodes();

    unordered_set<pair<string, string>> stmtAndVarSet;
    unordered_set<string> stmtSet;

    for(WhileNode* currentNode: listOfWhile) {
        CondExprNode* condExpr = currentNode->getCondExpr();
        if(isSynonym(argLeft)) {
            addToStmtAndVariableList(currentNode, &stmtAndVarSet);
        }
        else if (isWildCard(argLeft)) {
            addToStmtList(currentNode, &stmtSet);
        }
        else if(isIdent(argLeft)) {
            if(matchControlVarInCondExpr(condExpr, varLeft)) {
                addToStmtList(currentNode, &stmtSet);
            }
        }
    }

    // result construction
    if (isSynonym(argLeft)) {
        result = makeResult(make_pair(std::get<string>(patternSynonym.argumentValue), std::get<string>(arg1.argumentValue)), stmtAndVarSet);
    } else {
        result = makeResult(std::get<string>(patternSynonym.argumentValue), stmtSet);
    }

    bool resultValidity = processResult(resultTable);
    return resultValidity;
}

bool PatternClauseEvaluator::evaluateIf(ResultTable* resultTable) {
    Argument argLeft = arg1;
    Argument argRight = arg2;
    Expression varLeft;
    Expression exprRight;
    if(isIdent(argLeft)) {
        varLeft  = validateAndParseEntRef(std::get<string>(argLeft.argumentValue));
    }
    if(!isWildCard(argRight)) {
        throw "2nd argument is not a wild card";
    }
    if(clause->argList.size() == 4) {
        if(!isWildCard(clause->argList[3]))
            throw "3nd argument is not a wild card";
    } else {
        throw "wrong number of arguments";
    }

    auto listOfWhile = PKB::getInstance()->statement.ifStatements.getAllStatementNodes();

    unordered_set<pair<string, string>> stmtAndVarSet;
    unordered_set<string> stmtSet;

    for(IfNode* currentNode: listOfWhile) {
        CondExprNode* condExpr = currentNode->getCondExpr();
        if(isSynonym(argLeft)) {
            addToStmtAndVariableList(currentNode, &stmtAndVarSet);
        }
        else if (isWildCard(argLeft)) {
            addToStmtList(currentNode, &stmtSet);
        }
        else if(isIdent(argLeft)) {
            if(matchControlVarInCondExpr(condExpr, varLeft)) {
                addToStmtList(currentNode, &stmtSet);
            }
        }
    }

    // result construction
    if (isSynonym(argLeft)) {
        result = makeResult(make_pair(std::get<string>(patternSynonym.argumentValue), std::get<string>(arg1.argumentValue)), stmtAndVarSet);
    } else {
        result = makeResult(std::get<string>(patternSynonym.argumentValue), stmtSet);
    }

    bool resultValidity = processResult(resultTable);
    return resultValidity;
}

bool PatternClauseEvaluator::evaluateAssign(ResultTable* resultTable) {
    //validation and LHS/RHS parsing
    Argument argLeft = arg1;
    Argument argRight = arg2;
    Expression varLeft;
    Expression exprRight;
    if(isIdent(argLeft)) {
        varLeft  = validateAndParseEntRef(std::get<string>(argLeft.argumentValue));
    }
    if(!isWildCard(argRight)) {
        exprRight = validateAndParseExpression(std::get<string>(argRight.argumentValue));
    }
    // setup parsing and results
    auto listOfAssignNodes = PKB::getInstance()->statement.assignStatements.getAllStatementNodes();

    unordered_set<pair<string, string>> stmtAndVarSet;
    unordered_set<string> stmtSet;

    unordered_set<AssignNode*>::iterator i;
    // process results
    for ( i = listOfAssignNodes.begin(); i != listOfAssignNodes.end(); ++i) {
        AssignNode * currentNode = *i;
        VariableNode* LHSVariable = currentNode->getLeftNode();
        Expression RHSExpression = currentNode ->getRightNode();
        if (isSynonym(argLeft) && isWildCard(argRight)) {
            addToStmtAndVariableList(currentNode, &stmtAndVarSet);
        }
        else if (isIdent(argLeft) && isWildCard(argRight)) {
            if(matchExpressionValue(LHSVariable, varLeft, argLeft)) {
                addToStmtList(currentNode, &stmtSet);
            }
        }
        else if (isWildCard(argLeft) && isWildCard(argRight)) {
            addToStmtList(currentNode, &stmtSet);
        }
        else if (isSynonym(argLeft) && (isPartWildCard(argRight) || isIdent(argRight))) {
            if(matchExpressionValue(RHSExpression, exprRight, argRight)) {
                addToStmtAndVariableList(currentNode, &stmtAndVarSet);
            }
        }
        else if (isIdent(argLeft) && (isPartWildCard(argRight) || isIdent(argRight))) {
            if(matchExpressionValue(LHSVariable, varLeft, argLeft) &&
               matchExpressionValue(RHSExpression, exprRight, argRight)) {
                addToStmtList(currentNode, &stmtSet);
            }
        }
        else if (isWildCard(argLeft) && (isPartWildCard(argRight) || isIdent(argRight))) {
            if(matchExpressionValue(RHSExpression, exprRight, argRight)) {
                addToStmtList(currentNode, &stmtSet);
            }
        }
        else {
            throw "arguments in pattern clause mismatch " + std::get<string>(arg1.argumentValue) + " " + std::get<string>(arg2.argumentValue);
        }
    }

    // result construction
    if (isSynonym(argLeft)) {
        result = makeResult(make_pair(std::get<string>(patternSynonym.argumentValue), std::get<string>(arg1.argumentValue)), stmtAndVarSet);
    } else {
        result = makeResult(std::get<string>(patternSynonym.argumentValue), stmtSet);
    }
    bool resultValidity = processResult(resultTable);
    return resultValidity;
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

void addToStmtList(Node *node, unordered_set<string> *stmtNumberList) {
    string stmtNo = to_string(node->getStmtNumber());
    stmtNumberList->insert(stmtNo);
}

void addToStmtAndVariableList(Node *node, unordered_set<pair<string, string>> *statementAndVarList) {
    if(auto assignNode = dynamic_cast<AssignNode*>(node)) {
        statementAndVarList->insert(make_pair(to_string(assignNode->getStmtNumber()), assignNode->getLeftNode()->getVariableName()));
    } else if (auto whileNode = dynamic_cast<WhileNode*>(node)) {
        string stmtNo = to_string(whileNode->getStmtNumber());
        vector<VarName> controlVariables = collectControlVarInCondExpr(whileNode->getCondExpr());
        for(VarName controlVar: controlVariables) {
            statementAndVarList->insert(make_pair(stmtNo, controlVar));
        }
    } else if (auto ifNode = dynamic_cast<IfNode*>(node)) {
        string stmtNo = to_string(ifNode->getStmtNumber());
        vector<VarName> controlVariables = collectControlVarInCondExpr(ifNode->getCondExpr());
        for(VarName controlVar: controlVariables) {
            statementAndVarList->insert(make_pair(stmtNo, controlVar));
        }
    }
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