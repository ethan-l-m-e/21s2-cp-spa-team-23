//
// Created by Karan Dev Sapra on 17/2/22.
//

//#include "PKB.h"
#include "PKB/PKB.h"

#include "TNode/TNode.h"

#include "catch.hpp"

using namespace std;

PKB *pkb = PKB::getInstance();

VariableNode v = VariableNode("name");
BinaryOperatorNode bn = BinaryOperatorNode(&v, &v, "+");
RelExprNode rel = RelExprNode(&v, &v, "&&");
CondExprNode cond = CondExprNode(&rel);



TEST_CASE("Add statements") {
    pkb->clearPKB();

    REQUIRE(pkb->statement.statements.getAllStatementNumbers().empty());

    unordered_set<StmtNode *> statementNodes;

    for (int i = 1; i <= 10; i++) {
        auto n = StmtNode(i);
        statementNodes.insert(&n);
        pkb->statement.statements.addStatement(&n);
    }

    REQUIRE(pkb->statement.statements.getAllStatementNodes() == statementNodes);

    unordered_set<string> statementsSet = pkb->statement.statements.getAllStatementNumbers();

    for (int i = 1; i <= 10; i++) {
        string s = std::to_string(i);

        REQUIRE(pkb->statement.statements.isStatementNumber(s));

        REQUIRE(statementsSet.find(s) != statementsSet.end());
    }

}

TEST_CASE("Add variables") {
    pkb->clearPKB();

    REQUIRE(pkb->entity.variables.getAll().empty());

    unordered_set<string> variables = {"a", "b", "c", "obama", "trump", "biden"};

    for (string v: variables) {
        pkb->entity.variables.add(v);
    }

    unordered_set<string> variablesSet = pkb->entity.variables.getAll();

    for (string v: variables) {
        REQUIRE(pkb->entity.variables.isEntity(v));

        REQUIRE(variablesSet.find(v) != variablesSet.end());
    }

}


TEST_CASE("Add procedures") {
    pkb->clearPKB();

    REQUIRE(pkb->entity.procedures.getAll().empty());

    unordered_set<string> procedures = {"a", "b", "c", "obama", "trump", "biden"};

    for (string p: procedures) {
        pkb->entity.procedures.add(p);
    }

    unordered_set<string> proceduresSet = pkb->entity.procedures.getAll();

    for (string p: procedures) {
        REQUIRE(pkb->entity.procedures.isEntity(p));

        REQUIRE(proceduresSet.find(p) != proceduresSet.end());
    }

}

TEST_CASE("Add constants") {
    pkb->clearPKB();

    REQUIRE(pkb->entity.constants.getAll().empty());

    unordered_set<string> constants = {"1", "2", "3", "1111111111111111111111111111", "123456789012345678901234567890", "99999999999999999999999999999999999999999999999999999"};

    for (string c: constants) {
        pkb->entity.constants.add(c);
    }

    unordered_set<string> constantsSet = pkb->entity.constants.getAll();

    for (string c: constants) {
        REQUIRE(pkb->entity.constants.isEntity(c));

        REQUIRE(constantsSet.find(c) != constantsSet.end());
    }

}


TEST_CASE("Add Assign Statements") {
    pkb->clearPKB();

    REQUIRE(pkb->statement.assignStatements.getAllStatementNumbers().empty());

    unordered_set<int> statements = {1, 7, 45, 898, 124214123, 989988999};

    unordered_set<AssignNode *> statementNodes;

    for (int i : statements) {
        auto n = AssignNode(i, &v, &v);
        statementNodes.insert(&n);
        pkb->statement.assignStatements.addStatement(&n);
    }


    REQUIRE(pkb->statement.assignStatements.getAllStatementNodes() == statementNodes);

    unordered_set<string> assignStatementsSet = pkb->statement.assignStatements.getAllStatementNumbers();

    for (int i: statements) {
        string s = std::to_string(i);

        REQUIRE(pkb->statement.assignStatements.isStatementNumber(s));

        REQUIRE(assignStatementsSet.find(s) != assignStatementsSet.end());
    }

}


