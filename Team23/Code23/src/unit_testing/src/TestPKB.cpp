//
// Created by Karan Dev Sapra on 17/2/22.
//

#include "PKB.h"
#include "TNode/TNode.h"

#include "catch.hpp"

using namespace std;

PKB *pkb = PKB::getInstance();


TEST_CASE("Add statements") {
    pkb->clearPKB();

    REQUIRE(pkb->getAllStatements().empty());

    for (int i = 1; i <= 10; i++) {
        pkb->addStatement(i);
    }

    unordered_set<string> statementsSet = pkb->getAllStatements();

    for (int i = 1; i <= 10; i++) {
        string s = std::to_string(i);

        REQUIRE(pkb->isStatement(s));

        REQUIRE(statementsSet.find(s) != statementsSet.end());
    }

}

TEST_CASE("Add variables") {
    pkb->clearPKB();

    REQUIRE(pkb->getAllVariables().empty());

    unordered_set<string> variables = {"a", "b", "c", "obama", "trump", "biden"};

    for (string v: variables) {
        pkb->addVariable(v);
    }

    unordered_set<string> variablesSet = pkb->getAllVariables();

    for (string v: variables) {
        REQUIRE(pkb->isVariable(v));

        REQUIRE(variablesSet.find(v) != variablesSet.end());
    }

}


TEST_CASE("Add procedures") {
    pkb->clearPKB();

    REQUIRE(pkb->getAllProcedures().empty());

    unordered_set<string> procedures = {"a", "b", "c", "obama", "trump", "biden"};

    for (string p: procedures) {
        pkb->addProcedure(p);
    }

    unordered_set<string> proceduresSet = pkb->getAllProcedures();

    for (string p: procedures) {
        REQUIRE(pkb->isProcedure(p));

        REQUIRE(proceduresSet.find(p) != proceduresSet.end());
    }

}

TEST_CASE("Add constants") {
    pkb->clearPKB();

    REQUIRE(pkb->getAllConstants().empty());

    unordered_set<string> constants = {"1", "2", "3", "1111111111111111111111111111", "123456789012345678901234567890", "99999999999999999999999999999999999999999999999999999"};

    for (string c: constants) {
        pkb->addConstant(c);
    }

    unordered_set<string> constantsSet = pkb->getAllConstants();

    for (string c: constants) {
        REQUIRE(pkb->isConstant(c));

        REQUIRE(constantsSet.find(c) != constantsSet.end());
    }

}


TEST_CASE("Add Assign Statements") {
    pkb->clearPKB();

    REQUIRE(pkb->getAllAssignStatements().empty());

    unordered_set<int> statements = {1, 7, 45, 898, 124214123, 989988999};

    for (int i : statements) {
        pkb->addAssignStatement(i);
    }

    unordered_set<string> assignStatementsSet = pkb->getAllAssignStatements();

    for (int i: statements) {
        string s = std::to_string(i);

        REQUIRE(pkb->isAssignStatement(s));

        REQUIRE(assignStatementsSet.find(s) != assignStatementsSet.end());
    }

}


TEST_CASE("Add Read Statements") {
    pkb->clearPKB();

    REQUIRE(pkb->getAllReadStatements().empty());

    unordered_set<int> statements = {1, 7, 45, 898, 124214123, 989988999};

    for (int i : statements) {
        pkb->addReadStatement(i);
    }

    unordered_set<string> readStatementsSet = pkb->getAllReadStatements();

    for (int i: statements) {
        string s = std::to_string(i);

        REQUIRE(pkb->isReadStatement(s));

        REQUIRE(readStatementsSet.find(s) != readStatementsSet.end());
    }

}

TEST_CASE("Add Print Statements") {
    pkb->clearPKB();

    REQUIRE(pkb->getAllPrintStatements().empty());

    unordered_set<int> statements = {1, 7, 45, 898, 124214123, 989988999};

    for (int i : statements) {
        pkb->addPrintStatement(i);
    }

    unordered_set<string> printStatementsSet = pkb->getAllPrintStatements();

    for (int i: statements) {
        string s = std::to_string(i);

        REQUIRE(pkb->isPrintStatement(s));

        REQUIRE(printStatementsSet.find(s) != printStatementsSet.end());
    }

}


