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

    REQUIRE(fkb->statement.statementClass.getAllStatementNumbers().empty());

    for (int i = 1; i <= 10; i++) {
        auto n = StmtNode(i);
        fkb->statement.statementClass.addStatement(&n);
    }

    unordered_set<string> statementsSet = fkb->statement.statementClass.getAllStatementNumbers();

    for (int i = 1; i <= 10; i++) {
        string s = std::to_string(i);

        REQUIRE(fkb->statement.statementClass.isStatementNumber(s));

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

    REQUIRE(fkb->statement.assignStatementClass.getAllStatementNumbers().empty());

    unordered_set<int> statements = {1, 7, 45, 898, 124214123, 989988999};

    for (int i : statements) {
        auto n = AssignNode(i, &v, &v);
        fkb->statement.assignStatementClass.addStatement(&n);
    }

    unordered_set<string> assignStatementsSet = fkb->statement.assignStatementClass.getAllStatementNumbers();

    for (int i: statements) {
        string s = std::to_string(i);

        REQUIRE(fkb->statement.assignStatementClass.isStatementNumber(s));

        REQUIRE(assignStatementsSet.find(s) != assignStatementsSet.end());
    }

}


TEST_CASE("Add Read Statements") {
    fkb->clearFKB();

    REQUIRE(fkb->statement.readStatementClass.getAllStatementNumbers().empty());

    unordered_set<int> statements = {1, 7, 45, 898, 124214123, 989988999};

    for (int i : statements) {
        auto n = ReadNode(i, &v);
        fkb->statement.readStatementClass.addStatement(&n);
    }

    unordered_set<string> readStatementsSet = fkb->statement.readStatementClass.getAllStatementNumbers();

    for (int i: statements) {
        string s = std::to_string(i);

        REQUIRE(fkb->statement.readStatementClass.isStatementNumber(s));

        REQUIRE(readStatementsSet.find(s) != readStatementsSet.end());
    }

}

TEST_CASE("Add Print Statements") {
    fkb->clearFKB();

    REQUIRE(fkb->statement.printStatementClass.getAllStatementNumbers().empty());

    unordered_set<int> statements = {1, 7, 45, 898, 124214123, 989988999};

    for (int i : statements) {
        auto n = PrintNode(i, &v);
        fkb->statement.printStatementClass.addStatement(&n);
    }

    unordered_set<string> printStatementsSet = fkb->statement.printStatementClass.getAllStatementNumbers();

    for (int i: statements) {
        string s = std::to_string(i);

        REQUIRE(fkb->statement.printStatementClass.isStatementNumber(s));

        REQUIRE(printStatementsSet.find(s) != printStatementsSet.end());
    }

}


TEST_CASE("Add If Statements") {
    fkb->clearFKB();

    REQUIRE(fkb->statement.ifStatementClass.getAllStatementNumbers().empty());

    unordered_set<int> statements = {1, 7, 45, 898, 124214123, 989988999};

    for (int i : statements) {
        auto n = IfNode(i, &cond, {}, {});
        fkb->statement.ifStatementClass.addStatement(&n);
    }

    unordered_set<string> ifStatementsSet = fkb->statement.ifStatementClass.getAllStatementNumbers();

    for (int i: statements) {
        string s = std::to_string(i);

        REQUIRE(fkb->statement.ifStatementClass.isStatementNumber(s));

        REQUIRE(ifStatementsSet.find(s) != ifStatementsSet.end());
    }
}



TEST_CASE("Add While Statements") {
    fkb->clearFKB();

    REQUIRE(fkb->statement.whileStatementClass.getAllStatementNumbers().empty());

    unordered_set<int> statements = {1, 7, 45, 898, 124214123, 989988999};

    for (int i : statements) {
        auto n = WhileNode(i, &cond, {});
        fkb->statement.whileStatementClass.addStatement(&n);
    }

    unordered_set<string> whileStatementsSet = fkb->statement.whileStatementClass.getAllStatementNumbers();

    for (int i: statements) {
        string s = std::to_string(i);

        REQUIRE(fkb->statement.whileStatementClass.isStatementNumber(s));

        REQUIRE(whileStatementsSet.find(s) != whileStatementsSet.end());
    }
}