TEST_CASE("Add Read Statements") {
    pkb->clearPKB();

    REQUIRE(pkb->statement.readStatements.getAllStatementNumbers().empty());

    unordered_map<int, string> statementToVariableMap = {{1, "apple"},
                                                         {7, "orange"},
                                                         {45, "guava"},
                                                         {898, "mango"},
                                                         {124214123, "banana"},
                                                         {989988999, "grapes"}};

    unordered_set<ReadNode *> statementNodes;

    for (auto& iter : statementToVariableMap) {
        int i = iter.first;
        string name = iter.second;

        VariableNode v = VariableNode(name);
        auto n = ReadNode(i, &v);
        statementNodes.insert(&n);
        pkb->statement.readStatements.addStatement(&n);
    }


    REQUIRE(pkb->statement.readStatements.getAllStatementNodes() == statementNodes);

    unordered_set<string> readStatementsSet = pkb->statement.readStatements.getAllStatementNumbers();

    for (auto& iter : statementToVariableMap) {

        int i = iter.first;
        string name = iter.second;

        string s = std::to_string(i);

        REQUIRE(pkb->statement.readStatements.isStatementNumber(s));
        REQUIRE(readStatementsSet.find(s) != readStatementsSet.end());

        REQUIRE(pkb->statement.readStatements.getVariableName(s) == name);
    }

}

TEST_CASE("Add Print Statements") {
    pkb->clearPKB();

    REQUIRE(pkb->statement.printStatements.getAllStatementNumbers().empty());

    unordered_map<int, string> statementToVariableMap = {{1, "apple"},
                                                         {7, "orange"},
                                                         {45, "guava"},
                                                         {898, "mango"},
                                                         {124214123, "banana"},
                                                         {989988999, "grapes"}};


    unordered_set<PrintNode *> statementNodes;

    for (auto& iter : statementToVariableMap) {
        int i = iter.first;
        string name = iter.second;

        VariableNode f = VariableNode(name);

        auto n = PrintNode(i, &f);
        statementNodes.insert(&n);
        pkb->statement.printStatements.addStatement(&n);
    }

    REQUIRE(pkb->statement.printStatements.getAllStatementNodes() == statementNodes);

    unordered_set<string> printStatementsSet = pkb->statement.printStatements.getAllStatementNumbers();

    for (auto& iter : statementToVariableMap) {
        int i = iter.first;
        string name = iter.second;

        string s = std::to_string(i);

        REQUIRE(pkb->statement.printStatements.isStatementNumber(s));

        REQUIRE(printStatementsSet.find(s) != printStatementsSet.end());

        REQUIRE(pkb->statement.printStatements.getVariableName(s) == name);
    }

}


TEST_CASE("Add If Statements") {
    pkb->clearPKB();

    REQUIRE(pkb->statement.ifStatements.getAllStatementNumbers().empty());

    unordered_set<int> statements = {1, 7, 45, 898, 124214123, 989988999};

    unordered_set<IfNode *> statementNodes;

    for (int i : statements) {
        auto n = IfNode(i, &cond, {}, {});
        statementNodes.insert(&n);
        pkb->statement.ifStatements.addStatement(&n);
    }

    REQUIRE(pkb->statement.ifStatements.getAllStatementNodes() == statementNodes);

    unordered_set<string> ifStatementsSet = pkb->statement.ifStatements.getAllStatementNumbers();

    for (int i: statements) {
        string s = std::to_string(i);

        REQUIRE(pkb->statement.ifStatements.isStatementNumber(s));

        REQUIRE(ifStatementsSet.find(s) != ifStatementsSet.end());
    }
}



