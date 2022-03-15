//
// Created by Karan Dev Sapra on 17/2/22.
//

//#include "FKB.h"
#include "PKB/FKB.h"

#include "TNode/TNode.h"

#include "catch.hpp"

//#include "FKB/FKB.h"

using namespace std;

FKB *fkb = FKB::getInstance();

VariableNode v = VariableNode("name");
BinaryOperatorNode bn = BinaryOperatorNode(&v, &v, "+");
RelExprNode rel = RelExprNode(&v, &v, "&&");
CondExprNode cond = CondExprNode(&rel);



TEST_CASE("Add statements") {
    fkb->clearFKB();

    REQUIRE(fkb->statement.statements.getAllStatementNumbers().empty());

    for (int i = 1; i <= 10; i++) {
        auto n = StmtNode(i);
        fkb->statement.statements.addStatement(&n);
    }

    unordered_set<string> statementsSet = fkb->statement.statements.getAllStatementNumbers();

    for (int i = 1; i <= 10; i++) {
        string s = std::to_string(i);

        REQUIRE(fkb->statement.statements.isStatementNumber(s));

        REQUIRE(statementsSet.find(s) != statementsSet.end());
    }

}

TEST_CASE("Add variables") {
    fkb->clearFKB();

    REQUIRE(fkb->entity.variables.getAll().empty());

    unordered_set<string> variables = {"a", "b", "c", "obama", "trump", "biden"};

    for (string v: variables) {
        fkb->entity.variables.add(v);
    }

    unordered_set<string> variablesSet = fkb->entity.variables.getAll();

    for (string v: variables) {
        REQUIRE(fkb->entity.variables.isEntity(v));

        REQUIRE(variablesSet.find(v) != variablesSet.end());
    }

}


TEST_CASE("Add procedures") {
    fkb->clearFKB();

    REQUIRE(fkb->entity.procedures.getAll().empty());

    unordered_set<string> procedures = {"a", "b", "c", "obama", "trump", "biden"};

    for (string p: procedures) {
        fkb->entity.procedures.add(p);
    }

    unordered_set<string> proceduresSet = fkb->entity.procedures.getAll();

    for (string p: procedures) {
        REQUIRE(fkb->entity.procedures.isEntity(p));

        REQUIRE(proceduresSet.find(p) != proceduresSet.end());
    }

}

TEST_CASE("Add constants") {
    fkb->clearFKB();

    REQUIRE(fkb->entity.constants.getAll().empty());

    unordered_set<string> constants = {"1", "2", "3", "1111111111111111111111111111", "123456789012345678901234567890", "99999999999999999999999999999999999999999999999999999"};

    for (string c: constants) {
        fkb->entity.constants.add(c);
    }

    unordered_set<string> constantsSet = fkb->entity.constants.getAll();

    for (string c: constants) {
        REQUIRE(fkb->entity.constants.isEntity(c));

        REQUIRE(constantsSet.find(c) != constantsSet.end());
    }

}


TEST_CASE("Add Assign Statements") {
    fkb->clearFKB();

    REQUIRE(fkb->statement.assignStatements.getAllStatementNumbers().empty());

    unordered_set<int> statements = {1, 7, 45, 898, 124214123, 989988999};

    for (int i : statements) {
        auto n = AssignNode(i, &v, &v);
        fkb->statement.assignStatements.addStatement(&n);
    }

    unordered_set<string> assignStatementsSet = fkb->statement.assignStatements.getAllStatementNumbers();

    for (int i: statements) {
        string s = std::to_string(i);

        REQUIRE(fkb->statement.assignStatements.isStatementNumber(s));

        REQUIRE(assignStatementsSet.find(s) != assignStatementsSet.end());
    }

}


TEST_CASE("Add Read Statements") {
    fkb->clearFKB();

    REQUIRE(fkb->statement.readStatements.getAllStatementNumbers().empty());

    unordered_set<int> statements = {1, 7, 45, 898, 124214123, 989988999};

    for (int i : statements) {
        auto n = ReadNode(i, &v);
        fkb->statement.readStatements.addStatement(&n);
    }

    unordered_set<string> readStatementsSet = fkb->statement.readStatements.getAllStatementNumbers();

    for (int i: statements) {
        string s = std::to_string(i);

        REQUIRE(fkb->statement.readStatements.isStatementNumber(s));

        REQUIRE(readStatementsSet.find(s) != readStatementsSet.end());
    }

}

TEST_CASE("Add Print Statements") {
    fkb->clearFKB();

    REQUIRE(fkb->statement.printStatements.getAllStatementNumbers().empty());

    unordered_set<int> statements = {1, 7, 45, 898, 124214123, 989988999};

    for (int i : statements) {
        auto n = PrintNode(i, &v);
        fkb->statement.printStatements.addStatement(&n);
    }

    unordered_set<string> printStatementsSet = fkb->statement.printStatements.getAllStatementNumbers();

    for (int i: statements) {
        string s = std::to_string(i);

        REQUIRE(fkb->statement.printStatements.isStatementNumber(s));

        REQUIRE(printStatementsSet.find(s) != printStatementsSet.end());
    }

}