TEST_CASE("Add Follows") {
    fkb->clearFKB();

    REQUIRE(fkb->relationship.followsRelationshipClass.getLHS("2").empty());
    REQUIRE(fkb->relationship.followsRelationshipClass.getRHS("1").empty());

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

        fkb->relationship.followsRelationshipClass.setRelationship(followee, follower);
    }


    REQUIRE(fkb->relationship.followsRelationshipClass.isRelationship("1", "2") == false);
    REQUIRE(fkb->relationship.followsRelationshipClass.getRHS("2") == unordered_set<string>{});
    REQUIRE(fkb->relationship.followsRelationshipClass.getLHS("3") == unordered_set<string>{});

    for (auto& iter : followeeToFollowerMap) {
        string followee = std::to_string(iter.first);
        string follower = std::to_string(iter.second);

        REQUIRE(fkb->relationship.followsRelationshipClass.isRelationship(followee, follower));
        REQUIRE(fkb->relationship.followsRelationshipClass.getRHS(followee) == unordered_set<string>{follower});
        REQUIRE(fkb->relationship.followsRelationshipClass.getLHS(follower) == unordered_set<string>{followee});
    }


}


TEST_CASE("Add FollowsT") {
    fkb->clearFKB();

    REQUIRE(fkb->relationship.tFollowsRelationshipClass.getSetLHS("2").empty());
    REQUIRE(fkb->relationship.tFollowsRelationshipClass.getSetRHS("1").empty());


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
            fkb->relationship.tFollowsRelationshipClass.setRelationship(followee, follower);
        }

    }


    REQUIRE(fkb->relationship.tFollowsRelationshipClass.isRelationship("1", "3") == false);
    REQUIRE(fkb->relationship.tFollowsRelationshipClass.getSetRHS("2") == unordered_set<string>{});
    REQUIRE(fkb->relationship.tFollowsRelationshipClass.getSetLHS("3") == unordered_set<string>{});


    for (auto& iter : tFolloweeToFollowersMap) {
        string followee = std::to_string(iter.first);
        unordered_set<int> followerIntegers = iter.second;
        unordered_set<string> followers;
        for (int follower : followerIntegers) {
            followers.insert(std::to_string(follower));
        }

        for (string follower : followers) {
            REQUIRE(fkb->relationship.tFollowsRelationshipClass.isRelationship(followee, follower));

            unordered_set<string> followeesSet = fkb->relationship.tFollowsRelationshipClass.getSetLHS(follower);
            REQUIRE(followeesSet.find(followee) != followeesSet.end());
        }

        REQUIRE(fkb->relationship.tFollowsRelationshipClass.getSetRHS(followee) == followers);
    }


}


TEST_CASE("Add Parent") {
    fkb->clearFKB();

    REQUIRE(fkb->relationship.parentRelationshipClass.getLHS("2").empty());
    REQUIRE(fkb->relationship.parentRelationshipClass.getSetRHS("1").empty());

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
            fkb->relationship.parentRelationshipClass.setRelationship(parent, child);
        }
    }


    REQUIRE(fkb->relationship.parentRelationshipClass.isRelationship("1", "3") == false);
    REQUIRE(fkb->relationship.parentRelationshipClass.getLHS("3") == unordered_set<string>{});
    REQUIRE(fkb->relationship.parentRelationshipClass.getSetRHS("2") == unordered_set<string>{});


    for (auto& iter : parentToChildrenMap) {

        string parent = std::to_string(iter.first);

        unordered_set<int> childrenIntegers = iter.second;
        unordered_set<string> children;
        for (int child : childrenIntegers) {
            children.insert(std::to_string(child));
        }


        for (string child : children) {
            REQUIRE(fkb->relationship.parentRelationshipClass.isRelationship(parent, child));
            REQUIRE(fkb->relationship.parentRelationshipClass.getLHS(child) == unordered_set<string>{parent});
        }

        REQUIRE(fkb->relationship.parentRelationshipClass.getSetRHS(parent) == children);

    }


}


