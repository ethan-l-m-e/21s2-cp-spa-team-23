//
// Created by Tin Hong Wen on 4/2/22.
//
#include "RelationshipExtractor.h"
#include "PKB.h"
#include "TNode/Node.h"
#include "TNode/ProgramNode.h"
#include "TNode/AssignNode.h"
#include "TNode/WhileNode.h"
#include "TNode/IfNode.h"
#include "TNode/ReadNode.h"
#include "TNode/PrintNode.h"
#include "TNode/CallNode.h"
#include <unordered_set>

using std::begin, std::end;

class GraphNode {
    string name;
    vector<ProcName> toOtherNodes;
public:
    GraphNode(string name, vector<ProcName> toOtherNodes) {
        this-> name = name;
        this->toOtherNodes = toOtherNodes;
    }
    vector<ProcName> getDirectedNodes() {
        return this->toOtherNodes;
    }
    string getName() {
        return this->name;
    }
    void changeName(string name) {
        this->name = name;
    }
};

void extractFollowsFromStatementList(StatementList statementList) {
    int numOfChildNodes = statementList.size();
    if (numOfChildNodes > 1) {
        for (int i = 0; i < (numOfChildNodes - 1); i++) {
            Node *child = statementList.at(i);
            for (int j = i; j < numOfChildNodes - 1; j++) {
                Node *nextChild = statementList.at(j + 1);
                if (j == i) {
                    PKB::getInstance()->setFollows(child->getStmtNumber(), nextChild->getStmtNumber());
                }
                PKB::getInstance()->setFollowsT(child->getStmtNumber(), nextChild->getStmtNumber());
            }
        }
    }
}

