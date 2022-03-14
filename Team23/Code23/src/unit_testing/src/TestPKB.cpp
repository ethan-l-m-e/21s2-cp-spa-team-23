//
// Created by Karan Dev Sapra on 17/2/22.
//

//#include "PKB.h"
#include "PKB/PKB.h"

#include "TNode/TNode.h"

#include "catch.hpp"

//#include "PKB/PKB.h"

using namespace std;

PKB *pkb = PKB::getInstance();

VariableNode v = VariableNode("name");
BinaryOperatorNode bn = BinaryOperatorNode(&v, &v, "+");
RelExprNode rel = RelExprNode(&v, &v, "&&");
CondExprNode cond = CondExprNode(&rel);



TEST_CASE("Add statements") {
    pkb->clearPKB();

    REQUIRE(pkb->statement.statementClass.getAllStatementNumbers().empty());

    for (int i = 1; i <= 10; i++) {
        auto n = StmtNode(i);
        pkb->statement.statementClass.addStatement(&n);
    }

    unordered_set<string> statementsSet = pkb->statement.statementClass.getAllStatementNumbers();

    for (int i = 1; i <= 10; i++) {
        string s = std::to_string(i);

        REQUIRE(pkb->statement.statementClass.isStatementNumber(s));

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

    REQUIRE(pkb->statement.assignStatementClass.getAllStatementNumbers().empty());

    unordered_set<int> statements = {1, 7, 45, 898, 124214123, 989988999};

    for (int i : statements) {
        auto n = AssignNode(i, &v, &v);
        pkb->statement.assignStatementClass.addStatement(&n);
    }

    unordered_set<string> assignStatementsSet = pkb->statement.assignStatementClass.getAllStatementNumbers();

    for (int i: statements) {
        string s = std::to_string(i);

        REQUIRE(pkb->statement.assignStatementClass.isStatementNumber(s));

        REQUIRE(assignStatementsSet.find(s) != assignStatementsSet.end());
    }

}


TEST_CASE("Add Read Statements") {
    pkb->clearPKB();

    REQUIRE(pkb->statement.readStatementClass.getAllStatementNumbers().empty());

    unordered_set<int> statements = {1, 7, 45, 898, 124214123, 989988999};

    for (int i : statements) {
        auto n = ReadNode(i, &v);
        pkb->statement.readStatementClass.addStatement(&n);
    }

    unordered_set<string> readStatementsSet = pkb->statement.readStatementClass.getAllStatementNumbers();

    for (int i: statements) {
        string s = std::to_string(i);

        REQUIRE(pkb->statement.readStatementClass.isStatementNumber(s));

        REQUIRE(readStatementsSet.find(s) != readStatementsSet.end());
    }

}

TEST_CASE("Add Print Statements") {
    pkb->clearPKB();

    REQUIRE(pkb->statement.printStatementClass.getAllStatementNumbers().empty());

    unordered_set<int> statements = {1, 7, 45, 898, 124214123, 989988999};

    for (int i : statements) {
        auto n = PrintNode(i, &v);
        pkb->statement.printStatementClass.addStatement(&n);
    }

    unordered_set<string> printStatementsSet = pkb->statement.printStatementClass.getAllStatementNumbers();

    for (int i: statements) {
        string s = std::to_string(i);

        REQUIRE(pkb->statement.printStatementClass.isStatementNumber(s));

        REQUIRE(printStatementsSet.find(s) != printStatementsSet.end());
    }

}


TEST_CASE("Add If Statements") {
    pkb->clearPKB();

    REQUIRE(pkb->statement.ifStatementClass.getAllStatementNumbers().empty());

    unordered_set<int> statements = {1, 7, 45, 898, 124214123, 989988999};

    for (int i : statements) {
        auto n = IfNode(i, &cond, {}, {});
        pkb->statement.ifStatementClass.addStatement(&n);
    }

    unordered_set<string> ifStatementsSet = pkb->statement.ifStatementClass.getAllStatementNumbers();

    for (int i: statements) {
        string s = std::to_string(i);

        REQUIRE(pkb->statement.ifStatementClass.isStatementNumber(s));

        REQUIRE(ifStatementsSet.find(s) != ifStatementsSet.end());
    }
}



TEST_CASE("Add While Statements") {
    pkb->clearPKB();

    REQUIRE(pkb->statement.whileStatementClass.getAllStatementNumbers().empty());

    unordered_set<int> statements = {1, 7, 45, 898, 124214123, 989988999};

    for (int i : statements) {
        auto n = WhileNode(i, &cond, {});
        pkb->statement.whileStatementClass.addStatement(&n);
    }

    unordered_set<string> whileStatementsSet = pkb->statement.whileStatementClass.getAllStatementNumbers();

    for (int i: statements) {
        string s = std::to_string(i);

        REQUIRE(pkb->statement.whileStatementClass.isStatementNumber(s));

        REQUIRE(whileStatementsSet.find(s) != whileStatementsSet.end());
    }
}


TEST_CASE("Add Follows") {
    pkb->clearPKB();

    REQUIRE(pkb->relationship.followsRelationshipClass.getLHS("2").empty());
    REQUIRE(pkb->relationship.followsRelationshipClass.getRHS("1").empty());

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

        pkb->relationship.followsRelationshipClass.setRelationship(followee, follower);
    }


    REQUIRE(pkb->relationship.followsRelationshipClass.isRelationship("1", "2") == false);
    REQUIRE(pkb->relationship.followsRelationshipClass.getRHS("2") == unordered_set<string>{});
    REQUIRE(pkb->relationship.followsRelationshipClass.getLHS("3") == unordered_set<string>{});

    for (auto& iter : followeeToFollowerMap) {
        string followee = std::to_string(iter.first);
        string follower = std::to_string(iter.second);

        REQUIRE(pkb->relationship.followsRelationshipClass.isRelationship(followee, follower));
        REQUIRE(pkb->relationship.followsRelationshipClass.getRHS(followee) == unordered_set<string>{follower});
        REQUIRE(pkb->relationship.followsRelationshipClass.getLHS(follower) == unordered_set<string>{followee});
    }


}


