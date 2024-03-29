//
// Created by Tin Hong Wen on 5/2/22.
//
#include "iostream"
#include "SourceProcessor/RelationshipExtractor.h"
#include "SourceProcessor/EntityExtractor.h"
#include "TNode/TNode.h"
#include "catch.hpp"
#include "PKB/PKB.h"

using namespace std;

VariableNode v1 = VariableNode("y");
VariableNode v2 = VariableNode("x");
VariableNode v3 = VariableNode("a");
VariableNode v4 = VariableNode("b");
RelExprNode relNode = RelExprNode(&v2,&v1,"<");
RelExprNode* relPtr = &relNode;
CondExprNode defaultCond = CondExprNode(relPtr);
CondExprNode* condPtr = &defaultCond;
StatementList emptyStmtLst = {};

auto aNode= AssignNode(1,&v2,&v1);
auto bNode= AssignNode(2,&v3,&v4);
auto cNode= AssignNode(3,&v1,&v4);
auto dNode= AssignNode(5,&v2,&v3);
auto eNode= AssignNode(6,&v4,&v1);
auto fNode= AssignNode(7,&v3,&v2);

ProcNameNode p = ProcNameNode("test");
ProcNameNode p1 = ProcNameNode("name1");
ProcNameNode p2 = ProcNameNode("name2");
ProcNameNode p3 = ProcNameNode("name3");
ProcNameNode p4 = ProcNameNode("name4");

TEST_CASE("test follows - basic") {
    StatementList defaultStmtLst;
    StatementList defaultStmtLst2;

    defaultStmtLst.push_back(&aNode);
    defaultStmtLst.push_back(&bNode);
    defaultStmtLst.push_back(&cNode);

    ProcedureNode pNode = ProcedureNode(&p, defaultStmtLst);

    RelationshipExtractor::extractFollows(&pNode);
    REQUIRE(PKB::getInstance()->relationship.follows.isRelationship("1","2"));
    REQUIRE(PKB::getInstance()->relationship.follows.isRelationship("2","3"));
}
TEST_CASE("test follows - basic - if/else") {
    StatementList defaultStmtLst;
    StatementList defaultStmtLst2;

    defaultStmtLst.push_back(&aNode);
    defaultStmtLst.push_back(&bNode);
    defaultStmtLst.push_back(&cNode);

    defaultStmtLst2.push_back(&dNode);
    defaultStmtLst2.push_back(&eNode);

    IfNode iNode = IfNode(0,condPtr,defaultStmtLst,defaultStmtLst2);
    RelationshipExtractor::extractFollows(&iNode);
    REQUIRE(PKB::getInstance()->relationship.follows.isRelationship("1","2"));
    REQUIRE(PKB::getInstance()->relationship.follows.isRelationship("2","3"));
    REQUIRE(PKB::getInstance()->relationship.follows.isRelationship("3","5")==false);
    REQUIRE(PKB::getInstance()->relationship.follows.isRelationship("5","6"));
    REQUIRE(PKB::getInstance()->relationship.follows.isRelationship("2","1")==false);
    REQUIRE(PKB::getInstance()->relationship.follows.isRelationship("3","2")==false);
    REQUIRE(PKB::getInstance()->relationship.follows.isRelationship("5","3")==false);
    REQUIRE(PKB::getInstance()->relationship.follows.isRelationship("6","5")==false);
    REQUIRE(PKB::getInstance()->relationship.follows.isRelationship("1","3")==false);
    REQUIRE(PKB::getInstance()->relationship.follows.isRelationship("1","4")==false);

}
TEST_CASE("test follows - nested") {
    auto aaNode= AssignNode(1,&v2,&v1);
    auto abNode= AssignNode(2,&v3,&v4);
    auto acNode= AssignNode(4,&v1,&v4);
    auto adNode= AssignNode(5,&v2,&v3);
    auto aeNode= AssignNode(7,&v4,&v1);

    StatementList defaultStmtLst;
    StatementList defaultStmtLst2;
    StatementList defaultStmtLst3;

    defaultStmtLst.push_back(&aaNode);
    defaultStmtLst.push_back(&abNode);

    defaultStmtLst2.push_back(&acNode);
    defaultStmtLst2.push_back(&adNode);

    defaultStmtLst3.push_back(&aeNode);

    WhileNode w2Node = WhileNode(6, condPtr, defaultStmtLst3);
    defaultStmtLst2.push_back(&w2Node);
    WhileNode w1Node = WhileNode(3, condPtr, defaultStmtLst2);
    defaultStmtLst.push_back(&w1Node);

    ProcedureNode pNode = ProcedureNode(&p, defaultStmtLst);

    RelationshipExtractor::extractFollows(&pNode);
    REQUIRE(PKB::getInstance()->relationship.follows.isRelationship("1","2"));
    REQUIRE(PKB::getInstance()->relationship.follows.isRelationship("2","1")==false);
    REQUIRE(PKB::getInstance()->relationship.follows.isRelationship("2","3"));
    REQUIRE(PKB::getInstance()->relationship.follows.isRelationship("4","5"));
    REQUIRE(PKB::getInstance()->relationship.follows.isRelationship("6","5")==false);
    REQUIRE(PKB::getInstance()->relationship.follows.isRelationship("5","6"));
    REQUIRE(PKB::getInstance()->relationship.follows.isRelationship("7","6")==false);
    REQUIRE(PKB::getInstance()->relationship.follows.isRelationship("6","7")==false);
    REQUIRE(PKB::getInstance()->relationship.follows.isRelationship("4","3")==false);
    REQUIRE(PKB::getInstance()->relationship.follows.isRelationship("3","4")==false);
    REQUIRE(PKB::getInstance()->relationship.follows.isRelationship("3","5")==false);
    REQUIRE(PKB::getInstance()->relationship.follows.isRelationship("3","6")==false);
    REQUIRE(PKB::getInstance()->relationship.follows.isRelationship("3","7")==false);
}


