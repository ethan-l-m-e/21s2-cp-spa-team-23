#include <iostream>

#include "TNode.h"

#include "catch.hpp"
using namespace std;

void require(bool b) {
    REQUIRE(b);
}

/*
TEST_CASE("Value Test") {
    string nodeValue = "my Value";
    TNode node(nodeValue);
    CHECK(nodeValue == node.getValue());
}

TEST_CASE("Children Test") {
    string value1 = "pValue";
    string value2 = "cValue1";
    string value3 = "cValue2";
    string value4 = "ccValue1";
    TNode pNode(value1);
    TNode cNode1(value2);
    TNode cNode2(value3);
    TNode ccNode1(value4);
    pNode.addNode(&cNode1);
    pNode.addNode(&cNode2);
    cNode1.addNode(&ccNode1);
    CHECK(2 == pNode.getNumberOfChildNodes());
    CHECK(value2 == pNode.getNode(0) -> getValue());
    CHECK(value3 == pNode.getNode(1) -> getValue());
    CHECK(value4 == pNode.getNode(0) -> getNode(0) -> getValue());

}

TEST_CASE("stmtNoTest") {
    int stmtNo = 1;
    TNode node("value");
    CHECK(!node.hasStmtNo());
    node.setStmtNo(stmtNo);
    CHECK(node.hasStmtNo());
    TNode node2("value", stmtNo);
    CHECK(node.hasStmtNo());
    CHECK(stmtNo == node.getStmtNo());
}
*/

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
    CHECK(right == testNode ->getRightNode() ->getVariableName());
    CHECK(stmtNo == testNode ->getStmtNumber());
}

TEST_CASE("Binary operator node test") {
    shared_ptr<ConstValueNode> left = shared_ptr<ConstValueNode>(new ConstValueNode("1"));
    shared_ptr<ConstValueNode> right = shared_ptr<ConstValueNode>(new ConstValueNode("2"));
    string plusOperator = "+";
    auto testNode = BinaryOperatorNode(left, right, plusOperator);
    CHECK(get<shared_ptr<ConstValueNode>>(testNode.getLeftExpr()).get()->getConstValue() == "1");
    CHECK(get<shared_ptr<ConstValueNode>>(testNode.getRightExpr()).get()->getConstValue() == "2");
}

TEST_CASE("") {

}