TEST_CASE("Add If Statements") {
    fkb->clearFKB();

    REQUIRE(fkb->statement.ifStatements.getAllStatementNumbers().empty());

    unordered_set<int> statements = {1, 7, 45, 898, 124214123, 989988999};

    for (int i : statements) {
        auto n = IfNode(i, &cond, {}, {});
        fkb->statement.ifStatements.addStatement(&n);
    }

    unordered_set<string> ifStatementsSet = fkb->statement.ifStatements.getAllStatementNumbers();

    for (int i: statements) {
        string s = std::to_string(i);

        REQUIRE(fkb->statement.ifStatements.isStatementNumber(s));

        REQUIRE(ifStatementsSet.find(s) != ifStatementsSet.end());
    }
}



TEST_CASE("Add While Statements") {
    fkb->clearFKB();

    REQUIRE(fkb->statement.whileStatements.getAllStatementNumbers().empty());

    unordered_set<int> statements = {1, 7, 45, 898, 124214123, 989988999};

    for (int i : statements) {
        auto n = WhileNode(i, &cond, {});
        fkb->statement.whileStatements.addStatement(&n);
    }

    unordered_set<string> whileStatementsSet = fkb->statement.whileStatements.getAllStatementNumbers();

    for (int i: statements) {
        string s = std::to_string(i);

        REQUIRE(fkb->statement.whileStatements.isStatementNumber(s));

        REQUIRE(whileStatementsSet.find(s) != whileStatementsSet.end());
    }
}


TEST_CASE("Add Follows") {
    fkb->clearFKB();

    REQUIRE(fkb->relationship.follows.getLHS("2").empty());
    REQUIRE(fkb->relationship.follows.getRHS("1").empty());

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

        fkb->relationship.follows.setRelationship(followee, follower);
    }


    REQUIRE(fkb->relationship.follows.isRelationship("1", "2") == false);
    REQUIRE(fkb->relationship.follows.getRHS("2") == unordered_set<string>{});
    REQUIRE(fkb->relationship.follows.getLHS("3") == unordered_set<string>{});

    for (auto& iter : followeeToFollowerMap) {
        string followee = std::to_string(iter.first);
        string follower = std::to_string(iter.second);

        REQUIRE(fkb->relationship.follows.isRelationship(followee, follower));
        REQUIRE(fkb->relationship.follows.getRHS(followee) == unordered_set<string>{follower});
        REQUIRE(fkb->relationship.follows.getLHS(follower) == unordered_set<string>{followee});
    }


}


TEST_CASE("Add FollowsT") {
    fkb->clearFKB();

    REQUIRE(fkb->relationship.followsT.getSetLHS("2").empty());
    REQUIRE(fkb->relationship.followsT.getSetRHS("1").empty());


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
            fkb->relationship.followsT.setRelationship(followee, follower);
        }

    }


    REQUIRE(fkb->relationship.followsT.isRelationship("1", "3") == false);
    REQUIRE(fkb->relationship.followsT.getSetRHS("2") == unordered_set<string>{});
    REQUIRE(fkb->relationship.followsT.getSetLHS("3") == unordered_set<string>{});


    for (auto& iter : tFolloweeToFollowersMap) {
        string followee = std::to_string(iter.first);
        unordered_set<int> followerIntegers = iter.second;
        unordered_set<string> followers;
        for (int follower : followerIntegers) {
            followers.insert(std::to_string(follower));
        }

        for (string follower : followers) {
            REQUIRE(fkb->relationship.followsT.isRelationship(followee, follower));

            unordered_set<string> followeesSet = fkb->relationship.followsT.getSetLHS(follower);
            REQUIRE(followeesSet.find(followee) != followeesSet.end());
        }

        REQUIRE(fkb->relationship.followsT.getSetRHS(followee) == followers);
    }


}


TEST_CASE("Add Parent") {
    fkb->clearFKB();

    REQUIRE(fkb->relationship.parent.getLHS("2").empty());
    REQUIRE(fkb->relationship.parent.getSetRHS("1").empty());

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
            fkb->relationship.parent.setRelationship(parent, child);
        }
    }


    REQUIRE(fkb->relationship.parent.isRelationship("1", "3") == false);
    REQUIRE(fkb->relationship.parent.getLHS("3") == unordered_set<string>{});
    REQUIRE(fkb->relationship.parent.getSetRHS("2") == unordered_set<string>{});


    for (auto& iter : parentToChildrenMap) {

        string parent = std::to_string(iter.first);

        unordered_set<int> childrenIntegers = iter.second;
        unordered_set<string> children;
        for (int child : childrenIntegers) {
            children.insert(std::to_string(child));
        }


        for (string child : children) {
            REQUIRE(fkb->relationship.parent.isRelationship(parent, child));
            REQUIRE(fkb->relationship.parent.getLHS(child) == unordered_set<string>{parent});
        }

        REQUIRE(fkb->relationship.parent.getSetRHS(parent) == children);

    }


}


