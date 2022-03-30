//
// Created by Tianyi Wang on 13/3/22.
//

#include "TestUtilities.h"

Query makeQuery(unordered_map<string, DesignEntity>& declarations, std::vector<Argument> synonyms) {
    Query query;
    query.setDeclarations(declarations);
    ResultClause resultClause = ResultClause();
    resultClause.argList = synonyms;
    query.setResultClause(resultClause);
    return query;
}

Query makeQuery(unordered_map<string, DesignEntity>& declarations, std::vector<Argument> synonyms, vector<SuchThatClause> suchThatClauses, vector<PatternClause> patternClauses) {
    Query query;
    query.setDeclarations(declarations);
    ResultClause resultClause = ResultClause();
    resultClause.argList = synonyms;
    query.setResultClause(resultClause);
    query.setSuchThatClauses(std::move(suchThatClauses));
    query.setPatternClauses(std::move(patternClauses));
    return query;
}

Query makeQuery(unordered_map<string, DesignEntity>& declarations, std::vector<Argument> synonyms, vector<SuchThatClause> suchThatClauses) {
    Query query;
    query.setDeclarations(declarations);
    ResultClause resultClause = ResultClause();
    resultClause.argList = synonyms;
    query.setResultClause(resultClause);
    query.setSuchThatClauses(std::move(suchThatClauses));
    return query;
}

Query makeQuery(unordered_map<string, DesignEntity>& declarations, std::vector<Argument> synonyms, vector<PatternClause> patternClauses) {
    Query query;
    query.setDeclarations(declarations);
    ResultClause resultClause = ResultClause();
    resultClause.argList = synonyms;
    query.setResultClause(resultClause);
    query.setPatternClauses(std::move(patternClauses));
    return query;
}

ResultSet generateResultSet (list<string> result) {
    return {std::begin(result), std::end(result)};
}

ResultSet evaluateAndCreateResultSet(QueryEvaluator *qe, Query *query) {
    list<string> resultList = qe->evaluate(query);
    return {std::begin(resultList), std::end(resultList)};
}