TEST_CASE("test follows - fail test") {
    StatementList defaultStmtLst;
    StatementList defaultStmtLst2;

    defaultStmtLst.push_back(&aNode);
    defaultStmtLst.push_back(&bNode);
    defaultStmtLst.push_back(&cNode);

    ProcedureNode pNode = ProcedureNode(&p, defaultStmtLst);
    WhileNode wNode = WhileNode(0, condPtr, defaultStmtLst);

    RelationshipExtractor::extractFollows(&pNode);
    REQUIRE(PKB::getInstance()->relationship.follows.isRelationship("0","2")==false);
    REQUIRE(PKB::getInstance()->relationship.follows.isRelationship("1","3")==false);
}

TEST_CASE("test follows* - basic") {
    StatementList defaultStmtLst;
    StatementList defaultStmtLst2;

    defaultStmtLst.push_back(&aNode);
    defaultStmtLst.push_back(&bNode);
    defaultStmtLst.push_back(&cNode);

    ProcedureNode pNode = ProcedureNode(&p, defaultStmtLst);

    RelationshipExtractor::extractFollows(&pNode);
    REQUIRE(PKB::getInstance()->relationship.followsT.isRelationship("1","3"));
}

TEST_CASE("test parents - basic while") {
    StatementList defaultStmtLst;

    defaultStmtLst.push_back(&aNode);
    defaultStmtLst.push_back(&bNode);
    defaultStmtLst.push_back(&cNode);

    WhileNode wNode = WhileNode(0, condPtr, defaultStmtLst);
    vector<StmtLstNode*> v;
    v.push_back(&wNode);
    RelationshipExtractor::extractParent(&wNode,v);
    unordered_set<string> mySet = PKB::getInstance()->relationship.parent.getLHS("2");
    for (const auto& elem: mySet) {
        /* ... process elem ... */
        cout<<elem;
        cout<<"\n";
    }
    REQUIRE(PKB::getInstance()->relationship.parent.isRelationship("0","2"));
    REQUIRE(PKB::getInstance()->relationship.parent.isRelationship("1","1")==false);
}
TEST_CASE("test parents - basic if") {
    StatementList defaultStmtLst;
    StatementList defaultStmtLst2;

    defaultStmtLst.push_back(&aNode);
    defaultStmtLst.push_back(&bNode);
    defaultStmtLst.push_back(&cNode);

    defaultStmtLst2.push_back(&dNode);
    defaultStmtLst2.push_back(&eNode);

    IfNode iNode = IfNode(0,condPtr,defaultStmtLst,defaultStmtLst2);
    vector<StmtLstNode*> v;
    RelationshipExtractor::extractParent(&iNode,v);
    unordered_set<string> mySet = PKB::getInstance()->relationship.parent.getLHS("2");
    for (const auto& elem: mySet) {
        /* ... process elem ... */
        cout<<elem;
        cout<<"\n";
    }
    REQUIRE(PKB::getInstance()->relationship.parent.isRelationship("0","2"));
    REQUIRE(PKB::getInstance()->relationship.parent.isRelationship("0","5"));
}