TEST_CASE("Add ParentT") {
    fkb->clearFKB();

    REQUIRE(fkb->relationship.parentT.getSetLHS("2").empty());
    REQUIRE(fkb->relationship.parentT.getSetRHS("1").empty());


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
            fkb->relationship.parentT.setRelationship(parent, child);
        }

    }

    REQUIRE(fkb->relationship.parentT.isRelationship("1", "3") == false);
    REQUIRE(fkb->relationship.parentT.getSetLHS("3") == unordered_set<string>{});
    REQUIRE(fkb->relationship.parentT.getSetRHS("2") == unordered_set<string>{});


    for (auto& iter : tParentToChildrenMap) {
        string parent = std::to_string(iter.first);
        unordered_set<int> childrenIntegers = iter.second;
        unordered_set<string> children;
        for (int child : childrenIntegers) {
            children.insert(std::to_string(child));
        }

        for (string child : children) {
            REQUIRE(fkb->relationship.parentT.isRelationship(parent, child));

            unordered_set<string> parentsSet = fkb->relationship.parentT.getSetLHS(child);
            REQUIRE(parentsSet.find(parent) != parentsSet.end());
        }

        REQUIRE(fkb->relationship.parentT.getSetRHS(parent) == children);
    }


}


TEST_CASE("Add Uses") {
    fkb->clearFKB();

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

        for (string variable : variablesUsed) {
            fkb->relationship.usesS.setRelationship(statement, variable);
        }


    }

    REQUIRE(fkb->relationship.usesS.isRelationship("2", "a") == false);
    REQUIRE(fkb->relationship.usesS.getSetLHS("unusedVariable") == unordered_set<string>{});
    REQUIRE(fkb->relationship.usesS.getSetRHS("3") == unordered_set<string>{});


    for (auto& iter : statementToVariablesUsedMap) {

        string statement = std::to_string(iter.first);
        unordered_set<string> variablesUsed = iter.second;

        for (string v : variablesUsed) {
            REQUIRE(fkb->relationship.usesS.isRelationship(statement, v));

            unordered_set<string> userStatements = fkb->relationship.usesS.getSetLHS(v);
            REQUIRE(userStatements.find(statement) != userStatements.end());
        }

        REQUIRE(fkb->relationship.usesS.getSetRHS(statement) == variablesUsed);

    }


}



TEST_CASE("Add Modifies") {
    fkb->clearFKB();

    unordered_map<int, unordered_set<string>> statementToVariablesModifiedMap = {
            {1, {"a"}},
            {4, {"obama", "biden", "trump"}},
            {34, {"red", "green", "yellow", "blue", "white", "black"}},
            {56, {"a", "b", "c", "d", "e", "f"}},
            {345, {"x", "y", "z"}},
    };

    for (auto& iter : statementToVariablesModifiedMap) {
        int statement = iter.first;
        unordered_set<string> variablesUsed = iter.second;

        for (string variable : variablesUsed) {
            fkb->relationship.modifiesS.setRelationship(statement, variable);
        }


    }


    REQUIRE(fkb->relationship.modifiesS.isRelationship("2", "a") == false);
    REQUIRE(fkb->relationship.modifiesS.getSetLHS("unmodifiedVariable") == unordered_set<string>{});
    REQUIRE(fkb->relationship.modifiesS.getSetRHS("3") == unordered_set<string>{});


    for (auto& iter : statementToVariablesModifiedMap) {

        string statement = std::to_string(iter.first);
        unordered_set<string> variablesModified = iter.second;

        for (string v : variablesModified) {
            REQUIRE(fkb->relationship.modifiesS.isRelationship(statement, v));

            unordered_set<string> modifierStatements = fkb->relationship.modifiesS.getSetLHS(v);
            REQUIRE(modifierStatements.find(statement) != modifierStatements.end());
        }

        REQUIRE(fkb->relationship.modifiesS.getSetRHS(statement) == variablesModified);

    }


}



//TEST_CASE("Add Assign Node") {
//    fkb->clearFKB();
//
//    unordered_set<AssignNode *> assignNodesSet;
//
//    for (int stmtNo = 1; stmtNo <= 10; stmtNo++) {
//        VariableNode* leftNode = new VariableNode("leftVar");
//        VariableNode* rightNode = new VariableNode("rightVar");
//        AssignNode* newNode = new AssignNode(stmtNo, leftNode, rightNode);
//
//        assignNodesSet.insert(newNode);
//    }
//
//    for (AssignNode *assignNode : assignNodesSet) {
//        fkb->addAssignNode(assignNode);
//    }
//
//    vector<AssignNode *> resultsVector = fkb->getAllAssignNodes();
//    unordered_set<AssignNode *> resultsSet(resultsVector.begin(), resultsVector.end());
//
//    REQUIRE(assignNodesSet == resultsSet);
//
//}