TEST_CASE("Add FollowsT") {
    pkb->clearPKB();

    REQUIRE(pkb->relationship.tFollowsRelationshipClass.getSetLHS("2").empty());
    REQUIRE(pkb->relationship.tFollowsRelationshipClass.getSetRHS("1").empty());


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
            pkb->relationship.tFollowsRelationshipClass.setRelationship(followee, follower);
        }

    }


    REQUIRE(pkb->relationship.tFollowsRelationshipClass.isRelationship("1", "3") == false);
    REQUIRE(pkb->relationship.tFollowsRelationshipClass.getSetRHS("2") == unordered_set<string>{});
    REQUIRE(pkb->relationship.tFollowsRelationshipClass.getSetLHS("3") == unordered_set<string>{});


    for (auto& iter : tFolloweeToFollowersMap) {
        string followee = std::to_string(iter.first);
        unordered_set<int> followerIntegers = iter.second;
        unordered_set<string> followers;
        for (int follower : followerIntegers) {
            followers.insert(std::to_string(follower));
        }

        for (string follower : followers) {
            REQUIRE(pkb->relationship.tFollowsRelationshipClass.isRelationship(followee, follower));

            unordered_set<string> followeesSet = pkb->relationship.tFollowsRelationshipClass.getSetLHS(follower);
            REQUIRE(followeesSet.find(followee) != followeesSet.end());
        }

        REQUIRE(pkb->relationship.tFollowsRelationshipClass.getSetRHS(followee) == followers);
    }


}


TEST_CASE("Add Parent") {
    pkb->clearPKB();

    REQUIRE(pkb->relationship.parentRelationshipClass.getLHS("2").empty());
    REQUIRE(pkb->relationship.parentRelationshipClass.getRHS("1").empty());

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
            pkb->relationship.parentRelationshipClass.setRelationship(parent, child);
        }
    }


    REQUIRE(pkb->relationship.parentRelationshipClass.isRelationship("1", "3") == false);
    REQUIRE(pkb->relationship.parentRelationshipClass.getLHS("3") == unordered_set<string>{});
    REQUIRE(pkb->relationship.parentRelationshipClass.getRHS("2") == unordered_set<string>{});


    for (auto& iter : parentToChildrenMap) {

        string parent = std::to_string(iter.first);

        unordered_set<int> childrenIntegers = iter.second;
        unordered_set<string> children;
        for (int child : childrenIntegers) {
            children.insert(std::to_string(child));
        }


        for (string child : children) {
            REQUIRE(pkb->relationship.parentRelationshipClass.isRelationship(parent, child));
            REQUIRE(pkb->relationship.parentRelationshipClass.getLHS(child) == unordered_set<string>{parent});
        }

        REQUIRE(pkb->relationship.parentRelationshipClass.getRHS(parent) == children);

    }


}