TEST_CASE("test parents - fail") {
    StatementList defaultStmtLst;

    defaultStmtLst.push_back(&aNode);
    defaultStmtLst.push_back(&bNode);
    defaultStmtLst.push_back(&cNode);

    WhileNode wNode = WhileNode(0, condPtr, defaultStmtLst);
    vector<StmtLstNode*> v;
    v.push_back(&wNode);
    RelationshipExtractor::extractParent(&wNode,v);
    REQUIRE(PKB::getInstance()->relationship.parent.isRelationship("1","2")==false);
}

TEST_CASE("test parents* - basic") {
    StatementList defaultStmtLst;
    StatementList defaultStmtLst2;

    defaultStmtLst.push_back(&aNode);
    defaultStmtLst.push_back(&bNode);
//    defaultStmtLst.push_back(&cNode);

//    StatementList nestedStatementList;
//    nestedStatementList.push_back(&aNode);
//    nestedStatementList.push_back(&bNode);
    defaultStmtLst2.push_back(&dNode);
    defaultStmtLst2.push_back(&eNode);

    WhileNode w1Node = WhileNode(3, condPtr, defaultStmtLst2);
    defaultStmtLst.push_back(&w1Node);
    WhileNode w2Node = WhileNode(0, condPtr, defaultStmtLst);

    vector<StmtLstNode*> v;
    RelationshipExtractor::extractParent(&w2Node,v);
    REQUIRE(PKB::getInstance()->relationship.parentT.isRelationship("0","6"));
    REQUIRE(PKB::getInstance()->relationship.parentT.isRelationship("0","5"));
}

TEST_CASE("test uses - basic") {
    RelationshipExtractor::extractUses(&aNode);
    REQUIRE(PKB::getInstance()->relationship.usesS.isRelationship("1","y"));
}

TEST_CASE("test uses - container statement") {
    StatementList defaultStmtLst;
    StatementList defaultStmtLst3;

    defaultStmtLst.push_back(&aNode);
    defaultStmtLst.push_back(&bNode);
    defaultStmtLst.push_back(&cNode);
    defaultStmtLst3.push_back(&dNode);
    defaultStmtLst3.push_back(&eNode);

    auto wNode = WhileNode(3, condPtr, defaultStmtLst3);
    RelationshipExtractor::extractUses(&wNode);
    REQUIRE(PKB::getInstance()->relationship.usesS.isRelationship("3","a"));
}

TEST_CASE("test uses - call statement") {
    ProcedureList procLst;
    StatementList s1, s2;
    auto callNode = CallNode(2, &p1);
    s1.push_back(&aNode);
    s2.push_back(&callNode);
    ProcedureNode proc1 = ProcedureNode(&p1, s1);
    ProcedureNode proc2 = ProcedureNode(&p2, s2);
    procLst.push_back(&proc1);
    procLst.push_back(&proc2);
    ProgramNode prog = ProgramNode(procLst);
    RelationshipExtractor::extractUses(&callNode);
    REQUIRE(PKB::getInstance()->relationship.usesS.isRelationship("2","y"));
}

TEST_CASE("test modifies - basic") {
    RelationshipExtractor::extractModifies(&aNode);
    REQUIRE(PKB::getInstance()->relationship.modifiesS.isRelationship("1","x"));
}

TEST_CASE("test Modifies - container statement") {
    StatementList defaultStmtLst;
    StatementList defaultStmtLst4;

    defaultStmtLst.push_back(&aNode);
    defaultStmtLst.push_back(&bNode);
    defaultStmtLst.push_back(&cNode);
    defaultStmtLst4.push_back(&dNode);
    defaultStmtLst4.push_back(&eNode);
    auto wNode = WhileNode(3, condPtr, defaultStmtLst4);
    cout<<defaultStmtLst4.size();
    RelationshipExtractor::extractModifies(&wNode);
    REQUIRE(PKB::getInstance()->relationship.modifiesS.isRelationship("3","x"));
}

