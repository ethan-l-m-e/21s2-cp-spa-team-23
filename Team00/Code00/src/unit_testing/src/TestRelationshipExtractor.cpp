//
// Created by Tin Hong Wen on 5/2/22.
//

#include "RelationshipExtractor.h"
#include "TNode.h"
#include "catch.hpp"

using namespace std;

TEST_CASE("test follows") {
    TNode pNode("procedure");
    TNode aNode("assign", 2);
    TNode bNode("while", 3);
    TNode cNode("read:x", 6);
    TNode dNode("cond");
    TNode eNode("assign", 4);
    TNode fNode("print:x", 5);

    /*
    pNode.addNode(&aNode);
    pNode.addNode(&bNode);
    pNode.addNode(&cNode);

    bNode.addNode(&dNode);
    bNode.addNode(&eNode);
    bNode.addNode(&fNode);
    */

    RelationshipExtractor::extractFollows(&pNode);
}