TEST_CASE("Add While Statements") {
    pkb->clearPKB();

    REQUIRE(pkb->statement.whileStatements.getAllStatementNumbers().empty());

    unordered_set<int> statements = {1, 7, 45, 898, 124214123, 989988999};

    unordered_set<WhileNode *> statementNodes;

    for (int i : statements) {
        auto n = WhileNode(i, &cond, {});
        statementNodes.insert(&n);
        pkb->statement.whileStatements.addStatement(&n);
    }

    REQUIRE(pkb->statement.whileStatements.getAllStatementNodes() == statementNodes);

    unordered_set<string> whileStatementsSet = pkb->statement.whileStatements.getAllStatementNumbers();

    for (int i: statements) {
        string s = std::to_string(i);

        REQUIRE(pkb->statement.whileStatements.isStatementNumber(s));

        REQUIRE(whileStatementsSet.find(s) != whileStatementsSet.end());
    }
}


TEST_CASE("Add Call Statements") {
    pkb->clearPKB();

    REQUIRE(pkb->statement.callStatements.getAllStatementNumbers().empty());

    unordered_map<int, string> statementToVariableMap = {{1, "apple"},
                                                         {7, "orange"},
                                                         {45, "guava"},
                                                         {898, "mango"},
                                                         {124214123, "banana"},
                                                         {989988999, "grapes"}};


    unordered_set<CallNode *> statementNodes;

    for (auto& iter : statementToVariableMap) {
        int i = iter.first;
        string name = iter.second;

        ProcNameNode procedureName = ProcNameNode(name);
        auto n = CallNode(i, &procedureName);
        statementNodes.insert(&n);
        pkb->statement.callStatements.addStatement(&n);
    }


    REQUIRE(pkb->statement.callStatements.getAllStatementNodes() == statementNodes);

    unordered_set<string> callStatementsSet = pkb->statement.callStatements.getAllStatementNumbers();

    for (auto& iter : statementToVariableMap) {
        int i = iter.first;
        string name = iter.second;

        string s = std::to_string(i);

        REQUIRE(pkb->statement.callStatements.isStatementNumber(s));

        REQUIRE(callStatementsSet.find(s) != callStatementsSet.end());

        REQUIRE(pkb->statement.callStatements.getProcedureName(s) == name);
    }
}


TEST_CASE("Add Follows") {
    pkb->clearPKB();

    REQUIRE(pkb->relationship.follows.getLHS("2").empty());
    REQUIRE(pkb->relationship.follows.getRHS("1").empty());

    unordered_map<int, int> followeeToFollowerMap = {
            {1, 5},
            {4, 8},
            {34, 84},
            {56, 89},
            {345, 986},
    };


    for (auto& iter : followeeToFollowerMap) {
        int followee = iter.first;
        int follower = iter.second;

        pkb->relationship.follows.setRelationship(followee, follower);
    }


    REQUIRE(pkb->relationship.follows.isRelationship("1", "2") == false);
    REQUIRE(pkb->relationship.follows.getRHS("2") == unordered_set<string>{});
    REQUIRE(pkb->relationship.follows.getLHS("3") == unordered_set<string>{});

    for (auto& iter : followeeToFollowerMap) {
        string followee = std::to_string(iter.first);
        string follower = std::to_string(iter.second);

        REQUIRE(pkb->relationship.follows.isRelationship(followee, follower));
        REQUIRE(pkb->relationship.follows.getRHS(followee) == unordered_set<string>{follower});
        REQUIRE(pkb->relationship.follows.getLHS(follower) == unordered_set<string>{followee});
    }


}