TEST_CASE("test Modifies - call statement") {
    ProcedureList procLst;
    StatementList s1, s2;
    auto callNode = CallNode(2, &p1);
    s1.push_back(&aNode);
    s2.push_back(&callNode);
    ProcedureNode proc1 = ProcedureNode(&p1, s1);
    ProcedureNode proc2 = ProcedureNode(&p2, s2);
    procLst.push_back(&proc1);
    procLst.push_back(&proc2);
    ProgramNode prog = ProgramNode(procLst);
    RelationshipExtractor::extractModifies(&callNode);
    REQUIRE(PKB::getInstance()->relationship.modifiesS.isRelationship("2","x"));
}

TEST_CASE("test next - basic") {
    PKB::getInstance()->clearPKB();

    ProcedureList procLst;
    StatementList s1;
    s1.push_back(&aNode);
    s1.push_back(&bNode);
    ProcNameNode pNew = ProcNameNode("test1");
    ProcNameNode p1New = ProcNameNode("name11");
    ProcNameNode p2New = ProcNameNode("name21");

    ProcedureNode proc1 = ProcedureNode(&p1New, s1);
    procLst.push_back(&proc1);
    ProgramNode prog = ProgramNode(procLst);
    RelationshipExtractor::extractCFG(&prog);
    REQUIRE(PKB::getInstance()->relationship.next.isRelationship("1","2"));
}

TEST_CASE("test next - basic while") {
    PKB::getInstance()->clearPKB();
    ProcNameNode pNew = ProcNameNode("test1");
    ProcNameNode p1New = ProcNameNode("name11");
    ProcNameNode p2New = ProcNameNode("name21");

    ProcedureList procLst;
    StatementList s1,s2;
    s1.push_back(&aNode);
    s1.push_back(&bNode);
    s1.push_back(&cNode);
    s2.push_back(&dNode);
    s2.push_back(&eNode);

    auto wNode = WhileNode(4, condPtr, s2);
    s1.push_back(&wNode);

    ProcedureNode proc1 = ProcedureNode(&p1New, s1);
    procLst.push_back(&proc1);
    ProgramNode prog = ProgramNode(procLst);
    RelationshipExtractor::extractCFG(&prog);
    REQUIRE(PKB::getInstance()->relationship.next.isRelationship("1","2"));
    REQUIRE(PKB::getInstance()->relationship.next.isRelationship("2","3"));
    REQUIRE(PKB::getInstance()->relationship.next.isRelationship("1","3")==false);
    REQUIRE(PKB::getInstance()->relationship.next.isRelationship("2","4")==false);
    REQUIRE(PKB::getInstance()->relationship.next.isRelationship("1","4")==false);
    REQUIRE(PKB::getInstance()->relationship.next.isRelationship("3","4"));
    REQUIRE(PKB::getInstance()->relationship.next.isRelationship("4","5"));
    REQUIRE(PKB::getInstance()->relationship.next.isRelationship("5","6"));
    REQUIRE(PKB::getInstance()->relationship.next.isRelationship("6","4"));
}

