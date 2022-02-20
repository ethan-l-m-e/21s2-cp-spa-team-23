//
// Created by Tin Hong Wen on 4/2/22.
//
#include <iostream>

#include "RelationshipExtractor.h"
#include "PKB.h"
#include "TNode.h"
#include "Constants/Constants.h"
#include <unordered_set>

using std::begin, std::end;

//extracts all follows relationship starting from given node
void RelationshipExtractor::extractFollows(Node * node) {
    if(auto value = dynamic_cast<ProgramNode*>(node)) {
        vector<ProcedureNode *> v = value->getProcLst();
        for (ProcedureNode *p: v)
            extractFollows(p);
    }else if(auto value = dynamic_cast<IfNode*>(node)) {
        int numOfChildNodes1 = value->getThenStmtLst().size();
        if (numOfChildNodes1 > 1) {
            for (int i = 0; i < (numOfChildNodes1 - 1); i++) {
                Node *child = value->getThenStmtLst().at(i);
                for(int j = i; j<numOfChildNodes1-1;j++){
                    Node *nextChild = value->getThenStmtLst().at(j + 1);
                    if(j==i) {
                        PKB::getInstance()->setFollows(child->getStmtNumber(), nextChild->getStmtNumber());
                    }
                    PKB::getInstance()->setFollowsT(child->getStmtNumber(), nextChild->getStmtNumber());

                }
            }
        }
        for (int i = 0; i < (numOfChildNodes1); i++) {
            extractFollows(node->getStmtLst().at(i));
        }
        int numOfChildNodes2 = value->getElseStmtLst().size();
        if (numOfChildNodes2 > 1) {
            for (int i = 0; i < (numOfChildNodes2 - 1); i++) {
                Node *child = value->getElseStmtLst().at(i);
                for(int j = i; j<numOfChildNodes2-1;j++){
                    Node *nextChild = value->getElseStmtLst().at(j + 1);
                    if(j==i) {
                        cout<<child->getStmtNumber();
                        cout<<nextChild->getStmtNumber();
                        PKB::getInstance()->setFollows(child->getStmtNumber(), nextChild->getStmtNumber());
                    }
                    PKB::getInstance()->setFollowsT(child->getStmtNumber(), nextChild->getStmtNumber());

                }
            }
        }
        for (int i = 0; i < (numOfChildNodes2); i++) {
            extractFollows(node->getStmtLst().at(i));
        }

    }else if(node->hasStmtLst()) {
         int numOfChildNodes = node->getStmtLst().size();
         if (numOfChildNodes > 1) {
             for (int i = 0; i < (numOfChildNodes - 1); i++) {
                 Node *child = node->getStmtLst().at(i);
                 for(int j = i; j<numOfChildNodes-1;j++){
                     Node *nextChild = node->getStmtLst().at(j + 1);
                    if(j==i) {
                        PKB::getInstance()->setFollows(child->getStmtNumber(), nextChild->getStmtNumber());
                    }
                     PKB::getInstance()->setFollowsT(child->getStmtNumber(), nextChild->getStmtNumber());

                 }
             }
         }
         for (int i = 0; i < (numOfChildNodes); i++) {
             extractFollows(node->getStmtLst().at(i));
         }
     }
}
//extracts all parents relationship starting from given node
void RelationshipExtractor::extractParent(Node * node, vector<StmtLstNode*> parentList) {
    if(auto value = dynamic_cast<ProgramNode*>(node)) {
        vector<ProcedureNode *> v = value->getProcLst();
        for (ProcedureNode *p: v)
            extractParent(p,parentList);

    }else if(node->hasStmtLst()) {
        int numOfChildNodes = node->getStmtLst().size();
        if(node->getStmtNumber()!=-1) {
            parentList.push_back((StmtLstNode *) node);
            Node *parent = node;
            for (int i = 0; i < (numOfChildNodes); i++) {
                Node *child = node->getStmtLst().at(i);
                PKB::getInstance()->setParent(parent->getStmtNumber(), child->getStmtNumber());
                for (int j = 0; j < parentList.size(); j++) {
                    Node *parentT = parentList.at(j);
                    PKB::getInstance()->setParentT(parentT->getStmtNumber(), child->getStmtNumber());
                }
            }
        }
        for (int i = 0; i < (numOfChildNodes); i++) {
            extractParent(node->getStmtLst().at(i), parentList);
        }
    }
}