PKB* generateSamplePKB() {
/**
 * Procedure prop {
 * 01 read x;
 * 02 y = x + y + 3;
 * 03 z = 3 * y;
 * 04 print z;
 * 05 while (z > 5) {
 * 06   call pr; // uses y and modifies x
 * 07   if (x < y) then {
 * 08     y = x + z;}
 *      else {
 * 09     x = y + z;}
 * 10   z = z - 1;}
 * 11 print x;
 * }
 * Procedure pr{...}
 */

    string s1 = "read x;";
    string s2 = "y = x + y + 3 + a + b;";
    string s3 = "z = 3 * y;";
    string s4 = "print z;";
    string s5 = "while (z > 5) {";
    string s6 = "call pr;";
    string s7 = "if(x < y)then{\ny = x + z;}\n else { \nx = y + z;} \n";
    string s8 = "y = x + z;}";
    string s9 = "x = y + z;}";
    string s10 = "z = z - 1;}";
    string s11 = "print x;";

    PKB *testPKB = PKB::getInstance();
    testPKB->clearPKB();
    Parser::resetStatementNumber();
    ReadNode* n1 = Parser::parseRead(s1);
    testPKB->statement.statements.addStatement(n1);
    testPKB->statement.readStatements.addStatement(n1);

    AssignNode* n2 = Parser::parseAssign(s2);
    testPKB->statement.statements.addStatement(n2);
    testPKB->statement.assignStatements.addStatement(n2);

    AssignNode* n3 = Parser::parseAssign(s3);
    testPKB->statement.statements.addStatement(n3);
    testPKB->statement.assignStatements.addStatement(n3);

    PrintNode* n4 = Parser::parsePrint(s4);
    testPKB->statement.statements.addStatement(n4);
    testPKB->statement.printStatements.addStatement(n4);

    WhileNode* n5 = Parser::parseWhile(s5);
    testPKB->statement.statements.addStatement(n5);
    testPKB->statement.whileStatements.addStatement(n5);

    CallNode* n6 = Parser::parseCall(s6);
    testPKB->statement.statements.addStatement(n6);
    testPKB->statement.callStatements.addStatement(n6);

    IfNode* n7 = Parser::parseIf(s7);
    testPKB->statement.statements.addStatement(n7);
    testPKB->statement.ifStatements.addStatement(n7);

    AssignNode* n8 = dynamic_cast<AssignNode*>(((*n7).getThenStmtLst())[0]);
    testPKB->statement.statements.addStatement(n8);
    testPKB->statement.assignStatements.addStatement(n8);

    AssignNode* n9 = dynamic_cast<AssignNode*>(((*n7).getElseStmtLst())[0]);
    testPKB->statement.statements.addStatement(n9);
    testPKB->statement.assignStatements.addStatement(n9);

    AssignNode* n10 = Parser::parseAssign(s10);
    testPKB->statement.statements.addStatement(n10);
    testPKB->statement.assignStatements.addStatement(n10);

    PrintNode* n11 = Parser::parsePrint(s11);
    testPKB->statement.statements.addStatement(n11);
    testPKB->statement.printStatements.addStatement(n11);

    Parser::resetStatementNumber();
    testPKB->entity.variables.add("x");
    testPKB->entity.variables.add("y");
    testPKB->entity.variables.add("z");
    testPKB->entity.variables.add("a");
    testPKB->entity.variables.add("b");
    testPKB->entity.constants.add("1");
    testPKB->entity.constants.add("3");
    testPKB->entity.constants.add("5");
    testPKB->entity.procedures.add("prop");
    testPKB->entity.procedures.add("pr");

    testPKB->relationship.follows.setRelationship("1", "2");
    testPKB->relationship.follows.setRelationship("2", "3");
    testPKB->relationship.follows.setRelationship("3", "4");
    testPKB->relationship.follows.setRelationship("4", "5");
    testPKB->relationship.follows.setRelationship("5", "11");
    testPKB->relationship.follows.setRelationship("6", "7");
    testPKB->relationship.follows.setRelationship("7", "10");

    testPKB->relationship.followsT.setRelationship("1","2");
    testPKB->relationship.followsT.setRelationship("1","3");
    testPKB->relationship.followsT.setRelationship("1","4");
    testPKB->relationship.followsT.setRelationship("1","5");
    testPKB->relationship.followsT.setRelationship("1","11");
    testPKB->relationship.followsT.setRelationship("2","3");
    testPKB->relationship.followsT.setRelationship("2","4");
    testPKB->relationship.followsT.setRelationship("2","5");
    testPKB->relationship.followsT.setRelationship("2","11");
    testPKB->relationship.followsT.setRelationship("3","4");
    testPKB->relationship.followsT.setRelationship("3","5");
    testPKB->relationship.followsT.setRelationship("3","11");
    testPKB->relationship.followsT.setRelationship("4","5");
    testPKB->relationship.followsT.setRelationship("4","11");
    testPKB->relationship.followsT.setRelationship("5","11");
    testPKB->relationship.followsT.setRelationship("6", "7");
    testPKB->relationship.followsT.setRelationship("6", "10");
    testPKB->relationship.followsT.setRelationship("7", "10");

    testPKB->relationship.parent.setRelationship("5", "6");
    testPKB->relationship.parent.setRelationship("5", "7");
    testPKB->relationship.parent.setRelationship("5", "10");
    testPKB->relationship.parent.setRelationship("7", "8");
    testPKB->relationship.parent.setRelationship("7", "9");

    testPKB->relationship.parentT.setRelationship("5","6");
    testPKB->relationship.parentT.setRelationship("5","7");
    testPKB->relationship.parentT.setRelationship("5","8");
    testPKB->relationship.parentT.setRelationship("5","9");
    testPKB->relationship.parentT.setRelationship("5","10");
    testPKB->relationship.parentT.setRelationship("7", "8");
    testPKB->relationship.parentT.setRelationship("7", "9");

    testPKB->relationship.modifiesS.setRelationship("1", unordered_set<string>{"x"});
    testPKB->relationship.modifiesS.setRelationship("2", unordered_set<string>{"y"});
    testPKB->relationship.modifiesS.setRelationship("3", unordered_set<string>{"z"});
    testPKB->relationship.modifiesS.setRelationship("5", unordered_set<string>{"x", "y", "z"});
    testPKB->relationship.modifiesS.setRelationship("6", unordered_set<string>{"x"});
    testPKB->relationship.modifiesS.setRelationship("8", unordered_set<string>{"y"});
    testPKB->relationship.modifiesS.setRelationship("9", unordered_set<string>{"x"});
    testPKB->relationship.modifiesS.setRelationship("10", unordered_set<string>{"z"});
    testPKB->relationship.modifiesP.setRelationship("prop", unordered_set<string>{"x", "y", "z"});
    testPKB->relationship.modifiesP.setRelationship("pr", unordered_set<string>{"x"});

    testPKB->relationship.usesS.setRelationship("2", unordered_set<string>{"x", "y", "a", "b"});
    testPKB->relationship.usesS.setRelationship("3", unordered_set<string>{"y"});
    testPKB->relationship.usesS.setRelationship("4", unordered_set<string>{"z"});
    testPKB->relationship.usesS.setRelationship("5", unordered_set<string>{"x", "y", "z"});
    testPKB->relationship.usesS.setRelationship("6", unordered_set<string>{"y"});
    testPKB->relationship.usesS.setRelationship("7", unordered_set<string>{"x", "y", "z"});
    testPKB->relationship.usesS.setRelationship("8", unordered_set<string>{"x", "z"});
    testPKB->relationship.usesS.setRelationship("9", unordered_set<string>{"y", "z"});
    testPKB->relationship.usesS.setRelationship("10", unordered_set<string>{"z"});
    testPKB->relationship.usesS.setRelationship("11", unordered_set<string>{"x"});
    testPKB->relationship.usesP.setRelationship("prop", unordered_set<string>{"x", "y", "z", "a", "b"});
    testPKB->relationship.usesP.setRelationship("pr", unordered_set<string>{"y"});

    testPKB->relationship.calls.setRelationship("prop", unordered_set<string>{"pr"});
    testPKB->relationship.callsT.setRelationship("prop", unordered_set<string>{"pr"});

    vector<unordered_map<int, NodeCFG*>> v = constructCFGForSamplePKB();
    unordered_map<int, NodeCFG *> allNodes = v[0];

    for (auto& iter : allNodes) {
        int statementNumber = iter.first;
        NodeCFG *node = iter.second;
        testPKB->relationship.next.addCFGNode(node);
    }

    return testPKB;
}