TEST_CASE("Add ParentT") {
    fkb->clearFKB();

    REQUIRE(fkb->relationship.tParentRelationshipClass.getSetLHS("2").empty());
    REQUIRE(fkb->relationship.tParentRelationshipClass.getSetRHS("1").empty());


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
            fkb->relationship.tParentRelationshipClass.setRelationship(parent, child);
        }

    }

    REQUIRE(fkb->relationship.tParentRelationshipClass.isRelationship("1", "3") == false);
    REQUIRE(fkb->relationship.tParentRelationshipClass.getSetLHS("3") == unordered_set<string>{});
    REQUIRE(fkb->relationship.tParentRelationshipClass.getSetRHS("2") == unordered_set<string>{});


    for (auto& iter : tParentToChildrenMap) {
        string parent = std::to_string(iter.first);
        unordered_set<int> childrenIntegers = iter.second;
        unordered_set<string> children;
        for (int child : childrenIntegers) {
            children.insert(std::to_string(child));
        }

        for (string child : children) {
            REQUIRE(fkb->relationship.tParentRelationshipClass.isRelationship(parent, child));

            unordered_set<string> parentsSet = fkb->relationship.tParentRelationshipClass.getSetLHS(child);
            REQUIRE(parentsSet.find(parent) != parentsSet.end());
        }

        REQUIRE(fkb->relationship.tParentRelationshipClass.getSetRHS(parent) == children);
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
            fkb->relationship.usesSRelationshipClass.setRelationship(statement, variable);
        }


    }

    REQUIRE(fkb->relationship.usesSRelationshipClass.isRelationship("2", "a") == false);
    REQUIRE(fkb->relationship.usesSRelationshipClass.getSetLHS("unusedVariable") == unordered_set<string>{});
    REQUIRE(fkb->relationship.usesSRelationshipClass.getSetRHS("3") == unordered_set<string>{});


    for (auto& iter : statementToVariablesUsedMap) {

        string statement = std::to_string(iter.first);
        unordered_set<string> variablesUsed = iter.second;

        for (string v : variablesUsed) {
            REQUIRE(fkb->relationship.usesSRelationshipClass.isRelationship(statement, v));

            unordered_set<string> userStatements = fkb->relationship.usesSRelationshipClass.getSetLHS(v);
            REQUIRE(userStatements.find(statement) != userStatements.end());
        }

        REQUIRE(fkb->relationship.usesSRelationshipClass.getSetRHS(statement) == variablesUsed);

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
            fkb->relationship.modifiesSRelationshipClass.setRelationship(statement, variable);
        }


    }


    REQUIRE(fkb->relationship.modifiesSRelationshipClass.isRelationship("2", "a") == false);
    REQUIRE(fkb->relationship.modifiesSRelationshipClass.getSetLHS("unmodifiedVariable") == unordered_set<string>{});
    REQUIRE(fkb->relationship.modifiesSRelationshipClass.getSetRHS("3") == unordered_set<string>{});


    for (auto& iter : statementToVariablesModifiedMap) {

        string statement = std::to_string(iter.first);
        unordered_set<string> variablesModified = iter.second;

        for (string v : variablesModified) {
            REQUIRE(fkb->relationship.modifiesSRelationshipClass.isRelationship(statement, v));

            unordered_set<string> modifierStatements = fkb->relationship.modifiesSRelationshipClass.getSetLHS(v);
            REQUIRE(modifierStatements.find(statement) != modifierStatements.end());
        }

        REQUIRE(fkb->relationship.modifiesSRelationshipClass.getSetRHS(statement) == variablesModified);

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