TEST_CASE("Add FollowsT") {
    pkb->clearPKB();

    REQUIRE(pkb->relationship.followsT.getSetLHS("2").empty());
    REQUIRE(pkb->relationship.followsT.getSetRHS("1").empty());


    unordered_map<int, unordered_set<int>> tFolloweeToFollowersMap = {
            {1, {2}},
            {4, {8, 23}},
            {34, {45, 55, 67, 84}},
            {56, {89}},
            {345, {347, 349, 358, 456, 568, 678, 789, 986}},
    };


    for (auto& iter : tFolloweeToFollowersMap) {
        int followee = iter.first;
        unordered_set<int> followers = iter.second;

        for (int follower : followers) {
            pkb->relationship.followsT.setRelationship(followee, follower);
        }

    }


    REQUIRE(pkb->relationship.followsT.isRelationship("1", "3") == false);
    REQUIRE(pkb->relationship.followsT.getSetRHS("2") == unordered_set<string>{});
    REQUIRE(pkb->relationship.followsT.getSetLHS("3") == unordered_set<string>{});


    for (auto& iter : tFolloweeToFollowersMap) {
        string followee = std::to_string(iter.first);
        unordered_set<int> followerIntegers = iter.second;
        unordered_set<string> followers;
        for (int follower : followerIntegers) {
            followers.insert(std::to_string(follower));
        }

        for (string follower : followers) {
            REQUIRE(pkb->relationship.followsT.isRelationship(followee, follower));

            unordered_set<string> followeesSet = pkb->relationship.followsT.getSetLHS(follower);
            REQUIRE(followeesSet.find(followee) != followeesSet.end());
        }

        REQUIRE(pkb->relationship.followsT.getSetRHS(followee) == followers);
    }


}


TEST_CASE("Add Parent") {
    pkb->clearPKB();

    REQUIRE(pkb->relationship.parent.getLHS("2").empty());
    REQUIRE(pkb->relationship.parent.getSetRHS("1").empty());

    unordered_map<int, unordered_set<int>> parentToChildrenMap = {
            {1, {2}},
            {4, {8,9,10,11,12,13,14,15,16}},
            {34, {45, 47, 51}},
            {56, {89, 98, 123, 167, 265}},
            {345, {567, 986}},
    };


    for (auto& iter : parentToChildrenMap) {
        int parent = iter.first;
        unordered_set<int> children = iter.second;

        for (int child : children) {
            pkb->relationship.parent.setRelationship(parent, child);
        }
    }


    REQUIRE(pkb->relationship.parent.isRelationship("1", "3") == false);
    REQUIRE(pkb->relationship.parent.getLHS("3") == unordered_set<string>{});
    REQUIRE(pkb->relationship.parent.getSetRHS("2") == unordered_set<string>{});


    for (auto& iter : parentToChildrenMap) {

        string parent = std::to_string(iter.first);

        unordered_set<int> childrenIntegers = iter.second;
        unordered_set<string> children;
        for (int child : childrenIntegers) {
            children.insert(std::to_string(child));
        }


        for (string child : children) {
            REQUIRE(pkb->relationship.parent.isRelationship(parent, child));
            REQUIRE(pkb->relationship.parent.getLHS(child) == unordered_set<string>{parent});
        }

        REQUIRE(pkb->relationship.parent.getSetRHS(parent) == children);

    }


}


TEST_CASE("Add ParentT") {
    pkb->clearPKB();

    REQUIRE(pkb->relationship.parentT.getSetLHS("2").empty());
    REQUIRE(pkb->relationship.parentT.getSetRHS("1").empty());


    unordered_map<int, unordered_set<int>> tParentToChildrenMap = {
            {1, {2}},
            {4, {8, 23}},
            {34, {45, 55, 67, 84}},
            {56, {89}},
            {345, {347, 349, 358, 456, 568, 678, 789, 986}},
    };


    for (auto& iter : tParentToChildrenMap) {
        int parent = iter.first;
        unordered_set<int> children = iter.second;

        for (int child : children) {
            pkb->relationship.parentT.setRelationship(parent, child);
        }

    }

    REQUIRE(pkb->relationship.parentT.isRelationship("1", "3") == false);
    REQUIRE(pkb->relationship.parentT.getSetLHS("3") == unordered_set<string>{});
    REQUIRE(pkb->relationship.parentT.getSetRHS("2") == unordered_set<string>{});


    for (auto& iter : tParentToChildrenMap) {
        string parent = std::to_string(iter.first);
        unordered_set<int> childrenIntegers = iter.second;
        unordered_set<string> children;
        for (int child : childrenIntegers) {
            children.insert(std::to_string(child));
        }

        for (string child : children) {
            REQUIRE(pkb->relationship.parentT.isRelationship(parent, child));

            unordered_set<string> parentsSet = pkb->relationship.parentT.getSetLHS(child);
            REQUIRE(parentsSet.find(parent) != parentsSet.end());
        }

        REQUIRE(pkb->relationship.parentT.getSetRHS(parent) == children);
    }


}


