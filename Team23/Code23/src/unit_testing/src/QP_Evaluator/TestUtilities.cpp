//
// Created by Tianyi Wang on 13/3/22.
//

#include "TestUtilities.h"

Query makeQuery(unordered_map<string, DesignEntity>& declarations, std::vector<Argument> synonyms) {
    Query query;
    query.setDeclarations(declarations);
    query.setSynonyms(std::move(synonyms));
    return query;
}

Query makeQuery(unordered_map<string, DesignEntity>& declarations, std::vector<Argument> synonyms, vector<SuchThatClause> suchThatClauses, vector<PatternClause> patternClauses) {
    Query query;
    query.setDeclarations(declarations);
    query.setSynonyms(std::move(synonyms));
    query.setSuchThatClauses(std::move(suchThatClauses));
    query.setPatternClauses(std::move(patternClauses));
    return query;
}

Query makeQuery(unordered_map<string, DesignEntity>& declarations, std::vector<Argument> synonyms, vector<SuchThatClause> suchThatClauses) {
    Query query;
    query.setDeclarations(declarations);
    query.setSynonyms(std::move(synonyms));
    query.setSuchThatClauses(std::move(suchThatClauses));
    return query;
}

Query makeQuery(unordered_map<string, DesignEntity>& declarations, std::vector<Argument> synonyms, vector<PatternClause> patternClauses) {
    Query query;
    query.setDeclarations(declarations);
    query.setSynonyms(std::move(synonyms));
    query.setPatternClauses(std::move(patternClauses));
    return query;
}

ResultSet generateResultSet (list<string> result) {
    return {std::begin(result), std::end(result)};
}

ResultSet evaluateAndCreateResultSet(QueryEvaluator qe, Query *query) {
    list<string> resultList = qe.evaluate(query);
    return ResultSet (std::begin(resultList), std::end(resultList));
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
    string s2 = "y = x + y + 3;";
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
    testPKB->addReadStatement(Parser::parseRead(s1));
    testPKB->addAssignStatement(Parser::parseAssign(s2));
    testPKB->addAssignStatement(Parser::parseAssign(s3));
    testPKB->addPrintStatement(Parser::parsePrint(s4));
    testPKB->addWhileStatement(Parser::parseWhile(s5));
    testPKB->addCallStatement(Parser::parseCall(s6));
    IfNode* ifNode = Parser::parseIf(s7);
    AssignNode* assignNode1 = dynamic_cast<AssignNode*>(((*ifNode).getThenStmtLst())[0]);
    AssignNode* assignNode2 = dynamic_cast<AssignNode*>(((*ifNode).getElseStmtLst())[0]);
    testPKB->addIfStatement(ifNode);
    testPKB->addAssignStatement(assignNode1);
    testPKB->addAssignStatement(assignNode2);
    testPKB->addAssignStatement(Parser::parseAssign(s10));
    testPKB->addPrintStatement(Parser::parsePrint(s11));

    Parser::resetStatementNumber();
    testPKB->addVariable("x");
    testPKB->addVariable("y");
    testPKB->addVariable("z");
    testPKB->addConstant("1");
    testPKB->addConstant("3");
    testPKB->addConstant("5");
    testPKB->addProcedure("prop");
    testPKB->addProcedure("pr");

    testPKB->setFollows(1, 2);
    testPKB->setFollows(2, 3);
    testPKB->setFollows(3, 4);
    testPKB->setFollows(4, 5);
    testPKB->setFollows(5, 11);
    testPKB->setFollows(6, 7);
    testPKB->setFollows(7, 10);

    testPKB->setFollowsT(1,2);
    testPKB->setFollowsT(1,3);
    testPKB->setFollowsT(1,4);
    testPKB->setFollowsT(1,5);
    testPKB->setFollowsT(1,11);
    testPKB->setFollowsT(2,3);
    testPKB->setFollowsT(2,4);
    testPKB->setFollowsT(2,5);
    testPKB->setFollowsT(2,11);
    testPKB->setFollowsT(3,4);
    testPKB->setFollowsT(3,5);
    testPKB->setFollowsT(3,11);
    testPKB->setFollowsT(4,5);
    testPKB->setFollowsT(4,11);
    testPKB->setFollowsT(5,11);
    testPKB->setFollowsT(6, 7);
    testPKB->setFollowsT(6, 10);
    testPKB->setFollowsT(7, 10);

    testPKB->setParent(5, 6);
    testPKB->setParent(5, 7);
    testPKB->setParent(5, 10);
    testPKB->setParent(7, 8);
    testPKB->setParent(7, 9);

    testPKB->setParentT(5,6);
    testPKB->setParentT(5,7);
    testPKB->setParentT(5,8);
    testPKB->setParentT(5,9);
    testPKB->setParentT(5,10);
    testPKB->setParentT(7, 8);
    testPKB->setParentT(7, 9);

    testPKB->setModifiesS(1, {"x"});
    testPKB->setModifiesS(2, {"y"});
    testPKB->setModifiesS(3, {"z"});
    testPKB->setModifiesS(5, {"x", "y", "z"});
    testPKB->setModifiesS(6, {"x"});
    testPKB->setModifiesS(8, {"y"});
    testPKB->setModifiesS(9, {"x"});
    testPKB->setModifiesS(10, {"z"});
    testPKB->setModifiesP("prop", {"x", "y", "z"});
    testPKB->setModifiesP("pr", {"x"});

    testPKB->setUsesS(2, {"x", "y"});
    testPKB->setUsesS(3, {"y"});
    testPKB->setUsesS(4, {"z"});
    testPKB->setUsesS(5, {"x", "y", "z"});
    testPKB->setUsesS(6, {"y"});
    testPKB->setUsesS(7, {"x", "y", "z"});
    testPKB->setUsesS(8, {"x", "z"});
    testPKB->setUsesS(9, {"y", "z"});
    testPKB->setUsesS(10, {"z"});
    testPKB->setUsesS(11, {"x"});
    testPKB->setUsesP("prop", {"x", "y", "z"});
    testPKB->setUsesP("pr", {"y"});

    return testPKB;
}