PKB* generateSamplePKBForPatternMatchingAssign() {
    /**
     * Original. DO NOT DELETE OR MODIFY UNLESS YOU KNOW WHAT YOU ARE DOING.
     *    x = y;        // test var
     *    x = 1;        //test const
     *    x = y + 1;    //test basic expression
     *    y = (y + x + 2) + 1;  //test 1-nested expression
     *    y = ((y + (3 - z)) * (x + 2)) + 1;    // test >2-nested expression
     *    y = y + x * 1 + z;        // test AST structure
     */
    string a1 = "x = y;";
    string a2 = "x = 1;";
    string a3 = "x = y + 1;";
    string a4 = "y = (y + x + 2) + 1;";
    string a5 = "y = ((y + (3 - z)) * (x + 2)) + 1;";
    string a6 = "y = y + x * 1 + z;";
    string a7 = "x = (y + (3 - z)) + 1;";

    PKB *testPKB = PKB::getInstance();
    testPKB->clearPKB();

    Parser::resetStatementNumber();
    testPKB->entity.variables.add("x");
    testPKB->entity.variables.add("y");
    testPKB->entity.variables.add("z");

    AssignNode* n1 = Parser::parseAssign(a1);
    testPKB->statement.statements.addStatement(n1);
    testPKB->statement.assignStatements.addStatement(n1);

    AssignNode* n2 = Parser::parseAssign(a2);
    testPKB->statement.statements.addStatement(n2);
    testPKB->statement.assignStatements.addStatement(n2);

    AssignNode* n3 = Parser::parseAssign(a3);
    testPKB->statement.statements.addStatement(n3);
    testPKB->statement.assignStatements.addStatement(n3);

    AssignNode* n4 = Parser::parseAssign(a4);
    testPKB->statement.statements.addStatement(n4);
    testPKB->statement.assignStatements.addStatement(n4);

    AssignNode* n5 = Parser::parseAssign(a5);
    testPKB->statement.statements.addStatement(n5);
    testPKB->statement.assignStatements.addStatement(n5);

    AssignNode* n6 = Parser::parseAssign(a6);
    testPKB->statement.statements.addStatement(n6);
    testPKB->statement.assignStatements.addStatement(n6);

    AssignNode* n7 = Parser::parseAssign(a7);
    testPKB->statement.statements.addStatement(n7);
    testPKB->statement.assignStatements.addStatement(n7);

    testPKB->relationship.follows.setRelationship("1", "2");
    testPKB->relationship.follows.setRelationship("2", "3");
    testPKB->relationship.follows.setRelationship("3", "4");
    testPKB->relationship.follows.setRelationship("4", "5");
    testPKB->relationship.follows.setRelationship("5", "6");
    testPKB->relationship.follows.setRelationship("6", "7");

    testPKB->relationship.usesS.setRelationship("1", unordered_set<string>{"y"});
    testPKB->relationship.usesS.setRelationship("3", unordered_set<string>{"y"});
    testPKB->relationship.usesS.setRelationship("4", unordered_set<string>{"y", "x"});
    testPKB->relationship.usesS.setRelationship("5", unordered_set<string>{"y", "x", "z"});
    testPKB->relationship.usesS.setRelationship("6", unordered_set<string>{"y", "x", "z"});

    return testPKB;
}

