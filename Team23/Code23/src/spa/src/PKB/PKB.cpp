#include <string>
#include <vector>

using namespace std;

#include "PKB/PKB.h"

//#include "PKB/Statement/Statement.h"

//#include "Statement-Old/AbstractStatement.h"


PKB *PKB::singleton = nullptr;

PKB::PKB() {

}

PKB* PKB::getInstance() {

    if (PKB::singleton == nullptr) {
        PKB::singleton = new PKB();
    }

    return PKB::singleton;

}


void PKB::clearPKB() {

    entity.variables.clear();
    entity.procedures.clear();
    entity.constants.clear();


    statement.statementClass.clear();
    statement.assignStatementClass.clear();
    statement.readStatementClass.clear();
    statement.printStatementClass.clear();
    statement.ifStatementClass.clear();
    statement.whileStatementClass.clear();
    statement.callStatementClass.clear();


    relationship.followsRelationshipClass.clear();
    relationship.tFollowsRelationshipClass.clear();

    relationship.parentRelationshipClass.clear();
    relationship.tParentRelationshipClass.clear();

    relationship.usesSRelationshipClass.clear();
    relationship.usesPRelationshipClass.clear();

    relationship.modifiesSRelationshipClass.clear();
    relationship.modifiesPRelationshipClass.clear();

}