void RelationshipExtractor::extractFollows(Node * node) {
    if(auto value = dynamic_cast<ProgramNode*>(node)) {
        vector<ProcedureNode *> v = value->getProcLst();
        for (ProcedureNode *p: v)
            extractFollows(p);
    } else if (auto value = dynamic_cast<ProcedureNode*>(node)) {
        StatementList statementList = value->getStmtLst();
        extractFollowsFromStatementList(statementList);
        for(Node* node: statementList)
            extractFollows(node);
    } else if (auto value = dynamic_cast<WhileNode*>(node)) {
        StatementList statementList = value->getStmtLst();
        extractFollowsFromStatementList(statementList);
        for(Node* node: statementList)
            extractFollows(node);
    } else if (auto value = dynamic_cast<IfNode*>(node)) {
        StatementList elseStatementList = value->getElseStmtLst();
        extractFollowsFromStatementList(elseStatementList);
        StatementList thenStatementList = value->getThenStmtLst();
        extractFollowsFromStatementList(thenStatementList);
        for(Node* node: elseStatementList)
            extractFollows(node);
        for(Node* node: thenStatementList)
            extractFollows(node);
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
    if(auto value = dynamic_cast<ProgramNode*>(node)) {
        vector<ProcedureNode*> v = value -> getProcLst();
        for(ProcedureNode* p: v)
            extractUses(p);

        return {};
    } else if(auto value = dynamic_cast<ProcedureNode*>(node)) {
        vector<Node*> stmtLst = value->getStmtLst();
        vector<VarName> allUsedVariables, e;
        for(Node* s: stmtLst) {
            e = extractUses(s);
            allUsedVariables.insert(allUsedVariables.end(), e.begin(), e.end());
        }
        PKB::getInstance()->setUsesP(value->getProcName(), unordered_set<VarName>{allUsedVariables.begin(), allUsedVariables.end()});
        return allUsedVariables;
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
        PKB::getInstance()->setUsesS(value->getStmtNumber(), unordered_set<VarName>{allUsedVariables.begin(), allUsedVariables.end()});
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

        PKB::getInstance()->setUsesS(value->getStmtNumber(), unordered_set<VarName>{allUsedVariables.begin(), allUsedVariables.end()});
        return allUsedVariables;
    } else if(auto value = dynamic_cast<AssignNode*>(node)) {
        vector<VarName> variables = value->getListOfVarUsed();
        PKB::getInstance()->setUsesS(value->getStmtNumber(), unordered_set<VarName>{variables.begin(), variables.end()});
        return variables;
    } else if(auto value = dynamic_cast<PrintNode*>(node)) {
        vector<VarName> variables = value->getListOfVarUsed();
        PKB::getInstance()->setUsesS(value->getStmtNumber(), unordered_set<VarName>{variables.begin(), variables.end()});
        return variables;
    } else if (auto value = dynamic_cast<CallNode*>(node)) {
        Node* procedureCalled = value->getProcedure();
        vector<VarName> variables = extractUses(procedureCalled);
        PKB::getInstance()->setUsesS(value->getStmtNumber(),
                                        unordered_set<VarName>{variables.begin(), variables.end()});
        return variables;
    } else {
        return {};
    }


}

//set all variables modified by the node in the pkb
vector<string> RelationshipExtractor::extractModifies (Node * node) {
    if(auto value = dynamic_cast<ProgramNode*>(node)) {
        vector<ProcedureNode*> v = value -> getProcLst();
        for(ProcedureNode* p: v)
            extractModifies(p);

        return {};
    } else if(auto value = dynamic_cast<ProcedureNode*>(node)) {
        vector<Node*> stmtLst = value->getStmtLst();
        vector<VarName> allModifiedVariables, e;
        for(Node* s: stmtLst) {
            e = extractModifies(s);
            allModifiedVariables.insert(allModifiedVariables.end(), e.begin(), e.end());
        }
        PKB::getInstance()->setModifiesP(value->getProcName(), unordered_set<VarName>{allModifiedVariables.begin(), allModifiedVariables.end()});
        return allModifiedVariables;
    } else if(auto value = dynamic_cast<WhileNode*>(node)) {
        vector<Node*> stmtLst = value->getStmtLst();
        vector<VarName> allModifiedVariables;
        for(Node* stmt: stmtLst) {
            vector<VarName> modifiedVariables = extractModifies(stmt);
            allModifiedVariables.insert(allModifiedVariables.end(), modifiedVariables.begin(), modifiedVariables.end());
        }
        PKB::getInstance()->setModifiesS(value->getStmtNumber(), unordered_set<VarName>{allModifiedVariables.begin(), allModifiedVariables.end()});
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
        PKB::getInstance()->setModifiesS(value->getStmtNumber(), unordered_set<VarName>{allModifiedVariables.begin(), allModifiedVariables.end()});
        return allModifiedVariables;
    } else if(auto value = dynamic_cast<AssignNode*>(node)) {
        vector<VarName> variables = value->getListOfVarModified();
        PKB::getInstance()->setModifiesS(value->getStmtNumber(), unordered_set<VarName>{variables.begin(), variables.end()});
        return variables;
    } else if(auto value = dynamic_cast<ReadNode*>(node)) {
        vector<VarName> variables = value->getListOfVarModified();
        PKB::getInstance()->setModifiesS(value->getStmtNumber(),
                                        unordered_set<VarName>{variables.begin(), variables.end()});
        return variables;
    } else if (auto value = dynamic_cast<CallNode*>(node)) {
        Node* procedureCalled = value->getProcedure();
        vector<VarName> variables = extractModifies(procedureCalled);
        PKB::getInstance()->setModifiesS(value->getStmtNumber(),
                                        unordered_set<VarName>{variables.begin(), variables.end()});
        return variables;
    } else {
        return {};
    }
}
void RelationshipExtractor::extractCalls(Node * node, vector<StmtLstNode*> procList, ProcedureNode currProcName) {
    if(auto value = dynamic_cast<ProgramNode*>(node)) {
        vector<ProcedureNode *> v = value->getProcLst();
        for (ProcedureNode *p: v)
            extractCalls(p,procList,*p);

    }else if(node->hasStmtLst()) {
        int numOfChildNodes = node->getStmtLst().size();
        if(node->getStmtNumber()!=-1) {
            procList.push_back((StmtLstNode *) node);
            Node *parent = node;
            for (int i = 0; i < (numOfChildNodes); i++) {
                Node *child = node->getStmtLst().at(i);
                PKB::getInstance()->setParent(parent->getStmtNumber(), child->getStmtNumber());
                for (int j = 0; j < procList.size(); j++) {
                    Node *parentT = procList.at(j);
                    PKB::getInstance()->setParentT(parentT->getStmtNumber(), child->getStmtNumber());
                }
            }
        }
        for (int i = 0; i < (numOfChildNodes); i++) {
            extractParent(node->getStmtLst().at(i), procList);
        }
    }else if (auto value = dynamic_cast<CallNode*>(node)){
//        PKB::getInstance()->setCalls()
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
        PKB::getInstance()->addWhileStatement(value);
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
        PKB::getInstance()->addIfStatement(value);
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
        PKB::getInstance()->addAssignStatement(value);
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
        PKB::getInstance()->addReadStatement(value);
        PKB::getInstance()->addVariable(value->getVarName());
    } else if(auto value = dynamic_cast<PrintNode*>(node)) {
        PKB::getInstance()->addPrintStatement(value);
        PKB::getInstance()->addVariable(value->getVarName());
    } else if(auto value = dynamic_cast<CallNode*>(node)) {
        PKB::getInstance()->addCallStatement(value);
        PKB::getInstance()->addProcedure(value->getProcName());//Not sure if needed
    }
}

vector<ProcName> getAllProcedureCall(Node* node) {
    if(auto value = dynamic_cast<CallNode*>(node)) {
        ProcName procName = value->getProcName();
        return vector<ProcName>{procName};
    } else if (auto value = dynamic_cast<IfNode*>(node)) {
        vector<Node*> stmtLstNode = value->getStmtLst();
        vector<ProcName> procNameList, e;
        for(Node* s: stmtLstNode) {
            e = getAllProcedureCall(s);
            procNameList.insert(procNameList.end(), e.begin(), e.end());
        }
        return procNameList;
    } else if (auto value = dynamic_cast<WhileNode*>(node)) {
        vector<Node*> stmtLstNode = value->getStmtLst();
        vector<ProcName> procNameList, e;
        for(Node* s: stmtLstNode) {
            e = getAllProcedureCall(s);
            procNameList.insert(procNameList.end(), e.begin(), e.end());
        }
        return procNameList;
    } else if (auto value = dynamic_cast<ProcedureNode*>(node)) {
        vector<Node*> stmtLstNode = value->getStmtLst();
        vector<ProcName> procNameList, e;
        for(Node* s: stmtLstNode) {
            e = getAllProcedureCall(s);
            procNameList.insert(procNameList.end(), e.begin(), e.end());
        }
        return procNameList;
    }  else {
        return {};
    };
}

bool detectCyclicCallsRec(ProcName name,
                          unordered_map<ProcName, GraphNode*> graphNodes,
                          unordered_map<ProcName, bool> visited,
                          unordered_map<ProcName, bool> stack) {
    if(visited[name] == false) {
        visited[name] = true;
        stack[name] = true;
        GraphNode* currentNode = graphNodes[name];
        vector<ProcName> nameList = currentNode->getDirectedNodes();
        vector<ProcName>::iterator i;
        for(i = nameList.begin(); i != nameList.end(); ++i) {
            if(!visited[*i] &&
                    detectCyclicCallsRec(*i, graphNodes, stack, visited))
                return true;
            else if (stack[*i] == true) return true;
        }
    }
    stack[name] = false;
    return false;
}
void detectCyclicCalls(Node* node) {
    auto programNode = dynamic_cast<ProgramNode *>(node);
    vector<ProcedureNode *> v = programNode->getProcLst();

    unordered_map<ProcName, GraphNode *> graphNodes;
    vector < ProcName > allProcName;
    unordered_map<ProcName, bool> visited;
    unordered_map<ProcName, bool> stack;

    for (ProcedureNode *p: v) {
        ProcName name = p->getProcName();
        vector < ProcName > NodesFromP = getAllProcedureCall(p);
        GraphNode *node = new GraphNode(name, NodesFromP);
        graphNodes[name] = node;
        allProcName.push_back(name);
        visited[name], stack[name] = false;
    }
    // perform DFS to check for recursions
    for (int i = 0; i < allProcName.size(); i++) {
        ProcName name = allProcName[i];
        if (!visited[name] && detectCyclicCallsRec(name, graphNodes, visited, stack)) {
            cout << "cyclic call statements detected\n";
            graphNodes.clear();
            throw "cyclic calls detected\n";
        }
    }
    graphNodes.clear();
}

void detectDuplicateProcedure(Node * node) {
    if(auto value = dynamic_cast<ProgramNode*>(node)) {
        unordered_set<ProcName> procNames;
        ProcedureList procLst = value->getProcLst();
        for(ProcedureNode* p: procLst) {
            if(procNames.find(p->getProcName()) != procNames.end()) {
                throw "Cannot have duplicate Procedure names";
            }
            procNames.insert(p->getProcName());
        }
    }
}

void RelationshipExtractor::extractRelationships(Node * node){
    // check for semantics error
    detectDuplicateProcedure(node);
    detectCyclicCalls(node);

    //extract variables and constants etc
    extractAllEntities(node);

    //extract relationship
    vector<StmtLstNode*> v;
    extractFollows(node);
    extractParent(node,v);
    extractUses(node);
    extractModifies(node);
}