PKB* generateSamplePKBForPatternMatchingCondition() {
    PKB *testPKB = PKB::getInstance();
    testPKB->clearPKB();
    Parser::resetStatementNumber();
    string wh1le = "while";
    string filler = "{print x;}";
    string If = "if";
    string th3n = "then";
    string els3 = "else";

    string if_filler = th3n + filler + els3 + filler;

    string w1 = wh1le + "(x < y)" + filler;
    string w2 = wh1le + "(1 == 2)" + filler;
    string w3 = wh1le + "(!((x + 3) < (y + 2)))" + filler;
    string a4 = "z = (y + (3 - z)) + 1;";
    string i5 = If + "(x < y)" + if_filler;

    WhileNode* n1 = Parser::parseWhile(w1);
    WhileNode* n2 = Parser::parseWhile(w2);
    WhileNode* n3 = Parser::parseWhile(w3);

    testPKB->statement.statements.addStatement(n1);
    testPKB->statement.statements.addStatement(n2);
    testPKB->statement.statements.addStatement(n3);

    testPKB->statement.whileStatements.addStatement(n1);
    testPKB->statement.whileStatements.addStatement(n2);
    testPKB->statement.whileStatements.addStatement(n3);

    AssignNode* n4 = Parser::parseAssign(a4);
    testPKB->statement.statements.addStatement(n4);
    testPKB->statement.assignStatements.addStatement(n4);

    IfNode* n5 = Parser::parseIf(i5);
    testPKB->statement.statements.addStatement(n5);
    testPKB->statement.ifStatements.addStatement(n5);
    return testPKB;
}




PKB* generateAttrRefPKB() {
    string s1 = "a = b + c + d + h + i;";
    string s2 = "while(G > H) {";
    string s3 = "print C;}";
    string s4 = "while(G > 0) {";
    string s5 = "read a;}";


    PKB *testPKB = PKB::getInstance();
    testPKB->clearPKB();
    Parser::resetStatementNumber();

    AssignNode* n1 = Parser::parseAssign(s1);
    testPKB->statement.statements.addStatement(n1);
    testPKB->statement.assignStatements.addStatement(n1);

    WhileNode* n2 = Parser::parseWhile(s2);
    testPKB->statement.statements.addStatement(n2);
    testPKB->statement.whileStatements.addStatement(n2);

    PrintNode* n3 = Parser::parsePrint(s3);
    testPKB->statement.statements.addStatement(n3);
    testPKB->statement.printStatements.addStatement(n3);

    WhileNode* n4 = Parser::parseWhile(s4);
    testPKB->statement.statements.addStatement(n4);
    testPKB->statement.whileStatements.addStatement(n4);

    ReadNode* n5 = Parser::parseRead(s5);
    testPKB->statement.statements.addStatement(n5);
    testPKB->statement.readStatements.addStatement(n5);

    Parser::resetStatementNumber();
    testPKB->entity.variables.add("a");
    testPKB->entity.variables.add("b");
    testPKB->entity.variables.add("c");
    testPKB->entity.variables.add("d");
    testPKB->entity.variables.add("h");
    testPKB->entity.variables.add("i");
    testPKB->entity.variables.add("G");
    testPKB->entity.variables.add("H");
    testPKB->entity.variables.add("C");
    testPKB->entity.constants.add("0");

    testPKB->relationship.parent.setRelationship("2", "3");
    testPKB->relationship.parent.setRelationship("4", "5");

    testPKB->relationship.usesS.setRelationship("1", unordered_set<string>{"b", "c", "d", "h","i"});
    testPKB->relationship.usesS.setRelationship("2", unordered_set<string>{"G", "H", "C"});
    testPKB->relationship.usesS.setRelationship("3", unordered_set<string>{"C"});
    testPKB->relationship.usesS.setRelationship("4", unordered_set<string>{"G"});

    return testPKB;
}

