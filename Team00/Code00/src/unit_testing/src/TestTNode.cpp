#include <iostream>

#include "TNode.h"

#include "catch.hpp"
using namespace std;

void require(bool b) {
    REQUIRE(b);
}

TEST_CASE("Node Test") {
    Node parent;
    Node node;
    node.setParentNode(&parent);
    CHECK(&parent == node.getParentNode());
}

TEST_CASE("stmt Node Test") {
    int num = 4;
    StmtNode node(num);
    StmtNode *ptr;
    ptr = &node;
    CHECK(num == ptr -> getStmtNumber());
}

TEST_CASE("varNameNode Test") {
    string var = "x";
    VariableNode * varNode = new VariableNode(var);
    CHECK(var == varNode ->getVariableName());
}

TEST_CASE("constValueNode Test") {
    string value = "1";
    ConstValueNode * constValueNode = new ConstValueNode(value);
    CHECK(value == constValueNode->getConstValue());
}

TEST_CASE("Assign node test") {
    string left = "x";
    string right = "y";
    int stmtNo = 4;
    auto varLeftNode = new VariableNode(left);
    auto varRightNode = new VariableNode(right);

    AssignNode * testNode = new AssignNode(4, varLeftNode, varRightNode);
    CHECK(left == testNode -> getLeftNode() ->getVariableName());
    CHECK(right == get<VariableNode*>(testNode ->getRightNode())->getVariableName());
    CHECK(stmtNo == testNode ->getStmtNumber());
    CHECK(testNode == get<VariableNode*>(testNode ->getRightNode())->getParentNode());
}

TEST_CASE("Binary operator node test") {
    ConstValueNode left("1");
    ConstValueNode right("2");
    string plusOperator = "+";
    auto testNode = BinaryOperatorNode(&left, &right, plusOperator);
    CHECK(get<ConstValueNode*>(testNode.getLeftExpr())->getConstValue() == "1");
    CHECK(get<ConstValueNode*>(testNode.getRightExpr())->getConstValue() == "2");
    CHECK(testNode.getBinaryOperator() == plusOperator);
}

TEST_CASE("Relative expression node test") {
    ConstValueNode constValueNode("1");
    string andOperator = "&&";
    auto testNode = RelExprNode(&constValueNode, &constValueNode, andOperator);
    CHECK(get<ConstValueNode*>(testNode.getLeftFactor())->getConstValue() == constValueNode.getConstValue());
    CHECK(get<ConstValueNode*>(testNode.getRightFactor())->getConstValue() == constValueNode.getConstValue());
    CHECK(testNode.getRelativeOperator() == andOperator);
}

TEST_CASE("Condition expression node test") {
    ConstValueNode constValueNode("1");
    string andOperator = "&&";
    RelExprNode relExprNode(&constValueNode, &constValueNode, andOperator);
    // Case: rel_expr
    auto testNode1 = CondExprNode(&relExprNode);
    CHECK(testNode1.getCondOperator().empty());
    CHECK(testNode1.getLeftNode() == nullptr);
    CHECK(testNode1.getRightNode() == nullptr);
    // Case: '!' '(' cond_expr ')'
    string notOperator = "!";
    CondExprNode condExprNode(&relExprNode);
    auto testNode2 = CondExprNode(&condExprNode);
    //CHECK(testNode2.getRelExpr() ); TODO: WRITE EQUALITY CHECK FOR NODE
    CHECK(testNode2.getLeftNode() == nullptr);
    // CHECK(testNode2.getRightNode() == condExprNode); TODO: WRITE EQUALITY CHECK FOR NODE
    CHECK(testNode2.getCondOperator() == notOperator);
    // Case: '(' cond_expr ')' '&&' '(' cond_expr ')' |'(' cond_expr ')' '||' '(' cond_expr ')'
    auto testNode3 = CondExprNode(andOperator, &condExprNode, &condExprNode);
    CHECK(testNode3.getCondOperator() == andOperator);
    // TODO: WRITE EQUALITY CHECK FOR NODE
}

TEST_CASE("While node test") {
    ConstValueNode constValueNode("1");
    string andOperator = "&&";
    RelExprNode relExprNode(&constValueNode, &constValueNode, andOperator);
    CondExprNode condExprNode(&relExprNode);
    StatementList stmtLst = {};
    auto testNode = WhileNode(&condExprNode, stmtLst);
    CHECK(testNode.getStmtLst().size() == 0);
    // TODO: WRITE EQUALITY CHECK FOR NODE
}