TEST_CASE("Add If Statements") {
    pkb->clearPKB();

    REQUIRE(pkb->getAllIfStatements().empty());

    unordered_set<int> statements = {1, 7, 45, 898, 124214123, 989988999};

    for (int i : statements) {
        pkb->addIfStatement(i);
    }

    unordered_set<string> ifStatementsSet = pkb->getAllIfStatements();

    for (int i: statements) {
        string s = std::to_string(i);

        REQUIRE(pkb->isIfStatement(s));

        REQUIRE(ifStatementsSet.find(s) != ifStatementsSet.end());
    }
}



TEST_CASE("Add While Statements") {
    pkb->clearPKB();

    REQUIRE(pkb->getAllWhileStatements().empty());

    unordered_set<int> statements = {1, 7, 45, 898, 124214123, 989988999};

    for (int i : statements) {
        pkb->addWhileStatement(i);
    }

    unordered_set<string> whileStatementsSet = pkb->getAllWhileStatements();

    for (int i: statements) {
        string s = std::to_string(i);

        REQUIRE(pkb->isWhileStatement(s));

        REQUIRE(whileStatementsSet.find(s) != whileStatementsSet.end());
    }
}


TEST_CASE("Add Follows") {
    pkb->clearPKB();

    REQUIRE(pkb->getFollowee("2").empty());
    REQUIRE(pkb->getFollower("1").empty());

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

        pkb->setFollows(followee, follower);
    }


    REQUIRE(pkb->isFollows("1", "2") == false);
    REQUIRE(pkb->getFollower("2") == unordered_set<string>{});
    REQUIRE(pkb->getFollowee("3") == unordered_set<string>{});

    for (auto& iter : followeeToFollowerMap) {
        string followee = std::to_string(iter.first);
        string follower = std::to_string(iter.second);

        REQUIRE(pkb->isFollows(followee, follower));
        REQUIRE(pkb->getFollower(followee) == unordered_set<string>{follower});
        REQUIRE(pkb->getFollowee(follower) == unordered_set<string>{followee});
    }


}


TEST_CASE("Add FollowsT") {
    pkb->clearPKB();

    REQUIRE(pkb->getFolloweeT("2").empty());
    REQUIRE(pkb->getFollowerT("1").empty());


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
            pkb->setFollowsT(followee, follower);
        }

    }


    REQUIRE(pkb->isFollowsT("1", "3") == false);
    REQUIRE(pkb->getFollower("2") == unordered_set<string>{});
    REQUIRE(pkb->getFollowee("3") == unordered_set<string>{});


    for (auto& iter : tFolloweeToFollowersMap) {
        string followee = std::to_string(iter.first);
        unordered_set<int> followerIntegers = iter.second;
        unordered_set<string> followers;
        for (int follower : followerIntegers) {
            followers.insert(std::to_string(follower));
        }

        for (string follower : followers) {
            REQUIRE(pkb->isFollowsT(followee, follower));

            unordered_set<string> followeesSet = pkb->getFolloweeT(follower);
            REQUIRE(followeesSet.find(followee) != followeesSet.end());
        }

        REQUIRE(pkb->getFollowerT(followee) == followers);
    }


}


TEST_CASE("Add Parent") {
    pkb->clearPKB();

    REQUIRE(pkb->getFollowee("2").empty());
    REQUIRE(pkb->getFollower("1").empty());

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
            pkb->setParent(parent, child);
        }
    }


    REQUIRE(pkb->isParent("1", "3") == false);
    REQUIRE(pkb->getParent("3") == unordered_set<string>{});
    REQUIRE(pkb->getChildren("2") == unordered_set<string>{});


    for (auto& iter : parentToChildrenMap) {

        string parent = std::to_string(iter.first);

        unordered_set<int> childrenIntegers = iter.second;
        unordered_set<string> children;
        for (int child : childrenIntegers) {
            children.insert(std::to_string(child));
        }


        for (string child : children) {
            REQUIRE(pkb->isParent(parent, child));
            REQUIRE(pkb->getParent(child) == unordered_set<string>{parent});
        }

        REQUIRE(pkb->getChildren(parent) == children);

    }


}