//set all variables used by the node in the pkb
vector<string>  RelationshipExtractor::extractUses (Node * node) {
    /*
    vector<string> varList = node->getListOfVarUsed();
    if (!varList.empty()) {

        std::unordered_set<string> set;
        for (string &i: varList) {
            set.insert(i);
        }

        PKB::getInstance()->setUses(node->getStmtNumber(),set);
    }

    if(node->hasStmtLst()) {
        for (int i = 0; i < (node->getStmtLst().size()); i++) {
            extractUses(node->getStmtLst().at(i));
        }
    }
     */
    if(auto value = dynamic_cast<ProgramNode*>(node)) {
        vector<ProcedureNode*> v = value -> getProcLst();
        for(ProcedureNode* p: v)
            extractUses(p);

        return {};
    } else if(auto value = dynamic_cast<ProcedureNode*>(node)) {
        vector<Node*> stmtLst = value->getStmtLst();
        for(Node* s: stmtLst) {
            extractUses(s);
        }
        //TODO: for future iterations
        return {};
    } else if(auto value = dynamic_cast<WhileNode*>(node)) {
        //gather variables from cond_expr and stmtLst
        vector<VarName> condVariables = value->getCondExpr()->getListOfVarUsed();
        vector<Node*> stmtLst = value->getStmtLst();
        vector<VarName> allUsedVariables;
        allUsedVariables.insert(allUsedVariables.end(), condVariables.begin(), condVariables.end());
        for(Node* stmt: stmtLst) {
            vector<VarName> usedVariables = extractUses(stmt);
            allUsedVariables.insert(allUsedVariables.end(), usedVariables.begin(), usedVariables.end());
        }
        cout << "sending " << value-> getStmtNumber() << " whileVar: ";
        for(VarName v: allUsedVariables)
            cout << v << ", ";
        cout << "\n";
        PKB::getInstance()->setUses(value->getStmtNumber(), unordered_set<VarName>{allUsedVariables.begin(), allUsedVariables.end()});
        return allUsedVariables;
    } else if(auto value = dynamic_cast<IfNode*>(node)) {
        vector<VarName> condVariables = value->getCondExpr()->getAllVariables();
        vector<Node*> elseVector = value->getElseStmtLst();
        vector<Node*> thenVector = value->getThenStmtLst();
        vector<VarName> allUsedVariables;
        allUsedVariables.insert(allUsedVariables.end(), condVariables.begin(), condVariables.end());
        for(Node* stmt: elseVector) {
            vector<VarName> usedVariables = extractUses(stmt);
            allUsedVariables.insert(allUsedVariables.end(), usedVariables.begin(), usedVariables.end());
        }
        for(Node* stmt: thenVector) {
            vector<VarName> usedVariables = extractUses(stmt);
            allUsedVariables.insert(allUsedVariables.end(), usedVariables.begin(), usedVariables.end());
        }
        cout << "sending " << value-> getStmtNumber() << " ifVar: ";
        for(VarName v: allUsedVariables)
            cout << v << ", ";
        cout << "\n";
        PKB::getInstance()->setUses(value->getStmtNumber(), unordered_set<VarName>{allUsedVariables.begin(), allUsedVariables.end()});
        return allUsedVariables;
    } else if(auto value = dynamic_cast<AssignNode*>(node)) {
        vector<VarName> variables = value->getListOfVarUsed();
        cout << "sending " << value-> getStmtNumber() << " size: " << variables.size() << "\n";
        PKB::getInstance()->setUses(value->getStmtNumber(), unordered_set<VarName>{variables.begin(), variables.end()});
        return variables;
    } else if(auto value = dynamic_cast<PrintNode*>(node)) {
        vector<VarName> variables = value->getListOfVarUsed();
        cout << "sending " << value-> getStmtNumber() << " size: " << variables.size() << "\n";
        PKB::getInstance()->setUses(value->getStmtNumber(), unordered_set<VarName>{variables.begin(), variables.end()});
        return variables;
    } else {
        return {};
    }


}







//set all variables modified by the node in the pkb
vector<string> RelationshipExtractor::extractModifies (Node * node) {
    /*
    vector<string> varList = node->getListOfVarModified();
    if (!varList.empty()) {
        std::unordered_set<string> set;
        for (string &i: varList) {
            set.insert(i);
        }
        PKB::getInstance()->setModifies(node->getStmtNumber(),set);
    }
    if(node->hasStmtLst()) {
        for (int i = 0; i < (node->getStmtLst().size()); i++) {
            extractModifies(node->getStmtLst().at(i));
        }
    }*/
    if(auto value = dynamic_cast<ProgramNode*>(node)) {
        vector<ProcedureNode*> v = value -> getProcLst();
        for(ProcedureNode* p: v)
            extractModifies(p);

        return {};
    } else if(auto value = dynamic_cast<ProcedureNode*>(node)) {
        vector<Node*> stmtLst = value->getStmtLst();
        for(Node* s: stmtLst) {
            extractModifies(s);
        }
        //TODO: for future iterations
        return {};
    } else if(auto value = dynamic_cast<WhileNode*>(node)) {
        vector<Node*> stmtLst = value->getStmtLst();
        vector<VarName> allModifiedVariables;
        for(Node* stmt: stmtLst) {
            vector<VarName> modifiedVariables = extractModifies(stmt);
            allModifiedVariables.insert(allModifiedVariables.end(), modifiedVariables.begin(), modifiedVariables.end());
        }
        PKB::getInstance()->setModifies(value->getStmtNumber(), unordered_set<VarName>{allModifiedVariables.begin(), allModifiedVariables.end()});
        return allModifiedVariables;
    } else if(auto value = dynamic_cast<IfNode*>(node)) {
        vector<Node*> elseVector = value->getElseStmtLst();
        vector<Node*> thenVector = value->getThenStmtLst();
        vector<VarName> allModifiedVariables;
        for(Node* stmt: elseVector) {
            vector<VarName> modifiedVariables = extractModifies(stmt);
            allModifiedVariables.insert(allModifiedVariables.end(), modifiedVariables.begin(), modifiedVariables.end());
        }
        for(Node* stmt: thenVector) {
            vector<VarName> modifiedVariables = extractModifies(stmt);
            allModifiedVariables.insert(allModifiedVariables.end(), modifiedVariables.begin(), modifiedVariables.end());
        }
        PKB::getInstance()->setModifies(value->getStmtNumber(), unordered_set<VarName>{allModifiedVariables.begin(), allModifiedVariables.end()});
        return allModifiedVariables;
    } else if(auto value = dynamic_cast<AssignNode*>(node)) {
        vector<VarName> variables = value->getListOfVarModified();
        cout << "sending " << value-> getStmtNumber() << " size: " << variables.size() << "\n";
        PKB::getInstance()->setModifies(value->getStmtNumber(), unordered_set<VarName>{variables.begin(), variables.end()});
        return variables;
    } else if(auto value = dynamic_cast<ReadNode*>(node)) {
        vector<VarName> variables = value->getListOfVarModified();
        PKB::getInstance()->setModifies(value->getStmtNumber(), unordered_set<VarName>{variables.begin(), variables.end()});
        return variables;
    } else {
        return {};
    }
}