TEST_CASE("Add UsesS") {
    pkb->clearPKB();

    unordered_map<int, unordered_set<string>> statementToVariablesUsedMap = {
            {1, {"a"}},
            {4, {"obama", "biden", "trump"}},
            {34, {"red", "green", "yellow", "blue", "white", "black"}},
            {56, {"a", "b", "c", "d", "e", "f"}},
            {345, {"x", "y", "z"}},
    };

    for (auto& iter : statementToVariablesUsedMap) {
        int statement = iter.first;
        unordered_set<string> variablesUsed = iter.second;

        pkb->relationship.usesS.setRelationship(statement, variablesUsed);



    }

    REQUIRE(pkb->relationship.usesS.isRelationship("2", "a") == false);
    REQUIRE(pkb->relationship.usesS.getSetLHS("unusedVariable") == unordered_set<string>{});
    REQUIRE(pkb->relationship.usesS.getSetRHS("3") == unordered_set<string>{});


    for (auto& iter : statementToVariablesUsedMap) {

        string statement = std::to_string(iter.first);
        unordered_set<string> variablesUsed = iter.second;

        for (string v : variablesUsed) {
            REQUIRE(pkb->relationship.usesS.isRelationship(statement, v));

            unordered_set<string> userStatements = pkb->relationship.usesS.getSetLHS(v);
            REQUIRE(userStatements.find(statement) != userStatements.end());
        }

        REQUIRE(pkb->relationship.usesS.getSetRHS(statement) == variablesUsed);

    }


}


TEST_CASE("Add UsesP") {
    pkb->clearPKB();

    unordered_map<string, unordered_set<string>> procedureToVariablesUsedMap = {
            {"apple", {"a"}},
            {"orange", {"obama", "biden", "trump"}},
            {"watermelon", {"red", "green", "yellow", "blue", "white", "black"}},
            {"mango", {"a", "b", "c", "d", "e", "f"}},
            {"lychee", {"x", "y", "z"}},
    };

    for (auto& iter : procedureToVariablesUsedMap) {
        string procedure = iter.first;
        unordered_set<string> variablesUsed = iter.second;

        pkb->relationship.usesP.setRelationship(procedure, variablesUsed);


    }

    REQUIRE(pkb->relationship.usesP.isRelationship("banana", "a") == false);
    REQUIRE(pkb->relationship.usesP.getSetLHS("unusedVariable") == unordered_set<string>{});
    REQUIRE(pkb->relationship.usesP.getSetRHS("dragonfruit") == unordered_set<string>{});


    for (auto& iter : procedureToVariablesUsedMap) {

        string procedure = iter.first;
        unordered_set<string> variablesUsed = iter.second;

        for (string v : variablesUsed) {
            REQUIRE(pkb->relationship.usesP.isRelationship(procedure, v));

            unordered_set<string> userStatements = pkb->relationship.usesP.getSetLHS(v);
            REQUIRE(userStatements.find(procedure) != userStatements.end());
        }

        REQUIRE(pkb->relationship.usesP.getSetRHS(procedure) == variablesUsed);

    }


}