TEST_CASE("Add ParentT") {
    pkb->clearPKB();

    REQUIRE(pkb->getParentT("2").empty());
    REQUIRE(pkb->getChildrenT("1").empty());


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
            pkb->setParentT(parent, child);
        }

    }

    REQUIRE(pkb->isParentT("1", "3") == false);
    REQUIRE(pkb->getParentT("3") == unordered_set<string>{});
    REQUIRE(pkb->getChildrenT("2") == unordered_set<string>{});


    for (auto& iter : tParentToChildrenMap) {
        string parent = std::to_string(iter.first);
        unordered_set<int> childrenIntegers = iter.second;
        unordered_set<string> children;
        for (int child : childrenIntegers) {
            children.insert(std::to_string(child));
        }

        for (string child : children) {
            REQUIRE(pkb->isParentT(parent, child));

            unordered_set<string> parentsSet = pkb->getParentT(child);
            REQUIRE(parentsSet.find(parent) != parentsSet.end());
        }

        REQUIRE(pkb->getChildrenT(parent) == children);
    }


}


TEST_CASE("Add Uses") {
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

        pkb->setUses(statement, variablesUsed);

    }

    REQUIRE(pkb->isUses("2", "a") == false);
    REQUIRE(pkb->getUserStatements("unusedVariable") == unordered_set<string>{});
    REQUIRE(pkb->getVariablesUsed("3") == unordered_set<string>{});


    for (auto& iter : statementToVariablesUsedMap) {

        string statement = std::to_string(iter.first);
        unordered_set<string> variablesUsed = iter.second;

        for (string v : variablesUsed) {
            REQUIRE(pkb->isUses(statement, v));

            unordered_set<string> userStatements = pkb->getUserStatements(v);
            REQUIRE(userStatements.find(statement) != userStatements.end());
        }

        REQUIRE(pkb->getVariablesUsed(statement) == variablesUsed);

    }


}



TEST_CASE("Add Modifies") {
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
        unordered_set<string> variablesUsed = iter.second;

        pkb->setModifies(statement, variablesUsed);

    }


    REQUIRE(pkb->isModifies("2", "a") == false);
    REQUIRE(pkb->getModifierStatements("unmodifiedVariable") == unordered_set<string>{});
    REQUIRE(pkb->getVariablesModified("3") == unordered_set<string>{});


    for (auto& iter : statementToVariablesModifiedMap) {

        string statement = std::to_string(iter.first);
        unordered_set<string> variablesModified = iter.second;

        for (string v : variablesModified) {
            REQUIRE(pkb->isModifies(statement, v));

            unordered_set<string> modifierStatements = pkb->getModifierStatements(v);
            REQUIRE(modifierStatements.find(statement) != modifierStatements.end());
        }

        REQUIRE(pkb->getVariablesModified(statement) == variablesModified);

    }


}



TEST_CASE("Add Assign Node") {
    pkb->clearPKB();

    unordered_set<AssignNode *> assignNodesSet;

    for (int stmtNo = 1; stmtNo <= 10; stmtNo++) {
        VariableNode* leftNode = new VariableNode("leftVar");
        VariableNode* rightNode = new VariableNode("rightVar");
        AssignNode* newNode = new AssignNode(stmtNo, leftNode, rightNode);

        assignNodesSet.insert(newNode);
    }

    for (AssignNode *assignNode : assignNodesSet) {
        pkb->addAssignNode(assignNode);
    }

    vector<AssignNode *> resultsVector = pkb->getAllAssignNodes();
    unordered_set<AssignNode *> resultsSet(resultsVector.begin(), resultsVector.end());

    REQUIRE(assignNodesSet == resultsSet);

}
