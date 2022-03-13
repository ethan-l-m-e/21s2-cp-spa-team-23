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
 * 02 y = yeast + zealous + x;
 * 03 zealous = 3;
 * 04 print xylophone;
 * 05 while (z > 1) {
 * 06    x = 5 + x;
 * 07   if (z == 2) {
 * 08    print z;
 *     } else {
 * 09   call prop1;}};
 * }
 */

    string s1 = "read x;";
    string s2 = "y = yeast + zealous + x;";
    string s3 = "zealous = 3;";
    string s4 = "print xylophone;";
    string s5 = "while (z == 1) {";
    string s6 = "x = 5 + x;";
    string s7 = "print z;}";

    PKB *testPKB = PKB::getInstance();
    testPKB->clearPKB();
    testPKB->addReadStatement(Parser::parseRead(s1));
    testPKB->addAssignNode(Parser::parseAssign(s2));
    testPKB->addAssignNode(Parser::parseAssign(s3));
    testPKB->addPrintStatement(Parser::parsePrint(s4));
    testPKB->addWhileStatement(Parser::parseWhile(s5));
    testPKB->addAssignNode(Parser::parseAssign(s6));
    testPKB->addPrintStatement(Parser::parsePrint(s7));

    testPKB->addAssignStatement(Parser::parseAssign(s2));
    testPKB->addAssignStatement(Parser::parseAssign(s3));
    testPKB->addAssignStatement(Parser::parseAssign(s6));

    Parser::resetStatementNumber();
    testPKB->addVariable("x");
    testPKB->addVariable("y");
    testPKB->addVariable("z");
    testPKB->addVariable("xylophone");
    testPKB->addVariable("yeast");
    testPKB->addVariable("zealous");
    testPKB->addConstant("1");
    testPKB->addConstant("3");
    testPKB->addConstant("5");
    testPKB->addProcedure("p");

    testPKB->setFollows(1, 2);
    testPKB->setFollows(2, 3);
    testPKB->setFollows(3, 4);
    testPKB->setFollows(4, 5);
    testPKB->setFollowsT(1,2);
    testPKB->setFollowsT(1,3);
    testPKB->setFollowsT(1,4);
    testPKB->setFollowsT(1,5);
    testPKB->setFollowsT(2,3);
    testPKB->setFollowsT(2,4);
    testPKB->setFollowsT(2,5);
    testPKB->setFollowsT(3,4);
    testPKB->setFollowsT(3,5);
    testPKB->setFollowsT(4,5);

    testPKB->setParent(5, 6);
    testPKB->setParent(5, 7);
    testPKB->setParentT(5,6);
    testPKB->setParentT(5,7);

    testPKB->setModifiesS(1, {"x"});
    testPKB->setModifiesS(2, {"y"});
    testPKB->setModifiesS(3, {"zealous"});
    testPKB->setModifiesS(5, {"x"});
    testPKB->setModifiesS(6, {"x"});

    testPKB->setUsesS(2, {"yeast", "zealous", "x"});
    testPKB->setUsesS(4, {"xylophone"});
    testPKB->setUsesS(5, {"z", "x"});
    testPKB->setUsesS(6, {"x"});
    testPKB->setUsesS(7, {"z"});

    testPKB->setModifiesP("p", {"x"});
    testPKB->setModifiesP("p", {"y"});
    testPKB->setModifiesP("p", {"zealous"});
    testPKB->setModifiesP("p", {"x"});
    testPKB->setModifiesP("p", {"x"});
    testPKB->setUsesP("p", {"yeast", "zealous", "x"});
    testPKB->setUsesP("p", {"xylophone"});
    testPKB->setUsesP("p", {"z", "x"});
    testPKB->setUsesP("p", {"x"});
    testPKB->setUsesP("p", {"z"});

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