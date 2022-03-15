#include <string>
#include <vector>

using namespace std;

//#include "PKB/FKB.h"
#include "FKB.h"

//#include "PKB/Statement/Statement.h"

//#include "Statement-Old/AbstractStatement.h"


FKB *FKB::singleton = nullptr;

FKB::FKB() {

}

FKB* FKB::getInstance() {

    if (FKB::singleton == nullptr) {
        FKB::singleton = new FKB();
    }

    return FKB::singleton;

}


void FKB::clearFKB() {

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