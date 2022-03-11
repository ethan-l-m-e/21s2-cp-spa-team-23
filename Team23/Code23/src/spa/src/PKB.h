#pragma once

#include<stdio.h>
#include <iostream>
#include <string>
#include <vector>

#include <unordered_set>
#include <unordered_map>

using namespace std;
typedef short PROC;

class TNode;


class StmtNode;
class AssignNode;
class ReadNode;
class PrintNode;
class IfNode;
class WhileNode;
class CallNode;

class VarTable;  // no need to #include "VarTable.h" as all I need is postringer

class PKB {

private:
    PKB();

    static PKB* singleton;

    unordered_set<int> statementsSet;
    unordered_set<string> variablesSet;
    unordered_set<string> proceduresSet;
    unordered_set<string> constantsSet;

    unordered_set<int> assignStatementsSet;
    unordered_set<int> readStatementsSet;
    unordered_set<int> printStatementsSet;
    unordered_set<int> ifStatementsSet;
    unordered_set<int> whileStatementsSet;
    unordered_set<int> callStatementsSet;

    unordered_set<StmtNode *> statementNodesSet;
    unordered_set<ReadNode *> readNodesSet;
    unordered_set<PrintNode *> printNodesSet;
    unordered_set<IfNode *> ifNodesSet;
    unordered_set<WhileNode *> whileNodesSet;
    unordered_set<CallNode *> callNodesSet;

    unordered_map<int, int> followeeToFollowerMap;
    unordered_map<int, int> followerToFolloweeMap;

    unordered_map<int, unordered_set<int>> tFolloweeToFollowersMap;
    unordered_map<int, unordered_set<int>> tFollowerToFolloweesMap;

    unordered_map<int, unordered_set<int>> parentToChildrenMap;
    unordered_map<int, int> childToParentMap;

    unordered_map<int, unordered_set<int>> tParentToChildrenMap;
    unordered_map<int, unordered_set<int>> tChildToParentsMap;


    unordered_map<int, unordered_set<string>> statementToVariablesUsedMap;
    unordered_map<string, unordered_set<int>> variableUsedToStatementMap;

    unordered_map<int, unordered_set<string>> statementToVariablesModifiedMap;
    unordered_map<string, unordered_set<int>> variableModifiedToStatementMap;

    unordered_map<string, unordered_set<string>> procedureToVariablesUsedMap;
    unordered_map<string, unordered_set<string>> variableUsedToProcedureMap;

    unordered_map<string, unordered_set<string>> procedureToVariablesModifiedMap;
    unordered_map<string, unordered_set<string>> variableModifiedToProcedureMap;

    unordered_set<AssignNode *> assignNodesSet;

    // Getter Functions (Variables, Procedures etc.)

    bool isStatement(int statement);

    // Getter Functions (Statement Types)

    bool isAssignStatement(int statement);
    bool isReadStatement(int statement);
    bool isPrintStatement(int statement);
    bool isIfStatement(int statement);
    bool isWhileStatement(int statement);
    bool isCallStatement(int statement);

    // Getter Functions (Follows Relationship)

    bool isFollows(int followee, int follower);
    unordered_set<int> getFollower(int followee);
    unordered_set<int> getFollowee(int follower);

    // Getter Functions (FollowsT Relationship)

    bool isFollowsT(int followee, int follower);
    unordered_set<int> getFollowerT(int followee);
    unordered_set<int> getFolloweeT(int follower);

    // Getter Functions (Parent Relationship)

    bool isParent(int parent, int child);
    unordered_set<int> getChildren(int parent);
    unordered_set<int> getParent(int child);


    // Getter Functions (ParentT Relationship)

    bool isParentT(int parent, int child);
    unordered_set<int> getChildrenT(int parent);
    unordered_set<int> getParentT(int child);


    // Getter Functions (Uses Relationship)

    bool isUsesS(int statement, string variable);
    unordered_set<string> getVariablesUsedS(int statement);

    // Getter Functions (Modifies Relationship)

    bool isModifiesS(int statement, string variable);
    unordered_set<string> getVariablesModifiedS(int statement);

public:
//	static VarTable* varTable;
//	static string setProcToAST(PROC p, TNode* r);
//	static TNode* getRootAST (PROC p);


    static PKB* getInstance();

    void clearPKB();

    // Setter Functions (Assign Nodes)

    void addAssignNode(AssignNode *assignNode);