void extractAllEntities(Node *node) {
    if(auto value = dynamic_cast<ProgramNode*>(node)) {
        vector<ProcedureNode*> v = value -> getProcLst();
        for(ProcedureNode* p: v)
            extractAllEntities(p);

    } else if(auto value = dynamic_cast<ProcedureNode*>(node)) {
        vector<Node*> v = value->getStmtLst();
        for(Node* s: v) {
            extractAllEntities(s);
        }
        PKB::getInstance()->addProcedure(value->getProcName());

    } else if(auto value = dynamic_cast<WhileNode*>(node)) {
        Node* condExprNode = value->getCondExpr();
        vector<VarName> variables = condExprNode->getAllVariables();
        vector<Constant> constants = condExprNode->getAllConstants();
        vector<Node*> stmtLst = value->getStmtLst();
        for(VarName v: variables)
            PKB::getInstance()->addVariable(v);
        for(Constant c: constants)
            PKB::getInstance()->addConstant(c);
        for(Node* s: stmtLst)
            extractAllEntities(s);
        PKB::getInstance()->addWhileStatement(value->getStmtNumber());

    } else if(auto value = dynamic_cast<IfNode*>(node)) {
        Node* condExprNode = value->getCondExpr();
        vector<VarName> variables = condExprNode->getAllVariables();
        vector<Constant> constants = condExprNode->getAllConstants();
        vector<Node*> elseVector = value->getElseStmtLst();
        vector<Node*> thenVector = value->getThenStmtLst();
        for(VarName v: variables)
            PKB::getInstance()->addVariable(v);
        for(Constant c: constants)
            PKB::getInstance()->addConstant(c);
        for(Node* s: elseVector)
            extractAllEntities(s);
        for(Node* s: thenVector)
            extractAllEntities(s);
        PKB::getInstance()->addIfStatement(value->getStmtNumber());
    } else if(auto value = dynamic_cast<AssignNode*>(node)) {
        vector<VarName> variables = value->getAllVariables();
        vector<Constant> constants = value->getAllConstants();
        for(VarName variable: variables ) {
            PKB::getInstance() ->addVariable(variable);
        }
        for(Constant constant: constants) {
            PKB::getInstance() ->addConstant(constant);
        }
        PKB::getInstance()->addAssignNode(value);
        PKB::getInstance()->addAssignStatement(value->getStmtNumber());
    } else if(auto value = dynamic_cast<CondExprNode*>(node)) {
        vector<VarName> variables = value->getAllVariables();
        vector<Constant> constants = value->getAllConstants();
        for(VarName variable: variables ) {
            PKB::getInstance() ->addVariable(variable);
        }
        for(Constant constant: constants) {
            PKB::getInstance() ->addConstant(constant);
        }
    } else if(auto value = dynamic_cast<ReadNode*>(node)) {
        PKB::getInstance()->addReadStatement(value->getStmtNumber());
        PKB::getInstance()->addVariable(value->getVarName());
    } else if(auto value = dynamic_cast<PrintNode*>(node)) {
        PKB::getInstance()->addPrintStatement(value->getStmtNumber());
        PKB::getInstance()->addVariable(value->getVarName());
    }
}

void RelationshipExtractor::extractRelationships(Node * node){
    //extract relationship
    vector<StmtLstNode*> v;
    extractFollows(node);
    extractParent(node,v);
    extractUses(node);
    extractModifies(node);

    extractAllEntities(node);
    //extract entities
}