vector<unordered_map<int, NodeCFG*>> constructCFGForTesting() {
    /*
     * branch1 -> 2, 6
     * node2, 3, 4, 5
     * loop6( loop7 (8))
     *
     * node9
     *
     * loop10 (11, branch12 -> 13, 14)
     */
    BranchCFG* branch1 = new BranchCFG(1);
    NodeCFG* node2 = new NodeCFG(2);
    NodeCFG* node3 = new NodeCFG(3);
    NodeCFG* node4 = new NodeCFG(4);
    NodeCFG* node5 = new NodeCFG(5);
    LoopCFG* loop6 = new LoopCFG(6);
    LoopCFG* loop7 = new LoopCFG(7);
    NodeCFG* node8 = new NodeCFG(8);
    NodeCFG* node9 = new NodeCFG(9);
    LoopCFG* loop10 = new LoopCFG(10);
    NodeCFG* node11 = new NodeCFG(11);
    BranchCFG* branch12 = new BranchCFG(12);
    NodeCFG* node13 = new NodeCFG(13);
    NodeCFG* node14 = new NodeCFG(14);

    branch1->setLeftNode(node2);
    node2->setNextNode(node3);
    node3->setNextNode(node4);
    node4->setNextNode(node5);

    branch1->setRightNode(loop6);
    loop6->setNodeInLoop(loop7);
    loop7->setNodeInLoop(node8);
    node8->setNextNode(loop7);
    loop7->setNextNode(loop6);

    node5->setNextNode(node9);
    loop6->setNextNode(node9);
    node9->setNextNode(loop10);
    loop10->setNodeInLoop(node11);
    node11->setNextNode(branch12);
    branch12->setLeftNode(node13);
    branch12->setRightNode(node14);
    node13->setNextNode(loop10);
    node14->setNextNode(loop10);

    NodeCFG* node15 = new NodeCFG(15);
    NodeCFG* node16 = new NodeCFG(16);
    NodeCFG* node17 = new NodeCFG(17);

    node15->setNextNode(node16);
    node16->setNextNode(node17);

    unordered_map<int, NodeCFG*> allNodes;
    allNodes[1] = branch1;
    allNodes[2] = node2;
    allNodes[3] = node3;
    allNodes[4] = node4;
    allNodes[5] = node5;
    allNodes[6] = loop6;
    allNodes[7] = loop7;
    allNodes[8] = node8;
    allNodes[9] = node9;
    allNodes[10] = loop10;
    allNodes[11] = node11;
    allNodes[12] = branch12;
    allNodes[13] = node13;
    allNodes[14] = node14;
    allNodes[15] = node15;
    allNodes[16] = node16;
    allNodes[17] = node17;
    unordered_map<int, NodeCFG*> rootNodes;
    return vector<unordered_map<int, NodeCFG*>>{allNodes, rootNodes};
}


vector<unordered_map<int, NodeCFG*>> constructCFGForSamplePKB() {
    NodeCFG* node1 = new NodeCFG(1);
    NodeCFG* node2 = new NodeCFG(2);
    NodeCFG* node3 = new NodeCFG(3);
    NodeCFG* node4 = new NodeCFG(4);
    LoopCFG* loop5 = new LoopCFG(5);
    NodeCFG* node6 = new NodeCFG(6);
    BranchCFG* branch7 = new BranchCFG(7);
    NodeCFG* node8 = new NodeCFG(8);
    NodeCFG* node9 = new NodeCFG(9);
    NodeCFG* node10 = new NodeCFG(10);
    NodeCFG* node11 = new NodeCFG(11);

    node1->setNextNode(node2);
    node2->setNextNode(node3);
    node3->setNextNode(node4);
    node4->setNextNode(loop5);
    loop5->setNodeInLoop(node6);
    node6->setNextNode(branch7);
    branch7->setLeftNode(node8);
    branch7->setRightNode(node9);
    node9->setNextNode(node10);
    node8->setNextNode(node10);
    node10->setNextNode(loop5);
    loop5->setNextNode(node11);

    unordered_map<int, NodeCFG*> allNodes;
    allNodes[1] = node1;
    allNodes[2] = node2;
    allNodes[3] = node3;
    allNodes[4] = node4;
    allNodes[5] = loop5;
    allNodes[6] = node6;
    allNodes[7] = branch7;
    allNodes[8] = node8;
    allNodes[9] = node9;
    allNodes[10] = node10;
    allNodes[11] = node11;
    unordered_map<int, NodeCFG*> rootNodes;
    return vector<unordered_map<int, NodeCFG*>>{allNodes, rootNodes};
}

PKB* constructPKBWithParser(string sourceCode) {
    PKB *testPKB = PKB::getInstance();
    testPKB->clearPKB();
    Parser::resetStatementNumber();
    DesignExtractor::Extract(Parser::Parse(sourceCode));
    return testPKB;
}