TEST_CASE("test next - basic if") {
    PKB::getInstance()->clearPKB();

    ProcedureList procLst;
    StatementList defaultStmtLst;
    StatementList defaultStmtLst1;
    StatementList defaultStmtLst2;

    ProcNameNode pNew = ProcNameNode("test1");

    defaultStmtLst.push_back(&aNode);
    defaultStmtLst1.push_back(&bNode);
    defaultStmtLst1.push_back(&cNode);

    defaultStmtLst2.push_back(&dNode);
    defaultStmtLst2.push_back(&eNode);

    IfNode iNode = IfNode(4,condPtr,defaultStmtLst1,defaultStmtLst2);

    defaultStmtLst.push_back(&iNode);
    defaultStmtLst.push_back(&fNode);

    ProcedureNode proc1 = ProcedureNode(&pNew, defaultStmtLst);
    procLst.push_back(&proc1);
    ProgramNode prog = ProgramNode(procLst);
    RelationshipExtractor::extractCFG(&prog);
    REQUIRE(PKB::getInstance()->relationship.next.isRelationship("1","4"));
    REQUIRE(PKB::getInstance()->relationship.next.isRelationship("4","5"));
    REQUIRE(PKB::getInstance()->relationship.next.isRelationship("4","2"));
    REQUIRE(PKB::getInstance()->relationship.next.isRelationship("2","3"));
    REQUIRE(PKB::getInstance()->relationship.next.isRelationship("5","6"));
    REQUIRE(PKB::getInstance()->relationship.next.isRelationship("6","7"));
    REQUIRE(PKB::getInstance()->relationship.next.isRelationship("3","7"));
}
TEST_CASE("test next - nested while-if") {
    PKB::getInstance()->clearPKB();

    ProcedureList procLst;
    StatementList defaultStmtLst;
    StatementList defaultStmtLst1;
    StatementList defaultStmtLst2;
    StatementList defaultStmtLst3;
    ProcNameNode pNew = ProcNameNode("test1");

    defaultStmtLst.push_back(&aNode);
    defaultStmtLst1.push_back(&bNode);
    defaultStmtLst2.push_back(&cNode);
    defaultStmtLst3.push_back(&dNode);

    IfNode iNode = IfNode(4,condPtr,defaultStmtLst2,defaultStmtLst3);

    defaultStmtLst1.push_back(&iNode);
    defaultStmtLst1.push_back(&fNode);
    auto wNode = WhileNode(8, condPtr, defaultStmtLst1);
    defaultStmtLst.push_back(&wNode);
    defaultStmtLst.push_back(&eNode);

    ProcedureNode proc1 = ProcedureNode(&pNew, defaultStmtLst);
    procLst.push_back(&proc1);
    ProgramNode prog = ProgramNode(procLst);
    RelationshipExtractor::extractCFG(&prog);
    REQUIRE(PKB::getInstance()->relationship.next.isRelationship("1","8"));
    REQUIRE(PKB::getInstance()->relationship.next.isRelationship("8","2"));
    REQUIRE(PKB::getInstance()->relationship.next.isRelationship("2","4"));
    REQUIRE(PKB::getInstance()->relationship.next.isRelationship("4","3"));
    REQUIRE(PKB::getInstance()->relationship.next.isRelationship("4","5"));
    REQUIRE(PKB::getInstance()->relationship.next.isRelationship("3","7"));
    REQUIRE(PKB::getInstance()->relationship.next.isRelationship("5","7"));
    REQUIRE(PKB::getInstance()->relationship.next.isRelationship("7","8"));
    REQUIRE(PKB::getInstance()->relationship.next.isRelationship("8","6"));
}

TEST_CASE("test next - 2 procedures") {
    PKB::getInstance()->clearPKB();

    ProcedureList procLst;
    StatementList s1, s2;
    auto callNode = CallNode(3, &p1);
    s1.push_back(&aNode);
    s1.push_back(&dNode);
    s2.push_back(&bNode);
    s2.push_back(&callNode);
    ProcNameNode p1New = ProcNameNode("name11");
    ProcNameNode p2New = ProcNameNode("name21");

    ProcedureNode proc1 = ProcedureNode(&p1New, s1);
    ProcedureNode proc2 = ProcedureNode(&p2New, s2);
    procLst.push_back(&proc1);
    procLst.push_back(&proc2);
    ProgramNode prog = ProgramNode(procLst);

    RelationshipExtractor::extractCFG(&prog);
    REQUIRE(PKB::getInstance()->relationship.next.isRelationship("2","3"));
    REQUIRE(PKB::getInstance()->relationship.next.isRelationship("1","5"));
    REQUIRE(PKB::getInstance()->relationship.next.isRelationship("3","1")==false);
    REQUIRE(PKB::getInstance()->relationship.next.isRelationship("1","2")==false);
    REQUIRE(PKB::getInstance()->relationship.next.isRelationship("2","1")==false);
}

TEST_CASE("test calls - basic") {
    PKB::getInstance()->clearPKB();

    ProcedureList procLst;
    StatementList s1, s2;
    vector<ProcedureNode *> procList;
    auto callNode = CallNode(2, &p1);
    s1.push_back(&aNode);
    s2.push_back(&callNode);
    ProcedureNode proc1 = ProcedureNode(&p1, s1);
    ProcedureNode proc2 = ProcedureNode(&p2, s2);
    procLst.push_back(&proc1);
    procLst.push_back(&proc2);
    ProgramNode prog = ProgramNode(procLst);
    RelationshipExtractor::extractCalls(&prog,procList,nullptr);
    REQUIRE(PKB::getInstance()->relationship.calls.isRelationship("name2","name1"));
    REQUIRE(PKB::getInstance()->relationship.calls.isRelationship("name1","name2")==false);
}