TEST_CASE("Add ParentT") {
    pkb->clearPKB();

    REQUIRE(pkb->relationship.tParentRelationshipClass.getSetLHS("2").empty());
    REQUIRE(pkb->relationship.tParentRelationshipClass.getSetRHS("1").empty());


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
            pkb->relationship.tParentRelationshipClass.setRelationship(parent, child);
        }

    }

    REQUIRE(pkb->relationship.tParentRelationshipClass.isRelationship("1", "3") == false);
    REQUIRE(pkb->relationship.tParentRelationshipClass.getSetLHS("3") == unordered_set<string>{});
    REQUIRE(pkb->relationship.tParentRelationshipClass.getSetRHS("2") == unordered_set<string>{});


    for (auto& iter : tParentToChildrenMap) {
        string parent = std::to_string(iter.first);
        unordered_set<int> childrenIntegers = iter.second;
        unordered_set<string> children;
        for (int child : childrenIntegers) {
            children.insert(std::to_string(child));
        }

        for (string child : children) {
            REQUIRE(pkb->relationship.tParentRelationshipClass.isRelationship(parent, child));

            unordered_set<string> parentsSet = pkb->relationship.tParentRelationshipClass.getSetLHS(child);
            REQUIRE(parentsSet.find(parent) != parentsSet.end());
        }

        REQUIRE(pkb->relationship.tParentRelationshipClass.getSetRHS(parent) == children);
    }


}


//TEST_CASE("Add Uses") {
//    pkb->clearPKB();
//
//    unordered_map<int, unordered_set<string>> statementToVariablesUsedMap = {
//            {1, {"a"}},
//            {4, {"obama", "biden", "trump"}},
//            {34, {"red", "green", "yellow", "blue", "white", "black"}},
//            {56, {"a", "b", "c", "d", "e", "f"}},
//            {345, {"x", "y", "z"}},
//    };
//
//    for (auto& iter : statementToVariablesUsedMap) {
//        int statement = iter.first;
//        unordered_set<string> variablesUsed = iter.second;
//
//        pkb->relationship.usesSRelationshipClass.setRelationship(statement, variablesUsed);
//
//    }
//
//    REQUIRE(pkb->relationship.usesSRelationshipClass.isRelationship("2", "a") == false);
//    REQUIRE(pkb->relationship.usesSRelationshipClass.getLHS("unusedVariable") == unordered_set<string>{});
//    REQUIRE(pkb->relationship.usesSRelationshipClass.getRHS("3") == unordered_set<string>{});
//
//
//    for (auto& iter : statementToVariablesUsedMap) {
//
//        string statement = std::to_string(iter.first);
//        unordered_set<string> variablesUsed = iter.second;
//
//        for (string v : variablesUsed) {
//            REQUIRE(pkb->relationship.usesSRelationshipClass.isRelationship(statement, v));
//
//            unordered_set<string> userStatements = pkb->relationship.usesSRelationshipClass.getLHS(v);
//            REQUIRE(userStatements.find(statement) != userStatements.end());
//        }
//
//        REQUIRE(pkb->relationship.usesSRelationshipClass.getRHS(statement) == variablesUsed);
//
//    }
//
//
//}



//TEST_CASE("Add Modifies") {
//    pkb->clearPKB();
//
//    unordered_map<int, unordered_set<string>> statementToVariablesModifiedMap = {
//            {1, {"a"}},
//            {4, {"obama", "biden", "trump"}},
//            {34, {"red", "green", "yellow", "blue", "white", "black"}},
//            {56, {"a", "b", "c", "d", "e", "f"}},
//            {345, {"x", "y", "z"}},
//    };
//
//    for (auto& iter : statementToVariablesModifiedMap) {
//        int statement = iter.first;
//        unordered_set<string> variablesUsed = iter.second;
//
//        pkb->relationship.modifiesSRelationshipClass.setRelationship(statement, variablesUsed);
//
//    }
//
//
//    REQUIRE(pkb->relationship.modifiesSRelationshipClass.isRelationship("2", "a") == false);
//    REQUIRE(pkb->relationship.modifiesSRelationshipClass.getLHS("unmodifiedVariable") == unordered_set<string>{});
//    REQUIRE(pkb->relationship.modifiesSRelationshipClass.getRHS("3") == unordered_set<string>{});
//
//
//    for (auto& iter : statementToVariablesModifiedMap) {
//
//        string statement = std::to_string(iter.first);
//        unordered_set<string> variablesModified = iter.second;
//
//        for (string v : variablesModified) {
//            REQUIRE(pkb->relationship.modifiesSRelationshipClass.isRelationship(statement, v));
//
//            unordered_set<string> modifierStatements = pkb->relationship.modifiesSRelationshipClass.getLHS(v);
//            REQUIRE(modifierStatements.find(statement) != modifierStatements.end());
//        }
//
//        REQUIRE(pkb->relationship.modifiesSRelationshipClass.getRHS(statement) == variablesModified);
//
//    }
//
//
//}



//TEST_CASE("Add Assign Node") {
//    pkb->clearPKB();
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
//        pkb->addAssignNode(assignNode);
//    }
//
//    vector<AssignNode *> resultsVector = pkb->getAllAssignNodes();
//    unordered_set<AssignNode *> resultsSet(resultsVector.begin(), resultsVector.end());
//
//    REQUIRE(assignNodesSet == resultsSet);
//
//}