PKB* generateSamplePKBForPatternMatching() {
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
    testPKB->addAssignNode(Parser::parseAssign(a1));
    testPKB->addAssignNode(Parser::parseAssign(a2));
    testPKB->addAssignNode(Parser::parseAssign(a3));
    testPKB->addAssignNode(Parser::parseAssign(a4));
    testPKB->addAssignNode(Parser::parseAssign(a5));
    testPKB->addAssignNode(Parser::parseAssign(a6));
    testPKB->addAssignNode(Parser::parseAssign(a7));

    Parser::resetStatementNumber();
    testPKB->addVariable("x");
    testPKB->addVariable("y");
    testPKB->addVariable("z");

    testPKB->addAssignStatement(Parser::parseAssign(a1));
    testPKB->addAssignStatement(Parser::parseAssign(a2));
    testPKB->addAssignStatement(Parser::parseAssign(a3));
    testPKB->addAssignStatement(Parser::parseAssign(a4));
    testPKB->addAssignStatement(Parser::parseAssign(a5));
    testPKB->addAssignStatement(Parser::parseAssign(a6));
    testPKB->addAssignStatement(Parser::parseAssign(a7));


    testPKB->setFollows(1, 2);
    testPKB->setFollows(2, 3);
    testPKB->setFollows(3, 4);
    testPKB->setFollows(4, 5);
    testPKB->setFollows(5, 6);
    testPKB->setFollows(6, 7);

    testPKB->setUsesS(1, {"y"});
    testPKB->setUsesS(3, {"y"});
    testPKB->setUsesS(4, {"y", "x"});
    testPKB->setUsesS(5, {"y", "x", "z"});
    testPKB->setUsesS(6, {"y", "x", "z"});

    return testPKB;
}