TEST_CASE("test calls - multiple procedures one after another") {
    PKB::getInstance()->clearPKB();

    ProcedureList procLst;
    StatementList s1, s2, s3, s4;
    vector<ProcedureNode *> procList;

    auto callNode1 = CallNode(2, &p2);
    auto callNode2 = CallNode(3, &p3);
    auto callNode3 = CallNode(4, &p4);
    s4.push_back(&aNode);
    s1.push_back(&callNode1);
    s2.push_back(&callNode2);
    s3.push_back(&callNode3);
    ProcedureNode proc1 = ProcedureNode(&p1, s1);
    ProcedureNode proc2 = ProcedureNode(&p2, s2);
    ProcedureNode proc3 = ProcedureNode(&p3, s3);
    ProcedureNode proc4 = ProcedureNode(&p4, s4);
    procLst.push_back(&proc1);
    procLst.push_back(&proc2);
    procLst.push_back(&proc3);
    procLst.push_back(&proc4);
    ProgramNode prog = ProgramNode(procLst);
    RelationshipExtractor::extractCalls(&prog,procList,nullptr);
    REQUIRE(PKB::getInstance()->relationship.calls.isRelationship("name1","name2"));
    REQUIRE(PKB::getInstance()->relationship.calls.isRelationship("name1","name3")==false);
    REQUIRE(PKB::getInstance()->relationship.calls.isRelationship("name1","name4")==false);
    REQUIRE(PKB::getInstance()->relationship.callsT.isRelationship("name1","name2"));
    REQUIRE(PKB::getInstance()->relationship.callsT.isRelationship("name1","name3"));
    REQUIRE(PKB::getInstance()->relationship.callsT.isRelationship("name1","name4"));

    REQUIRE(PKB::getInstance()->relationship.calls.isRelationship("name2","name3"));
    REQUIRE(PKB::getInstance()->relationship.calls.isRelationship("name2","name1")==false);
    REQUIRE(PKB::getInstance()->relationship.calls.isRelationship("name2","name4")==false);
    REQUIRE(PKB::getInstance()->relationship.callsT.isRelationship("name2","name3"));
    REQUIRE(PKB::getInstance()->relationship.callsT.isRelationship("name2","name4"));
    REQUIRE(PKB::getInstance()->relationship.callsT.isRelationship("name2","name1")==false);

    REQUIRE(PKB::getInstance()->relationship.calls.isRelationship("name3","name4"));
    REQUIRE(PKB::getInstance()->relationship.calls.isRelationship("name3","name1")==false);
    REQUIRE(PKB::getInstance()->relationship.calls.isRelationship("name3","name2")==false);
    REQUIRE(PKB::getInstance()->relationship.callsT.isRelationship("name3","name4"));
    REQUIRE(PKB::getInstance()->relationship.callsT.isRelationship("name3","name1")==false);
    REQUIRE(PKB::getInstance()->relationship.callsT.isRelationship("name3","name2")==false);

    REQUIRE(PKB::getInstance()->relationship.calls.isRelationship("name4","name1")==false);
    REQUIRE(PKB::getInstance()->relationship.callsT.isRelationship("name4","name1")==false);

    REQUIRE(PKB::getInstance()->relationship.calls.isRelationship("name1","name1")==false);
    REQUIRE(PKB::getInstance()->relationship.calls.isRelationship("name2","name2")==false);
    REQUIRE(PKB::getInstance()->relationship.calls.isRelationship("name3","name3")==false);
    REQUIRE(PKB::getInstance()->relationship.calls.isRelationship("name4","name4")==false);

    REQUIRE(PKB::getInstance()->relationship.callsT.isRelationship("name1","name1")==false);
    REQUIRE(PKB::getInstance()->relationship.callsT.isRelationship("name2","name2")==false);
    REQUIRE(PKB::getInstance()->relationship.callsT.isRelationship("name3","name3")==false);
    REQUIRE(PKB::getInstance()->relationship.callsT.isRelationship("name4","name4")==false);

}
TEST_CASE("test calls - multiple calls in one procedure") {
    PKB::getInstance()->clearPKB();

    ProcedureList procLst;
    StatementList s1, s2, s3, s4;
    vector<ProcedureNode *> procList;

    auto callNode1 = CallNode(2, &p2);
    auto callNode2 = CallNode(3, &p3);
    auto callNode3 = CallNode(4, &p4);
    s4.push_back(&aNode);
    s1.push_back(&callNode1);
    s1.push_back(&callNode2);
    s2.push_back(&callNode3);
    s3.push_back(&dNode);

    ProcedureNode proc1 = ProcedureNode(&p1, s1);
    ProcedureNode proc2 = ProcedureNode(&p2, s2);
    ProcedureNode proc3 = ProcedureNode(&p3, s3);
    ProcedureNode proc4 = ProcedureNode(&p4, s4);
    procLst.push_back(&proc1);
    procLst.push_back(&proc2);
    procLst.push_back(&proc3);
    procLst.push_back(&proc4);
    ProgramNode prog = ProgramNode(procLst);
    RelationshipExtractor::extractCalls(&prog, procList, nullptr);

    REQUIRE(PKB::getInstance()->relationship.calls.isRelationship("name1","name2"));
    REQUIRE(PKB::getInstance()->relationship.calls.isRelationship("name1","name3"));
    REQUIRE(PKB::getInstance()->relationship.calls.isRelationship("name1","name4")==false);
    REQUIRE(PKB::getInstance()->relationship.callsT.isRelationship("name1","name2"));
    REQUIRE(PKB::getInstance()->relationship.callsT.isRelationship("name1","name3"));
    REQUIRE(PKB::getInstance()->relationship.callsT.isRelationship("name1","name4"));

    REQUIRE(PKB::getInstance()->relationship.calls.isRelationship("name2","name3")==false);
    REQUIRE(PKB::getInstance()->relationship.calls.isRelationship("name2","name1")==false);
    REQUIRE(PKB::getInstance()->relationship.calls.isRelationship("name2","name4"));
    REQUIRE(PKB::getInstance()->relationship.callsT.isRelationship("name2","name3")==false);
    REQUIRE(PKB::getInstance()->relationship.callsT.isRelationship("name2","name4"));
    REQUIRE(PKB::getInstance()->relationship.callsT.isRelationship("name2","name1")==false);

    REQUIRE(PKB::getInstance()->relationship.calls.isRelationship("name3","name4")==false);
    REQUIRE(PKB::getInstance()->relationship.calls.isRelationship("name3","name1")==false);
    REQUIRE(PKB::getInstance()->relationship.calls.isRelationship("name3","name2")==false);
    REQUIRE(PKB::getInstance()->relationship.callsT.isRelationship("name3","name4")==false);
    REQUIRE(PKB::getInstance()->relationship.callsT.isRelationship("name3","name1")==false);
    REQUIRE(PKB::getInstance()->relationship.callsT.isRelationship("name3","name2")==false);

    REQUIRE(PKB::getInstance()->relationship.calls.isRelationship("name4","name1")==false);
    REQUIRE(PKB::getInstance()->relationship.callsT.isRelationship("name4","name1")==false);

    REQUIRE(PKB::getInstance()->relationship.calls.isRelationship("name1","name1")==false);
    REQUIRE(PKB::getInstance()->relationship.calls.isRelationship("name2","name2")==false);
    REQUIRE(PKB::getInstance()->relationship.calls.isRelationship("name3","name3")==false);
    REQUIRE(PKB::getInstance()->relationship.calls.isRelationship("name4","name4")==false);

    REQUIRE(PKB::getInstance()->relationship.callsT.isRelationship("name1","name1")==false);
    REQUIRE(PKB::getInstance()->relationship.callsT.isRelationship("name2","name2")==false);
    REQUIRE(PKB::getInstance()->relationship.callsT.isRelationship("name3","name3")==false);
    REQUIRE(PKB::getInstance()->relationship.callsT.isRelationship("name4","name4")==false);
}

TEST_CASE("Entity Extractor - assign all stmt nodes to a procedure") {

    PKB::getInstance()->clearPKB();

    ProcedureList procLst;
    StatementList s1;
    s1.push_back(&aNode);
    s1.push_back(&bNode);

    ProcedureNode proc1 = ProcedureNode(&p1, s1);
    procLst.push_back(&proc1);
    ProgramNode prog = ProgramNode(procLst);
    EntityExtractor::assignProcedureToNodes(&prog,nullptr);
    REQUIRE(dynamic_cast<ProcedureNode*>(aNode.getProc())->getProcName() == "name1");
    REQUIRE(dynamic_cast<ProcedureNode*>(bNode.getProc())->getProcName() == "name1");

}