TEST_CASE("Add ModifiesS") {
    pkb->clearPKB();

    unordered_map<int, unordered_set<string>> statementToVariablesModifiedMap = {
            {1, {"a"}},
            {4, {"obama", "biden", "trump"}},
            {34, {"red", "green", "yellow", "blue", "white", "black"}},
            {56, {"a", "b", "c", "d", "e", "f"}},
            {345, {"x", "y", "z"}},
    };

    for (auto& iter : statementToVariablesModifiedMap) {
        int statement = iter.first;
        unordered_set<string> variablesModified = iter.second;

        pkb->relationship.modifiesS.setRelationship(statement, variablesModified);


    }


    REQUIRE(pkb->relationship.modifiesS.isRelationship("2", "a") == false);
    REQUIRE(pkb->relationship.modifiesS.getSetLHS("unmodifiedVariable") == unordered_set<string>{});
    REQUIRE(pkb->relationship.modifiesS.getSetRHS("3") == unordered_set<string>{});


    for (auto& iter : statementToVariablesModifiedMap) {

        string statement = std::to_string(iter.first);
        unordered_set<string> variablesModified = iter.second;

        for (string v : variablesModified) {
            REQUIRE(pkb->relationship.modifiesS.isRelationship(statement, v));

            unordered_set<string> modifierStatements = pkb->relationship.modifiesS.getSetLHS(v);
            REQUIRE(modifierStatements.find(statement) != modifierStatements.end());
        }

        REQUIRE(pkb->relationship.modifiesS.getSetRHS(statement) == variablesModified);

    }


}



TEST_CASE("Add ModifiesP") {
    pkb->clearPKB();

    unordered_map<string, unordered_set<string>> procedureToVariablesModifiedMap = {
            {"apple", {"a"}},
            {"orange", {"obama", "biden", "trump"}},
            {"watermelon", {"red", "green", "yellow", "blue", "white", "black"}},
            {"mango", {"a", "b", "c", "d", "e", "f"}},
            {"lychee", {"x", "y", "z"}},
    };

    for (auto& iter : procedureToVariablesModifiedMap) {
        string procedure = iter.first;
        unordered_set<string> variablesModified = iter.second;

        pkb->relationship.modifiesP.setRelationship(procedure, variablesModified);


    }


    REQUIRE(pkb->relationship.modifiesP.isRelationship("banana", "a") == false);
    REQUIRE(pkb->relationship.modifiesP.getSetLHS("unmodifiedVariable") == unordered_set<string>{});
    REQUIRE(pkb->relationship.modifiesP.getSetRHS("dragonfruit") == unordered_set<string>{});


    for (auto& iter : procedureToVariablesModifiedMap) {

        string procedure = iter.first;
        unordered_set<string> variablesModified = iter.second;

        for (string v : variablesModified) {
            REQUIRE(pkb->relationship.modifiesP.isRelationship(procedure, v));

            unordered_set<string> modifierStatements = pkb->relationship.modifiesP.getSetLHS(v);
            REQUIRE(modifierStatements.find(procedure) != modifierStatements.end());
        }

        REQUIRE(pkb->relationship.modifiesP.getSetRHS(procedure) == variablesModified);

    }


}



TEST_CASE("Add Next") {
    pkb->clearPKB();

    unordered_map<int, NodeCFG *> statementNumberToNodeCFGMap;


    for (int statementNumber : {1, 2, 34, 56, 57, 345}) {

        NodeCFG node = NodeCFG(statementNumber);

        statementNumberToNodeCFGMap.emplace(statementNumber, &node);
    }


    for (auto& iter : statementNumberToNodeCFGMap) {
        int statementNumber = iter.first;
        NodeCFG *node = iter.second;

        pkb->relationship.next.setRelationship(statementNumber, node);
    }



    REQUIRE(pkb->relationship.next.getCFGSize() == statementNumberToNodeCFGMap.size());


    for (auto& iter : statementNumberToNodeCFGMap) {
        int statementNumber = iter.first;
        NodeCFG *node = iter.second;

        REQUIRE(pkb->relationship.next.getCFGNode(statementNumber) == node);

    }


}