    // Getter Functions (Assign Nodes)

    vector<AssignNode *> getAllAssignNodes();

    // Setter Functions (Variables, Procedures etc.)
    void addStatement(StmtNode *node);
    void addVariable(string variable);
    void addProcedure(string procedure);
    void addConstant(string constant);

    // Setter Functions (Statement Types)

    void addAssignStatement(AssignNode *node);

    void addReadStatement(ReadNode *node);
    void addPrintStatement(PrintNode *node);

    void addIfStatement(IfNode *node);
    void addWhileStatement(WhileNode *node);

    void addCallStatement(CallNode *node);

    // Getter Functions (Variables, Procedures etc.)

    bool isStatement(string statement);

    bool isVariable(string variable);
    bool isProcedure(string procedure);
    bool isConstant(string constant);

    unordered_set<string> getAllStatements();
    unordered_set<string> getAllVariables();
    unordered_set<string> getAllProcedures();
    unordered_set<string> getAllConstants();

    // Getter Functions (Statement Types)

    bool isAssignStatement(string statement);
    bool isReadStatement(string statement);
    bool isPrintStatement(string statement);
    bool isIfStatement(string statement);
    bool isWhileStatement(string statement);
    bool isCallStatement(string statement);



    unordered_set<string> getAllAssignStatements();
    unordered_set<string> getAllReadStatements();
    unordered_set<string> getAllPrintStatements();
    unordered_set<string> getAllIfStatements();
    unordered_set<string> getAllWhileStatements();
    unordered_set<string> getAllCallStatements();

    //----------------------------------------------------------------------------------RELATIONSHIP SETTER FUNCTIONS---------------------------------------------------------------------------------------------------------------------------------------------------------------

    // Setter Functions (Follows Relationship)
    void setFollows(int followee, int follower);

    // Setter Functions (FollowsT Relationship)
    void setFollowsT(int followee, int follower);

    // Setter Functions (Parent Relationship)
    void setParent(int parent, int child);

    // Setter Functions (ParentT Relationship)
    void setParentT(int parent, int child);

    // Setter Functions (Uses Relationship)

    void setUsesS(int statement, unordered_set<string> variables);
    void setUsesP(string procedure, unordered_set<string> variables);

    // Setter Functions (Modifies Relationship)

    void setModifiesS(int statement, unordered_set<string> variables);
    void setModifiesP(string procedure, unordered_set<string> variables);


    //----------------------------------------------------------------------------------RELATIONSHIP GETTER FUNCTIONS---------------------------------------------------------------------------------------------------------------------------------------------------------------

    // Getter Functions (Follows Relationship)

    bool isFollows(string followee, string follower);
    unordered_set<string> getFollower(string followee);
    unordered_set<string> getFollowee(string follower);

    // Getter Functions (FollowsT Relationship)

    bool isFollowsT(string followee, string follower);
    unordered_set<string> getFollowerT(string followee);
    unordered_set<string> getFolloweeT(string follower);


    // Getter Functions (Parent Relationship)

    bool isParent(string parent, string child);
    unordered_set<string> getChildren(string parent);
    unordered_set<string> getParent(string child);


    // Getter Functions (ParentT Relationship)

    bool isParentT(string parent, string child);
    unordered_set<string> getChildrenT(string parent);
    unordered_set<string> getParentT(string child);


    // Getter Functions (Uses Relationship)

    bool isUsesS(string statement, string variable);
    unordered_set<string> getVariablesUsedS(string statement);
    unordered_set<string> getUserStatements(string variable);

    // Getter Functions (Modifies Relationship)

    bool isModifiesS(string statement, string variable);
    unordered_set<string> getVariablesModifiedS(string statement);
    unordered_set<string> getModifierStatements(string variable);

    bool isUsesP(string procedure, string variable);
    unordered_set<string> getVariablesUsedP(string procedure);
    unordered_set<string> getUserProcedures(string variable);

    bool isModifiesP(string procedure, string variable);
    unordered_set<string> getVariablesModifiedP(string procedure);
    unordered_set<string> getModifierProcedures(string variable);


    // Return a string representing the variable being read in a read statement.
    string getVarRead(string stmtNo);

    // Return a string representing the variable being printed in a print statement
    string getVarPrinted(string stmtNo);

    // Return a string representing the procedure name being called in a call statement.
    string getProcByCall(string stmtNo);
};


