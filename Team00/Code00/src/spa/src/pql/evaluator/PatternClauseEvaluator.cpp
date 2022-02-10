//
// Created by Tin Hong Wen on 10/2/22.
//
#include "PKB.h"
#include "PatternClauseEvaluator.h"
#include "TNode.h"

Result PatternClauseEvaluator::evaluateClause() {
    Argument argLeft = argList[0];
    Argument argRight = argList[1];
    ResultType resultType;
    ResultHeader resultHeader;
    vector<ResultItem> resultItem;

    vector<AssignNode*> listOfAssignNodes;
    //PKB::getInstance() -> getAllAssignPointers();
    resultType = ResultType::LIST;



    // pattern case scenarios
    // 1) Only need to handle constant and variable matching
    // 2)Only need to handle partial matching and wildcard, no exacts
    for (int i = 0; i < listOfAssignNodes.size(); i++) {
        // get statement number


        //LHS can be synonym, _ or "concreteValue"
        //RHS can be _, _const or variable_

        // return type
        //  LHS /   RHS         _const | var_                   _
        //  synonym             filtered LHS var & stmtNo       all LHS variable & stmtNo
        //  "concrete value"    filtered stmtNo                 filtered stmtNo
        //      _               filtered stmtNo                 all stmtNo

        if(leftIsSynonym()) {
            //result Type set to var

            //if right is expressionSpec,
        } else if (false) {     //if _, _
            // return stmtNo
        } else {

        }

        // return list of statement numbers that match the pattern clause
    }
}



bool checkRightHandSide() {
    return true;
}